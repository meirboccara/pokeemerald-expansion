@ KJH: translated from pokecrystal maps/DragonShrine.asm by kjh_tools/johto

JohtoDragonShrine_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoDragonShrine_OnFrame
	.byte 0

JohtoDragonShrine_OnFrame:
	map_script_2 VAR_J_SCENE_DRAGON_SHRINE, 0, J_SC_DragonShrineTakeTestScene
	.2byte 0

J_W_DragonShrineElder1Script::
	lock
	call J_DragonShrineElder1Script
	release
	end

J_W_DragonShrineElder2Script::
	lock
	call J_DragonShrineElder2Script
	release
	end

J_W_DragonShrineElder3Script::
	lock
	call J_DragonShrineElder3Script
	release
	end

J_SC_DragonShrineTakeTestScene::
	lockall
	call J_DragonShrineTakeTestScene
	releaseall
	end

J_DragonShrine_MapScripts::
J_DragonShrineTakeTestScene::
	call J_DragonShrineTakeTestScript
	return
J_DragonShrineNoopScene::
	return
J_DragonShrineTakeTestScript::
	applymovement OBJ_EVENT_ID_PLAYER, J_DragonShrinePlayerWalkInMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, J_DragonShrineElderStepDownMovement
	waitmovement 1
	message J_DragonShrineElderGreetingText
	waitmessage
	waitbuttonpress
J_DragonShrineTakeTestScript_Question1:
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2
	message J_DragonShrineQuestion1Text
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 1
	goto_if_eq VAR_RESULT, 1, J_DragonShrineTakeTestScript_RightAnswer
	goto_if_eq VAR_RESULT, 2, J_DragonShrineTakeTestScript_WrongAnswer
	goto_if_eq VAR_RESULT, 3, J_DragonShrineTakeTestScript_RightAnswer
	return
J_DragonShrineTakeTestScript_Question2:
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_3
	message J_DragonShrineQuestion2Text
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 1
	goto_if_eq VAR_RESULT, 1, J_DragonShrineTakeTestScript_RightAnswer
	goto_if_eq VAR_RESULT, 2, J_DragonShrineTakeTestScript_RightAnswer
	goto_if_eq VAR_RESULT, 3, J_DragonShrineTakeTestScript_WrongAnswer
J_DragonShrineTakeTestScript_Question3:
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_4
	message J_DragonShrineQuestion3Text
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 1
	goto_if_eq VAR_RESULT, 1, J_DragonShrineTakeTestScript_WrongAnswer
	goto_if_eq VAR_RESULT, 2, J_DragonShrineTakeTestScript_RightAnswer
	goto_if_eq VAR_RESULT, 3, J_DragonShrineTakeTestScript_RightAnswer
J_DragonShrineTakeTestScript_Question4:
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_5
	message J_DragonShrineQuestion4Text
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 1
	goto_if_eq VAR_RESULT, 1, J_DragonShrineTakeTestScript_RightAnswer
	goto_if_eq VAR_RESULT, 2, J_DragonShrineTakeTestScript_WrongAnswer
	goto_if_eq VAR_RESULT, 3, J_DragonShrineTakeTestScript_RightAnswer
J_DragonShrineTakeTestScript_Question5:
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_6
	message J_DragonShrineQuestion5Text
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 1
	goto_if_eq VAR_RESULT, 1, J_DragonShrineTakeTestScript_WrongAnswer
	goto_if_eq VAR_RESULT, 2, J_DragonShrineTakeTestScript_RightAnswer
	goto_if_eq VAR_RESULT, 3, J_DragonShrineTakeTestScript_WrongAnswer
J_DragonShrineTakeTestScript_RightAnswer:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_6, J_L246
	setvar VAR_RESULT, 1
J_L246:
	goto_if_ne VAR_RESULT, 0, J_DragonShrineTakeTestScript_PassedTheTest
	message J_DragonShrineRightAnswerText
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_5, J_L247
	setvar VAR_RESULT, 1
J_L247:
	goto_if_ne VAR_RESULT, 0, J_DragonShrineTakeTestScript_Question5
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_4, J_L248
	setvar VAR_RESULT, 1
J_L248:
	goto_if_ne VAR_RESULT, 0, J_DragonShrineTakeTestScript_Question4
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_3, J_L249
	setvar VAR_RESULT, 1
