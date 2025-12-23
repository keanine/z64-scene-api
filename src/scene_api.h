#ifndef SCENE_API_H
#define SCENE_API_H

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
    SceneAPI_Exit* exitIdList;
} SceneAPI_CustomScene;

typedef struct SceneAPI_Grotto {
    SceneId scene;
    SceneAPI_Exit exit;
    f32 x;
    f32 y;
    f32 z;
} SceneAPI_Grotto;

typedef struct SceneAPI_ExitOverride {
    SceneId originalScene;
    u16 originalEntranceId;
    SceneAPI_Exit newExit;
} SceneAPI_ExitOverride;

RECOMP_DECLARE_EVENT(SceneAPI_Init());
RECOMP_DECLARE_EVENT(SceneAPI_PostInit());

void SceneAPI_SetSceneAtIndex(u8 customSceneIndex, char* name, SceneCmd* header, SceneCmd* rooms[], SceneAPI_Exit exitIDs[]);
u16 SceneAPI_AddScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[], SceneAPI_Exit exitIDs[]);
void SceneAPI_AddExitOverride(SceneId originalScene, u16 originalEntranceId, SceneAPI_Exit exit);
void SceneAPI_AddGrotto(SceneId scene, SceneAPI_Exit exit, f32 x, f32 y, f32 z);

/// This can be an expensive operation
u16 SceneAPI_GetSceneIdByName(char* name);

// Helper Macros 

// enum SceneAPI_ExitType exitType;
// u16 id;
// char* sceneName;
#define SCENEAPI_EXIT(exitType, id, sceneName) (SceneAPI_Exit){ exitType, id, sceneName }

#endif /* SCENE_API_H */