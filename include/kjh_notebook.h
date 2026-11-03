#ifndef GUARD_KJH_NOTEBOOK_H
#define GUARD_KJH_NOTEBOOK_H

// KJH (LV-12): the training notebook's entries, kept in struct PokemonStorage (include/kjh_move_stars.h)

#define KJH_NOTEBOOK_SIZE    100

struct KjhNotebookEntry
{
    u32 personality; // the Pokemon
    u16 move;
    u8 points;       // 0..KJH_MOVE_POINTS_MAX
    u8 unused;
};

#endif // GUARD_KJH_NOTEBOOK_H
