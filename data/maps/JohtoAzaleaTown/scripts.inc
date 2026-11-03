@ KJH: translated from pokecrystal maps/AzaleaTown.asm by kjh_tools/johto

JohtoAzaleaTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoAzaleaTown_OnTransition
	.byte 0

JohtoAzaleaTown_OnTransition:
	call J_AzaleaTownFlypointCallback
	end

J_W_AzaleaTownRocket1Script::
	lock
	call J_AzaleaTownRocket1Script
	release
	end

J_W_AzaleaTownGrampsScript::
	lock
	call J_AzaleaTownGrampsScript
	release
	end

J_W_AzaleaTownTeacherScript::
	lock
	call J_AzaleaTownTeacherScript
	release
	end

J_W_AzaleaTownYoungsterScript::
	lock
	call J_AzaleaTownYoungsterScript
	release
	end

J_W_AzaleaTownSlowpokeScript::
	lock
	call J_AzaleaTownSlowpokeScript
	release
	end

J_W_WhiteApricornTree::
	lock
	call J_WhiteApricornTree
	release
	end

J_W_AzaleaTownRocket2Script::
	lock
	call J_AzaleaTownRocket2Script
	release
	end

J_W_AzaleaTownKurtScript::
	lock
	call J_AzaleaTownKurtScript
	release
	end

J_C_AzaleaTownRivalBattleScene1::
	lockall
	call J_AzaleaTownRivalBattleScene1
	releaseall
	end

J_C_AzaleaTownRivalBattleScene2::
	lockall
	call J_AzaleaTownRivalBattleScene2
	releaseall
	end

J_C_AzaleaTownCelebiScene::
	lockall
	call J_AzaleaTownCelebiScene
	releaseall
	end

J_S_AzaleaTownSign::
	lockall
	call J_AzaleaTownSign
	releaseall
	end

J_S_KurtsHouseSign::
	lockall
	call J_KurtsHouseSign
	releaseall
	end

J_S_AzaleaGymSign::
	lockall
	call J_AzaleaGymSign
	releaseall
	end

J_S_SlowpokeWellSign::
	lockall
	call J_SlowpokeWellSign
	releaseall
	end

J_S_CharcoalKilnSign::
	lockall
	call J_CharcoalKilnSign
	releaseall
	end

J_S_AzaleaTownPokecenterSign::
	lockall
	call J_AzaleaTownPokecenterSign
	releaseall
	end

J_S_AzaleaTownMartSign::
	lockall
	call J_AzaleaTownMartSign
	releaseall
	end

J_S_AzaleaTownIlextForestSign::
	lockall
	call J_AzaleaTownIlextForestSign
	releaseall
	end

J_AzaleaTown_MapScripts::
J_AzaleaTownNoop1Scene::
	return
J_AzaleaTownNoop2Scene::
	return
J_AzaleaTownNoop3Scene::
	return
J_AzaleaTownFlypointCallback::
	setflag FLAG_J_ENGINE_FLYPOINT_AZALEA
	return
J_AzaleaTownRivalBattleScene1::
	setobjectxyperm 10, 11, 11
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	fadeoutbgm 0
	delay 15
	addobject 10
	applymovement 10, J_AzaleaTownRivalBattleApproachMovement1
	waitmovement 10
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	goto J_AzaleaTownRivalBattleScript
J_AzaleaTownRivalBattleScene2::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	fadeoutbgm 0
	delay 15
	addobject 10
	applymovement 10, J_AzaleaTownRivalBattleApproachMovement2
	waitmovement 10
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
J_AzaleaTownRivalBattleScript::
	playbgm MUS_RG_ENCOUNTER_RIVAL, FALSE
	message J_AzaleaTownRivalBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_RIVAL_AZALEA_TOWN
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TOTODILE_FROM_ELM, J_L371
	setvar VAR_RESULT, 1
J_L371:
	goto_if_ne VAR_RESULT, 0, J_AzaleaTownRivalBattleScript_Totodile
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_CHIKORITA_FROM_ELM, J_L372
	setvar VAR_RESULT, 1
