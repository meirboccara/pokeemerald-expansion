@ KJH: translated from pokecrystal maps/ElmsLab.asm by kjh_tools/johto

JohtoElmsLab_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoElmsLab_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoElmsLab_OnFrame
	.byte 0

JohtoElmsLab_OnTransition:
	call J_ElmsLabMoveElmCallback
	end

JohtoElmsLab_OnFrame:
	map_script_2 VAR_J_SCENE_ELMS_LAB, 0, J_SC_ElmsLabMeetElmScene
	.2byte 0

J_W_ProfElmScript::
	lock
	call J_ProfElmScript
	call KJH_EventScript_ProfessorAbility
	release
	end

J_W_ElmsAideScript::
	lock
	call J_ElmsAideScript
	release
	end

J_W_CyndaquilPokeBallScript::
	lock
	call J_CyndaquilPokeBallScript
	release
	end

J_W_TotodilePokeBallScript::
	lock
	call J_TotodilePokeBallScript
	release
	end

J_W_ChikoritaPokeBallScript::
	lock
	call J_ChikoritaPokeBallScript
	release
	end

J_W_CopScript::
	lock
	call J_CopScript
	release
	end

J_C_LabTryToLeaveScript::
	lockall
	call J_LabTryToLeaveScript
	releaseall
	end

J_C_MeetCopScript::
	lockall
	call J_MeetCopScript
	releaseall
	end

J_C_MeetCopScript2::
	lockall
	call J_MeetCopScript2
	releaseall
	end

J_C_AideScript_WalkPotion1::
	lockall
	call J_AideScript_WalkPotion1
	releaseall
	end

J_C_AideScript_WalkPotion2::
	lockall
	call J_AideScript_WalkPotion2
	releaseall
	end

J_C_AideScript_WalkBalls1::
	lockall
	call J_AideScript_WalkBalls1
	releaseall
	end

J_C_AideScript_WalkBalls2::
	lockall
	call J_AideScript_WalkBalls2
	releaseall
	end

J_S_ElmsLabHealingMachine::
	lockall
	call J_ElmsLabHealingMachine
	releaseall
	end

J_S_ElmsLabBookshelf::
	lockall
	call J_ElmsLabBookshelf
	releaseall
	end

J_S_ElmsLabTravelTip1::
	lockall
	call J_ElmsLabTravelTip1
	releaseall
	end

J_S_ElmsLabTravelTip2::
	lockall
	call J_ElmsLabTravelTip2
	releaseall
	end

J_S_ElmsLabTravelTip3::
	lockall
	call J_ElmsLabTravelTip3
	releaseall
	end

J_S_ElmsLabTravelTip4::
	lockall
	call J_ElmsLabTravelTip4
	releaseall
	end

J_S_ElmsLabTrashcan::
	lockall
	call J_ElmsLabTrashcan
	releaseall
	end

J_S_ElmsLabWindow::
	lockall
	call J_ElmsLabWindow
	releaseall
	end

J_S_ElmsLabPC::
	lockall
	call J_ElmsLabPC
	releaseall
	end

J_SC_ElmsLabMeetElmScene::
	lockall
	call J_ElmsLabMeetElmScene
	releaseall
	end

J_ElmsLab_MapScripts::
J_ElmsLabMeetElmScene::
	call J_ElmsLabWalkUpToElmScript
	return
J_ElmsLabNoop1Scene::
	return
J_ElmsLabNoop2Scene::
	return
J_ElmsLabNoop3Scene::
	return
J_ElmsLabNoop4Scene::
	return
J_ElmsLabNoop5Scene::
	return
J_ElmsLabMoveElmCallback::
	copyvar VAR_RESULT, VAR_J_SCENE_ELMS_LAB
	goto_if_ne VAR_RESULT, 0, J_ElmsLabMoveElmCallback_Skip
	setobjectxyperm 1, 3, 4
J_ElmsLabMoveElmCallback_Skip:
	return
J_ElmsLabWalkUpToElmScript::
	applymovement OBJ_EVENT_ID_PLAYER, J_ElmsLab_WalkUpToElmMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, J_Movement_Exclamation
	waitmovement 0
	turnobject 1, DIR_EAST
	message J_ElmText_Intro
	waitmessage
J_ElmsLabWalkUpToElmScript_MustSayYes:
	yesnobox 20, 8
	goto_if_ne VAR_RESULT, 0, J_ElmsLabWalkUpToElmScript_ElmGetsEmail
	message J_ElmText_Refused
	waitmessage
	goto J_ElmsLabWalkUpToElmScript_MustSayYes
