#ifndef SCENE_API_GROTTOS_H
#define SCENE_API_GROTTOS_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"
#include "scene_api.h"

extern u16 sceneAPI_savedGrottoEntrance;

extern struct SceneAPI_Grotto sceneAPI_warpGrottos[SCENEAPI_MAX_ARRAY];
extern u32 sceneAPI_grottosCount;

extern SceneAPI_Grotto* sceneAPI_currentGrotto;

#endif /* SCENE_API_GROTTOS_H */