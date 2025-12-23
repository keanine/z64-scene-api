#include "mm_test2_scene.h"

/**
 * Header Default
*/
#define LENGTH_MM_TEST2_ROOM_1_HEADER00_OBJECTLIST 3
SceneCmd mm_test2_room_1_header00[] = {
    SCENE_CMD_ROOM_SHAPE(&mm_test2_room_1_shapeHeader),
    SCENE_CMD_ECHO_SETTINGS(0x00),
    SCENE_CMD_ROOM_BEHAVIOR(ROOM_TYPE_DUNGEON, ROOM_ENV_DEFAULT, false, false, false, false),
    SCENE_CMD_SKYBOX_DISABLES(false, false),
    SCENE_CMD_TIME_SETTINGS(255, 255, 10),
    SCENE_CMD_OBJECT_LIST(LENGTH_MM_TEST2_ROOM_1_HEADER00_OBJECTLIST, mm_test2_room_1_header00_objectList),
    SCENE_CMD_END(),
};

s16 mm_test2_room_1_header00_objectList[LENGTH_MM_TEST2_ROOM_1_HEADER00_OBJECTLIST] = {
    OBJECT_ST,
    OBJECT_BOX,
    OBJECT_BDOOR,
};

RoomShapeNormal mm_test2_room_1_shapeHeader = {
    ROOM_SHAPE_TYPE_NORMAL,
    ARRAY_COUNT(mm_test2_room_1_shapeDListsEntry),
    mm_test2_room_1_shapeDListsEntry,
    mm_test2_room_1_shapeDListsEntry + ARRAY_COUNT(mm_test2_room_1_shapeDListsEntry)
};

RoomShapeDListsEntry mm_test2_room_1_shapeDListsEntry[1] = {
    { mm_test2_room_1_shapeHeader_entry_0_opaque, NULL }
};

