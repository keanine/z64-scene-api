#ifndef SCENE_API_TYPES_H
#define SCENE_API_TYPES_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"

enum SceneAPI_SceneType { SCENEAPI_SCENETYPE_VANILLA, SCENEAPI_SCENETYPE_MODDED };

typedef struct SceneAPI_SceneId {
    u8 sceneType;
    u16 sceneId;
    char* sceneName;
} SceneAPI_SceneId;

typedef struct SceneAPI_SceneProperties {
    u8 enableElegyOfEmptiness;
    u8 enableSongOfSoaring;
} SceneAPI_SceneProperties;

typedef struct SceneAPI_CustomScene {
    char* sceneName;
    SceneCmd* sceneSegment;
    SceneCmd** roomList;
    SceneAPI_SceneProperties properties;
} SceneAPI_CustomScene;

typedef struct SceneAPI_Grotto {
    // SceneId scene;
    // u16 customSceneIndex;
    // SceneAPI_SceneId exit;
    SceneAPI_SceneId fromScene;
    SceneAPI_SceneId toScene;
    u16 spawnIndex;
    f32 x;
    f32 y;
    f32 z;
    Actor* actor;
} SceneAPI_Grotto;

typedef struct SceneAPI_ExitOverride {
    SceneAPI_SceneId fromScene;
    u16 exitIndex;
    SceneAPI_SceneId toScene;
    u16 entranceIndex;
} SceneAPI_ExitOverride;

extern EntranceSceneId sceneAPI_entrances[];

#endif /* SCENE_API_TYPES_H */