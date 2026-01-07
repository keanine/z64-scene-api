#ifndef SCENE_API_H
#define SCENE_API_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"

#include "scene_api_types.h"

#include <z64scene.h>

u16 SceneAPI_GetSceneIdByName(char* name);

// enum SceneAPI_ExitType exitType;
// u16 id;
// char* sceneName;
#define SCENEAPI_EXIT(exitType, id, sceneName) (SceneAPI_Exit){ exitType, id, sceneName }

// Woodfall seems to crash?
// #define SCENEAPI_SCENE SCENE_MITURIN
// #define SCENEAPI_SCENE_ENTR 0x3000
#define SCENEAPI_SCENE SCENE_INSIDETOWER
#define SCENEAPI_SCENE_ENTR 0xC010

#define SCENEAPI_VANILLA_ID 65535

#define SCENEAPI_ENTRANCE(scene, spawn) ((((scene) & 0x7F) << 9) | (((spawn) & 0x1F) << 4))

extern struct SceneAPI_CustomScene sceneAPI_customScenes[500];
extern struct SceneAPI_ExitOverride sceneAPI_exitOverrides[500];
extern struct SceneAPI_Grotto sceneAPI_warpGrottos[500];

extern u8 sceneAPI_isNextEntranceModified;
extern u16 sceneAPI_modifiedNextEntrance;
extern u16 sceneAPI_savedGrottoEntrance;

extern PlayState* sceneAPI_play;
extern SceneAPI_Grotto* sceneAPI_currentGrotto;

extern u32 sceneAPI_customSceneIterator;
extern u32 sceneAPI_exitOverrideIterator;
extern u32 sceneAPI_grottosIterator;

extern u16 sceneAPI_customSceneId;
extern u16 sceneAPI_nextCustomSceneId;

RECOMP_DECLARE_EVENT(SceneAPI_Init());
RECOMP_DECLARE_EVENT(SceneAPI_PostInit());

#endif /* SCENE_API_H */