#include "mm_test2_scene.h"

/**
 * Header Default
*/
SceneCmd mm_test2_scene_header00[] = {
    SCENE_CMD_COL_HEADER(&mm_test2_scene_collisionHeader),
    SCENE_CMD_ROOM_LIST(2, mm_test2_scene_roomList),
    SCENE_CMD_SOUND_SETTINGS(0x00, 0x00, NA_BGM_GENERAL_SFX),
    SCENE_CMD_SPECIAL_FILES(NAVI_QUEST_HINTS_NONE, GAMEPLAY_FIELD_KEEP),
    SCENE_CMD_SKYBOX_SETTINGS(0x00, SKYBOX_NONE, SKYBOX_CONFIG_0, 0x00),
    SCENE_CMD_ENV_LIGHT_SETTINGS(1, mm_test2_scene_header00_lightSettings),
    SCENE_CMD_TRANSITION_ACTOR_LIST(1, mm_test2_scene_header00_transitionActors),
    SCENE_CMD_ENTRANCE_LIST(mm_test2_scene_header00_entranceList),
    SCENE_CMD_SPAWN_LIST(7, mm_test2_scene_header00_playerEntryList),
    SCENE_CMD_ANIMATED_MATERIAL_LIST(mm_test2_scene_header00_AnimatedMaterial),
    SCENE_CMD_ACTOR_CUTSCENE_LIST(13, mm_test2_scene_header00_ActorCutsceneList),
    SCENE_CMD_ACTOR_CUTSCENE_CAM_LIST(2, mm_test2_scene_header00_ActorCutsceneCameraInfo),
    SCENE_CMD_EXIT_LIST(mm_test2_scene_header00_exitList),
    SCENE_CMD_END(),
};

RomFile mm_test2_scene_roomList[] = {
    { (uintptr_t)_mm_test2_room_0SegmentRomStart, (uintptr_t)_mm_test2_room_0SegmentRomEnd },
    { (uintptr_t)_mm_test2_room_1SegmentRomStart, (uintptr_t)_mm_test2_room_1SegmentRomEnd },
};

ActorEntry mm_test2_scene_header00_playerEntryList[] = {
    // Player
    {
        /* Actor ID   */ ACTOR_PLAYER,
        /* Position   */ { -878, -94, -124 },
        /* Rotation   */ { SPAWN_ROT_FLAGS(0, 0x00), SPAWN_ROT_FLAGS(90, 0x00), SPAWN_ROT_FLAGS(0, 0x00) },
        /* Parameters */ 0x0FFF
    },
    // Player
    {
        /* Actor ID   */ ACTOR_PLAYER,
        /* Position   */ { 300, 0, -251 },
        /* Rotation   */ { SPAWN_ROT_FLAGS(0, 0x00), SPAWN_ROT_FLAGS(0, 0x00), SPAWN_ROT_FLAGS(0, 0x00) },
        /* Parameters */ 0x0FFF
    },
    // Player
    {
        /* Actor ID   */ ACTOR_PLAYER,
        /* Position   */ { -300, 0, -251 },
        /* Rotation   */ { SPAWN_ROT_FLAGS(0, 0x00), SPAWN_ROT_FLAGS(0, 0x00), SPAWN_ROT_FLAGS(0, 0x00) },
        /* Parameters */ 0x0FFF
    },
    // Player
    {
        /* Actor ID   */ ACTOR_PLAYER,
        /* Position   */ { 426, 0, 178 },
        /* Rotation   */ { SPAWN_ROT_FLAGS(0, 0x00), SPAWN_ROT_FLAGS(270, 0x00), SPAWN_ROT_FLAGS(0, 0x00) },
        /* Parameters */ 0x0FFF
    },
    // Player
    {
        /* Actor ID   */ ACTOR_PLAYER,
        /* Position   */ { -427, 0, 178 },
        /* Rotation   */ { SPAWN_ROT_FLAGS(0, 0x00), SPAWN_ROT_FLAGS(90, 0x00), SPAWN_ROT_FLAGS(0, 0x00) },
        /* Parameters */ 0x0FFF
    },
    // Player
    {
        /* Actor ID   */ ACTOR_PLAYER,
        /* Position   */ { -427, 0, 456 },
        /* Rotation   */ { SPAWN_ROT_FLAGS(0, 0x00), SPAWN_ROT_FLAGS(90, 0x00), SPAWN_ROT_FLAGS(0, 0x00) },
        /* Parameters */ 0x0FFF
    },
    // Player
    {
        /* Actor ID   */ ACTOR_PLAYER,
        /* Position   */ { 0, 0, 602 },
        /* Rotation   */ { SPAWN_ROT_FLAGS(0, 0x00), SPAWN_ROT_FLAGS(180, 0x00), SPAWN_ROT_FLAGS(0, 0x00) },
        /* Parameters */ 0x0FFF
    },
};