J_ElmsLabWalkUpToElmScript_ElmGetsEmail:
	message J_ElmText_Accepted
	waitmessage
	waitbuttonpress
	message J_ElmText_ResearchAmbitions
	waitmessage
	waitbuttonpress
	closemessage
	playse SE_SELECT
	delay 30
	applymovement 1, J_Movement_Exclamation
	waitmovement 0
	turnobject 1, DIR_SOUTH
	message J_ElmText_GotAnEmail
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 1, DIR_EAST
	message J_ElmText_MissionFromMrPokemon
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_ElmsLab_ElmToDefaultPositionMovement1
	waitmovement 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	applymovement 1, J_ElmsLab_ElmToDefaultPositionMovement2
	waitmovement 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	message J_ElmText_ChooseAPokemon
	waitmessage
	waitbuttonpress
	setvar VAR_J_SCENE_ELMS_LAB, 1
	closemessage
	return
J_ProfElmScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_SS_TICKET_FROM_ELM, J_L621
	setvar VAR_RESULT, 1
J_L621:
	goto_if_ne VAR_RESULT, 0, J_ElmCheckMasterBall
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L622
	setvar VAR_RESULT, 1
J_L622:
	goto_if_ne VAR_RESULT, 0, J_ElmGiveTicketScript
J_ElmCheckMasterBall::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_MASTER_BALL_FROM_ELM, J_L623
	setvar VAR_RESULT, 1
J_L623:
	goto_if_ne VAR_RESULT, 0, J_ElmCheckEverstone
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L624
	setvar VAR_RESULT, 1
J_L624:
	goto_if_ne VAR_RESULT, 0, J_ElmGiveMasterBallScript
J_ElmCheckEverstone::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_EVERSTONE_FROM_ELM, J_L625
	setvar VAR_RESULT, 1
J_L625:
	goto_if_ne VAR_RESULT, 0, J_ElmScript_CallYou
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SHOWED_TOGEPI_TO_ELM, J_L626
	setvar VAR_RESULT, 1
J_L626:
	goto_if_ne VAR_RESULT, 0, J_ElmGiveEverstoneScript
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TOLD_ELM_ABOUT_TOGEPI_OVER_THE_PHONE, J_L627
	setvar VAR_RESULT, 1
J_L627:
	goto_if_eq VAR_RESULT, 0, J_ElmCheckTogepiEgg
	setvar VAR_RESULT, 175
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_ShowElmTogepiScript
	setvar VAR_RESULT, 176
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_ShowElmTogepiScript
	message J_ElmThoughtEggHatchedText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmEggHatchedScript::
	setvar VAR_RESULT, 175
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_ShowElmTogepiScript
	setvar VAR_RESULT, 176
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_ShowElmTogepiScript
	goto J_ElmCheckGotEggAgain
J_ElmCheckTogepiEgg::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TOGEPI_EGG_FROM_ELMS_AIDE, J_L628
	setvar VAR_RESULT, 1
J_L628:
	goto_if_eq VAR_RESULT, 0, J_ElmCheckGotEggAgain
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TOGEPI_HATCHED, J_L629
	setvar VAR_RESULT, 1
J_L629:
	goto_if_ne VAR_RESULT, 0, J_ElmEggHatchedScript
J_ElmCheckGotEggAgain::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TOGEPI_EGG_FROM_ELMS_AIDE, J_L630
	setvar VAR_RESULT, 1
J_L630:
	goto_if_ne VAR_RESULT, 0, J_ElmWaitingEggHatchScript
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE01_GET, J_L631
	setvar VAR_RESULT, 1
J_L631:
	goto_if_ne VAR_RESULT, 0, J_ElmAideHasEggScript
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_MYSTERY_EGG_TO_ELM, J_L632
	setvar VAR_RESULT, 1
J_L632:
	goto_if_ne VAR_RESULT, 0, J_ElmStudyingEggScript
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_MYSTERY_EGG_FROM_MR_POKEMON, J_L633
	setvar VAR_RESULT, 1
J_L633:
	goto_if_ne VAR_RESULT, 0, J_ElmAfterTheftScript
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_KJH_GOT_JOHTO_STARTER, J_L634
	setvar VAR_RESULT, 1
J_L634:
	goto_if_ne VAR_RESULT, 0, J_ElmDescribesMrPokemonScript
	message J_ElmText_LetYourMonBattleIt
	waitmessage
	waitbuttonpress
	closemessage
	return
J_LabTryToLeaveScript::
	turnobject 1, DIR_SOUTH
	message J_LabWhereGoingText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_ElmsLab_CantLeaveMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	return
J_CyndaquilPokeBallScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_KJH_GOT_JOHTO_STARTER, J_L635
	setvar VAR_RESULT, 1
