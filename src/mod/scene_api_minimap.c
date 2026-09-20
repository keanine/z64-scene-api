#include "scene_api_minimap.h"
#include "code/gDPLoadTextureBlock_Runtime.inc.c"

extern s32 MapDisp_AreRoomsSameStorey(s32 curRoom, s32 prevRoom);
extern void MapDisp_Minimap_DrawDoorActors(PlayState* play);
extern void MapDisp_Minimap_DrawRedCompassIcon(PlayState* play, s32 x, s32 z, s32 rot);
extern void MapDisp_Minimap_DrawActors(PlayState* play);
extern void MapDisp_DrawMinimapRoom(PlayState* play, TexturePtr texture, s32 x, s32 y, s32 room, f32 intensity);
extern s32 MapDisp_CanDisplayMinimap(PlayState* play);
extern s32 MapDisp_IsLocationMinimapBlocked(PlayState* play);
extern f32 MapDisp_GetStoreyY(f32 checkY);
extern s32 MapDisp_IsLocationRomaniRanchAltScene(PlayState* play);

extern MapDisp sMapDisp;
extern s32 sSceneNumRooms;
extern u64 sWhiteSquareTex[];
extern Gfx gCompassArrowDL[];
extern u64 gMapChestIconTex[];
extern Color_RGBA8 sMinimapActorCategoryColors[12];

extern MapDataRoom sMapDataRooms[ROOM_MAX];

extern void MapDisp_InitBossRoomStorey(PlayState* play);
extern void MapDisp_InitSceneFloorData(PlayState* play);
extern MapDataScene sMapDataScene;
extern MapDataRoom sMapDataRooms[ROOM_MAX];
RECOMP_PATCH void MapDisp_InitMapData(PlayState* play, void* segmentAddress) {
    MapDataScene* mapDataScene;
    MapDataRoom* mapDataRooms;
    s32 i;

    // recomp_printf("Name: %s\n", SceneAPI_GetSceneNameById(sceneAPI_customSceneId));
    recomp_printf("play->sceneId: %d\n", play->sceneId);

    if (/*!Map_IsInBossScene(play) && */play->sceneId == SCENEAPI_SCENE) {
        sSceneNumRooms = play->roomList.count;
        mapDataScene = Lib_SegmentedToVirtual(segmentAddress);
        sMapDataScene = *mapDataScene;
        sMapDisp.mapDataScene = &sMapDataScene;

        LoadCustomMinimap(&sceneAPI_customScenes[sceneAPI_customSceneId].minimap);

        if (play->colCtx.colHeader != NULL) {
            sMapDisp.sceneMinX = play->colCtx.colHeader->minBounds.x;
            sMapDisp.sceneMinZ = play->colCtx.colHeader->minBounds.z;
            sMapDisp.sceneWidth = play->colCtx.colHeader->maxBounds.x - play->colCtx.colHeader->minBounds.x;
            sMapDisp.sceneHeight = play->colCtx.colHeader->maxBounds.z - play->colCtx.colHeader->minBounds.z;
            sMapDisp.sceneMidX = sMapDisp.sceneMinX + (sMapDisp.sceneWidth * 0.5f);
            sMapDisp.sceneMidZ = sMapDisp.sceneMinZ + (sMapDisp.sceneHeight * 0.5f);
        }
    }
    else if (!Map_IsInBossScene(play)) {
        sSceneNumRooms = play->roomList.count;
        mapDataScene = Lib_SegmentedToVirtual(segmentAddress);
        sMapDataScene = *mapDataScene;
        mapDataRooms = Lib_SegmentedToVirtual(mapDataScene->rooms);

        for (i = 0; i < sSceneNumRooms; i++) {
            sMapDataRooms[i] = *mapDataRooms++;
        }

        sMapDataScene.rooms = sMapDataRooms;
        if (play->colCtx.colHeader != NULL) {
            sMapDisp.sceneMinX = play->colCtx.colHeader->minBounds.x;
            sMapDisp.sceneMinZ = play->colCtx.colHeader->minBounds.z;
            sMapDisp.sceneWidth = play->colCtx.colHeader->maxBounds.x - play->colCtx.colHeader->minBounds.x;
            sMapDisp.sceneHeight = play->colCtx.colHeader->maxBounds.z - play->colCtx.colHeader->minBounds.z;
            sMapDisp.sceneMidX = sMapDisp.sceneMinX + (sMapDisp.sceneWidth * 0.5f);
            sMapDisp.sceneMidZ = sMapDisp.sceneMinZ + (sMapDisp.sceneHeight * 0.5f);
        }
    }
    sMapDisp.mapDataScene = &sMapDataScene;
    MapDisp_InitSceneFloorData(play);
    MapDisp_InitBossRoomStorey(play);
}

