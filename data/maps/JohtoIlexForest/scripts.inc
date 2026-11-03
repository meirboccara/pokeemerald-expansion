@ KJH: translated from pokecrystal maps/IlexForest.asm by kjh_tools/johto

JohtoIlexForest_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoIlexForest_OnTransition
	.byte 0

JohtoIlexForest_OnTransition:
	call J_IlexForestFarfetchdCallback
	end

J_W_IlexForestFarfetchdScript::
	lock
	call J_IlexForestFarfetchdScript
	release
	end

J_W_IlexForestCharcoalApprenticeScript::
	lock
	call J_IlexForestCharcoalApprenticeScript
	release
	end

J_W_IlexForestCharcoalMasterScript::
	lock
	call J_IlexForestCharcoalMasterScript
	release
	end

J_W_IlexForestHeadbuttGuyScript::
	lock
	call J_IlexForestHeadbuttGuyScript
	release
	end

J_W_IlexForestLassScript::
	lock
	call J_IlexForestLassScript
	release
	end

J_T_TrainerBugCatcherWayne::
	trainerbattle_single TRAINER_J_BUG_CATCHER_WAYNE, J_BugCatcherWayneSeenText, J_BugCatcherWayneBeatenText
	call J_TrainerBugCatcherWayne_Script
	release
	end

J_S_IlexForestSignpost::
	lockall
	call J_IlexForestSignpost
	releaseall
	end

J_S_IlexForestShrineScript::
	lockall
	call J_IlexForestShrineScript
	releaseall
	end

J_IlexForest_MapScripts::
J_IlexForestFarfetchdCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_HM01_CUT, J_L207
	setvar VAR_RESULT, 1
J_L207:
	goto_if_ne VAR_RESULT, 0, J_IlexForestFarfetchdCallback_Static
	copyvar VAR_RESULT, VAR_J_MEM_FARFETCHDPOSITION
	goto_if_eq VAR_RESULT, 1, J_IlexForestFarfetchdCallback_PositionOne
	goto_if_eq VAR_RESULT, 2, J_IlexForestFarfetchdCallback_PositionTwo
	goto_if_eq VAR_RESULT, 3, J_IlexForestFarfetchdCallback_PositionThree
	goto_if_eq VAR_RESULT, 4, J_IlexForestFarfetchdCallback_PositionFour
	goto_if_eq VAR_RESULT, 5, J_IlexForestFarfetchdCallback_PositionFive
	goto_if_eq VAR_RESULT, 6, J_IlexForestFarfetchdCallback_PositionSix
	goto_if_eq VAR_RESULT, 7, J_IlexForestFarfetchdCallback_PositionSeven
	goto_if_eq VAR_RESULT, 8, J_IlexForestFarfetchdCallback_PositionEight
	goto_if_eq VAR_RESULT, 9, J_IlexForestFarfetchdCallback_PositionNine
	goto_if_eq VAR_RESULT, 10, J_IlexForestFarfetchdCallback_PositionTen
J_IlexForestFarfetchdCallback_Static:
	return
J_IlexForestFarfetchdCallback_PositionOne:
	setobjectxyperm 1, 14, 31
	clearflag FLAG_J_ILEX_FOREST_FARFETCHD
	return
J_IlexForestFarfetchdCallback_PositionTwo:
	setobjectxyperm 1, 15, 25
	clearflag FLAG_J_ILEX_FOREST_FARFETCHD
	return
J_IlexForestFarfetchdCallback_PositionThree:
	setobjectxyperm 1, 20, 24
	clearflag FLAG_J_ILEX_FOREST_FARFETCHD
	return
J_IlexForestFarfetchdCallback_PositionFour:
	setobjectxyperm 1, 29, 22
	clearflag FLAG_J_ILEX_FOREST_FARFETCHD
	return
J_IlexForestFarfetchdCallback_PositionFive:
	setobjectxyperm 1, 28, 31
	clearflag FLAG_J_ILEX_FOREST_FARFETCHD
	return
J_IlexForestFarfetchdCallback_PositionSix:
	setobjectxyperm 1, 24, 35
	clearflag FLAG_J_ILEX_FOREST_FARFETCHD
	return
