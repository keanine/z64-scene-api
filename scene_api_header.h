#ifndef SCENE_API_HEADER_H
#define SCENE_API_HEADER_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"

typedef struct SceneAPI_ScenePermissions {
    // Restriction Flags
    bool allowButtonB;
    bool allowTradeItems; // Includes deed trade quest, anju/kafei trade quest, bottles, and ocarina
    bool allowSongOfTime;
    bool allowSongOfDoubleTime;
    bool allowInvertedSongOfTime;
    bool allowSongOfSoaring;
    bool allowSongOfStorms;
    bool allowMasks;
    bool allowPictoBox;
    bool allowAll; // "another"; enables all item permissions

    // Additional Flags
    bool allowElegyOfEmptiness;
    bool allowFierceDeity;
} SceneAPI_ScenePermissions;

typedef struct SceneAPI_ScenePersistentFlags {
    u32 chest;
    u32 switch0;
    u32 switch1;
    u32 collectible;
} SceneAPI_ScenePersistentFlags;


typedef struct SceneAPI_SceneId {
    u8 sceneType;
    u16 entrId;
    char* sceneName;
} SceneAPI_SceneId;


#define SCENEAPI_MSCENE_ID(customSceneName) (SceneAPI_SceneId){ 1, 0, customSceneName }
#define SCENEAPI_VSCENE_ID(scene) (SceneAPI_SceneId){ 0, scene, "" }

RECOMP_IMPORT("z64_scene_api", u16 SceneAPI_RegisterScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[]));
RECOMP_IMPORT("z64_scene_api", u16 SceneAPI_RegisterExitOverride(SceneAPI_SceneId fromScene, u16 exitIndex, SceneAPI_SceneId toScene, u16 entranceIndex));
RECOMP_IMPORT("z64_scene_api", u16 SceneAPI_RegisterWarpGrotto(SceneAPI_SceneId fromScene, SceneAPI_SceneId toScene, u16 spawnIndex, f32 x, f32 y, f32 z));

RECOMP_IMPORT("z64_scene_api", void SceneAPI_SetPermissionsPresetNone(u16 slot));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_SetPermissionsPresetAll(u16 slot));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_SetPermissionsPresetDefault(u16 slot));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_SetPermissionsPresetIndoors(u16 slot));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_SetPermissionsPresetMoon(u16 slot));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_SetPermissionsPresetNoDoubleTime(u16 slot));

RECOMP_IMPORT("z64_scene_api", void SceneAPI_ApplyDungeonData(u16 slot, bool isDungeon, bool isBossRoom));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_ApplyAllPermissions(u16 slot, bool allowButtonB, bool allowTradeItems, bool allowSongOfTime, bool allowSongOfDoubleTime, bool allowInvertedSongOfTime, bool allowSongOfSoaring, bool allowSongOfStorms, bool allowMasks, bool allowPictoBox, bool allowAll, bool allowElegyOfEmptiness, bool allowFierceDeity));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_ApplyPersistentFlags(u16 slot, u32 chest, u32 switch0, u32 switch1, u32 collectible));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_AddRoomToMinimap(u16 slot, u16 roomNumber, s32 floor, TexturePtr texture, s32 texWidth, s32 texHeight));

RECOMP_IMPORT("z64_scene_api", void SceneAPI_ApplyPermissionButtonB(u16 slot));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_ApplyPermissionTradeItems(u16 slot));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_ApplyPermissionSongOfTime(u16 slot));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_ApplyPermissionSongOfDoubleTime(u16 slot));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_ApplyPermissionInvertedSongOfTime(u16 slot));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_ApplyPermissionSongOfSoaring(u16 slot));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_ApplyPermissionSongOfStorms(u16 slot));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_ApplyPermissionMasks(u16 slot));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_ApplyPermissionPictoBox(u16 slot));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_ApplyPermissionAllItems(u16 slot)); // This is not well named.
RECOMP_IMPORT("z64_scene_api", void SceneAPI_ApplyPermissionElegyOfEmptiness(u16 slot));
RECOMP_IMPORT("z64_scene_api", void SceneAPI_ApplyPermissionFierceDeity(u16 slot));

#define SCENE_HEADER(scenePrefix) scenePrefix##_scene_header00
#define ROOM_HEADER(scenePrefix, roomNumber) scenePrefix##_room_##roomNumber##_header00

#define DUMMY_SEGMENT(scene, roomNumber) u8 _##scene##_room_##roomNumber##SegmentRomStart[1]; u8 _##scene##_room_##roomNumber##SegmentRomEnd[1];
#define ALL_DUMMY_SEGMENTS(scene) \
DUMMY_SEGMENT(scene, 0) \
DUMMY_SEGMENT(scene, 1) \
DUMMY_SEGMENT(scene, 2) \
DUMMY_SEGMENT(scene, 3) \
DUMMY_SEGMENT(scene, 4) \
DUMMY_SEGMENT(scene, 5) \
DUMMY_SEGMENT(scene, 6) \
DUMMY_SEGMENT(scene, 7) \
DUMMY_SEGMENT(scene, 8) \
DUMMY_SEGMENT(scene, 9) \
DUMMY_SEGMENT(scene, 10) \
DUMMY_SEGMENT(scene, 11) \
DUMMY_SEGMENT(scene, 12) \
DUMMY_SEGMENT(scene, 13) \
DUMMY_SEGMENT(scene, 14) \
DUMMY_SEGMENT(scene, 15) \
DUMMY_SEGMENT(scene, 16) \
DUMMY_SEGMENT(scene, 17) \
DUMMY_SEGMENT(scene, 18) \
DUMMY_SEGMENT(scene, 19) \
DUMMY_SEGMENT(scene, 20) \
DUMMY_SEGMENT(scene, 21) \
DUMMY_SEGMENT(scene, 22) \
DUMMY_SEGMENT(scene, 23) \
DUMMY_SEGMENT(scene, 24) \
DUMMY_SEGMENT(scene, 25) \
DUMMY_SEGMENT(scene, 26) \
DUMMY_SEGMENT(scene, 27) \
DUMMY_SEGMENT(scene, 28) \
DUMMY_SEGMENT(scene, 29) \
DUMMY_SEGMENT(scene, 30) \
DUMMY_SEGMENT(scene, 31) 

#endif /* SCENE_API_HEADER_H */