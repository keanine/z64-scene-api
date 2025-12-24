#ifndef SCENE_API_HEADER_H
#define SCENE_API_HEADER_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"

enum SceneAPI_ExitType { SCENEAPI_EXITTYPE_VANILLA, SCENEAPI_EXITTYPE_MODDED };

typedef struct SceneAPI_Exit {
    enum SceneAPI_ExitType exitType;
    u16 id;
    char* sceneName;
} SceneAPI_Exit;

#define SCENEAPI_EXIT(exitType, id, sceneName) (SceneAPI_Exit){ exitType, id, sceneName }

RECOMP_IMPORT("z64_scene_api", u16 SceneAPI_AddScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[], SceneAPI_Exit exitIDs[]));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_AddExitOverride(SceneId originalScene, u16 originalEntranceId, SceneAPI_Exit exit));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_AddGrotto(SceneId scene, SceneAPI_Exit exit, f32 x, f32 y, f32 z));
RECOMP_IMPORT("z64_scene_api",  void SceneAPI_AddGrottoToCustomScene(char* sceneName, SceneAPI_Exit exit, f32 x, f32 y, f32 z));

#endif /* SCENE_API_HEADER_H */