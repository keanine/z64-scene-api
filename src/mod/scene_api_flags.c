#include "scene_api_flags.h"

static PlayState* sPlay;
static s32 sStoredEntranceBeforeAutosave;

// Storage for flags in the decomp
    // gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE]
    // gSaveContext.cycleSceneFlags[SCENEAPI_SCENE]
    // play->actorCtx.sceneFlags


// Temp storage for flags, this is saved into KV, and KV loads into this array
SceneAPI_SceneFlags sceneAPI_sceneFlags[SCENEAPI_MAX_ARRAY];


void LoadFlagsFromKV(char* prefix) {
    u16 i;
    for (i = 0; i < sceneAPI_customSceneCount; i++) {
        u32 len = strlen(prefix) + 1 + strlen(SceneAPI_GetSceneNameById(i));
        char key[len];
        sprintf(key, "%s.%s", prefix, SceneAPI_GetSceneNameById(i));
        if (KV_Slot_Has(key)) {
            KV_Slot_Get(key, &sceneAPI_sceneFlags[i], sizeof(SceneAPI_SceneFlags));
        }
        else {
            sceneAPI_sceneFlags[i] = SCENE_FLAGS_EMPTY;
        } 
    }
}

void SaveFlagsToKV(char* prefix) {
    u16 i;
    for (i = 0; i < sceneAPI_customSceneCount; i++) {
        u32 len = strlen(prefix) + 1 + strlen(SceneAPI_GetSceneNameById(i));
        char key[len];
        sprintf(key, "%s.%s", prefix, SceneAPI_GetSceneNameById(i));
        KV_Slot_Set(key, &sceneAPI_sceneFlags[i], sizeof(SceneAPI_SceneFlags));   
    }
}

void DeleteFlagsFromKV(char* prefix) {
    u16 i;
    for (i = 0; i < sceneAPI_customSceneCount; i++) {
        u32 len = strlen(prefix) + 1 + strlen(SceneAPI_GetSceneNameById(i));
        char key[len];
        sprintf(key, "%s.%s", prefix, SceneAPI_GetSceneNameById(i));
        KV_Slot_Remove(key);
    }
}


void LoadMainFlagsFromKV() {
    LoadFlagsFromKV("SceneAPI");
}


void LoadOwlFlagsFromKV() {
    LoadFlagsFromKV("SceneAPI.owl");
}


void SaveMainFlagsToKV() {
    SaveFlagsToKV("SceneAPI");
}


void SaveOwlFlagsToKV() {
    SaveFlagsToKV("SceneAPI.owl");
}


void DeleteOwlFlagsFromKV() {
    DeleteFlagsFromKV("SceneAPI.owl");
}


void UpdateActorAndSaveContextFromSceneFlags(ActorContext* actorCtx, u32 customSceneId) {
    actorCtx->sceneFlags.chest =          sceneAPI_sceneFlags[customSceneId].cycleChest;
    actorCtx->sceneFlags.switches[0] =    sceneAPI_sceneFlags[customSceneId].cycleSwitch0;
    actorCtx->sceneFlags.switches[1] =    sceneAPI_sceneFlags[customSceneId].cycleSwitch1;
    actorCtx->sceneFlags.clearedRoom =    sceneAPI_sceneFlags[customSceneId].cycleClearedRoom;
    actorCtx->sceneFlags.collectible[0] = sceneAPI_sceneFlags[customSceneId].cycleCollectible;

    gSaveContext.cycleSceneFlags[SCENEAPI_SCENE].chest =       sceneAPI_sceneFlags[customSceneId].cycleChest;
    gSaveContext.cycleSceneFlags[SCENEAPI_SCENE].switch0 =     sceneAPI_sceneFlags[customSceneId].cycleSwitch0;
    gSaveContext.cycleSceneFlags[SCENEAPI_SCENE].switch1 =     sceneAPI_sceneFlags[customSceneId].cycleSwitch1;
    gSaveContext.cycleSceneFlags[SCENEAPI_SCENE].clearedRoom = sceneAPI_sceneFlags[customSceneId].cycleClearedRoom;
    gSaveContext.cycleSceneFlags[SCENEAPI_SCENE].collectible = sceneAPI_sceneFlags[customSceneId].cycleCollectible;

    gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].chest =       sceneAPI_sceneFlags[customSceneId].permanentChest;
    gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].switch0 =     sceneAPI_sceneFlags[customSceneId].permanentSwitch0;
    gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].switch1 =     sceneAPI_sceneFlags[customSceneId].permanentSwitch1;
    gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].clearedRoom = sceneAPI_sceneFlags[customSceneId].permanentClearedRoom;
    gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].collectible = sceneAPI_sceneFlags[customSceneId].permanentCollectible;
    gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].unk_14 =      sceneAPI_sceneFlags[customSceneId].permanentUnk14;
    gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].rooms =       sceneAPI_sceneFlags[customSceneId].permanentRooms;
}


