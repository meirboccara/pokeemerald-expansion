@ KJH: translated from pokecrystal maps/MountMortar2FInside.asm by kjh_tools/johto

JohtoMountMortar2FInside_MapScripts::
	.byte 0

J_T_TrainerSupernerdHugh::
	trainerbattle_single TRAINER_J_SUPER_NERD_HUGH, J_SupernerdHughSeenText, J_SupernerdHughBeatenText
	call J_TrainerSupernerdHugh_Script
	release
	end

J_MountMortar2FInside_MapScripts::
J_TrainerSupernerdHugh::
J_TrainerSupernerdHugh_Script:
	message J_SupernerdHughAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MountMortar2FInsideMaxPotion::
	finditem ITEM_MAX_POTION, 1
	return
J_MountMortar2FInsideRareCandy::
	finditem ITEM_RARE_CANDY, 1
	return
J_MountMortar2FInsideTMDefenseCurl::
	finditem ITEM_RARE_CANDY, 1
	return
J_MountMortar2FInsideDragonScale::
	finditem ITEM_DRAGON_SCALE, 1
	return
J_MountMortar2FInsideElixer::
	finditem ITEM_ELIXIR, 1
	return
J_MountMortar2FInsideEscapeRope::
	finditem ITEM_ESCAPE_ROPE, 1
	return
J_MountMortar2FInsideHiddenFullRestore::
	finditem ITEM_FULL_RESTORE
	return
J_SupernerdHughSeenText::
	.string "Yo! MARKUS!$"
J_SupernerdHughBeatenText::
	.string "Sorry, my mistake.$"
J_SupernerdHughAfterBattleText::
	.string "I'm investigating\nMT.MORTAR, but my\lpal's gone AWOL.\pHave you seen a\ntrainer who has a\pSLOWPOKE that can\nuse STRENGTH?$"
J_MountMortar2FInside_MapEvents::
