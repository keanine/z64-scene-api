#include "scene_api_flags.h"

static PlayState* sPlay;
static s32 sStoredEntrance;

// gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE]
// gSaveContext.cycleSceneFlags[SCENEAPI_SCENE]
// play->actorCtx.sceneFlags

typedef struct SceneAPI_SceneFlags {
    u32 cycleChest;
    u32 cycleSwitch0;
    u32 cycleSwitch1;
    u32 cycleCollectible;
    u32 cycleClearedRoom;
    
    u32 permanentChest;
    u32 permanentSwitch0;
    u32 permanentSwitch1;
    u32 permanentCollectible;
    u32 permanentClearedRoom;
    u32 permanentUnk14;
    u32 permanentRooms;
} SceneAPI_SceneFlags;

#define SCENE_FLAGS_EMPTY (SceneAPI_SceneFlags){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
#define SCENE_FLAGS_CLEAR_CYCLE(sceneFlags) (SceneAPI_SceneFlags){ 0, 0, 0, 0, 0, sceneFlags.permanentChest, sceneFlags.permanentSwitch0, sceneFlags.permanentSwitch1, sceneFlags.permanentCollectible, sceneFlags.permanentClearedRoom, 0, 0 }

// Temp storage for flags, this is saved into KV, and KV loads into this array
SceneAPI_SceneFlags sceneAPI_sceneFlags[500];


// Load a save file from inside FileSelect_LoadGame
static FileSelectState* sFileSelect;
RECOMP_HOOK("Sram_OpenSave") void on_Sram_OpenSave(FileSelectState* fileSelect, SramContext* sramCtx) {
    sFileSelect = fileSelect;
}
RECOMP_HOOK_RETURN("Sram_OpenSave") void return_Sram_OpenSave() {
    if (gSaveContext.fileNum == 0xFF) {
        // Nothing
    } else if (sFileSelect->isOwlSave[gSaveContext.fileNum + 2]) {
        LoadOwlFlagsFromKV();
    } else {
        LoadMainFlagsFromKV();
    }
    PermanentToCycle();
}


// Save on Song of Time and Dawn of the New Day, clear previous cycle
RECOMP_HOOK("Sram_SaveEndOfCycle") void on_Sram_SaveEndOfCycle() {
    SaveMainFlagsToKV();
    DeleteOwlFlagsFromKV();
    // ClearCycleFlags();
    ResetCycleToPersistent();
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
    if (sceneAPI_customSceneId == SCENEAPI_VANILLA_ID) {
        // recomp_printf("Current scene is vanilla. Not saving flags.\n");
        return;
    }
    // recomp_printf("Current scene is custom (%s). Saving flags.\n", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);

    SetSceneFlags(&this->actorCtx, sceneAPI_customSceneId);
}


// Entering a new scene
RECOMP_HOOK("Actor_InitPlayerImpact") void on_Actor_InitPlayerImpact(PlayState* play) {
    if (sceneAPI_customSceneId == SCENEAPI_VANILLA_ID) {
        // recomp_printf("Current scene is vanilla. Not loading flags.\n");
        return;
    }
    // recomp_printf("Current scene is custom (%s). Loading flags.\n", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);

    GetSceneFlags(&play->actorCtx, sceneAPI_customSceneId);
}


// Store cycleSceneFlags into permanentSceneFlags when starting a new day
RECOMP_HOOK("Interface_NewDay") void on_Interface_NewDay(PlayState* play, s32 day) {
    CycleToPermanent();
}


// Store permanentSceneFlags into cycleSceneFlags when restarting after a moon crash
RECOMP_HOOK_RETURN("Sram_ResetSaveFromMoonCrash") void return_Sram_ResetSaveFromMoonCrash() {
    PermanentToCycle();
}


// Store cycleSceneFlags into permanentSceneFlags.
RECOMP_HOOK_RETURN("func_8014546C") void return_func_8014546C() {
    CycleToPermanent();
}


