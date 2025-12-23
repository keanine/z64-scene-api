#include "scene_api.h"
#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "scenes/mm_test/mm_test_scene.h"

#define SPIDER_SCENE_NAME "MinecraftSpiderHouse"
#define SPIDER_SCENE_HEADER mm_test_scene_header00
// #define SPIDER_SCENE_ROOMS (SceneCmd*[]){ mm_test_room_0_header00 }
SceneCmd* SPIDER_SCENE_ROOMS[] = {
    mm_test_room_0_header00
};

// Dummy symbols to let the rooms compile
u8 _mm_test_room_0SegmentRomStart[1];
u8 _mm_test_room_0SegmentRomEnd[1];

RECOMP_CALLBACK("z64_scene_api", SceneAPI_Init)
void Scene_Spider_Init() {
    // SceneAPI_AddExitOverride(SCENE_CLOCKTOWER, 0xC010, 0);
    // SceneAPI_SetSceneAtIndex(0x1, SPIDER_SCENE_NAME, SPIDER_SCENE_HEADER, SPIDER_SCENE_ROOMS, (u16[]){  });
    SceneAPI_AddScene(SPIDER_SCENE_NAME, SPIDER_SCENE_HEADER, SPIDER_SCENE_ROOMS, (SceneAPI_Exit[]){  });
}