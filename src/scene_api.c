#include "scene_api.h"
#include "ProxyMM_ObjDepLoader.h"
#include <overlays/actors/ovl_Door_Ana/z_door_ana.h>
#include <z64scene.h>

RECOMP_CALLBACK("*", recomp_on_init)
void SceneAPI_RecompInit() {
    recomp_printf("\n== Initializing Scene API ==\n");
    SceneAPI_Init();
    SceneAPI_PostInit();
    recomp_printf("== Scene API Initialized ==\n\n");
    recomp_printf("Scene: %x\n", SCENE_INSIDETOWER);
    recomp_printf("Entr: %x\n", ENTR_SCENE_CLOCK_TOWER_INTERIOR);
    recomp_printf("Entr w/ exit: %x\n", ENTRANCE(CLOCK_TOWER_INTERIOR, 1));
}

void SceneAPI_SetSceneAtIndex(u8 customSceneIndex, char* name, SceneCmd* header, SceneCmd* rooms[], SceneAPI_Exit exitIDs[]) {
    sceneAPI_customScenes[customSceneIndex] = (struct SceneAPI_CustomScene){ name, header, rooms, exitIDs };
    recomp_printf("%s Initialized in Slot %x\n", name, customSceneIndex);
}

u16 SceneAPI_AddScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[], SceneAPI_Exit exitIDs[]) {
    u16 slot = sceneAPI_customSceneIterator;
    sceneAPI_customScenes[sceneAPI_customSceneIterator++] = (struct SceneAPI_CustomScene){ sceneName, header, rooms, exitIDs };
    recomp_printf("Scene %s Initialized in Slot %x\n", sceneName, slot);
    return slot;
}

void SceneAPI_AddExitOverride(SceneId originalScene, u16 originalEntranceId, SceneAPI_Exit exit) {
    sceneAPI_exitOverrides[sceneAPI_exitOverrideIterator++] = (SceneAPI_ExitOverride){ originalScene, originalEntranceId, exit };
}

void SceneAPI_AddGrotto(SceneId scene, SceneAPI_Exit exit, f32 x, f32 y, f32 z) {
    sceneAPI_grottos[sceneAPI_grottosIterator++] = (SceneAPI_Grotto){ scene, SCENEAPI_VANILLA_ID, exit, x, y, z, NULL };
}

void SceneAPI_AddGrottoToCustomScene(char* sceneName, SceneAPI_Exit exit, f32 x, f32 y, f32 z) {
    sceneAPI_grottos[sceneAPI_grottosIterator++] = (SceneAPI_Grotto){ SCENEAPI_SCENE, SceneAPI_GetSceneIdByName(sceneName), exit, x, y, z, NULL };
}

u16 SceneAPI_GetSceneIdByName(char* name) {
    for (u16 i = 0; i < ARRAY_COUNT(sceneAPI_customScenes); i++) {
        if (sceneAPI_customScenes[i].sceneName == name) {
            return i;
        }
    }
}

RECOMP_HOOK("func_808354A4") void on_Exit(PlayState* play, s32 exitIndex, s32 arg2) {
    sceneAPI_play = play;
    if (sceneAPI_customSceneId != SCENEAPI_VANILLA_ID) {
        sceneAPI_isNextEntranceModified = true;
        recomp_printf("Exit Index %d\n", exitIndex);

        if (sceneAPI_customScenes[sceneAPI_customSceneId].exitIdList[exitIndex].exitType == SCENEAPI_EXITTYPE_MODDED) {
            recomp_printf("Exit Destination (Modded): %s\n", sceneAPI_customScenes[sceneAPI_customSceneId].exitIdList[exitIndex].sceneName);
            sceneAPI_modifiedNextEntrance = SCENEAPI_SCENE_ENTR;
            // Change the entrance id as well to the custom one
            sceneAPI_nextCustomSceneId = SceneAPI_GetSceneIdByName(sceneAPI_customScenes[sceneAPI_customSceneId].exitIdList[exitIndex].sceneName);
        } else {
            recomp_printf("Exit Destination (Vanilla): %d\n", sceneAPI_customScenes[sceneAPI_customSceneId].exitIdList[exitIndex].id);
            sceneAPI_modifiedNextEntrance = sceneAPI_customScenes[sceneAPI_customSceneId].exitIdList[exitIndex].id;
            sceneAPI_nextCustomSceneId = SCENEAPI_VANILLA_ID;
            sceneAPI_customSceneId = SCENEAPI_VANILLA_ID;
        }
    }
    else {
        sceneAPI_nextCustomSceneId = SCENEAPI_VANILLA_ID;
        for (u32 i = 0; i < ARRAY_COUNT(sceneAPI_exitOverrides); i++) {
            if (play->sceneId == sceneAPI_exitOverrides[i].originalScene) {
                if (play->setupExitList[exitIndex] == sceneAPI_exitOverrides[i].originalEntranceId) {
                    sceneAPI_isNextEntranceModified = true;

                    if (sceneAPI_exitOverrides[i].newExit.exitType == SCENEAPI_EXITTYPE_MODDED) {
                        sceneAPI_modifiedNextEntrance = SCENEAPI_SCENE_ENTR;
                        // Change the entrance id as well to the custom one
                        sceneAPI_nextCustomSceneId = SceneAPI_GetSceneIdByName(sceneAPI_exitOverrides[i].newExit.sceneName);
                        recomp_printf("Override Destination (Modded): %s\n", sceneAPI_exitOverrides[i].newExit.sceneName);
                    }
                    else {
                        sceneAPI_modifiedNextEntrance = sceneAPI_exitOverrides[i].newExit.id;
                        sceneAPI_nextCustomSceneId = SCENEAPI_VANILLA_ID;
                        sceneAPI_isNextEntranceModified = true;
                        recomp_printf("Override Destination (Vanilla): %d\n", sceneAPI_exitOverrides[i].newExit.id);
                    }
                    break;
                }
            }
        }
    }
}

