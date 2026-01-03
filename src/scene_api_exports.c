#include "scene_api_exports.h"
#include "scene_api.h"

u16 SceneAPI_RegisterScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[]) {
    u16 slot = sceneAPI_customSceneIterator;
    sceneAPI_customScenes[sceneAPI_customSceneIterator++] = (struct SceneAPI_CustomScene){ sceneName, header, rooms };
    recomp_printf("Scene %s Initialized in Slot %x\n", sceneName, slot);
    return slot;
}

void SceneAPI_RegisterExitOverride(SceneId originalScene, u16 originalEntranceId, SceneAPI_Exit exit) {
    sceneAPI_exitOverrides[sceneAPI_exitOverrideIterator++] = (SceneAPI_ExitOverride){ originalScene, originalEntranceId, exit };
}

void SceneAPI_RegisterGrotto(SceneId scene, SceneAPI_Exit exit, f32 x, f32 y, f32 z) {
    sceneAPI_grottos[sceneAPI_grottosIterator++] = (SceneAPI_Grotto){ scene, SCENEAPI_VANILLA_ID, exit, x, y, z, NULL };
}

void SceneAPI_RegisterGrottoToCustomScene(char* sceneName, SceneAPI_Exit exit, f32 x, f32 y, f32 z) {
    sceneAPI_grottos[sceneAPI_grottosIterator++] = (SceneAPI_Grotto){ SCENEAPI_SCENE, SceneAPI_GetSceneIdByName(sceneName), exit, x, y, z, NULL };
}