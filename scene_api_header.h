#ifndef SCENE_API_HEADER_H
#define SCENE_API_HEADER_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"

typedef struct SceneAPI_Exit {
    u8 exitType;
    u16 id;
    char* sceneName;
} SceneAPI_Exit;

#define SCENEAPI_MODDED_EXIT(sceneName) (SceneAPI_Exit){ 1, 0, sceneName }
#define SCENEAPI_VANILLA_EXIT(entranceId) (SceneAPI_Exit){ 0, entranceId, "" }

RECOMP_IMPORT("z64_scene_api", u16 SceneAPI_RegisterScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[]));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_RegisterExitOverride(SceneId originalScene, u16 originalEntranceId, SceneAPI_Exit exit));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_RegisterGrotto(SceneId scene, SceneAPI_Exit exit, f32 x, f32 y, f32 z));
RECOMP_IMPORT("z64_scene_api",  void SceneAPI_RegisterGrottoToCustomScene(char* sceneName, SceneAPI_Exit exit, f32 x, f32 y, f32 z));

#endif /* SCENE_API_HEADER_H */