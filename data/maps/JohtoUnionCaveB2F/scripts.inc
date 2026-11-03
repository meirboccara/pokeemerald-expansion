@ KJH: translated from pokecrystal maps/UnionCaveB2F.asm by kjh_tools/johto

JohtoUnionCaveB2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoUnionCaveB2F_OnTransition
	.byte 0

JohtoUnionCaveB2F_OnTransition:
	call J_UnionCaveB2FLaprasCallback
	end

J_T_TrainerCooltrainermNick::
	trainerbattle_single TRAINER_J_COOLTRAINERM_NICK, J_CooltrainermNickSeenText, J_CooltrainermNickBeatenText
	call J_TrainerCooltrainermNick_Script
	release
	end

J_T_TrainerCooltrainerfGwen::
	trainerbattle_single TRAINER_J_COOLTRAINERF_GWEN, J_CooltrainerfGwenSeenText, J_CooltrainerfGwenBeatenText
	call J_TrainerCooltrainerfGwen_Script
	release
	end

J_T_TrainerCooltrainerfEmma::
	trainerbattle_single TRAINER_J_COOLTRAINERF_EMMA, J_CooltrainerfEmmaSeenText, J_CooltrainerfEmmaBeatenText
	call J_TrainerCooltrainerfEmma_Script
	release
	end

J_W_UnionCaveLapras::
	lock
	call J_UnionCaveLapras
	release
	end

J_UnionCaveB2F_MapScripts::
J_UnionCaveB2FLaprasCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_UNION_CAVE_LAPRAS, J_L138
	setvar VAR_RESULT, 1
J_L138:
	goto_if_ne VAR_RESULT, 0, J_UnionCaveB2FLaprasCallback_NoAppear
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 5, J_UnionCaveB2FLaprasCallback_Appear
J_UnionCaveB2FLaprasCallback_NoAppear:
	setflag FLAG_J_UNION_CAVE_B2F_LAPRAS
	return
J_UnionCaveB2FLaprasCallback_Appear:
	clearflag FLAG_J_UNION_CAVE_B2F_LAPRAS
	return
J_UnionCaveLapras::
	faceplayer
	playmoncry SPECIES_LAPRAS, CRY_MODE_NORMAL
	waitmoncry
	setwildbattle SPECIES_LAPRAS, 20
	dowildbattle
	removeobject 6
	setflag FLAG_J_ENGINE_UNION_CAVE_LAPRAS
	return
J_TrainerCooltrainermNick::
J_TrainerCooltrainermNick_Script:
	message J_CooltrainermNickAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainerfGwen::
J_TrainerCooltrainerfGwen_Script:
	message J_CooltrainerfGwenAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainerfEmma::
J_TrainerCooltrainerfEmma_Script:
	message J_CooltrainerfEmmaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_UnionCaveB2FElixer::
	finditem ITEM_ELIXIR, 1
	return
J_UnionCaveB2FHyperPotion::
	finditem ITEM_HYPER_POTION, 1
	return
J_CooltrainermNickSeenText::
	.string "There are two\nkinds of people.\pThose who have\nstyle, and those\lwho don't.\pWhat kind of\nperson are you?$"
J_CooltrainermNickBeatenText::
	.string "You've got\ndazzling style!$"
J_CooltrainermNickAfterBattleText::
	.string "Your POKéMON style\nis stunning and\lcolorful, I admit.\pYou'll just keep\ngetting better!$"
J_CooltrainerfGwenSeenText::
	.string "I'm in training.\nCare for a round?$"
J_CooltrainerfGwenBeatenText::
	.string "Aww, no! You're\ntoo good for me.$"
J_CooltrainerfGwenAfterBattleText::
	.string "I'm going to train\nby myself until I\limprove.$"
J_CooltrainerfEmmaSeenText::
	.string "If the POKéMON I\nliked were there,\lI'd go anywhere.\pThat's what a real\ntrainer does.$"
J_CooltrainerfEmmaBeatenText::
	.string "I'd rather pet my\nbabies than this!$"
J_CooltrainerfEmmaAfterBattleText::
	.string "Just once a week,\na POKéMON comes to\lthe water's edge.\pI wanted to see\nthat POKéMON…$"
J_UnionCaveB2F_MapEvents::
