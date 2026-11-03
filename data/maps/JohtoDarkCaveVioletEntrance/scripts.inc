@ KJH: translated from pokecrystal maps/DarkCaveVioletEntrance.asm by kjh_tools/johto

JohtoDarkCaveVioletEntrance_MapScripts::
	.byte 0

J_W_DarkCaveVioletEntranceRock::
	lock
	call J_DarkCaveVioletEntranceRock
	release
	end

J_DarkCaveVioletEntrance_MapScripts::
J_DarkCaveVioletEntrancePotion::
	finditem ITEM_POTION, 1
	return
J_DarkCaveVioletEntranceFullHeal::
	finditem ITEM_FULL_HEAL, 1
	return
J_DarkCaveVioletEntranceHyperPotion::
	finditem ITEM_HYPER_POTION, 1
	return
J_DarkCaveVioletEntranceDireHit::
	finditem ITEM_DIRE_HIT, 1
	return
J_DarkCaveVioletEntranceRock::
	goto EventScript_RockSmash
J_DarkCaveVioletEntranceHiddenElixer::
	finditem ITEM_ELIXIR
	return
J_DarkCaveVioletEntrance_MapEvents::