// Set save entrance to fix custom scene autosaves
// Store data in autosave
RECOMP_CALLBACK("*", recomp_on_autosave) void BeforeAutosave(PlayState* play) {
    sStoredEntrance = gSaveContext.save.entrance;
    gSaveContext.save.entrance = ENTRANCE(CLOCK_TOWER_INTERIOR, 0);

    if (sceneAPI_customSceneId != SCENEAPI_VANILLA_ID) {
        SetSceneFlags(&play->actorCtx, sceneAPI_customSceneId);
        CycleToPermanent();
    }

    SaveOwlFlagsToKV();
}

// Restore save entrance to its original value
RECOMP_CALLBACK("*", recomp_after_autosave) void AfterAutosave(PlayState* play) {
    gSaveContext.save.entrance = sStoredEntrance;
}



void LoadMainFlagsFromKV() {
    u16 i;
    for (i = 0; i < sceneAPI_customSceneIterator; i++) {
        u32 len = strlen("SceneAPI.") + strlen(SceneAPI_GetSceneNameById(i));
        char key[len];
        sprintf(key, "SceneAPI.%s", SceneAPI_GetSceneNameById(i));
        if (KV_Slot_Has(key)) {
            KV_Slot_Get(key, &sceneAPI_sceneFlags[i], sizeof(SceneAPI_SceneFlags));
        }
        else {
            sceneAPI_sceneFlags[i] = SCENE_FLAGS_EMPTY;
        } 
    }
}


void LoadOwlFlagsFromKV() {
    u16 i;
    for (i = 0; i < sceneAPI_customSceneIterator; i++) {
        u32 len = strlen("SceneAPI.owl.") + strlen(SceneAPI_GetSceneNameById(i));
        char key[len];
        sprintf(key, "SceneAPI.owl.%s", SceneAPI_GetSceneNameById(i));
        if (KV_Slot_Has(key)) {
            KV_Slot_Get(key, &sceneAPI_sceneFlags[i], sizeof(SceneAPI_SceneFlags));
        }
        else {
            sceneAPI_sceneFlags[i] = SCENE_FLAGS_EMPTY;
        } 
    }
}


void SaveMainFlagsToKV() {
    u16 i;
    for (i = 0; i < sceneAPI_customSceneIterator; i++) {
        u32 len = strlen("SceneAPI.") + strlen(SceneAPI_GetSceneNameById(i));
        char key[len];
        sprintf(key, "SceneAPI.%s", SceneAPI_GetSceneNameById(i));
        KV_Slot_Set(key, &sceneAPI_sceneFlags[i], sizeof(SceneAPI_SceneFlags));   
    }
}


void SaveOwlFlagsToKV() {
    u16 i;
    for (i = 0; i < sceneAPI_customSceneIterator; i++) {
        u32 len = strlen("SceneAPI.owl.") + strlen(SceneAPI_GetSceneNameById(i));
        char key[len];
        sprintf(key, "SceneAPI.owl.%s", SceneAPI_GetSceneNameById(i));
        KV_Slot_Set(key, &sceneAPI_sceneFlags[i], sizeof(SceneAPI_SceneFlags));   
    }
}


void DeleteOwlFlagsFromKV() {
    u16 i;
    for (i = 0; i < sceneAPI_customSceneIterator; i++) {
        u32 len = strlen("SceneAPI.owl.") + strlen(SceneAPI_GetSceneNameById(i));
        char key[len];
        sprintf(key, "SceneAPI.owl.%s", SceneAPI_GetSceneNameById(i));
        KV_Slot_Remove(key);   
    }
}


