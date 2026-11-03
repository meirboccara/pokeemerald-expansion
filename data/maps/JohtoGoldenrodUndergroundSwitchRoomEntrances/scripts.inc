@ KJH: translated from pokecrystal maps/GoldenrodUndergroundSwitchRoomEntrances.asm by kjh_tools/johto

JohtoGoldenrodUndergroundSwitchRoomEntrances_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, JohtoGoldenrodUndergroundSwitchRoomEntrances_OnLoad
	.byte 0

JohtoGoldenrodUndergroundSwitchRoomEntrances_OnLoad:
	call J_KJH_OpenAllUGDoors
	end

J_T_TrainerBurglarDuncan::
	trainerbattle_single TRAINER_J_BURGLAR_DUNCAN, J_BurglarDuncanSeenText, J_BurglarDuncanBeatenText
	call J_TrainerBurglarDuncan_Script
	release
	end

J_T_TrainerBurglarEddie::
	trainerbattle_single TRAINER_J_BURGLAR_EDDIE, J_BurglarEddieSeenText, J_BurglarEddieBeatenText
	call J_TrainerBurglarEddie_Script
	release
	end

J_T_TrainerGruntM13::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_13, J_GruntM13SeenText, J_GruntM13BeatenText
	call J_TrainerGruntM13_Script
	release
	end

J_T_TrainerGruntM11::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_11, J_GruntM11SeenText, J_GruntM11BeatenText
	call J_TrainerGruntM11_Script
	release
	end

J_T_TrainerGruntM25::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_25, J_GruntM25SeenText, J_GruntM25BeatenText
	call J_TrainerGruntM25_Script
	release
	end

J_T_TrainerGruntF3::
	trainerbattle_single TRAINER_J_GRUNTF_GRUNTF_3, J_GruntF3SeenText, J_GruntF3BeatenText
	call J_TrainerGruntF3_Script
	release
	end

J_W_GoldenrodUndergroundSwitchRoomEntrancesTeacherScript::
	lock
	call J_GoldenrodUndergroundSwitchRoomEntrancesTeacherScript
	release
	end

J_W_GoldenrodUndergroundSwitchRoomEntrancesSuperNerdScript::
	lock
	call J_GoldenrodUndergroundSwitchRoomEntrancesSuperNerdScript
	release
	end

J_C_UndergroundRivalScene1::
	lockall
	call J_UndergroundRivalScene1
	releaseall
	end

J_C_UndergroundRivalScene2::
	lockall
	call J_UndergroundRivalScene2
	releaseall
	end

J_S_Switch1Script::
	lockall
	call J_Switch1Script
	releaseall
	end

J_S_Switch2Script::
	lockall
	call J_Switch2Script
	releaseall
	end

J_S_Switch3Script::
	lockall
	call J_Switch3Script
	releaseall
	end

J_S_EmergencySwitchScript::
	lockall
	call J_EmergencySwitchScript
	releaseall
	end

