#include "scene_api.h"
#include "ProxyMM_ObjDepLoader.h"
#include <overlays/actors/ovl_Door_Ana/z_door_ana.h>
#include <z64scene.h>

struct SceneAPI_CustomScene sceneAPI_customScenes[500];
struct SceneAPI_ExitOverride sceneAPI_exitOverrides[500];
struct SceneAPI_Grotto sceneAPI_grottos[500];

u32 sceneAPI_customSceneIterator = 0;
u32 sceneAPI_exitOverrideIterator = 0;
u32 sceneAPI_grottosIterator = 0;

u8 sceneAPI_isNextEntranceModified = false;
u16 sceneAPI_modifiedNextEntrance = -1;
u16 sceneAPI_savedGrottoEntrance = 0;

PlayState* sceneAPI_play = NULL;
SceneAPI_Grotto* sceneAPI_currentGrotto = NULL;

u16 sceneAPI_customSceneId = SCENEAPI_VANILLA_ID;
u16 sceneAPI_nextCustomSceneId = SCENEAPI_VANILLA_ID;

// Used to register custom scenes from external scene mods
RECOMP_CALLBACK("*", recomp_on_init)
void SceneAPI_RecompInit() {
    recomp_printf("\n== Initializing Scene API ==\n");
    
    // Register custom scenes
    SceneAPI_Init();
    
    // Register grottos and exit overrides
    SceneAPI_PostInit();
    
    recomp_printf("== Scene API Initialized ==\n\n");
    recomp_printf("Scene: %x\n", SCENE_INSIDETOWER);
    recomp_printf("Entr: %x\n", ENTR_SCENE_CLOCK_TOWER_INTERIOR);
    recomp_printf("Entr w/ exit: %x\n", ENTRANCE(CLOCK_TOWER_INTERIOR, 1));
}

// Override the sceneSegment as well as setting the customSceneId
RECOMP_HOOK("Play_InitScene") void on_init_scene(PlayState* play, s32 spawn) {
    recomp_printf("Spawning into scene %d (spawn %d)\n", play->sceneId, spawn);
    
    if (sceneAPI_nextCustomSceneId != 65535) {
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
    if (sceneAPI_customSceneId != 65535) {
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
    if (sceneAPI_customSceneId != 65535) {
        if (play->sceneId == SCENEAPI_SCENE) {
            play->colCtx.memSize = 0x23000 * 2; // increase this if you need more surface nodes
        }
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