void PrintMapDisp() {
    recomp_printf("\n");
    recomp_printf("== NEW SCENE LOADED ==\n");

    // sMapDisp.mapDataScene;
    recomp_printf("curRoom: %d\n", sMapDisp.curRoom);
    recomp_printf("minimapBaseX: %d\n", sMapDisp.minimapBaseX);
    recomp_printf("minimapBaseY: %d\n", sMapDisp.minimapBaseY);
    recomp_printf("minimapCurX: %d\n", sMapDisp.minimapCurX);
    recomp_printf("minimapCurY: %d\n", sMapDisp.minimapCurY);
    // sMapDisp.minimapCurTex; // gameplay cur minimap room
    recomp_printf("prevRoom: %d\n", sMapDisp.prevRoom);
    // sMapDisp.minimapPrevTex;
    recomp_printf("minimapPrevX: %d\n", sMapDisp.minimapPrevX); // for room swap animation
    recomp_printf("minimapPrevY: %d\n", sMapDisp.minimapPrevY); // for room swap animation
    recomp_printf("unk20: %d\n", sMapDisp.unk20);
    recomp_printf("swapAnimTimer: %d\n", sMapDisp.swapAnimTimer);
    // sMapDisp.texBuff0;
    // sMapDisp.texBuff1;
    recomp_printf("sceneMinX: %d\n", sMapDisp.sceneMinX); //scene minBounds.x
    recomp_printf("sceneMinZ: %d\n", sMapDisp.sceneMinZ); //scene minBounds.z
    recomp_printf("sceneWidth: %d\n", sMapDisp.sceneWidth); //scene boundsWidth.x
    recomp_printf("sceneHeight: %d\n", sMapDisp.sceneHeight); //scene boundsWidth.z
    recomp_printf("sceneMidX: %d\n", sMapDisp.sceneMidX); //scene boundsMidpoint.x
    recomp_printf("sceneMidZ: %d\n", sMapDisp.sceneMidZ); //scene boundsMidpoint.z
    // sMapDisp.roomStoreyList; // list of lowest storey each room crosses
    recomp_printf("numStoreys: %d\n", sMapDisp.numStoreys); // number of distinct storeys
    recomp_printf("pauseMapCurStorey: %d\n", sMapDisp.pauseMapCurStorey);
    recomp_printf("bottomStorey: %d\n", sMapDisp.bottomStorey); // configures what storey 0 is displayed as
    // sMapDisp.storeyYList; // list of min Ys for each storey
    recomp_printf("timer: %d\n", sMapDisp.timer);
    recomp_printf("numChests: %d\n", sMapDisp.numChests);
    // sMapDisp.mapDataChests;
    recomp_printf("bossRoomStorey: %d\n", sMapDisp.bossRoomStorey);
    recomp_printf("unk5A: %d\n", sMapDisp.unk5A);
}

RECOMP_HOOK("MapDisp_SwapRooms") void on_MapDisp_SwapRooms(s16 nextRoom) {
}
RECOMP_HOOK_RETURN("MapDisp_SwapRooms") void return_MapDisp_SwapRooms() {
    if (SceneAPI_IsCustomScene()) {
        SceneAPI_Minimap* minimap = &sceneAPI_customScenes[sceneAPI_customSceneId].minimap;
        sMapDisp.minimapCurTex = minimap->rooms[sMapDisp.curRoom].texture;
    }
}

void LoadCustomMinimap(SceneAPI_Minimap* minimap) {
    // MapDataScene* mapDataScene;
    // recomp_printf("minimap->scale: %d\n", minimap->scale)
    recomp_printf("Load\n");
    sMapDisp.mapDataScene->scale = minimap->scale;
    for (int i = 0; i < ROOM_MAX; i++) {
        if (minimap->rooms[i].isValid) {
            sMapDisp.mapDataScene->rooms[i].mapId = 0x0106;
            sMapDisp.mapDataScene->rooms[i].centerX = 0;
            // sMapDisp.mapDataScene->rooms[i].floorY = minimap->rooms[i].floor;
            sMapDisp.mapDataScene->rooms[i].floorY = 0;
            sMapDisp.mapDataScene->rooms[i].centerZ = 0;
            sMapDisp.mapDataScene->rooms[i].flags = 0x0;
        }
    }
    // recomp_printf("Load Finish\n");
}

