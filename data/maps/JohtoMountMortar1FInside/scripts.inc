@ KJH: translated from pokecrystal maps/MountMortar1FInside.asm by kjh_tools/johto

JohtoMountMortar1FInside_MapScripts::
	.byte 0

J_W_MountMortar1FBoulder::
	lock
	call J_MountMortar1FBoulder
	release
	end

J_T_TrainerPokemaniacMiller::
	trainerbattle_single TRAINER_J_POKEMANIAC_MILLER, J_PokemaniacMillerSeenText, J_PokemaniacMillerBeatenText
	call J_TrainerPokemaniacMiller_Script
	release
	end

J_T_TrainerSupernerdMarkus::
	trainerbattle_single TRAINER_J_SUPER_NERD_MARKUS, J_SupernerdMarkusSeenText, J_SupernerdMarkusBeatenText
	call J_TrainerSupernerdMarkus_Script
	release
	end

J_MountMortar1FInside_MapScripts::
J_TrainerPokemaniacMiller::
J_TrainerPokemaniacMiller_Script:
	message J_PokemaniacMillerAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSupernerdMarkus::
J_TrainerSupernerdMarkus_Script:
	message J_SupernerdMarkusAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MountMortar1FBoulder::
	goto EventScript_StrengthBoulder
J_MountMortar1FInsideEscapeRope::
	finditem ITEM_ESCAPE_ROPE, 1
	return
J_MountMortar1FInsideMaxRevive::
	finditem ITEM_MAX_REVIVE, 1
	return
J_MountMortar1FInsideHyperPotion::
	finditem ITEM_HYPER_POTION, 1
	return
J_MountMortar1FInsideMaxPotion::
	finditem ITEM_MAX_POTION, 1
	return
J_MountMortar1FInsideNugget::
	finditem ITEM_NUGGET, 1
	return
J_MountMortar1FInsideIron::
	finditem ITEM_IRON, 1
	return
J_MountMortar1FInsideUltraBall::
	finditem ITEM_ULTRA_BALL, 1
	return
J_MountMortar1FInsideHiddenMaxRepel::
	finditem ITEM_MAX_REPEL
	return
J_PokemaniacMillerSeenText::
	.string "I'm not losing\nthis time!$"
J_PokemaniacMillerBeatenText::
	.string "I lost to some\nkid…?$"
J_PokemaniacMillerAfterBattleText::
	.string "A while back, this\nkarate dude wanted\pto battle. He was\nridiculously good.\pHe just thrashed\nus silly.\pHe went in deeper\nsaying it was for\phis training. I\nwonder how he is?$"
J_SupernerdMarkusSeenText::
	.string "Hey! HUGH!$"
J_SupernerdMarkusBeatenText::
	.string "I mistook you for\nsomeone else…$"
J_SupernerdMarkusAfterBattleText::
	.string "I came to explore\nMT.MORTAR, but I\pgot separated from\nmy partner…\pDid you run into a\ntrainer who uses a\pSEADRA that knows\nWATERFALL?$"
J_MountMortar1FInside_MapEvents::
