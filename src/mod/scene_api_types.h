#ifndef SCENE_API_TYPES_H
#define SCENE_API_TYPES_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"

enum SceneAPI_SceneType { SCENEAPI_SCENETYPE_VANILLA, SCENEAPI_SCENETYPE_MODDED };

typedef struct SceneAPI_SceneId {
    u8 sceneType;
    u16 entrId;
    char* sceneName;
} SceneAPI_SceneId;


typedef struct SceneAPI_ScenePermissions {
    // Restriction Flags
    // bool enableHeartGauge; // Not implemented
    bool allowButtonB;
    // bool enableButtonA; // Not implemented
    bool allowTradeItems;
    bool allowSongOfTime;
    bool allowSongOfDoubleTime;
    bool allowInvertedSongOfTime;
    bool allowSongOfSoaring;
    bool allowSongOfStorms;
    bool allowMasks;
    bool allowPictoBox;
    bool allowAll;

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


typedef struct SceneAPI_CustomScene {
    char* sceneName;
    SceneCmd* sceneSegment;
    SceneCmd** roomList;
    SceneAPI_ScenePermissions permissions;
    SceneAPI_ScenePersistentFlags persistentFlags;
} SceneAPI_CustomScene;


typedef struct SceneAPI_Grotto {
    SceneAPI_SceneId fromScene;
    SceneAPI_SceneId toScene;
    SceneId fromSceneId;
    SceneId toSceneId;
    u16 spawnIndex;
    f32 x;
    f32 y;
    f32 z;
    Actor* actor;
} SceneAPI_Grotto;


typedef struct SceneAPI_ExitOverride {
    SceneAPI_SceneId fromScene;
    SceneAPI_SceneId toScene;
    SceneId fromSceneId;
    SceneId toSceneId;
    u16 exitIndex;
    u16 entranceIndex;
} SceneAPI_ExitOverride;


typedef struct {
    /* 0x0 */ u8 scene;
    /* 0x1 */ u8 flags1;
    /* 0x2 */ u8 flags2;
    /* 0x3 */ u8 flags3;
} RestrictionFlags; // size = 0x4


typedef struct PersistentCycleSceneFlags {
    /* 0x0 */ u32 switch0;
    /* 0x4 */ u32 switch1;
    /* 0x8 */ u32 chest;
    /* 0xC */ u32 collectible;
} PersistentCycleSceneFlags; // size = 0x10


typedef struct SceneAPI_SceneFlags {
    u32 cycleChest;
    u32 cycleSwitch0;
    u32 cycleSwitch1;
    u32 cycleCollectible;
    u32 cycleClearedRoom;
    
    u32 permanentChest;
    u32 permanentSwitch0;
    u32 permanentSwitch1;
    u32 permanentCollectible;
    u32 permanentClearedRoom;
    u32 permanentUnk14;
    u32 permanentRooms;
} SceneAPI_SceneFlags;


extern EntranceSceneId sceneAPI_sceneId_to_entranceId[];
extern SceneId sceneAPI_entranceId_to_sceneId[];

#endif /* SCENE_API_TYPES_H */