#include "scene_api_flags.h"

static PlayState* sPlay;

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

// FileSelect_LoadGame
static FileSelectState* sFileSelect;
RECOMP_HOOK("Sram_OpenSave") void on_Sram_OpenSave(FileSelectState* fileSelect, SramContext* sramCtx) {
    sFileSelect = fileSelect;
}
RECOMP_HOOK_RETURN("Sram_OpenSave") void return_Sram_OpenSave() {
    s32 phi_t1;

    if (gSaveContext.fileNum == 0xFF) {
        // Nothing
    } else if (sFileSelect->isOwlSave[gSaveContext.fileNum + 2]) {
        phi_t1 = gSaveContext.fileNum + 2;
        phi_t1 *= 2;
        // Load owl KV into sceneAPI_sceneFlags if isOwlSave is not false
        LoadOwlFlagsFromKV();
    } else {
        phi_t1 = gSaveContext.fileNum;
        phi_t1 *= 2;
        // Load normal KV into sceneAPI_sceneFlags if isOwlSave is false
        LoadMainFlagsFromKV();
    }

    // Store permanentSceneFlags in cycleSceneFlags.
    PermanentToCycle();
}

// (Song of Time and Dawn of the New Day)
RECOMP_HOOK("Sram_SaveEndOfCycle") void on_Sram_SaveEndOfCycle() {
    SaveMainFlagsToKV();
    DeleteOwlFlagsFromKV();
    DeleteCycleFlags();
}

RECOMP_HOOK("Sram_SaveSpecialEnterClockTown") void on_Sram_SaveSpecialEnterClockTown() {
    SaveMainFlagsToKV();
    DeleteOwlFlagsFromKV();
}

RECOMP_HOOK("Sram_StartWriteToFlashOwlSave") void on_Sram_StartWriteToFlashOwlSave() {
    SaveOwlFlagsToKV();
}

// Leaving a custom scene
RECOMP_HOOK("Play_SaveCycleSceneFlags") void on_Play_SaveCycleSceneFlags(PlayState* this) {
    if (sceneAPI_customSceneId == SCENEAPI_VANILLA_ID) {
        recomp_printf("Current scene is vanilla. Not saving flags.\n");
        return;
    }
    recomp_printf("Current scene is custom (%s). Saving flags.\n", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);

    SetSceneFlags(&this->actorCtx, sceneAPI_customSceneId);
}

// Entering a custom scene
RECOMP_HOOK("Actor_InitPlayerImpact") void on_Actor_InitPlayerImpact(PlayState* play) {
    if (sceneAPI_customSceneId == SCENEAPI_VANILLA_ID) {
        recomp_printf("Current scene is vanilla. Not loading flags.\n");
        return;
    }
    recomp_printf("Current scene is custom (%s). Loading flags.\n", sceneAPI_customScenes[sceneAPI_customSceneId].sceneName);

    GetSceneFlags(&play->actorCtx, sceneAPI_customSceneId);
}

// void Interface_NewDay(PlayState* play, s32 day)
// Store cycleSceneFlags in permanentSceneFlags
RECOMP_HOOK("Interface_NewDay") void on_Interface_NewDay(PlayState* play, s32 day) {
    CycleToPermanent();
}

// void Sram_ResetSaveFromMoonCrash(SramContext* sramCtx)
// Store permanentSceneFlags in cycleSceneFlags
RECOMP_HOOK_RETURN("Sram_ResetSaveFromMoonCrash") void return_Sram_ResetSaveFromMoonCrash() {
    PermanentToCycle();
}

// void func_8014546C(SramContext* sramCtx)
// Store cycleSceneFlags in permanentSceneFlags. normal/owl
RECOMP_HOOK_RETURN("func_8014546C") void return_func_8014546C() {
    CycleToPermanent();
}

// void func_80145698(SramContext* sramCtx)
// Store cycleSceneFlags in permanentSceneFlags. normal only
RECOMP_HOOK_RETURN("func_80145698") void return_func_80145698() {
    CycleToPermanent();
}




void LoadMainFlagsFromKV() {
    recomp_printf("Call LoadMainFlagsFromKV\n");
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
    recomp_printf("Call LoadOwlFlagsFromKV\n");
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
    recomp_printf("Call SaveMainFlagsToKV\n");
    u16 i;
    for (i = 0; i < sceneAPI_customSceneIterator; i++) {
        u32 len = strlen("SceneAPI.") + strlen(SceneAPI_GetSceneNameById(i));
        char key[len];
        sprintf(key, "SceneAPI.%s", SceneAPI_GetSceneNameById(i));
        KV_Slot_Set(key, &sceneAPI_sceneFlags[i], sizeof(SceneAPI_SceneFlags));   
    }
}

