@ KJH: translated from pokecrystal maps/Route35NationalParkGate.asm by kjh_tools/johto

JohtoRoute35NationalParkGate_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoRoute35NationalParkGate_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoRoute35NationalParkGate_OnFrame
	.byte 0

JohtoRoute35NationalParkGate_OnTransition:
	call J_Route35NationalParkGateCheckIfContestRunningCallback
	call J_Route35NationalParkGateCheckIfContestAvailableCallback
	end

JohtoRoute35NationalParkGate_OnFrame:
	map_script_2 VAR_J_SCENE_ROUTE_35_NATIONAL_PARK_GATE, 2, J_SC_Route35NationalParkGateLeaveContestEarlyScene
	.2byte 0

J_W_Route35OfficerScriptContest::
	lock
	call J_Route35OfficerScriptContest
	release
	end

J_W_Route35NationalParkGateYoungsterScript::
	lock
	call J_Route35NationalParkGateYoungsterScript
	release
	end

J_W_Route35NationalParkGateOfficerScript::
	lock
	call J_Route35NationalParkGateOfficerScript
	release
	end

J_S_BugCatchingContestExplanationSign::
	lockall
	call J_BugCatchingContestExplanationSign
	releaseall
	end

J_SC_Route35NationalParkGateLeaveContestEarlyScene::
	lockall
	call J_Route35NationalParkGateLeaveContestEarlyScene
	releaseall
	end

J_Route35NationalParkGate_MapScripts::
J_Route35NationalParkGateNoop1Scene::
	return
J_Route35NationalParkGateNoop2Scene::
	return
J_Route35NationalParkGateLeaveContestEarlyScene::
	call J_Route35NationalParkGateLeavingContestEarlyScript
	return
J_Route35NationalParkGateCheckIfContestRunningCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_BUG_CONTEST_TIMER, J_L458
	setvar VAR_RESULT, 1
J_L458:
	goto_if_ne VAR_RESULT, 0, J_Route35NationalParkBugContestIsRunningScript
	setvar VAR_J_SCENE_ROUTE_35_NATIONAL_PARK_GATE, 0
	return
J_Route35NationalParkBugContestIsRunningScript::
	setvar VAR_J_SCENE_ROUTE_35_NATIONAL_PARK_GATE, 2
	return
J_Route35NationalParkGateCheckIfContestAvailableCallback::
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 2, J_Route35NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer
	goto_if_eq VAR_RESULT, 4, J_Route35NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer
	goto_if_eq VAR_RESULT, 6, J_Route35NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_BUG_CONTEST_TIMER, J_L459
	setvar VAR_RESULT, 1
J_L459:
	goto_if_ne VAR_RESULT, 0, J_Route35NationalParkBugContestIsRunningScript
	setflag FLAG_J_ROUTE_35_NATIONAL_PARK_GATE_OFFICER_CONTEST_DAY
	clearflag FLAG_J_ROUTE_35_NATIONAL_PARK_GATE_YOUNGSTER
	clearflag FLAG_J_ROUTE_35_NATIONAL_PARK_GATE_OFFICER_NOT_CONTEST_DAY
	return
J_Route35NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer:
	clearflag FLAG_J_ROUTE_35_NATIONAL_PARK_GATE_OFFICER_CONTEST_DAY
	setflag FLAG_J_ROUTE_35_NATIONAL_PARK_GATE_YOUNGSTER
	setflag FLAG_J_ROUTE_35_NATIONAL_PARK_GATE_OFFICER_NOT_CONTEST_DAY
	return
J_Route35NationalParkGateLeavingContestEarlyScript::
	applymovement OBJ_EVENT_ID_PLAYER, J_Route35NationalParkGatePlayerApproachOfficer1Movement
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject 1, DIR_EAST
	setvar VAR_0x8004, 17
	special KJH_CrystalReadVar
	addvar VAR_RESULT, 1
	bufferstring STR_VAR_1, J_Text_Empty
	message J_Route35NationalParkGateOfficer1WantToFinishText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_Route35NationalParkGateLeavingContestEarlyScript_GoBackToContest
	message J_Route35NationalParkGateOfficer1WaitAtNorthGateText
	waitmessage
	waitbuttonpress
	closemessage
	goto J_Std_Nop
J_Route35NationalParkGateLeavingContestEarlyScript_GoBackToContest:
	message J_Route35NationalParkGateOfficer1OkGoFinishText
	waitmessage
	waitbuttonpress
	closemessage
	call J_Route35NationalParkGate_EnterContest
	playse SE_DOOR
	fadescreen FADE_TO_WHITE
	waitse
	warp MAP_JOHTO_NATIONAL_PARK_BUG_CONTEST, 10, 47
	waitstate
	return
