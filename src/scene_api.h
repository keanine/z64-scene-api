#ifndef SCENE_API_H
#define SCENE_API_H

#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "PR/gbi.h"

#include <z64scene.h>

enum SceneAPI_ExitType { SCENEAPI_EXITTYPE_VANILLA, SCENEAPI_EXITTYPE_MODDED };

typedef struct SceneAPI_Exit {
    enum SceneAPI_ExitType exitType;
    u16 id;
    char* sceneName;
} SceneAPI_Exit;

typedef struct SceneAPI_CustomScene {
    char* sceneName;
    SceneCmd* sceneSegment;
    SceneCmd** roomList;
    SceneAPI_Exit* exitIdList;
} SceneAPI_CustomScene;

typedef struct SceneAPI_Grotto {
    SceneId scene;
    u16 customSceneIndex;
    SceneAPI_Exit exit;
    f32 x;
    f32 y;
    f32 z;
    Actor* actor;
} SceneAPI_Grotto;

typedef struct SceneAPI_ExitOverride {
    SceneId originalScene;
    u16 originalEntranceId;
    SceneAPI_Exit newExit;
} SceneAPI_ExitOverride;

void SceneAPI_SetSceneAtIndex(u8 customSceneIndex, char* name, SceneCmd* header, SceneCmd* rooms[], SceneAPI_Exit exitIDs[]);
RECOMP_EXPORT u16 SceneAPI_AddScene(char* sceneName, SceneCmd* header, SceneCmd* rooms[], SceneAPI_Exit exitIDs[]);
RECOMP_EXPORT void SceneAPI_AddExitOverride(SceneId originalScene, u16 originalEntranceId, SceneAPI_Exit exit);
RECOMP_EXPORT void SceneAPI_AddGrotto(SceneId scene, SceneAPI_Exit exit, f32 x, f32 y, f32 z);
RECOMP_EXPORT void SceneAPI_AddGrottoToCustomScene(char* sceneName, SceneAPI_Exit exit, f32 x, f32 y, f32 z);


u16 SceneAPI_GetSceneIdByName(char* name);

// enum SceneAPI_ExitType exitType;
// u16 id;
// char* sceneName;
#define SCENEAPI_EXIT(exitType, id, sceneName) (SceneAPI_Exit){ exitType, id, sceneName }

#define SCENEAPI_SCENE SCENE_INSIDETOWER
#define SCENEAPI_SCENE_ENTR 0xC010

struct SceneAPI_CustomScene sceneAPI_customScenes[500];
struct SceneAPI_ExitOverride sceneAPI_exitOverrides[500];
struct SceneAPI_Grotto sceneAPI_grottos[500];

u8 sceneAPI_isNextEntranceModified = false;
u16 sceneAPI_modifiedNextEntrance = -1;
u16 sceneAPI_savedGrottoEntrance = 0;

PlayState* sceneAPI_play = NULL;
SceneAPI_Grotto* sceneAPI_currentGrotto = NULL;

u32 sceneAPI_customSceneIterator = 0;
u32 sceneAPI_exitOverrideIterator = 0;
u32 sceneAPI_grottosIterator = 0;

#define SCENEAPI_VANILLA_ID 65535
u16 sceneAPI_customSceneId = SCENEAPI_VANILLA_ID;
u16 sceneAPI_nextCustomSceneId = SCENEAPI_VANILLA_ID;

RECOMP_DECLARE_EVENT(SceneAPI_Init());
RECOMP_DECLARE_EVENT(SceneAPI_PostInit());

