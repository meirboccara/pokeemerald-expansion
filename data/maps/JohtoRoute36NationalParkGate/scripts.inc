@ KJH: translated from pokecrystal maps/Route36NationalParkGate.asm by kjh_tools/johto

JohtoRoute36NationalParkGate_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoRoute36NationalParkGate_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoRoute36NationalParkGate_OnFrame
	.byte 0

JohtoRoute36NationalParkGate_OnTransition:
	call J_Route36NationalParkGateCheckIfContestRunningCallback
	call J_Route36NationalParkGateCheckIfContestAvailableCallback
	end

JohtoRoute36NationalParkGate_OnFrame:
	map_script_2 VAR_J_SCENE_ROUTE_36_NATIONAL_PARK_GATE, 2, J_SC_Route36NationalParkGateLeaveContestEarlyScene
	.2byte 0

J_W_Route36OfficerScriptContest::
	lock
	call J_Route36OfficerScriptContest
	release
	end

J_W_BugCatchingContestant1BScript::
	lock
	call J_BugCatchingContestant1BScript
	release
	end

J_W_BugCatchingContestant2BScript::
	lock
	call J_BugCatchingContestant2BScript
	release
	end

J_W_BugCatchingContestant3BScript::
	lock
	call J_BugCatchingContestant3BScript
	release
	end

J_W_BugCatchingContestant4BScript::
	lock
	call J_BugCatchingContestant4BScript
	release
	end

J_W_BugCatchingContestant5BScript::
	lock
	call J_BugCatchingContestant5BScript
	release
	end

J_W_BugCatchingContestant6BScript::
	lock
	call J_BugCatchingContestant6BScript
	release
	end

J_W_BugCatchingContestant7BScript::
	lock
	call J_BugCatchingContestant7BScript
	release
	end

J_W_BugCatchingContestant8BScript::
	lock
	call J_BugCatchingContestant8BScript
	release
	end

J_W_BugCatchingContestant9BScript::
	lock
	call J_BugCatchingContestant9BScript
	release
	end

J_W_BugCatchingContestant10BScript::
	lock
	call J_BugCatchingContestant10BScript
	release
	end

J_W_Route36NationalParkGateOfficerScript::
	lock
	call J_Route36NationalParkGateOfficerScript
	release
	end

J_SC_Route36NationalParkGateLeaveContestEarlyScene::
	lockall
	call J_Route36NationalParkGateLeaveContestEarlyScene
	releaseall
	end

J_Route36NationalParkGate_MapScripts::
J_Route36NationalParkGateNoop1Scene::
	return
J_Route36NationalParkGateNoop2Scene::
	return
J_Route36NationalParkGateLeaveContestEarlyScene::
	call J_Route36NationalParkGateLeavingContestEarlyScript
	return
J_Route36NationalParkGateCheckIfContestRunningCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_BUG_CONTEST_TIMER, J_L462
	setvar VAR_RESULT, 1
J_L462:
	goto_if_ne VAR_RESULT, 0, J_Route36NationalParkGateCheckIfContestRunningCallback_BugContestIsRunning
	setvar VAR_J_SCENE_ROUTE_36_NATIONAL_PARK_GATE, 0
	return
J_Route36NationalParkGateCheckIfContestRunningCallback_BugContestIsRunning:
	setvar VAR_J_SCENE_ROUTE_36_NATIONAL_PARK_GATE, 2
	return
J_Route36NationalParkGateCheckIfContestAvailableCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WARPED_FROM_ROUTE_35_NATIONAL_PARK_GATE, J_L463
	setvar VAR_RESULT, 1
J_L463:
	goto_if_ne VAR_RESULT, 0, J_Route36NationalParkGateCheckIfContestAvailableCallback_Return
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 2, J_Route36NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer
	goto_if_eq VAR_RESULT, 4, J_Route36NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer
	goto_if_eq VAR_RESULT, 6, J_Route36NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_BUG_CONTEST_TIMER, J_L464
	setvar VAR_RESULT, 1