EntranceEntry mm_test2_scene_header00_entranceList[] = {
    // { Spawn Actor List Index, Room Index }
    { 0, 0 },
    { 1, 0 },
    { 2, 0 },
    { 3, 0 },
    { 4, 0 },
    { 5, 0 },
    { 6, 0 },
};

// SceneAPI_Exit mm_test2_scene_header00_exitList[] = {
//     { "Custom", 0xC010, 0x72 },
//     { "Custom", 0xC010, 0x71 },
// };

u16 mm_test2_scene_header00_exitList[] = {
    0,
    0,
};

TransitionActorEntry mm_test2_scene_header00_transitionActors[] = {
    // Dungeon Door
    {
        /* Room & Cam Index (Front, Back) */ { 0, 0xFF, 1, 0xFF },
        /* Actor ID                       */ ACTOR_DOOR_SHUTTER,
        /* Position                       */ { 520, -326, 0 },
        /* Rotation Y                     */ ((0x005A & 0x1FF) << 7) | (127 & 0x7F),
        /* Parameters                     */ 0x0000
    },
};

EnvLightSettings mm_test2_scene_header00_lightSettings[1] = {
    // Custom No. 1 Lighting
    {
        {   143,    65,    37 },   // Ambient Color
        {    73,   -73,    73 },   // Diffuse0 Direction
        {   219,   204,   194 },   // Diffuse0 Color
        {   -73,    73,   -73 },   // Diffuse1 Direction
        {   133,   113,    22 },   // Diffuse1 Color
        {   196,   182,   175 },   // Fog Color
        ((1 << 10) | 993),         // Blend Rate & Fog Near
        12800,                     // Fog Far
    },
};

AnimatedMatTexScrollParams mm_test2_scene_header00_AnimatedMaterialTexScrollParams_00[] = {
    { 0, -1, 32, 32 },
    { 0, -1, 32, 32 }
};

AnimatedMatTexScrollParams mm_test2_scene_header00_AnimatedMaterialTexScrollParams_01[] = {
    { 0, 1, 32, 32 },
    { 0, -1, 32, 32 }
};

F3DPrimColor mm_test2_scene_header00_AnimatedMaterialColorPrimColor_02[] = {
    { 255, 255, 255, 255, 128 },
    { 255, 255, 255, 255, 128 },
    { 128, 0, 0, 255, 128 },
    { 255, 255, 255, 255, 128 },
    { 255, 255, 255, 255, 128 }
};

F3DEnvColor mm_test2_scene_header00_AnimatedMaterialColorEnvColor_02[] = {
    { 255, 255, 255, 255 },
    { 255, 255, 255, 255 },
    { 255, 255, 255, 255 },
    { 255, 255, 255, 255 },
    { 255, 255, 255, 255 }
};

u16 mm_test2_scene_header00_AnimatedMaterialColorKeyFrames_02[] = {
    0,
    5,
    30,
    55,
    59
};

AnimatedMatColorParams mm_test2_scene_header00_AnimatedMaterialColorParams_02 = {
    60,
    5,
    mm_test2_scene_header00_AnimatedMaterialColorPrimColor_02,
    mm_test2_scene_header00_AnimatedMaterialColorEnvColor_02,
    mm_test2_scene_header00_AnimatedMaterialColorKeyFrames_02,
};

