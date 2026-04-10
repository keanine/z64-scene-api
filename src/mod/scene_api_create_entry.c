#include "scene_api.h"
#include "ProxyMM_ObjDepLoader.h"
#include <overlays/actors/ovl_Door_Ana/z_door_ana.h>
#include <z64scene.h>

#include "segment_symbols.h"

extern u8 _Z2_INSIDETOWERSegmentRomStart[1];
extern u8 _Z2_INSIDETOWERSegmentRomEnd[1];

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

#define PERSISTENT_CYCLE_FLAGS_SET(switch0, switch1, chest, collectible) { switch0, switch1, chest, collectible }
#define PERSISTENT_CYCLE_FLAGS_NONE PERSISTENT_CYCLE_FLAGS_SET(0, 0, 0, 0)

#define DEFINE_SCENE(_name, enumValue, _textId, _drawConfig, restrictionFlags, _persistentCycleFlags) \
    { enumValue, restrictionFlags }
RestrictionFlags entryRestrictionFlag = DEFINE_SCENE(Z2_INSIDETOWER, SCENE_UNSET_01, 0, SCENE_DRAW_CFG_MAT_ANIM, RESTRICTIONS_NONE, PERSISTENT_CYCLE_FLAGS_NONE);
#undef DEFINE_SCENE

#define DEFINE_SCENE(name, _enumValue, textId, drawConfig, _restrictionFlags, _persistentCycleFlags) \
    { { SEGMENT_ROM_START(name), SEGMENT_ROM_END(name) }, textId, 0, drawConfig, 0, 0 }
SceneTableEntry entrySceneTableEntry = DEFINE_SCENE(Z2_INSIDETOWER, SCENE_UNSET_01, 0, SCENE_DRAW_CFG_MAT_ANIM, RESTRICTIONS_NONE, PERSISTENT_CYCLE_FLAGS_NONE);
#undef DEFINE_SCENE

#define DEFINE_SCENE(_name, _enumValue, _textId, _drawConfig, _restrictionFlags, persistentCycleFlags) \
    persistentCycleFlags
PersistentCycleSceneFlags entryPersistentCycleSceneFlags = DEFINE_SCENE(Z2_INSIDETOWER, SCENE_UNSET_01, 0, SCENE_DRAW_CFG_MAT_ANIM, RESTRICTIONS_NONE, PERSISTENT_CYCLE_FLAGS_NONE);
#undef DEFINE_SCENE