J_L464:
	goto_if_ne VAR_RESULT, 0, J_Route36NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer
	setflag FLAG_J_ROUTE_36_NATIONAL_PARK_GATE_OFFICER_CONTEST_DAY
	clearflag FLAG_J_ROUTE_36_NATIONAL_PARK_GATE_OFFICER_NOT_CONTEST_DAY
	return
J_Route36NationalParkGateCheckIfContestAvailableCallback_SetContestOfficer:
	clearflag FLAG_J_ROUTE_36_NATIONAL_PARK_GATE_OFFICER_CONTEST_DAY
	setflag FLAG_J_ROUTE_36_NATIONAL_PARK_GATE_OFFICER_NOT_CONTEST_DAY
J_Route36NationalParkGateCheckIfContestAvailableCallback_Return:
	return
J_Route36NationalParkGateLeavingContestEarlyScript::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	setvar VAR_0x8004, 17
	special KJH_CrystalReadVar
	addvar VAR_RESULT, 1
	bufferstring STR_VAR_1, J_Text_Empty
	message J_Route36NationalParkGateOfficer1WantToFinishText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_Route36NationalParkGateLeavingContestEarlyScript_GoBackToContest
	message J_Route36NationalParkGateOfficer1WaitHereForAnnouncementText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_BLACK
	call J_Route36NationalParkGateLeavingContestEarlyScript_CopyContestants
	removeobject 1
	addobject 12
	applymovement OBJ_EVENT_ID_PLAYER, J_Route36NationalParkGatePlayerWaitWithContestantsMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 15
	fadescreen FADE_FROM_BLACK
	goto J_Std_Nop
J_Route36NationalParkGateLeavingContestEarlyScript_GoBackToContest:
	message J_Route36NationalParkGateOfficer1OkGoFinishText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_EXIT
	fadescreen FADE_TO_WHITE
	waitse
	warp MAP_JOHTO_NATIONAL_PARK_BUG_CONTEST, 33, 18
	waitstate
	return
J_Route36NationalParkGateLeavingContestEarlyScript_CopyContestants:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUG_CATCHING_CONTESTANT_1A, J_L465
	setvar VAR_RESULT, 1
J_L465:
	goto_if_ne VAR_RESULT, 0, J_Route36NationalParkGateLeavingContestEarlyScript_Not1
	addobject 2
J_Route36NationalParkGateLeavingContestEarlyScript_Not1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUG_CATCHING_CONTESTANT_2A, J_L466
	setvar VAR_RESULT, 1
J_L466:
	goto_if_ne VAR_RESULT, 0, J_Route36NationalParkGateLeavingContestEarlyScript_Not2
	addobject 3
J_Route36NationalParkGateLeavingContestEarlyScript_Not2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUG_CATCHING_CONTESTANT_3A, J_L467
	setvar VAR_RESULT, 1
J_L467:
	goto_if_ne VAR_RESULT, 0, J_Route36NationalParkGateLeavingContestEarlyScript_Not3
	addobject 4
J_Route36NationalParkGateLeavingContestEarlyScript_Not3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUG_CATCHING_CONTESTANT_4A, J_L468
	setvar VAR_RESULT, 1
J_L468:
	goto_if_ne VAR_RESULT, 0, J_Route36NationalParkGateLeavingContestEarlyScript_Not4
	addobject 5
J_Route36NationalParkGateLeavingContestEarlyScript_Not4:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUG_CATCHING_CONTESTANT_5A, J_L469
	setvar VAR_RESULT, 1
J_L469:
	goto_if_ne VAR_RESULT, 0, J_Route36NationalParkGateLeavingContestEarlyScript_Not5
	addobject 6
J_Route36NationalParkGateLeavingContestEarlyScript_Not5:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUG_CATCHING_CONTESTANT_6A, J_L470
	setvar VAR_RESULT, 1