void GetSceneFlags(ActorContext* actorCtx, u32 customSceneId) {
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


void SetSceneFlags(ActorContext* actorCtx, u32 customSceneId) {
    sceneAPI_sceneFlags[customSceneId].cycleChest       = actorCtx->sceneFlags.chest;
    sceneAPI_sceneFlags[customSceneId].cycleSwitch0     = actorCtx->sceneFlags.switches[0];
    sceneAPI_sceneFlags[customSceneId].cycleSwitch1     = actorCtx->sceneFlags.switches[1];
    sceneAPI_sceneFlags[customSceneId].cycleClearedRoom = actorCtx->sceneFlags.clearedRoom;
    sceneAPI_sceneFlags[customSceneId].cycleCollectible = actorCtx->sceneFlags.collectible[0];

    sceneAPI_sceneFlags[customSceneId].permanentChest = gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].chest;
    sceneAPI_sceneFlags[customSceneId].permanentSwitch0 = gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].switch0;
    sceneAPI_sceneFlags[customSceneId].permanentSwitch1 = gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].switch1;
    sceneAPI_sceneFlags[customSceneId].permanentClearedRoom = gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].clearedRoom;
    sceneAPI_sceneFlags[customSceneId].permanentCollectible = gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].collectible;
    sceneAPI_sceneFlags[customSceneId].permanentUnk14 = gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].unk_14;
    sceneAPI_sceneFlags[customSceneId].permanentRooms = gSaveContext.save.saveInfo.permanentSceneFlags[SCENEAPI_SCENE].rooms;
}

void ClearCycleFlags() {
    u16 i;
    for (i = 0; i < sceneAPI_customSceneIterator; i++) {
        sceneAPI_sceneFlags[i] = SCENE_FLAGS_CLEAR_CYCLE(sceneAPI_sceneFlags[i]);
    }
}


void CycleToPermanent() {
    u16 i;
    for (i = 0; i < sceneAPI_customSceneIterator; i++) {
        sceneAPI_sceneFlags[i].permanentChest = sceneAPI_sceneFlags[i].cycleChest;
        sceneAPI_sceneFlags[i].permanentSwitch0 = sceneAPI_sceneFlags[i].cycleSwitch0;
        sceneAPI_sceneFlags[i].permanentSwitch1 = sceneAPI_sceneFlags[i].cycleSwitch1;
        sceneAPI_sceneFlags[i].permanentClearedRoom = sceneAPI_sceneFlags[i].cycleClearedRoom;
        sceneAPI_sceneFlags[i].permanentCollectible = sceneAPI_sceneFlags[i].cycleCollectible;
    }
}


void PermanentToCycle() {
    u16 i;
    for (i = 0; i < sceneAPI_customSceneIterator; i++) {
        sceneAPI_sceneFlags[i].cycleChest = sceneAPI_sceneFlags[i].permanentChest;
        sceneAPI_sceneFlags[i].cycleSwitch0 = sceneAPI_sceneFlags[i].permanentSwitch0;
        sceneAPI_sceneFlags[i].cycleSwitch1 = sceneAPI_sceneFlags[i].permanentSwitch1;
        sceneAPI_sceneFlags[i].cycleClearedRoom = sceneAPI_sceneFlags[i].permanentClearedRoom;
        sceneAPI_sceneFlags[i].cycleCollectible = sceneAPI_sceneFlags[i].permanentCollectible;
    }
}


void DebugClearCurrentSceneFlags(PlayState* play) {
    play->actorCtx.sceneFlags.chest = 0;
    play->actorCtx.sceneFlags.switches[0] = 0;
    play->actorCtx.sceneFlags.switches[1] = 0;
    play->actorCtx.sceneFlags.clearedRoom = 0;
    play->actorCtx.sceneFlags.collectible[0] = 0;
}

void ResetCycleToPersistent() {
    u16 i;
    for (i = 0; i < sceneAPI_customSceneIterator; i++) {
        sceneAPI_sceneFlags[i].cycleChest &= sceneAPI_customScenes[i].persistentFlags.chest;
        sceneAPI_sceneFlags[i].cycleSwitch0 &= sceneAPI_customScenes[i].persistentFlags.switch0;
        sceneAPI_sceneFlags[i].cycleSwitch1 &= sceneAPI_customScenes[i].persistentFlags.switch1;
        sceneAPI_sceneFlags[i].cycleCollectible &= sceneAPI_customScenes[i].persistentFlags.collectible;
    }
}