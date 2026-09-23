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

    // Custom
    if (play->sceneId == SCENEAPI_SCENE) {
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
    // Vanilla
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