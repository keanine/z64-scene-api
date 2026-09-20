#ifndef SCENE_API_EXPORTS_H
#define SCENE_API_EXPORTS_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"

#include "scene_api.h"
#include "scene_api_exit.h"
#include "scene_api_grottos.h"

RECOMP_EXPORT u16 SceneAPI_RegisterScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[]);
RECOMP_EXPORT u16 SceneAPI_RegisterExitOverride(SceneAPI_SceneId fromScene, u16 exitIndex, SceneAPI_SceneId toScene, u16 entranceIndex);
RECOMP_EXPORT u16 SceneAPI_RegisterWarpGrotto(SceneAPI_SceneId fromScene, SceneAPI_SceneId toScene, u16 spawnIndex, f32 x, f32 y, f32 z);

RECOMP_EXPORT void SceneAPI_SetPermissionsPreset_None(u16 slot);
RECOMP_EXPORT void SceneAPI_SetPermissionsPreset_All(u16 slot);
RECOMP_EXPORT void SceneAPI_SetPermissionsPreset_Default(u16 slot);
RECOMP_EXPORT void SceneAPI_SetPermissionsPreset_Indoors(u16 slot);
RECOMP_EXPORT void SceneAPI_SetPermissionsPreset_Moon(u16 slot);
RECOMP_EXPORT void SceneAPI_SetPermissionsPreset_NoDoubleTime(u16 slot);

RECOMP_EXPORT void SceneAPI_ApplyDungeonData(u16 slot, bool isDungeon, bool isBossRoom);
RECOMP_EXPORT void SceneAPI_ApplyPersistentFlags(u16 slot, u32 chest, u32 switch0, u32 switch1, u32 collectible);
RECOMP_EXPORT void SceneAPI_AddRoomToMinimap(u16 slot, u16 roomNumber, s32 floor, TexturePtr texture, s32 texWidth, s32 texHeight);

RECOMP_EXPORT void SceneAPI_ApplyAllPermissions(u16 slot, bool allowButtonB, bool allowTradeItems, bool allowSongOfTime, bool allowSongOfDoubleTime, bool allowInvertedSongOfTime, bool allowSongOfSoaring, bool allowSongOfStorms, bool allowMasks, bool allowPictoBox, bool allowAll, bool allowElegyOfEmptiness, bool allowFierceDeity);
RECOMP_EXPORT void SceneAPI_ApplyPermissionButtonB(u16 slot, bool enabled);
RECOMP_EXPORT void SceneAPI_ApplyPermissionTradeItems(u16 slot, bool enabled);
RECOMP_EXPORT void SceneAPI_ApplyPermissionSongOfTime(u16 slot, bool enabled);
RECOMP_EXPORT void SceneAPI_ApplyPermissionSongOfDoubleTime(u16 slot, bool enabled);
RECOMP_EXPORT void SceneAPI_ApplyPermissionInvertedSongOfTime(u16 slot, bool enabled);
RECOMP_EXPORT void SceneAPI_ApplyPermissionSongOfSoaring(u16 slot, bool enabled);
RECOMP_EXPORT void SceneAPI_ApplyPermissionSongOfStorms(u16 slot, bool enabled);
RECOMP_EXPORT void SceneAPI_ApplyPermissionMasks(u16 slot, bool enabled);
RECOMP_EXPORT void SceneAPI_ApplyPermissionPictoBox(u16 slot, bool enabled);
RECOMP_EXPORT void SceneAPI_ApplyPermissionAllItems(u16 slot, bool enabled); // This is not well named.
RECOMP_EXPORT void SceneAPI_ApplyPermissionElegyOfEmptiness(u16 slot, bool enabled);
RECOMP_EXPORT void SceneAPI_ApplyPermissionFierceDeity(u16 slot, bool enabled);

#define CREATE_PERMISSIONS(buttonB, tradeItems, SoT, SoDT, invSoT, soaring, storms, masks, pictoBox, allItems, elegy, fierceDeity) \
(SceneAPI_ScenePermissions){ buttonB, tradeItems, SoT, SoDT, invSoT, soaring, storms, masks, pictoBox, allItems, elegy, fierceDeity }

#endif /* SCENE_API_EXPORTS_H */
