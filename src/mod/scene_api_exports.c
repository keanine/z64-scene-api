#include "scene_api_exports.h"
#include "scene_api.h"

u16 SceneAPI_RegisterScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[], 
    SceneAPI_ScenePermissions permissions, SceneAPI_ScenePersistentFlags persistentFlags) {
    u16 slot = sceneAPI_customSceneIterator;
    sceneAPI_customScenes[sceneAPI_customSceneIterator++] = (struct SceneAPI_CustomScene){ sceneName, header, rooms, permissions, persistentFlags };
    recomp_printf("Scene %s Initialized in Slot %x\n", sceneName, slot);
    return slot;
}

u16 SceneAPI_RegisterExitOverride(SceneAPI_SceneId fromScene, u16 exitIndex, SceneAPI_SceneId toScene, u16 entranceIndex) {
    u16 slot = sceneAPI_exitOverrideIterator;

    SceneId fromId = SCENEAPI_SCENE;
    SceneId toId = SCENEAPI_SCENE;

    // Entrance_GetSceneIdAbsolute(fromScene.entrId)
    if (fromScene.sceneType == SCENEAPI_SCENETYPE_VANILLA) fromId = sceneAPI_entranceId_to_sceneId[fromScene.entrId];
    if (toScene.sceneType == SCENEAPI_SCENETYPE_VANILLA) toId = sceneAPI_entranceId_to_sceneId[toScene.entrId];

    sceneAPI_exitOverrides[sceneAPI_exitOverrideIterator++] = (SceneAPI_ExitOverride){ fromScene, toScene, fromId, toId, exitIndex, entranceIndex };
    return slot;
}

u16 SceneAPI_RegisterWarpGrotto(SceneAPI_SceneId fromScene, SceneAPI_SceneId toScene, u16 spawnIndex, f32 x, f32 y, f32 z) {
    u16 slot = sceneAPI_grottosIterator;
    
    SceneId fromId = SCENEAPI_SCENE;
    SceneId toId = SCENEAPI_SCENE;

    if (fromScene.sceneType == SCENEAPI_SCENETYPE_VANILLA) fromId = sceneAPI_entranceId_to_sceneId[fromScene.entrId];
    if (toScene.sceneType == SCENEAPI_SCENETYPE_VANILLA) toId = sceneAPI_entranceId_to_sceneId[toScene.entrId];

    sceneAPI_warpGrottos[sceneAPI_grottosIterator++] = (SceneAPI_Grotto){ fromScene, toScene, fromId, toId, spawnIndex, x, y, z, NULL };
    return slot;
}

void SceneAPI_SetPermissionsNone(SceneAPI_ScenePermissions* outPermissions) {
    *outPermissions = (SceneAPI_ScenePermissions){ false, false, false, false, false, false, false, false, false, false, false };
}

void SceneAPI_SetPermissionsAll(SceneAPI_ScenePermissions* outPermissions) {
    *outPermissions = (SceneAPI_ScenePermissions){ true, true, true, true, true, true, true, true, true, true, true };
}

void SceneAPI_SetPermissionsDefault(SceneAPI_ScenePermissions* outPermissions) {
    *outPermissions = (SceneAPI_ScenePermissions){ true, true, true, true, true, true, true, false, true, true, true };
}

void SceneAPI_SetPermissionsIndoors(SceneAPI_ScenePermissions* outPermissions) {
    *outPermissions = (SceneAPI_ScenePermissions){ false, true, true, false, true, true, false, false, true, true, false };
}

void SceneAPI_SetPermissionsMoon(SceneAPI_ScenePermissions* outPermissions) {
    *outPermissions = (SceneAPI_ScenePermissions){ true, true, true, false, false, false, true, false, true, true, true };
}

void SceneAPI_SetPermissionsNoDoubleTime(SceneAPI_ScenePermissions* outPermissions) {
    *outPermissions = (SceneAPI_ScenePermissions){ true, true, true, false, true, true, true, false, true, true, true };
}