AnimatedMaterial mm_test2_scene_header00_AnimatedMaterial[] = {
    { 1 /* 8 */, 1, mm_test2_scene_header00_AnimatedMaterialTexScrollParams_00 },
    { 2 /* 9 */, 1, mm_test2_scene_header00_AnimatedMaterialTexScrollParams_01 },
    { -3 /* 10 */, 4, &mm_test2_scene_header00_AnimatedMaterialColorParams_02 }
};

Vec3s mm_test2_scene_header00_ActorCutsceneCameraData[] = {
    {    608,    279,   -730 },
    { 0x0C3B, 0xE10A, 0x0000 },
    {   4000,     -1,     -1 },

    {   -506,    279,   -730 },
    { 0x0C3B, 0x2067, 0x0000 },
    {     -1,     -1,     -1 },
};

ActorCsCamInfo mm_test2_scene_header00_ActorCutsceneCameraInfo[] = {
    { CAM_SET_NORMAL0, 3, &mm_test2_scene_header00_ActorCutsceneCameraData[0] },
    { CAM_SET_NORMAL0, 3, &mm_test2_scene_header00_ActorCutsceneCameraData[3] },
};

CutsceneEntry mm_test2_scene_header00_ActorCutsceneList[] = {
    /* 00 */ { 550, -1, CS_CAM_ID_GLOBAL_ITEM_OCARINA, -1, 1, CS_END_SFX_NONE, 255, CS_HUD_VISIBILITY_NONE, CS_END_CAM_0, 30 },
    /* 01 */ { 600, -1, CS_CAM_ID_GLOBAL_ITEM_GET, -1, 2, CS_END_SFX_NONE, 255, CS_HUD_VISIBILITY_NONE, CS_END_CAM_0, 30 },
    /* 02 */ { 700, -1, CS_CAM_ID_GLOBAL_ITEM_BOTTLE, -1, 3, CS_END_SFX_NONE, 255, CS_HUD_VISIBILITY_NONE, CS_END_CAM_0, 30 },
    /* 03 */ { 700, -1, CS_CAM_ID_GLOBAL_ITEM_SHOW, -1, 4, CS_END_SFX_NONE, 255, CS_HUD_VISIBILITY_NONE, CS_END_CAM_0, 30 },
    /* 04 */ { 500, -1, CS_CAM_ID_GLOBAL_WARP_PAD_MOON, -1, 5, CS_END_SFX_NONE, 255, CS_HUD_VISIBILITY_NONE, CS_END_CAM_0, 30 },
    /* 05 */ { 400, -1, CS_CAM_ID_GLOBAL_MASK_TRANSFORMATION, -1, 6, CS_END_SFX_NONE, 255, CS_HUD_VISIBILITY_NONE, CS_END_CAM_0, 30 },
    /* 06 */ { 100, -1, CS_CAM_ID_GLOBAL_DEATH, -1, 7, CS_END_SFX_NONE, 255, CS_HUD_VISIBILITY_NONE, CS_END_CAM_0, 30 },
    /* 07 */ { 200, -1, CS_CAM_ID_GLOBAL_REVIVE, -1, 8, CS_END_SFX_NONE, 255, CS_HUD_VISIBILITY_NONE, CS_END_CAM_0, 30 },
    /* 08 */ { 700, -1, CS_CAM_ID_GLOBAL_SONG_WARP, -1, 9, CS_END_SFX_NONE, 255, CS_HUD_VISIBILITY_NONE, CS_END_CAM_0, 30 },
    /* 09 */ { 700, -1, CS_CAM_ID_GLOBAL_WARP_PAD_ENTRANCE, -1, 10, CS_END_SFX_NONE, 255, CS_HUD_VISIBILITY_NONE, CS_END_CAM_0, 30 },
    /* 10 */ { 700, 135, CS_CAM_ID_GLOBAL_LONG_CHEST_OPENING, -1, -1, CS_END_SFX_NONE, 1, CS_HUD_VISIBILITY_NONE, CS_END_CAM_0, 30 },
    /* 11 */ { 700, -1, 0, -1, 12, CS_END_SFX_NONE, 255, CS_HUD_VISIBILITY_NONE, CS_END_CAM_0, 30 },
    /* 12 */ { 700, -1, 1, -1, -1, CS_END_SFX_NONE, 255, CS_HUD_VISIBILITY_NONE, CS_END_CAM_0, 30 }
};