void UpdateSceneFlagsFromActorAndSaveContext(ActorContext* actorCtx, u32 customSceneId) {
    sceneAPI_sceneFlags[customSceneId].cycleChest       = actorCtx->sceneFlags.chest;
    sceneAPI_sceneFlags[customSceneId].cycleSwitch0     = actorCtx->sceneFlags.switches[0];
    sceneAPI_sceneFlags[customSceneId].cycleSwitch1     = actorCtx->sceneFlags.switches[1];
    sceneAPI_sceneFlags[customSceneId].cycleClearedRoom = actorCtx->sceneFlags.clearedRoom;
    sceneAPI_sceneFlags[customSceneId].cycleCollectible = actorCtx->sceneFlags.collectible[0];

    sceneAPI_sceneFlags[customSceneId].permanentChest =       gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].chest;
    sceneAPI_sceneFlags[customSceneId].permanentSwitch0 =     gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].switch0;
    sceneAPI_sceneFlags[customSceneId].permanentSwitch1 =     gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].switch1;
    sceneAPI_sceneFlags[customSceneId].permanentClearedRoom = gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].clearedRoom;
    sceneAPI_sceneFlags[customSceneId].permanentCollectible = gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].collectible;
    sceneAPI_sceneFlags[customSceneId].permanentUnk14 =       gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].unk_14;
    sceneAPI_sceneFlags[customSceneId].permanentRooms =       gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].rooms;
}


void ClearCycleFlags() {
    u16 i;
    for (i = 0; i < sceneAPI_customSceneCount; i++) {
        sceneAPI_sceneFlags[i] = SCENE_FLAGS_CLEAR_CYCLE(sceneAPI_sceneFlags[i]);
    }
}


void StoreCycleAsPermanentFlags() {
    u16 i;
    for (i = 0; i < sceneAPI_customSceneCount; i++) {
        sceneAPI_sceneFlags[i].permanentChest = sceneAPI_sceneFlags[i].cycleChest;
        sceneAPI_sceneFlags[i].permanentSwitch0 = sceneAPI_sceneFlags[i].cycleSwitch0;
        sceneAPI_sceneFlags[i].permanentSwitch1 = sceneAPI_sceneFlags[i].cycleSwitch1;
        sceneAPI_sceneFlags[i].permanentClearedRoom = sceneAPI_sceneFlags[i].cycleClearedRoom;
        sceneAPI_sceneFlags[i].permanentCollectible = sceneAPI_sceneFlags[i].cycleCollectible;
    }
}


void StorePermanentFlagsAsCycleFlags() {
    u16 i;
    for (i = 0; i < sceneAPI_customSceneCount; i++) {
        sceneAPI_sceneFlags[i].cycleChest = sceneAPI_sceneFlags[i].permanentChest;
        sceneAPI_sceneFlags[i].cycleSwitch0 = sceneAPI_sceneFlags[i].permanentSwitch0;
        sceneAPI_sceneFlags[i].cycleSwitch1 = sceneAPI_sceneFlags[i].permanentSwitch1;
        sceneAPI_sceneFlags[i].cycleClearedRoom = sceneAPI_sceneFlags[i].permanentClearedRoom;
        sceneAPI_sceneFlags[i].cycleCollectible = sceneAPI_sceneFlags[i].permanentCollectible;
    }
}

void ResetCycleFlagsToPersistentFlags() {
    u16 i;
    for (i = 0; i < sceneAPI_customSceneCount; i++) {
        sceneAPI_sceneFlags[i].cycleChest &= sceneAPI_customScenes[i].persistentFlags.chest;
        sceneAPI_sceneFlags[i].cycleSwitch0 &= sceneAPI_customScenes[i].persistentFlags.switch0;
        sceneAPI_sceneFlags[i].cycleSwitch1 &= sceneAPI_customScenes[i].persistentFlags.switch1;
        sceneAPI_sceneFlags[i].cycleCollectible &= sceneAPI_customScenes[i].persistentFlags.collectible;
    }
}