J_Route35OfficerScriptContest::
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J_Route35NationalParkGate_NoContestToday
	goto_if_eq VAR_RESULT, 1, J_Route35NationalParkGate_NoContestToday
	goto_if_eq VAR_RESULT, 3, J_Route35NationalParkGate_NoContestToday
	goto_if_eq VAR_RESULT, 5, J_Route35NationalParkGate_NoContestToday
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_DAILY_BUG_CONTEST, J_L460
	setvar VAR_RESULT, 1
J_L460:
	goto_if_ne VAR_RESULT, 0, J_Route35NationalParkGate_ContestIsOver
	call J_Route35NationalParkGate_GetDayOfWeek
	message J_Route35NationalParkGateOfficer1AskToParticipateText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_Route35NationalParkGate_DeclinedToParticipate
	setvar VAR_0x8004, 1
	special KJH_CrystalReadVar
	goto_if_gt VAR_RESULT, 1, J_Route35NationalParkGate_LeaveTheRestBehind
	clearflag FLAG_J_LEFT_MONS_WITH_CONTEST_OFFICER
J_Route35NationalParkGate_OkayToProceed::
	setflag FLAG_J_ENGINE_BUG_CONTEST_TIMER
	fadedefaultbgm
	message J_Route35NationalParkGateOfficer1GiveParkBallsText
	waitmessage
	waitbuttonpress
	message J_Route35NationalParkGatePlayerReceivedParkBallsText
	waitmessage
	playse SE_SUCCESS
	waitse
	message J_Route35NationalParkGateOfficer1ExplainsRulesText
	waitmessage
	waitbuttonpress
	closemessage
	call J_Route35NationalParkGate_EnterContest
	playse SE_DOOR
	fadescreen FADE_TO_WHITE
	waitse
	warp MAP_JOHTO_NATIONAL_PARK_BUG_CONTEST, 10, 47
	waitstate
	return
J_Route35NationalParkGate_EnterContest::
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 2, J_Route35NationalParkGate_FacingLeft
	applymovement OBJ_EVENT_ID_PLAYER, J_Route35NationalParkGatePlayerGoAroundOfficerAndEnterParkMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	return
J_Route35NationalParkGate_FacingLeft::
	applymovement OBJ_EVENT_ID_PLAYER, J_Route35NationalParkGatePlayerEnterParkMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	return
J_Route35NationalParkGate_LeaveTheRestBehind::
	setvar VAR_0x8004, 1
	special KJH_CrystalReadVar
	goto_if_lt VAR_RESULT, 6, J_Route35NationalParkGate_LessThanFullParty
	setvar VAR_0x8004, 16
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J_Route35NationalParkGate_NoRoomInBox
J_Route35NationalParkGate_LessThanFullParty::
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 1, J_Route35NationalParkGate_FirstMonIsEgg
	message J_Route35NationalParkGateOfficer1AskToUseFirstMonText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_Route35NationalParkGate_DeclinedToLeaveMonsBehind
	goto_if_ne VAR_RESULT, 0, J_Route35NationalParkGate_FirstMonIsFainted
	setflag FLAG_J_LEFT_MONS_WITH_CONTEST_OFFICER
	message J_Route35NationalParkGateOfficer1WellHoldYourMonText
	waitmessage
	waitbuttonpress
	message J_Route35NationalParkGatePlayersMonLeftWithHelperText
	waitmessage
	playse SE_SUCCESS
	waitse
	waitbuttonpress
	goto J_Route35NationalParkGate_OkayToProceed
J_Route35NationalParkGate_DeclinedToParticipate::
	message J_Route35NationalParkGateOfficer1TakePartInFutureText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route35NationalParkGate_DeclinedToLeaveMonsBehind::
	message J_Route35NationalParkGateOfficer1ChooseMonAndComeBackText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route35NationalParkGate_FirstMonIsFainted::
	message J_Route35NationalParkGateOfficer1FirstMonCantBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route35NationalParkGate_NoRoomInBox::
	message J_Route35NationalParkGateOfficer1MakeRoomText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route35NationalParkGate_FirstMonIsEgg::
	message J_Route35NationalParkGateOfficer1EggAsFirstMonText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route35NationalParkGate_ContestIsOver::
	message J_Route35NationalParkGateOfficer1ContestIsOverText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route35NationalParkGate_NoContestToday::
	faceplayer
	message J_Route35NationalParkGateOfficer1WeHoldContestsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route35NationalParkGateOfficerScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_DAILY_BUG_CONTEST, J_L461
	setvar VAR_RESULT, 1
