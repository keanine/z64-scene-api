#include "scene_api.h"
#include "ProxyMM_ObjDepLoader.h"
#include <overlays/actors/ovl_Door_Ana/z_door_ana.h>
#include <z64scene.h>

struct SceneAPI_CustomScene sceneAPI_customScenes[SCENEAPI_MAX_ARRAY];
u32 sceneAPI_customSceneCount = 0;

bool sceneAPI_isNextEntranceModified = false;

PlayState* sceneAPI_play = NULL;

u16 sceneAPI_customSceneId = SCENEAPI_INVALID;
u16 sceneAPI_nextCustomSceneId = SCENEAPI_INVALID;

u8 sceneAPI_modifiedElegyScene = false;

#define DEFINE_SCENE(name, textId, drawConfig) \
    { { SEGMENT_ROM_START(name), SEGMENT_ROM_END(name) }, textId, 0, drawConfig, 0, 0 }
SceneTableEntry entrySceneTableEntry = DEFINE_SCENE(Z2_INSIDETOWER, 0x11F, SCENE_DRAW_CFG_MAT_ANIM);
#undef DEFINE_SCENE


static EntranceTableEntry sCustomEntrance0[] = { { SCENE_UNSET_01, 0, 0x0102 } };
static EntranceTableEntry sCustomEntrance1[] = { { SCENE_UNSET_01, 1, 0x0102 } };
static EntranceTableEntry sCustomEntrance2[] = { { SCENE_UNSET_01, 2, 0x0102 } };
static EntranceTableEntry sCustomEntrance3[] = { { SCENE_UNSET_01, 3, 0x0102 } };
static EntranceTableEntry sCustomEntrance4[] = { { SCENE_UNSET_01, 4, 0x0102 } };
static EntranceTableEntry sCustomEntrance5[] = { { SCENE_UNSET_01, 5, 0x0102 } };
static EntranceTableEntry sCustomEntrance6[] = { { SCENE_UNSET_01, 6, 0x0102 } };
static EntranceTableEntry sCustomEntrance7[] = { { SCENE_UNSET_01, 7, 0x0102 } };
static EntranceTableEntry sCustomEntrance8[] = { { SCENE_UNSET_01, 8, 0x0102 } };
static EntranceTableEntry sCustomEntrance9[] = { { SCENE_UNSET_01, 9, 0x0102 } };
static EntranceTableEntry sCustomEntrance10[] = { { SCENE_UNSET_01, 10, 0x0102 } };
static EntranceTableEntry sCustomEntrance11[] = { { SCENE_UNSET_01, 11, 0x0102 } };

static EntranceTableEntry* sCustomEntranceTable[] = {
    sCustomEntrance0,sCustomEntrance1,sCustomEntrance2,
    sCustomEntrance3,sCustomEntrance4,sCustomEntrance5,
    sCustomEntrance6,sCustomEntrance7,sCustomEntrance8,
    sCustomEntrance9,sCustomEntrance10,sCustomEntrance11,
};

extern SceneEntranceTableEntry sSceneEntranceTable[];

// Used to register custom scenes from external scene mods
RECOMP_CALLBACK("*", recomp_on_init)
void SceneAPI_RecompInit() {
    recomp_printf("\n== Initializing Scene API ==\n");
    
    // Register custom scenes
    SceneAPI_Init();
    
    // Register warp grottos and exit overrides
    SceneAPI_PostInit();
    
    // Set the custom scenes table entry
    gSceneTable[SCENEAPI_SCENE] = entrySceneTableEntry;
    
    recomp_printf("== Scene API Initialized ==\n\n");
}

bool IsSceneCustom(u16 sceneId) {
    
}

// Override the sceneSegment as well as setting the customSceneId
RECOMP_HOOK("Play_InitScene") void on_init_scene(PlayState* play, s32 spawn) {
    recomp_printf("Spawning into scene %d (spawn %d)\n", play->sceneId, spawn);
    sceneAPI_play = play;

    // Set the custom scenes entrance table // THIS SHOULD HAPPEN ONCE, AFTER RECOMP_INIT
    sSceneEntranceTable[SCENEAPI_SCENE_ENTR] = (SceneEntranceTableEntry)SCENEAPI_DEFINE_ENTRANCE(sCustomEntranceTable);
    SceneEntranceTableEntry entry = sSceneEntranceTable[SCENEAPI_SCENE_ENTR];

    // Reset the customSceneId to default
    sceneAPI_customSceneId = SCENEAPI_INVALID;

    if (sceneAPI_nextCustomSceneId != SCENEAPI_INVALID) {
        if (play->sceneId == SCENEAPI_SCENE) {
            sceneAPI_customSceneId = sceneAPI_nextCustomSceneId;
            sceneAPI_nextCustomSceneId = SCENEAPI_INVALID;

            sRestrictionFlags[SCENEAPI_SCENE] = SceneAPI_GetRestrictionsFromCustomScene(sceneAPI_customSceneId);

            // No need to free the original memory since it's part of an arena and will get freed automatically when resetting between scenes.
            play->sceneSegment = sceneAPI_customScenes[sceneAPI_customSceneId].sceneSegment;
        }
    }
}

