#ifndef SCENE_API_EXPORTS_H
#define SCENE_API_EXPORTS_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"

#include "scene_api_types.h"

RECOMP_EXPORT u16 SceneAPI_RegisterScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[], SceneAPI_SceneProperties properties);
RECOMP_EXPORT u16 SceneAPI_RegisterExitOverride(SceneAPI_SceneId fromScene, u16 exitIndex, SceneAPI_SceneId toScene, u16 entranceIndex);
RECOMP_EXPORT u16 SceneAPI_RegisterWarpGrotto(SceneAPI_SceneId fromScene, SceneAPI_SceneId toScene, u16 spawnIndex, f32 x, f32 y, f32 z);
// RECOMP_EXPORT u16 SceneAPI_RegisterWarpGrottoToCustomScene(char* sceneName, SceneAPI_Exit exit, f32 x, f32 y, f32 z);

#endif /* SCENE_API_EXPORTS_H */