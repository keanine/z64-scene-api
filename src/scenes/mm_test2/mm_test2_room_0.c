#include "mm_test2_scene.h"

/**
 * Header Default
*/
#define LENGTH_MM_TEST2_ROOM_0_HEADER00_OBJECTLIST 3
SceneCmd mm_test2_room_0_header00[] = {
    SCENE_CMD_ROOM_SHAPE(&mm_test2_room_0_shapeHeader),
    SCENE_CMD_ECHO_SETTINGS(0x00),
    SCENE_CMD_ROOM_BEHAVIOR(ROOM_TYPE_DUNGEON, ROOM_ENV_DEFAULT, false, false, false, false),
    SCENE_CMD_SKYBOX_DISABLES(false, false),
    SCENE_CMD_TIME_SETTINGS(255, 255, 10),
    SCENE_CMD_OBJECT_LIST(LENGTH_MM_TEST2_ROOM_0_HEADER00_OBJECTLIST, mm_test2_room_0_header00_objectList),
    SCENE_CMD_END(),
};

s16 mm_test2_room_0_header00_objectList[LENGTH_MM_TEST2_ROOM_0_HEADER00_OBJECTLIST] = {
    OBJECT_ST,
    OBJECT_BOX,
    OBJECT_BDOOR,
};

RoomShapeNormal mm_test2_room_0_shapeHeader = {
    ROOM_SHAPE_TYPE_NORMAL,
    ARRAY_COUNT(mm_test2_room_0_shapeDListsEntry),
    mm_test2_room_0_shapeDListsEntry,
    mm_test2_room_0_shapeDListsEntry + ARRAY_COUNT(mm_test2_room_0_shapeDListsEntry)
};

RoomShapeDListsEntry mm_test2_room_0_shapeDListsEntry[1] = {
    { mm_test2_room_0_shapeHeader_entry_0_opaque, NULL }
};

Gfx mm_test2_room_0_shapeHeader_entry_0_opaque[] = {
	gsSPDisplayList(mm_test2_room_0_dl_Cube_mesh_layer_Opaque),
	gsSPDisplayList(mm_test2_room_0_dl_Plane_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

u64 mm_test2_room_0_dl_grass_block_top_y_ci8[] = {
	0x0001000202030405, 0x0600050207080903, 0x000506000a040a02, 0x0408080001050205, 0x0b03040207020303, 0x0006080c020d040e, 0x0f020500030a0400, 0x0402030003050804, 
	0x06020c020c10020c, 0x110f04080c040203, 0x0a000d0804000006, 0x020002020d020300, 0x0406080300020504, 0x02020e0c03080003, 0x0302060503040802, 0x000c020403060408, 
	0x08060e080c040c06, 0x0e08020002000604, 0x00020e0305000804, 0x02030008030e0304, 0x06060008020e0300, 0x0104080203020003, 0x020c020b00020007, 0x000005040e040405, 
	0x110004050a030204, 0x0503050406080400, 0x04080f00040a0401, 0x0600080606020810, 0x0b0601040e0c0000, 0x0400000208060504, 0x0200020708000000, 0x0312040802030206, 
	
};

u64 mm_test2_room_0_dl_grass_block_top_y_pal_rgba16[] = {
	0x6c918dd7640f6c51, 0x5bcf645174d36411, 0x7d13534d74917513, 0x7d535b8f8595538d, 0x7d558d958dd50000
};

Vtx mm_test2_room_0_dl_Cube_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {-149, -290, 216}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-149, -205, 216}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-149, -205, 130}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-149, -290, 130}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-63, -290, 216}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-63, -205, 216}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-63, -205, 130}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-63, -290, 130}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx mm_test2_room_0_dl_Cube_mesh_layer_Opaque_vtx_0[24] = {
	{{ {-149, -290, 216}, 0, {192, 512}, {129, 0, 0, 255} }},
	{{ {-149, -205, 216}, 0, {320, 512}, {129, 0, 0, 255} }},
	{{ {-149, -205, 130}, 0, {320, 384}, {129, 0, 0, 255} }},
	{{ {-149, -290, 130}, 0, {192, 384}, {129, 0, 0, 255} }},
	{{ {-149, -290, 130}, 0, {192, 384}, {0, 0, 129, 255} }},
	{{ {-149, -205, 130}, 0, {320, 384}, {0, 0, 129, 255} }},
	{{ {-63, -205, 130}, 0, {320, 256}, {0, 0, 129, 255} }},
	{{ {-63, -290, 130}, 0, {192, 256}, {0, 0, 129, 255} }},
	{{ {-63, -290, 130}, 0, {192, 256}, {127, 0, 0, 255} }},
	{{ {-63, -205, 130}, 0, {320, 256}, {127, 0, 0, 255} }},
	{{ {-63, -205, 216}, 0, {320, 128}, {127, 0, 0, 255} }},
	{{ {-63, -290, 216}, 0, {192, 128}, {127, 0, 0, 255} }},
	{{ {-63, -290, 216}, 0, {192, 128}, {0, 0, 127, 255} }},
	{{ {-63, -205, 216}, 0, {320, 128}, {0, 0, 127, 255} }},
	{{ {-149, -205, 216}, 0, {320, 0}, {0, 0, 127, 255} }},
	{{ {-149, -290, 216}, 0, {192, 0}, {0, 0, 127, 255} }},
	{{ {-149, -290, 130}, 0, {64, 256}, {0, 129, 0, 255} }},
	{{ {-63, -290, 130}, 0, {192, 256}, {0, 129, 0, 255} }},
	{{ {-63, -290, 216}, 0, {192, 128}, {0, 129, 0, 255} }},
	{{ {-149, -290, 216}, 0, {64, 128}, {0, 129, 0, 255} }},
	{{ {-63, -205, 130}, 0, {320, 256}, {0, 127, 0, 255} }},
	{{ {-149, -205, 130}, 0, {448, 256}, {0, 127, 0, 255} }},
	{{ {-149, -205, 216}, 0, {448, 128}, {0, 127, 0, 255} }},
	{{ {-63, -205, 216}, 0, {320, 128}, {0, 127, 0, 255} }},
};

