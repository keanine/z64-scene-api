#ifndef SCENE_API_EXIT_H
#define SCENE_API_EXIT_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"

#include "scene_api.h"

extern SceneAPI_ExitOverride* sceneAPI_currentExitOverride;

extern struct SceneAPI_ExitOverride sceneAPI_exitOverrides[SCENEAPI_MAX_ARRAY];
extern u32 sceneAPI_exitOverrideCount;

#endif /* SCENE_API_EXIT_H */