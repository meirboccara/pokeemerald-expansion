@ KJH: translated from pokecrystal maps/RuinsOfAlphHoOhChamber.asm by kjh_tools/johto

JohtoRuinsOfAlphHoOhChamber_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, JohtoRuinsOfAlphHoOhChamber_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoRuinsOfAlphHoOhChamber_OnFrame
	.byte 0

JohtoRuinsOfAlphHoOhChamber_OnLoad:
	call J_RuinsOfAlphHoOhChamberHiddenDoorsCallback
	end

JohtoRuinsOfAlphHoOhChamber_OnFrame:
	map_script_2 VAR_J_SCENE_RUINS_OF_ALPH_HO_OH_CHAMBER, 0, J_SC_RuinsOfAlphHoOhChamberCheckWallScene
	.2byte 0

J_S_RuinsOfAlphHoOhChamberAncientReplica::
	lockall
	call J_RuinsOfAlphHoOhChamberAncientReplica
	releaseall
	end

J_S_RuinsOfAlphHoOhChamberPuzzle::
	lockall
	call J_RuinsOfAlphHoOhChamberPuzzle
	releaseall
	end

J_S_RuinsOfAlphHoOhChamberDescriptionSign::
	lockall
	call J_RuinsOfAlphHoOhChamberDescriptionSign
	releaseall
	end

J_S_RuinsOfAlphHoOhChamberWallPatternLeft::
	lockall
	call J_RuinsOfAlphHoOhChamberWallPatternLeft
	releaseall
	end

J_S_RuinsOfAlphHoOhChamberWallPatternRight::
	lockall
	call J_RuinsOfAlphHoOhChamberWallPatternRight
	releaseall
	end

J_SC_RuinsOfAlphHoOhChamberCheckWallScene::
	lockall
	call J_RuinsOfAlphHoOhChamberCheckWallScene
	releaseall
	end

J_RuinsOfAlphHoOhChamber_MapScripts::
J_RuinsOfAlphHoOhChamberCheckWallScene::
	setvar VAR_RESULT, 0
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WALL_OPENED_IN_HO_OH_CHAMBER, J_L115
	setvar VAR_RESULT, 1
J_L115:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphHoOhChamberCheckWallScene_OpenWall
	return
J_RuinsOfAlphHoOhChamberCheckWallScene_OpenWall:
	call J_RuinsOfAlphHoOhChamberWallOpenScript
	return
J_RuinsOfAlphHoOhChamberNoopScene::
	return
J_RuinsOfAlphHoOhChamberHiddenDoorsCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WALL_OPENED_IN_HO_OH_CHAMBER, J_L116
	setvar VAR_RESULT, 1
J_L116:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphHoOhChamberHiddenDoorsCallback_WallOpen
	setmetatile 4, 0, 37, TRUE
	setmetatile 5, 0, 5, TRUE
	setmetatile 4, 1, 8, FALSE
	setmetatile 5, 1, 8, FALSE
J_RuinsOfAlphHoOhChamberHiddenDoorsCallback_WallOpen:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SOLVED_HO_OH_PUZZLE, J_L117
	setvar VAR_RESULT, 1
J_L117:
	goto_if_eq VAR_RESULT, 0, J_RuinsOfAlphHoOhChamberHiddenDoorsCallback_FloorClosed
	return
J_RuinsOfAlphHoOhChamberHiddenDoorsCallback_FloorClosed:
	setmetatile 2, 2, 9, TRUE
	setmetatile 3, 2, 10, TRUE
	setmetatile 2, 3, 12, TRUE
	setmetatile 3, 3, 38, FALSE
	setmetatile 4, 2, 11, TRUE
	setmetatile 5, 2, 9, TRUE
	setmetatile 4, 3, 39, FALSE
	setmetatile 5, 3, 12, TRUE
	return