J_L249:
	goto_if_ne VAR_RESULT, 0, J_DragonShrineTakeTestScript_Question3
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2, J_L250
	setvar VAR_RESULT, 1
J_L250:
	goto_if_ne VAR_RESULT, 0, J_DragonShrineTakeTestScript_Question2
J_DragonShrineTakeTestScript_WrongAnswer:
	closemessage
	turnobject 1, DIR_WEST
	message J_DragonShrineWrongAnswerText1
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 1, DIR_SOUTH
	message J_DragonShrineWrongAnswerText2
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_ANSWERED_DRAGON_MASTER_QUIZ_WRONG
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_6, J_L251
	setvar VAR_RESULT, 1
J_L251:
	goto_if_ne VAR_RESULT, 0, J_DragonShrineTakeTestScript_Question5
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_5, J_L252
	setvar VAR_RESULT, 1
J_L252:
	goto_if_ne VAR_RESULT, 0, J_DragonShrineTakeTestScript_Question4
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_4, J_L253
	setvar VAR_RESULT, 1
J_L253:
	goto_if_ne VAR_RESULT, 0, J_DragonShrineTakeTestScript_Question3
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_3, J_L254
	setvar VAR_RESULT, 1
J_L254:
	goto_if_ne VAR_RESULT, 0, J_DragonShrineTakeTestScript_Question2
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2, J_L255
	setvar VAR_RESULT, 1
J_L255:
	goto_if_ne VAR_RESULT, 0, J_DragonShrineTakeTestScript_Question1
J_DragonShrineTakeTestScript_PassedTheTest:
	message J_DragonShrinePassedTestText
	waitmessage
	waitbuttonpress
	closemessage
	playse SE_DOOR
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_GYM_LEADER, FALSE
	addobject 4
	waitse
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	delay 30
	applymovement 4, J_DragonShrineClairWalkInMovement
	waitmovement 4
	turnobject 4, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	turnobject 1, DIR_WEST
	message J_DragonShrineClairYouPassedText
	waitmessage
	waitbuttonpress
	closemessage
	fadeoutbgm 0
	applymovement 4, J_DragonShrineClairBigStepLeftMovement
	waitmovement 4
	message J_DragonShrineClairThatCantBeText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, J_DragonShrineClairSlowStepLeftMovement
	waitmovement 4
	message J_DragonShrineClairYoureLyingText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_DragonShrineElderWalkToClairMovement
	waitmovement 1
	turnobject 4, DIR_NORTH
	message J_DragonShrineMustIInformLanceText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, J_Movement_Exclamation
	waitmovement 0
	message J_DragonShrineIUnderstandText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, J_DragonShrineClairTwoSlowStepsRightMovement
	waitmovement 4
	message J_DragonShrineHereRisingBadgeText
	waitmessage
	waitbuttonpress
	setflag FLAG_JOHTO_BADGE08_GET
	playse SE_SUCCESS
	waitse
	fadedefaultbgm
	setvar VAR_J_SCENE_DRAGON_SHRINE, 1
	setvar VAR_J_SCENE_DRAGONS_DEN_B1F, 1
	message J_DragonShrinePlayerReceivedRisingBadgeText
	waitmessage
	waitbuttonpress
	message J_DragonShrineRisingBadgeExplanationText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_DragonShrineElderWalkAway1Movement
	waitmovement 1
	turnobject 4, DIR_NORTH
	applymovement 1, J_DragonShrineElderWalkAway2Movement
	waitmovement 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	message J_DragonShrineElderScoldsClairText
	waitmessage
	waitbuttonpress
	closemessage
	message J_DragonShrineSpeechlessText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, J_DragonShrineClairWalkOutMovement
	waitmovement 4
	playse SE_DOOR
	removeobject 4
	waitse
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1
	return
J_DragonShrineElder1Script::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L256
	setvar VAR_RESULT, 1
J_L256:
	goto_if_ne VAR_RESULT, 0, J_DragonShrineElder1Script_DontGiveDratiniYet
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_7, J_L257
	setvar VAR_RESULT, 1
J_L257:
	goto_if_ne VAR_RESULT, 0, J_DragonShrineElder1Script_ReceivedDratini
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_DRATINI, J_L258
	setvar VAR_RESULT, 1
