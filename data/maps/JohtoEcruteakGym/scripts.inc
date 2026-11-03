@ KJH: translated from pokecrystal maps/EcruteakGym.asm by kjh_tools/johto

JohtoEcruteakGym_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoEcruteakGym_OnFrame
	.byte 0

JohtoEcruteakGym_OnFrame:
	map_script_2 VAR_J_SCENE_ECRUTEAK_GYM, 0, J_SC_EcruteakGymForcedToLeaveScene
	.2byte 0

J_W_EcruteakGymMortyScript::
	lock
	call J_EcruteakGymMortyScript
	release
	end

J_T_TrainerSageJeffrey::
	trainerbattle_single TRAINER_J_SAGE_JEFFREY, J_SageJeffreySeenText, J_SageJeffreyBeatenText
	call J_TrainerSageJeffrey_Script
	release
	end

J_T_TrainerSagePing::
	trainerbattle_single TRAINER_J_SAGE_PING, J_SagePingSeenText, J_SagePingBeatenText
	call J_TrainerSagePing_Script
	release
	end

J_T_TrainerMediumMartha::
	trainerbattle_single TRAINER_J_MEDIUM_MARTHA, J_MediumMarthaSeenText, J_MediumMarthaBeatenText
	call J_TrainerMediumMartha_Script
	release
	end

J_T_TrainerMediumGrace::
	trainerbattle_single TRAINER_J_MEDIUM_GRACE, J_MediumGraceSeenText, J_MediumGraceBeatenText
	call J_TrainerMediumGrace_Script
	release
	end

J_W_EcruteakGymGuideScript::
	lock
	call J_EcruteakGymGuideScript
	release
	end

J_S_EcruteakGymStatue::
	lockall
	call J_EcruteakGymStatue
	releaseall
	end

J_SC_EcruteakGymForcedToLeaveScene::
	lockall
	call J_EcruteakGymForcedToLeaveScene
	releaseall
	end

J_EcruteakGym_MapScripts::
J_EcruteakGymForcedToLeaveScene::
	call J_EcruteakGymClosed
	return
J_EcruteakGymNoopScene::
	return
J_EcruteakGymMortyScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_MORTY, J_L284
	setvar VAR_RESULT, 1
J_L284:
	goto_if_ne VAR_RESULT, 0, J_EcruteakGymMortyScript_FightDone
	message J_MortyIntroText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_J_MORTY_MORTY1, J_MortyWinLossText
	setflag FLAG_J_BEAT_MORTY
	message J_Text_ReceivedFogBadge
	waitmessage
	playse SE_SUCCESS
	waitse
	setflag FLAG_JOHTO_BADGE04_GET
	setvar VAR_0x8004, 7
	special KJH_CrystalReadVar
	call J_EcruteakGymActivateRockets
	setvar VAR_J_SCENE_ECRUTEAK_TIN_TOWER_ENTRANCE, 1
	setflag FLAG_J_RANG_CLEAR_BELL_1
	setflag FLAG_J_RANG_CLEAR_BELL_2
J_EcruteakGymMortyScript_FightDone:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM30_SHADOW_BALL, J_L285
	setvar VAR_RESULT, 1
J_L285:
	goto_if_ne VAR_RESULT, 0, J_EcruteakGymMortyScript_GotShadowBall
	setflag (TRAINER_FLAGS_START + TRAINER_J_SAGE_JEFFREY)
	setflag (TRAINER_FLAGS_START + TRAINER_J_SAGE_PING)
	setflag (TRAINER_FLAGS_START + TRAINER_J_MEDIUM_MARTHA)
	setflag (TRAINER_FLAGS_START + TRAINER_J_MEDIUM_GRACE)
	message J_MortyText_FogBadgeSpeech
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM30, 1
	goto_if_eq VAR_RESULT, 0, J_EcruteakGymMortyScript_NoRoomForShadowBall
	setflag FLAG_J_GOT_TM30_SHADOW_BALL
	message J_MortyText_ShadowBallSpeech
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakGymMortyScript_GotShadowBall:
	message J_MortyFightDoneText
	waitmessage
	waitbuttonpress
J_EcruteakGymMortyScript_NoRoomForShadowBall:
	closemessage
	return
J_EcruteakGymActivateRockets::
	goto_if_eq VAR_RESULT, 7, J_EcruteakGymActivateRockets_RadioTowerRockets
	goto_if_eq VAR_RESULT, 6, J_EcruteakGymActivateRockets_GoldenrodRockets
	return
J_EcruteakGymActivateRockets_GoldenrodRockets:
	goto J_GoldenrodRocketsScript
J_EcruteakGymActivateRockets_RadioTowerRockets:
	goto J_RadioTowerRocketsScript
J_EcruteakGymClosed::
	applymovement OBJ_EVENT_ID_PLAYER, J_EcruteakGymPlayerStepUpMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 7, J_EcruteakGymGrampsSlowStepDownMovement
	waitmovement 7
	message J_EcruteakGymClosedText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_EcruteakGymPlayerSlowStepDownMovement
	applymovement 7, J_EcruteakGymPlayerSlowStepDownMovement
	waitmovement 7
	waitmovement OBJ_EVENT_ID_PLAYER
	fadescreen FADE_TO_WHITE
	playse SE_DOOR
	waitse
	warp MAP_JOHTO_ECRUTEAK_CITY, 6, 27
	waitstate
	return
