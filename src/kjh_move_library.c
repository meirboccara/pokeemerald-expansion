// KJH (LV-10): the move library (include/kjh_move_library.h).
#include "global.h"
#include "event_data.h"
#include "item.h"
#include "kjh_bond.h"
#include "kjh_move_library.h"
#include "move.h"
#include "party_menu.h"
#include "pokemon.h"
#include "string_util.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/moves.h"

struct KjhTutor
{
    u16 move;
    u16 flag;
};

// Kanto's tutors (FireRed's data/scripts/move_tutors_frlg.inc) and the flag each sets once it has taught
static const struct KjhTutor sKantoTutors[] =
{
    {MOVE_DOUBLE_EDGE,   FLAG_TUTOR_DOUBLE_EDGE},
    {MOVE_THUNDER_WAVE,  FLAG_TUTOR_THUNDER_WAVE},
    {MOVE_ROCK_SLIDE,    FLAG_TUTOR_ROCK_SLIDE},
    {MOVE_EXPLOSION,     FLAG_TUTOR_EXPLOSION},
    {MOVE_MEGA_PUNCH,    FLAG_TUTOR_MEGA_PUNCH},
    {MOVE_MEGA_KICK,     FLAG_TUTOR_MEGA_KICK},
    {MOVE_DREAM_EATER,   FLAG_TUTOR_DREAM_EATER},
    {MOVE_SOFT_BOILED,   FLAG_TUTOR_SOFT_BOILED},
    {MOVE_SUBSTITUTE,    FLAG_TUTOR_SUBSTITUTE},
    {MOVE_SWORDS_DANCE,  FLAG_TUTOR_SWORDS_DANCE},
    {MOVE_SEISMIC_TOSS,  FLAG_TUTOR_SEISMIC_TOSS},
    {MOVE_COUNTER,       FLAG_TUTOR_COUNTER},
    {MOVE_METRONOME,     FLAG_TUTOR_METRONOME},
    {MOVE_MIMIC,         FLAG_TUTOR_MIMIC},
    {MOVE_BODY_SLAM,     FLAG_TUTOR_BODY_SLAM},
    {MOVE_FRENZY_PLANT,  FLAG_TUTOR_FRENZY_PLANT},
    {MOVE_BLAST_BURN,    FLAG_TUTOR_BLAST_BURN},
    {MOVE_HYDRO_CANNON,  FLAG_TUTOR_HYDRO_CANNON},
};

u32 KJH_LibraryLevel(struct BoxPokemon *boxMon)
{
    if (FlagGet(FLAG_SYS_GAME_CLEAR))
        return MAX_LEVEL;
    return max(GetBoxMonData(boxMon, MON_DATA_PEAK_LEVEL), GetLevelFromBoxMonExp(boxMon));
}

bool32 KJH_HasEggMovesInLibrary(struct BoxPokemon *boxMon)
{
    u32 peak = max(GetBoxMonData(boxMon, MON_DATA_PEAK_BOND),
                   KJH_FriendshipToBond(GetBoxMonData(boxMon, MON_DATA_FRIENDSHIP)));
    return peak >= KJH_LIBRARY_EGG_MOVES_BOND;
}

bool32 KJH_IsTutorMoveInLibrary(u32 move)
{
    for (u32 i = 0; i < ARRAY_COUNT(sKantoTutors); i++)
    {
        if (sKantoTutors[i].move == move)
            return FlagGet(sKantoTutors[i].flag);
    }
    return FALSE;
}

static bool32 IsLevelUpMoveUpTo(u32 species, u32 move, u32 level)
{
    do
    {
        const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END && learnset[i].level <= level; i++)
        {
            if (learnset[i].move == move)
                return TRUE;
        }
        species = GetSpeciesPreEvolution(species);
    } while (species != SPECIES_NONE);
    return FALSE;
}

static bool32 IsEggMove(u32 species, u32 move)
{
    const u16 *eggMoves;

    while (GetSpeciesPreEvolution(species) != SPECIES_NONE)
        species = GetSpeciesPreEvolution(species);
    eggMoves = GetSpeciesEggMoves(species);
    for (u32 i = 0; eggMoves[i] != MOVE_UNAVAILABLE; i++)
    {
        if (eggMoves[i] == move)
            return TRUE;
    }
    return FALSE;
}