// Overrides the room list
RECOMP_HOOK("Room_RequestNewRoom") void on_room_request(PlayState* play, RoomContext* roomCtx, s32 index) {
    if (sceneAPI_customSceneId != SCENEAPI_INVALID) {
        if (play->sceneId == SCENEAPI_SCENE && roomCtx->status == 0) {
            roomCtx->prevRoom = roomCtx->curRoom;
            roomCtx->curRoom.num = index;
            roomCtx->curRoom.segment = NULL;
            roomCtx->status = 1;
            roomCtx->roomRequestAddr = sceneAPI_customScenes[sceneAPI_customSceneId].roomList[index];
            roomCtx->activeBufPage ^= 1;

            // Record that a room load request has to be sent after the request function returns.
            osCreateMesgQueue(&roomCtx->loadQueue, roomCtx->loadMsg, ARRAY_COUNT(roomCtx->loadMsg));
            osSendMesg(&roomCtx->loadQueue, NULL, OS_MESG_NOBLOCK);
        }
    }
}

// Increases the number of surface nodes
RECOMP_HOOK("BgCheck_GetSpecialSceneMaxObjects") void set_col_memsize(PlayState* play, s32* maxNodes, s32* maxPolygons, s32* maxVertices) {
    if (sceneAPI_customSceneId != SCENEAPI_INVALID) {
        if (play->sceneId == SCENEAPI_SCENE) {
            play->colCtx.memSize = 0x23000 * 2; // increase this if you need more surface nodes
        }
    }
}

// If the elegy of emptiness is played, check if the custom scene allows it
RECOMP_HOOK("Message_DrawMain") void on_Message_DrawMain(PlayState* play, Gfx** gfxP) {
    MessageContext* msgCtx = &play->msgCtx;
    sceneAPI_play = play;

    if (sceneAPI_customSceneId != SCENEAPI_INVALID && play->sceneId == SCENEAPI_SCENE) {
        if (msgCtx->msgLength != 0) {
            if (msgCtx->msgMode == MSGMODE_18) {
                if (sceneAPI_customScenes[sceneAPI_customSceneId].permissions.allowElegyOfEmptiness) {
                    sceneAPI_modifiedElegyScene = true;
                    play->sceneId = SCENE_F40;
                }
            }
        }
    }
}

// Reset elegy variables if they were changed
RECOMP_HOOK_RETURN("Message_DrawMain") void return_Message_DrawMain() {
    MessageContext* msgCtx = &sceneAPI_play->msgCtx;

    if (sceneAPI_modifiedElegyScene) {
        sceneAPI_play->sceneId = SCENEAPI_SCENE;
        sceneAPI_modifiedElegyScene = false;
    }
}

u16 SceneAPI_GetSceneIdByName(char* name) {
    for (u16 i = 0; i < sceneAPI_customSceneCount; i++) {
        if (strcmp(sceneAPI_customScenes[i].sceneName, name) == 0) {
            return i;
        }
    }
    return -1;
}

char* SceneAPI_GetSceneNameById(u32 sceneId) {
    return sceneAPI_customScenes[sceneId].sceneName;
}

bool SceneAPI_IsCurrentScene(PlayState* play, SceneAPI_SceneId scene) {
    switch (scene.sceneType) {
        case SCENEAPI_SCENETYPE_VANILLA:
            return (play->sceneId == sceneAPI_entranceId_to_sceneId[scene.entrId]);
        case SCENEAPI_SCENETYPE_MODDED:
            return (play->sceneId == SCENEAPI_SCENE && sceneAPI_customSceneId == SceneAPI_GetSceneIdByName(scene.sceneName));
    }
    return false;
}

bool SceneAPI_IsCustomScene(PlayState* play) {
    return play->sceneId == SCENEAPI_SCENE;
}

RestrictionFlags SceneAPI_GetRestrictionsFromCustomScene(u16 customSceneId) {
    SceneAPI_ScenePermissions permissions = sceneAPI_customScenes[customSceneId].permissions;

    return (RestrictionFlags){ SCENEAPI_SCENE,
        RESTRICTIONS_SET(
            0,
            permissions.allowButtonB ? 0 : 1,
            0,
            permissions.allowTradeItems ? 0 : 1,
            permissions.allowSongOfTime ? 0 : 1,
            permissions.allowSongOfDoubleTime ? 0 : 1,
            permissions.allowInvertedSongOfTime ? 0 : 1,
            permissions.allowSongOfSoaring ? 0 : 1,
            permissions.allowSongOfStorms ? 0 : 1,
            permissions.allowMasks ? 0 : 1,
            permissions.allowPictoBox ? 0 : 1,
            permissions.allowAll ? 0 : 1
        )
    };
}