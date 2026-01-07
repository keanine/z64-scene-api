#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "scenes/ddan/ddan_scene.h"

#include "scene_api_header.h"

static char* sceneName = "Dodongo's Cavern";
static const SceneCmd* sceneHeader = SCENE_HEADER(ddan);
static const SceneCmd* sceneRooms[] = {
    ROOM_HEADER(ddan, 0),
    ROOM_HEADER(ddan, 1),
};

THIRTY_DUMMY_SEGMENTS(ddan)

RECOMP_CALLBACK("z64_scene_api", SceneAPI_Init)
void Scene_DDAN_Init() {
    SceneAPI_RegisterScene(sceneName, sceneHeader, sceneRooms, SCENEAPI_DEFAULT_PROPERTIES);
}

RECOMP_CALLBACK("z64_scene_api", SceneAPI_PostInit)
void Scene_DDAN_PostInit() {
    SceneAPI_RegisterWarpGrotto(SCENE_BACKTOWN, SCENEAPI_MODDED_EXIT(sceneName), -584,    200,  -1780);
    SceneAPI_RegisterWarpGrotto(SCENE_BACKTOWN, SCENEAPI_VANILLA_EXIT(ENTRANCE(CLOCK_TOWER_INTERIOR, 1)), -524,    200,  -1780);

    SceneAPI_RegisterExitOverride(SCENE_CLOCKTOWER, 0xC010, SCENEAPI_MODDED_EXIT(sceneName));
}