J_L635:
	goto_if_ne VAR_RESULT, 0, J_LookAtElmPokeBallScript
	turnobject 1, DIR_SOUTH
	special DrawWholeMapView
	showmonpic SPECIES_CYNDAQUIL, 10, 3
	playmoncry SPECIES_CYNDAQUIL, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	hidemonpic
	message J_TakeCyndaquilText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_DidntChooseStarterScript
	removeobject 3
	setflag FLAG_J_GOT_CYNDAQUIL_FROM_ELM
	message J_ChoseStarterText
	waitmessage
	waitbuttonpress
	waitse
	message J_ReceivedStarterText
	waitmessage
	playse SE_SUCCESS
	waitse
	waitbuttonpress
	givemon SPECIES_CYNDAQUIL, 5, ITEM_ORAN_BERRY
	setflag FLAG_SYS_POKEMON_GET
	bufferspeciesname STR_VAR_1, SPECIES_CYNDAQUIL
	playfanfare MUS_LEVEL_UP
	message J_Text_ReceivedMon
	waitmessage
	waitfanfare
	setvar VAR_RESULT, 1
	closemessage
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 3, J_ElmDirectionsScript
	applymovement OBJ_EVENT_ID_PLAYER, J_AfterCyndaquilMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	goto J_ElmDirectionsScript
J_TotodilePokeBallScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_KJH_GOT_JOHTO_STARTER, J_L636
	setvar VAR_RESULT, 1
J_L636:
	goto_if_ne VAR_RESULT, 0, J_LookAtElmPokeBallScript
	turnobject 1, DIR_SOUTH
	special DrawWholeMapView
	showmonpic SPECIES_TOTODILE, 10, 3
	playmoncry SPECIES_TOTODILE, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	hidemonpic
	message J_TakeTotodileText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_DidntChooseStarterScript
	removeobject 4
	setflag FLAG_J_GOT_TOTODILE_FROM_ELM
	message J_ChoseStarterText
	waitmessage
	waitbuttonpress
	waitse
	message J_ReceivedStarterText
	waitmessage
	playse SE_SUCCESS
	waitse
	waitbuttonpress
	givemon SPECIES_TOTODILE, 5, ITEM_ORAN_BERRY
	setflag FLAG_SYS_POKEMON_GET
	bufferspeciesname STR_VAR_1, SPECIES_TOTODILE
	playfanfare MUS_LEVEL_UP
	message J_Text_ReceivedMon
	waitmessage
	waitfanfare
	setvar VAR_RESULT, 1
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_AfterTotodileMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	goto J_ElmDirectionsScript
J_ChikoritaPokeBallScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_KJH_GOT_JOHTO_STARTER, J_L637
	setvar VAR_RESULT, 1
J_L637:
	goto_if_ne VAR_RESULT, 0, J_LookAtElmPokeBallScript
	turnobject 1, DIR_SOUTH
	special DrawWholeMapView
	showmonpic SPECIES_CHIKORITA, 10, 3
	playmoncry SPECIES_CHIKORITA, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	hidemonpic
	message J_TakeChikoritaText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_DidntChooseStarterScript
	removeobject 5
	setflag FLAG_J_GOT_CHIKORITA_FROM_ELM
	message J_ChoseStarterText
	waitmessage
	waitbuttonpress
	waitse
	message J_ReceivedStarterText
	waitmessage
	playse SE_SUCCESS
	waitse
	waitbuttonpress
	givemon SPECIES_CHIKORITA, 5, ITEM_ORAN_BERRY
	setflag FLAG_SYS_POKEMON_GET
	bufferspeciesname STR_VAR_1, SPECIES_CHIKORITA
	playfanfare MUS_LEVEL_UP
	message J_Text_ReceivedMon
	waitmessage
	waitfanfare
	setvar VAR_RESULT, 1
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_AfterChikoritaMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	goto J_ElmDirectionsScript
J_DidntChooseStarterScript::
	message J_DidntChooseStarterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmDirectionsScript::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	message J_ElmDirectionsText1
	waitmessage
	waitbuttonpress
	closemessage
	message J_GotElmsNumberText
	waitmessage
	playse SE_SUCCESS
	waitse
	waitbuttonpress
	closemessage
	turnobject 1, DIR_WEST
	message J_ElmDirectionsText2
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 1, DIR_SOUTH
	message J_ElmDirectionsText3
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_KJH_GOT_JOHTO_STARTER
	setflag FLAG_J_RIVAL_CHERRYGROVE_CITY
	setvar VAR_J_SCENE_ELMS_LAB, 5
	setvar VAR_J_SCENE_NEW_BARK_TOWN, 1
	return