BgCamInfo mm_test2_scene_bgCamInfo[] = {
    { CAM_SET_NORMAL0, 0, NULL },
};

SurfaceType mm_test2_scene_polygonTypes[3] = {
    {
        (((0 & 1) << 31) | ((0 & 1) << 30) | ((0x00 & 0x0F) << 26) | ((0x00 & 0x1F) << 21) | ((0 & 0x07) << 18) | ((0x00 & 0x1F) << 13) | ((0 & 0x1F) << 8) | (0 & 0xFF)),
        (((0 & 1) << 27) | ((0 & 0x3F) << 21) | ((0 & 0x07) << 18) | ((0 & 1) << 17) | ((0 & 0x3F) << 11) | ((0 & 0x1F) << 6) | ((0x00 & 0x03) << 4) | (SURFACE_MATERIAL_DIRT & 0x0F))
    },
    {
        (((0 & 1) << 31) | ((0 & 1) << 30) | ((0x00 & 0x0F) << 26) | ((0x00 & 0x1F) << 21) | ((0 & 0x07) << 18) | ((0x00 & 0x1F) << 13) | ((1 & 0x1F) << 8) | (0 & 0xFF)),
        (((0 & 1) << 27) | ((0 & 0x3F) << 21) | ((0 & 0x07) << 18) | ((0 & 1) << 17) | ((0 & 0x3F) << 11) | ((0 & 0x1F) << 6) | ((0x00 & 0x03) << 4) | (SURFACE_MATERIAL_DIRT & 0x0F))
    },
    {
        (((0 & 1) << 31) | ((0 & 1) << 30) | ((0x00 & 0x0F) << 26) | ((0x00 & 0x1F) << 21) | ((0 & 0x07) << 18) | ((0x00 & 0x1F) << 13) | ((2 & 0x1F) << 8) | (0 & 0xFF)),
        (((0 & 1) << 27) | ((0 & 0x3F) << 21) | ((0 & 0x07) << 18) | ((0 & 1) << 17) | ((0 & 0x3F) << 11) | ((0 & 0x1F) << 6) | ((0x00 & 0x03) << 4) | (SURFACE_MATERIAL_DIRT & 0x0F))
    },
};

Vec3s mm_test2_scene_vertices[40] = {
    {   -149,   -290,    216 },
    {   -149,   -205,    216 },
    {   -149,   -205,    130 },
    {   -149,   -290,    130 },
    {    -63,   -205,    130 },
    {    -63,   -290,    130 },
    {    -63,   -205,    216 },
    {    -63,   -290,    216 },
    {    540,   -376,     60 },
    {    540,   -176,     60 },
    {    500,   -176,     60 },
    {    500,   -376,     60 },
    {    500,   -176,    -60 },
    {    500,   -376,    -60 },
    {    540,   -176,    -60 },
    {    540,   -376,    -60 },
    {   -532,   -325,    429 },
    {    532,   -325,    429 },
    {    532,   -325,   -636 },
    {   -532,   -325,   -636 },
    {    924,   -301,    -87 },
    {    924,   -301,    103 },
    {    952,   -489,    103 },
    {    952,   -489,    -87 },
    {    736,   -329,    103 },
    {    764,   -517,    103 },
    {    736,   -329,    -87 },
    {    764,   -517,    -87 },
    {    924,   -301,    138 },
    {    924,   -301,    328 },
    {    952,   -489,    328 },
    {    952,   -489,    138 },
    {    736,   -329,    328 },
    {    764,   -517,    328 },
    {    736,   -329,    138 },
    {    764,   -517,    138 },
    {    508,   -325,    391 },
    {   1502,   -325,    391 },
    {   1502,   -325,   -603 },
    {    508,   -325,   -603 },
};

