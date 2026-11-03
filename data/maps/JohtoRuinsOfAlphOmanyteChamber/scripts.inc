@ KJH: translated from pokecrystal maps/RuinsOfAlphOmanyteChamber.asm by kjh_tools/johto

JohtoRuinsOfAlphOmanyteChamber_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, JohtoRuinsOfAlphOmanyteChamber_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoRuinsOfAlphOmanyteChamber_OnFrame
	.byte 0

JohtoRuinsOfAlphOmanyteChamber_OnLoad:
	call J_RuinsOfAlphOmanyteChamberHiddenDoorsCallback
	end

JohtoRuinsOfAlphOmanyteChamber_OnFrame:
	map_script_2 VAR_J_SCENE_RUINS_OF_ALPH_OMANYTE_CHAMBER, 0, J_SC_RuinsOfAlphOmanyteChamberCheckWallScene
	.2byte 0

J_S_RuinsOfAlphOmanyteChamberAncientReplica::
	lockall
	call J_RuinsOfAlphOmanyteChamberAncientReplica
	releaseall
	end

J_S_RuinsOfAlphOmanyteChamberPuzzle::
	lockall
	call J_RuinsOfAlphOmanyteChamberPuzzle
	releaseall
	end

J_S_RuinsOfAlphOmanyteChamberDescriptionSign::
	lockall
	call J_RuinsOfAlphOmanyteChamberDescriptionSign
	releaseall
	end

J_S_RuinsOfAlphOmanyteChamberWallPatternLeft::
	lockall
	call J_RuinsOfAlphOmanyteChamberWallPatternLeft
	releaseall
	end

J_S_RuinsOfAlphOmanyteChamberWallPatternRight::
	lockall
	call J_RuinsOfAlphOmanyteChamberWallPatternRight
	releaseall
	end

J_SC_RuinsOfAlphOmanyteChamberCheckWallScene::
	lockall
	call J_RuinsOfAlphOmanyteChamberCheckWallScene
	releaseall
	end

J_RuinsOfAlphOmanyteChamber_MapScripts::
J_RuinsOfAlphOmanyteChamberCheckWallScene::
	setvar VAR_RESULT, 0
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WALL_OPENED_IN_OMANYTE_CHAMBER, J_L125
	setvar VAR_RESULT, 1
J_L125:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphOmanyteChamberCheckWallScene_OpenWall
	return
J_RuinsOfAlphOmanyteChamberCheckWallScene_OpenWall:
	call J_RuinsOfAlphOmanyteChamberWallOpenScript
	return
J_RuinsOfAlphOmanyteChamberNoopScene::
	return
J_RuinsOfAlphOmanyteChamberHiddenDoorsCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WALL_OPENED_IN_OMANYTE_CHAMBER, J_L126
	setvar VAR_RESULT, 1
J_L126:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphOmanyteChamberHiddenDoorsCallback_WallOpen
	setmetatile 4, 0, 37, TRUE
	setmetatile 5, 0, 5, TRUE
	setmetatile 4, 1, 8, FALSE
	setmetatile 5, 1, 8, FALSE
J_RuinsOfAlphOmanyteChamberHiddenDoorsCallback_WallOpen:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SOLVED_OMANYTE_PUZZLE, J_L127
	setvar VAR_RESULT, 1
J_L127:
	goto_if_eq VAR_RESULT, 0, J_RuinsOfAlphOmanyteChamberHiddenDoorsCallback_FloorClosed
	return
J_RuinsOfAlphOmanyteChamberHiddenDoorsCallback_FloorClosed:
	setmetatile 2, 2, 9, TRUE
	setmetatile 3, 2, 10, TRUE
	setmetatile 2, 3, 12, TRUE
	setmetatile 3, 3, 38, FALSE
	setmetatile 4, 2, 11, TRUE
	setmetatile 5, 2, 9, TRUE
	setmetatile 4, 3, 39, FALSE
	setmetatile 5, 3, 12, TRUE
	return
J_RuinsOfAlphOmanyteChamberWallOpenScript::
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
	setvar VAR_J_SCENE_RUINS_OF_ALPH_OMANYTE_CHAMBER, 1
	closemessage
	return
J_RuinsOfAlphOmanyteChamberPuzzle::
	special DrawWholeMapView
	setvar VAR_RESULT, 1
	setvar VAR_RESULT, 0
	closemessage
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphOmanyteChamberPuzzle_PuzzleComplete
	return
J_RuinsOfAlphOmanyteChamberPuzzle_PuzzleComplete:
	setflag FLAG_J_RUINS_OF_ALPH_INNER_CHAMBER_TOURISTS
	setflag FLAG_J_SOLVED_OMANYTE_PUZZLE
	setflag FLAG_J_ENGINE_UNLOCKED_UNOWNS_L_TO_R
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
	applymovement OBJ_EVENT_ID_PLAYER, J_RuinsOfAlphOmanyteChamberSkyfallTopMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_M_TELEPORT
	waitse
	delay 20
	return
J_RuinsOfAlphOmanyteChamberAncientReplica::
	message J_RuinsOfAlphOmanyteChamberAncientReplicaText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphOmanyteChamberDescriptionSign::
	message J_RuinsOfAlphOmanyteChamberDescriptionText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphOmanyteChamberWallPatternLeft::
	message J_RuinsOfAlphOmanyteChamberWallPatternLeftText
	waitmessage
	setvar VAR_RESULT, 2
	closemessage
	return
J_RuinsOfAlphOmanyteChamberWallPatternRight::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WALL_OPENED_IN_OMANYTE_CHAMBER, J_L128
	setvar VAR_RESULT, 1
J_L128:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphOmanyteChamberWallPatternRight_WallOpen
	message J_RuinsOfAlphOmanyteChamberWallPatternRightText
	waitmessage
	setvar VAR_RESULT, 2
	closemessage
	return
J_RuinsOfAlphOmanyteChamberWallPatternRight_WallOpen:
	message J_RuinsOfAlphOmanyteChamberWallHoleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphOmanyteChamberSkyfallTopMovement::
	step_end
J_RuinsOfAlphOmanyteChamberWallPatternLeftText::
	.string "Patterns appeared\non the walls…$"
J_RuinsOfAlphOmanyteChamberUnownText::
	.string "It's UNOWN text!$"
J_RuinsOfAlphOmanyteChamberWallPatternRightText::
	.string "Patterns appeared\non the walls…$"
J_RuinsOfAlphOmanyteChamberWallHoleText::
	.string "There's a big hole\nin the wall!$"
J_RuinsOfAlphOmanyteChamberAncientReplicaText::
	.string "It's a replica of\nan ancient POKé-\lMON.$"
J_RuinsOfAlphOmanyteChamberDescriptionText::
	.string "This POKéMON\ndrifted in the\psea by twisting\nits ten tentacles.$"
J_RuinsOfAlphOmanyteChamber_MapEvents::