J_L470:
	goto_if_ne VAR_RESULT, 0, J_Route36NationalParkGateLeavingContestEarlyScript_Not6
	addobject 7
J_Route36NationalParkGateLeavingContestEarlyScript_Not6:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUG_CATCHING_CONTESTANT_7A, J_L471
	setvar VAR_RESULT, 1
J_L471:
	goto_if_ne VAR_RESULT, 0, J_Route36NationalParkGateLeavingContestEarlyScript_Not7
	addobject 8
J_Route36NationalParkGateLeavingContestEarlyScript_Not7:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUG_CATCHING_CONTESTANT_8A, J_L472
	setvar VAR_RESULT, 1
J_L472:
	goto_if_ne VAR_RESULT, 0, J_Route36NationalParkGateLeavingContestEarlyScript_Not8
	addobject 9
J_Route36NationalParkGateLeavingContestEarlyScript_Not8:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUG_CATCHING_CONTESTANT_9A, J_L473
	setvar VAR_RESULT, 1
J_L473:
	goto_if_ne VAR_RESULT, 0, J_Route36NationalParkGateLeavingContestEarlyScript_Not9
	addobject 10
J_Route36NationalParkGateLeavingContestEarlyScript_Not9:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUG_CATCHING_CONTESTANT_10A, J_L474
	setvar VAR_RESULT, 1
J_L474:
	goto_if_ne VAR_RESULT, 0, J_Route36NationalParkGateLeavingContestEarlyScript_Not10
	addobject 11
J_Route36NationalParkGateLeavingContestEarlyScript_Not10:
	return
J_Route36OfficerScriptContest::
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J__ContestNotOn
	goto_if_eq VAR_RESULT, 1, J__ContestNotOn
	goto_if_eq VAR_RESULT, 3, J__ContestNotOn
	goto_if_eq VAR_RESULT, 5, J__ContestNotOn
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_DAILY_BUG_CONTEST, J_L475
	setvar VAR_RESULT, 1
J_L475:
	goto_if_ne VAR_RESULT, 0, J_Route36Officer_ContestHasConcluded
	call J_Route36ParkGate_DayToText
	message J_Route36NationalParkGateOfficer1AskToParticipateText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_Route36OfficerScriptContest_DecidedNotToJoinContest
	setvar VAR_0x8004, 1
	special KJH_CrystalReadVar
	goto_if_gt VAR_RESULT, 1, J_Route36OfficerScriptContest_LeaveMonsWithOfficer
	clearflag FLAG_J_LEFT_MONS_WITH_CONTEST_OFFICER
J_Route36OfficerScriptContest_ResumeStartingContest:
	setflag FLAG_J_ENGINE_BUG_CONTEST_TIMER
	fadedefaultbgm
	message J_Route36NationalParkGateOfficer1GiveParkBallsText
	waitmessage
	waitbuttonpress
	waitse
	message J_Route36NationalParkGatePlayerReceivedParkBallsText
	waitmessage
	playse SE_SUCCESS
	waitse
	message J_Route36NationalParkGateOfficer1ExplainsRulesText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_ENGINE_BUG_CONTEST_TIMER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_EXIT
	fadescreen FADE_TO_WHITE
	waitse
	warp MAP_JOHTO_NATIONAL_PARK_BUG_CONTEST, 33, 18
	waitstate
	return