J_ElmDescribesMrPokemonScript::
	message J_ElmDescribesMrPokemonText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_LookAtElmPokeBallScript::
	message J_ElmPokeBallText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmsLabHealingMachine::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_KJH_GOT_JOHTO_STARTER, J_L638
	setvar VAR_RESULT, 1
J_L638:
	goto_if_ne VAR_RESULT, 0, J_ElmsLabHealingMachine_CanHeal
	message J_ElmsLabHealingMachineText1
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmsLabHealingMachine_CanHeal:
	message J_ElmsLabHealingMachineText2
	waitmessage
	yesnobox 20, 8
	goto_if_ne VAR_RESULT, 0, J_ElmsLabHealingMachine_HealParty
	closemessage
	return
J_ElmsLabHealingMachine_HealParty::
	special HealPlayerParty
	playbgm MUS_NONE, FALSE
	setvar VAR_RESULT, 1
	delay 30
	fadedefaultbgm
	closemessage
	return
J_ElmAfterTheftDoneScript::
	waitbuttonpress
	closemessage
	return
J_ElmAfterTheftScript::
	message J_ElmAfterTheftText1
	waitmessage
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_MYSTERY_EGG, J_L639
	setvar VAR_RESULT, 1
J_L639:
	goto_if_eq VAR_RESULT, 0, J_ElmAfterTheftDoneScript
	waitbuttonpress
	message J_ElmAfterTheftText2
	waitmessage
	waitbuttonpress
	clearflag FLAG_J_HAS_MYSTERY_EGG
	setvar VAR_RESULT, 1
	call J_ElmJumpBackScript1
	message J_ElmAfterTheftText3
	waitmessage
	waitbuttonpress
	call J_ElmJumpBackScript2
	message J_ElmAfterTheftText4
	waitmessage
	waitbuttonpress
	message J_ElmAfterTheftText5
	waitmessage
	waitbuttonpress
	setflag FLAG_J_GAVE_MYSTERY_EGG_TO_ELM
	setflag FLAG_J_ENGINE_MOBILE_SYSTEM
	setvar VAR_J_SCENE_ROUTE_29, 1
	clearflag FLAG_J_ROUTE_30_YOUNGSTER_JOEY
	setflag FLAG_J_ROUTE_30_BATTLE
	message J_ElmAfterTheftText6
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_J_SCENE_ELMS_LAB, 6
	return
J_ElmStudyingEggScript::
	message J_ElmStudyingEggText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmAideHasEggScript::
	message J_ElmAideHasEggText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmWaitingEggHatchScript::
	message J_ElmWaitingEggHatchText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ShowElmTogepiScript::
	message J_ShowElmTogepiText1
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_Movement_Exclamation
	waitmovement 0
	setflag FLAG_J_SHOWED_TOGEPI_TO_ELM
	message J_ShowElmTogepiText2
	waitmessage
	waitbuttonpress
	message J_ShowElmTogepiText3
	waitmessage
	waitbuttonpress
J_ElmGiveEverstoneScript::
	message J_ElmGiveEverstoneText1
	waitmessage
	waitbuttonpress
	giveitem ITEM_EVERSTONE, 1
	goto_if_eq VAR_RESULT, 0, J_ElmScript_NoRoomForEverstone
	message J_ElmGiveEverstoneText2
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_GOT_EVERSTONE_FROM_ELM
	return
J_ElmScript_CallYou::
	message J_ElmText_CallYou
	waitmessage
	waitbuttonpress
J_ElmScript_NoRoomForEverstone::
	closemessage
	return
J_ElmGiveMasterBallScript::
	message J_ElmGiveMasterBallText1
	waitmessage
	waitbuttonpress
	giveitem ITEM_MASTER_BALL, 1
	goto_if_eq VAR_RESULT, 0, J_ElmGiveMasterBallScript_notdone
	setflag FLAG_J_GOT_MASTER_BALL_FROM_ELM
	message J_ElmGiveMasterBallText2
	waitmessage
	waitbuttonpress
J_ElmGiveMasterBallScript_notdone:
	closemessage
	return
J_ElmGiveTicketScript::
	message J_ElmGiveTicketText1
	waitmessage
	waitbuttonpress
	bufferstring STR_VAR_2, J_ItemName_S_S_TICKET
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message J_Text_ReceivedKeyItem
	waitmessage
	waitfanfare
	setflag FLAG_J_HAS_S_S_TICKET
	setvar VAR_RESULT, 1
	setflag FLAG_J_GOT_SS_TICKET_FROM_ELM
	message J_ElmGiveTicketText2
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmJumpBackScript1::
	closemessage
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J_ElmJumpDownScript
	goto_if_eq VAR_RESULT, 1, J_ElmJumpUpScript
	goto_if_eq VAR_RESULT, 2, J_ElmJumpLeftScript
	goto_if_eq VAR_RESULT, 3, J_ElmJumpRightScript
	return
