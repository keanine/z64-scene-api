#include "scene_api_exit.h"
#include "scene_api.h"

// Override the exit transition to lead to the new exit location
RECOMP_HOOK("func_808354A4") void on_Exit(PlayState* play, s32 exitIndex, s32 arg2) {
    sceneAPI_play = play;
    sceneAPI_nextCustomSceneId = SCENEAPI_VANILLA_ID;
    
    // for (u32 i = 0; i < ARRAY_COUNT(sceneAPI_exitOverrides); i++) {
    //     if (play->sceneId == sceneAPI_exitOverrides[i].originalScene) {
    //         if (play->setupExitList[exitIndex] == sceneAPI_exitOverrides[i].originalEntranceId) {
    //             sceneAPI_isNextEntranceModified = true;

    //             if (sceneAPI_exitOverrides[i].newExit.sceneType == SCENEAPI_SCENETYPE_MODDED) {
    //                 sceneAPI_modifiedNextEntrance = SCENEAPI_SCENE_ENTR;
    //                 // Change the entrance id as well to the custom one
    //                 sceneAPI_nextCustomSceneId = SceneAPI_GetSceneIdByName(sceneAPI_exitOverrides[i].newExit.sceneName);
    //                 recomp_printf("Override Destination (Modded): %s\n", sceneAPI_exitOverrides[i].newExit.sceneName);
    //             }
    //             else {
    //                 sceneAPI_modifiedNextEntrance = sceneAPI_exitOverrides[i].newExit.sceneId;
    //                 sceneAPI_nextCustomSceneId = SCENEAPI_VANILLA_ID;
    //                 sceneAPI_isNextEntranceModified = true;
    //                 recomp_printf("Override Destination (Vanilla): %d\n", sceneAPI_exitOverrides[i].newExit.sceneId);
    //             }
    //             break;
    //         }
    //     }
    // }

    for (u32 i = 0; i < ARRAY_COUNT(sceneAPI_exitOverrides); i++) {
        if (IsCurrentScene(play, sceneAPI_exitOverrides[i].fromScene)) {
            if (exitIndex == sceneAPI_exitOverrides[i].exitIndex) {
                sceneAPI_currentExitOverride = &sceneAPI_exitOverrides[i];
                sceneAPI_isNextEntranceModified = true;

                if (sceneAPI_currentExitOverride->toScene.sceneType == SCENEAPI_SCENETYPE_MODDED) {
                    sceneAPI_modifiedNextEntrance = SCENEAPI_SCENE_ENTR;
                    sceneAPI_nextCustomSceneId = SceneAPI_GetSceneIdByName(sceneAPI_currentExitOverride->toScene.sceneName);
                    recomp_printf("Override Destination (Modded): %s\n", sceneAPI_currentExitOverride->toScene.sceneName);
                }
                else { 
                    sceneAPI_modifiedNextEntrance = sceneAPI_exitOverrides[i].toScene.sceneId;
                    sceneAPI_nextCustomSceneId = SCENEAPI_VANILLA_ID;
                    recomp_printf("Override Destination (Vanilla): %d\n", sceneAPI_currentExitOverride->toScene.sceneId);
                }
            }
        }
    }
}

// Apply the new exit if an override was found
RECOMP_HOOK_RETURN("func_808354A4") void return_Exit() {
    if (sceneAPI_isNextEntranceModified) {
        sceneAPI_play->nextEntrance = ((((sceneAPI_entrances[sceneAPI_currentExitOverride->toScene.sceneId]) & 0x7F) << 9) | (((sceneAPI_currentExitOverride->exitIndex) & 0x1F) << 4));
        sceneAPI_isNextEntranceModified = false;
    }
}

// When the player voids out, make sure the next custom scene is the current custom scene
RECOMP_HOOK("func_80169EFC") void on_Gameplay_TriggerVoidOut(PlayState* this) {
    if (sceneAPI_customSceneId != 65535) {
        sceneAPI_nextCustomSceneId = sceneAPI_customSceneId;
    }
}