Gfx mm_test2_room_0_dl_Cube_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(mm_test2_room_0_dl_Cube_mesh_layer_Opaque_vtx_0 + 0, 24, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSPEndDisplayList(),
};

Vtx mm_test2_room_0_dl_Plane_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {-532, -325, 429}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-532, -325, 429}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-532, -325, -636}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-532, -325, -636}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {532, -325, 429}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {532, -325, 429}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {532, -325, -636}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {532, -325, -636}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx mm_test2_room_0_dl_Plane_mesh_layer_Opaque_vtx_0[4] = {
	{{ {-532, -325, 429}, 0, {0, 512}, {0, 127, 0, 255} }},
	{{ {532, -325, 429}, 0, {512, 512}, {0, 127, 0, 255} }},
	{{ {532, -325, -636}, 0, {512, 0}, {0, 127, 0, 255} }},
	{{ {-532, -325, -636}, 0, {0, 0}, {0, 127, 0, 255} }},
};

Gfx mm_test2_room_0_dl_Plane_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(mm_test2_room_0_dl_Plane_mesh_layer_Opaque_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_mm_test2_room_0_dl_grass_block_top_001_f3d_layerOpaque[] = {
	gsSPLoadGeometryMode(G_SHADE | G_FOG | G_CULL_BACK | G_LIGHTING | G_ZBUFFER | G_SHADING_SMOOTH),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_TD_CLAMP | G_TC_FILT | G_TP_PERSP | G_TF_POINT | G_TT_RGBA16 | G_CD_MAGICSQ | G_TL_TILE | G_PM_NPRIMITIVE | G_CYC_2CYCLE | G_AD_NOISE | G_CK_NONE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mm_test2_room_0_dl_grass_block_top_y_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 18),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, mm_test2_room_0_dl_grass_block_top_y_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 127, 1024),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 2, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 60),
	gsSPEndDisplayList(),
};

Gfx mat_revert_mm_test2_room_0_dl_grass_block_top_001_f3d_layerOpaque[] = {
	gsDPPipeSync(),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_OPA_SURF2 | G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_OPA_SURF),
	gsSPEndDisplayList(),
};

Gfx mm_test2_room_0_dl_Cube_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(mm_test2_room_0_dl_Cube_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_mm_test2_room_0_dl_bedrock_001_f3d_layerOpaque),
	gsSPDisplayList(mm_test2_room_0_dl_Cube_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_revert_mm_test2_room_0_dl_bedrock_001_f3d_layerOpaque),
	gsSPEndDisplayList(),
};

Gfx mm_test2_room_0_dl_Plane_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(mm_test2_room_0_dl_Plane_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_mm_test2_room_0_dl_grass_block_top_001_f3d_layerOpaque),
	gsSPDisplayList(mm_test2_room_0_dl_Plane_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_revert_mm_test2_room_0_dl_grass_block_top_001_f3d_layerOpaque),
	gsSPEndDisplayList(),
};

