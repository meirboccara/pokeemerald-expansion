@ KJH: translated from pokecrystal maps/TinTower4F.asm by kjh_tools/johto

JohtoTinTower4F_MapScripts::
	.byte 0

J_TinTower4F_MapScripts::
J_TinTower4FUltraBall::
	finditem ITEM_ULTRA_BALL, 1
	return
J_TinTower4FPPUp::
	finditem ITEM_PP_UP, 1
	return
J_TinTower4FEscapeRope::
	finditem ITEM_ESCAPE_ROPE, 1
	return
J_TinTower4FHiddenMaxPotion::
	finditem ITEM_MAX_POTION
	return
J_TinTower4F_MapEvents::
