#ifndef SCENE_API_EXPORTS_H
#define SCENE_API_EXPORTS_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"

#include "scene_api.h"
#include "scene_api_exit.h"
#include "scene_api_grottos.h"

RECOMP_EXPORT u16 SceneAPI_RegisterScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[], 
    SceneAPI_ScenePermissions permissions, SceneAPI_ScenePersistentFlags persistentFlags);
RECOMP_EXPORT u16 SceneAPI_RegisterExitOverride(SceneAPI_SceneId fromScene, u16 exitIndex, SceneAPI_SceneId toScene, u16 entranceIndex);
RECOMP_EXPORT u16 SceneAPI_RegisterWarpGrotto(SceneAPI_SceneId fromScene, SceneAPI_SceneId toScene, u16 spawnIndex, f32 x, f32 y, f32 z);

RECOMP_EXPORT void SceneAPI_SetPermissionsNone(SceneAPI_ScenePermissions* outPermissions);
RECOMP_EXPORT void SceneAPI_SetPermissionsAll(SceneAPI_ScenePermissions* outPermissions);
RECOMP_EXPORT void SceneAPI_SetPermissionsDefault(SceneAPI_ScenePermissions* outPermissions);
RECOMP_EXPORT void SceneAPI_SetPermissionsIndoors(SceneAPI_ScenePermissions* outPermissions);
RECOMP_EXPORT void SceneAPI_SetPermissionsMoon(SceneAPI_ScenePermissions* outPermissions);
RECOMP_EXPORT void SceneAPI_SetPermissionsNoDoubleTime(SceneAPI_ScenePermissions* outPermissions);

#define CREATE_PERMISSIONS(buttonB, tradeItems, SoT, SoDT, invSoT, soaring, storms, masks, pictoBox, all, elegy, fierceDeity) \
(SceneAPI_ScenePermissions){ buttonB, tradeItems, SoT, SoDT, invSoT, soaring, storms, masks, pictoBox, all, elegy, fierceDeity }

#endif /* SCENE_API_EXPORTS_H */