EntranceSceneId sceneAPI_entrances[] = {
    /* Southern Swamp (Clear) */
    /* SCENE_20SICHITAI2 */
    ENTR_SCENE_SOUTHERN_SWAMP_CLEARED,

    /* SCENE_UNSET_01 */ 0,
    /* SCENE_UNSET_02 */ 0,
    /* SCENE_UNSET_03 */ 0,
    /* SCENE_UNSET_04 */ 0,
    /* SCENE_UNSET_05 */ 0,
    /* SCENE_UNSET_06 */ 0,

    /* Lone Peak Shrine & Grottos */
    /* SCENE_KAKUSIANA */
    ENTR_SCENE_GROTTOS,

    /* Cutscene Scene */
    /* SCENE_SPOT00 */
    ENTR_SCENE_CUTSCENE,

    /* SCENE_UNSET_09 */ ENTR_SCENE_UNSET_2E,

    /* Magic Hags' Potion Shop */
    /* SCENE_WITCH_SHOP */
    ENTR_SCENE_MAGIC_HAGS_POTION_SHOP,

    /* Majora's Lair */
    /* SCENE_LAST_BS */
    ENTR_SCENE_MAJORAS_LAIR,

    // Beneath the Graveyard
    /* SCENE_HAKASHITA */
    ENTR_SCENE_BENEATH_THE_GRAVERYARD,

    /* Curiosity Shop */
    /* SCENE_AYASHIISHOP */
    ENTR_SCENE_CURIOSITY_SHOP,
    
    /* SCENE_UNSET_0E */ 0,
    /* SCENE_UNSET_0F */ 0,

    /* Mama's House (Ranch House in PAL) & Barn */
    /* SCENE_OMOYA */
    ENTR_SCENE_RANCH_HOUSE,

    /* Honey & Darling's Shop */
    /* SCENE_BOWLING */
    ENTR_SCENE_HONEY_AND_DARLINGS_SHOP,

    /* The Mayor's Residence */
    /* SCENE_SONCHONOIE */
    ENTR_SCENE_MAYORS_RESIDENCE,

    /* Ikana Canyon */
    /* SCENE_IKANA */
    ENTR_SCENE_IKANA_CANYON,

    /* Pirates' Fortress */
    /* SCENE_KAIZOKU */
    ENTR_SCENE_PIRATES_FORTRESS,

    /* Milk Bar */
    /* SCENE_MILK_BAR */
    ENTR_SCENE_MILK_BAR,

    /* Stone Tower Temple */
    /* SCENE_INISIE_N */
    ENTR_SCENE_STONE_TOWER_TEMPLE,

    /* Treasure Chest Shop */
    /* SCENE_TAKARAYA */
    ENTR_SCENE_TREASURE_CHEST_SHOP,

    /* Inverted Stone Tower Temple */
    /* SCENE_INISIE_R */
    ENTR_SCENE_STONE_TOWER_TEMPLE_INVERTED,

    /* Clock Tower Rooftop */
    /* SCENE_OKUJOU */
    ENTR_SCENE_CLOCK_TOWER_ROOFTOP,

    /* Before Clock Town */
    /* SCENE_OPENINGDAN */
    ENTR_SCENE_OPENING_DUNGEON,
    
    /* Woodfall Temple */
    /* SCENE_MITURIN */
    ENTR_SCENE_WOODFALL_TEMPLE,

    /* Path to Mountain Village */
    /* SCENE_13HUBUKINOMITI */
    ENTR_SCENE_PATH_TO_MOUNTAIN_VILLAGE,

    /* Ancient Castle of Ikana */
    /* SCENE_CASTLE */
    ENTR_SCENE_IKANA_CASTLE,

    /* Deku Scrub Playground*/
    /* SCENE_DEKUTES */ 
    ENTR_SCENE_DEKU_SCRUB_PLAYGROUND,

    /* Odolwa's Lair */
    /* SCENE_MITURIN_BS */
    ENTR_SCENE_ODOLWAS_LAIR,

    /* Town Shooting Gallery */
    /* SCENE_SYATEKI_MIZU */
    ENTR_SCENE_TOWN_SHOOTING_GALLERY,

    // Snowhead Temple
    /* SCENE_HAKUGIN */
    ENTR_SCENE_SNOWHEAD_TEMPLE,

    // Milk Road
    /* SCENE_ROMANYMAE */
    ENTR_SCENE_MILK_ROAD,

    // Pirates' Fortress Interior
    /* SCENE_PIRATE */
    ENTR_SCENE_PIRATES_FORTRESS_INTERIOR,

    // Swamp Shooting Gallery
    /* SCENE_SYATEKI_MORI */
    ENTR_SCENE_SWAMP_SHOOTING_GALLERY,

    // Pinnacle Rock
    /* SCENE_SINKAI */
    ENTR_SCENE_PINNACLE_ROCK,

    // Fairy's Fountain
    /* SCENE_YOUSEI_IZUMI */
    ENTR_SCENE_FAIRY_FOUNTAIN,

    // Swamp Spider House
    /* SCENE_KINSTA1 */
    ENTR_SCENE_SWAMP_SPIDER_HOUSE,

    // Oceanside Spider House
    /* SCENE_KINDAN2 */
    ENTR_SCENE_OCEANSIDE_SPIDER_HOUSE,

    // Astral Observatory
    /* SCENE_TENMON_DAI */
    ENTR_SCENE_ASTRAL_OBSERVATORY,

    // Moon Deku Trial
    /* SCENE_LAST_DEKU */
    ENTR_SCENE_MOON_DEKU_TRIAL,

    // Deku Palace
    /* SCENE_22DEKUCITY */
    ENTR_SCENE_DEKU_PALACE,

    // Mountain Smithy
    /* SCENE_KAJIYA */
    ENTR_SCENE_MOUNTAIN_SMITHY,

    // Termina Field
    /* SCENE_00KEIKOKU */
    ENTR_SCENE_TERMINA_FIELD,

    // Post Office
    /* SCENE_POSTHOUSE */
    ENTR_SCENE_POST_OFFICE,

    // Marine Research Lab
    /* SCENE_LABO */
    ENTR_SCENE_MARINE_RESEARCH_LAB,

    /* Beneath the Graveyard (Day 3) and Dampe's House */
    /* SCENE_DANPEI2TEST */
    ENTR_SCENE_DAMPES_HOUSE,

    /* SCENE_UNSET_31 */
    0,

    // Goron Shrine
    /* SCENE_16GORON_HOUSE */
    ENTR_SCENE_GORON_SHRINE,

    // Zora Hall
    /* SCENE_33ZORACITY */
    ENTR_SCENE_ZORA_HALL,

    // Trading Post
    /* SCENE_8ITEMSHOP */
    ENTR_SCENE_TRADING_POST,

    // Romani Ranch
    /* SCENE_F01 */
    ENTR_SCENE_ROMANI_RANCH,

    // Twinmold's Lair
    /* SCENE_INISIE_BS */
    ENTR_SCENE_TWINMOLDS_LAIR,

    // Great Bay Coast
    /* SCENE_30GYOSON */
    ENTR_SCENE_GREAT_BAY_COAST,

    // Zora Cape
    /* SCENE_31MISAKI */
    ENTR_SCENE_ZORA_CAPE,

    // Lottery Shop
    /* SCENE_TAKARAKUJI */
    ENTR_SCENE_LOTTERY_SHOP,

    /* SCENE_UNSET_3A */
    ENTR_SCENE_UNSET_37,

    // Pirates' Fortress Moat
    /* SCENE_TORIDE */
    ENTR_SCENE_PIRATES_FORTRESS_EXTERIOR,

    // Fisherman's Hut
    /* SCENE_FISHERMAN */
    ENTR_SCENE_FISHERMANS_HUT,

    // Goron Shop
    /* SCENE_GORONSHOP */
    ENTR_SCENE_GORON_SHOP,

    // Deku King's Chamber
    /* SCENE_DEKU_KING */
    ENTR_SCENE_DEKU_KINGS_CHAMBER,

    // Moon Goron Trial
    /* SCENE_LAST_GORON */
    ENTR_SCENE_MOON_GORON_TRIAL,

    // Road to Southern Swamp
    /* SCENE_24KEMONOMITI */
    ENTR_SCENE_ROAD_TO_SOUTHERN_SWAMP,

    // Doggy Racetrack
    /* SCENE_F01_B */
    ENTR_SCENE_DOGGY_RACETRACK,

    // Cucco Shack
    /* SCENE_F01C */
    ENTR_SCENE_CUCCO_SHACK,

    // Ikana Graveyard
    /* SCENE_BOTI */
    ENTR_SCENE_IKANA_GRAVEYARD,

    // Goht's Lair
    /* SCENE_HAKUGIN_BS */
    ENTR_SCENE_GOHTS_LAIR,

    // Southern Swamp (poison)
    /* SCENE_20SICHITAI */
    ENTR_SCENE_SOUTHERN_SWAMP_POISONED,

    // Woodfall
    /* SCENE_21MITURINMAE */
    ENTR_SCENE_WOODFALL,

    // Moon Zora Trial
    /* SCENE_LAST_ZORA */
    ENTR_SCENE_MOON_ZORA_TRIAL,

    // Goron Village (spring)
    /* SCENE_11GORONNOSATO2 */
    ENTR_SCENE_GORON_VILLAGE_SPRING,

    // Great Bay Temple
    /* SCENE_SEA */
    ENTR_SCENE_GREAT_BAY_TEMPLE,

    // Waterfall Rapids
    /* SCENE_35TAKI */
    ENTR_SCENE_WATERFALL_RAPIDS,

    // Beneath the Well
    /* SCENE_REDEAD */
    ENTR_SCENE_BENEATH_THE_WELL,

    // Zora Hall Rooms
    /* SCENE_BANDROOM */
    ENTR_SCENE_ZORA_HALL_ROOMS,

    // Goron Village (winter)
    /* SCENE_11GORONNOSATO */
    ENTR_SCENE_GORON_VILLAGE_WINTER,

    // Goron Graveyard
    /* SCENE_GORON_HAKA */
    ENTR_SCENE_GORON_GRAVERYARD,

    // Sakon's Hideout
    /* SCENE_SECOM */
    ENTR_SCENE_SAKONS_HIDEOUT,

    // Mountain Village (winter)
    /* SCENE_10YUKIYAMANOMURA */
    ENTR_SCENE_MOUNTAIN_VILLAGE_WINTER,

    // Ghost Hut
    /* SCENE_TOUGITES */
    ENTR_SCENE_GHOST_HUT,

    // Deku Shrine
    /* SCENE_DANPEI */
    ENTR_SCENE_DEKU_SHRINE,

    // Road to Ikana
    /* SCENE_IKANAMAE */
    ENTR_SCENE_ROAD_TO_IKANA,

    // Swordsman's School
    /* SCENE_DOUJOU */
    ENTR_SCENE_SWORDMANS_SCHOOL,

    // Music Box House
    /* SCENE_MUSICHOUSE */
    ENTR_SCENE_MUSIC_BOX_HOUSE,

    // Igos du Ikana's Lair
    /* SCENE_IKNINSIDE */
    ENTR_SCENE_IGOS_DU_IKANAS_LAIR,

    // Tourist Information
    /* SCENE_MAP_SHOP */
    ENTR_SCENE_TOURIST_INFORMATION,

    /* Stone Tower */
    /* SCENE_F40 */
    ENTR_SCENE_STONE_TOWER,

    /* Inverted Stone Tower */
    /* SCENE_F41 */
    ENTR_SCENE_STONE_TOWER_INVERTED,

    // Mountain Village (spring)
    /* SCENE_10YUKIYAMANOMURA2 */
    ENTR_SCENE_MOUNTAIN_VILLAGE_SPRING,

    // Path to Snowhead
    /* SCENE_14YUKIDAMANOMITI */
    ENTR_SCENE_PATH_TO_SNOWHEAD,

    // Snowhead
    /* SCENE_12HAKUGINMAE */
    ENTR_SCENE_SNOWHEAD,

    // Path to Goron Village (winter)
    /* SCENE_17SETUGEN */
    ENTR_SCENE_PATH_TO_GORON_VILLAGE_WINTER,

    // Path to Goron Village (spring)
    /* SCENE_17SETUGEN2 */
    ENTR_SCENE_PATH_TO_GORON_VILLAGE_SPRING,

    // Gyorg's Lair
    /* SCENE_SEA_BS */
    ENTR_SCENE_GYORGS_LAIR,

    // Secret Shrine
    /* SCENE_RANDOM */
    ENTR_SCENE_SECRET_SHRINE,

    // Stock Pot Inn
    /* SCENE_YADOYA */
    ENTR_SCENE_STOCK_POT_INN,

    // Great Bay Cutscene
    /* SCENE_KONPEKI_ENT */
    ENTR_SCENE_GREAT_BAY_CUTSCENE,

    // Clock Tower Interior
    /* SCENE_INSIDETOWER */
    ENTR_SCENE_CLOCK_TOWER_INTERIOR,

    // Woods of Mystery
    /* SCENE_26SARUNOMORI */
    ENTR_SCENE_WOODS_OF_MYSTERY,

    // Lost Woods (Intro)
    /* SCENE_LOST_WOODS */
    ENTR_SCENE_LOST_WOODS,

    // Moon Link Trial
    /* SCENE_LAST_LINK */
    ENTR_SCENE_MOON_LINK_TRIAL,

    // The Moon
    /* SCENE_SOUGEN */
    ENTR_SCENE_THE_MOON,

    // Bomb Shop
    /* SCENE_BOMYA */
    ENTR_SCENE_BOMB_SHOP,

    // Giants' Chamber
    /* SCENE_KYOJINNOMA */
    ENTR_SCENE_GIANTS_CHAMBER,

    // Gorman Track
    /* SCENE_KOEPONARACE */
    ENTR_SCENE_GORMAN_TRACK,

    // Goron Racetrack
    /* SCENE_GORONRACE */
    ENTR_SCENE_GORON_RACETRACK,

    // East Clock Town
    /* SCENE_TOWN */
    ENTR_SCENE_EAST_CLOCK_TOWN,

    // West Clock Town
    /* SCENE_ICHIBA */
    ENTR_SCENE_WEST_CLOCK_TOWN,

    // North Clock Town
    /* SCENE_BACKTOWN */
    ENTR_SCENE_NORTH_CLOCK_TOWN,

    // South Clock Town
    /* SCENE_CLOCKTOWER */
    ENTR_SCENE_SOUTH_CLOCK_TOWN,

    // Laundry Pool
    /* SCENE_ALLEY */
    ENTR_SCENE_LAUNDRY_POOL
};

#endif /* SCENE_API_H */