Gfx mm_test2_room_1_shapeHeader_entry_0_opaque[] = {
	gsSPDisplayList(mm_test2_room_1_dl_Exit_Cube_mesh_layer_Opaque),
	gsSPDisplayList(mm_test2_room_1_dl_Exit_Cube_001_mesh_layer_Opaque),
	gsSPDisplayList(mm_test2_room_1_dl_Plane_001_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

Vtx mm_test2_room_1_dl_Exit_Cube_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {736, -517, 103}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {736, -301, 103}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {736, -301, -87}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {736, -517, -87}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {952, -517, 103}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {952, -301, 103}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {952, -301, -87}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {952, -517, -87}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx mm_test2_room_1_dl_Exit_Cube_mesh_layer_Opaque_vtx_0[24] = {
	{{ {924, -301, -87}, 0, {368, 1008}, {126, 19, 0, 255} }},
	{{ {924, -301, 103}, 0, {368, 752}, {126, 19, 0, 255} }},
	{{ {952, -489, 103}, 0, {624, 752}, {126, 19, 0, 255} }},
	{{ {952, -489, -87}, 0, {624, 1008}, {126, 19, 0, 255} }},
	{{ {924, -301, 103}, 0, {368, 752}, {0, 0, 127, 255} }},
	{{ {736, -329, 103}, 0, {368, 496}, {0, 0, 127, 255} }},
	{{ {764, -517, 103}, 0, {624, 496}, {0, 0, 127, 255} }},
	{{ {952, -489, 103}, 0, {624, 752}, {0, 0, 127, 255} }},
	{{ {736, -329, 103}, 0, {368, 496}, {130, 237, 0, 255} }},
	{{ {736, -329, -87}, 0, {368, 240}, {130, 237, 0, 255} }},
	{{ {764, -517, -87}, 0, {624, 240}, {130, 237, 0, 255} }},
	{{ {764, -517, 103}, 0, {624, 496}, {130, 237, 0, 255} }},
	{{ {736, -329, -87}, 0, {368, 240}, {0, 0, 129, 255} }},
	{{ {924, -301, -87}, 0, {368, -16}, {0, 0, 129, 255} }},
	{{ {952, -489, -87}, 0, {624, -16}, {0, 0, 129, 255} }},
	{{ {764, -517, -87}, 0, {624, 240}, {0, 0, 129, 255} }},
	{{ {924, -301, 103}, 0, {112, 496}, {237, 126, 0, 255} }},
	{{ {924, -301, -87}, 0, {112, 240}, {237, 126, 0, 255} }},
	{{ {736, -329, -87}, 0, {368, 240}, {237, 126, 0, 255} }},
	{{ {736, -329, 103}, 0, {368, 496}, {237, 126, 0, 255} }},
	{{ {764, -517, 103}, 0, {624, 496}, {19, 130, 0, 255} }},
	{{ {764, -517, -87}, 0, {624, 240}, {19, 130, 0, 255} }},
	{{ {952, -489, -87}, 0, {880, 240}, {19, 130, 0, 255} }},
	{{ {952, -489, 103}, 0, {880, 496}, {19, 130, 0, 255} }},
};

Gfx mm_test2_room_1_dl_Exit_Cube_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(mm_test2_room_1_dl_Exit_Cube_mesh_layer_Opaque_vtx_0 + 0, 24, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSPEndDisplayList(),
};

Vtx mm_test2_room_1_dl_Exit_Cube_001_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {736, -517, 328}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {736, -301, 328}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {736, -301, 138}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {736, -517, 138}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {952, -517, 328}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {952, -301, 328}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {952, -301, 138}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {952, -517, 138}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx mm_test2_room_1_dl_Exit_Cube_001_mesh_layer_Opaque_vtx_0[24] = {
	{{ {924, -301, 138}, 0, {368, 1008}, {126, 19, 0, 255} }},
	{{ {924, -301, 328}, 0, {368, 752}, {126, 19, 0, 255} }},
	{{ {952, -489, 328}, 0, {624, 752}, {126, 19, 0, 255} }},
	{{ {952, -489, 138}, 0, {624, 1008}, {126, 19, 0, 255} }},
	{{ {924, -301, 328}, 0, {368, 752}, {0, 0, 127, 255} }},
	{{ {736, -329, 328}, 0, {368, 496}, {0, 0, 127, 255} }},
	{{ {764, -517, 328}, 0, {624, 496}, {0, 0, 127, 255} }},
	{{ {952, -489, 328}, 0, {624, 752}, {0, 0, 127, 255} }},
	{{ {736, -329, 328}, 0, {368, 496}, {130, 237, 0, 255} }},
	{{ {736, -329, 138}, 0, {368, 240}, {130, 237, 0, 255} }},
	{{ {764, -517, 138}, 0, {624, 240}, {130, 237, 0, 255} }},
	{{ {764, -517, 328}, 0, {624, 496}, {130, 237, 0, 255} }},
	{{ {736, -329, 138}, 0, {368, 240}, {0, 0, 129, 255} }},
	{{ {924, -301, 138}, 0, {368, -16}, {0, 0, 129, 255} }},
	{{ {952, -489, 138}, 0, {624, -16}, {0, 0, 129, 255} }},
	{{ {764, -517, 138}, 0, {624, 240}, {0, 0, 129, 255} }},
	{{ {924, -301, 328}, 0, {112, 496}, {237, 126, 0, 255} }},
	{{ {924, -301, 138}, 0, {112, 240}, {237, 126, 0, 255} }},
	{{ {736, -329, 138}, 0, {368, 240}, {237, 126, 0, 255} }},
	{{ {736, -329, 328}, 0, {368, 496}, {237, 126, 0, 255} }},
	{{ {764, -517, 328}, 0, {624, 496}, {19, 130, 0, 255} }},
	{{ {764, -517, 138}, 0, {624, 240}, {19, 130, 0, 255} }},
	{{ {952, -489, 138}, 0, {880, 240}, {19, 130, 0, 255} }},
	{{ {952, -489, 328}, 0, {880, 496}, {19, 130, 0, 255} }},
};

Gfx mm_test2_room_1_dl_Exit_Cube_001_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(mm_test2_room_1_dl_Exit_Cube_001_mesh_layer_Opaque_vtx_0 + 0, 24, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSPEndDisplayList(),
};

Vtx mm_test2_room_1_dl_Plane_001_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {508, -325, 391}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {508, -325, 391}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {508, -325, -603}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {508, -325, -603}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1502, -325, 391}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1502, -325, 391}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1502, -325, -603}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1502, -325, -603}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx mm_test2_room_1_dl_Plane_001_mesh_layer_Opaque_vtx_0[4] = {
	{{ {508, -325, 391}, 0, {0, 512}, {0, 127, 0, 255} }},
	{{ {1502, -325, 391}, 0, {512, 512}, {0, 127, 0, 255} }},
	{{ {1502, -325, -603}, 0, {512, 0}, {0, 127, 0, 255} }},
	{{ {508, -325, -603}, 0, {0, 0}, {0, 127, 0, 255} }},
};