static bool32 IsTmInBag(u32 move)
{
    u32 item = GetTMHMItemIdFromMoveId(move);
    return item != ITEM_NONE && CheckBagHasItem(item, 1);
}

bool32 KJH_IsMoveInLibrary(struct BoxPokemon *boxMon, u32 move)
{
    u32 species = GetBoxMonData(boxMon, MON_DATA_SPECIES);

    if (move == MOVE_NONE)
        return FALSE;
    if (IsLevelUpMoveUpTo(species, move, KJH_LibraryLevel(boxMon)))
        return TRUE;
    if (KJH_HasEggMovesInLibrary(boxMon) && IsEggMove(species, move))
        return TRUE;
    if (CanLearnTeachableMove(species, move) && (IsTmInBag(move) || KJH_IsTutorMoveInLibrary(move)))
        return TRUE;
    return FALSE;
}

// Collect from learnsets, not by asking about every possible move. The bitmap
// deduplicates sources and preserves the old ascending-ID truncation order.
u32 KJH_GetUnknownLibraryMoves(struct BoxPokemon *boxMon, u16 *moves, u32 maxMoves)
{
    u8 eligible[(MOVES_COUNT + 7) / 8] = {0};
    u32 species = GetBoxMonData(boxMon, MON_DATA_SPECIES);
    u32 ancestor = species, baseSpecies, level = KJH_LibraryLevel(boxMon);
    u32 count = 0;

    do
    {
        const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(ancestor);
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END && learnset[i].level <= level; i++)
        {
            u32 move = learnset[i].move;
            if (move < MOVES_COUNT)
                eligible[move / 8] |= 1 << (move % 8);
        }
        baseSpecies = ancestor;
        ancestor = GetSpeciesPreEvolution(ancestor);
    } while (ancestor != SPECIES_NONE);

    if (KJH_HasEggMovesInLibrary(boxMon))
    {
        const u16 *eggMoves = GetSpeciesEggMoves(baseSpecies);
        for (u32 i = 0; eggMoves[i] != MOVE_UNAVAILABLE; i++)
        {
            u32 move = eggMoves[i];
            if (move < MOVES_COUNT)
                eligible[move / 8] |= 1 << (move % 8);
        }
    }
    if (species != SPECIES_EGG)
    {
        const u16 *teachable = GetSpeciesTeachableLearnset(species);
        for (u32 i = 0; teachable[i] != MOVE_UNAVAILABLE; i++)
        {
            u32 move = teachable[i];
            if (move < MOVES_COUNT && (IsTmInBag(move) || KJH_IsTutorMoveInLibrary(move)))
                eligible[move / 8] |= 1 << (move % 8);
        }
    }
    for (u32 slot = 0; slot < MAX_MON_MOVES; slot++)
    {
        u32 move = GetBoxMonData(boxMon, MON_DATA_MOVE1 + slot);
        if (move < MOVES_COUNT)
            eligible[move / 8] &= ~(1 << (move % 8));
    }
    for (u32 move = 1; move < MOVES_COUNT && count < maxMoves; move++)
        if (eligible[move / 8] & (1 << (move % 8)))
            moves[count++] = move;
    return count;
}

u32 KJH_GetNewLevelUpMoves(u32 species, u32 fromLevel, u32 toLevel, u16 *moves, u32 maxMoves)
{
    u32 count = 0;

    do
    {
        const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);
        for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END && count < maxMoves; i++)
        {
            u32 j;
            if (learnset[i].level <= fromLevel || learnset[i].level > toLevel)
                continue;
            if (IsLevelUpMoveUpTo(species, learnset[i].move, fromLevel)) // already reachable another way
                continue;
            for (j = 0; j < count && moves[j] != learnset[i].move; j++)
                ;
            if (j == count)
                moves[count++] = learnset[i].move;
        }
        species = GetSpeciesPreEvolution(species);
    } while (species != SPECIES_NONE && count < maxMoves);
    return count;
}

bool32 KJH_AreMovesLocked(void)
{
    return FlagGet(FLAG_KJH_MOVES_LOCKED);
}

void KJH_LockMoves(void)
{
    FlagSet(FLAG_KJH_MOVES_LOCKED);
}

void KJH_UnlockMoves(void)
{
    FlagClear(FLAG_KJH_MOVES_LOCKED);
}