void DebugClearCurrentSceneFlags(PlayState* play) {
    play->actorCtx.sceneFlags.chest = 0;
    play->actorCtx.sceneFlags.switches[0] = 0;
    play->actorCtx.sceneFlags.switches[1] = 0;
    play->actorCtx.sceneFlags.clearedRoom = 0;
    play->actorCtx.sceneFlags.collectible[0] = 0;
}


// ==== HOOKS ====


// Load a save file from inside FileSelect_LoadGame
static FileSelectState* sFileSelect;
RECOMP_HOOK("Sram_OpenSave") void on_Sram_OpenSave(FileSelectState* fileSelect, SramContext* sramCtx) {
    sFileSelect = fileSelect;
}
RECOMP_HOOK_RETURN("Sram_OpenSave") void return_Sram_OpenSave() {
    if (gSaveContext.flashSaveAvailable) {
        if (gSaveContext.fileNum == 0xFF) {
            // Nothing
        } else if (sFileSelect->isOwlSave[gSaveContext.fileNum + 2]) {
            LoadOwlFlagsFromKV();
        } else {
            LoadMainFlagsFromKV();
        }
        PermanentToCycle();
    }
}


// Save on Song of Time and Dawn of the New Day, which ends the cycle
RECOMP_HOOK("Sram_SaveEndOfCycle") void on_Sram_SaveEndOfCycle() {
    SaveMainFlagsToKV();
    DeleteOwlFlagsFromKV();
    ResetCycleFlagsToPersistentFlags();
}


// First Cycle Save
RECOMP_HOOK("Sram_SaveSpecialEnterClockTown") void on_Sram_SaveSpecialEnterClockTown() {
    SaveMainFlagsToKV();
    DeleteOwlFlagsFromKV();
    CycleToPermanent();
}

// Owl Save
RECOMP_HOOK("Sram_StartWriteToFlashOwlSave") void on_Sram_StartWriteToFlashOwlSave() {
    SaveOwlFlagsToKV();
}


// Leaving a new scene
RECOMP_HOOK("Play_SaveCycleSceneFlags") void on_Play_SaveCycleSceneFlags(PlayState* this) {
    if (sceneAPI_customSceneId != SCENEAPI_INVALID) {
        UpdateSceneFlagsFromActorAndSaveContext(&this->actorCtx, sceneAPI_customSceneId);
    }
}


// Entering a new scene
RECOMP_HOOK("Actor_InitPlayerImpact") void on_Actor_InitPlayerImpact(PlayState* play) {
    if (sceneAPI_customSceneId != SCENEAPI_INVALID) {
        UpdateActorAndSaveContextFromSceneFlags(&play->actorCtx, sceneAPI_customSceneId);
    }
}


// Starting a new day
RECOMP_HOOK("Interface_NewDay") void on_Interface_NewDay(PlayState* play, s32 day) {
    CycleToPermanent();
}


// Restarting after a moon crash
RECOMP_HOOK_RETURN("Sram_ResetSaveFromMoonCrash") void return_Sram_ResetSaveFromMoonCrash() {
    PermanentToCycle();
}


// Store cycleSceneFlags into permanentSceneFlags?
RECOMP_HOOK_RETURN("func_8014546C") void return_func_8014546C() {
    CycleToPermanent();
}


// Set save entrance to fix custom scene autosaves
// Store data in autosave
RECOMP_CALLBACK("*", recomp_on_autosave) void BeforeAutosave(PlayState* play) {
    sStoredEntranceBeforeAutosave = gSaveContext.save.entrance;
    gSaveContext.save.entrance = ENTRANCE(CLOCK_TOWER_INTERIOR, 0);

    if (sceneAPI_customSceneId != SCENEAPI_INVALID) {
        UpdateSceneFlagsFromActorAndSaveContext(&play->actorCtx, sceneAPI_customSceneId);
        CycleToPermanent();
    }

    SaveOwlFlagsToKV();
}

// Restore save entrance to its original value
RECOMP_CALLBACK("*", recomp_after_autosave) void AfterAutosave(PlayState* play) {
    gSaveContext.save.entrance = sStoredEntranceBeforeAutosave;
}