J_IlexForestFarfetchdCallback_PositionSeven:
	setobjectxyperm 1, 22, 31
	clearflag FLAG_J_ILEX_FOREST_FARFETCHD
	return
J_IlexForestFarfetchdCallback_PositionEight:
	setobjectxyperm 1, 15, 29
	clearflag FLAG_J_ILEX_FOREST_FARFETCHD
	return
J_IlexForestFarfetchdCallback_PositionNine:
	setobjectxyperm 1, 10, 35
	clearflag FLAG_J_ILEX_FOREST_FARFETCHD
	return
J_IlexForestFarfetchdCallback_PositionTen:
	setobjectxyperm 1, 6, 28
	clearflag FLAG_J_ILEX_FOREST_FARFETCHD
	return
J_IlexForestCharcoalApprenticeScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HERDED_FARFETCHD, J_L208
	setvar VAR_RESULT, 1
J_L208:
	goto_if_ne VAR_RESULT, 0, J_IlexForestCharcoalApprenticeScript_DoneFarfetchd
	message J_IlexForestApprenticeIntroText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_IlexForestCharcoalApprenticeScript_DoneFarfetchd:
	message J_IlexForestApprenticeAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_IlexForestFarfetchdScript::
	copyvar VAR_RESULT, VAR_J_MEM_FARFETCHDPOSITION
	goto_if_eq VAR_RESULT, 1, J_IlexForestFarfetchdScript_Position1
	goto_if_eq VAR_RESULT, 2, J_IlexForestFarfetchdScript_Position2
	goto_if_eq VAR_RESULT, 3, J_IlexForestFarfetchdScript_Position3
	goto_if_eq VAR_RESULT, 4, J_IlexForestFarfetchdScript_Position4
	goto_if_eq VAR_RESULT, 5, J_IlexForestFarfetchdScript_Position5
	goto_if_eq VAR_RESULT, 6, J_IlexForestFarfetchdScript_Position6
	goto_if_eq VAR_RESULT, 7, J_IlexForestFarfetchdScript_Position7
	goto_if_eq VAR_RESULT, 8, J_IlexForestFarfetchdScript_Position8
	goto_if_eq VAR_RESULT, 9, J_IlexForestFarfetchdScript_Position9
	goto_if_eq VAR_RESULT, 10, J_IlexForestFarfetchdScript_Position10
J_IlexForestFarfetchdScript_Position1:
	faceplayer
	message J_Text_ItsTheMissingPokemon
	waitmessage
	waitbuttonpress
	message J_Text_Kwaaaa
	waitmessage
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	applymovement 1, J_MovementData_Farfetchd_Pos1_Pos2
	waitmovement 1
	setobjectxyperm 1, 15, 25
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 2
	return
J_IlexForestFarfetchdScript_Position2:
	call J_IlexForestFarfetchdScript_CryAndCheckFacing
	goto_if_eq VAR_RESULT, 0, J_IlexForestFarfetchdScript_Position2_Down
	applymovement 1, J_MovementData_Farfetchd_Pos2_Pos3
	waitmovement 1
	setobjectxyperm 1, 20, 24
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 3
	return
J_IlexForestFarfetchdScript_Position2_Down:
	applymovement 1, J_MovementData_Farfetchd_Pos2_Pos8
	waitmovement 1
	setobjectxyperm 1, 15, 29
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 8
	return
J_IlexForestFarfetchdScript_Position3:
	call J_IlexForestFarfetchdScript_CryAndCheckFacing
	goto_if_eq VAR_RESULT, 2, J_IlexForestFarfetchdScript_Position3_Left
	applymovement 1, J_MovementData_Farfetchd_Pos3_Pos4
	waitmovement 1
	setobjectxyperm 1, 29, 22
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 4
	return
J_IlexForestFarfetchdScript_Position3_Left:
	applymovement 1, J_MovementData_Farfetchd_Pos3_Pos2
	waitmovement 1
	setobjectxyperm 1, 15, 25
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 2
	return
J_IlexForestFarfetchdScript_Position4:
	call J_IlexForestFarfetchdScript_CryAndCheckFacing
	goto_if_eq VAR_RESULT, 1, J_IlexForestFarfetchdScript_Position4_Up
	applymovement 1, J_MovementData_Farfetchd_Pos4_Pos5
	waitmovement 1
	setobjectxyperm 1, 28, 31
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 5
	return