bool32 KJH_HasPendingMoveReview(void)
{
    return VarGet(VAR_KJH_MOVE_REVIEW_PENDING) != 0;
}

void KJH_ClearMoveReview(void)
{
    VarSet(VAR_KJH_MOVE_REVIEW_PENDING, 0);
}

// Persist the last offered party growth state: declining must survive saving/loading.
// Moves themselves are deliberately excluded so teaching or declining does not nag.
bool32 KJH_CheckMoveReview(void)
{
    u32 signature = 17;
    bool32 hasMon = FALSE;
    if (KJH_AreMovesLocked())
        return FALSE;
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        u32 species = GetMonData(mon, MON_DATA_SPECIES);
        if (species == SPECIES_NONE || GetMonData(mon, MON_DATA_IS_EGG))
            continue;
        hasMon = TRUE;
        signature += species * 31 + KJH_LibraryLevel(&mon->box) * 127
                   + GetMonData(mon, MON_DATA_PERSONALITY);
    }
    signature = (signature & 0xFFFF) | 1;
    if (!hasMon || VarGet(VAR_KJH_MOVE_REVIEW_SIGNATURE) == signature)
        return FALSE;
    VarSet(VAR_KJH_MOVE_REVIEW_SIGNATURE, signature);
    VarSet(VAR_KJH_MOVE_REVIEW_PENDING, 1);
    return TRUE;
}

#define NEW_MOVES_LISTED 3 // names in the message; more become "..."

// Special, for EventScript_KjhLibraryNewMoves: from party slot VAR_0x8004 on, the next Pokemon whose library gained
// level-up moves between team levels VAR_0x8005 and VAR_0x8006 gets "{NAME} can now use A, B, C..." in gStringVar4;
// VAR_0x8004 moves past it. FALSE when no Pokemon is left.
u16 KJH_BufferNextNewLibraryMoves(void)
{
    u16 moves[16];

    while (gSpecialVar_0x8004 < PARTY_SIZE)
    {
        struct Pokemon *mon = &gPlayerParty[gSpecialVar_0x8004++];
        u32 species = GetMonData(mon, MON_DATA_SPECIES), count;
        u8 *end;

        if (species == SPECIES_NONE || GetMonData(mon, MON_DATA_IS_EGG))
            continue;
        bool32 emptySlot = FALSE;
        for (u32 slot = 0; slot < MAX_MON_MOVES; slot++)
            if (GetMonData(mon, MON_DATA_MOVE1 + slot) == MOVE_NONE)
                emptySlot = TRUE;
        // An incomplete moveset also deserves an offer for older library moves.
        if (!emptySlot && GetMonData(mon, MON_DATA_PEAK_LEVEL) > gSpecialVar_0x8006)
            continue;
        if (emptySlot)
        {
            count = KJH_GetUnknownLibraryMoves(&mon->box, moves, ARRAY_COUNT(moves));
        }
        else
        {
            count = KJH_GetNewLevelUpMoves(species, gSpecialVar_0x8005,
                                         min(KJH_LibraryLevel(&mon->box), gSpecialVar_0x8006),
                                         moves, ARRAY_COUNT(moves));
            for (u32 i = 0; i < count; )
            {
                bool32 known = FALSE;
                for (u32 slot = 0; slot < MAX_MON_MOVES; slot++)
                    if (GetMonData(mon, MON_DATA_MOVE1 + slot) == moves[i])
                        known = TRUE;
                if (known)
                    moves[i] = moves[--count];
                else
                    i++;
            }
        }
        if (count == 0)
            continue;
        GetMonNickname(mon, gStringVar4);
        end = StringAppend(gStringVar4, COMPOUND_STRING(" can now use\n"));
        for (u32 i = 0; i < count && i < NEW_MOVES_LISTED; i++)
        {
            if (i != 0)
                end = StringAppend(end, COMPOUND_STRING(", "));
            end = StringAppend(end, GetMoveName(moves[i]));
        }
        StringAppend(end, count > NEW_MOVES_LISTED ? COMPOUND_STRING("...!") : COMPOUND_STRING("!"));
        return TRUE;
    }
    return FALSE;
}

u32 KJH_PpAfterSwap(u32 newMaxPP, u32 oldPP, u32 oldMaxPP)
{
    if (oldMaxPP == 0)
        return newMaxPP;
    return newMaxPP * min(oldPP, oldMaxPP) / oldMaxPP;
}
