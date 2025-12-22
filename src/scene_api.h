#ifndef SCENE_API_H
#define SCENE_API_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"

enum SceneAPI_ExitType { EXITTYPE_VANILLA, EXITTYPE_MODDED };

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

/// This can be an expensive operation
u16 SceneAPI_GetSceneIdByName(char* name);

#endif /* SCENE_API_H */