J_KJH_OpenAllUGDoors::
	setmetatile 16, 6, 5, FALSE
	setmetatile 17, 6, 5, FALSE
	setmetatile 16, 7, 5, FALSE
	setmetatile 17, 7, 5, FALSE
	setmetatile 10, 6, 5, FALSE
	setmetatile 11, 6, 5, FALSE
	setmetatile 10, 7, 5, FALSE
	setmetatile 11, 7, 5, FALSE
	setmetatile 2, 6, 5, FALSE
	setmetatile 3, 6, 5, FALSE
	setmetatile 2, 7, 5, FALSE
	setmetatile 3, 7, 5, FALSE
	setmetatile 2, 10, 5, FALSE
	setmetatile 3, 10, 5, FALSE
	setmetatile 2, 11, 5, FALSE
	setmetatile 3, 11, 5, FALSE
	setmetatile 10, 10, 5, FALSE
	setmetatile 11, 10, 5, FALSE
	setmetatile 10, 11, 5, FALSE
	setmetatile 11, 11, 5, FALSE
	setmetatile 16, 10, 5, FALSE
	setmetatile 17, 10, 5, FALSE
	setmetatile 16, 11, 5, FALSE
	setmetatile 17, 11, 5, FALSE
	setmetatile 12, 6, 10, TRUE
	setmetatile 13, 6, 11, TRUE
	setmetatile 12, 7, 12, TRUE
	setmetatile 13, 7, 12, TRUE
	setmetatile 12, 8, 5, FALSE
	setmetatile 13, 8, 5, FALSE
	setmetatile 12, 9, 5, FALSE
	setmetatile 13, 9, 5, FALSE
	setmetatile 6, 6, 10, TRUE
	setmetatile 7, 6, 11, TRUE
	setmetatile 6, 7, 12, TRUE
	setmetatile 7, 7, 12, TRUE
	setmetatile 6, 8, 5, FALSE
	setmetatile 7, 8, 5, FALSE
	setmetatile 6, 9, 5, FALSE
	setmetatile 7, 9, 5, FALSE
	setmetatile 12, 10, 10, TRUE
	setmetatile 13, 10, 11, TRUE
	setmetatile 12, 11, 12, TRUE
	setmetatile 13, 11, 12, TRUE
	setmetatile 12, 12, 5, FALSE
	setmetatile 13, 12, 5, FALSE
	setmetatile 12, 13, 5, FALSE
	setmetatile 13, 13, 5, FALSE
	setmetatile 6, 10, 10, TRUE
	setmetatile 7, 10, 11, TRUE
	setmetatile 6, 11, 12, TRUE
	setmetatile 7, 11, 12, TRUE
	setmetatile 6, 12, 5, FALSE
	setmetatile 7, 12, 5, FALSE
	setmetatile 6, 13, 5, FALSE
	setmetatile 7, 13, 5, FALSE
	setmetatile 18, 10, 10, TRUE
	setmetatile 19, 10, 11, TRUE
	setmetatile 18, 11, 12, TRUE
	setmetatile 19, 11, 12, TRUE
	setmetatile 18, 12, 5, FALSE
	setmetatile 19, 12, 5, FALSE
	setmetatile 18, 13, 5, FALSE
	setmetatile 19, 13, 5, FALSE
	return

	@ unhandled: shift 4
	setmetatile 0, 0, 9, TRUE
	setmetatile 1, 0, 9, TRUE
	setmetatile 0, 1, 9, TRUE
	setmetatile 1, 1, 9, TRUE
J_GoldenrodUndergroundSwitchRoomEntrances_MapScripts::
J_GoldenrodUndergroundSwitchRoomEntrancesNoop1Scene::
	return
J_GoldenrodUndergroundSwitchRoomEntrancesNoop2Scene::
	return
J_GoldenrodUndergroundSwitchRoomEntrancesUpdateDoorPositionsCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_DOOR_X_OPEN, J_L227
	setvar VAR_RESULT, 1
J_L227:
	goto_if_eq VAR_RESULT, 0, J_GoldenrodUndergroundSwitchRoomEntrancesUpdateDoorPositionsCallback_door__d_n__closed
	return
J_GoldenrodUndergroundSwitchRoomEntrancesSuperNerdScript::
	faceplayer
	message J_GoldenrodUndergroundSwitchRoomEntrances_SuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodUndergroundSwitchRoomEntrancesTeacherScript::
	faceplayer
	message J_GoldenrodUndergroundSwitchRoomEntrances_TeacherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_UndergroundRivalScene1::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	fadeoutbgm 0
	delay 15
	playse SE_EXIT
	addobject 11
	waitse
	applymovement 11, J_UndergroundRivalApproachMovement1
	waitmovement 11
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	call J_UndergroundRivalBattleScript
	applymovement 11, J_UndergroundRivalRetreatMovement1
	waitmovement 11
	playse SE_EXIT
	removeobject 11
	setvar VAR_J_SCENE_GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 1
	waitse
	fadedefaultbgm
	return
J_UndergroundRivalScene2::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	fadeoutbgm 0
	delay 15
	playse SE_EXIT
	addobject 11
	waitse
	applymovement 11, J_UndergroundRivalApproachMovement2
	waitmovement 11
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	call J_UndergroundRivalBattleScript
	applymovement 11, J_UndergroundRivalRetreatMovement2
	waitmovement 11
	playse SE_EXIT
	removeobject 11
	setvar VAR_J_SCENE_GOLDENROD_UNDERGROUND_SWITCH_ROOM_ENTRANCES, 1
	waitse
	fadedefaultbgm
	return
J_UndergroundRivalBattleScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RIVAL_BURNED_TOWER, J_L228
	setvar VAR_RESULT, 1
J_L228:
	goto_if_ne VAR_RESULT, 0, J_UndergroundRivalBattleScript_Continue
	setflag FLAG_J_RIVAL_BURNED_TOWER
	setvar VAR_J_SCENE_BURNED_TOWER_1F, 1
J_UndergroundRivalBattleScript_Continue:
	playbgm MUS_RG_ENCOUNTER_RIVAL, FALSE
	message J_UndergroundRivalBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_RIVAL_GOLDENROD_UNDERGROUND
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TOTODILE_FROM_ELM, J_L229
	setvar VAR_RESULT, 1
