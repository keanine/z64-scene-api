#ifndef SCENE_API_H
#define SCENE_API_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"
#include <string.h>

#include "scene_api_types.h"

#include <z64scene.h>

// From Decomp

#define RESTRICTIONS_SET(hGauge, bButton, aButton, tradeItems, songOfTime, songOfDoubleTime, invSongOfTime, \
                         songOfSoaring, songOfStorms, masks, pictoBox, all)                                 \
    ((((hGauge)&3) << 6) | (((bButton)&3) << 4) | (((aButton)&3) << 2) | (((tradeItems)&3) << 0)),          \
        ((((songOfTime)&3) << 6) | (((songOfDoubleTime)&3) << 4) | (((invSongOfTime)&3) << 2) |             \
         (((songOfSoaring)&3) << 0)),                                                                       \
        ((((songOfStorms)&3) << 6) | (((masks)&3) << 4) | (((pictoBox)&3) << 2) | (((all)&3) << 0))

extern u8 _Z2_INSIDETOWERSegmentRomStart[1];
extern u8 _Z2_INSIDETOWERSegmentRomEnd[1];

extern RestrictionFlags sRestrictionFlags[];
extern SceneTableEntry gSceneTable[SCENE_MAX];

extern u8 D_808141F0[];

extern SceneTableEntry entrySceneTableEntry;


// API

#define SCENEAPI_DEFINE_ENTRANCE(entranceTable) \
    { ARRAY_COUNT(entranceTable), entranceTable, NULL }

#define SCENEAPI_ENTRANCE(scene, spawn) ((((scene) & 0x7F) << 9) | (((spawn) & 0x1F) << 4))

#define SCENEAPI_SCENE SCENE_UNSET_01
#define SCENEAPI_SCENE_ENTR ENTR_SCENE_UNSET_08

#define SCENEAPI_INVALID 65535

#define SCENEAPI_MAX_ARRAY 500

extern char* SceneAPI_GetSceneNameById(u32 sceneId);
extern u16 SceneAPI_GetSceneIdByName(char* name);
extern bool SceneAPI_IsCurrentScene(PlayState* play, SceneAPI_SceneId scene);
extern bool SceneAPI_IsCustomScene(PlayState* play);

extern void SceneAPI_UnequipRestrictedItems();
extern RestrictionFlags SceneAPI_GetRestrictionsFromCustomScene(u16 customSceneId);

RECOMP_DECLARE_EVENT(SceneAPI_RegisterScenes());
RECOMP_DECLARE_EVENT(SceneAPI_RegisterGrottosAndExits());

extern struct SceneAPI_CustomScene sceneAPI_customScenes[SCENEAPI_MAX_ARRAY];
extern u32 sceneAPI_customSceneCount;

extern PlayState* sceneAPI_play;

extern RestrictionFlags entryRestrictionFlag;
extern SceneTableEntry entrySceneTableEntry;
extern PersistentCycleSceneFlags entryPersistentCycleSceneFlags;

extern u16 sceneAPI_customSceneId;
extern u16 sceneAPI_nextCustomSceneId;
extern bool sceneAPI_isNextEntranceModified;

extern u8 sceneAPI_modifiedElegyScene;

#endif /* SCENE_API_H */