Gfx mm_test2_room_1_dl_Plane_001_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(mm_test2_room_1_dl_Plane_001_mesh_layer_Opaque_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_mm_test2_room_1_dl_exit1_layerOpaque[] = {
	gsSPLoadGeometryMode(G_SHADE | G_FOG | G_CULL_BACK | G_LIGHTING | G_ZBUFFER | G_SHADING_SMOOTH),
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_TD_CLAMP | G_TT_NONE | G_TC_FILT | G_TP_PERSP | G_TF_BILERP | G_CD_MAGICSQ | G_TL_TILE | G_PM_NPRIMITIVE | G_CYC_2CYCLE | G_AD_NOISE | G_CK_NONE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_mm_test2_room_1_dl_exit1_layerOpaque[] = {
	gsDPPipeSync(),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_OPA_SURF2 | G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_OPA_SURF),
	gsSPEndDisplayList(),
};

Gfx mat_mm_test2_room_1_dl_exit2_layerOpaque[] = {
	gsSPLoadGeometryMode(G_SHADE | G_FOG | G_CULL_BACK | G_LIGHTING | G_ZBUFFER | G_SHADING_SMOOTH),
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_TD_CLAMP | G_TT_NONE | G_TC_FILT | G_TP_PERSP | G_TF_BILERP | G_CD_MAGICSQ | G_TL_TILE | G_PM_NPRIMITIVE | G_CYC_2CYCLE | G_AD_NOISE | G_CK_NONE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 159, 251, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_mm_test2_room_1_dl_exit2_layerOpaque[] = {
	gsDPPipeSync(),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_OPA_SURF2 | G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_OPA_SURF),
	gsSPEndDisplayList(),
};

Gfx mm_test2_room_1_dl_Exit_Cube_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(mm_test2_room_1_dl_Exit_Cube_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_mm_test2_room_1_dl_exit1_layerOpaque),
	gsSPDisplayList(mm_test2_room_1_dl_Exit_Cube_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_revert_mm_test2_room_1_dl_exit1_layerOpaque),
	gsSPEndDisplayList(),
};

Gfx mm_test2_room_1_dl_Exit_Cube_001_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(mm_test2_room_1_dl_Exit_Cube_001_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_mm_test2_room_1_dl_exit2_layerOpaque),
	gsSPDisplayList(mm_test2_room_1_dl_Exit_Cube_001_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_revert_mm_test2_room_1_dl_exit2_layerOpaque),
	gsSPEndDisplayList(),
};

Gfx mm_test2_room_1_dl_Plane_001_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(mm_test2_room_1_dl_Plane_001_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_mm_test2_room_0_dl_bedrock_001_f3d_layerOpaque),
	gsSPDisplayList(mm_test2_room_1_dl_Plane_001_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_revert_mm_test2_room_0_dl_bedrock_001_f3d_layerOpaque),
	gsSPEndDisplayList(),
};