J_TrainerSageJeffrey::
J_TrainerSageJeffrey_Script:
	message J_SageJeffreyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSagePing::
J_TrainerSagePing_Script:
	message J_SagePingAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerMediumMartha::
J_TrainerMediumMartha_Script:
	message J_MediumMarthaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerMediumGrace::
J_TrainerMediumGrace_Script:
	message J_MediumGraceAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakGymGuideScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_MORTY, J_L286
	setvar VAR_RESULT, 1
J_L286:
	goto_if_ne VAR_RESULT, 0, J_EcruteakGymGuideScript_EcruteakGymGuideWinScript
	message J_EcruteakGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakGymGuideScript_EcruteakGymGuideWinScript:
	message J_EcruteakGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakGymStatue::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE04_GET, J_L287
	setvar VAR_RESULT, 1
J_L287:
	goto_if_ne VAR_RESULT, 0, J_EcruteakGymStatue_Beaten
	goto J_GymStatue1Script
J_EcruteakGymStatue_Beaten:
	bufferstring STR_VAR_2, J_TrainerName_MORTY_MORTY1
	goto J_GymStatue2Script
J_EcruteakGymPlayerStepUpMovement::
	walk_up
	step_end
J_EcruteakGymPlayerSlowStepDownMovement::
	lock_facing_direction
	walk_slow_down
	unlock_facing_direction
	step_end
J_EcruteakGymGrampsSlowStepDownMovement::
	walk_slow_down
	step_end
J_MortyIntroText::
	.string "Good of you to\nhave come.\pHere in ECRUTEAK,\nPOKéMON have been\lrevered.\pIt's said that a\nrainbow-colored\pPOKéMON will come\ndown to appear\pbefore a truly\npowerful trainer.\pI believed that\ntale, so I have\psecretly trained\nhere all my life.\pAs a result, I can\nnow see what\lothers cannot.\pJust a bit more…\pWith a little\nmore, I could see\pa future in which\nI meet the POKéMON\lof rainbow colors.\pYou're going to\nhelp me reach that\llevel!$"
J_MortyWinLossText::
	.string "I'm not good\nenough yet…\pAll right. This\nBADGE is yours.$"
J_Text_ReceivedFogBadge::
	.string "{PLAYER} received\nFOGBADGE.$"
J_MortyText_FogBadgeSpeech::
	.string "By having FOG-\nBADGE, POKéMON up\pto L50 will obey\nyou.\pAlso, POKéMON that\nknow SURF will be\pable to use that\nmove anytime.\pI want you to have\nthis too.$"
J_MortyText_ShadowBallSpeech::
	.string "It's SHADOW BALL.\nIt causes damage\pand may reduce\nSPCL.DEF.\pUse it if it\nappeals to you.$"
J_MortyFightDoneText::
	.string "I see…\pYour journey has\ntaken you to far-\laway places.\pAnd you have wit-\nnessed much more\lthan I.\pI envy you for\nthat…$"
J_SageJeffreySeenText::
	.string "I spent the spring\nwith my POKéMON.\pThen summer, fall\nand winter…\pThen spring came\nagain. We have\plived together\nfor a long time.$"
J_SageJeffreyBeatenText::
	.string "Wins and losses, I\nexperienced both.$"
J_SageJeffreyAfterBattleText::
	.string "Where did POKéMON\ncome from?$"
J_SagePingSeenText::
	.string "Can you inflict\nany damage on our\lPOKéMON?$"
J_SagePingBeatenText::
	.string "Ah! Well done!$"
J_SagePingAfterBattleText::
	.string "We use only ghost-\ntype POKéMON.\pNo normal-type\nattack can harm\lthem!$"
J_MediumMarthaSeenText::
	.string "I shall win!$"
J_MediumMarthaBeatenText::
	.string "I, I, I lost!$"
J_MediumMarthaAfterBattleText::
	.string "The one who wants\nto win most--will!$"
J_MediumGraceSeenText::
	.string "Stumped by our in-\nvisible floor?\pDefeat me if you\nwant a hint!$"
J_MediumGraceBeatenText::
	.string "Wha-what?$"
J_MediumGraceAfterBattleText::
	.string "Fine. I shall tell\nyou the secret of\pthe invisible\nfloor.\pThe path is right\nbefore our eyes!$"
J_EcruteakGymGuideText::
	.string "The trainers here\nhave secret mo-\ltives.\pIf you win, they\nmay tell you some\pdeep secrets about\nECRUTEAK.$"
J_EcruteakGymGuideWinText::
	.string "Whew, {PLAYER}.\nYou did great!\pI was cowering in\nthe corner out of\lpure terror!$"
J_EcruteakGymClosedText::
	.string "MORTY, the GYM\nLEADER, is absent.\pSorry, but you'll\nhave to leave.\pHohohoho.$"
J_EcruteakGym_MapEvents::
