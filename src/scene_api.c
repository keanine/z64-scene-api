#include "scene_api.h"

#define REPLACED_SCENE SCENE_INSIDETOWER
#define REPLACED_SCENE_ENTR 0xC010

struct SceneAPI_CustomScene customScenes[500];
struct SceneAPI_ExitOverride exitOverrides[500];

u32 customSceneIterator = 0;
u32 exitOverrideIterator = 0;

#define VANILLA_ID 65535
u16 customSceneId = VANILLA_ID;
u16 nextCustomSceneId = VANILLA_ID;

void SceneAPI_SetSceneAtIndex(u8 customSceneIndex, char* name, SceneCmd* header, SceneCmd* rooms[], SceneAPI_Exit exitIDs[]) {
    customScenes[customSceneIndex] = (struct SceneAPI_CustomScene){ name, header, rooms, exitIDs };
    recomp_printf("%s Initialized in Slot %x\n", name, customSceneIndex);
}

void SceneAPI_AddScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[], SceneAPI_Exit exitIDs[]) {
    customScenes[customSceneIterator++] = (struct SceneAPI_CustomScene){ sceneName, header, rooms, exitIDs };
    recomp_printf("Scene %s Initialized in Slot %x\n", sceneName, customSceneIterator - 1);

    // Automatically build an export for the scene id so other mods can access it.
    // Look at EZTR for how Schmitty did it perhaps?
}

void SceneAPI_AddExitOverride(SceneId originalScene, u16 originalEntranceId, u16 newCustomSceneId) {
    exitOverrides[exitOverrideIterator++] = (SceneAPI_ExitOverride){ originalScene, originalEntranceId, newCustomSceneId };
}

u8 nextEntranceModified = false;
u16 modifiedNextEntrance = -1;
PlayState* sceneAPI_play;
RECOMP_HOOK("func_808354A4") void func_808354A4(PlayState* play, s32 exitIndex, s32 arg2) {
    sceneAPI_play = play;

    if (customSceneId != VANILLA_ID) {
        nextEntranceModified = true;
        recomp_printf("Exit Index %d\n", exitIndex);

        if (customScenes[customSceneId].exitIdList[exitIndex].exitType == EXITTYPE_MODDED) {
            recomp_printf("New Destination (Modded): %d\n", customScenes[customSceneId].exitIdList[exitIndex]);
            modifiedNextEntrance = REPLACED_SCENE_ENTR;
            nextCustomSceneId = customScenes[customSceneId].exitIdList[exitIndex].id;
        } else {
            recomp_printf("New Destination (Vanilla): %d\n", customScenes[customSceneId].exitIdList[exitIndex]);
            modifiedNextEntrance = customScenes[customSceneId].exitIdList[exitIndex].id;
            nextCustomSceneId = VANILLA_ID;
            customSceneId = VANILLA_ID;
        }
    }
    else {
        nextCustomSceneId = VANILLA_ID;
        for (u32 i = 0; i < ARRAY_COUNT(exitOverrides); i++) {
            if (play->sceneId == exitOverrides[i].originalScene) {
                if (play->setupExitList[exitIndex] == exitOverrides[i].originalEntranceId) {
                    modifiedNextEntrance = REPLACED_SCENE_ENTR;
                    nextCustomSceneId = exitOverrides[i].newCustomSceneId;
                    nextEntranceModified = true;
                    break;
                }
            }
        }
    }
}

RECOMP_HOOK_RETURN("func_808354A4") void func_808354A4_Return() {
    if (nextEntranceModified) {
        sceneAPI_play->nextEntrance = modifiedNextEntrance;
        nextEntranceModified = false;
    }
}

RECOMP_HOOK("Play_InitScene") void on_init_scene(PlayState* play, s32 spawn) {
    recomp_printf("Spawning into scene %d (spawn %d)\n", play->sceneId, spawn);
    
    if (nextCustomSceneId != 65535) {
        if (play->sceneId == REPLACED_SCENE) {
            customSceneId = nextCustomSceneId;
            nextCustomSceneId = VANILLA_ID;
            // No need to free the original memory since it's part of an arena and will get freed automatically when resetting between scenes.
            play->sceneSegment = customScenes[customSceneId].sceneSegment;
        }
    }
}

RECOMP_HOOK("Room_RequestNewRoom") void on_room_request(PlayState* play, RoomContext* roomCtx, s32 index) {
    if (customSceneId != 65535) {
        if (play->sceneId == REPLACED_SCENE && roomCtx->status == 0) {
            roomCtx->prevRoom = roomCtx->curRoom;
            roomCtx->curRoom.num = index;
            roomCtx->curRoom.segment = NULL;
            roomCtx->status = 1;
            roomCtx->roomRequestAddr = customScenes[customSceneId].roomList[index];
            roomCtx->activeBufPage ^= 1;

            // Record that a room load request has to be sent after the request function returns.
            osCreateMesgQueue(&roomCtx->loadQueue, roomCtx->loadMsg, ARRAY_COUNT(roomCtx->loadMsg));
            osSendMesg(&roomCtx->loadQueue, NULL, OS_MESG_NOBLOCK);
        }
    }
}

RECOMP_HOOK("BgCheck_GetSpecialSceneMaxObjects") void set_col_memsize(PlayState* play, s32* maxNodes, s32* maxPolygons, s32* maxVertices) {
    if (customSceneId != 65535) {
        if (play->sceneId == REPLACED_SCENE) {
            play->colCtx.memSize = 0x23000 * 2; // increase this if you need more surface nodes
        }
    }
}