J_ElmJumpBackScript2::
	closemessage
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J_ElmJumpUpScript
	goto_if_eq VAR_RESULT, 1, J_ElmJumpDownScript
	goto_if_eq VAR_RESULT, 2, J_ElmJumpRightScript
	goto_if_eq VAR_RESULT, 3, J_ElmJumpLeftScript
	return
J_ElmJumpUpScript::
	applymovement 1, J_ElmJumpUpMovement
	waitmovement 1
	return
J_ElmJumpDownScript::
	applymovement 1, J_ElmJumpDownMovement
	waitmovement 1
	return
J_ElmJumpLeftScript::
	applymovement 1, J_ElmJumpLeftMovement
	waitmovement 1
	return
J_ElmJumpRightScript::
	applymovement 1, J_ElmJumpRightMovement
	waitmovement 1
	return
J_AideScript_WalkPotion1::
	applymovement 2, J_AideWalksRight1
	waitmovement 2
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	call J_AideScript_GivePotion
	applymovement 2, J_AideWalksLeft1
	waitmovement 2
	return
J_AideScript_WalkPotion2::
	applymovement 2, J_AideWalksRight2
	waitmovement 2
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	call J_AideScript_GivePotion
	applymovement 2, J_AideWalksLeft2
	waitmovement 2
	return
J_AideScript_GivePotion::
	message J_AideText_GiveYouPotion
	waitmessage
	waitbuttonpress
	giveitem ITEM_POTION, 1
	message J_AideText_AlwaysBusy
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_J_SCENE_ELMS_LAB, 2
	return
J_AideScript_WalkBalls1::
	applymovement 2, J_AideWalksRight1
	waitmovement 2
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	call J_AideScript_GiveYouBalls
	applymovement 2, J_AideWalksLeft1
	waitmovement 2
	return
J_AideScript_WalkBalls2::
	applymovement 2, J_AideWalksRight2
	waitmovement 2
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	call J_AideScript_GiveYouBalls
	applymovement 2, J_AideWalksLeft2
	waitmovement 2
	return
J_AideScript_GiveYouBalls::
	message J_AideText_GiveYouBalls
	waitmessage
	waitbuttonpress
	bufferitemname STR_VAR_1, ITEM_POTION
	call J_AideScript_ReceiveTheBalls
	additem ITEM_POKE_BALL, 5
	message J_AideText_ExplainBalls
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_J_SCENE_ELMS_LAB, 2
	return
J_AideScript_ReceiveTheBalls::
	goto J_ReceiveItemScript
	return
J_ElmsAideScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TOGEPI_EGG_FROM_ELMS_AIDE, J_L640
	setvar VAR_RESULT, 1
J_L640:
	goto_if_ne VAR_RESULT, 0, J_AideScript_AfterTheft
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_MYSTERY_EGG_TO_ELM, J_L641
	setvar VAR_RESULT, 1
J_L641:
	goto_if_ne VAR_RESULT, 0, J_AideScript_ExplainBalls
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_MYSTERY_EGG_FROM_MR_POKEMON, J_L642
	setvar VAR_RESULT, 1
J_L642:
	goto_if_ne VAR_RESULT, 0, J_AideScript_TheftTestimony
	message J_AideText_AlwaysBusy
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AideScript_TheftTestimony::
	message J_AideText_TheftTestimony
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AideScript_ExplainBalls::
	message J_AideText_ExplainBalls
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AideScript_AfterTheft::
	message J_AideText_AfterTheft
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MeetCopScript2::
	applymovement OBJ_EVENT_ID_PLAYER, J_MeetCopScript2_StepLeft
	waitmovement OBJ_EVENT_ID_PLAYER
J_MeetCopScript::
	applymovement OBJ_EVENT_ID_PLAYER, J_MeetCopScript_WalkUp
	waitmovement OBJ_EVENT_ID_PLAYER
J_CopScript::
	turnobject 6, DIR_WEST
	message J_ElmsLabOfficerText1
	waitmessage
	waitbuttonpress
	message J_ElmsLabOfficerText2
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 6, J_OfficerLeavesMovement
	waitmovement 6
	removeobject 6
	setvar VAR_J_SCENE_ELMS_LAB, 2
	return
J_ElmsLabWindow::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_VIOLET, J_L643
	setvar VAR_RESULT, 1