J_Route36OfficerScriptContest_LeaveMonsWithOfficer:
	setvar VAR_0x8004, 1
	special KJH_CrystalReadVar
	goto_if_lt VAR_RESULT, 6, J_Route36OfficerScriptContest_ContinueLeavingMons
	setvar VAR_0x8004, 16
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J_Route36OfficerScriptContest_BoxFull
J_Route36OfficerScriptContest_ContinueLeavingMons:
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 1, J_Route36OfficerScriptContest_FirstMonIsEgg
	message J_Route36NationalParkGateOfficer1AskToUseFirstMonText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_Route36OfficerScriptContest_RefusedToLeaveMons
	goto_if_ne VAR_RESULT, 0, J_Route36OfficerScriptContest_FirstMonIsFainted
	setflag FLAG_J_LEFT_MONS_WITH_CONTEST_OFFICER
	message J_Route36NationalParkGateOfficer1WellHoldYourMonText
	waitmessage
	waitbuttonpress
	message J_Route36NationalParkGatePlayersMonLeftWithHelperText
	waitmessage
	playse SE_SUCCESS
	waitse
	waitbuttonpress
	goto J_Route36OfficerScriptContest_ResumeStartingContest
J_Route36OfficerScriptContest_DecidedNotToJoinContest:
	message J_Route36NationalParkGateOfficer1TakePartInFutureText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36OfficerScriptContest_RefusedToLeaveMons:
	message J_Route36NationalParkGateOfficer1ChooseMonAndComeBackText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36OfficerScriptContest_FirstMonIsFainted:
	message J_Route36NationalParkGateOfficer1FirstMonCantBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36OfficerScriptContest_BoxFull:
	message J_Route36NationalParkGateOfficer1MakeRoomText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36OfficerScriptContest_FirstMonIsEgg:
	message J_Route36NationalParkGateOfficer1EggAsFirstMonText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36Officer_ContestHasConcluded::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CONTEST_OFFICER_HAS_SUN_STONE, J_L476
	setvar VAR_RESULT, 1
J_L476:
	goto_if_ne VAR_RESULT, 0, J_Route36Officer_ContestHasConcluded_Sunstone
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CONTEST_OFFICER_HAS_EVERSTONE, J_L477
	setvar VAR_RESULT, 1
J_L477:
	goto_if_ne VAR_RESULT, 0, J_Route36Officer_ContestHasConcluded_Everstone
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CONTEST_OFFICER_HAS_GOLD_BERRY, J_L478
	setvar VAR_RESULT, 1
J_L478:
	goto_if_ne VAR_RESULT, 0, J_Route36Officer_ContestHasConcluded_GoldBerry
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CONTEST_OFFICER_HAS_BERRY, J_L479
	setvar VAR_RESULT, 1
J_L479:
	goto_if_ne VAR_RESULT, 0, J_Route36Officer_ContestHasConcluded_Berry
	message J_Route36NationalParkGateOfficer1ContestIsOverText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36Officer_ContestHasConcluded_Sunstone:
	message J_Route36NationalParkGateOfficer1HeresThePrizeText
	waitmessage
	waitbuttonpress
	giveitem ITEM_SUN_STONE, 1
	goto_if_eq VAR_RESULT, 0, J_Route36Officer_ContestHasConcluded_BagFull
	clearflag FLAG_J_CONTEST_OFFICER_HAS_SUN_STONE
	closemessage
	return
J_Route36Officer_ContestHasConcluded_Everstone:
	message J_Route36NationalParkGateOfficer1HeresThePrizeText
	waitmessage
	waitbuttonpress
	giveitem ITEM_EVERSTONE, 1
	goto_if_eq VAR_RESULT, 0, J_Route36Officer_ContestHasConcluded_BagFull
	clearflag FLAG_J_CONTEST_OFFICER_HAS_EVERSTONE
	closemessage
	return
J_Route36Officer_ContestHasConcluded_GoldBerry:
	message J_Route36NationalParkGateOfficer1HeresThePrizeText
	waitmessage
	waitbuttonpress
	giveitem ITEM_SITRUS_BERRY, 1
	goto_if_eq VAR_RESULT, 0, J_Route36Officer_ContestHasConcluded_BagFull
	clearflag FLAG_J_CONTEST_OFFICER_HAS_GOLD_BERRY
	closemessage
	return
