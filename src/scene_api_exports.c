#include "scene_api_exports.h"
#include "scene_api.h"

u16 SceneAPI_RegisterScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[], SceneAPI_SceneProperties properties) {
    u16 slot = sceneAPI_customSceneIterator;
    sceneAPI_customScenes[sceneAPI_customSceneIterator++] = (struct SceneAPI_CustomScene){ sceneName, header, rooms, properties };
    recomp_printf("Scene %s Initialized in Slot %x\n", sceneName, slot);
    return slot;
}

u16 SceneAPI_RegisterExitOverride(SceneAPI_SceneId fromScene, u16 exitIndex, SceneAPI_SceneId toScene, u16 entranceIndex) {
    u16 slot = sceneAPI_exitOverrideIterator;
    sceneAPI_exitOverrides[sceneAPI_exitOverrideIterator++] = (SceneAPI_ExitOverride){ fromScene, exitIndex, toScene, entranceIndex };
    return slot;
}

u16 SceneAPI_RegisterWarpGrotto(SceneAPI_SceneId fromScene, SceneAPI_SceneId toScene, u16 spawnIndex, f32 x, f32 y, f32 z) {
    u16 slot = sceneAPI_grottosIterator;
    sceneAPI_warpGrottos[sceneAPI_grottosIterator++] = (SceneAPI_Grotto){ fromScene, toScene, spawnIndex, x, y, z, NULL };
    return slot;
}

// u16 SceneAPI_RegisterWarpGrottoToCustomScene(char* sceneName, SceneAPI_SceneId exit, f32 x, f32 y, f32 z) {
//     u16 slot = sceneAPI_grottosIterator;
//     sceneAPI_warpGrottos[sceneAPI_grottosIterator++] = (SceneAPI_Grotto){ SCENEAPI_SCENE, SceneAPI_GetSceneIdByName(sceneName), exit, x, y, z, NULL };
//     return slot;
// }