J_L372:
	goto_if_ne VAR_RESULT, 0, J_AzaleaTownRivalBattleScript_Chikorita
	setvar VAR_LAST_TALKED, 10
	trainerbattle_no_intro TRAINER_J_RIVAL1_RIVAL1_2_TOTODILE, J_AzaleaTownRivalWinText
	goto J_AzaleaTownRivalBattleScript_AfterBattle
J_AzaleaTownRivalBattleScript_Totodile:
	setvar VAR_LAST_TALKED, 10
	trainerbattle_no_intro TRAINER_J_RIVAL1_RIVAL1_2_CHIKORITA, J_AzaleaTownRivalWinText
	goto J_AzaleaTownRivalBattleScript_AfterBattle
J_AzaleaTownRivalBattleScript_Chikorita:
	setvar VAR_LAST_TALKED, 10
	trainerbattle_no_intro TRAINER_J_RIVAL1_RIVAL1_2_CYNDAQUIL, J_AzaleaTownRivalWinText
	goto J_AzaleaTownRivalBattleScript_AfterBattle
J_AzaleaTownRivalBattleScript_AfterBattle:
	playbgm MUS_RG_RIVAL_EXIT, FALSE
	message J_AzaleaTownRivalAfterText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement 10, J_AzaleaTownRivalBattleExitMovement
	waitmovement 10
	playse SE_EXIT
	removeobject 10
	setvar VAR_J_SCENE_AZALEA_TOWN, 0
	waitse
	fadedefaultbgm
	return
J_AzaleaTownRocket1Script::
	faceplayer
	message J_AzaleaTownRocket1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaTownRocket2Script::
	faceplayer
	message J_AzaleaTownRocket2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaTownGrampsScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_SLOWPOKE_WELL, J_L373
	setvar VAR_RESULT, 1
J_L373:
	goto_if_ne VAR_RESULT, 0, J_AzaleaTownGrampsScript_ClearedWell
	message J_AzaleaTownGrampsTextBefore
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaTownGrampsScript_ClearedWell:
	message J_AzaleaTownGrampsTextAfter
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaTownTeacherScript::
	faceplayer
	message J_AzaleaTownTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaTownYoungsterScript::
	faceplayer
	message J_AzaleaTownYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaTownSlowpokeScript::
	message J_AzaleaTownSlowpokeText1
	waitmessage
	delay 60
	message J_AzaleaTownSlowpokeText2
	waitmessage
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_UnusedWoosterScript::
	faceplayer
	message J_WoosterText
	waitmessage
	playmoncry SPECIES_QUAGSIRE, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_AzaleaTownCelebiScene::
	applymovement OBJ_EVENT_ID_PLAYER, J_AzaleaTownPlayerLeavesKurtsHouseMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	message J_AzaleaTownKurtText1
	waitmessage
	waitbuttonpress
	turnobject 12, DIR_EAST
	message J_AzaleaTownKurtText2
	waitmessage
	waitbuttonpress
	message J_AzaleaTownKurtText3
	waitmessage
	waitbuttonpress
	bufferstring STR_VAR_2, J_ItemName_GS_BALL
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message J_Text_ReceivedKeyItem
	waitmessage
	waitfanfare
	setflag FLAG_J_HAS_GS_BALL
	setvar VAR_RESULT, 1
	turnobject 12, DIR_WEST
	setflag FLAG_J_ENGINE_FOREST_IS_RESTLESS
	clearflag FLAG_J_ILEX_FOREST_LASS
	setflag FLAG_J_ROUTE_34_ILEX_FOREST_GATE_LASS
	setvar VAR_J_SCENE_AZALEA_TOWN, 0
	closemessage
	return
J_AzaleaTownKurtScript::
	faceplayer
	message J_AzaleaTownKurtText3
	waitmessage
	waitbuttonpress
	turnobject 12, DIR_WEST
	closemessage
	return
J_AzaleaTownSign::
	message J_AzaleaTownSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_KurtsHouseSign::
	message J_KurtsHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaGymSign::
	message J_AzaleaGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SlowpokeWellSign::
	message J_SlowpokeWellSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CharcoalKilnSign::
	message J_CharcoalKilnSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaTownIlextForestSign::
	message J_AzaleaTownIlexForestSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaTownPokecenterSign::
	goto J_PokecenterSignScript
J_AzaleaTownMartSign::
	goto J_MartSignScript