extern void MapDisp_InitMapI(PlayState* play);
extern void MapDisp_InitRoomStoreyRecord(PlayState* play, s16* roomStorey);
extern void MapDisp_AwaitGameplayDangeonKeep(PlayState* play);
RECOMP_PATCH void MapDisp_Init(PlayState* play) {
    s32 i;

    sMapDisp.mapDataScene = NULL;
    sMapDisp.curRoom = -1;
    sMapDisp.minimapBaseX = 210;
    sMapDisp.minimapBaseY = 140;
    sMapDisp.minimapCurX = 210;
    sMapDisp.minimapCurY = 140;
    sMapDisp.minimapCurTex = NULL;
    sMapDisp.prevRoom = -1;
    sMapDisp.minimapPrevTex = NULL;
    sMapDisp.minimapPrevX = 0;
    sMapDisp.minimapPrevY = 0;
    sMapDisp.unk20 = 0;
    sMapDisp.swapAnimTimer = 0;

    recomp_printf("play->roomList.count: %d\n", play->roomList.count);
    if (!Map_IsInBossScene(play)) {
        sSceneNumRooms = play->roomList.count;
    }
    sMapDisp.texBuff0 = THA_AllocTailAlign16(&play->state.tha, 0x4000);
    sMapDisp.texBuff1 = THA_AllocTailAlign16(&play->state.tha, 0x4000);
    MapDisp_AwaitGameplayDangeonKeep(play);
    if (!Map_IsInBossScene(play)) {
        sMapDisp.sceneMinX = 0;
        sMapDisp.sceneMinZ = 0;
        sMapDisp.sceneWidth = 100;
        sMapDisp.sceneHeight = 100;
        sMapDisp.sceneMidX = TRUNCF_BINANG((f32)sMapDisp.sceneMinX + ((f32)sMapDisp.sceneWidth * 0.5f));
        sMapDisp.sceneMidZ = TRUNCF_BINANG((f32)sMapDisp.sceneMinZ + ((f32)sMapDisp.sceneHeight * 0.5f));
    }
    sMapDisp.roomStoreyList = THA_AllocTailAlign16(&play->state.tha, sSceneNumRooms * sizeof(s16));

    for (i = 0; i < sSceneNumRooms; i++) {
        MapDisp_InitRoomStoreyRecord(play, &sMapDisp.roomStoreyList[i]);
    }
    sMapDisp.storeyYList = THA_AllocTailAlign16(&play->state.tha, ROOM_MAX * sizeof(s16));

    for (i = 0; i < ROOM_MAX; i++) {
        sMapDisp.storeyYList[i] = FLOOR_MIN_Y;
    }
    MapDisp_InitMapI(play);
    sMapDisp.bossRoomStorey = 0;
    sMapDisp.unk5A = 0;
    if (Map_IsInBossScene(play)) {
        MapDisp_InitMapData(play, NULL);
        MapDisp_InitChestData(play, 0, NULL);
    }
}


