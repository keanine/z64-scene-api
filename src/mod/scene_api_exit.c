#include "scene_api_exit.h"

SceneAPI_ExitOverride* sceneAPI_currentExitOverride = NULL;

struct SceneAPI_ExitOverride sceneAPI_exitOverrides[SCENEAPI_MAX_ARRAY];
u32 sceneAPI_exitOverrideCount = 0;

// Override the exit transition to lead to the new exit location
RECOMP_HOOK("func_808354A4") void on_Exit(PlayState* play, s32 exitIndex, s32 arg2) {
    sceneAPI_play = play;
    sceneAPI_nextCustomSceneId = SCENEAPI_INVALID;

    for (u32 i = 0; i < ARRAY_COUNT(sceneAPI_exitOverrides); i++) {
        if (SceneAPI_IsCurrentScene(play, sceneAPI_exitOverrides[i].fromScene)) {
            if (exitIndex == sceneAPI_exitOverrides[i].exitIndex) {
                sceneAPI_currentExitOverride = &sceneAPI_exitOverrides[i];
                sceneAPI_isNextEntranceModified = true;

                if (sceneAPI_currentExitOverride->toScene.sceneType == SCENEAPI_SCENETYPE_MODDED) {
                    sceneAPI_nextCustomSceneId = SceneAPI_GetSceneIdByName(sceneAPI_currentExitOverride->toScene.sceneName);
                    recomp_printf("Override Destination (Modded): %s\n", sceneAPI_currentExitOverride->toScene.sceneName);
                }
                else {
                    sceneAPI_nextCustomSceneId = SCENEAPI_INVALID;
                    recomp_printf("Override Destination (Vanilla): %d\n", sceneAPI_currentExitOverride->toSceneId);
                }
            }
        }
    }
}

// Apply the new exit if an override was found
RECOMP_HOOK_RETURN("func_808354A4") void return_Exit() {
    if (sceneAPI_isNextEntranceModified) {
        recomp_printf("toscene entrId: %d", sceneAPI_currentExitOverride->toScene.entrId);
        sceneAPI_play->nextEntrance = SCENEAPI_ENTRANCE(sceneAPI_currentExitOverride->toScene.entrId, sceneAPI_currentExitOverride->exitIndex);
        sceneAPI_isNextEntranceModified = false;
    }
}

// When the player voids out, make sure the next custom scene is the current custom scene
RECOMP_HOOK("func_80169EFC") void on_Gameplay_TriggerVoidOut(PlayState* this) {
    if (sceneAPI_customSceneId != SCENEAPI_INVALID) {
        sceneAPI_nextCustomSceneId = sceneAPI_customSceneId;
    }
}