J_L229:
	goto_if_ne VAR_RESULT, 0, J_UndergroundRivalBattleScript_Totodile
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_CHIKORITA_FROM_ELM, J_L230
	setvar VAR_RESULT, 1
J_L230:
	goto_if_ne VAR_RESULT, 0, J_UndergroundRivalBattleScript_Chikorita
	setvar VAR_LAST_TALKED, 11
	trainerbattle_no_intro TRAINER_J_RIVAL1_RIVAL1_4_TOTODILE, J_UndergroundRivalWinText
	goto J_UndergroundRivalBattleScript_FinishRivalBattle
J_UndergroundRivalBattleScript_Totodile:
	setvar VAR_LAST_TALKED, 11
	trainerbattle_no_intro TRAINER_J_RIVAL1_RIVAL1_4_CHIKORITA, J_UndergroundRivalWinText
	goto J_UndergroundRivalBattleScript_FinishRivalBattle
J_UndergroundRivalBattleScript_Chikorita:
	setvar VAR_LAST_TALKED, 11
	trainerbattle_no_intro TRAINER_J_RIVAL1_RIVAL1_4_CYNDAQUIL, J_UndergroundRivalWinText
	goto J_UndergroundRivalBattleScript_FinishRivalBattle
J_UndergroundRivalBattleScript_FinishRivalBattle:
	playbgm MUS_RG_RIVAL_EXIT, FALSE
	message J_UndergroundRivalAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM11::
J_TrainerGruntM11_Script:
	message J_GruntM11AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM25::
J_TrainerGruntM25_Script:
	message J_GruntM25AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBurglarDuncan::
J_TrainerBurglarDuncan_Script:
	message J_BurglarDuncanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBurglarEddie::
J_TrainerBurglarEddie_Script:
	message J_BurglarEddieAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM13::
J_TrainerGruntM13_Script:
	message J_GruntM13AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntF3::
J_TrainerGruntF3_Script:
	message J_GruntF3AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Switch1Script::
	message J_SwitchRoomText_Switch1
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SWITCH_1, J_L231
	setvar VAR_RESULT, 1
J_L231:
	goto_if_ne VAR_RESULT, 0, J_Switch1Script_On
	message J_SwitchRoomText_OffTurnOn
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_GoldenrodUndergroundSwitchRoomEntrances_DontToggle
	copyvar VAR_RESULT, VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS
	addvar VAR_RESULT, 1
	copyvar VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS, VAR_RESULT
	setflag FLAG_J_SWITCH_1
	goto J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors
J_Switch1Script_On:
	message J_SwitchRoomText_OnTurnOff
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_GoldenrodUndergroundSwitchRoomEntrances_DontToggle
	copyvar VAR_RESULT, VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS
	addvar VAR_RESULT, -1
	copyvar VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS, VAR_RESULT
	clearflag FLAG_J_SWITCH_1
	goto J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors
J_Switch2Script::
	message J_SwitchRoomText_Switch2
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SWITCH_2, J_L232
	setvar VAR_RESULT, 1
J_L232:
	goto_if_ne VAR_RESULT, 0, J_Switch2Script_On
	message J_SwitchRoomText_OffTurnOn
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_GoldenrodUndergroundSwitchRoomEntrances_DontToggle
	copyvar VAR_RESULT, VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS
	addvar VAR_RESULT, 2
	copyvar VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS, VAR_RESULT
	setflag FLAG_J_SWITCH_2
	goto J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors
J_Switch2Script_On:
	message J_SwitchRoomText_OnTurnOff
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_GoldenrodUndergroundSwitchRoomEntrances_DontToggle
	copyvar VAR_RESULT, VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS
	addvar VAR_RESULT, -2
	copyvar VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS, VAR_RESULT
	clearflag FLAG_J_SWITCH_2
	goto J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors
J_Switch3Script::
	message J_SwitchRoomText_Switch3
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SWITCH_3, J_L233
	setvar VAR_RESULT, 1
J_L233:
	goto_if_ne VAR_RESULT, 0, J_Switch3Script_On
	message J_SwitchRoomText_OffTurnOn
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_GoldenrodUndergroundSwitchRoomEntrances_DontToggle
	copyvar VAR_RESULT, VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS
	addvar VAR_RESULT, 3
	copyvar VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS, VAR_RESULT
	setflag FLAG_J_SWITCH_3
	goto J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors
J_Switch3Script_On:
	message J_SwitchRoomText_OnTurnOff
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_GoldenrodUndergroundSwitchRoomEntrances_DontToggle
	copyvar VAR_RESULT, VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS
	addvar VAR_RESULT, -3
	copyvar VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS, VAR_RESULT
	clearflag FLAG_J_SWITCH_3
	goto J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors
J_EmergencySwitchScript::
	message J_SwitchRoomText_Emergency
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EMERGENCY_SWITCH, J_L234
	setvar VAR_RESULT, 1
J_L234:
	goto_if_ne VAR_RESULT, 0, J_EmergencySwitchScript_On
	message J_SwitchRoomText_OffTurnOn
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_GoldenrodUndergroundSwitchRoomEntrances_DontToggle
	setvar VAR_RESULT, 7
	copyvar VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS, VAR_RESULT
	setflag FLAG_J_EMERGENCY_SWITCH
	setflag FLAG_J_SWITCH_1
	setflag FLAG_J_SWITCH_2
	setflag FLAG_J_SWITCH_3
	goto J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors
J_EmergencySwitchScript_On:
	message J_SwitchRoomText_OnTurnOff
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_GoldenrodUndergroundSwitchRoomEntrances_DontToggle
	setvar VAR_RESULT, 0
	copyvar VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS, VAR_RESULT
	clearflag FLAG_J_EMERGENCY_SWITCH
	clearflag FLAG_J_SWITCH_1
	clearflag FLAG_J_SWITCH_2
	clearflag FLAG_J_SWITCH_3
	goto J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors
J_GoldenrodUndergroundSwitchRoomEntrances_DontToggle::
	closemessage
	return
J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors::
	copyvar VAR_RESULT, VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS
	goto_if_eq VAR_RESULT, 0, J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_Position0
	goto_if_eq VAR_RESULT, 1, J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_Position1
	goto_if_eq VAR_RESULT, 2, J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_Position2
	goto_if_eq VAR_RESULT, 3, J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_Position3
	goto_if_eq VAR_RESULT, 4, J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_Position4
	goto_if_eq VAR_RESULT, 5, J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_Position5
	goto_if_eq VAR_RESULT, 6, J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_Position6
	goto_if_eq VAR_RESULT, 7, J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_EmergencyPosition
J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_Position0:
	playse SE_DOOR
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor1
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor2
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor3
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor4
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor5
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor6
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor7
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor8
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor9
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor10
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor11
	special DrawWholeMapView
	closemessage
	return
J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_Position1:
	playse SE_DOOR
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor1
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor7
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor10
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor6
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor8
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor9
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor11
	special DrawWholeMapView
	closemessage
	return
J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_Position2:
	playse SE_DOOR
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor2
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor8
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor9
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor5
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor7
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor10
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor11
	special DrawWholeMapView
	closemessage
	return
J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_Position3:
	playse SE_DOOR
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor3
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor7
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor10
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor4
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor8
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor9
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor11
	special DrawWholeMapView
	closemessage
	return
J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_Position4:
	playse SE_DOOR
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor4
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor8
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor9
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor3
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor7
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor10
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor11
	special DrawWholeMapView
	closemessage
	return
J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_Position5:
	playse SE_DOOR
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor5
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor7
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor10
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor2
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor8
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor9
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor11
	special DrawWholeMapView
	closemessage
	return
J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_Position6:
	playse SE_DOOR
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor6
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor8
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor9
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor11
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor1
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor7
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor10
	special DrawWholeMapView
	closemessage
	return
J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_EmergencyPosition:
	playse SE_DOOR
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor1
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor2
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor3
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor4
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor5
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor6
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor7
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor8
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor9
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_CloseDoor10
	call J_GoldenrodUndergroundSwitchRoomEntrances_UpdateDoors_OpenDoor11
	special DrawWholeMapView
	closemessage
	setvar VAR_RESULT, 6
	copyvar VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS, VAR_RESULT
	return
	setflag FLAG_J_DOOR_X_OPEN
	return
	clearflag FLAG_J_DOOR_X_OPEN
	return
J_GoldenrodUndergroundSwitchRoomEntrancesSmokeBall::
	finditem ITEM_SMOKE_BALL, 1
	return
J_GoldenrodUndergroundSwitchRoomEntrancesFullHeal::
	finditem ITEM_FULL_HEAL, 1
	return
J_GoldenrodUndergroundSwitchRoomEntrancesHiddenMaxPotion::
	finditem ITEM_MAX_POTION
	return
J_GoldenrodUndergroundSwitchRoomEntrancesHiddenRevive::
	finditem ITEM_REVIVE
	return
J_UndergroundRivalApproachMovement1::
	walk_down
	walk_left
	walk_left
	walk_left
	step_end
J_UndergroundRivalApproachMovement2::
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end
J_UndergroundRivalRetreatMovement1::
	walk_right
	walk_right
	walk_right
	walk_up
	step_end