CollisionPoly mm_test2_scene_polygons[52] = {
    { 0, (((0 & 7) << 13) | (0 & 0x1FFF)), (((0 & 7) << 13) | (1 & 0x1FFF)), 2 & 0x1FFF, { COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 65387 },
    { 0, (((0 & 7) << 13) | (0 & 0x1FFF)), (((0 & 7) << 13) | (2 & 0x1FFF)), 3 & 0x1FFF, { COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 65387 },
    { 0, (((0 & 7) << 13) | (3 & 0x1FFF)), (((0 & 7) << 13) | (2 & 0x1FFF)), 4 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(7.549790126404332e-08), COLPOLY_SNORMAL(-1.0) }, 130 },
    { 0, (((0 & 7) << 13) | (3 & 0x1FFF)), (((0 & 7) << 13) | (4 & 0x1FFF)), 5 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(7.549790126404332e-08), COLPOLY_SNORMAL(-1.0) }, 130 },
    { 0, (((0 & 7) << 13) | (5 & 0x1FFF)), (((0 & 7) << 13) | (4 & 0x1FFF)), 6 & 0x1FFF, { COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 63 },
    { 0, (((0 & 7) << 13) | (5 & 0x1FFF)), (((0 & 7) << 13) | (6 & 0x1FFF)), 7 & 0x1FFF, { COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 63 },
    { 0, (((0 & 7) << 13) | (7 & 0x1FFF)), (((0 & 7) << 13) | (6 & 0x1FFF)), 1 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-7.549790126404332e-08), COLPOLY_SNORMAL(1.0) }, 65320 },
    { 0, (((0 & 7) << 13) | (7 & 0x1FFF)), (((0 & 7) << 13) | (1 & 0x1FFF)), 0 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-7.549790126404332e-08), COLPOLY_SNORMAL(1.0) }, 65320 },
    { 0, (((0 & 7) << 13) | (3 & 0x1FFF)), (((0 & 7) << 13) | (5 & 0x1FFF)), 7 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(-7.549790126404332e-08) }, 65246 },
    { 0, (((0 & 7) << 13) | (3 & 0x1FFF)), (((0 & 7) << 13) | (7 & 0x1FFF)), 0 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(-7.549790126404332e-08) }, 65246 },
    { 0, (((0 & 7) << 13) | (4 & 0x1FFF)), (((0 & 7) << 13) | (2 & 0x1FFF)), 1 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(7.549790126404332e-08) }, 205 },
    { 0, (((0 & 7) << 13) | (4 & 0x1FFF)), (((0 & 7) << 13) | (1 & 0x1FFF)), 6 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(7.549790126404332e-08) }, 205 },
    { 0, (((0 & 7) << 13) | (8 & 0x1FFF)), (((0 & 7) << 13) | (9 & 0x1FFF)), 10 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-7.549790126404332e-08), COLPOLY_SNORMAL(1.0) }, 65476 },
    { 0, (((0 & 7) << 13) | (8 & 0x1FFF)), (((0 & 7) << 13) | (10 & 0x1FFF)), 11 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-7.549790126404332e-08), COLPOLY_SNORMAL(1.0) }, 65476 },
    { 0, (((0 & 7) << 13) | (11 & 0x1FFF)), (((0 & 7) << 13) | (10 & 0x1FFF)), 12 & 0x1FFF, { COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 500 },
    { 0, (((0 & 7) << 13) | (11 & 0x1FFF)), (((0 & 7) << 13) | (12 & 0x1FFF)), 13 & 0x1FFF, { COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 500 },
    { 0, (((0 & 7) << 13) | (13 & 0x1FFF)), (((0 & 7) << 13) | (12 & 0x1FFF)), 14 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(7.549790126404332e-08), COLPOLY_SNORMAL(-1.0) }, 65476 },
    { 0, (((0 & 7) << 13) | (13 & 0x1FFF)), (((0 & 7) << 13) | (14 & 0x1FFF)), 15 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(7.549790126404332e-08), COLPOLY_SNORMAL(-1.0) }, 65476 },
    { 0, (((0 & 7) << 13) | (15 & 0x1FFF)), (((0 & 7) << 13) | (14 & 0x1FFF)), 9 & 0x1FFF, { COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 64996 },
    { 0, (((0 & 7) << 13) | (15 & 0x1FFF)), (((0 & 7) << 13) | (9 & 0x1FFF)), 8 & 0x1FFF, { COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 64996 },
    { 0, (((0 & 7) << 13) | (11 & 0x1FFF)), (((0 & 7) << 13) | (13 & 0x1FFF)), 15 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(-7.549790126404332e-08) }, 65160 },
    { 0, (((0 & 7) << 13) | (11 & 0x1FFF)), (((0 & 7) << 13) | (15 & 0x1FFF)), 8 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(-7.549790126404332e-08) }, 65160 },
    { 0, (((0 & 7) << 13) | (12 & 0x1FFF)), (((0 & 7) << 13) | (10 & 0x1FFF)), 9 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(7.549790126404332e-08) }, 176 },
    { 0, (((0 & 7) << 13) | (12 & 0x1FFF)), (((0 & 7) << 13) | (9 & 0x1FFF)), 14 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(7.549790126404332e-08) }, 176 },
    { 0, (((0 & 7) << 13) | (16 & 0x1FFF)), (((0 & 7) << 13) | (17 & 0x1FFF)), 18 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(7.549790126404332e-08) }, 325 },
    { 0, (((0 & 7) << 13) | (16 & 0x1FFF)), (((0 & 7) << 13) | (18 & 0x1FFF)), 19 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(7.549790126404332e-08) }, 325 },
    { 0, (((0 & 7) << 13) | (36 & 0x1FFF)), (((0 & 7) << 13) | (37 & 0x1FFF)), 38 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(7.549790126404332e-08) }, 325 },
    { 0, (((0 & 7) << 13) | (36 & 0x1FFF)), (((0 & 7) << 13) | (38 & 0x1FFF)), 39 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(7.549790126404332e-08) }, 325 },
    { 1, (((0 & 7) << 13) | (22 & 0x1FFF)), (((0 & 7) << 13) | (20 & 0x1FFF)), 21 & 0x1FFF, { COLPOLY_SNORMAL(0.9891147613525391), COLPOLY_SNORMAL(0.14714592695236206), COLPOLY_SNORMAL(1.1109209552273569e-08) }, 64667 },
    { 1, (((0 & 7) << 13) | (22 & 0x1FFF)), (((0 & 7) << 13) | (23 & 0x1FFF)), 20 & 0x1FFF, { COLPOLY_SNORMAL(0.9891147613525391), COLPOLY_SNORMAL(0.14714592695236206), COLPOLY_SNORMAL(1.1109209552273569e-08) }, 64667 },
    { 1, (((0 & 7) << 13) | (25 & 0x1FFF)), (((0 & 7) << 13) | (21 & 0x1FFF)), 24 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-7.549790126404332e-08), COLPOLY_SNORMAL(1.0) }, 65433 },
    { 1, (((0 & 7) << 13) | (25 & 0x1FFF)), (((0 & 7) << 13) | (22 & 0x1FFF)), 21 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-7.549790126404332e-08), COLPOLY_SNORMAL(1.0) }, 65433 },
    { 1, (((0 & 7) << 13) | (27 & 0x1FFF)), (((0 & 7) << 13) | (24 & 0x1FFF)), 26 & 0x1FFF, { COLPOLY_SNORMAL(-0.9891147613525391), COLPOLY_SNORMAL(-0.14714592695236206), COLPOLY_SNORMAL(-1.1109209552273569e-08) }, 679 },
    { 1, (((0 & 7) << 13) | (27 & 0x1FFF)), (((0 & 7) << 13) | (25 & 0x1FFF)), 24 & 0x1FFF, { COLPOLY_SNORMAL(-0.9891147613525391), COLPOLY_SNORMAL(-0.14714592695236206), COLPOLY_SNORMAL(-1.1109209552273569e-08) }, 679 },
    { 1, (((0 & 7) << 13) | (23 & 0x1FFF)), (((0 & 7) << 13) | (26 & 0x1FFF)), 20 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(7.549790126404332e-08), COLPOLY_SNORMAL(-1.0) }, 65449 },
    { 1, (((0 & 7) << 13) | (27 & 0x1FFF)), (((0 & 7) << 13) | (26 & 0x1FFF)), 23 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(7.549790126404332e-08), COLPOLY_SNORMAL(-1.0) }, 65449 },
    { 1, (((0 & 7) << 13) | (26 & 0x1FFF)), (((0 & 7) << 13) | (21 & 0x1FFF)), 20 & 0x1FFF, { COLPOLY_SNORMAL(-0.14714591205120087), COLPOLY_SNORMAL(0.9891147613525391), COLPOLY_SNORMAL(7.467608753586319e-08) }, 434 },
    { 1, (((0 & 7) << 13) | (26 & 0x1FFF)), (((0 & 7) << 13) | (24 & 0x1FFF)), 21 & 0x1FFF, { COLPOLY_SNORMAL(-0.14714591205120087), COLPOLY_SNORMAL(0.9891147613525391), COLPOLY_SNORMAL(7.467608753586319e-08) }, 434 },
    { 1, (((0 & 7) << 13) | (25 & 0x1FFF)), (((0 & 7) << 13) | (27 & 0x1FFF)), 23 & 0x1FFF, { COLPOLY_SNORMAL(0.14714591205120087), COLPOLY_SNORMAL(-0.9891147613525391), COLPOLY_SNORMAL(-7.467608753586319e-08) }, 64912 },
    { 1, (((0 & 7) << 13) | (25 & 0x1FFF)), (((0 & 7) << 13) | (23 & 0x1FFF)), 22 & 0x1FFF, { COLPOLY_SNORMAL(0.14714591205120087), COLPOLY_SNORMAL(-0.9891147613525391), COLPOLY_SNORMAL(-7.467608753586319e-08) }, 64912 },
    { 2, (((0 & 7) << 13) | (30 & 0x1FFF)), (((0 & 7) << 13) | (28 & 0x1FFF)), 29 & 0x1FFF, { COLPOLY_SNORMAL(0.9891147613525391), COLPOLY_SNORMAL(0.14714592695236206), COLPOLY_SNORMAL(1.1109209552273569e-08) }, 64667 },
    { 2, (((0 & 7) << 13) | (30 & 0x1FFF)), (((0 & 7) << 13) | (31 & 0x1FFF)), 28 & 0x1FFF, { COLPOLY_SNORMAL(0.9891147613525391), COLPOLY_SNORMAL(0.14714592695236206), COLPOLY_SNORMAL(1.1109209552273569e-08) }, 64667 },
    { 2, (((0 & 7) << 13) | (33 & 0x1FFF)), (((0 & 7) << 13) | (29 & 0x1FFF)), 32 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-7.549790126404332e-08), COLPOLY_SNORMAL(1.0) }, 65208 },
    { 2, (((0 & 7) << 13) | (33 & 0x1FFF)), (((0 & 7) << 13) | (30 & 0x1FFF)), 29 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-7.549790126404332e-08), COLPOLY_SNORMAL(1.0) }, 65208 },
    { 2, (((0 & 7) << 13) | (35 & 0x1FFF)), (((0 & 7) << 13) | (32 & 0x1FFF)), 34 & 0x1FFF, { COLPOLY_SNORMAL(-0.9891147613525391), COLPOLY_SNORMAL(-0.14714592695236206), COLPOLY_SNORMAL(-1.1109209552273569e-08) }, 679 },
    { 2, (((0 & 7) << 13) | (35 & 0x1FFF)), (((0 & 7) << 13) | (33 & 0x1FFF)), 32 & 0x1FFF, { COLPOLY_SNORMAL(-0.9891147613525391), COLPOLY_SNORMAL(-0.14714592695236206), COLPOLY_SNORMAL(-1.1109209552273569e-08) }, 679 },
    { 2, (((0 & 7) << 13) | (31 & 0x1FFF)), (((0 & 7) << 13) | (34 & 0x1FFF)), 28 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(7.549790126404332e-08), COLPOLY_SNORMAL(-1.0) }, 138 },
    { 2, (((0 & 7) << 13) | (35 & 0x1FFF)), (((0 & 7) << 13) | (34 & 0x1FFF)), 31 & 0x1FFF, { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(7.549790126404332e-08), COLPOLY_SNORMAL(-1.0) }, 138 },
    { 2, (((0 & 7) << 13) | (34 & 0x1FFF)), (((0 & 7) << 13) | (29 & 0x1FFF)), 28 & 0x1FFF, { COLPOLY_SNORMAL(-0.14714591205120087), COLPOLY_SNORMAL(0.9891148209571838), COLPOLY_SNORMAL(7.467609464129055e-08) }, 434 },
    { 2, (((0 & 7) << 13) | (34 & 0x1FFF)), (((0 & 7) << 13) | (32 & 0x1FFF)), 29 & 0x1FFF, { COLPOLY_SNORMAL(-0.14714591205120087), COLPOLY_SNORMAL(0.9891148209571838), COLPOLY_SNORMAL(7.467609464129055e-08) }, 434 },
    { 2, (((0 & 7) << 13) | (33 & 0x1FFF)), (((0 & 7) << 13) | (35 & 0x1FFF)), 31 & 0x1FFF, { COLPOLY_SNORMAL(0.14714591205120087), COLPOLY_SNORMAL(-0.9891148209571838), COLPOLY_SNORMAL(-7.467609464129055e-08) }, 64912 },
    { 2, (((0 & 7) << 13) | (33 & 0x1FFF)), (((0 & 7) << 13) | (31 & 0x1FFF)), 30 & 0x1FFF, { COLPOLY_SNORMAL(0.14714591205120087), COLPOLY_SNORMAL(-0.9891148209571838), COLPOLY_SNORMAL(-7.467609464129055e-08) }, 64912 },
};

