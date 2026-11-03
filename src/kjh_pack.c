// KJH: wild packs in battle (docs/PACKS.md in the KJH repo, rules in src/kjh_pack_rules.c).
//
// 1 random wild Pokemon in 20 leads a pack: a few levels higher, perfect IVs, harder to catch, more Exp., and a
// gold healthbox with a crown. The wild Pokemon met first is the leader (party slot 0).
#include "global.h"
#include "battle.h"
#include "battle_interface.h"
#include "battle_setup.h"
#include "kjh_pack.h"
#include "palette.h"
#include "pokemon.h"
#include "random.h"
#include "safari_zone.h"
#include "sprite.h"
#include "constants/rgb.h"

#ifdef KJH_DEBUG_WARP
// Harness (kjh_tools/test/emu_expansion_eng6.py in the KJH repo): 1 at 0x0203FF30 makes every wild Pokemon that
// can lead a pack a leader.
#define DEBUG_PACK (*(vu8 *)0x0203FF30)
#else
#define DEBUG_PACK 0
#endif

#define PACK_FLAG_LEADER 1 // the wild Pokemon leads a pack

// The wild Pokemon just made by CreateWildMon, until the battle starts
EWRAM_DATA static u8 sPackNextEncounter = 0;
// This battle's (PACK_FLAG_*)
EWRAM_DATA static u8 sPackBattleFlags = 0;

u32 KJH_PackWildEncounterLevel(enum Species species, u32 level)
{
    sPackNextEncounter = 0;
    // The Safari Zone and the Pokemon Tower's ghosts make their wild Pokemon here too, but never have packs
    if (!KJH_PackSpeciesAllowed(species) || GetSafariZoneFlag()
     || CheckSilphScopeInPokemonTower(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum))
        return level;
    // Outcome 0 leads, so a test that doesn't set RNG_KJH_PACK_LEADER (its default is the last outcome) never meets one
    if (!DEBUG_PACK && RandomWeighted(RNG_KJH_PACK_LEADER, 1, KJH_PACK_LEADER_ODDS - 1) != 0)
        return level;

    sPackNextEncounter = PACK_FLAG_LEADER;
    return KJH_PackLeaderLevel(level);
}

void KJH_PackFinishWildMon(struct Pokemon *mon)
{
    u32 iv = KJH_PACK_LEADER_IV;

    if (!(sPackNextEncounter & PACK_FLAG_LEADER))
        return;
    for (enum Stat stat = STAT_HP; stat < NUM_STATS; stat++)
        SetMonData(mon, MON_DATA_HP_IV + stat, &iv);
    CalculateMonStats(mon);
}

void KJH_PackSetNextEncounter(bool32 leader)
{
    sPackNextEncounter = leader ? PACK_FLAG_LEADER : 0;
}

void KJH_PackBattleStart(void)
{
    // Only a plain random wild battle: not a trainer, safari, ghost, roamer, legendary or scripted battle (those
    // set battle type flags), and not one of expansion's double wild battles. A recorded one (the test runner's)
    // plays the same.
    sPackBattleFlags = (gBattleTypeFlags & ~(BATTLE_TYPE_IS_MASTER | BATTLE_TYPE_RECORDED)) == 0 ? sPackNextEncounter : 0;
    sPackNextEncounter = 0;

    // The healthboxes were drawn before the battle knew it had a leader
    if (KJH_PackIsLeaderBattle())
        KJH_PackDecorateHealthbox(gHealthboxSpriteIds[B_POSITION_OPPONENT_LEFT], B_POSITION_OPPONENT_LEFT);
}

bool32 KJH_PackIsLeaderBattle(void)
{
    return (sPackBattleFlags & PACK_FLAG_LEADER) != 0;
}

enum KjhPackRole KJH_PackRole(u32 battler)
{
    if (!KJH_PackIsLeaderBattle() || GetBattlerSide(battler) != B_SIDE_OPPONENT)
        return KJH_PACK_ROLE_NONE;
    // The leader is the wild Pokemon met first; helpers fill the wild party slots after it
    return gBattlerPartyIndexes[battler] == 0 ? KJH_PACK_ROLE_LEADER : KJH_PACK_ROLE_LEADER_HELPER;
}

bool32 KJH_PackIsLeader(u32 battler)
{
    return KJH_PackRole(battler) == KJH_PACK_ROLE_LEADER;
}

// ---------------------------------------------------------------- the leader's healthbox
// The leader stands out from its helpers: its healthbox uses a copy of the healthbox palette where the text colors
// are gold (its name and level), and a small gold crown sits on the box. Both go when another Pokemon takes its
// place.

#define TAG_PACK_LEADER 0x4B08 // the crown's tiles and the gold healthbox palette
#define CROWN_X (-22)          // from the healthbox's main (left) sprite: on its top edge, over the name
#define CROWN_Y (-14)

// Healthbox palette entries the text is drawn with (sHealthBoxTextColor, src/battle_interface.c)
#define HEALTHBOX_TEXT   1
#define HEALTHBOX_SHADOW 3

// Drawn with the healthbox palette: its outline is the gold text color (1), then the healthbox's yellow (9) and
// pink (10)
static const u32 sCrown_Gfx[] = INCGFX_U32("graphics/battle_interface/kjh_pack_crown.png", ".4bpp");

