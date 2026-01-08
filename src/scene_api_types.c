#include "scene_api_types.h"

// Pass in a SCENE_ value to get the ENTR value in return
EntranceSceneId sceneAPI_sceneId_to_entranceId[] = {
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

SceneId sceneAPI_entranceId_to_sceneId[] = {
    /* 0x00 ENTR_SCENE_MAYORS_RESIDENCE */              SCENE_SONCHONOIE,
    /* 0x01 ENTR_SCENE_MAJORAS_LAIR */                  SCENE_LAST_BS,
    /* 0x02 ENTR_SCENE_MAGIC_HAGS_POTION_SHOP */        SCENE_WITCH_SHOP,
    /* 0x03 ENTR_SCENE_RANCH_HOUSE */                   SCENE_OMOYA,
    /* 0x04 ENTR_SCENE_HONEY_AND_DARLINGS_SHOP */       SCENE_BOWLING,
    /* 0x05 ENTR_SCENE_BENEATH_THE_GRAVERYARD */        SCENE_HAKASHITA,
    /* 0x06 ENTR_SCENE_SOUTHERN_SWAMP_CLEARED */        SCENE_20SICHITAI2,
    /* 0x07 ENTR_SCENE_CURIOSITY_SHOP */                SCENE_AYASHIISHOP,
    /* 0x08 ENTR_SCENE_UNSET_08 */                      0,
    /* 0x09 ENTR_SCENE_UNSET_09 */                      0,
    /* 0x0A ENTR_SCENE_GROTTOS */                       SCENE_KAKUSIANA,
    /* 0x0B ENTR_SCENE_UNSET_0B */                      0,
    /* 0x0C ENTR_SCENE_UNSET_0C */                      0,
    /* 0x0D ENTR_SCENE_UNSET_0D */                      0,
    /* 0x0E ENTR_SCENE_CUTSCENE */                      SCENE_SPOT00,
    /* 0x0F ENTR_SCENE_UNSET_0F */                      0,
    /* 0x10 ENTR_SCENE_IKANA_CANYON */                  SCENE_IKANA,
    /* 0x11 ENTR_SCENE_PIRATES_FORTRESS */              SCENE_KAIZOKU,
    /* 0x12 ENTR_SCENE_MILK_BAR */                      SCENE_MILK_BAR,
    /* 0x13 ENTR_SCENE_STONE_TOWER_TEMPLE */            SCENE_INISIE_N,
    /* 0x14 ENTR_SCENE_TREASURE_CHEST_SHOP */           SCENE_TAKARAYA,
    /* 0x15 ENTR_SCENE_STONE_TOWER_TEMPLE_INVERTED */   SCENE_INISIE_R,
    /* 0x16 ENTR_SCENE_CLOCK_TOWER_ROOFTOP */           SCENE_OKUJOU,
    /* 0x17 ENTR_SCENE_OPENING_DUNGEON */               SCENE_OPENINGDAN,
    /* 0x18 ENTR_SCENE_WOODFALL_TEMPLE */               SCENE_MITURIN,
    /* 0x19 ENTR_SCENE_PATH_TO_MOUNTAIN_VILLAGE */      SCENE_13HUBUKINOMITI,
    /* 0x1A ENTR_SCENE_IKANA_CASTLE */                  SCENE_CASTLE,
    /* 0x1B ENTR_SCENE_DEKU_SCRUB_PLAYGROUND */         SCENE_DEKUTES,
    /* 0x1C ENTR_SCENE_ODOLWAS_LAIR */                  SCENE_MITURIN_BS,
    /* 0x1D ENTR_SCENE_TOWN_SHOOTING_GALLERY */         SCENE_SYATEKI_MIZU,
    /* 0x1E ENTR_SCENE_SNOWHEAD_TEMPLE */               SCENE_HAKUGIN,
    /* 0x1F ENTR_SCENE_MILK_ROAD */                     SCENE_ROMANYMAE,
    /* 0x20 ENTR_SCENE_PIRATES_FORTRESS_INTERIOR */     SCENE_PIRATE,
    /* 0x21 ENTR_SCENE_SWAMP_SHOOTING_GALLERY */        SCENE_SYATEKI_MORI,
    /* 0x22 ENTR_SCENE_PINNACLE_ROCK */                 SCENE_SINKAI,
    /* 0x23 ENTR_SCENE_FAIRY_FOUNTAIN */                SCENE_YOUSEI_IZUMI,
    /* 0x24 ENTR_SCENE_SWAMP_SPIDER_HOUSE */            SCENE_KINSTA1,
    /* 0x25 ENTR_SCENE_OCEANSIDE_SPIDER_HOUSE */        SCENE_KINDAN2,
    /* 0x26 ENTR_SCENE_ASTRAL_OBSERVATORY */            SCENE_TENMON_DAI,
    /* 0x27 ENTR_SCENE_MOON_DEKU_TRIAL */               SCENE_LAST_DEKU,
    /* 0x28 ENTR_SCENE_DEKU_PALACE */                   SCENE_22DEKUCITY,
    /* 0x29 ENTR_SCENE_MOUNTAIN_SMITHY */               SCENE_KAJIYA,
    /* 0x2A ENTR_SCENE_TERMINA_FIELD */                 SCENE_00KEIKOKU,
    /* 0x2B ENTR_SCENE_POST_OFFICE */                   SCENE_POSTHOUSE,
    /* 0x2C ENTR_SCENE_MARINE_RESEARCH_LAB */           SCENE_LABO,
    /* 0x2D ENTR_SCENE_DAMPES_HOUSE */                  SCENE_DANPEI2TEST,
    /* 0x2E ENTR_SCENE_UNSET_2E */                      0,
    /* 0x2F ENTR_SCENE_GORON_SHRINE */                  SCENE_16GORON_HOUSE,
    /* 0x30 ENTR_SCENE_ZORA_HALL */                     SCENE_33ZORACITY,
    /* 0x31 ENTR_SCENE_TRADING_POST */                  SCENE_8ITEMSHOP,
    /* 0x32 ENTR_SCENE_ROMANI_RANCH */                  SCENE_F01,
    /* 0x33 ENTR_SCENE_TWINMOLDS_LAIR */                SCENE_INISIE_BS,
    /* 0x34 ENTR_SCENE_GREAT_BAY_COAST */               SCENE_30GYOSON,
    /* 0x35 ENTR_SCENE_ZORA_CAPE */                     SCENE_31MISAKI,
    /* 0x36 ENTR_SCENE_LOTTERY_SHOP */                  SCENE_TAKARAKUJI,
    /* 0x37 ENTR_SCENE_UNSET_37 */                      0,
    /* 0x38 ENTR_SCENE_PIRATES_FORTRESS_EXTERIOR */     SCENE_TORIDE,
    /* 0x39 ENTR_SCENE_FISHERMANS_HUT */                SCENE_FISHERMAN,
    /* 0x3A ENTR_SCENE_GORON_SHOP */                    SCENE_GORONSHOP,
    /* 0x3B ENTR_SCENE_DEKU_KINGS_CHAMBER */            SCENE_DEKU_KING,
    /* 0x3C ENTR_SCENE_MOON_GORON_TRIAL */              SCENE_LAST_GORON,
    /* 0x3D ENTR_SCENE_ROAD_TO_SOUTHERN_SWAMP */        SCENE_24KEMONOMITI,
    /* 0x3E ENTR_SCENE_DOGGY_RACETRACK */               SCENE_F01_B,
    /* 0x3F ENTR_SCENE_CUCCO_SHACK */                   SCENE_F01C,
    /* 0x40 ENTR_SCENE_IKANA_GRAVEYARD */               SCENE_BOTI,
    /* 0x41 ENTR_SCENE_GOHTS_LAIR */                    SCENE_HAKUGIN_BS,
    /* 0x42 ENTR_SCENE_SOUTHERN_SWAMP_POISONED */       SCENE_20SICHITAI,
    /* 0x43 ENTR_SCENE_WOODFALL */                      SCENE_21MITURINMAE,
    /* 0x44 ENTR_SCENE_MOON_ZORA_TRIAL */               SCENE_LAST_ZORA,
    /* 0x45 ENTR_SCENE_GORON_VILLAGE_SPRING */          SCENE_11GORONNOSATO2,
    /* 0x46 ENTR_SCENE_GREAT_BAY_TEMPLE */              SCENE_SEA,
    /* 0x47 ENTR_SCENE_WATERFALL_RAPIDS */              SCENE_35TAKI,
    /* 0x48 ENTR_SCENE_BENEATH_THE_WELL */              SCENE_REDEAD,
    /* 0x49 ENTR_SCENE_ZORA_HALL_ROOMS */               SCENE_BANDROOM,
    /* 0x4A ENTR_SCENE_GORON_VILLAGE_WINTER */          SCENE_11GORONNOSATO,
    /* 0x4B ENTR_SCENE_GORON_GRAVERYARD */              SCENE_GORON_HAKA,
    /* 0x4C ENTR_SCENE_SAKONS_HIDEOUT */                SCENE_SECOM,
    /* 0x4D ENTR_SCENE_MOUNTAIN_VILLAGE_WINTER */       SCENE_10YUKIYAMANOMURA,
    /* 0x4E ENTR_SCENE_GHOST_HUT */                     SCENE_TOUGITES,
    /* 0x4F ENTR_SCENE_DEKU_SHRINE */                   SCENE_DANPEI,
    /* 0x50 ENTR_SCENE_ROAD_TO_IKANA */                 SCENE_IKANAMAE,
    /* 0x51 ENTR_SCENE_SWORDMANS_SCHOOL */              SCENE_DOUJOU,
    /* 0x52 ENTR_SCENE_MUSIC_BOX_HOUSE */               SCENE_MUSICHOUSE,
    /* 0x53 ENTR_SCENE_IGOS_DU_IKANAS_LAIR */           SCENE_IKNINSIDE,
    /* 0x54 ENTR_SCENE_TOURIST_INFORMATION */           SCENE_MAP_SHOP,
    /* 0x55 ENTR_SCENE_STONE_TOWER */                   SCENE_F40,
    /* 0x56 ENTR_SCENE_STONE_TOWER_INVERTED */          SCENE_F41,
    /* 0x57 ENTR_SCENE_MOUNTAIN_VILLAGE_SPRING */       SCENE_10YUKIYAMANOMURA2,
    /* 0x58 ENTR_SCENE_PATH_TO_SNOWHEAD */              SCENE_14YUKIDAMANOMITI,
    /* 0x59 ENTR_SCENE_SNOWHEAD */                      SCENE_12HAKUGINMAE,
    /* 0x5A ENTR_SCENE_PATH_TO_GORON_VILLAGE_WINTER */  SCENE_17SETUGEN,
    /* 0x5B ENTR_SCENE_PATH_TO_GORON_VILLAGE_SPRING */  SCENE_17SETUGEN2,
    /* 0x5C ENTR_SCENE_GYORGS_LAIR */                   SCENE_SEA_BS,
    /* 0x5D ENTR_SCENE_SECRET_SHRINE */                 SCENE_RANDOM,
    /* 0x5E ENTR_SCENE_STOCK_POT_INN */                 SCENE_YADOYA,
    /* 0x5F ENTR_SCENE_GREAT_BAY_CUTSCENE */            SCENE_KONPEKI_ENT,
    /* 0x60 ENTR_SCENE_CLOCK_TOWER_INTERIOR */          SCENE_INSIDETOWER,
    /* 0x61 ENTR_SCENE_WOODS_OF_MYSTERY */              SCENE_26SARUNOMORI,
    /* 0x62 ENTR_SCENE_LOST_WOODS */                    SCENE_LOST_WOODS,
    /* 0x63 ENTR_SCENE_MOON_LINK_TRIAL */               SCENE_LAST_LINK,
    /* 0x64 ENTR_SCENE_THE_MOON */                      SCENE_SOUGEN,
    /* 0x65 ENTR_SCENE_BOMB_SHOP */                     SCENE_BOMYA,
    /* 0x66 ENTR_SCENE_GIANTS_CHAMBER */                SCENE_KYOJINNOMA,
    /* 0x67 ENTR_SCENE_GORMAN_TRACK */                  SCENE_KOEPONARACE,
    /* 0x68 ENTR_SCENE_GORON_RACETRACK */               SCENE_GORONRACE,
    /* 0x69 ENTR_SCENE_EAST_CLOCK_TOWN */               SCENE_TOWN,
    /* 0x6A ENTR_SCENE_WEST_CLOCK_TOWN */               SCENE_ICHIBA,
    /* 0x6B ENTR_SCENE_NORTH_CLOCK_TOWN */              SCENE_BACKTOWN,
    /* 0x6C ENTR_SCENE_SOUTH_CLOCK_TOWN */              SCENE_CLOCKTOWER,
    /* 0x6D ENTR_SCENE_LAUNDRY_POOL */                  SCENE_ALLEY,
};