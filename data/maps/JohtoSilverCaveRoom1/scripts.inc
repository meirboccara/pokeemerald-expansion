@ KJH: translated from pokecrystal maps/SilverCaveRoom1.asm by kjh_tools/johto

JohtoSilverCaveRoom1_MapScripts::
	.byte 0

J_SilverCaveRoom1_MapScripts::
J_SilverCaveRoom1MaxElixer::
	finditem ITEM_MAX_ELIXIR, 1
	return
J_SilverCaveRoom1Protein::
	finditem ITEM_PROTEIN, 1
	return
J_SilverCaveRoom1EscapeRope::
	finditem ITEM_ESCAPE_ROPE, 1
	return
J_SilverCaveRoom1UltraBall::
	finditem ITEM_ULTRA_BALL, 1
	return
J_SilverCaveRoom1HiddenDireHit::
	finditem ITEM_DIRE_HIT
	return
J_SilverCaveRoom1HiddenUltraBall::
	finditem ITEM_ULTRA_BALL
	return
J_SilverCaveRoom1_MapEvents::
