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

extern void LoadMainFlagsFromKV();
extern void LoadOwlFlagsFromKV();
extern void SaveMainFlagsToKV();
extern void SaveOwlFlagsToKV();
extern void DeleteOwlFlagsFromKV();
extern void ClearCycleFlags();

extern void CycleToPermanent();
extern void PermanentToCycle();
extern void ResetCycleToPersistent();

extern void GetSceneFlags(ActorContext* actorCtx, u32 customSceneId);
extern void SetSceneFlags(ActorContext* actorCtx, u32 customSceneId);

extern void DebugClearCurrentSceneFlags(PlayState* play);

#endif /* SCENE_API_FLAGS_H */