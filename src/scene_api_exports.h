#ifndef SCENE_API_EXPORTS_H
#define SCENE_API_EXPORTS_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"

#include "scene_api_types.h"

RECOMP_EXPORT u16 SceneAPI_RegisterScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[], SceneAPI_SceneProperties properties);
RECOMP_EXPORT u16 SceneAPI_RegisterExitOverride(SceneId originalScene, u16 originalEntranceId, SceneAPI_Exit exit);
RECOMP_EXPORT u16 SceneAPI_RegisterWarpGrotto(SceneId scene, SceneAPI_Exit exit, f32 x, f32 y, f32 z);
RECOMP_EXPORT u16 SceneAPI_RegisterWarpGrottoToCustomScene(char* sceneName, SceneAPI_Exit exit, f32 x, f32 y, f32 z);

#endif /* SCENE_API_EXPORTS_H */