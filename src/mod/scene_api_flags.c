#include "scene_api_flags.h"
#include "ProxyMM_KV.h"
#include <string.h>
char *strcat(char *dest, const char *src);

void ClearCustomSceneFlags() {
    gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].chest = 0;
    gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].switch0 = 0;
    gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].switch1 = 0;
    gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].clearedRoom = 0;
    gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].collectible = 0;
    gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].rooms = 0;
}