void DrawCustomActorIcon(PlayState* play, SceneAPI_Minimap* minimap, SceneAPI_MinimapRoom* roomData, Actor* actor) {
    // MapDataRoom* mapDataRoom;
    s32 posX;
    s32 posY;
    s32 texOffsetX;
    s32 texOffsetY;
    s32 texWidth;
    s32 texHeight;
    f32 scaleFrac;
    Player* player = GET_PLAYER(play);
    s32 scale;

    // MapDisp_GetMapTexDim(mapDataRoom, &texWidth, &texHeight);
    texWidth = roomData->texWidth;
    texHeight = roomData->texHeight;
    
    // MapDisp_GetMapOffset(mapDataRoom, &texOffsetX, &texOffsetY);
    texOffsetX = texWidth / 2;
    texOffsetY = texHeight / 2;

    scale = minimap->scale;
    if (minimap->scale == 0) {
        scale = 20;
    }

    s16 centerX = 0;
    s16 centerZ = 0;

    scaleFrac = 1.0f / scale;
    posX = (s32)((actor->world.pos.x - centerX) * scaleFrac) + sMapDisp.minimapBaseX +
            sMapDisp.minimapCurX - sMapDisp.minimapBaseX + texOffsetX;
    posY = (s32)((actor->world.pos.z - centerZ) * scaleFrac) + sMapDisp.minimapBaseY +
            sMapDisp.minimapCurY - sMapDisp.minimapBaseY + texOffsetY;

    if ((posX > 0) && (posX < 0x3FF) && (posY > 0) && (posY < 0x3FF)) {
        OPEN_DISPS(play->state.gfxCtx);

        if ((actor->category == ACTORCAT_PLAYER) && (actor->flags & ACTOR_FLAG_MINIMAP_ICON_ENABLED)) {
            s16 compassRot;

            Gfx_SetupDL42_Overlay(play->state.gfxCtx);
            gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                              PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
            gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, play->interfaceCtx.minimapAlpha);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
            gDPSetRenderMode(OVERLAY_DISP++, G_RM_AA_DEC_LINE, G_RM_NOOP2);

            Matrix_Translate(posX - 160.0f, 120.0f - posY, 0.0f, MTXMODE_NEW);
            Matrix_RotateXFApply(-1.6f);
            compassRot = (s32)(0x7FFF - actor->focus.rot.y) / 1024;
            Matrix_RotateYF(compassRot / 10.0f, MTXMODE_APPLY);
            Matrix_Scale(0.4f, 0.4f, 0.4f, MTXMODE_APPLY);
            MATRIX_FINALIZE_AND_LOAD(OVERLAY_DISP++, play->state.gfxCtx);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 200, 255, 0, play->interfaceCtx.minimapAlpha);
            gSPDisplayList(OVERLAY_DISP++, gCompassArrowDL);
        } else if ((actor->id == ACTOR_EN_BOX) && !Flags_GetTreasure(play, actor->params & 0x1F) /*&&
                   (MapDisp_GetStoreyY(player->actor.world.pos.y) == MapDisp_GetStoreyY(actor->world.pos.y))*/) {
            Gfx_SetupDL39_Overlay(play->state.gfxCtx);
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetTextureLUT(OVERLAY_DISP++, G_TT_NONE);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, play->interfaceCtx.minimapAlpha);
            gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, play->interfaceCtx.minimapAlpha);
            gDPPipeSync(OVERLAY_DISP++);

            gDPLoadTextureBlock_Runtime(OVERLAY_DISP++, gMapChestIconTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0,
                                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                        G_TX_NOLOD, G_TX_NOLOD);

            gSPTextureRectangle(OVERLAY_DISP++, (posX - 4) << 2, (posY - 4) << 2, (posX + 4) << 2, (posY + 4) << 2,
                                G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        } else {
            Gfx_SetupDL39_Overlay(play->state.gfxCtx);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            if (actor->flags & ACTOR_FLAG_MINIMAP_ICON_ENABLED) {
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sMinimapActorCategoryColors[actor->category].r,
                                sMinimapActorCategoryColors[actor->category].g,
                                sMinimapActorCategoryColors[actor->category].b, play->interfaceCtx.minimapAlpha);
                gSPTextureRectangle(OVERLAY_DISP++, (posX - 1) << 2, (posY - 1) << 2, (posX + 1) << 2, (posY + 1) << 2,
                                    G_TX_RENDERTILE, 0, 0, 0x0001, 0x0001);
            }
        }
        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void DrawCustomActors(PlayState* play, SceneAPI_Minimap* minimap, SceneAPI_MinimapRoom* roomData) {
    ActorContext* actorCtx;
    s32 i;

    if (play->roomCtx.curRoom.num != -1) {
        OPEN_DISPS(play->state.gfxCtx);

        gDPLoadTextureBlock_4b(OVERLAY_DISP++, &sWhiteSquareTex, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        actorCtx = &play->actorCtx;
        for (i = 0; i < ACTORCAT_MAX; i++) {
            Actor* actor = actorCtx->actorLists[i].first;
            
            // This hack is not vanilla behaviour and WILL break things.
            //sMapDisp.curRoom = 0;

            while (actor != NULL) {
                if ((actor->update != NULL) && (actor->init == NULL) &&
                    Object_IsLoaded(&play->objectCtx, actor->objectSlot) &&
                    ((actor->id == ACTOR_EN_BOX) || (i == ACTORCAT_PLAYER) ||
                     (actor->flags & ACTOR_FLAG_MINIMAP_ICON_ENABLED)) &&
                    ((sMapDisp.curRoom == actor->room) || (actor->room == -1))) {
                    DrawCustomActorIcon(play, minimap, roomData, actor);
                }
                actor = actor->next;
            }
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}


void DrawCustomMinimapRoom(PlayState* play, SceneAPI_Minimap* minimap, SceneAPI_MinimapRoom* roomData, s32 x, s32 y, f32 intensity) {
    s32 texWidth;
    s32 texHeight;
    s32 dtdy;
    s32 dsdx;
    s32 t;
    s32 s;
    s16 dsdx_temp;
    s16 dtdy_temp;
    Color_RGBA8 color;
    s32 drawType;
    TexturePtr texture;

    texture = roomData->texture;
    // texture = minimap_room_0;
    texWidth = roomData->texWidth;
    texHeight = roomData->texHeight;

    color = minimap->color;
    drawType = minimap->drawType;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL39_Overlay(play->state.gfxCtx);
    
    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, color.r, color.g, color.b,
                    (s32)(play->interfaceCtx.minimapAlpha * intensity * color.a / 255.0f));

    switch (drawType) {
        case MAPDATA_DRAW_1:
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            gDPLoadTextureBlock_4b(OVERLAY_DISP++, texture, G_IM_FMT_IA, texWidth, texHeight, 0,
                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            break;

        case MAPDATA_DRAW_3:
            gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);
            gDPLoadTextureBlock_4b(OVERLAY_DISP++, texture, G_IM_FMT_I, texWidth, texHeight, 0,
                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            break;

        default:
        case MAPDATA_DRAW_0:
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            gDPLoadTextureBlock_4b(OVERLAY_DISP++, texture, G_IM_FMT_I, texWidth, texHeight, 0,
                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    
    s = 0;
    t = (texHeight - 1) << 5;
    dsdx = 1 * (1 << 10);
    dtdy = (-1 * (1 << 10)) & 0xFFFF;

    gSPTextureRectangle(OVERLAY_DISP++, x << 2, y << 2, (texWidth + x) << 2, (y + texHeight) << 2, G_TX_RENDERTILE, s,
                        t, dsdx, dtdy);

    CLOSE_DISPS(play->state.gfxCtx);
}

void DrawCustomMinimap(PlayState* play, s32 playerInitX, s32 playerInitZ, s32 playerInitDir) {
    PauseContext* pauseCtx = &play->pauseCtx;
    SceneAPI_CustomScene* scene = GetCustomScene(sceneAPI_customSceneId);
    // SceneAPI_MinimapRoom* curRoomData = &scene->minimap.rooms[sMapDisp.curRoom];
    // SceneAPI_MinimapRoom* prevRoomData = &scene->minimap.rooms[sMapDisp.prevRoom];
    SceneAPI_MinimapRoom* curRoomData = &scene->minimap.rooms[0];

    if ((curRoomData->isValid) && ((s32)pauseCtx->state <= PAUSE_STATE_OPENING_2) && !R_MINIMAP_DISABLED && (play->interfaceCtx.minimapAlpha != 0)) {
        if (play->csCtx.state == CS_STATE_IDLE) {
            DrawCustomMinimapRoom(play, &scene->minimap, curRoomData, sMapDisp.minimapCurX, sMapDisp.minimapCurY, 1.0f - (sMapDisp.swapAnimTimer * 0.05f));
            DrawCustomMinimapRoom(play, &scene->minimap, curRoomData, sMapDisp.minimapCurX, sMapDisp.minimapCurY, 1.0f - (sMapDisp.swapAnimTimer * 0.05f));
            // MapDisp_Minimap_DrawActors(play);
            DrawCustomActors(play, &scene->minimap, curRoomData);
        }
    }
}

RECOMP_PATCH s32 MapDisp_CanDisplayMinimap(PlayState* play) {
    if (play->sceneId == SCENEAPI_SCENE) {
        return true;
    }

    if ((!Map_CurRoomHasMapI(play) && Inventory_IsMapVisible(play->sceneId)) ||
        (Map_CurRoomHasMapI(play) && CHECK_DUNGEON_ITEM(DUNGEON_MAP, gSaveContext.mapIndex))) {
        return true;
    }
    return false;
}

RECOMP_PATCH s32 MapDisp_IsLocationMinimapBlocked(PlayState* play) {
    if (play->sceneId == SCENEAPI_SCENE) {
        return false;
    }

    if (((play->csCtx.state != CS_STATE_IDLE) && !MapDisp_IsLocationRomaniRanchAltScene(play)) ||
        (sMapDisp.unk20 & 2) || Map_IsInBossScene(play)) {
        return true;
    }
    return false;
}

RECOMP_PATCH s32 MapDisp_IsMinimapToggleBlocked(PlayState* play) {
    if (play->sceneId == SCENEAPI_SCENE) {
        return false;
    }

    if ((MapDisp_IsLocationMinimapBlocked(play) == true) || !MapDisp_CanDisplayMinimap(play)) {
        return true;
    }
    return false;
}

extern s32 Map_GetDungeonSceneIndex(PlayState* play);
RECOMP_PATCH s32 Map_CurRoomHasMapI(PlayState* play) {
    if (play->sceneId == SCENEAPI_SCENE) {
        return true;
    }

    if ((Map_GetDungeonSceneIndex(play) == -1) || !MapDisp_CurRoomHasMapI(play)) {
        return false;
    }

    return true;
}