#include "scene_api.h"

static PlayState* sPlay;
RECOMP_HOOK("Interface_UpdateButtonsPart2") void on_Interface_UpdateButtonsPart2(PlayState* play) {
    sPlay = play;
}

RECOMP_HOOK_RETURN("Interface_UpdateButtonsPart2") void return_Interface_UpdateButtonsPart2() {
    if (!SceneAPI_IsCustomScene(sPlay)) {
        return;
    }

    MessageContext* msgCtx = &sPlay->msgCtx;
    InterfaceContext* interfaceCtx = &sPlay->interfaceCtx;
    Player* player = GET_PLAYER(sPlay);
    s16 i;

    // C buttons
    if (GET_PLAYER_FORM == player->transformation) {
        for (i = EQUIP_SLOT_C_LEFT; i <= EQUIP_SLOT_C_RIGHT; i++) {
            // Individual C button

            if (GET_CUR_FORM_BTN_ITEM(i) == ITEM_MASK_FIERCE_DEITY) {
                // Fierce Deity's Mask is equipped
                if (!sceneAPI_customScenes[sceneAPI_customSceneId].permissions.allowFierceDeity) {
                    if (gSaveContext.buttonStatus[i] != BTN_DISABLED) {
                        gSaveContext.buttonStatus[i] = BTN_DISABLED;
                    }
                } else if (gSaveContext.buttonStatus[i] == BTN_DISABLED) {
                    gSaveContext.buttonStatus[i] = BTN_ENABLED;
                }
            }
        }
    }
}