void SaveOwlFlagsToKV() {
    recomp_printf("Call SaveOwlFlagsToKV\n");
    u16 i;
    for (i = 0; i < sceneAPI_customSceneIterator; i++) {
        u32 len = strlen("SceneAPI.owl.") + strlen(SceneAPI_GetSceneNameById(i));
        char key[len];
        sprintf(key, "SceneAPI.owl.%s", SceneAPI_GetSceneNameById(i));
        KV_Slot_Set(key, &sceneAPI_sceneFlags[i], sizeof(SceneAPI_SceneFlags));   
    }
}


void DeleteOwlFlagsFromKV() {
    recomp_printf("Call DeleteOwlFlagsFromKV\n");
    u16 i;
    for (i = 0; i < sceneAPI_customSceneIterator; i++) {
        u32 len = strlen("SceneAPI.owl.") + strlen(SceneAPI_GetSceneNameById(i));
        char key[len];
        sprintf(key, "SceneAPI.owl.%s", SceneAPI_GetSceneNameById(i));
        KV_Slot_Remove(key);   
    }
}


// Should copy across cycle and permanent into saveContext here too, for actors like z_en_elfgrp.c
// Copy sceneAPI_sceneFlags[i].cycle into actorCtx.sceneFlags
void GetSceneFlags(ActorContext* actorCtx, u32 customSceneId) {
    recomp_printf("Call GetSceneFlags\n");
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

// Copy actorCtx.sceneFlags into sceneAPI_sceneFlags[i].cycle
void SetSceneFlags(ActorContext* actorCtx, u32 customSceneId) {
    recomp_printf("Call SetSceneFlags\n");
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

void DeleteCycleFlags() {
    recomp_printf("Call DeleteCycleFlags\n");
    u16 i;
    for (i = 0; i < sceneAPI_customSceneIterator; i++) {
        sceneAPI_sceneFlags[i] = SCENE_FLAGS_CLEAR_CYCLE(sceneAPI_sceneFlags[i]);
    }
}

void CycleToPermanent() {
    recomp_printf("Call CycleToPermanent\n");
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
    recomp_printf("Call PermanentToCycle\n");
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
    recomp_printf("Call DebugClearCurrentSceneFlags\n");
    play->actorCtx.sceneFlags.chest = 0;
    play->actorCtx.sceneFlags.switches[0] = 0;
    play->actorCtx.sceneFlags.switches[1] = 0;
    play->actorCtx.sceneFlags.clearedRoom = 0;
    play->actorCtx.sceneFlags.collectible[0] = 0;
}

// AUTOSAVE
#define SAVE_TYPE_AUTOSAVE 2

RECOMP_CALLBACK("*", recomp_on_autosave) void on_SaveAutosave(PlayState* play) {
    if (sceneAPI_customSceneId != SCENEAPI_VANILLA_ID) {
        SetSceneFlags(&play->actorCtx, sceneAPI_customSceneId);
    }

    SaveOwlFlagsToKV();
}

// HOOK void Sram_OpenSave()
// if (gSaveContext.save.isOwlSave == SAVE_TYPE_AUTOSAVE)
// change gSaveContext.save.entrance to clocktown

// RETURN void Sram_OpenSave()
// if (gSaveContext.save.isOwlSave == SAVE_TYPE_AUTOSAVE)
// restore gSaveContext.save.entrance

s32 sEntrance;
RECOMP_HOOK("Sram_OpenSave") void on_LoadAutosave(FileSelectState* fileSelect, SramContext* sramCtx) {
    recomp_printf("on load autosave\n");
    if (gSaveContext.save.isOwlSave == SAVE_TYPE_AUTOSAVE) {
        // sEntrance = gSaveContext.save.entrance;
        // gSaveContext.save.entrance = ENTRANCE(SOUTH_CLOCK_TOWN, 0);
    }
}
RECOMP_HOOK_RETURN("Sram_OpenSave") void return_LoadAutosave() {
    recomp_printf("return load autosave\n");
    if (gSaveContext.save.isOwlSave == SAVE_TYPE_AUTOSAVE) {
        // gSaveContext.save.entrance = sEntrance;
    }
}