CollisionHeader mm_test2_scene_collisionHeader = {
    { -532, -517, -636 },
    { 1502, -176, 429 },
    ARRAY_COUNT(mm_test2_scene_vertices), mm_test2_scene_vertices,
    ARRAY_COUNT(mm_test2_scene_polygons), mm_test2_scene_polygons,
    mm_test2_scene_polygonTypes,
    mm_test2_scene_bgCamInfo,
    0, NULL
};

u64 mm_test2_room_0_dl_bedrock_i8[] = {
	0x6333333333579763, 0x5797573333573357, 0x3363639763976397, 0x3397976322335733, 0x3322333322333333, 0x9733575757975763, 0x5797636357225797, 0x5757333333333357, 
	0x2233973333333357, 0x3333639797636333, 0x3357575733575733, 0x3322575733332233, 0x9797635763979763, 0x5763979763973322, 0x5757573357575733, 0x3322333357336357, 
	0x6397975733335757, 0x6397976397979797, 0x5733332233573357, 0x3363573333339763, 0x6363973363979733, 0x2233979797633333, 0x2257575733335763, 0x9797576363979722, 
	0x5733333363573333, 0x6397333333333357, 0x6397639757225733, 0x3333223357639797, 0x6363573333573333, 0x5763979757333357, 0x3322333322979763, 0x3357632233335763, 
	
};

Gfx mat_mm_test2_room_0_dl_bedrock_001_f3d_layerOpaque[] = {
	gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_LIGHTING | G_ZBUFFER),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_CK_NONE | G_AD_NOISE | G_TC_FILT | G_CD_MAGICSQ | G_PM_NPRIMITIVE | G_CYC_2CYCLE | G_TT_NONE | G_TD_CLAMP | G_TF_POINT | G_TP_PERSP | G_TL_TILE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_FOG_SHADE_A | G_ZS_PIXEL | G_RM_AA_ZB_OPA_SURF2 | G_AC_NONE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b_LOAD_BLOCK, 1, mm_test2_room_0_dl_bedrock_i8),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 127, 1024),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 2, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 60),
	gsSPEndDisplayList(),
};

Gfx mat_revert_mm_test2_room_0_dl_bedrock_001_f3d_layerOpaque[] = {
	gsDPPipeSync(),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_OPA_SURF2 | G_ZS_PIXEL | G_RM_AA_ZB_OPA_SURF | G_AC_NONE),
	gsSPEndDisplayList(),
};

