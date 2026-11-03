@ KJH: translated from pokecrystal maps/WhirlIslandB1F.asm by kjh_tools/johto

JohtoWhirlIslandB1F_MapScripts::
	.byte 0

J_W_WhirlIslandB1FBoulder::
	lock
	call J_WhirlIslandB1FBoulder
	release
	end

J_WhirlIslandB1F_MapScripts::
J_WhirlIslandB1FFullRestore::
	finditem ITEM_FULL_RESTORE, 1
	return
J_WhirlIslandB1FCarbos::
	finditem ITEM_CARBOS, 1
	return
J_WhirlIslandB1FCalcium::
	finditem ITEM_CALCIUM, 1
	return
J_WhirlIslandB1FNugget::
	finditem ITEM_NUGGET, 1
	return
J_WhirlIslandB1FEscapeRope::
	finditem ITEM_ESCAPE_ROPE, 1
	return
J_WhirlIslandB1FBoulder::
	goto EventScript_StrengthBoulder
J_WhirlIslandB1FHiddenRareCandy::
	finditem ITEM_RARE_CANDY
	return
J_WhirlIslandB1FHiddenUltraBall::
	finditem ITEM_ULTRA_BALL
	return
J_WhirlIslandB1FHiddenFullRestore::
	finditem ITEM_FULL_RESTORE
	return
J_WhirlIslandB1F_MapEvents::
