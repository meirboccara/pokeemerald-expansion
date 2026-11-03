@ KJH: translated from pokecrystal maps/CherrygroveCity.asm by kjh_tools/johto

JohtoCherrygroveCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoCherrygroveCity_OnTransition
	.byte 0

JohtoCherrygroveCity_OnTransition:
	call J_CherrygroveCityFlypointCallback
	end

J_W_CherrygroveCityGuideGent::
	lock
	call J_CherrygroveCityGuideGent
	release
	end

J_W_CherrygroveTeacherScript::
	lock
	call J_CherrygroveTeacherScript
	release
	end

J_W_CherrygroveYoungsterScript::
	lock
	call J_CherrygroveYoungsterScript
	release
	end

J_W_MysticWaterGuy::
	lock
	call J_MysticWaterGuy
	release
	end

J_C_CherrygroveRivalSceneNorth::
	lockall
	call J_CherrygroveRivalSceneNorth
	releaseall
	end

J_C_CherrygroveRivalSceneSouth::
	lockall
	call J_CherrygroveRivalSceneSouth
	releaseall
	end

J_S_CherrygroveCitySign::
	lockall
	call J_CherrygroveCitySign
	releaseall
	end

J_S_GuideGentsHouseSign::
	lockall
	call J_GuideGentsHouseSign
	releaseall
	end

J_S_CherrygroveCityMartSign::
	lockall
	call J_CherrygroveCityMartSign
	releaseall
	end

J_S_CherrygroveCityPokecenterSign::
	lockall
	call J_CherrygroveCityPokecenterSign
	releaseall
	end

J_CherrygroveCity_MapScripts::
J_CherrygroveCityNoop1Scene::
	return
J_CherrygroveCityNoop2Scene::
	return
J_CherrygroveCityFlypointCallback::
	setflag FLAG_J_ENGINE_FLYPOINT_CHERRYGROVE
	return
J_CherrygroveCityGuideGent::
	faceplayer
	message J_GuideGentIntroText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_CherrygroveCityGuideGent_No
	goto J_CherrygroveCityGuideGent_Yes
J_CherrygroveCityGuideGent_Yes:
	message J_GuideGentTourText1
	waitmessage
	waitbuttonpress
	closemessage
	playbgm MUS_RG_FOLLOW_ME, FALSE
	applymovement 1, J_GuideGentMovement1
	applymovement OBJ_EVENT_ID_PLAYER, J_GuideGentMovement1
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement 1
	message J_GuideGentPokecenterText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_GuideGentMovement2
	applymovement OBJ_EVENT_ID_PLAYER, J_GuideGentMovement2
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	message J_GuideGentMartText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_GuideGentMovement3
	applymovement OBJ_EVENT_ID_PLAYER, J_GuideGentMovement3
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	message J_GuideGentRoute30Text
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_GuideGentMovement4
	applymovement OBJ_EVENT_ID_PLAYER, J_GuideGentMovement4
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	message J_GuideGentSeaText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_GuideGentMovement5
	applymovement OBJ_EVENT_ID_PLAYER, J_GuideGentMovement5
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 60
	turnobject 1, DIR_WEST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	message J_GuideGentGiftText
	waitmessage
	waitbuttonpress
	bufferstring STR_VAR_2, J_CherrygroveCityGuideGent_mapcardname
	call J_CherrygroveCityGuideGent_JumpstdReceiveItem
	setflag FLAG_J_ENGINE_MAP_CARD
	message J_GotMapCardText
	waitmessage
	waitbuttonpress
	message J_GuideGentPokegearText
	waitmessage
	waitbuttonpress
	closemessage
	fadedefaultbgm
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	applymovement 1, J_GuideGentMovement6
	waitmovement 1
	playse SE_DOOR
	removeobject 1
	clearflag FLAG_J_GUIDE_GENT_VISIBLE_IN_CHERRYGROVE
	waitse
	return
J_CherrygroveCityGuideGent_JumpstdReceiveItem:
	goto J_ReceiveItemScript
	return
J_CherrygroveCityGuideGent_mapcardname:
	.string "MAP CARD$"
J_CherrygroveCityGuideGent_No:
	message J_GuideGentNoText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CherrygroveRivalSceneSouth::
	setobjectxyperm 2, 39, 7
J_CherrygroveRivalSceneNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	fadeoutbgm 0
	delay 15
	addobject 2
	applymovement 2, J_CherrygroveCity_RivalWalksToYou
	waitmovement 2
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	playbgm MUS_RG_ENCOUNTER_RIVAL, FALSE
	message J_CherrygroveRivalText_Seen
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TOTODILE_FROM_ELM, J_L681
	setvar VAR_RESULT, 1