J_IlexForestFarfetchdScript_Position4_Up:
	applymovement 1, J_MovementData_Farfetchd_Pos4_Pos3
	waitmovement 1
	setobjectxyperm 1, 20, 24
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 3
	return
J_IlexForestFarfetchdScript_Position5:
	call J_IlexForestFarfetchdScript_CryAndCheckFacing
	goto_if_eq VAR_RESULT, 1, J_IlexForestFarfetchdScript_Position5_Up
	goto_if_eq VAR_RESULT, 2, J_IlexForestFarfetchdScript_Position5_Left
	goto_if_eq VAR_RESULT, 3, J_IlexForestFarfetchdScript_Position5_Right
	applymovement 1, J_MovementData_Farfetchd_Pos5_Pos6
	waitmovement 1
	setobjectxyperm 1, 24, 35
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 6
	return
J_IlexForestFarfetchdScript_Position5_Left:
	applymovement 1, J_MovementData_Farfetchd_Pos5_Pos7
	waitmovement 1
	setobjectxyperm 1, 22, 31
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 7
	return
J_IlexForestFarfetchdScript_Position5_Up:
	applymovement 1, J_MovementData_Farfetched_Pos5_Pos4_Up
	waitmovement 1
	setobjectxyperm 1, 29, 22
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 4
	return
J_IlexForestFarfetchdScript_Position5_Right:
	applymovement 1, J_MovementData_Farfetched_Pos5_Pos4_Right
	waitmovement 1
	setobjectxyperm 1, 29, 22
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 4
	return
J_IlexForestFarfetchdScript_Position6:
	call J_IlexForestFarfetchdScript_CryAndCheckFacing
	goto_if_eq VAR_RESULT, 3, J_IlexForestFarfetchdScript_Position6_Right
	applymovement 1, J_MovementData_Farfetched_Pos6_Pos7
	waitmovement 1
	setobjectxyperm 1, 22, 31
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 7
	return
J_IlexForestFarfetchdScript_Position6_Right:
	applymovement 1, J_MovementData_Farfetched_Pos6_Pos5
	waitmovement 1
	setobjectxyperm 1, 28, 31
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 5
	return
J_IlexForestFarfetchdScript_Position7:
	call J_IlexForestFarfetchdScript_CryAndCheckFacing
	goto_if_eq VAR_RESULT, 0, J_IlexForestFarfetchdScript_Position7_Down
	goto_if_eq VAR_RESULT, 2, J_IlexForestFarfetchdScript_Position7_Left
	applymovement 1, J_MovementData_Farfetched_Pos7_Pos8
	waitmovement 1
	setobjectxyperm 1, 15, 29
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 8
	return
J_IlexForestFarfetchdScript_Position7_Left:
	applymovement 1, J_MovementData_Farfetched_Pos7_Pos6
	waitmovement 1
	setobjectxyperm 1, 24, 35
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 6
	return
J_IlexForestFarfetchdScript_Position7_Down:
	applymovement 1, J_MovementData_Farfetched_Pos7_Pos5
	waitmovement 1
	setobjectxyperm 1, 28, 31
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 5
	return
J_IlexForestFarfetchdScript_Position8:
	call J_IlexForestFarfetchdScript_CryAndCheckFacing
	goto_if_eq VAR_RESULT, 1, J_IlexForestFarfetchdScript_Position8_Up
	goto_if_eq VAR_RESULT, 2, J_IlexForestFarfetchdScript_Position8_Left
	goto_if_eq VAR_RESULT, 3, J_IlexForestFarfetchdScript_Position8_Right
	applymovement 1, J_MovementData_Farfetched_Pos8_Pos9
	waitmovement 1
	setobjectxyperm 1, 10, 35
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 9
	return
J_IlexForestFarfetchdScript_Position8_Right:
	applymovement 1, J_MovementData_Farfetched_Pos8_Pos7
	waitmovement 1
	setobjectxyperm 1, 22, 31
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 7
	return
J_IlexForestFarfetchdScript_Position8_Up:
J_IlexForestFarfetchdScript_Position8_Left:
	applymovement 1, J_MovementData_Farfetched_Pos8_Pos2
	waitmovement 1
	setobjectxyperm 1, 15, 25
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 2
	return
