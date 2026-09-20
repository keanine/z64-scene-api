#include "scene_api_exports.h"

u16 SceneAPI_RegisterScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[]) {
    u16 slot = sceneAPI_customSceneCount;

    SceneAPI_ScenePermissions permissions;
    SceneAPI_ScenePersistentFlags persistentFlags;
    permissions = CREATE_PERMISSIONS(false, false, false, false, false, false, false, false, false, false, false, false);
    persistentFlags = (SceneAPI_ScenePersistentFlags){ 0, 0, 0, 0 };

    sceneAPI_customScenes[slot] = (struct SceneAPI_CustomScene){ sceneName, header, rooms, (SceneAPI_DungeonData){ false, false }, permissions, persistentFlags, SCENEAPI_EMPTY_MINIMAP };
    sceneAPI_customSceneCount++;
    recomp_printf("Scene %s Initialized in Slot %x\n", sceneName, slot);
    return slot;
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


void SceneAPI_SetPermissionsPreset_None(u16 slot) {
    SceneAPI_ScenePermissions* permissions = &sceneAPI_customScenes[slot].permissions;
    *permissions = CREATE_PERMISSIONS(false, false, false, false, false, false, false, false, false, false, false, false);
}

void SceneAPI_SetPermissionsPreset_All(u16 slot) {
    SceneAPI_ScenePermissions* permissions = &sceneAPI_customScenes[slot].permissions;
    *permissions = CREATE_PERMISSIONS(true, true, true, true, true, true, true, true, true, true, true, true );
}

void SceneAPI_SetPermissionsPreset_Default(u16 slot) {
    SceneAPI_ScenePermissions* permissions = &sceneAPI_customScenes[slot].permissions;
    *permissions = CREATE_PERMISSIONS(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, false, false);
}

void SceneAPI_SetPermissionsPreset_Indoors(u16 slot) {
    SceneAPI_ScenePermissions* permissions = &sceneAPI_customScenes[slot].permissions;
    *permissions = CREATE_PERMISSIONS(0, 1, 1, 0, 1, 1, 0, 1, 1, 0, false, false);
}

void SceneAPI_SetPermissionsPreset_Moon(u16 slot) {
    SceneAPI_ScenePermissions* permissions = &sceneAPI_customScenes[slot].permissions;
    *permissions = CREATE_PERMISSIONS(1, 1, 1, 0, 0, 0, 1, 1, 1, 1, false, false);
}

void SceneAPI_SetPermissionsPreset_NoDoubleTime(u16 slot) {
    SceneAPI_ScenePermissions* permissions = &sceneAPI_customScenes[slot].permissions;
    *permissions = CREATE_PERMISSIONS(1, 1, 1, 0, 1, 1, 1, 1, 1, 1, false, false);
}

void SceneAPI_ApplyDungeonData(u16 slot, bool isDungeon, bool isBossRoom) {
    SceneAPI_DungeonData* dungeonData = &sceneAPI_customScenes[slot].dungeonData;
    dungeonData->isDungeon = isDungeon;
    dungeonData->isBossRoom = isBossRoom;
}

void SceneAPI_ApplyPermissions(u16 slot, bool allowButtonB, bool allowTradeItems, bool allowSongOfTime, bool allowSongOfDoubleTime, bool allowInvertedSongOfTime, bool allowSongOfSoaring, bool allowSongOfStorms, bool allowMasks, bool allowPictoBox, bool allowAllItems, bool allowElegyOfEmptiness, bool allowFierceDeity) {
    SceneAPI_ScenePermissions* permissions = &sceneAPI_customScenes[slot].permissions;
    permissions->allowButtonB = allowButtonB;
    permissions->allowTradeItems = allowTradeItems;
    permissions->allowSongOfTime = allowSongOfTime;
    permissions->allowSongOfDoubleTime = allowSongOfDoubleTime;
    permissions->allowInvertedSongOfTime = allowInvertedSongOfTime;
    permissions->allowSongOfSoaring = allowSongOfSoaring;
    permissions->allowSongOfStorms = allowSongOfStorms;
    permissions->allowMasks = allowMasks;
    permissions->allowPictoBox = allowPictoBox;
    permissions->allowAllItems = allowAllItems;
    permissions->allowElegyOfEmptiness = allowElegyOfEmptiness;
    permissions->allowFierceDeity = allowFierceDeity;
}

void SceneAPI_ApplyPersistentFlags(u16 slot, u32 chest, u32 switch0, u32 switch1, u32 collectible) {
    SceneAPI_ScenePersistentFlags* persistentFlags = &sceneAPI_customScenes[slot].persistentFlags;
    persistentFlags->chest = chest;
    persistentFlags->switch0 = switch0;
    persistentFlags->switch1 = switch1;
    persistentFlags->collectible = collectible;
}

void SceneAPI_AddRoomToMinimap(u16 slot, u16 roomNumber, s32 floor, TexturePtr texture, s32 texWidth, s32 texHeight) {
    sceneAPI_customScenes[slot].minimap.rooms[roomNumber] = 
    (SceneAPI_MinimapRoom){
        true,
        floor,
        texture,
        texWidth,
        texHeight,
    };
}

void SceneAPI_ApplyPermissionButtonB(u16 slot, bool enabled) {
    sceneAPI_customScenes[slot].permissions.allowButtonB = enabled;
}

void SceneAPI_ApplyPermissionTradeItems(u16 slot, bool enabled) {
    sceneAPI_customScenes[slot].permissions.allowTradeItems = enabled;
}

void SceneAPI_ApplyPermissionSongOfTime(u16 slot, bool enabled) {
    sceneAPI_customScenes[slot].permissions.allowSongOfTime = enabled;
}

void SceneAPI_ApplyPermissionSongOfDoubleTime(u16 slot, bool enabled) {
    sceneAPI_customScenes[slot].permissions.allowSongOfDoubleTime = enabled;
}

void SceneAPI_ApplyPermissionInvertedSongOfTime(u16 slot, bool enabled) {
    sceneAPI_customScenes[slot].permissions.allowInvertedSongOfTime = enabled;
}

void SceneAPI_ApplyPermissionSongOfSoaring(u16 slot, bool enabled) {
    sceneAPI_customScenes[slot].permissions.allowSongOfSoaring = enabled;
}

void SceneAPI_ApplyPermissionSongOfStorms(u16 slot, bool enabled) {
    sceneAPI_customScenes[slot].permissions.allowSongOfStorms = enabled;
}

void SceneAPI_ApplyPermissionMasks(u16 slot, bool enabled) {
    sceneAPI_customScenes[slot].permissions.allowMasks = enabled;
}

void SceneAPI_ApplyPermissionPictoBox(u16 slot, bool enabled) {
    sceneAPI_customScenes[slot].permissions.allowPictoBox = enabled;
}

void SceneAPI_ApplyPermissionAllItems(u16 slot, bool enabled) {
    sceneAPI_customScenes[slot].permissions.allowAllItems = enabled;
}

void SceneAPI_ApplyPermissionElegyOfEmptiness(u16 slot, bool enabled) {
    sceneAPI_customScenes[slot].permissions.allowElegyOfEmptiness = enabled;
}

void SceneAPI_ApplyPermissionFierceDeity(u16 slot, bool enabled) {
    sceneAPI_customScenes[slot].permissions.allowFierceDeity = enabled;
}
