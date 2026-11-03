@ KJH: translated from pokecrystal maps/RuinsOfAlphAerodactylChamber.asm by kjh_tools/johto

JohtoRuinsOfAlphAerodactylChamber_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, JohtoRuinsOfAlphAerodactylChamber_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoRuinsOfAlphAerodactylChamber_OnFrame
	.byte 0

JohtoRuinsOfAlphAerodactylChamber_OnLoad:
	call J_RuinsOfAlphAerodactylChamberHiddenDoorsCallback
	end

JohtoRuinsOfAlphAerodactylChamber_OnFrame:
	map_script_2 VAR_J_SCENE_RUINS_OF_ALPH_AERODACTYL_CHAMBER, 0, J_SC_RuinsOfAlphAerodactylChamberCheckWallScene
	.2byte 0

J_S_RuinsOfAlphAerodactylChamberAncientReplica::
	lockall
	call J_RuinsOfAlphAerodactylChamberAncientReplica
	releaseall
	end

J_S_RuinsOfAlphAerodactylChamberPuzzle::
	lockall
	call J_RuinsOfAlphAerodactylChamberPuzzle
	releaseall
	end

J_S_RuinsOfAlphAerodactylChamberDescriptionSign::
	lockall
	call J_RuinsOfAlphAerodactylChamberDescriptionSign
	releaseall
	end

J_S_RuinsOfAlphAerodactylChamberWallPatternLeft::
	lockall
	call J_RuinsOfAlphAerodactylChamberWallPatternLeft
	releaseall
	end

J_S_RuinsOfAlphAerodactylChamberWallPatternRight::
	lockall
	call J_RuinsOfAlphAerodactylChamberWallPatternRight
	releaseall
	end

J_SC_RuinsOfAlphAerodactylChamberCheckWallScene::
	lockall
	call J_RuinsOfAlphAerodactylChamberCheckWallScene
	releaseall
	end

J_RuinsOfAlphAerodactylChamber_MapScripts::
J_RuinsOfAlphAerodactylChamberCheckWallScene::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WALL_OPENED_IN_AERODACTYL_CHAMBER, J_L129
	setvar VAR_RESULT, 1
J_L129:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphAerodactylChamberCheckWallScene_OpenWall
	return
J_RuinsOfAlphAerodactylChamberCheckWallScene_OpenWall:
	call J_RuinsOfAlphAerodactylChamberWallOpenScript
	return
J_RuinsOfAlphAerodactylChamberNoopScene::
	return
J_RuinsOfAlphAerodactylChamberHiddenDoorsCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WALL_OPENED_IN_AERODACTYL_CHAMBER, J_L130
	setvar VAR_RESULT, 1
J_L130:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphAerodactylChamberHiddenDoorsCallback_WallOpen
	setmetatile 4, 0, 37, TRUE
	setmetatile 5, 0, 5, TRUE
	setmetatile 4, 1, 8, FALSE
	setmetatile 5, 1, 8, FALSE
J_RuinsOfAlphAerodactylChamberHiddenDoorsCallback_WallOpen:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SOLVED_AERODACTYL_PUZZLE, J_L131
	setvar VAR_RESULT, 1
J_L131:
	goto_if_eq VAR_RESULT, 0, J_RuinsOfAlphAerodactylChamberHiddenDoorsCallback_FloorClosed
	return
J_RuinsOfAlphAerodactylChamberHiddenDoorsCallback_FloorClosed:
	setmetatile 2, 2, 9, TRUE
	setmetatile 3, 2, 10, TRUE
	setmetatile 2, 3, 12, TRUE
	setmetatile 3, 3, 38, FALSE
	setmetatile 4, 2, 11, TRUE
	setmetatile 5, 2, 9, TRUE
	setmetatile 4, 3, 39, FALSE
	setmetatile 5, 3, 12, TRUE
	return
J_RuinsOfAlphAerodactylChamberWallOpenScript::
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
	setvar VAR_J_SCENE_RUINS_OF_ALPH_AERODACTYL_CHAMBER, 1
	closemessage
	return
J_RuinsOfAlphAerodactylChamberPuzzle::
	special DrawWholeMapView
	setvar VAR_RESULT, 2
	setvar VAR_RESULT, 0
	closemessage
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphAerodactylChamberPuzzle_PuzzleComplete
	return
J_RuinsOfAlphAerodactylChamberPuzzle_PuzzleComplete:
	setflag FLAG_J_RUINS_OF_ALPH_INNER_CHAMBER_TOURISTS
	setflag FLAG_J_SOLVED_AERODACTYL_PUZZLE
	setflag FLAG_J_ENGINE_UNLOCKED_UNOWNS_S_TO_W
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
	applymovement OBJ_EVENT_ID_PLAYER, J_RuinsOfAlphAerodactylChamberSkyfallTopMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_M_TELEPORT
	waitse
	delay 20
	return
J_RuinsOfAlphAerodactylChamberAncientReplica::
	message J_RuinsOfAlphAerodactylChamberAncientReplicaText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphAerodactylChamberDescriptionSign::
	message J_RuinsOfAlphAerodactylChamberDescriptionText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphAerodactylChamberWallPatternLeft::
	message J_RuinsOfAlphAerodactylChamberWallPatternLeftText
	waitmessage
	setvar VAR_RESULT, 1
	closemessage
	return
J_RuinsOfAlphAerodactylChamberWallPatternRight::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WALL_OPENED_IN_AERODACTYL_CHAMBER, J_L132
	setvar VAR_RESULT, 1
J_L132:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphAerodactylChamberWallPatternRight_WallOpen
	message J_RuinsOfAlphAerodactylChamberWallPatternRightText
	waitmessage
	setvar VAR_RESULT, 1
	closemessage
	return
J_RuinsOfAlphAerodactylChamberWallPatternRight_WallOpen:
	message J_RuinsOfAlphAerodactylChamberWallHoleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphAerodactylChamberSkyfallTopMovement::
	step_end
J_RuinsOfAlphAerodactylChamberWallPatternLeftText::
	.string "Patterns appeared\non the walls…$"
J_RuinsOfAlphAerodactylChamberUnownText::
	.string "It's UNOWN text!$"
J_RuinsOfAlphAerodactylChamberWallPatternRightText::
	.string "Patterns appeared\non the walls…$"
J_RuinsOfAlphAerodactylChamberWallHoleText::
	.string "There's a big hole\nin the wall!$"
J_RuinsOfAlphAerodactylChamberAncientReplicaText::
	.string "It's a replica of\nan ancient POKé-\lMON.$"
J_RuinsOfAlphAerodactylChamberDescriptionText::
	.string "This flying POKé-\nMON attacked its\pprey with saw-like\nfangs.$"
J_RuinsOfAlphAerodactylChamber_MapEvents::
