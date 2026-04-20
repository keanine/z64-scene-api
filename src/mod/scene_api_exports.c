#include "scene_api_exports.h"

u16 SceneAPI_RegisterScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[], 
    SceneAPI_ScenePermissions permissions, SceneAPI_ScenePersistentFlags persistentFlags) {
    u16 slot = sceneAPI_customSceneCount;
    sceneAPI_customScenes[sceneAPI_customSceneCount++] = (struct SceneAPI_CustomScene){ sceneName, header, rooms, permissions, persistentFlags };
    recomp_printf("Scene %s Initialized in Slot %x\n", sceneName, slot);
    return slot;
}

u16 SceneAPI_RegisterSceneBasic(char* sceneName, SceneCmd* header, SceneCmd* rooms[]) {
    SceneAPI_ScenePermissions permissions;
    SceneAPI_ScenePersistentFlags persistentFlags;

    SceneAPI_SetPermissionsNone(&permissions);
    persistentFlags = (SceneAPI_ScenePersistentFlags){ 0, 0, 0, 0 };

    SceneAPI_RegisterScene(sceneName, header, rooms, permissions, persistentFlags);
}

u16 SceneAPI_RegisterExitOverride(SceneAPI_SceneId fromScene, u16 exitIndex, SceneAPI_SceneId toScene, u16 entranceIndex) {
    u16 slot = sceneAPI_exitOverrideCount;

    SceneId fromId = SCENEAPI_SCENE;
    SceneId toId = SCENEAPI_SCENE;

    // Entrance_GetSceneIdAbsolute(fromScene.entrId) should work here. RecompInit is probably too early.

    switch (fromScene.sceneType) {
        case SCENEAPI_SCENETYPE_VANILLA:
            fromId = sceneAPI_entranceId_to_sceneId[fromScene.entrId];
            break;
        case SCENEAPI_SCENETYPE_MODDED:
            fromScene.entrId = SCENEAPI_SCENE_ENTR;
            break;
    }

    switch (toScene.sceneType) {
        case SCENEAPI_SCENETYPE_VANILLA:
            toId = sceneAPI_entranceId_to_sceneId[toScene.entrId];
            break;
        case SCENEAPI_SCENETYPE_MODDED:
            toScene.entrId = SCENEAPI_SCENE_ENTR;
            break;
    }

    sceneAPI_exitOverrides[sceneAPI_exitOverrideCount++] = (SceneAPI_ExitOverride){ fromScene, toScene, fromId, toId, exitIndex, entranceIndex };
    return slot;
}

u16 SceneAPI_RegisterWarpGrotto(SceneAPI_SceneId fromScene, SceneAPI_SceneId toScene, u16 spawnIndex, f32 x, f32 y, f32 z) {
    u16 slot = sceneAPI_grottosCount;
    
    SceneId fromId = SCENEAPI_SCENE;
    SceneId toId = SCENEAPI_SCENE;

    if (fromScene.sceneType == SCENEAPI_SCENETYPE_VANILLA) fromId = sceneAPI_entranceId_to_sceneId[fromScene.entrId];
    if (toScene.sceneType == SCENEAPI_SCENETYPE_VANILLA) toId = sceneAPI_entranceId_to_sceneId[toScene.entrId];

    sceneAPI_warpGrottos[sceneAPI_grottosCount++] = (SceneAPI_Grotto){ fromScene, toScene, fromId, toId, spawnIndex, x, y, z, NULL };
    return slot;
}


void SceneAPI_SetPermissionsNone(SceneAPI_ScenePermissions* outPermissions) {
    *outPermissions = CREATE_PERMISSIONS(false, false, false, false, false, false, false, false, false, false, false, false);
}

void SceneAPI_SetPermissionsAll(SceneAPI_ScenePermissions* outPermissions) {
    *outPermissions = CREATE_PERMISSIONS(true, true, true, true, true, true, true, true, true, true, true, true );
}

void SceneAPI_SetPermissionsDefault(SceneAPI_ScenePermissions* outPermissions) {
    *outPermissions = CREATE_PERMISSIONS(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, false, false);
}

void SceneAPI_SetPermissionsIndoors(SceneAPI_ScenePermissions* outPermissions) {
    *outPermissions = CREATE_PERMISSIONS(0, 1, 1, 0, 1, 1, 0, 1, 1, 0, false, false);
}

void SceneAPI_SetPermissionsMoon(SceneAPI_ScenePermissions* outPermissions) {
    *outPermissions = CREATE_PERMISSIONS(1, 1, 1, 0, 0, 0, 1, 1, 1, 1, false, false);
}

void SceneAPI_SetPermissionsNoDoubleTime(SceneAPI_ScenePermissions* outPermissions) {
    *outPermissions = CREATE_PERMISSIONS(1, 1, 1, 0, 1, 1, 1, 1, 1, 1, false, false);
}

SceneAPI_ScenePermissions* SceneAPI_GetScenePermissions(u16 customSceneId) {
    return &sceneAPI_customScenes[customSceneId].permissions;
}