J_RuinsOfAlphHoOhChamberWallOpenScript::
	delay 30
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 4
	special ShakeScreen
	delay 40
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	delay 30
	playse SE_M_STRENGTH
	setmetatile 4, 0, 4, FALSE
	setmetatile 5, 0, 5, TRUE
	setmetatile 4, 1, 8, FALSE
	setmetatile 5, 1, 8, FALSE
	special DrawWholeMapView
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 4
	special ShakeScreen
	delay 40
	setvar VAR_J_SCENE_RUINS_OF_ALPH_HO_OH_CHAMBER, 1
	closemessage
	return
J_RuinsOfAlphHoOhChamberPuzzle::
	special DrawWholeMapView
	setvar VAR_RESULT, 3
	setvar VAR_RESULT, 0
	closemessage
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphHoOhChamberPuzzle_PuzzleComplete
	return
J_RuinsOfAlphHoOhChamberPuzzle_PuzzleComplete:
	setflag FLAG_J_RUINS_OF_ALPH_INNER_CHAMBER_TOURISTS
	setflag FLAG_J_SOLVED_HO_OH_PUZZLE
	setflag FLAG_J_ENGINE_UNLOCKED_UNOWNS_X_TO_Z
	setvar VAR_J_SCENE_RUINS_OF_ALPH_INNER_CHAMBER, 1
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 4
	special ShakeScreen
	delay 40
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	setmetatile 2, 2, 9, TRUE
	setmetatile 3, 2, 10, TRUE
	setmetatile 2, 3, 12, TRUE
	setmetatile 3, 3, 13, FALSE
	setmetatile 4, 2, 11, TRUE
	setmetatile 5, 2, 9, TRUE
	setmetatile 4, 3, 13, FALSE
	setmetatile 5, 3, 12, TRUE
	special DrawWholeMapView
	playse SE_M_STRENGTH
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 4
	special ShakeScreen
	delay 40
	applymovement OBJ_EVENT_ID_PLAYER, J_RuinsOfAlphHoOhChamberSkyfallTopMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_M_TELEPORT
	waitse
	delay 20
	return
J_RuinsOfAlphHoOhChamberAncientReplica::
	message J_RuinsOfAlphHoOhChamberAncientReplicaText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphHoOhChamberDescriptionSign::
	message J_RuinsOfAlphHoOhChamberDescriptionText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphHoOhChamberWallPatternLeft::
	message J_RuinsOfAlphHoOhChamberWallPatternLeftText
	waitmessage
	setvar VAR_RESULT, 3
	closemessage
	return
J_RuinsOfAlphHoOhChamberWallPatternRight::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WALL_OPENED_IN_HO_OH_CHAMBER, J_L118
	setvar VAR_RESULT, 1
J_L118:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphHoOhChamberWallPatternRight_WallOpen
	message J_RuinsOfAlphHoOhChamberWallPatternRightText
	waitmessage
	setvar VAR_RESULT, 3
	closemessage
	return
J_RuinsOfAlphHoOhChamberWallPatternRight_WallOpen:
	message J_RuinsOfAlphHoOhChamberWallHoleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphHoOhChamberSkyfallTopMovement::
	step_end
J_RuinsOfAlphHoOhChamberWallPatternLeftText::
	.string "Patterns appeared\non the walls…$"
J_RuinsOfAlphHoOhChamberUnownText::
	.string "It's UNOWN text!$"
J_RuinsOfAlphHoOhChamberWallPatternRightText::
	.string "Patterns appeared\non the walls…$"
J_RuinsOfAlphHoOhChamberWallHoleText::
	.string "There's a big hole\nin the wall!$"
J_RuinsOfAlphHoOhChamberAncientReplicaText::
	.string "It's a replica of\nan ancient POKé-\lMON.$"
J_RuinsOfAlphHoOhChamberDescriptionText::
	.string "A POKéMON that\nflew gracefully on\prainbow-colored\nwings.$"
J_RuinsOfAlphHoOhChamber_MapEvents::
