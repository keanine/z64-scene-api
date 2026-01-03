#ifndef SCENE_API_TYPES_H
#define SCENE_API_TYPES_H

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

typedef struct SceneAPI_CustomScene {
    char* sceneName;
    SceneCmd* sceneSegment;
    SceneCmd** roomList;
    // SceneAPI_Exit* exitIdList;
} SceneAPI_CustomScene;

typedef struct SceneAPI_Grotto {
    SceneId scene;
    u16 customSceneIndex;
    SceneAPI_Exit exit;
    f32 x;
    f32 y;
    f32 z;
    Actor* actor;
} SceneAPI_Grotto;

typedef struct SceneAPI_ExitOverride {
    SceneId originalScene;
    u16 originalEntranceId;
    SceneAPI_Exit newExit;
} SceneAPI_ExitOverride;

extern EntranceSceneId sceneAPI_entrances[];

#endif /* SCENE_API_TYPES_H */