J_Route36Officer_ContestHasConcluded_Berry:
	message J_Route36NationalParkGateOfficer1HeresThePrizeText
	waitmessage
	waitbuttonpress
	giveitem ITEM_ORAN_BERRY, 1
	goto_if_eq VAR_RESULT, 0, J_Route36Officer_ContestHasConcluded_BagFull
	clearflag FLAG_J_CONTEST_OFFICER_HAS_BERRY
	closemessage
	return
J_Route36Officer_ContestHasConcluded_BagFull:
	message J_Route36NationalParkGateOfficer1WellHoldPrizeText
	waitmessage
	waitbuttonpress
	closemessage
	return
J__ContestNotOn::
	faceplayer
	message J_Route36NationalParkGateOfficer1SomeMonOnlySeenInParkText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36NationalParkGateOfficerScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_DAILY_BUG_CONTEST, J_L480
	setvar VAR_RESULT, 1
J_L480:
	goto_if_ne VAR_RESULT, 0, J_Route36Officer_ContestHasConcluded
	message J_Route36NationalParkGateOfficer1SomeMonOnlySeenInParkText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36ParkGate_DayToText::
	goto J_Std_Nop
	return
J_BugCatchingContestant1BScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L481
	setvar VAR_RESULT, 1
J_L481:
	goto_if_eq VAR_RESULT, 0, J_BugCatchingContestant1BScript_StillCompeting
	message J_BugCatchingContestant1BText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant1BScript_StillCompeting:
	message J_BugCatchingContestant1BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant2BScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L482
	setvar VAR_RESULT, 1
J_L482:
	goto_if_eq VAR_RESULT, 0, J_BugCatchingContestant2BScript_StillCompeting
	message J_BugCatchingContestant2BText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant2BScript_StillCompeting:
	message J_BugCatchingContestant2BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant3BScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L483
	setvar VAR_RESULT, 1
J_L483:
	goto_if_eq VAR_RESULT, 0, J_BugCatchingContestant3BScript_StillCompeting
	message J_BugCatchingContestant3BText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant3BScript_StillCompeting:
	message J_BugCatchingContestant3BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant4BScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L484
	setvar VAR_RESULT, 1
J_L484:
	goto_if_eq VAR_RESULT, 0, J_BugCatchingContestant4BScript_StillCompeting
	message J_BugCatchingContestant4BText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant4BScript_StillCompeting:
	message J_BugCatchingContestant4BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant5BScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L485
	setvar VAR_RESULT, 1
J_L485:
	goto_if_eq VAR_RESULT, 0, J_BugCatchingContestant5BScript_StillCompeting
	message J_BugCatchingContestant5BText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant5BScript_StillCompeting:
	message J_BugCatchingContestant5BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant6BScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L486
	setvar VAR_RESULT, 1
J_L486:
	goto_if_eq VAR_RESULT, 0, J_BugCatchingContestant6BScript_StillCompeting
	message J_BugCatchingContestant6BText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant6BScript_StillCompeting:
	message J_BugCatchingContestant6BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant7BScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L487
	setvar VAR_RESULT, 1
J_L487:
	goto_if_eq VAR_RESULT, 0, J_BugCatchingContestant7BScript_StillCompeting
	message J_BugCatchingContestant7BText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant7BScript_StillCompeting:
	message J_BugCatchingContestant7BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant8BScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L488
	setvar VAR_RESULT, 1
J_L488:
	goto_if_eq VAR_RESULT, 0, J_BugCatchingContestant8BScript_StillCompeting
	message J_BugCatchingContestant8BText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant8BScript_StillCompeting:
	message J_BugCatchingContestant8BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant9BScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L489
	setvar VAR_RESULT, 1
J_L489:
	goto_if_eq VAR_RESULT, 0, J_BugCatchingContestant9BScript_StillCompeting
	message J_BugCatchingContestant9BText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant9BScript_StillCompeting:
	message J_BugCatchingContestant9BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant10BScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L490
	setvar VAR_RESULT, 1