J_L461:
	goto_if_ne VAR_RESULT, 0, J_Route35NationalParkGate_ContestIsOver
	message J_Route35NationalParkGateOfficer1WeHoldContestsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route35NationalParkGateYoungsterScript::
	faceplayer
	message J_Route35NationalParkGateYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestExplanationSign::
	message J_BugCatchingContestExplanationText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route35NationalParkGate_GetDayOfWeek::
	goto J_Std_Nop
	return
J_Route35NationalParkGatePlayerApproachOfficer1Movement::
	walk_down
	face_left
	step_end
J_Route35NationalParkGatePlayerGoAroundOfficerAndEnterParkMovement::
	walk_right
	walk_up
	walk_up
	step_end
J_Route35NationalParkGatePlayerEnterParkMovement::
	walk_up
	step_end
J_Route35NationalParkGateOfficer1AskToParticipateText::
	.string "Today's {STR_VAR_1}.\nThat means the\pBug-Catching Con-\ntest is on today.\pThe rules are sim-\nple.\pUsing one of your\nPOKéMON, catch a\pbug POKéMON to be\njudged.\pWould you like to\ngive it a try?$"
J_Route35NationalParkGateOfficer1GiveParkBallsText::
	.string "Here are the PARK\nBALLS for the\lContest.$"
J_Route35NationalParkGatePlayerReceivedParkBallsText::
	.string "{PLAYER} received\n20 PARK BALLS.$"
J_Route35NationalParkGateOfficer1ExplainsRulesText::
	.string "The person who\ngets the strong-\lest bug POKéMON\lis the winner.\pYou have 20\nminutes.\pIf you run out of\nPARK BALLS, you're\ldone.\pYou can keep the\nlast POKéMON you\lcatch as your own.\pGo out and catch\nthe strongest bug\pPOKéMON you can\nfind!$"
J_Route35NationalParkGateOfficer1AskToUseFirstMonText::
	.string "Uh-oh…\pYou have more than\none POKéMON.\pYou'll have to use\n{STR_VAR_1}, the\pfirst POKéMON in\nyour party.\pIs that OK with\nyou?$"
J_Route35NationalParkGateOfficer1WellHoldYourMonText::
	.string "Fine, we'll hold\nyour other POKéMON\lwhile you compete.$"
J_Route35NationalParkGatePlayersMonLeftWithHelperText::
	.string "{PLAYER}'s POKéMON\nwere left with the\lCONTEST HELPER.$"
J_Route35NationalParkGateOfficer1ChooseMonAndComeBackText::
	.string "Please choose the\nPOKéMON to be used\pin the Contest,\nthen come see me.$"
J_Route35NationalParkGateOfficer1TakePartInFutureText::
	.string "OK. We hope you'll\ntake part in the\lfuture.$"
J_Route35NationalParkGateOfficer1FirstMonCantBattleText::
	.string "Uh-oh…\nThe first POKéMON\pin your party\ncan't battle.\pPlease switch it\nwith the POKéMON\pyou want to use,\nthen come see me.$"
J_Route35NationalParkGateOfficer1MakeRoomText::
	.string "Uh-oh…\nBoth your party\pand your PC BOX\nare full.\pYou have no room\nto put the bug\lPOKéMON you catch.\pPlease make room\nin your party or\pyour PC BOX, then\ncome see me.$"
J_Route35NationalParkGateOfficer1EggAsFirstMonText::
	.string "Uh-oh…\nYou have an EGG as\pthe first POKéMON\nin your party.\pPlease switch it\nwith the POKéMON\pyou want to use,\nthen come see me.$"
J_Route35NationalParkGateOfficer1WantToFinishText::
	.string "You still have {STR_VAR_1}\nminute(s) left.\pDo you want to\nfinish now?$"
J_Route35NationalParkGateOfficer1WaitAtNorthGateText::
	.string "OK. Please wait at\nthe North Gate for\pthe announcement\nof the winners.$"
J_Route35NationalParkGateOfficer1OkGoFinishText::
	.string "OK. Please get\nback outside and\lfinish up.$"
J_Route35NationalParkGateOfficer1ContestIsOverText::
	.string "Today's Contest is\nover. We hope you\pwill participate\nin the future.$"
J_Route35NationalParkGateOfficer1WeHoldContestsText::
	.string "We hold Contests\nregularly in the\pPARK. You should\ngive it a shot.$"
J_Route35NationalParkGateYoungsterText::
	.string "When is the next\nBug-Catching Con-\ltest going to be?$"
J_BugCatchingContestExplanationText::
	.string "The Bug-Catching\nContest is held on\pTuesday, Thursday\nand Saturday.\pNot only do you\nearn a prize just\pfor participating,\nyou also get to\pkeep the bug\nPOKéMON you may\phave at the end of\nthe contest.$"
J_Route35NationalParkGate_MapEvents::
