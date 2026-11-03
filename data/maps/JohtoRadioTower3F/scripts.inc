@ KJH: translated from pokecrystal maps/RadioTower3F.asm by kjh_tools/johto

JohtoRadioTower3F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, JohtoRadioTower3F_OnLoad
	.byte 0

JohtoRadioTower3F_OnLoad:
	call J_RadioTower3FCardKeyShutterCallback
	end

J_W_RadioTower3FSuperNerdScript::
	lock
	call J_RadioTower3FSuperNerdScript
	release
	end

J_W_RadioTower3FGymGuideScript::
	lock
	call J_RadioTower3FGymGuideScript
	release
	end

J_W_RadioTower3FCooltrainerFScript::
	lock
	call J_RadioTower3FCooltrainerFScript
	release
	end

J_T_TrainerGruntM7::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_7, J_GruntM7SeenText, J_GruntM7BeatenText
	call J_TrainerGruntM7_Script
	release
	end

J_T_TrainerGruntM8::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_8, J_GruntM8SeenText, J_GruntM8BeatenText
	call J_TrainerGruntM8_Script
	release
	end

J_T_TrainerGruntM9::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_9, J_GruntM9SeenText, J_GruntM9BeatenText
	call J_TrainerGruntM9_Script
	release
	end

J_T_TrainerScientistMarc::
	trainerbattle_single TRAINER_J_SCIENTIST_MARC, J_ScientistMarcSeenText, J_ScientistMarcBeatenText
	call J_TrainerScientistMarc_Script
	release
	end

J_S_RadioTower3FPersonnelSign::
	lockall
	call J_RadioTower3FPersonnelSign
	releaseall
	end

J_S_RadioTower3FPokemonMusicSign::
	lockall
	call J_RadioTower3FPokemonMusicSign
	releaseall
	end

J_S_CardKeySlotScript::
	lockall
	call J_CardKeySlotScript
	releaseall
	end

J_RadioTower3F_MapScripts::
J_RadioTower3FCardKeyShutterCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_USED_THE_CARD_KEY_IN_THE_RADIO_TOWER, J_L102
	setvar VAR_RESULT, 1
J_L102:
	goto_if_ne VAR_RESULT, 0, J_RadioTower3FCardKeyShutterCallback_Change
	return
J_RadioTower3FCardKeyShutterCallback_Change:
	setmetatile 14, 2, 48, TRUE
	setmetatile 15, 2, 1, TRUE
	setmetatile 14, 3, 52, FALSE
	setmetatile 15, 3, 6, FALSE
	setmetatile 14, 4, 6, FALSE
	setmetatile 15, 4, 6, FALSE
	setmetatile 14, 5, 6, FALSE
	setmetatile 15, 5, 6, FALSE
	return
J_RadioTower3FSuperNerdScript::
	faceplayer
	message J_RadioTower3FSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower3FGymGuideScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L103
	setvar VAR_RESULT, 1
J_L103:
	goto_if_ne VAR_RESULT, 0, J_RadioTower3FGymGuideScript_NoRockets
	message J_RadioTower3FGymGuideText_Rockets
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower3FGymGuideScript_NoRockets:
	message J_RadioTower3FGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower3FCooltrainerFScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_SUNNY_DAY_FROM_RADIO_TOWER, J_L104
	setvar VAR_RESULT, 1
J_L104:
	goto_if_ne VAR_RESULT, 0, J_RadioTower3FCooltrainerFScript_GotSunnyDay
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L105
	setvar VAR_RESULT, 1
J_L105:
	goto_if_ne VAR_RESULT, 0, J_RadioTower3FCooltrainerFScript_NoRockets
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_USED_THE_CARD_KEY_IN_THE_RADIO_TOWER, J_L106
	setvar VAR_RESULT, 1
J_L106:
	goto_if_ne VAR_RESULT, 0, J_RadioTower3FCooltrainerFScript_UsedCardKey
	message J_RadioTower3FCooltrainerFPleaseSaveDirectorText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower3FCooltrainerFScript_UsedCardKey:
	message J_RadioTower3FCooltrainerFIsDirectorSafeText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower3FCooltrainerFScript_NoRockets:
	message J_RadioTower3FCooltrainerFYoureMyHeroText
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM11, 1
	goto_if_eq VAR_RESULT, 0, J_RadioTower3FCooltrainerFScript_NoRoom
	message J_RadioTower3FCooltrainerFItsSunnyDayText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_GOT_SUNNY_DAY_FROM_RADIO_TOWER
	return
J_RadioTower3FCooltrainerFScript_GotSunnyDay:
	message J_RadioTower3FCooltrainerFYouWereMarvelousText
	waitmessage
	waitbuttonpress
J_RadioTower3FCooltrainerFScript_NoRoom:
	closemessage
	return
J_TrainerGruntM7::
J_TrainerGruntM7_Script:
	message J_GruntM7AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM8::