J_L490:
	goto_if_eq VAR_RESULT, 0, J_BugCatchingContestant10BScript_StillCompeting
	message J_BugCatchingContestant10BText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant10BScript_StillCompeting:
	message J_BugCatchingContestant10BStillCompetingText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_UnusedBugCatchingContestExplanationSign::
	message J_UnusedBugCatchingContestExplanationText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36NationalParkGatePlayerWaitWithContestantsMovement::
	walk_fast_down
	walk_fast_right
	face_up
	step_end
J_Route36NationalParkGateOfficer1AskToParticipateText::
	.string "Today's {STR_VAR_1}.\nThat means the\pBug-Catching Con-\ntest is on today.\pThe rules are sim-\nple.\pUsing one of your\nPOKéMON, catch a\pbug POKéMON to be\njudged.\pWould you like to\ngive it a try?$"
J_Route36NationalParkGateOfficer1GiveParkBallsText::
	.string "Here are the PARK\nBALLS for the\lContest.$"
J_Route36NationalParkGatePlayerReceivedParkBallsText::
	.string "{PLAYER} received\n20 PARK BALLS.$"
J_Route36NationalParkGateOfficer1ExplainsRulesText::
	.string "The person who\ngets the strong-\lest bug POKéMON\lis the winner.\pYou have 20\nminutes.\pIf you run out of\nPARK BALLS, you're\ldone.\pYou can keep the\nlast POKéMON you\lcatch as your own.\pGo out and catch\nthe strongest bug\pPOKéMON you can\nfind!$"
J_Route36NationalParkGateOfficer1AskToUseFirstMonText::
	.string "Uh-oh…\pYou have more than\none POKéMON.\pYou'll have to use\n{STR_VAR_1}, the\pfirst POKéMON in\nyour party.\pIs that OK with\nyou?$"
J_Route36NationalParkGateOfficer1WellHoldYourMonText::
	.string "Fine, we'll hold\nyour other POKéMON\lwhile you compete.$"
J_Route36NationalParkGatePlayersMonLeftWithHelperText::
	.string "{PLAYER}'s POKéMON\nwere left with the\lCONTEST HELPER.$"
J_Route36NationalParkGateOfficer1ChooseMonAndComeBackText::
	.string "Please choose the\nPOKéMON to be used\pin the Contest,\nthen come see me.$"
J_Route36NationalParkGateOfficer1TakePartInFutureText::
	.string "OK. We hope you'll\ntake part in the\lfuture.$"
J_Route36NationalParkGateOfficer1FirstMonCantBattleText::
	.string "Uh-oh…\nThe first POKéMON\pin your party\ncan't battle.\pPlease switch it\nwith the POKéMON\pyou want to use,\nthen come see me.$"
J_Route36NationalParkGateOfficer1MakeRoomText::
	.string "Uh-oh…\nBoth your party\pand your PC BOX\nare full.\pYou have no room\nto put the bug\lPOKéMON you catch.\pPlease make room\nin your party or\pyour PC BOX, then\ncome see me.$"
J_Route36NationalParkGateOfficer1EggAsFirstMonText::
	.string "Uh-oh…\nYou have an EGG as\pthe first POKéMON\nin your party.\pPlease switch it\nwith the POKéMON\pyou want to use,\nthen come see me.$"
J_Route36NationalParkGateOfficer1WantToFinishText::
	.string "You still have {STR_VAR_1}\nminute(s) left.\pDo you want to\nfinish now?$"
J_Route36NationalParkGateOfficer1WaitHereForAnnouncementText::
	.string "OK. Please wait\nhere for the\pannouncement of\nthe winners.$"
J_Route36NationalParkGateOfficer1OkGoFinishText::
	.string "OK. Please go back\noutside and finish\lup.$"
J_Route36NationalParkGateOfficer1ContestIsOverText::
	.string "Today's Contest is\nover. We hope you\pwill participate\nin the future.$"