J_L643:
	goto_if_ne VAR_RESULT, 0, J_ElmsLabWindow_Normal
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ELM_CALLED_ABOUT_STOLEN_POKEMON, J_L644
	setvar VAR_RESULT, 1
J_L644:
	goto_if_ne VAR_RESULT, 0, J_ElmsLabWindow_BreakIn
	goto J_ElmsLabWindow_Normal
J_ElmsLabWindow_BreakIn:
	message J_ElmsLabWindowText2
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmsLabWindow_Normal:
	message J_ElmsLabWindowText1
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmsLabTravelTip1::
	message J_ElmsLabTravelTip1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmsLabTravelTip2::
	message J_ElmsLabTravelTip2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmsLabTravelTip3::
	message J_ElmsLabTravelTip3Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmsLabTravelTip4::
	message J_ElmsLabTravelTip4Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmsLabTrashcan::
	message J_ElmsLabTrashcanText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmsLabPC::
	message J_ElmsLabPCText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmsLabTrashcan2::
	goto J_TrashCanScript
J_ElmsLabBookshelf::
	goto J_DifficultBookshelfScript
J_ElmsLab_WalkUpToElmMovement::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_left
	step_end
J_ElmsLab_CantLeaveMovement::
	walk_up
	step_end
J_MeetCopScript2_StepLeft::
	walk_left
	step_end
J_MeetCopScript_WalkUp::
	walk_up
	walk_up
	face_right
	step_end
J_OfficerLeavesMovement::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
J_AideWalksRight1::
	walk_right
	walk_right
	face_up
	step_end
J_AideWalksRight2::
	walk_right
	walk_right
	walk_right
	face_up
	step_end
J_AideWalksLeft1::
	walk_left
	walk_left
	face_down
	step_end
J_AideWalksLeft2::
	walk_left
	walk_left
	walk_left
	face_down
	step_end
J_ElmJumpUpMovement::
	lock_facing_direction
	walk_fast_up
	unlock_facing_direction
	step_end
J_ElmJumpDownMovement::
	lock_facing_direction
	walk_fast_down
	unlock_facing_direction
	step_end
J_ElmJumpLeftMovement::
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	step_end
J_ElmJumpRightMovement::
	lock_facing_direction
	walk_fast_right
	unlock_facing_direction
	step_end
J_ElmsLab_ElmToDefaultPositionMovement1::
	walk_up
	step_end
J_ElmsLab_ElmToDefaultPositionMovement2::
	walk_right
	walk_right
	walk_up
	face_down
	step_end
J_AfterCyndaquilMovement::
	walk_left
	walk_up
	face_up
	step_end
J_AfterTotodileMovement::
	walk_left
	walk_left
	walk_up
	face_up
	step_end
J_AfterChikoritaMovement::
	walk_left
	walk_left
	walk_left
	walk_up
	face_up
	step_end
J_ElmText_Intro::
	.string "ELM: {PLAYER}!\nThere you are!\pI needed to ask\nyou a favor.\pI'm conducting new\nPOKéMON research\pright now. I was\nwondering if you\pcould help me with\nit, {PLAYER}.\pYou see…\pI'm writing a\npaper that I want\pto present at a\nconference.\pBut there are some\nthings I don't\pquite understand\nyet.\pSo!\pI'd like you to\nraise a POKéMON\pthat I recently\ncaught.$"
J_ElmText_Accepted::
	.string "Thanks, {PLAYER}!\pYou're a great\nhelp!$"
J_ElmText_Refused::
	.string "But… Please, I\nneed your help!$"
J_ElmText_ResearchAmbitions::
	.string "When I announce my\nfindings, I'm sure\pwe'll delve a bit\ndeeper into the\pmany mysteries of\nPOKéMON.\pYou can count on\nit!$"
J_ElmText_GotAnEmail::
	.string "Oh, hey! I got an\ne-mail!\p………………\nHm… Uh-huh…\pOkay…$"
J_ElmText_MissionFromMrPokemon::
	.string "Hey, listen.\pI have an acquain-\ntance called MR.\lPOKéMON.\pHe keeps finding\nweird things and\praving about his\ndiscoveries.\pAnyway, I just got\nan e-mail from him\psaying that this\ntime it's real.\pIt is intriguing,\nbut we're busy\pwith our POKéMON\nresearch…\pWait!\pI know!\p{PLAYER}, can you\ngo in our place?$"
J_ElmText_ChooseAPokemon::
	.string "I want you to\nraise one of the\pPOKéMON contained\nin these BALLS.\pYou'll be that\nPOKéMON's first\lpartner, {PLAYER}!\pGo on. Pick one!$"
