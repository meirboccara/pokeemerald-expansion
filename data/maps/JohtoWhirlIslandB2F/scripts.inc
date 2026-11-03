@ KJH: translated from pokecrystal maps/WhirlIslandB2F.asm by kjh_tools/johto

JohtoWhirlIslandB2F_MapScripts::
	.byte 0

J_WhirlIslandB2F_MapScripts::
J_WhirlIslandB2FFullRestore::
	finditem ITEM_FULL_RESTORE, 1
	return
J_WhirlIslandB2FMaxRevive::
	finditem ITEM_MAX_REVIVE, 1
	return
J_WhirlIslandB2FMaxElixer::
	finditem ITEM_MAX_ELIXIR, 1
	return
J_WhirlIslandB2F_MapEvents::