J_L681:
	goto_if_ne VAR_RESULT, 0, J_CherrygroveRivalSceneNorth_Totodile
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_CHIKORITA_FROM_ELM, J_L682
	setvar VAR_RESULT, 1
J_L682:
	goto_if_ne VAR_RESULT, 0, J_CherrygroveRivalSceneNorth_Chikorita
	setvar VAR_LAST_TALKED, 2
	trainerbattle_no_intro TRAINER_J_RIVAL1_RIVAL1_1_TOTODILE, J_RivalCherrygroveWinText
	goto_if_ne VAR_RESULT, 0, J_CherrygroveRivalSceneNorth_AfterVictorious
	goto J_CherrygroveRivalSceneNorth_AfterYourDefeat
J_CherrygroveRivalSceneNorth_Totodile:
	setvar VAR_LAST_TALKED, 2
	trainerbattle_no_intro TRAINER_J_RIVAL1_RIVAL1_1_CHIKORITA, J_RivalCherrygroveWinText
	goto_if_ne VAR_RESULT, 0, J_CherrygroveRivalSceneNorth_AfterVictorious
	goto J_CherrygroveRivalSceneNorth_AfterYourDefeat
J_CherrygroveRivalSceneNorth_Chikorita:
	setvar VAR_LAST_TALKED, 2
	trainerbattle_no_intro TRAINER_J_RIVAL1_RIVAL1_1_CYNDAQUIL, J_RivalCherrygroveWinText
	goto_if_ne VAR_RESULT, 0, J_CherrygroveRivalSceneNorth_AfterVictorious
	goto J_CherrygroveRivalSceneNorth_AfterYourDefeat
J_CherrygroveRivalSceneNorth_AfterVictorious:
	playbgm MUS_RG_RIVAL_EXIT, FALSE
	message J_CherrygroveRivalText_YouWon
	waitmessage
	waitbuttonpress
	closemessage
	goto J_CherrygroveRivalSceneNorth_FinishRival
J_CherrygroveRivalSceneNorth_AfterYourDefeat:
	playbgm MUS_RG_RIVAL_EXIT, FALSE
	message J_CherrygroveRivalText_YouLost
	waitmessage
	waitbuttonpress
	closemessage
J_CherrygroveRivalSceneNorth_FinishRival:
	playse SE_M_COMET_PUNCH
	applymovement OBJ_EVENT_ID_PLAYER, J_CherrygroveCity_RivalPushesYouOutOfTheWay
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement 2, J_CherrygroveCity_RivalExitsStageLeft
	waitmovement 2
	removeobject 2
	setvar VAR_J_SCENE_CHERRYGROVE_CITY, 0
	special HealPlayerParty
	fadedefaultbgm
	return
J_CherrygroveTeacherScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_MAP_CARD, J_L683
	setvar VAR_RESULT, 1
J_L683:
	goto_if_ne VAR_RESULT, 0, J_CherrygroveTeacherScript_HaveMapCard
	message J_CherrygroveTeacherText_NoMapCard
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CherrygroveTeacherScript_HaveMapCard:
	message J_CherrygroveTeacherText_HaveMapCard
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CherrygroveYoungsterScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_SYS_POKEDEX_GET, J_L684
	setvar VAR_RESULT, 1
J_L684:
	goto_if_ne VAR_RESULT, 0, J_CherrygroveYoungsterScript_HavePokedex
	message J_CherrygroveYoungsterText_NoPokedex
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CherrygroveYoungsterScript_HavePokedex:
	message J_CherrygroveYoungsterText_HavePokedex
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MysticWaterGuy::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_MYSTIC_WATER_IN_CHERRYGROVE, J_L685
	setvar VAR_RESULT, 1
J_L685:
	goto_if_ne VAR_RESULT, 0, J_MysticWaterGuy_After
	message J_MysticWaterGuyTextBefore
	waitmessage
	waitbuttonpress
	giveitem ITEM_MYSTIC_WATER, 1
	goto_if_eq VAR_RESULT, 0, J_MysticWaterGuy_Exit
	setflag FLAG_J_GOT_MYSTIC_WATER_IN_CHERRYGROVE
J_MysticWaterGuy_After:
	message J_MysticWaterGuyTextAfter
	waitmessage
	waitbuttonpress
J_MysticWaterGuy_Exit:
	closemessage
	return
J_CherrygroveCitySign::
	message J_CherrygroveCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GuideGentsHouseSign::
	message J_GuideGentsHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CherrygroveCityPokecenterSign::
	goto J_PokecenterSignScript