J_Route36NationalParkGateOfficer1SomeMonOnlySeenInParkText::
	.string "Some POKéMON can\nonly be seen in\lthe PARK.$"
J_BugCatchingContestant1BText::
	.string "DON: Wow, you beat\nme. You're pretty\lgood.$"
J_BugCatchingContestant1BStillCompetingText::
	.string "DON: Luck plays a\nbig part in this.\pYou never know\nwhat POKéMON will\lappear.$"
J_BugCatchingContestant2BText::
	.string "ED: I envy you.\nI just couldn't\ldo it this time.$"
J_BugCatchingContestant2BStillCompetingText::
	.string "ED: Maybe you win\nwith big POKéMON?$"
J_BugCatchingContestant3BText::
	.string "NICK: Well done!\nI'm going to raise\lmy POKéMON better.$"
J_BugCatchingContestant3BStillCompetingText::
	.string "NICK: Maybe you\nget a higher score\pfor a POKéMON of\nan unusual color.$"
J_BugCatchingContestant4BText::
	.string "WILLIAM: You're\nthe winner? What\ldid you catch?$"
J_BugCatchingContestant4BStillCompetingText::
	.string "WILLIAM: Well, I'm\nsatisfied because\pI caught a POKéMON\nthat I wanted.$"
J_BugCatchingContestant5BText::
	.string "BENNY: Congrats!\nYou have earned my\lrespect!$"
J_BugCatchingContestant5BStillCompetingText::
	.string "BENNY: I caught a\nSCYTHER before,\lbut I didn't win.$"
J_BugCatchingContestant6BText::
	.string "BARRY: That POKé-\nMON you caught…\lit's awesome!$"
J_BugCatchingContestant6BStillCompetingText::
	.string "BARRY: It's easier\nto win if you get\pa strong bug\nPOKéMON.\pBut I think they\nalso consider some\lother points.$"
J_BugCatchingContestant7BText::
	.string "CINDY: You won?\nThat's great!\pDo you feel like\nlooking for bug\lPOKéMON with me?$"
J_BugCatchingContestant7BStillCompetingText::
	.string "CINDY: I really\nlove bug POKéMON!$"
J_BugCatchingContestant8BText::
	.string "JOSH: I… I can't\nbelieve I lost at\lbug-catching…$"
J_BugCatchingContestant8BStillCompetingText::
	.string "JOSH: I heard that\nsomebody won with\la CATERPIE!$"
J_BugCatchingContestant9BText::
	.string "SAMUEL: Next time,\nI'm going to win.$"
J_BugCatchingContestant9BStillCompetingText::
	.string "SAMUEL: Darn.\nI thought I would\lscore higher…$"
J_BugCatchingContestant10BText::
	.string "KIPP: Could you\ngive me some tips?\pI want to study\nyour style.$"
J_BugCatchingContestant10BStillCompetingText::
	.string "KIPP: I study a\nlot, but that's\pnot good enough to\nwin.$"
J_UnusedSilphScope2Text::
	.string "I hear there's a\nPOKéMON that looks\ljust like a tree.\pYou can reveal its\nidentity using a\lSILPHSCOPE 2.$"
J_UnusedBugCatchingContestExplanationText::
	.string "The Bug-Catching\nContest is held on\pTuesday, Thursday\nand Saturday.\pNot only do you\nearn a prize just\pfor participating,\nyou also get to\pkeep the bug\nPOKéMON you may\phave at the end of\nthe contest.$"
J_Route36NationalParkGateOfficer1WellHoldPrizeText::
	.string "Uh-oh… Your PACK\nis full.\pWe'll hold on to\nyour prize, but\lonly for today.\pPlease make room,\nthen come see me.$"
J_Route36NationalParkGateOfficer1HeresThePrizeText::
	.string "{PLAYER}?\pHere's the prize\nwe were holding\lfor you.$"
J_Route36NationalParkGate_MapEvents::
