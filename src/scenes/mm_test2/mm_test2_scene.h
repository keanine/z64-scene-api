#ifndef MM_TEST2_SCENE_H
#define MM_TEST2_SCENE_H

#include "ultra64.h"
#include "macros.h"
#include "z64.h"
#include "command_macros_base.h"
#include "../../scene_api.h"

extern SceneCmd mm_test2_scene_header00[];
extern RomFile mm_test2_scene_roomList[];
extern u8 _mm_test2_room_0SegmentRomStart[];
extern u8 _mm_test2_room_0SegmentRomEnd[];
extern u8 _mm_test2_room_1SegmentRomStart[];
extern u8 _mm_test2_room_1SegmentRomEnd[];
extern ActorEntry mm_test2_scene_header00_playerEntryList[];
extern EntranceEntry mm_test2_scene_header00_entranceList[];
extern TransitionActorEntry mm_test2_scene_header00_transitionActors[];
extern EnvLightSettings mm_test2_scene_header00_lightSettings[1];
extern AnimatedMatTexScrollParams mm_test2_scene_header00_AnimatedMaterialTexScrollParams_00[];
extern AnimatedMatTexScrollParams mm_test2_scene_header00_AnimatedMaterialTexScrollParams_01[];
extern F3DPrimColor mm_test2_scene_header00_AnimatedMaterialColorPrimColor_02[];
extern F3DEnvColor mm_test2_scene_header00_AnimatedMaterialColorEnvColor_02[];
extern u16 mm_test2_scene_header00_AnimatedMaterialColorKeyFrames_02[];
extern AnimatedMatColorParams mm_test2_scene_header00_AnimatedMaterialColorParams_02;
extern AnimatedMaterial mm_test2_scene_header00_AnimatedMaterial[];extern Vec3s mm_test2_scene_header00_ActorCutsceneCameraData[];
extern ActorCsCamInfo mm_test2_scene_header00_ActorCutsceneCameraInfo[];
extern CutsceneEntry mm_test2_scene_header00_ActorCutsceneList[];
extern BgCamInfo mm_test2_scene_bgCamInfo[];
extern SurfaceType mm_test2_scene_polygonTypes[3];
extern Vec3s mm_test2_scene_vertices[40];
extern CollisionPoly mm_test2_scene_polygons[52];
extern CollisionHeader mm_test2_scene_collisionHeader;
extern u64 mm_test2_room_0_dl_bedrock_i8[];
extern Gfx mat_mm_test2_room_0_dl_bedrock_001_f3d_layerOpaque[];
extern Gfx mat_revert_mm_test2_room_0_dl_bedrock_001_f3d_layerOpaque[];
extern SceneCmd mm_test2_room_0_header00[];
extern s16 mm_test2_room_0_header00_objectList[];
extern Gfx mm_test2_room_0_shapeHeader_entry_0_opaque[];
extern u64 mm_test2_room_0_dl_grass_block_top_y_ci8[];
extern u64 mm_test2_room_0_dl_grass_block_top_y_pal_rgba16[];
extern Vtx mm_test2_room_0_dl_Cube_mesh_layer_Opaque_vtx_cull[8];
extern Vtx mm_test2_room_0_dl_Cube_mesh_layer_Opaque_vtx_0[24];
extern Gfx mm_test2_room_0_dl_Cube_mesh_layer_Opaque_tri_0[];
extern Vtx mm_test2_room_0_dl_Plane_mesh_layer_Opaque_vtx_cull[8];
extern Vtx mm_test2_room_0_dl_Plane_mesh_layer_Opaque_vtx_0[4];
extern Gfx mm_test2_room_0_dl_Plane_mesh_layer_Opaque_tri_0[];
extern Gfx mat_mm_test2_room_0_dl_grass_block_top_001_f3d_layerOpaque[];
extern Gfx mat_revert_mm_test2_room_0_dl_grass_block_top_001_f3d_layerOpaque[];
extern Gfx mm_test2_room_0_dl_Cube_mesh_layer_Opaque[];
extern Gfx mm_test2_room_0_dl_Plane_mesh_layer_Opaque[];
extern RoomShapeNormal mm_test2_room_0_shapeHeader;
extern RoomShapeDListsEntry mm_test2_room_0_shapeDListsEntry[1];
extern SceneCmd mm_test2_room_1_header00[];
extern s16 mm_test2_room_1_header00_objectList[];
extern Gfx mm_test2_room_1_shapeHeader_entry_0_opaque[];
extern Vtx mm_test2_room_1_dl_Exit_Cube_mesh_layer_Opaque_vtx_cull[8];
extern Vtx mm_test2_room_1_dl_Exit_Cube_mesh_layer_Opaque_vtx_0[24];
extern Gfx mm_test2_room_1_dl_Exit_Cube_mesh_layer_Opaque_tri_0[];
extern Vtx mm_test2_room_1_dl_Exit_Cube_001_mesh_layer_Opaque_vtx_cull[8];
extern Vtx mm_test2_room_1_dl_Exit_Cube_001_mesh_layer_Opaque_vtx_0[24];
extern Gfx mm_test2_room_1_dl_Exit_Cube_001_mesh_layer_Opaque_tri_0[];
extern Vtx mm_test2_room_1_dl_Plane_001_mesh_layer_Opaque_vtx_cull[8];
extern Vtx mm_test2_room_1_dl_Plane_001_mesh_layer_Opaque_vtx_0[4];
extern Gfx mm_test2_room_1_dl_Plane_001_mesh_layer_Opaque_tri_0[];
extern Gfx mat_mm_test2_room_1_dl_exit1_layerOpaque[];
extern Gfx mat_revert_mm_test2_room_1_dl_exit1_layerOpaque[];
extern Gfx mat_mm_test2_room_1_dl_exit2_layerOpaque[];
extern Gfx mat_revert_mm_test2_room_1_dl_exit2_layerOpaque[];
extern Gfx mm_test2_room_1_dl_Exit_Cube_mesh_layer_Opaque[];
extern Gfx mm_test2_room_1_dl_Exit_Cube_001_mesh_layer_Opaque[];
extern Gfx mm_test2_room_1_dl_Plane_001_mesh_layer_Opaque[];
extern RoomShapeNormal mm_test2_room_1_shapeHeader;
extern RoomShapeDListsEntry mm_test2_room_1_shapeDListsEntry[1];
extern u16 mm_test2_scene_header00_exitList[];

#endif