static const struct SpriteSheet sSpriteSheet_Crown = {sCrown_Gfx, sizeof(sCrown_Gfx), TAG_PACK_LEADER};

static const struct OamData sOamData_Crown =
{
    .shape = SPRITE_SHAPE(8x8),
    .size = SPRITE_SIZE(8x8),
    .priority = 1,
};

static void SpriteCB_Crown(struct Sprite *sprite);

static const struct SpriteTemplate sSpriteTemplate_Crown =
{
    .tileTag = TAG_PACK_LEADER,
    .paletteTag = TAG_PACK_LEADER,
    .oam = &sOamData_Crown,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_Crown,
};

#define tHealthbox data[0]
#define tBattler   data[1]

// The gold healthbox palette, loaded the first time. 0xFF: no free palette (the box stays as it is).
static u32 LeaderPaletteNum(void)
{
    u32 paletteNum = IndexOfSpritePaletteTag(TAG_PACK_LEADER);
    u32 healthboxPal = IndexOfSpritePaletteTag(TAG_HEALTHBOX_PAL);
    u16 colors[16];
    struct SpritePalette palette = {colors, TAG_PACK_LEADER};

    if (paletteNum != 0xFF || healthboxPal == 0xFF)
        return paletteNum;

    CpuCopy16(&gPlttBufferUnfaded[OBJ_PLTT_ID(healthboxPal)], colors, sizeof(colors));
    colors[HEALTHBOX_TEXT] = RGB(23, 15, 0);    // dark gold
    colors[HEALTHBOX_SHADOW] = RGB(31, 26, 12); // light gold
    return LoadSpritePalette(&palette);
}

static void SetHealthboxPalette(u32 healthboxSpriteId, u32 paletteNum)
{
    gSprites[healthboxSpriteId].oam.paletteNum = paletteNum;
    gSprites[gSprites[healthboxSpriteId].oam.affineParam].oam.paletteNum = paletteNum; // the right half
}

static bool32 IsCrown(struct Sprite *sprite)
{
    return sprite->inUse && sprite->template == &sSpriteTemplate_Crown;
}

// The healthbox goes back to the usual palette, and the gold one is freed (a battle has one leader)
static void RemoveGold(u32 healthboxSpriteId)
{
    u32 goldPal = IndexOfSpritePaletteTag(TAG_PACK_LEADER);

    if (gSprites[healthboxSpriteId].inUse && gSprites[healthboxSpriteId].oam.paletteNum == goldPal)
        SetHealthboxPalette(healthboxSpriteId, IndexOfSpritePaletteTag(TAG_HEALTHBOX_PAL));
    FreeSpritePaletteByTag(TAG_PACK_LEADER);
}

static void DestroyCrown(struct Sprite *sprite)
{
    RemoveGold(sprite->tHealthbox);
    DestroySprite(sprite);
    FreeSpriteTilesByTag(TAG_PACK_LEADER);
}

// Sits on the leader's healthbox, and goes once another Pokemon is in its slot. Only battle globals that outlive
// the battle are read here: the last frames of a battle run after its resources are freed.
static void SpriteCB_Crown(struct Sprite *sprite)
{
    struct Sprite *healthbox = &gSprites[sprite->tHealthbox];

    if (!healthbox->inUse || gHealthboxSpriteIds[sprite->tBattler] != sprite->tHealthbox
     || gBattlerPartyIndexes[sprite->tBattler] != 0)
    {
        DestroyCrown(sprite);
        return;
    }

    sprite->x = healthbox->x + healthbox->x2 + CROWN_X;
    sprite->y = healthbox->y + healthbox->y2 + CROWN_Y;
    sprite->invisible = healthbox->invisible;
}

static void ShowCrown(u32 healthboxSpriteId, u32 battler)
{
    u32 spriteId;

    for (u32 i = 0; i < MAX_SPRITES; i++)
    {
        if (IsCrown(&gSprites[i]) && gSprites[i].tHealthbox == healthboxSpriteId)
            return;
    }

    if (GetSpriteTileStartByTag(TAG_PACK_LEADER) == 0xFFFF)
        LoadSpriteSheet(&sSpriteSheet_Crown);
    spriteId = CreateSprite(&sSpriteTemplate_Crown, 0, 0, 0);
    if (spriteId == MAX_SPRITES)
        return;

    gSprites[spriteId].tHealthbox = healthboxSpriteId;
    gSprites[spriteId].tBattler = battler;
    gSprites[spriteId].callback(&gSprites[spriteId]); // in place from the first frame
}

#undef tHealthbox
#undef tBattler

void KJH_PackDecorateHealthbox(u32 healthboxSpriteId, u32 battler)
{
    u32 paletteNum;

    if (KJH_PackIsLeader(battler) && (paletteNum = LeaderPaletteNum()) != 0xFF)
    {
        SetHealthboxPalette(healthboxSpriteId, paletteNum);
        ShowCrown(healthboxSpriteId, battler);
    }
    else if (gSprites[healthboxSpriteId].oam.paletteNum == IndexOfSpritePaletteTag(TAG_PACK_LEADER))
    {
        RemoveGold(healthboxSpriteId); // a helper took the leader's slot before its crown noticed
    }
}
