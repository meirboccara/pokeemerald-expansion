#ifndef GUARD_KJH_CHARMS_H
#define GUARD_KJH_CHARMS_H

// KJH: the Shiny Charm and the Oval Charm (CF-3). Prof. Oak gives the Shiny Charm once every species of
// sShinyCharmDex (src/kjh_charms.c) is caught; the Day Care man gives the Oval Charm once an egg has hatched.

u32 KJH_ShinyCharmSpeciesCount(void);
u16 KJH_ShinyCharmSpeciesLeft(void);   // special: also buffers the number in gStringVar1
u16 KJH_HasHatchedAnEgg(void);         // special

#endif // GUARD_KJH_CHARMS_H
