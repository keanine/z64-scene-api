#include "scene_api_grottos.h"
#include <overlays/actors/ovl_Door_Ana/z_door_ana.h>

SceneAPI_Grotto* sceneAPI_currentGrotto = NULL;

struct SceneAPI_Grotto sceneAPI_warpGrottos[SCENEAPI_MAX_ARRAY];
u32 sceneAPI_grottosCount = 0;

u16 sceneAPI_savedGrottoEntrance = 0;

// Spawn registered grottos
RECOMP_HOOK("Cutscene_HandleEntranceTriggers") void on_PostInit(PlayState* play) {
    for (u32 i = 0; i < sceneAPI_grottosCount; i++) {
        if (SceneAPI_IsCurrentScene(play, sceneAPI_warpGrottos[i].fromScene)) {
            sceneAPI_warpGrottos[i].actor = Actor_Spawn(&play->actorCtx, play, ACTOR_DOOR_ANA, sceneAPI_warpGrottos[i].x, sceneAPI_warpGrottos[i].y, sceneAPI_warpGrottos[i].z, SPAWN_ROT_FLAGS(0, 0x0007), SPAWN_ROT_FLAGS(0X86,0x000D), SPAWN_ROT_FLAGS(0, 0x007F), 0x0300);
        }
        else {
            sceneAPI_warpGrottos[i].actor = NULL;
        }
    }
}

// Select the current registered grotto's data
RECOMP_HOOK("DoorAna_WaitOpen") void on_DoorAna_WaitOpen(DoorAna* this, PlayState* play) {
    sceneAPI_play = play;
    sceneAPI_currentGrotto = NULL;

    Player* player = GET_PLAYER(play);
    s32 grottoType = DOORANA_GET_TYPE(&this->actor);

    if (Math_StepToF(&this->actor.scale.x, 0.01f, 0.001f)) {
        if ((this->actor.attentionRangeType != ATTENTION_RANGE_0) && (play->transitionTrigger == TRANS_TRIGGER_OFF) &&
            (play->transitionMode == TRANS_MODE_OFF) && (player->stateFlags1 & PLAYER_STATE1_80000000) &&
            (player->av1.actionVar1 == 0)) {

            if (grottoType == DOORANA_TYPE_VISIBLE_SCENE_EXIT) {
                for (u32 i = 0; i < sceneAPI_grottosCount; i++) {
                    if (sceneAPI_warpGrottos[i].actor == &this->actor) {
                        sceneAPI_currentGrotto = &sceneAPI_warpGrottos[i];
                        sceneAPI_savedGrottoEntrance = play->nextEntrance;
                        break;
                    }
                }
            }
        }
    }

}

// Override the exit location of the current grotto if it is registered as a scene API grotto
RECOMP_HOOK_RETURN("DoorAna_WaitOpen") void return_DoorAna_WaitOpen() {
    if (sceneAPI_currentGrotto != NULL && sceneAPI_savedGrottoEntrance != sceneAPI_play->nextEntrance) {
        if (sceneAPI_currentGrotto->toScene.sceneType == SCENEAPI_SCENETYPE_MODDED) {
            sceneAPI_play->nextEntrance = SCENEAPI_ENTRANCE(SCENEAPI_SCENE_ENTR, sceneAPI_currentGrotto->spawnIndex);
            sceneAPI_nextCustomSceneId = SceneAPI_GetSceneIdByName(sceneAPI_currentGrotto->toScene.sceneName);
            recomp_printf("Grotto Destination (Modded): %s\n", sceneAPI_currentGrotto->toScene.sceneName);
        }
        else {            
            sceneAPI_play->nextEntrance = SCENEAPI_ENTRANCE(sceneAPI_currentGrotto->toScene.entrId, sceneAPI_currentGrotto->spawnIndex);
            sceneAPI_nextCustomSceneId = SCENEAPI_INVALID;
            sceneAPI_customSceneId = SCENEAPI_INVALID;
            recomp_printf("Grotto Destination (Vanilla): %d\n", sceneAPI_currentGrotto->toSceneId);
        }
    }
}