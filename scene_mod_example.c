#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "scenes/ddan/ddan_scene.h"

#include "scene_api_header.h"

u16 DDAN_ID;
#define DDAN_SCENE_NAME "DDAN"
const SceneCmd* DDAN_SCENE_HEADER = ddan_scene_header00;
const SceneCmd* DDAN_SCENE_ROOMS[] = {
    ddan_room_0_header00,
    ddan_room_1_header00
};

// Dummy symbols to let the rooms compile
u8 _ddan_room_0SegmentRomStart[1];
u8 _ddan_room_0SegmentRomEnd[1];
u8 _ddan_room_1SegmentRomStart[1];
u8 _ddan_room_1SegmentRomEnd[1];

// Registers a custom scene, ddan_scene
RECOMP_CALLBACK("z64_scene_api", SceneAPI_Init)
void Scene_DDAN_Init() {
    DDAN_ID = SceneAPI_RegisterScene(DDAN_SCENE_NAME, DDAN_SCENE_HEADER, DDAN_SCENE_ROOMS);
}

// Registers a grotto in North Clock Town
RECOMP_CALLBACK("z64_scene_api", SceneAPI_PostInit)
void Scene_DDAN_PostInit() {
    SceneAPI_RegisterGrotto(SCENE_BACKTOWN, SCENEAPI_EXIT(SCENEAPI_EXITTYPE_MODDED, 0, DDAN_SCENE_NAME), -584,    200,  -1780);
}