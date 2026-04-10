#include "scene_api_flags.h"
#include "ProxyMM_KV.h"
#include "libc64/sprintf.h"

static PlayState* sPlay;

// gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE]
// gSaveContext.cycleSceneFlags[SCENEAPI_SCENE]
// play->actorCtx.sceneFlags

void ClearCustomSceneFlags(PlayState* play) {
    play->actorCtx.sceneFlags.chest = 0;
    play->actorCtx.sceneFlags.switches[0] = 0;
    play->actorCtx.sceneFlags.switches[1] = 0;
    play->actorCtx.sceneFlags.clearedRoom = 0;
    play->actorCtx.sceneFlags.collectible[0] = 0;
}


RECOMP_HOOK("Play_SaveCycleSceneFlags") void SaveCustomSceneFlagsStart(PlayState* this) {
    sPlay = this;
}

RECOMP_HOOK_RETURN("Play_SaveCycleSceneFlags") void SaveCustomSceneFlagsEnd() {
    if (sceneAPI_customSceneId == SCENEAPI_VANILLA_ID) {
        recomp_printf("Current scene is vanilla. Not saving flags.\n");
        return;
    }
    recomp_printf("Current scene is custom (%s). Saving flags.\n", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);

    ActorContext* actorCtx;

    u32 chest;
    u32 switch0;
    u32 switch1;
    u32 collectible;
    u32 clearedRoom;

    actorCtx = &sPlay->actorCtx;

    // concat the ids
    char chest_id[100]; sprintf(chest_id, "%s chest", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);
    char switch0_id[100]; sprintf(switch0_id, "%s switch0", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);
    char switch1_id[100]; sprintf(switch1_id, "%s switch1", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);
    char collectible_id[100]; sprintf(collectible_id, "%s collectible", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);
    char clearedRoom_id[100]; sprintf(clearedRoom_id, "%s clearedRoom", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);

    // get the data from actorCtx
    chest = sPlay->actorCtx.sceneFlags.chest;
    switch0 = sPlay->actorCtx.sceneFlags.switches[0];
    switch1 = sPlay->actorCtx.sceneFlags.switches[1];
    collectible = sPlay->actorCtx.sceneFlags.collectible[0];
    clearedRoom = sPlay->actorCtx.sceneFlags.clearedRoom;

    // apply the data to KV
    KV_Slot_Set_U32(chest_id, chest);
    KV_Slot_Set_U32(switch0_id, switch0);
    KV_Slot_Set_U32(switch1_id, switch1);
    KV_Slot_Set_U32(collectible_id, collectible);
    KV_Slot_Set_U32(clearedRoom_id, clearedRoom);
}

// This function is used once in the game, directly after data is loaded into actorCtx->sceneFlags
RECOMP_HOOK("Actor_InitPlayerImpact") void LoadCustomSceneFlags(PlayState* play) {
    if (sceneAPI_customSceneId == SCENEAPI_VANILLA_ID) {
        recomp_printf("Current scene is vanilla. Not loading flags.\n");
        return;
    }
    recomp_printf("Current scene is custom (%s). Loading flags.\n", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);

    ActorContext* actorCtx;
    CycleSceneFlags* cycleFlags;

    u32 chest;
    u32 switch0;
    u32 switch1;
    u32 collectible;
    u32 clearedRoom;

    actorCtx = &play->actorCtx;

    // concat the ids
    char chest_id[100]; sprintf(chest_id, "%s chest", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);
    char switch0_id[100]; sprintf(switch0_id, "%s switch0", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);
    char switch1_id[100]; sprintf(switch1_id, "%s switch1", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);
    char collectible_id[100]; sprintf(collectible_id, "%s collectible", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);
    char clearedRoom_id[100]; sprintf(clearedRoom_id, "%s clearedRoom", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);

    // get the data from KV
    chest = KV_Slot_Get_U32(chest_id, 0);
    switch0 = KV_Slot_Get_U32(switch0_id, 0);
    switch1 = KV_Slot_Get_U32(switch1_id, 0);
    collectible = KV_Slot_Get_U32(collectible_id, 0);
    clearedRoom = KV_Slot_Get_U32(clearedRoom_id, 0);

    // apply the data to actorCtx
    actorCtx->sceneFlags.chest = chest;
    actorCtx->sceneFlags.switches[0] = switch0;
    actorCtx->sceneFlags.switches[1] = switch1;
    actorCtx->sceneFlags.collectible[0] = collectible;
    actorCtx->sceneFlags.clearedRoom = clearedRoom;
}