J_CherrygroveCityMartSign::
	goto J_MartSignScript
J_GuideGentMovement1::
	walk_left
	walk_left
	walk_up
	walk_left
	face_up
	step_end
J_GuideGentMovement2::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end
J_GuideGentMovement3::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end
J_GuideGentMovement4::
	walk_left
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	face_left
	step_end
J_GuideGentMovement5::
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	step_end
J_GuideGentMovement6::
	walk_up
	walk_up
	step_end
J_CherrygroveCity_RivalWalksToYou::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end
J_CherrygroveCity_RivalPushesYouOutOfTheWay::
	walk_fast_down
	face_up
	step_end
J_CherrygroveCity_UnusedMovementData::
	walk_left
	face_down
	step_end
J_CherrygroveCity_RivalExitsStageLeft::
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	step_end
J_GuideGentIntroText::
	.string "You're a rookie\ntrainer, aren't\lyou? I can tell!\pThat's OK! Every-\none is a rookie\lat some point!\pIf you'd like, I\ncan teach you a\lfew things.$"
J_GuideGentTourText1::
	.string "OK, then!\nFollow me!$"
J_GuideGentPokecenterText::
	.string "This is a POKéMON\nCENTER. They heal\pyour POKéMON in no\ntime at all.\pYou'll be relying\non them a lot, so\pyou better learn\nabout them.$"
J_GuideGentMartText::
	.string "This is a POKéMON\nMART.\pThey sell BALLS\nfor catching wild\pPOKéMON and other\nuseful items.$"
J_GuideGentRoute30Text::
	.string "ROUTE 30 is out\nthis way.\pTrainers will be\nbattling their\pprized POKéMON\nthere.$"
J_GuideGentSeaText::
	.string "This is the sea,\nas you can see.\pSome POKéMON are\nfound only in\lwater.$"
J_GuideGentGiftText::
	.string "Here…\pIt's my house!\nThanks for your\lcompany.\pLet me give you a\nsmall gift.$"
J_GotMapCardText::
	.string "{PLAYER}'s POKéGEAR\nnow has a MAP!$"
J_GuideGentPokegearText::
	.string "POKéGEAR becomes\nmore useful as you\ladd CARDS.\pI wish you luck on\nyour journey!$"
J_GuideGentNoText::
	.string "Oh… It's something\nI enjoy doing…\pFine. Come see me\nwhen you like.$"
J_CherrygroveRivalText_Seen::
	.string "…… …… ……\pYou got a POKéMON\nat the LAB.\pWhat a waste.\nA wimp like you.\p…… …… ……\pDon't you get what\nI'm saying?\pWell, I too, have\na good POKéMON.\pI'll show you\nwhat I mean!$"
J_RivalCherrygroveWinText::
	.string "Humph. Are you\nhappy you won?$"
J_CherrygroveRivalText_YouLost::
	.string "…… …… ……\pMy name's ???.\pI'm going to be\nthe world's great-\lest POKéMON\ltrainer.$"
J_RivalCherrygroveLossText::
	.string "Humph. That was a\nwaste of time.$"
J_CherrygroveRivalText_YouWon::
	.string "…… …… ……\pMy name's ???.\pI'm going to be\nthe world's great-\lest POKéMON\ltrainer.$"
J_CherrygroveTeacherText_NoMapCard::
	.string "Did you talk to\nthe old man by the\lPOKéMON CENTER?\pHe'll put a MAP of\nJOHTO on your\lPOKéGEAR.$"
J_CherrygroveTeacherText_HaveMapCard::
	.string "When you're with\nPOKéMON, going\lanywhere is fun.$"
J_CherrygroveYoungsterText_NoPokedex::
	.string "MR.POKéMON's house\nis still farther\lup ahead.$"
J_CherrygroveYoungsterText_HavePokedex::
	.string "I battled the\ntrainers on the\lroad.\pMy POKéMON lost.\nThey're a mess! I\pmust take them to\na POKéMON CENTER.$"
J_MysticWaterGuyTextBefore::
	.string "A POKéMON I caught\nhad an item.\pI think it's\nMYSTIC WATER.\pI don't need it,\nso do you want it?$"
J_MysticWaterGuyTextAfter::
	.string "Back to fishing\nfor me, then.$"
J_CherrygroveCitySignText::
	.string "CHERRYGROVE CITY\pThe City of Cute,\nFragrant Flowers$"
J_GuideGentsHouseSignText::
	.string "GUIDE GENT'S HOUSE$"
J_CherrygroveCity_MapEvents::