J_ElmText_LetYourMonBattleIt::
	.string "If a wild POKéMON\nappears, let your\lPOKéMON battle it!$"
J_LabWhereGoingText::
	.string "ELM: Wait! Where\nare you going?$"
J_TakeCyndaquilText::
	.string "ELM: You'll take\nCYNDAQUIL, the\lfire POKéMON?$"
J_TakeTotodileText::
	.string "ELM: Do you want\nTOTODILE, the\lwater POKéMON?$"
J_TakeChikoritaText::
	.string "ELM: So, you like\nCHIKORITA, the\lgrass POKéMON?$"
J_DidntChooseStarterText::
	.string "ELM: Think it over\ncarefully.\pYour partner is\nimportant.$"
J_ChoseStarterText::
	.string "ELM: I think\nthat's a great\lPOKéMON too!$"
J_ReceivedStarterText::
	.string "{PLAYER} received\n{STR_VAR_1}!$"
J_ElmDirectionsText1::
	.string "MR.POKéMON lives a\nlittle bit beyond\pCHERRYGROVE, the\nnext city over.\pIt's almost a\ndirect route\pthere, so you\ncan't miss it.\pBut just in case,\nhere's my phone\pnumber. Call me if\nanything comes up!$"
J_ElmDirectionsText2::
	.string "If your POKéMON is\nhurt, you should\pheal it with this\nmachine.\pFeel free to use\nit anytime.$"
J_ElmDirectionsText3::
	.string "{PLAYER}, I'm\ncounting on you!$"
J_GotElmsNumberText::
	.string "{PLAYER} got ELM's\nphone number.$"
J_ElmDescribesMrPokemonText::
	.string "MR.POKéMON goes\neverywhere and\lfinds rarities.\pToo bad they're\njust rare and\lnot very useful…$"
J_ElmPokeBallText::
	.string "It contains a\nPOKéMON caught by\lPROF.ELM.$"
J_ElmsLabHealingMachineText1::
	.string "I wonder what this\ndoes?$"
J_ElmsLabHealingMachineText2::
	.string "Would you like to\nheal your POKéMON?$"
J_ElmAfterTheftText1::
	.string "ELM: {PLAYER}, this\nis terrible…\pOh, yes, what was\nMR.POKéMON's big\ldiscovery?$"
J_ElmAfterTheftText2::
	.string "{PLAYER} handed\nthe MYSTERY EGG to\lPROF.ELM.$"
J_ElmAfterTheftText3::
	.string "ELM: This?$"
J_ElmAfterTheftText4::
	.string "But… Is it a\nPOKéMON EGG?\pIf it is, it is a\ngreat discovery!$"
J_ElmAfterTheftText5::
	.string "ELM: What?!?\pPROF.OAK gave you\na POKéDEX?\p{PLAYER}, is that\ntrue? Th-that's\lincredible!\pHe is superb at\nseeing the poten-\ltial of people as\ltrainers.\pWow, {PLAYER}. You\nmay have what it\ptakes to become\nthe CHAMPION.\pYou seem to be\ngetting on great\lwith POKéMON too.\pYou should take\nthe POKéMON GYM\lchallenge.\pThe closest GYM\nwould be the one\lin VIOLET CITY.$"
J_ElmAfterTheftText6::
	.string "…{PLAYER}. The\nroad to the\pchampionship will\nbe a long one.\pBefore you leave,\nmake sure that you\ltalk to your mom.$"
J_ElmStudyingEggText::
	.string "ELM: Don't give\nup! I'll call if\pI learn anything\nabout that EGG!$"
J_ElmAideHasEggText::
	.string "ELM: {PLAYER}?\nDidn't you meet my\lassistant?\pHe should have met\nyou with the EGG\pat VIOLET CITY's\nPOKéMON CENTER.\pYou must have just\nmissed him. Try to\lcatch him there.$"
J_ElmWaitingEggHatchText::
	.string "ELM: Hey, has that\nEGG changed any?$"
J_ElmThoughtEggHatchedText::
	.string "{PLAYER}? I thought\nthe EGG hatched.\pWhere is the\nPOKéMON?$"
J_ShowElmTogepiText1::
	.string "ELM: {PLAYER}, you\nlook great!$"
J_ShowElmTogepiText2::
	.string "What?\nThat POKéMON!?!$"
J_ShowElmTogepiText3::
	.string "The EGG hatched!\nSo, POKéMON are\lborn from EGGS…\pNo, perhaps not\nall POKéMON are.\pWow, there's still\na lot of research\lto be done.$"
