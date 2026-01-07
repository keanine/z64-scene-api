#ifndef SCENE_API_HEADER_H
#define SCENE_API_HEADER_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"

typedef struct SceneAPI_SceneProperties {
    u8 enableElegyOfEmptiness;
    u8 enableSongOfSoaring;
} SceneAPI_SceneProperties;

#define SCENEAPI_DEFAULT_PROPERTIES (SceneAPI_SceneProperties){ false, false }
#define SCENEAPI_PROPERTIES(elegy, soaring) (SceneAPI_SceneProperties){ elegy, soaring }

typedef struct SceneAPI_Exit {
    u8 exitType;
    u16 id;
    char* sceneName;
} SceneAPI_Exit;

#define SCENEAPI_MODDED_EXIT(sceneName) (SceneAPI_Exit){ 1, 0, sceneName }
#define SCENEAPI_VANILLA_EXIT(entranceId) (SceneAPI_Exit){ 0, entranceId, "" }

RECOMP_IMPORT("z64_scene_api", u16 SceneAPI_RegisterScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[], SceneAPI_SceneProperties properties));
RECOMP_IMPORT("z64_scene_api", u16 SceneAPI_RegisterExitOverride(SceneId originalScene, u16 originalEntranceId, SceneAPI_Exit exit));
RECOMP_IMPORT("z64_scene_api", u16 SceneAPI_RegisterWarpGrotto(SceneId scene, SceneAPI_Exit exit, f32 x, f32 y, f32 z));
RECOMP_IMPORT("z64_scene_api", u16 SceneAPI_RegisterWarpGrottoToCustomScene(char* sceneName, SceneAPI_Exit exit, f32 x, f32 y, f32 z));

#define SCENE_HEADER(scenePrefix) scenePrefix##_scene_header00
#define ROOM_HEADER(scenePrefix, roomNumber) scenePrefix##_room_##roomNumber##_header00


#define DUMMY_SEGMENT(scene, roomNumber) u8 _##scene##_room_##roomNumber##SegmentRomStart[1]; u8 _##scene##_room_##roomNumber##SegmentRomEnd[1];
#define THIRTY_DUMMY_SEGMENTS(scene) \
DUMMY_SEGMENT(scene, 0) \
DUMMY_SEGMENT(scene, 1) \
DUMMY_SEGMENT(scene, 2) \
DUMMY_SEGMENT(scene, 3) \
DUMMY_SEGMENT(scene, 4) \
DUMMY_SEGMENT(scene, 5) \
DUMMY_SEGMENT(scene, 6) \
DUMMY_SEGMENT(scene, 7) \
DUMMY_SEGMENT(scene, 8) \
DUMMY_SEGMENT(scene, 9) \
DUMMY_SEGMENT(scene, 10) \
DUMMY_SEGMENT(scene, 11) \
DUMMY_SEGMENT(scene, 12) \
DUMMY_SEGMENT(scene, 13) \
DUMMY_SEGMENT(scene, 14) \
DUMMY_SEGMENT(scene, 15) \
DUMMY_SEGMENT(scene, 16) \
DUMMY_SEGMENT(scene, 17) \
DUMMY_SEGMENT(scene, 18) \
DUMMY_SEGMENT(scene, 19) \
DUMMY_SEGMENT(scene, 20) \
DUMMY_SEGMENT(scene, 21) \
DUMMY_SEGMENT(scene, 22) \
DUMMY_SEGMENT(scene, 23) \
DUMMY_SEGMENT(scene, 24) \
DUMMY_SEGMENT(scene, 25) \
DUMMY_SEGMENT(scene, 26) \
DUMMY_SEGMENT(scene, 27) \
DUMMY_SEGMENT(scene, 28) \
DUMMY_SEGMENT(scene, 29) \
DUMMY_SEGMENT(scene, 30)

#endif /* SCENE_API_HEADER_H */