J_L258:
	goto_if_eq VAR_RESULT, 0, J_DragonShrineElder1Script_GiveDratini
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_RIVAL_IN_MT_MOON, J_L259
	setvar VAR_RESULT, 1
J_L259:
	goto_if_ne VAR_RESULT, 0, J_DragonShrineElder1Script_BeatRivalInMtMoon
	message J_DragonShrineClairsGrandfatherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DragonShrineElder1Script_GiveDratini:
	message J_DragonShrineTakeThisDratiniText
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, 1
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 6, J_DragonShrineElder1Script_PartyFull
	message J_DragonShrinePlayerReceivedDratiniText
	waitmessage
	playse SE_SUCCESS
	waitse
	givemon SPECIES_DRATINI, 15, ITEM_NONE
	setflag FLAG_SYS_POKEMON_GET
	bufferspeciesname STR_VAR_1, SPECIES_DRATINI
	playfanfare MUS_LEVEL_UP
	message J_Text_ReceivedMon
	waitmessage
	waitfanfare
	setvar VAR_RESULT, 1
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ANSWERED_DRAGON_MASTER_QUIZ_WRONG, J_L260
	setvar VAR_RESULT, 1
J_L260:
	givemon SPECIES_DRATINI, 15, ITEM_NONE
	setflag FLAG_J_GOT_DRATINI
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_7
	message J_DragonShrineSymbolicDragonText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DragonShrineElder1Script_PartyFull:
	message J_DragonShrinePartyFullText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DragonShrineElder1Script_BeatRivalInMtMoon:
	message J_DragonShrineRivalIsInTrainingText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DragonShrineElder1Script_DontGiveDratiniYet:
	message J_DragonShrineComeAgainText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DragonShrineElder1Script_ReceivedDratini:
	message J_DragonShrineSymbolicDragonText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DragonShrineElder2Script::
	faceplayer
	message J_DragonShrineElder2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DragonShrineElder3Script::
	faceplayer
	message J_DragonShrineElder3Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DragonShrineQuestion1_MenuHeader::
J_DragonShrineQuestion1_MenuHeader_MenuData:
	.string "Pal$"
	.string "Underling$"
	.string "Friend$"
J_DragonShrineQuestion2_MenuHeader::
J_DragonShrineQuestion2_MenuHeader_MenuData:
	.string "Strategy$"
	.string "Raising$"
	.string "Cheating$"
J_DragonShrineQuestion3_MenuHeader::
J_DragonShrineQuestion3_MenuHeader_MenuData:
	.string "Weak person$"
	.string "Tough person$"
	.string "Anybody$"
J_DragonShrineQuestion4_MenuHeader::
J_DragonShrineQuestion4_MenuHeader_MenuData:
	.string "Love$"
	.string "Violence$"
	.string "Knowledge$"
J_DragonShrineQuestion5_MenuHeader::
J_DragonShrineQuestion5_MenuHeader_MenuData:
	.string "Tough$"
	.string "Both$"
	.string "Weak$"
J_DragonShrinePlayerWalkInMovement::
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_right
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end
J_DragonShrineElderStepDownMovement::
	walk_slow_down
	step_end
J_DragonShrineElderWalkToClairMovement::
	walk_slow_left
	walk_slow_left
	walk_slow_left
	face_down
	step_end
J_DragonShrineElderWalkAway1Movement::
	walk_slow_right
	walk_slow_right
	step_end
J_DragonShrineElderWalkAway2Movement::
	walk_slow_right
	face_down
	step_end
J_DragonShrineClairWalkInMovement::
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end
J_DragonShrineClairBigStepLeftMovement::
	lock_facing_direction
	walk_fast_left
	step_end
J_DragonShrineClairSlowStepLeftMovement::
	walk_slow_left
	unlock_facing_direction
	step_end
J_DragonShrineClairTwoSlowStepsRightMovement::
	walk_slow_right
	walk_slow_right
	step_end
J_DragonShrineClairWalkOutMovement::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
J_DragonShrineElderGreetingText::
	.string "Hm… Good to see\nyou here.\pNo need to explain\nwhy you came.\pCLAIR sent you\nhere, didn't she?\pThat girl is a\nhandful…\pI am sorry, but I\nmust test you.\pNot to worry, you\nare to answer only\la few questions.\pReady?$"