J_TrainerGruntM8_Script:
	message J_GruntM8AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM9::
J_TrainerGruntM9_Script:
	message J_GruntM9AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerScientistMarc::
J_TrainerScientistMarc_Script:
	message J_ScientistMarcAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CardKeySlotScript::
	message J_RadioTower3FCardKeySlotText
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_USED_THE_CARD_KEY_IN_THE_RADIO_TOWER, J_L107
	setvar VAR_RESULT, 1
J_L107:
	goto_if_ne VAR_RESULT, 0, J_CardKeySlotScript_UsedCardKey
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_CARD_KEY, J_L108
	setvar VAR_RESULT, 1
J_L108:
	goto_if_ne VAR_RESULT, 0, J_CardKeySlotScript_HaveCardKey
J_CardKeySlotScript_UsedCardKey:
	closemessage
	return
J_CardKeySlotScript_HaveCardKey:
	message J_InsertedTheCardKeyText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_USED_THE_CARD_KEY_IN_THE_RADIO_TOWER
	playse SE_DOOR
	setmetatile 14, 2, 48, TRUE
	setmetatile 15, 2, 1, TRUE
	setmetatile 14, 3, 52, FALSE
	setmetatile 15, 3, 6, FALSE
	setmetatile 14, 4, 6, FALSE
	setmetatile 15, 4, 6, FALSE
	setmetatile 14, 5, 6, FALSE
	setmetatile 15, 5, 6, FALSE
	special DrawWholeMapView
	closemessage
	waitse
	return
J_RadioTower3FPersonnelSign::
	message J_RadioTower3FPersonnelSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower3FPokemonMusicSign::
	message J_RadioTower3FPokemonMusicSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower3FSuperNerdText::
	.string "We have recordings\nof the cries of\pall POKéMON that\nhave been found.\pWe must have about\n200 kinds.$"
J_RadioTower3FGymGuideText_Rockets::
	.string "To trainers, POKé-\nMON are their\lbeloved partners.\pIt's terrible how\nTEAM ROCKET is\ptrying to control\nPOKéMON.$"
J_RadioTower3FGymGuideText::
	.string "We run 24 hours a\nday to broadcast\pentertaining pro-\ngrams.\pI'll do my best to\nrun around the\lclock too!$"
J_RadioTower3FCooltrainerFPleaseSaveDirectorText::
	.string "The TEAM ROCKET\nboss has locked\lhimself in.\pBut the DIRECTOR\ncan open it.\pHe's up on the\nfifth floor.\pPlease save him!$"
J_RadioTower3FCooltrainerFIsDirectorSafeText::
	.string "Is the DIRECTOR\nsafe?$"
J_RadioTower3FCooltrainerFYoureMyHeroText::
	.string "Thank you!\nYou're my hero!\pThis is a token of\nmy appreciation.$"
J_RadioTower3FCooltrainerFItsSunnyDayText::
	.string "It's SUNNY DAY.\nIt powers up fire-\ltype moves for a\lwhile.$"
J_RadioTower3FCooltrainerFYouWereMarvelousText::
	.string "You were simply\nmarvelous!$"
J_GruntM7SeenText::
	.string "I've been given\nstrict orders.\pI'm to crush any-\none who challenges\lTEAM ROCKET!$"
J_GruntM7BeatenText::
	.string "What?!$"
J_GruntM7AfterBattleText::
	.string "I failed in my\nduties…\pI'll be docked pay\nfor this…$"
J_GruntM8SeenText::
	.string "It feels great\nordering POKéMON\lto commit crimes.$"
J_GruntM8BeatenText::
	.string "You're kidding!$"
J_GruntM8AfterBattleText::
	.string "I feel lousy over\nlosing!\pDarn it! I hate\nuseless POKéMON!$"
J_GruntM9SeenText::
	.string "Why did the shut-\nter open? Did you\phave something to\ndo with this?$"
J_GruntM9BeatenText::
	.string "I'm done for!$"
J_GruntM9AfterBattleText::
	.string "What?! You made it\npast our men in\lthe UNDERGROUND?\pHow could you?$"
J_ScientistMarcSeenText::
	.string "An unknown child\nwandering here?\pWho are you?$"
J_ScientistMarcBeatenText::
	.string "Tch! I took you\ntoo lightly!$"
J_ScientistMarcAfterBattleText::
	.string "Bwahahaha…\pI can transmit as\nstrong a signal as\lI need from here.$"
J_RadioTower3FCardKeySlotText::
	.string "It's the CARD KEY\nslot.$"
J_InsertedTheCardKeyText::
	.string "{PLAYER} inserted\nthe CARD KEY.$"
J_RadioTower3FPersonnelSignText::
	.string "3F PERSONNEL$"
J_RadioTower3FPokemonMusicSignText::
	.string "POKéMON MUSIC with\nHost DJ BEN$"
J_RadioTower3F_MapEvents::
