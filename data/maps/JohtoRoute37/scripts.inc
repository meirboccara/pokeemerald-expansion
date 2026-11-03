@ KJH: translated from pokecrystal maps/Route37.asm by kjh_tools/johto

JohtoRoute37_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoRoute37_OnTransition
	.byte 0

JohtoRoute37_OnTransition:
	call J_Route37SunnyCallback
	end

J_T_TrainerTwinsAnnandanne1::
	trainerbattle_single TRAINER_J_TWINS_ANNANDANNE1, J_TwinsAnnandanne1SeenText, J_TwinsAnnandanne1BeatenText
	call J_TrainerTwinsAnnandanne1_Script
	release
	end

J_T_TrainerTwinsAnnandanne2::
	trainerbattle_single TRAINER_J_TWINS_ANNANDANNE2, J_TwinsAnnandanne2SeenText, J_TwinsAnnandanne2BeatenText
	call J_TrainerTwinsAnnandanne2_Script
	release
	end

J_T_TrainerPsychicGreg::
	trainerbattle_single TRAINER_J_PSYCHIC_T_GREG, J_PsychicGregSeenText, J_PsychicGregBeatenText
	call J_TrainerPsychicGreg_Script
	release
	end

J_W_Route37FruitTree1::
	lock
	call J_Route37FruitTree1
	release
	end

J_W_SunnyScript::
	lock
	call J_SunnyScript
	release
	end

J_W_Route37FruitTree2::
	lock
	call J_Route37FruitTree2
	release
	end

J_W_Route37FruitTree3::
	lock
	call J_Route37FruitTree3
	release
	end

J_S_Route37Sign::
	lockall
	call J_Route37Sign
	releaseall
	end

J_Route37_MapScripts::
J_Route37SunnyCallback::
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J_Route37SunnyCallback_SunnyAppears
	setflag FLAG_J_ROUTE_37_SUNNY_OF_SUNDAY
	return
J_Route37SunnyCallback_SunnyAppears:
	clearflag FLAG_J_ROUTE_37_SUNNY_OF_SUNDAY
	return
J_TrainerTwinsAnnandanne1::
J_TrainerTwinsAnnandanne1_Script:
	message J_TwinsAnnandanne1AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerTwinsAnnandanne2::
J_TrainerTwinsAnnandanne2_Script:
	message J_TwinsAnnandanne2AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPsychicGreg::
J_TrainerPsychicGreg_Script:
	message J_PsychicGregAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SunnyScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_MAGNET_FROM_SUNNY, J_L445
	setvar VAR_RESULT, 1
J_L445:
	goto_if_ne VAR_RESULT, 0, J_SunnySundayScript
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_ne VAR_RESULT, 0, J_SunnyNotSundayScript
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_MET_SUNNY_OF_SUNDAY, J_L446
	setvar VAR_RESULT, 1
J_L446:
	goto_if_ne VAR_RESULT, 0, J_SunnyScript_MetSunny
	message J_MeetSunnyText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_MET_SUNNY_OF_SUNDAY
J_SunnyScript_MetSunny:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_PLAYER_IS_FEMALE, J_L447
	setvar VAR_RESULT, 1
J_L447:
	goto_if_ne VAR_RESULT, 0, J_SunnyScript_Kris
	message J_SunnyGivesGiftText1
	waitmessage
	waitbuttonpress
	goto J_SunnyScript_next
J_SunnyScript_Kris:
	message J_SunnyGivesGiftText2
	waitmessage
	waitbuttonpress
J_SunnyScript_next:
	giveitem ITEM_MAGNET, 1
	goto_if_eq VAR_RESULT, 0, J_SunnyDoneScript
	setflag FLAG_J_GOT_MAGNET_FROM_SUNNY
	message J_SunnyGaveGiftText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SunnySundayScript::
	message J_SunnySundayText
	waitmessage
	waitbuttonpress
J_SunnyDoneScript::
	closemessage
	return
J_SunnyNotSundayScript::
	message J_SunnyNotSundayText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route37Sign::
	message J_Route37SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route37FruitTree1::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_Route37FruitTree2::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_Route37FruitTree3::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_Route37HiddenEther::
	finditem ITEM_ETHER
	return
J_TwinsAnnandanne1SeenText::
	.string "ANN: ANNE and I\nare in this to-\lgether!$"
J_TwinsAnnandanne1BeatenText::
	.string "ANN & ANNE: Nnn… A\nlittle too strong.$"
J_TwinsAnnandanne1AfterBattleText::
	.string "ANN: I can tell\nwhat my sister and\pmy POKéMON are\nthinking.$"
J_TwinsAnnandanne2SeenText::
	.string "ANNE: ANN and I\nare in this to-\lgether!$"
J_TwinsAnnandanne2BeatenText::
	.string "ANN & ANNE: Nnn… A\nlittle too strong.$"
J_TwinsAnnandanne2AfterBattleText::
	.string "ANNE: We share the\nsame feelings as\lour POKéMON.$"
J_PsychicGregSeenText::
	.string "POKéMON can't do a\nthing if they are\lasleep.\pI'll show you how\nscary that is!$"
J_PsychicGregBeatenText::
	.string "I lost. That's\npretty sad…$"
J_PsychicGregAfterBattleText::
	.string "Putting POKéMON to\nsleep or paralyz-\ling them are good\lbattle techniques.$"
J_MeetSunnyText::
	.string "SUNNY: Hi!\pI'm SUNNY of Sun-\nday, meaning it's\lSunday today!$"
J_SunnyGivesGiftText1::
	.string "I was told to give\nyou this if I saw\lyou!$"
J_SunnyGivesGiftText2::
	.string "I was told to give\nyou this if I saw\lyou!$"
J_SunnyGaveGiftText::
	.string "SUNNY: That thing…\pUm…\p… What was it now…\p…\pOh! I remember\nnow!\pA POKéMON that\nknows electric\pmoves should hold\nit.\pMy sis MONICA said\nit powers up\lelectric moves!$"
J_SunnySundayText::
	.string "SUNNY: My sisters\nand brothers are\lMONICA, TUSCANY,\lWESLEY, ARTHUR,\lFRIEDA and SANTOS.\pThey're all older\nthan me!$"
J_SunnyNotSundayText::
	.string "SUNNY: Isn't today\nSunday?\lUm… I forgot!$"
J_Route37SignText::
	.string "ROUTE 37$"
J_Route37_MapEvents::