RECOMP_HOOK_RETURN("func_808354A4") void func_808354A4_Return() {
    if (sceneAPI_isNextEntranceModified) {
        sceneAPI_play->nextEntrance = sceneAPI_modifiedNextEntrance;
        sceneAPI_isNextEntranceModified = false;
    }
}

RECOMP_HOOK("Cutscene_HandleEntranceTriggers") void on_PostInit(PlayState* play) {
    for (u32 i = 0; i < sceneAPI_grottosIterator; i++) {
        if (play->sceneId == sceneAPI_grottos[i].scene && (sceneAPI_customSceneId == SCENEAPI_VANILLA_ID || (sceneAPI_customSceneId != SCENEAPI_VANILLA_ID && sceneAPI_customSceneId == sceneAPI_grottos[i].customSceneIndex))) {
            if (sceneAPI_customSceneId == SCENEAPI_VANILLA_ID || 
                (sceneAPI_customSceneId != SCENEAPI_VANILLA_ID && sceneAPI_grottos[i].customSceneIndex == sceneAPI_customSceneId)) {
                sceneAPI_grottos[i].actor = Actor_Spawn(&play->actorCtx, play, ACTOR_DOOR_ANA, sceneAPI_grottos[i].x, sceneAPI_grottos[i].y, sceneAPI_grottos[i].z, SPAWN_ROT_FLAGS(    0, 0x0007), SPAWN_ROT_FLAGS(0X86,0x000D),SPAWN_ROT_FLAGS(0, 0x007F), 0x0304);
            }
        }
    }
}

RECOMP_HOOK("DoorAna_WaitOpen") void on_DoorAna_WaitOpen(DoorAna* this, PlayState* play) {
    sceneAPI_play = play;

    for (u32 i = 0; i < sceneAPI_grottosIterator; i++) {
        if (sceneAPI_grottos[i].actor == this) {
            sceneAPI_currentGrotto = &sceneAPI_grottos[i];
            sceneAPI_savedGrottoEntrance = play->nextEntrance;
            return;
        }
    }
    sceneAPI_currentGrotto = NULL;
}

RECOMP_HOOK_RETURN("DoorAna_WaitOpen") void return_DoorAna_WaitOpen() {

    if (sceneAPI_currentGrotto != NULL && sceneAPI_savedGrottoEntrance != sceneAPI_play->nextEntrance) {
        sceneAPI_play->nextEntrance = SCENEAPI_SCENE_ENTR;
        if (sceneAPI_currentGrotto->exit.exitType == SCENEAPI_EXITTYPE_MODDED) {
            sceneAPI_modifiedNextEntrance = SCENEAPI_SCENE_ENTR;
            sceneAPI_nextCustomSceneId = SceneAPI_GetSceneIdByName(sceneAPI_currentGrotto->exit.sceneName);
            recomp_printf("Grotto Destination (Modded): %s\n", sceneAPI_currentGrotto->exit.sceneName);
        }
        else {
            sceneAPI_modifiedNextEntrance = sceneAPI_currentGrotto->exit.id;
            sceneAPI_nextCustomSceneId = SCENEAPI_VANILLA_ID;
            sceneAPI_isNextEntranceModified = true;
            recomp_printf("Grotto Destination (Vanilla): %d\n", sceneAPI_currentGrotto->exit.id);
        }
    }
}

// When the player voids out, make sure the next custom scene is the current custom scene
RECOMP_HOOK("func_80169EFC") void on_Gameplay_TriggerVoidOut(PlayState* this) {
    if (sceneAPI_customSceneId != 65535) {
        sceneAPI_nextCustomSceneId = sceneAPI_customSceneId;
    }
}

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

RECOMP_HOOK("BgCheck_GetSpecialSceneMaxObjects") void set_col_memsize(PlayState* play, s32* maxNodes, s32* maxPolygons, s32* maxVertices) {
    if (sceneAPI_customSceneId != 65535) {
        if (play->sceneId == SCENEAPI_SCENE) {
            play->colCtx.memSize = 0x23000 * 2; // increase this if you need more surface nodes
        }
    }
}
