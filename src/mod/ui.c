#include "scene_api.h"
#include "recompui.h"

#include <string.h>
#include "libc64/sprintf.h"

// #define DEBUG_UI_ENABLED

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

u32 printCount;

extern void setup_recompui();
extern void update_ui();

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

    update_ui();

    recompui_show_context(context);
}

void update_ui() {
    printCount++;
    recompui_open_context(context);

    if (lblChest) {
        recompui_destroy_element(root, lblCounter);
        recompui_destroy_element(root, lblChest);
        recompui_destroy_element(root, lblSwitch0);
        recompui_destroy_element(root, lblSwitch1);
        recompui_destroy_element(root, lblClearedRoom);
        recompui_destroy_element(root, lblCollectible);
        recompui_destroy_element(root, lblUnk_14);
        recompui_destroy_element(root, lblRooms);
    }

    RecompuiColor bg_color;
    bg_color.r = 0;
    bg_color.g = 0;
    bg_color.b = 0;
    bg_color.a = 255;
    
    char msg_printcount[50]; sprintf(msg_printcount, "printcount: %lu", printCount);
    char msg_chest[50]; sprintf(msg_chest, "chest: %lu", gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].chest);
    char msg_switch0[50]; sprintf(msg_switch0, "switch0: %lu", gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].switch0);
    char msg_switch1[50]; sprintf(msg_switch1, "switch1: %lu", gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].switch1);
    char msg_clearedRoom[50]; sprintf(msg_clearedRoom, "clearedRoom: %lu", gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].clearedRoom);
    char msg_collectible[50]; sprintf(msg_collectible, "collectible: %lu", gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].collectible);
    char msg_unk_14[50]; sprintf(msg_unk_14, "unk_14: %lu", gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].unk_14);
    char msg_rooms[50]; sprintf(msg_rooms, "rooms: %lu", gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].rooms);
    
    recompui_set_background_color(root, &bg_color);

    lblCounter = recompui_create_label(context, root, msg_printcount, LABELSTYLE_SMALL);
    lblChest = recompui_create_label(context, root, msg_chest, LABELSTYLE_SMALL);
    lblSwitch0 = recompui_create_label(context, root, msg_switch0, LABELSTYLE_SMALL);
    lblSwitch1 = recompui_create_label(context, root, msg_switch1, LABELSTYLE_SMALL);
    lblClearedRoom = recompui_create_label(context, root, msg_clearedRoom, LABELSTYLE_SMALL);
    lblCollectible = recompui_create_label(context, root, msg_collectible, LABELSTYLE_SMALL);
    lblUnk_14 = recompui_create_label(context, root, msg_unk_14, LABELSTYLE_SMALL);
    lblRooms = recompui_create_label(context, root, msg_rooms, LABELSTYLE_SMALL);

    recompui_close_context(context);
}



RECOMP_HOOK("Map_InitRoomData") void Map_InitRoomDataUI(PlayState* play, s16 room) {
    if (room >= 0) {
        if (play->sceneId == SCENEAPI_SCENE) {
            SET_ROOM_VISITED(Play_GetOriginalSceneId(play->sceneId), room);
            update_ui();
        }
    }
}

RECOMP_HOOK("Play_InitScene") void InitSceneUI(PlayState* play, s32 spawn) {
    update_ui();
}

u32 printDelay = 500;
RECOMP_HOOK("Player_UpdateCommon") void on_Player_UpdateCommonUI(Player* this, PlayState* play, Input* input) {
    if (printDelay >= 500) {
        printDelay = 0;
        update_ui();
    }
    printDelay++;
}
#endif