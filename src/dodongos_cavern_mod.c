#include "scene_api.h"
#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "scenes/ddan/ddan_scene.h"

u16 DDAN_ID;
#define DDAN_SCENE_NAME "DDAN"
const SceneCmd* DDAN_SCENE_HEADER = ddan_scene_header00;
const SceneCmd* DDAN_SCENE_ROOMS[] = {
    ddan_room_0_header00,
    ddan_room_1_header00
};

const SceneAPI_Exit DDAN_EXIT_IDS[] = {
    // SCENEAPI_EXIT(EXITTYPE_MODDED, 0, MMTEST2_SCENE_NAME), // Go to the scene with custom ID 0
    // SCENEAPI_EXIT(EXITTYPE_VANILLA, 0xC010, "") // Go to the vanilla entrance 0xC010
};

// Dummy symbols to let the rooms compile
u8 _ddan_room_0SegmentRomStart[1];
u8 _ddan_room_0SegmentRomEnd[1];
u8 _ddan_room_1SegmentRomStart[1];
u8 _ddan_room_1SegmentRomEnd[1];

RECOMP_CALLBACK("z64_scene_api", SceneAPI_Init)
void Scene_DDAN_Init() {
    DDAN_ID = SceneAPI_AddScene(DDAN_SCENE_NAME, DDAN_SCENE_HEADER, DDAN_SCENE_ROOMS, DDAN_EXIT_IDS);
}

RECOMP_CALLBACK("z64_scene_api", SceneAPI_PostInit)
void Scene_DDAN_PostInit() {
    SceneAPI_AddGrotto(SCENE_BACKTOWN, SCENEAPI_EXIT(SCENEAPI_EXITTYPE_MODDED, 0, DDAN_SCENE_NAME), -584,    200,  -1780);
    SceneAPI_AddGrotto(SCENE_CLOCKTOWER, SCENEAPI_EXIT(SCENEAPI_EXITTYPE_MODDED, 0, DDAN_SCENE_NAME), -540,    100,  -1099);
}