J_WhiteApricornTree::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_AzaleaTownHiddenFullHeal::
	finditem ITEM_FULL_HEAL
	return
J_AzaleaTownRivalBattleApproachMovement1::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end
J_AzaleaTownRivalBattleApproachMovement2::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_down
	step_end
J_AzaleaTownRivalBattleExitMovement::
	walk_left
	walk_left
	walk_left
	step_end
J_AzaleaTownPlayerLeavesKurtsHouseMovement::
	walk_left
	walk_left
	walk_up
	face_left
	step_end
J_AzaleaTownRivalBeforeText::
	.string "…Tell me some-\nthing.\pIs it true that\nTEAM ROCKET has\lreturned?\pWhat? You beat\nthem? Hah! Quit\llying.\pYou're not joking?\nThen let's see how\lgood you are.$"
J_AzaleaTownRivalWinText::
	.string "… Humph! Useless\nPOKéMON!\pListen, you. You\nonly won because\pmy POKéMON were\nweak.$"
J_AzaleaTownRivalAfterText::
	.string "I hate the weak.\pPOKéMON, trainers.\nIt doesn't matter\lwho or what.\pI'm going to be\nstrong and wipe\lout the weak.\pThat goes for TEAM\nROCKET too.\pThey act big and\ntough in a group.\pBut get them\nalone, and they're\lweak.\pI hate them all.\pYou stay out of my\nway. A weakling\plike you is only a\ndistraction.$"
J_AzaleaTownRivalLossText::
	.string "…Humph! I knew\nyou were lying.$"
J_AzaleaTownRocket1Text::
	.string "It's unsafe to go\nin there, so I'm\lstanding guard.\pAren't I a good\nSamaritan?$"
J_AzaleaTownRocket2Text::
	.string "Do you know about\nSLOWPOKETAIL? I\lheard it's tasty!\pAren't you glad I\ntold you that?$"
J_AzaleaTownGrampsTextBefore::
	.string "The SLOWPOKE have\ndisappeared from\ltown…\pI heard their\nTAILS are being\lsold somewhere.$"
J_AzaleaTownGrampsTextAfter::
	.string "The SLOWPOKE have\nreturned.\pKnowing them, they\ncould've just been\pgoofing off some-\nwhere.$"
J_AzaleaTownTeacherText::
	.string "Did you come to\nget KURT to make\lsome BALLS?\pA lot of people do\njust that.$"
J_AzaleaTownYoungsterText::
	.string "Cut through AZALEA\nand you'll be in\lILEX FOREST.\pBut these skinny\ntrees make it\pimpossible to get\nthrough.\pThe CHARCOAL MAN's\nPOKéMON can CUT\ldown trees.$"
J_AzaleaTownSlowpokeText1::
	.string "SLOWPOKE: …\p…… …… ……$"
J_AzaleaTownSlowpokeText2::
	.string "…… ……Yawn?$"
J_WoosterText::
	.string "WOOSTER: Gugyoo…$"
J_AzaleaTownKurtText1::
	.string "ILEX FOREST is\nrestless!\pWhat is going on?$"
J_AzaleaTownKurtText2::
	.string "{PLAYER}, here's\nyour GS BALL back!$"
J_AzaleaTownKurtText3::
	.string "Could you go see\nwhy ILEX FOREST is\lso restless?$"
J_AzaleaTownSignText::
	.string "AZALEA TOWN\nWhere People and\pPOKéMON Live in\nHappy Harmony$"
J_KurtsHouseSignText::
	.string "KURT'S HOUSE$"
J_AzaleaGymSignText::
	.string "AZALEA TOWN\nPOKéMON GYM\lLEADER: BUGSY\pThe Walking\nBug POKéMON\lEncyclopedia$"
J_SlowpokeWellSignText::
	.string "SLOWPOKE WELL\pAlso known as the\nRAINMAKER WELL.\pLocals believe\nthat a SLOWPOKE's\lyawn summons rain.\pRecords show that\na SLOWPOKE's yawn\pended a drought\n400 years ago.$"
J_CharcoalKilnSignText::
	.string "CHARCOAL KILN$"
J_AzaleaTownIlexForestSignText::
	.string "ILEX FOREST\pEnter through the\ngate.$"
J_AzaleaTown_MapEvents::