J_DragonShrineQuestion1Text::
	.string "What are POKéMON\nto you?$"
J_DragonShrineQuestion2Text::
	.string "What helps you to\nwin battles?$"
J_DragonShrineQuestion3Text::
	.string "What kind of\ntrainer do you\lwish to battle?$"
J_DragonShrineQuestion4Text::
	.string "What is most\nimportant for\lraising POKéMON?$"
J_DragonShrineQuestion5Text::
	.string "Strong POKéMON.\nWeak POKéMON.\pWhich is more\nimportant?$"
J_DragonShrinePassedTestText::
	.string "Hm… I see…\pYou care deeply\nfor POKéMON.\pVery commendable.\pThat conviction is\nwhat is important!\p{PLAYER}, don't\nlose that belief.\pIt will see you\nthrough at the\lPOKéMON LEAGUE.$"
J_DragonShrineMustIInformLanceText::
	.string "CLAIR!\pThis child is\nimpeccable, in\lskill and spirit!\pAdmit defeat and\nconfer the RISING-\lBADGE!\p…Or must I inform\nLANCE of this?$"
J_DragonShrineElderScoldsClairText::
	.string "CLAIR…\pReflect upon what\nit is that you\plack and this\nchild has.$"
J_DragonShrineComeAgainText::
	.string "Come again, if you\nso desire.$"
J_DragonShrineTakeThisDratiniText::
	.string "Hm… Good to see\nyou here.\pYour arrival is\nmost fortunate.\pI have something\nfor you.\pTake this DRATINI\nas proof that I\phave recognized\nyour worth.$"
J_DragonShrinePlayerReceivedDratiniText::
	.string "{PLAYER} received\nDRATINI!$"
J_DragonShrinePartyFullText::
	.string "Hm? Your POKéMON\nparty is full.$"
J_DragonShrineSymbolicDragonText::
	.string "Dragon POKéMON are\nsymbolic of our\lclan.\pYou have shown\nthat you can be\pentrusted with\none.$"
J_DragonShrineClairsGrandfatherText::
	.string "CLAIR appears to\nhave learned an\pinvaluable lesson\nfrom you.\pI thank you as her\ngrandfather.$"
J_DragonShrineRivalIsInTrainingText::
	.string "A boy close to\nyour age is in\ltraining here.\pHe is much like\nCLAIR when she was\pyounger. It is a\nlittle worrisome…$"
J_DragonShrineWrongAnswerText1::
	.string "Hah? I didn't\nquite catch that…$"
J_DragonShrineWrongAnswerText2::
	.string "What was it you\nsaid?$"
J_DragonShrineRightAnswerText::
	.string "Oh, I understand…$"
J_DragonShrineElder2Text::
	.string "It's been quite\nsome time since a\ptrainer has gained\nour MASTER's rare\lapproval.\pIn fact, not since\nMaster LANCE.$"
J_DragonShrineElder3Text::
	.string "You know young\nMaster LANCE?\pHe looks so much\nlike our MASTER\ldid in his youth.\pIt's in their\nblood.$"
J_DragonShrineClairYouPassedText::
	.string "So how did it go?\pI guess there's no\npoint in asking.\pYou did fail?\p………………………………\p…What? You passed?$"
J_DragonShrineClairThatCantBeText::
	.string "That can't be!$"
J_DragonShrineClairYoureLyingText::
	.string "You're lying!\pEven I haven't\nbeen approved!$"
J_DragonShrineIUnderstandText::
	.string "I-I understand…$"
J_DragonShrineHereRisingBadgeText::
	.string "Here, this is the\nRISINGBADGE…\pHurry up! Take it!$"
J_DragonShrinePlayerReceivedRisingBadgeText::
	.string "{PLAYER} received\nRISINGBADGE.$"
J_DragonShrineRisingBadgeExplanationText::
	.string "RISINGBADGE will\nenable your\pPOKéMON to use the\nmove for climbing\lwaterfalls.\pAlso, all POKéMON\nwill recognize you\pas a trainer and\nobey your every\pcommand without\nquestion.$"
J_DragonShrineSpeechlessText::
	.string "………………………………$"
J_DragonShrine_MapEvents::