J_UndergroundRivalRetreatMovement2::
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	step_end
J_UndergroundRivalBeforeText::
	.string "Hold it!\pI saw you, so I\ntailed you.\pI don't need you\nunderfoot while I\ptake care of TEAM\nROCKET.\p…Wait a second.\nYou beat me be-\lfore, didn't you?\pThat was just a\nfluke.\pBut I repay my\ndebts!$"
J_UndergroundRivalWinText::
	.string "…Why…\nWhy do I lose?\pI've assembled the\ntoughest POKéMON.\pI didn't ease up\non the gas.\pSo why do I lose?$"
J_UndergroundRivalAfterText::
	.string "…I don't under-\nstand…\pIs what that LANCE\nguy said true?\pThat I don't treat\nPOKéMON properly?\pLove…\pTrust…\pAre they really\nwhat I lack?\pAre they keeping\nme from winning?\pI… I just don't\nunderstand.\pBut it's not going\nto end here.\pNot now. Not\nbecause of this.\pI won't give up my\ndream of becoming\pthe world's best\nPOKéMON trainer!$"
J_UndergroundRivalLossText::
	.string "Humph. This is my\nreal power, wimp.\pI'll make TEAM\nROCKET history.\pAnd I'm going to\ngrind that LANCE\lunder my heels.$"
J_GoldenrodUndergroundSwitchRoomEntrances_SuperNerdText::
	.string "I was challenged\nto a battle down-\lstairs.\pIt's rough down\nthere. You'd\lbetter be careful.$"
J_GoldenrodUndergroundSwitchRoomEntrances_TeacherText::
	.string "There are some\nshops downstairs…\pBut there are\nalso trainers.\pI'm scared to go\ndown there.$"
J_GruntM11SeenText::
	.string "Open one shutter,\nanother closes.\pBet you can't get\nwhere you want!$"
J_GruntM11BeatenText::
	.string "Drat! I was sunk\nby indecision!$"
J_GruntM11AfterBattleText::
	.string "I'm confused too…\nThe switch on the\pend is the one to\npress first, but…$"
J_GruntM25SeenText::
	.string "Kwahaha!\pConfounded by the\nshutters, are we?\pI'll let you in on\na secret if you\lcan beat me!$"
J_GruntM25BeatenText::
	.string "Uwww…\nI blew it.$"
J_GruntM25AfterBattleText::
	.string "All right. A hint!\pChange the order\nof switching.\pThat'll change the\nways the shutters\lopen and close.$"
J_BurglarDuncanSeenText::
	.string "Fork over your\ngoodies!$"
J_BurglarDuncanBeatenText::
	.string "Mercy!$"
J_BurglarDuncanAfterBattleText::
	.string "Steal and sell!\nThat's basic in\lcrime, kid!$"
J_BurglarEddieSeenText::
	.string "They ditched this\nproject before\lthey finished.\pI'm searching for\nleftover loot.$"
J_BurglarEddieBeatenText::
	.string "Over the top!$"
J_BurglarEddieAfterBattleText::
	.string "UNDERGROUND WARE-\nHOUSE?\pWhat do you want\nto go there for?\pThere's nothing\ndown there.$"
J_GruntM13SeenText::
	.string "I don't care if\nyou're lost.\pYou show up here,\nyou're nothing but\la victim!$"
J_GruntM13BeatenText::
	.string "Urk! Yeah, think\nyou're cool, huh?$"
J_GruntM13AfterBattleText::
	.string "You must have ice\nin your veins to\ldis TEAM ROCKET.$"
J_SwitchRoomText_Switch1::
	.string "It's labeled\nSWITCH 1.$"
J_GruntF3SeenText::
	.string "Are you lost? No,\nyou can't be.\pYou don't have\nthat scared look.\pI'll give you\nsomething to be\lscared about!$"
J_GruntF3BeatenText::
	.string "How could you?$"
J_GruntF3AfterBattleText::
	.string "Go wherever you'd\nlike! Get lost!\lSee if I care!$"
J_SwitchRoomText_OffTurnOn::
	.string "It's OFF.\nTurn it ON?$"
J_SwitchRoomText_OnTurnOff::
	.string "It's ON.\nTurn it OFF?$"
J_SwitchRoomText_Switch2::
	.string "It's labeled\nSWITCH 2.$"
J_SwitchRoomText_Switch3::
	.string "It's labeled\nSWITCH 3.$"
J_SwitchRoomText_Emergency::
	.string "It's labeled\nEMERGENCY.$"
J_GoldenrodUndergroundSwitchRoomEntrances_MapEvents::
