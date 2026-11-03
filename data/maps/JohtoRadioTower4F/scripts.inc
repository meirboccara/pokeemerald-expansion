@ KJH: translated from pokecrystal maps/RadioTower4F.asm by kjh_tools/johto

JohtoRadioTower4F_MapScripts::
	.byte 0

J_W_RadioTower4FFisherScript::
	lock
	call J_RadioTower4FFisherScript
	release
	end

J_W_RadioTower4FDJMaryScript::
	lock
	call J_RadioTower4FDJMaryScript
	release
	end

J_W_RadioTowerMeowth::
	lock
	call J_RadioTowerMeowth
	release
	end

J_T_TrainerGruntM10::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_10, J_GruntM10SeenText, J_GruntM10BeatenText
	call J_TrainerGruntM10_Script
	release
	end

J_T_TrainerExecutivem2::
	trainerbattle_single TRAINER_J_EXECUTIVEM_EXECUTIVEM_2, J_Executivem2SeenText, J_Executivem2BeatenText
	call J_TrainerExecutivem2_Script
	release
	end

J_T_TrainerGruntF4::
	trainerbattle_single TRAINER_J_GRUNTF_GRUNTF_4, J_GruntF4SeenText, J_GruntF4BeatenText
	call J_TrainerGruntF4_Script
	release
	end

J_T_TrainerScientistRich::
	trainerbattle_single TRAINER_J_SCIENTIST_RICH, J_ScientistRichSeenText, J_ScientistRichBeatenText
	call J_TrainerScientistRich_Script
	release
	end

J_S_RadioTower4FProductionSign::
	lockall
	call J_RadioTower4FProductionSign
	releaseall
	end

J_S_RadioTower4FStudio2Sign::
	lockall
	call J_RadioTower4FStudio2Sign
	releaseall
	end

J_RadioTower4F_MapScripts::
J_RadioTower4FFisherScript::
	faceplayer
	message J_RadioTower4FFisherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower4FDJMaryScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_PINK_BOW_FROM_MARY, J_L109
	setvar VAR_RESULT, 1
J_L109:
	goto_if_ne VAR_RESULT, 0, J_RadioTower4FDJMaryScript_GotPinkBow
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L110
	setvar VAR_RESULT, 1
J_L110:
	goto_if_ne VAR_RESULT, 0, J_RadioTower4FDJMaryScript_ClearedRockets
	message J_RadioTower4FDJMaryText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower4FDJMaryScript_ClearedRockets:
	message J_RadioTower4FDJMaryText_ClearedRockets
	waitmessage
	waitbuttonpress
	giveitem ITEM_SILK_SCARF, 1
	goto_if_eq VAR_RESULT, 0, J_RadioTower4FDJMaryScript_NoRoom
	message J_RadioTower4FDJMaryText_GivePinkBow
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_GOT_PINK_BOW_FROM_MARY
	return
J_RadioTower4FDJMaryScript_GotPinkBow:
	message J_RadioTower4FDJMaryText_After
	waitmessage
	waitbuttonpress
J_RadioTower4FDJMaryScript_NoRoom:
	closemessage
	return
J_RadioTowerMeowth::
	message J_RadioTowerMeowthText
	waitmessage
	playmoncry SPECIES_MEOWTH, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM10::
J_TrainerGruntM10_Script:
	message J_GruntM10AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerExecutivem2::
J_TrainerExecutivem2_Script:
	message J_Executivem2AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntF4::
J_TrainerGruntF4_Script:
	message J_GruntF4AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerScientistRich::
J_TrainerScientistRich_Script:
	message J_ScientistRichAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower4FProductionSign::
	message J_RadioTower4FProductionSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower4FStudio2Sign::
	message J_RadioTower4FStudio2SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower4FFisherText::
	.string "I listened to the\nradio while I was\lat the RUINS.\pI heard a strange\nbroadcast there.$"
J_RadioTower4FDJMaryText::
	.string "MARY: Why? Why do\nI have to suffer\lthrough this?\pMEOWTH, help me!$"
J_RadioTower4FDJMaryText_ClearedRockets::
	.string "MARY: Oh! You're\nmy little savior!\pWill you take this\nas my thanks?$"
J_RadioTower4FDJMaryText_GivePinkBow::
	.string "MARY: It's just\nright for POKéMON\pthat know normal-\ntype moves.$"
J_RadioTower4FDJMaryText_After::
	.string "MARY: Please tune\ninto me on PROF.\pOAK'S POKéMON TALK\nshow.$"
J_RadioTowerMeowthText::
	.string "MEOWTH: Meowth…$"
J_GruntM10SeenText::
	.string "You plan to rescue\nthe DIRECTOR?\pThat won't be pos-\nsible because I'm\lgoing to beat you!$"
J_GruntM10BeatenText::
	.string "No! Unbelievable!$"
J_GruntM10AfterBattleText::
	.string "I don't believe\nit! I was beaten!$"
J_Executivem2SeenText::
	.string "Stop! I'm known as\nthe TEAM ROCKET\lfortress!\pYou're not taking\nanother step!$"
J_Executivem2BeatenText::
	.string "The fortress came\ndown!$"
J_Executivem2AfterBattleText::
	.string "You've earned my\nrespect, so here's\lsome advice.\pIt's not too late.\nYou can still turn\lback.$"
J_GruntF4SeenText::
	.string "Don't I think\nPOKéMON are cute?\pI'll think my\nPOKéMON are cute--\pafter they beat\nyours!$"
J_GruntF4BeatenText::
	.string "Oh, no! They're so\nuseless!$"
J_GruntF4AfterBattleText::
	.string "I love my\nbeautiful self!\pWho cares about\nPOKéMON?$"
J_ScientistRichSeenText::
	.string "Most excellent.\pThis RADIO TOWER\nwill fulfill our\lgrand design.$"
J_ScientistRichBeatenText::
	.string "Hmmm…\pAll grand plans\ncome with snags.$"
J_ScientistRichAfterBattleText::
	.string "Do you honestly\nbelieve you can\lstop TEAM ROCKET?$"
J_RadioTower4FProductionSignText::
	.string "4F PRODUCTION$"
J_RadioTower4FStudio2SignText::
	.string "4F STUDIO 2$"
J_RadioTower4F_MapEvents::
