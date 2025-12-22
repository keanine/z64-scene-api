#include "scene_api.h"
#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "scenes/mm_test2/mm_test2_scene.h"

u16 MMTEST2_ID;
#define MMTEST2_SCENE_NAME "MM_TEST_2"
const SceneCmd* MMTEST2_SCENE_HEADER = mm_test2_scene_header00;
const SceneCmd* MMTEST2_SCENE_ROOMS[] = {
    mm_test2_room_0_header00,
    mm_test2_room_1_header00
};

const SceneAPI_Exit EXIT_IDS[] = {
    { EXITTYPE_MODDED, 0, MMTEST2_SCENE_NAME }, // Go to the scene with custom ID 0
    { EXITTYPE_VANILLA, 0xC010, "" } // Go to the vanilla entrance 0xC010
};

// Dummy symbols to let the rooms compile
u8 _mm_test2_room_0SegmentRomStart[1];
u8 _mm_test2_room_0SegmentRomEnd[1];
u8 _mm_test2_room_1SegmentRomStart[1];
u8 _mm_test2_room_1SegmentRomEnd[1];

RECOMP_CALLBACK("z64_scene_api", SceneAPI_Init)
void Scene_Test2_Init() {
    // SceneAPI_SetSceneAtIndex(0, MMTEST2_SCENE_NAME, MMTEST2_SCENE_HEADER, MMTEST2_SCENE_ROOMS, EXIT_IDS);
    MMTEST2_ID = SceneAPI_AddScene(MMTEST2_SCENE_NAME, MMTEST2_SCENE_HEADER, MMTEST2_SCENE_ROOMS, EXIT_IDS);
}

RECOMP_CALLBACK("z64_scene_api", SceneAPI_PostInit)
void Scene_Test2_PostInit() {
    SceneAPI_AddExitOverride(SCENE_CLOCKTOWER, 0xC010, (SceneAPI_Exit){ EXITTYPE_MODDED, 0, MMTEST2_SCENE_NAME });
}