J_ElmGiveEverstoneText1::
	.string "Thanks, {PLAYER}!\nYou're helping\punravel POKéMON\nmysteries for us!\pI want you to have\nthis as a token of\lour appreciation.$"
J_ElmGiveEverstoneText2::
	.string "That's an\nEVERSTONE.\pSome species of\nPOKéMON evolve\pwhen they grow to\ncertain levels.\pA POKéMON holding\nthe EVERSTONE\lwon't evolve.\pGive it to a POKé-\nMON you don't want\lto evolve.$"
J_ElmText_CallYou::
	.string "ELM: {PLAYER}, I'll\ncall you if any-\lthing comes up.$"
J_AideText_AfterTheft::
	.string "…sigh… That\nstolen POKéMON.\pI wonder how it's\ndoing.\pThey say a POKéMON\nraised by a bad\pperson turns bad\nitself.$"
J_ElmGiveMasterBallText1::
	.string "ELM: Hi, {PLAYER}!\nThanks to you, my\presearch is going\ngreat!\pTake this as a\ntoken of my\lappreciation.$"
J_ElmGiveMasterBallText2::
	.string "The MASTER BALL is\nthe best!\pIt's the ultimate\nBALL! It'll catch\pany POKéMON with-\nout fail.\pIt's given only to\nrecognized POKéMON\lresearchers.\pI think you can\nmake much better\puse of it than I\ncan, {PLAYER}!$"
J_ElmGiveTicketText1::
	.string "ELM: {PLAYER}!\nThere you are!\pI called because I\nhave something for\lyou.\pSee? It's an\nS.S.TICKET.\pNow you can catch\nPOKéMON in KANTO.$"
J_ElmGiveTicketText2::
	.string "The ship departs\nfrom OLIVINE CITY.\pBut you knew that\nalready, {PLAYER}.\pAfter all, you've\ntraveled all over\lwith your POKéMON.\pGive my regards to\nPROF.OAK in KANTO!$"
J_ElmsLabMonEggText::
	.string "It's the POKéMON\nEGG being studied\lby PROF.ELM.$"
J_AideText_GiveYouPotion::
	.string "{PLAYER}, I want\nyou to have this\lfor your errand.$"
J_AideText_AlwaysBusy::
	.string "There are only two\nof us, so we're\lalways busy.$"
J_AideText_TheftTestimony::
	.string "There was a loud\nnoise outside…\pWhen we went to\nlook, someone\lstole a POKéMON.\pIt's unbelievable\nthat anyone would\ldo that!\p…sigh… That\nstolen POKéMON.\pI wonder how it's\ndoing.\pThey say a POKéMON\nraised by a bad\pperson turns bad\nitself.$"
J_AideText_GiveYouBalls::
	.string "{PLAYER}!\pUse these on your\nPOKéDEX quest!$"
J_AideText_ExplainBalls::
	.string "To add to your\nPOKéDEX, you have\lto catch POKéMON.\pThrow POKé BALLS\nat wild POKéMON\lto get them.$"
J_ElmsLabOfficerText1::
	.string "I heard a POKéMON\nwas stolen here…\pI was just getting\nsome information\lfrom PROF.ELM.\pApparently, it was\na young male with\llong, red hair…\pWhat?\pYou battled a\ntrainer like that?\pDid you happen to\nget his name?$"
J_ElmsLabOfficerText2::
	.string "OK! So {RIVAL}\nwas his name.\pThanks for helping\nmy investigation!$"
J_ElmsLabWindowText1::
	.string "The window's open.\pA pleasant breeze\nis blowing in.$"
J_ElmsLabWindowText2::
	.string "He broke in\nthrough here!$"
J_ElmsLabTravelTip1Text::
	.string "{PLAYER} opened a\nbook.\pTravel Tip 1:\pPress START to\nopen the MENU.$"
J_ElmsLabTravelTip2Text::
	.string "{PLAYER} opened a\nbook.\pTravel Tip 2:\pRecord your trip\nwith SAVE!$"
J_ElmsLabTravelTip3Text::
	.string "{PLAYER} opened a\nbook.\pTravel Tip 3:\pOpen your PACK and\npress SELECT to\lmove items.$"
J_ElmsLabTravelTip4Text::
	.string "{PLAYER} opened a\nbook.\pTravel Tip 4:\pCheck your POKéMON\nmoves. Press the\pA Button to switch\nmoves.$"
J_ElmsLabTrashcanText::
	.string "The wrapper from\nthe snack PROF.ELM\late is in there…$"
J_ElmsLabPCText::
	.string "OBSERVATIONS ON\nPOKéMON EVOLUTION\p…It says on the\nscreen…$"
J_ElmsLab_MapEvents::
