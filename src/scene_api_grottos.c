#include "scene_api_grottos.h"
#include <overlays/actors/ovl_Door_Ana/z_door_ana.h>

#include "scene_api.h"

// Spawn registered grottos
RECOMP_HOOK("Cutscene_HandleEntranceTriggers") void on_PostInit(PlayState* play) {
    for (u32 i = 0; i < sceneAPI_grottosIterator; i++) {
        if (play->sceneId == sceneAPI_warpGrottos[i].scene && (sceneAPI_customSceneId == SCENEAPI_VANILLA_ID || (sceneAPI_customSceneId != SCENEAPI_VANILLA_ID && sceneAPI_customSceneId == sceneAPI_warpGrottos[i].customSceneIndex))) {
            if (sceneAPI_customSceneId == SCENEAPI_VANILLA_ID || 
                (sceneAPI_customSceneId != SCENEAPI_VANILLA_ID && sceneAPI_warpGrottos[i].customSceneIndex == sceneAPI_customSceneId)) {
                sceneAPI_warpGrottos[i].actor = Actor_Spawn(&play->actorCtx, play, ACTOR_DOOR_ANA, sceneAPI_warpGrottos[i].x, sceneAPI_warpGrottos[i].y, sceneAPI_warpGrottos[i].z, SPAWN_ROT_FLAGS(0, 0x0007), SPAWN_ROT_FLAGS(0X86,0x000D), SPAWN_ROT_FLAGS(0, 0x007F), 0x0304);
            }
        }
    }
}

// Select the current registered grotto's data
RECOMP_HOOK("DoorAna_WaitOpen") void on_DoorAna_WaitOpen(DoorAna* this, PlayState* play) {
    sceneAPI_play = play;

    for (u32 i = 0; i < sceneAPI_grottosIterator; i++) {
        if (sceneAPI_warpGrottos[i].actor == this) {
            sceneAPI_currentGrotto = &sceneAPI_warpGrottos[i];
            sceneAPI_savedGrottoEntrance = play->nextEntrance;
            return;
        }
    }
    sceneAPI_currentGrotto = NULL;
}

// Override the exit location of the current grotto if it is registered as a scene API grotto
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