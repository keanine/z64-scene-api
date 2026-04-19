#ifndef SCENE_API_FLAGS_H
#define SCENE_API_FLAGS_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"

#include "scene_api.h"
#include "overlays/gamestates/ovl_file_choose/z_file_select.h"

#include "ProxyMM_KV.h"
#include "libc64/sprintf.h"

extern void LoadFlagsFromKV(char* prefix);
extern void SaveFlagsFromKV(char* prefix);
extern void DeleteFlagsFromKV(char* prefix);

extern void LoadMainFlagsFromKV();
extern void LoadOwlFlagsFromKV();
extern void SaveMainFlagsToKV();
extern void SaveOwlFlagsToKV();
extern void DeleteOwlFlagsFromKV();
extern void ClearCycleFlags();

extern void StoreCycleAsPermanentFlags();
extern void StorePermanentFlagsAsCycleFlags();
extern void ResetCycleFlagsToPersistentFlags();

extern void UpdateActorAndSaveContextFromSceneFlags(ActorContext* actorCtx, u32 customSceneId);
extern void UpdateSceneFlagsFromActorAndSaveContext(ActorContext* actorCtx, u32 customSceneId);

extern void DebugClearCurrentSceneFlags(PlayState* play);

extern struct SceneAPI_SceneFlags sceneAPI_sceneFlags[SCENEAPI_MAX_ARRAY];

#define SCENE_FLAGS_EMPTY (SceneAPI_SceneFlags){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
#define SCENE_FLAGS_CLEAR_CYCLE(sceneFlags) (SceneAPI_SceneFlags){ 0, 0, 0, 0, 0, sceneFlags.permanentChest, sceneFlags.permanentSwitch0, sceneFlags.permanentSwitch1, sceneFlags.permanentCollectible, sceneFlags.permanentClearedRoom, 0, 0 }

#endif /* SCENE_API_FLAGS_H */