#ifndef GUARD_CONSTANTS_KJH_PACK_H
#define GUARD_CONSTANTS_KJH_PACK_H

// KJH: the steps of a wild pack's call for help, for the kjhpack battle script command (src/kjh_pack.c, BS_KjhPack)
#define KJH_PACK_OP_ANSWER          0 // someone answers the call (a helper joins the party), else jump
#define KJH_PACK_OP_JUMP_IF_WAITING 1 // both wild slots are taken: the helper waits, jump
#define KJH_PACK_OP_JUMP_IF_DOUBLE  2 // already a double battle: jump
#define KJH_PACK_OP_TO_DOUBLE       3 // fade out, turn the battle into a double battle, rebuild the screen
#define KJH_PACK_OP_PREPARE_HELPER  4 // the scripting battler is the free wild slot, the newest helper goes there
#define KJH_PACK_OP_PREPARE_PARTNER 5 // the scripting battler is the player's right slot, else jump (nobody left)

#endif // GUARD_CONSTANTS_KJH_PACK_H
