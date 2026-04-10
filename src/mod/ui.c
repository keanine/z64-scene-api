#include "scene_api.h"
#include "recompui.h"

#include <string.h>
#include "libc64/sprintf.h"

#define DEBUG_UI_ENABLED

#if defined DEBUG_UI_ENABLED
char *strcat(char *dest, const char *src);

RecompuiContext context;
RecompuiTextTransform textbox;
RecompuiResource root;
bool is_context_shown;
bool conflict_found;

RecompuiResource lblCounter;
RecompuiResource lblChest;
RecompuiResource lblSwitch0;
RecompuiResource lblSwitch1;
RecompuiResource lblClearedRoom;
RecompuiResource lblCollectible;
RecompuiResource lblUnk_14;
RecompuiResource lblRooms;

RecompuiResource lblCChest;
RecompuiResource lblCSwitch0;
RecompuiResource lblCSwitch1;
RecompuiResource lblCClearedRoom;
RecompuiResource lblCCollectible;

u32 printCount;

extern void setup_recompui();
extern void update_ui(PlayState* play);

RECOMP_CALLBACK("*", recomp_on_init)
void SceneAPI_RecompInitUI() {
    setup_recompui();
}

void setup_recompui() {
    context = recompui_create_context();
    recompui_open_context(context);
    recompui_set_context_captures_input(context, false);
    recompui_set_context_captures_mouse(context, false);

    root = recompui_context_root(context);

    recompui_set_width_auto(root);
    recompui_set_height_auto(root);
    recompui_set_display(root, DISPLAY_FLEX);
    recompui_set_flex_direction(root, FLEX_DIRECTION_COLUMN);
    
    recompui_set_padding(root, 5, UNIT_DP);
    recompui_set_column_gap(root, 5, UNIT_DP);
    recompui_set_row_gap(root, 5, UNIT_DP);

    recompui_close_context(context);

    recompui_show_context(context);
}

void update_ui(PlayState* play) {
    printCount++;
    recompui_open_context(context);

    if (lblChest) {
        recompui_destroy_element(root, lblCounter);
        
        recompui_destroy_element(root, lblChest);
        recompui_destroy_element(root, lblSwitch0);
        recompui_destroy_element(root, lblSwitch1);
        recompui_destroy_element(root, lblClearedRoom);
        recompui_destroy_element(root, lblCollectible);
    }

    RecompuiColor bg_color;
    bg_color.r = 0;
    bg_color.g = 0;
    bg_color.b = 0;
    bg_color.a = 255;
    
    char msg_printcount[50]; sprintf(msg_printcount, "UI refresh counter: %lu", printCount);
    
    char msg_chest[50]; sprintf(msg_chest, "actorCtx chest: %lu", play->actorCtx.sceneFlags.chest);
    char msg_switch0[50]; sprintf(msg_switch0, "actorCtx switch0: %lu", play->actorCtx.sceneFlags.switches[0]);
    char msg_switch1[50]; sprintf(msg_switch1, "actorCtx switch1: %lu", play->actorCtx.sceneFlags.switches[1]);
    char msg_clearedRoom[50]; sprintf(msg_clearedRoom, "actorCtx clearedRoom: %lu", play->actorCtx.sceneFlags.clearedRoom);
    char msg_collectible[50]; sprintf(msg_collectible, "actorCtx collectible: %lu", play->actorCtx.sceneFlags.collectible[0]);
    
    recompui_set_background_color(root, &bg_color);

    lblCounter = recompui_create_label(context, root, msg_printcount, LABELSTYLE_SMALL);
    
    lblChest = recompui_create_label(context, root, msg_chest, LABELSTYLE_SMALL);
    lblSwitch0 = recompui_create_label(context, root, msg_switch0, LABELSTYLE_SMALL);
    lblSwitch1 = recompui_create_label(context, root, msg_switch1, LABELSTYLE_SMALL);
    lblClearedRoom = recompui_create_label(context, root, msg_clearedRoom, LABELSTYLE_SMALL);
    lblCollectible = recompui_create_label(context, root, msg_collectible, LABELSTYLE_SMALL);

    recompui_close_context(context);
}

extern void ClearCustomSceneFlags(PlayState* play);

// Update the UI every so often. RecompUI can crash when updating so doesn't print every frame.
u32 printDelay = 50;
RECOMP_HOOK("Player_UpdateCommon") void on_Player_UpdateCommonUI(Player* this, PlayState* play, Input* input) {
    if (printDelay >= 50) {
        printDelay = 0;
        update_ui(play);
    }
    printDelay++;

    if (CHECK_BTN_ANY(input->press.button, BTN_L)) {
        if (sceneAPI_customSceneId != SCENEAPI_VANILLA_ID) {
            recomp_printf("Flags cleared in custom scene (%s).\n", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);
            ClearCustomSceneFlags(play);
        }
    }
}
#endif