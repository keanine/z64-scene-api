#ifndef SCENE_API_H
#define SCENE_API_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"
#include <string.h>

#include "scene_api_types.h"

#include <z64scene.h>

extern char* SceneAPI_GetSceneNameById(u32 sceneId);
extern u16 SceneAPI_GetSceneIdByName(char* name);
extern u8 IsCurrentScene(PlayState* play, SceneAPI_SceneId scene);

extern void InitSceneVariables();
extern RestrictionFlags GetRestrictionsFromCustomScene(u16 customSceneId);

#define SCENEAPI_SCENE SCENE_UNSET_01
#define SCENEAPI_SCENE_ENTR ENTR_SCENE_UNSET_08

#define SCENEAPI_VANILLA_ID 65535

#define SCENEAPI_ENTRANCE(scene, spawn) ((((scene) & 0x7F) << 9) | (((spawn) & 0x1F) << 4))

extern struct SceneAPI_CustomScene sceneAPI_customScenes[500];
extern struct SceneAPI_ExitOverride sceneAPI_exitOverrides[500];
extern struct SceneAPI_Grotto sceneAPI_warpGrottos[500];

extern u8 sceneAPI_isNextEntranceModified;
extern u16 sceneAPI_savedGrottoEntrance;

extern PlayState* sceneAPI_play;
extern SceneAPI_Grotto* sceneAPI_currentGrotto;
extern SceneAPI_ExitOverride* sceneAPI_currentExitOverride;

extern u32 sceneAPI_customSceneIterator;
extern u32 sceneAPI_exitOverrideIterator;
extern u32 sceneAPI_grottosIterator;

extern u16 sceneAPI_customSceneId;
extern u16 sceneAPI_nextCustomSceneId;

extern u8 sceneAPI_expansionsEnabled;

RECOMP_DECLARE_EVENT(SceneAPI_Init());
RECOMP_DECLARE_EVENT(SceneAPI_PostInit());

extern u8 D_808141F0[];

extern RestrictionFlags sRestrictionFlags[];
extern SceneTableEntry gSceneTable[SCENE_MAX];
extern PersistentCycleSceneFlags sPersistentCycleSceneFlags[SCENE_MAX];

#define SCENEAPI_DEFINE_ENTRANCE(entranceTable) \
    { ARRAY_COUNT(entranceTable), entranceTable, NULL }
    
#define RESTRICTIONS_SET(hGauge, bButton, aButton, tradeItems, songOfTime, songOfDoubleTime, invSongOfTime, \
                         songOfSoaring, songOfStorms, masks, pictoBox, all)                                 \
    ((((hGauge)&3) << 6) | (((bButton)&3) << 4) | (((aButton)&3) << 2) | (((tradeItems)&3) << 0)),          \
        ((((songOfTime)&3) << 6) | (((songOfDoubleTime)&3) << 4) | (((invSongOfTime)&3) << 2) |             \
         (((songOfSoaring)&3) << 0)),                                                                       \
        ((((songOfStorms)&3) << 6) | (((masks)&3) << 4) | (((pictoBox)&3) << 2) | (((all)&3) << 0))

// Common patterns
#define RESTRICTIONS_NONE RESTRICTIONS_SET(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define RESTRICTIONS_INDOORS RESTRICTIONS_SET(0, 1, 0, 0, 0, 3, 0, 0, 3, 0, 0, 1)
#define RESTRICTIONS_MOON RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0)
#define RESTRICTIONS_NO_DOUBLE_TIME RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0)

#endif /* SCENE_API_H */