J_IlexForestFarfetchdScript_Position9:
	call J_IlexForestFarfetchdScript_CryAndCheckFacing
	goto_if_eq VAR_RESULT, 0, J_IlexForestFarfetchdScript_Position9_Down
	goto_if_eq VAR_RESULT, 3, J_IlexForestFarfetchdScript_Position9_Right
	applymovement 1, J_MovementData_Farfetched_Pos9_Pos10
	waitmovement 1
	setobjectxyperm 1, 6, 28
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 10
	addobject 3
	setflag FLAG_J_CHARCOAL_KILN_BOSS
	setflag FLAG_J_HERDED_FARFETCHD
	return
J_IlexForestFarfetchdScript_Position9_Right:
	applymovement 1, J_MovementData_Farfetched_Pos9_Pos8_Right
	waitmovement 1
	setobjectxyperm 1, 15, 29
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 8
	return
J_IlexForestFarfetchdScript_Position9_Down:
	applymovement 1, J_MovementData_Farfetched_Pos9_Pos8_Down
	waitmovement 1
	setobjectxyperm 1, 15, 29
	removeobject 1
	addobject 1
	setvar VAR_J_MEM_FARFETCHDPOSITION, 8
	return
J_IlexForestFarfetchdScript_Position10:
	faceplayer
	message J_Text_Kwaaaa
	waitmessage
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_IlexForestFarfetchdScript_CryAndCheckFacing:
	faceplayer
	message J_Text_Kwaaaa
	waitmessage
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	return
J_IlexForestCharcoalMasterScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_HM01_CUT, J_L209
	setvar VAR_RESULT, 1
J_L209:
	goto_if_ne VAR_RESULT, 0, J_IlexForestCharcoalMasterScript_AlreadyGotCut
	message J_Text_CharcoalMasterIntro
	waitmessage
	waitbuttonpress
	giveitem ITEM_HM01, 1
	setflag FLAG_J_GOT_HM01_CUT
	message J_Text_CharcoalMasterOutro
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_ILEX_FOREST_FARFETCHD
	setflag FLAG_J_ILEX_FOREST_APPRENTICE
	setflag FLAG_J_ILEX_FOREST_CHARCOAL_MASTER
	clearflag FLAG_J_CHARCOAL_KILN_FARFETCH_D
	clearflag FLAG_J_CHARCOAL_KILN_APPRENTICE
	clearflag FLAG_J_CHARCOAL_KILN_BOSS
	return
J_IlexForestCharcoalMasterScript_AlreadyGotCut:
	message J_Text_CharcoalMasterTalkAfter
	waitmessage
	waitbuttonpress
	closemessage
	return
J_IlexForestHeadbuttGuyScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM02_HEADBUTT, J_L210
	setvar VAR_RESULT, 1
J_L210:
	goto_if_ne VAR_RESULT, 0, J_IlexForestHeadbuttGuyScript_AlreadyGotHeadbutt
	message J_Text_HeadbuttIntro
	waitmessage
	waitbuttonpress
	giveitem ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, 0, J_IlexForestHeadbuttGuyScript_BagFull
	setflag FLAG_J_GOT_TM02_HEADBUTT
J_IlexForestHeadbuttGuyScript_AlreadyGotHeadbutt:
	message J_Text_HeadbuttOutro
	waitmessage
	waitbuttonpress
J_IlexForestHeadbuttGuyScript_BagFull:
	closemessage
	return
J_TrainerBugCatcherWayne::
J_TrainerBugCatcherWayne_Script:
	message J_BugCatcherWayneAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_IlexForestLassScript::
	faceplayer
	message J_Text_IlexForestLass
	waitmessage
	waitbuttonpress
	closemessage
	return
J_IlexForestRevive::
	finditem ITEM_REVIVE, 1
	return
J_IlexForestXAttack::
	finditem ITEM_X_ATTACK, 1
	return
J_IlexForestAntidote::
	finditem ITEM_ANTIDOTE, 1
	return
J_IlexForestEther::
	finditem ITEM_ETHER, 1
	return
J_IlexForestHiddenEther::
	finditem ITEM_ETHER
	return
J_IlexForestHiddenSuperPotion::
	finditem ITEM_SUPER_POTION
	return
