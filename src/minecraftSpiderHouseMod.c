#include "scene_api.h"
#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "scenes/mm_test/mm_test_scene.h"

#define SPIDER_SCENE_NAME "Minecraft Spider House"
#define SPIDER_SCENE_HEADER mm_test_scene_header00
// #define SPIDER_SCENE_ROOMS (SceneCmd*[]){ mm_test_room_0_header00 }
SceneCmd* SPIDER_SCENE_ROOMS[] = {
    mm_test_room_0_header00
};

// Dummy symbols to let the rooms compile
u8 _mm_test_room_0SegmentRomStart[1];
u8 _mm_test_room_0SegmentRomEnd[1];

RECOMP_CALLBACK("*", recomp_on_init)
void init_minecraft_spiderhouse() {
    SceneAPI_SetSceneAtIndex(0x1, SPIDER_SCENE_NAME, SPIDER_SCENE_HEADER, SPIDER_SCENE_ROOMS, (u16[]){  });
    // SceneAPI_AddScene(SPIDER_SCENE_NAME, SPIDER_SCENE_HEADER, SPIDER_SCENE_ROOMS, (u16[]){  });
}
