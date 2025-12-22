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
} SceneAPI_Exit;

typedef struct SceneAPI_CustomScene {
    char* sceneName;
    SceneCmd* sceneSegment;
    SceneCmd** roomList;
    SceneAPI_Exit* exitIdList;
} SceneAPI_CustomScene;

// typedef struct SceneAPI_Exit {
//     char* customFlag;
//     u16 entrance;
//     u16 customSceneId;
// } SceneAPI_Exit;

typedef struct SceneAPI_ExitOverride {
    SceneId originalScene;
    u16 originalEntranceId;
    u16 newCustomSceneId;
} SceneAPI_ExitOverride;

void SceneAPI_SetSceneAtIndex(u8 customSceneIndex, char* name, SceneCmd* header, SceneCmd* rooms[], SceneAPI_Exit exitIDs[]);
void SceneAPI_AddScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[], SceneAPI_Exit exitIDs[]);
void SceneAPI_AddExitOverride(SceneId originalScene, u16 originalEntranceId, u16 newCustomSceneId);

#endif /* SCENE_API_H */