J_IlexForestHiddenFullHeal::
	finditem ITEM_FULL_HEAL
	return
J_IlexForestBoulder::
	goto EventScript_StrengthBoulder
J_IlexForestSignpost::
	message J_IlexForestSignpostText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_IlexForestShrineScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOREST_IS_RESTLESS, J_L211
	setvar VAR_RESULT, 1
J_L211:
	goto_if_ne VAR_RESULT, 0, J_IlexForestShrineScript_ForestIsRestless
	goto J_IlexForestShrineScript_DontDoCelebiEvent
J_IlexForestShrineScript_ForestIsRestless:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_GS_BALL, J_L212
	setvar VAR_RESULT, 1
J_L212:
	goto_if_ne VAR_RESULT, 0, J_IlexForestShrineScript_AskCelebiEvent
J_IlexForestShrineScript_DontDoCelebiEvent:
	message J_Text_IlexForestShrine
	waitmessage
	waitbuttonpress
	closemessage
	return
J_IlexForestShrineScript_AskCelebiEvent:
	message J_Text_ShrineCelebiEvent
	waitmessage
	yesnobox 20, 8
	goto_if_ne VAR_RESULT, 0, J_IlexForestShrineScript_CelebiEvent
	closemessage
	return
J_IlexForestShrineScript_CelebiEvent:
	clearflag FLAG_J_HAS_GS_BALL
	setvar VAR_RESULT, 1
	clearflag FLAG_J_FOREST_IS_RESTLESS
	setflag FLAG_J_AZALEA_TOWN_KURT
	removeobject 7
	clearflag FLAG_J_ROUTE_34_ILEX_FOREST_GATE_LASS
	message J_Text_InsertGSBall
	waitmessage
	waitbuttonpress
	closemessage
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	fadeoutbgm 0
	applymovement OBJ_EVENT_ID_PLAYER, J_IlexForestPlayerStepsDownMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 30
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	delay 20
	clearflag FLAG_J_ENGINE_FOREST_IS_RESTLESS
	setvar VAR_RESULT, 0
	setwildbattle SPECIES_CELEBI, 90
	kjh_legendaryboss @ KJH (CF-13)
	dowildbattle
	delay 20
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_IlexForestShrineScript_DidntCatchCelebi
	addobject 6
	applymovement 6, J_IlexForestKurtStepsUpMovement
	waitmovement 6
	message J_Text_KurtCaughtCelebi
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 6, J_IlexForestKurtStepsDownMovement
	waitmovement 6
	removeobject 6
J_IlexForestShrineScript_DidntCatchCelebi:
	return
J_MovementData_Farfetchd_Pos1_Pos2::
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end
J_MovementData_Farfetchd_Pos2_Pos3::
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	step_end
J_MovementData_Farfetchd_Pos2_Pos8::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end
J_MovementData_Farfetchd_Pos3_Pos4::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end
J_MovementData_Farfetchd_Pos3_Pos2::
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end
J_MovementData_Farfetchd_Pos4_Pos5::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end
J_MovementData_Farfetchd_Pos4_Pos3::
	walk_fast_left
	jump_2_left
	walk_fast_left
	walk_fast_left
	step_end
J_MovementData_Farfetchd_Pos5_Pos6::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end
J_MovementData_Farfetchd_Pos5_Pos7::
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end
J_MovementData_Farfetched_Pos5_Pos4_Up::
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_up
	step_end
J_MovementData_Farfetched_Pos5_Pos4_Right::
	walk_fast_right
	face_up
	delay_1
	face_down
	delay_1
	face_up
	delay_1
	walk_fast_down
	walk_fast_down
	lock_facing_direction
	jump_2_up
	delay_8
	delay_8
	unlock_facing_direction
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end
J_MovementData_Farfetched_Pos6_Pos7::
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_up
	step_end
