#include "scene_api.h"
#include "ProxyMM_ObjDepLoader.h"
#include <overlays/actors/ovl_Door_Ana/z_door_ana.h>
#include <z64scene.h>

struct SceneAPI_CustomScene sceneAPI_customScenes[500];
struct SceneAPI_ExitOverride sceneAPI_exitOverrides[500];
struct SceneAPI_Grotto sceneAPI_warpGrottos[500];

u32 sceneAPI_customSceneIterator = 0;
u32 sceneAPI_exitOverrideIterator = 0;
u32 sceneAPI_grottosIterator = 0;

u8 sceneAPI_isNextEntranceModified = false;
u16 sceneAPI_savedGrottoEntrance = 0;

PlayState* sceneAPI_play = NULL;
SceneAPI_Grotto* sceneAPI_currentGrotto = NULL;
SceneAPI_ExitOverride* sceneAPI_currentExitOverride = NULL;

u16 sceneAPI_customSceneId = SCENEAPI_VANILLA_ID;
u16 sceneAPI_nextCustomSceneId = SCENEAPI_VANILLA_ID;

u8 sceneAPI_modifiedElegyScene = false;

// Used to register custom scenes from external scene mods
RECOMP_CALLBACK("*", recomp_on_init)
void SceneAPI_RecompInit() {
    recomp_printf("\n== Initializing Scene API ==\n");
    
    // Register custom scenes
    SceneAPI_Init();
    
    // Register warp grottos and exit overrides
    SceneAPI_PostInit();
    
    recomp_printf("== Scene API Initialized ==\n\n");
}

// Override the sceneSegment as well as setting the customSceneId
RECOMP_HOOK("Play_InitScene") void on_init_scene(PlayState* play, s32 spawn) {
    recomp_printf("Spawning into scene %d (spawn %d)\n", play->sceneId, spawn);
    
    if (sceneAPI_nextCustomSceneId != SCENEAPI_VANILLA_ID) {
        if (play->sceneId == SCENEAPI_SCENE) {
            sceneAPI_customSceneId = sceneAPI_nextCustomSceneId;
            sceneAPI_nextCustomSceneId = SCENEAPI_VANILLA_ID;
            // No need to free the original memory since it's part of an arena and will get freed automatically when resetting between scenes.
            play->sceneSegment = sceneAPI_customScenes[sceneAPI_customSceneId].sceneSegment;
        }
    }
}

// Overrides the room list
RECOMP_HOOK("Room_RequestNewRoom") void on_room_request(PlayState* play, RoomContext* roomCtx, s32 index) {
    if (sceneAPI_customSceneId != SCENEAPI_VANILLA_ID) {
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
    if (sceneAPI_customSceneId != SCENEAPI_VANILLA_ID) {
        if (play->sceneId == SCENEAPI_SCENE) {
            play->colCtx.memSize = 0x23000 * 2; // increase this if you need more surface nodes
        }
    }
}

// If the elegy of emptiness is played, check if the custom scene allows it
RECOMP_HOOK("Message_DrawMain") void on_Message_DrawMain(PlayState* play, Gfx** gfxP) {
    MessageContext* msgCtx = &play->msgCtx;
    sceneAPI_play = play;

    if (sceneAPI_customSceneId != SCENEAPI_VANILLA_ID && play->sceneId == SCENEAPI_SCENE) {
        if (msgCtx->msgLength != 0) {
            if (msgCtx->msgMode == MSGMODE_18) {
                if (sceneAPI_customScenes[sceneAPI_customSceneId].properties.enableElegyOfEmptiness) {
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
    for (u16 i = 0; i < ARRAY_COUNT(sceneAPI_customScenes); i++) {
        if (sceneAPI_customScenes[i].sceneName == name) {
            return i;
        }
    }
    return -1;
}

u8 IsCurrentScene(PlayState* play, SceneAPI_SceneId scene) {
    switch (scene.sceneType) {
        case SCENEAPI_SCENETYPE_VANILLA:
            return (play->sceneId == sceneAPI_entranceId_to_sceneId[scene.entrId]);
        case SCENEAPI_SCENETYPE_MODDED:
            return (play->sceneId == SCENEAPI_SCENE && sceneAPI_customSceneId == SceneAPI_GetSceneIdByName(scene.sceneName));
    }
    return false;
}