J_MovementData_Farfetched_Pos6_Pos5::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end
J_MovementData_Farfetched_Pos7_Pos8::
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end
J_MovementData_Farfetched_Pos7_Pos6::
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end
J_MovementData_Farfetched_Pos7_Pos5::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end
J_MovementData_Farfetched_Pos8_Pos9::
	walk_fast_down
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end
J_MovementData_Farfetched_Pos8_Pos7::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end
J_MovementData_Farfetched_Pos8_Pos2::
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end
J_MovementData_Farfetched_Pos9_Pos10::
	walk_fast_left
	walk_fast_left
	lock_facing_direction
	jump_2_right
	delay_8
	delay_8
	unlock_facing_direction
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end
J_MovementData_Farfetched_Pos9_Pos8_Right::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end
J_MovementData_Farfetched_Pos9_Pos8_Down::
	walk_fast_left
	walk_fast_left
	lock_facing_direction
	jump_2_right
	delay_8
	delay_8
	unlock_facing_direction
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end
J_IlexForestKurtStepsUpMovement::
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
J_IlexForestKurtStepsDownMovement::
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
J_IlexForestPlayerStepsDownMovement::
	lock_facing_direction
	walk_slow_down
	unlock_facing_direction
	step_end
J_IlexForestApprenticeIntroText::
	.string "Oh, man… My boss\nis going to be\lsteaming…\pThe FARFETCH'D\nthat CUTS trees\pfor charcoal took\noff on me.\pI can't go looking\nfor it here in the\lILEX FOREST.\pIt's too big, dark\nand scary for me…$"
J_IlexForestApprenticeAfterText::
	.string "Wow! Thanks a\nwhole bunch!\pMy boss's POKéMON\nwon't obey me be-\lcause I don't have\la BADGE.$"
J_Text_ItsTheMissingPokemon::
	.string "It's the missing\nPOKéMON!$"
J_Text_Kwaaaa::
	.string "FARFETCH'D: Kwaa!$"
J_Text_CharcoalMasterIntro::
	.string "Ah! My FARFETCH'D!\pYou found it for\nus, kid?\pWithout it, we\nwouldn't be able\pto CUT trees for\ncharcoal.\pThanks, kid!\pNow, how can I\nthank you…\pI know! Here, take\nthis.$"
J_Text_CharcoalMasterOutro::
	.string "That's the CUT HM.\nTeach that to a\pPOKéMON to clear\nsmall trees.\pOf course, you\nhave to have the\pGYM BADGE from\nAZALEA to use it.$"
J_Text_CharcoalMasterTalkAfter::
	.string "Do you want to\napprentice as a\pcharcoal maker\nwith me?\pYou'll be first-\nrate in ten years!$"
J_Text_HeadbuttIntro::
	.string "What am I doing?\pI'm shaking trees\nusing HEADBUTT.\pIt's fun. Here,\nyou try it too!$"
J_Text_HeadbuttOutro::
	.string "Rattle trees with\nHEADBUTT. Some-\ltimes, sleeping\lPOKéMON fall out.$"
J_Text_IlexForestLass::
	.string "Did something\nhappen to the\lforest's guardian?$"
J_IlexForestSignpostText::
	.string "ILEX FOREST is\nso overgrown with\ptrees that you\ncan't see the sky.\pPlease watch out\nfor items that may\lhave been dropped.$"
J_Text_IlexForestShrine::
	.string "ILEX FOREST\nSHRINE…\pIt's in honor of\nthe forest's\lprotector…$"
J_Text_ShrineCelebiEvent::
	.string "ILEX FOREST\nSHRINE…\pIt's in honor of\nthe forest's\lprotector…\pOh? What is this?\pIt's a hole.\nIt looks like the\pGS BALL would fit\ninside it.\pWant to put the GS\nBALL here?$"
J_Text_InsertGSBall::
	.string "{PLAYER} put in the\nGS BALL.$"
J_Text_KurtCaughtCelebi::
	.string "Whew, wasn't that\nsomething!\p{PLAYER}, that was\nfantastic. Thanks!\pThe legends about\nthat SHRINE were\lreal after all.\pI feel inspired by\nwhat I just saw.\pIt motivates me to\nmake better BALLS!\pI'm going!$"
J_BugCatcherWayneSeenText::
	.string "Don't sneak up on\nme like that!\pYou frightened a\nPOKéMON away!$"
J_BugCatcherWayneBeatenText::
	.string "I hadn't seen that\nPOKéMON before…$"
J_BugCatcherWayneAfterBattleText::
	.string "A POKéMON I've\nnever seen before\pfell out of the\ntree when I used\lHEADBUTT.\pI ought to use\nHEADBUTT in other\lplaces too.$"
J_IlexForest_MapEvents::
