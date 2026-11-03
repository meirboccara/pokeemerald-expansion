@ KJH: translated from pokecrystal maps/RuinsOfAlphKabutoChamber.asm by kjh_tools/johto

JohtoRuinsOfAlphKabutoChamber_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, JohtoRuinsOfAlphKabutoChamber_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoRuinsOfAlphKabutoChamber_OnFrame
	.byte 0

JohtoRuinsOfAlphKabutoChamber_OnLoad:
	call J_RuinsOfAlphKabutoChamberHiddenDoorsCallback
	end

JohtoRuinsOfAlphKabutoChamber_OnFrame:
	map_script_2 VAR_J_SCENE_RUINS_OF_ALPH_KABUTO_CHAMBER, 0, J_SC_RuinsOfAlphKabutoChamberCheckWallScene
	.2byte 0

J_W_RuinsOfAlphKabutoChamberReceptionistScript::
	lock
	call J_RuinsOfAlphKabutoChamberReceptionistScript
	release
	end

J_W_RuinsOfAlphKabutoChamberScientistScript::
	lock
	call J_RuinsOfAlphKabutoChamberScientistScript
	release
	end

J_S_RuinsOfAlphKabutoChamberAncientReplica::
	lockall
	call J_RuinsOfAlphKabutoChamberAncientReplica
	releaseall
	end

J_S_RuinsOfAlphKabutoChamberPuzzle::
	lockall
	call J_RuinsOfAlphKabutoChamberPuzzle
	releaseall
	end

J_S_RuinsOfAlphKabutoChamberDescriptionSign::
	lockall
	call J_RuinsOfAlphKabutoChamberDescriptionSign
	releaseall
	end

J_S_RuinsOfAlphKabutoChamberWallPatternLeft::
	lockall
	call J_RuinsOfAlphKabutoChamberWallPatternLeft
	releaseall
	end

J_S_RuinsOfAlphKabutoChamberWallPatternRight::
	lockall
	call J_RuinsOfAlphKabutoChamberWallPatternRight
	releaseall
	end

J_SC_RuinsOfAlphKabutoChamberCheckWallScene::
	lockall
	call J_RuinsOfAlphKabutoChamberCheckWallScene
	releaseall
	end

J_RuinsOfAlphKabutoChamber_MapScripts::
J_RuinsOfAlphKabutoChamberCheckWallScene::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WALL_OPENED_IN_KABUTO_CHAMBER, J_L119
	setvar VAR_RESULT, 1
J_L119:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphKabutoChamberCheckWallScene_OpenWall
	return
J_RuinsOfAlphKabutoChamberCheckWallScene_OpenWall:
	call J_RuinsOfAlphKabutoChamberWallOpenScript
	return
J_RuinsOfAlphKabutoChamberNoopScene::
	return
J_RuinsOfAlphKabutoChamberHiddenDoorsCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WALL_OPENED_IN_KABUTO_CHAMBER, J_L120
	setvar VAR_RESULT, 1
J_L120:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphKabutoChamberHiddenDoorsCallback_WallOpen
	setmetatile 4, 0, 37, TRUE
	setmetatile 5, 0, 5, TRUE
	setmetatile 4, 1, 8, FALSE
	setmetatile 5, 1, 8, FALSE
J_RuinsOfAlphKabutoChamberHiddenDoorsCallback_WallOpen:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SOLVED_KABUTO_PUZZLE, J_L121
	setvar VAR_RESULT, 1
J_L121:
	goto_if_eq VAR_RESULT, 0, J_RuinsOfAlphKabutoChamberHiddenDoorsCallback_FloorClosed
	return
J_RuinsOfAlphKabutoChamberHiddenDoorsCallback_FloorClosed:
	setmetatile 2, 2, 9, TRUE
	setmetatile 3, 2, 10, TRUE
	setmetatile 2, 3, 12, TRUE
	setmetatile 3, 3, 38, FALSE
	setmetatile 4, 2, 11, TRUE
	setmetatile 5, 2, 9, TRUE
	setmetatile 4, 3, 39, FALSE
	setmetatile 5, 3, 12, TRUE
	return
J_RuinsOfAlphKabutoChamberWallOpenScript::
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
	setvar VAR_J_SCENE_RUINS_OF_ALPH_KABUTO_CHAMBER, 1
	closemessage
	return
J_RuinsOfAlphKabutoChamberReceptionistScript::
	faceplayer
	message J_RuinsOfAlphKabutoChamberReceptionistText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphKabutoChamberPuzzle::
	special DrawWholeMapView
	setvar VAR_RESULT, 0
	setvar VAR_RESULT, 0
	closemessage
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphKabutoChamberPuzzle_PuzzleComplete
	return
J_RuinsOfAlphKabutoChamberPuzzle_PuzzleComplete:
	setflag FLAG_J_RUINS_OF_ALPH_INNER_CHAMBER_TOURISTS
	setflag FLAG_J_SOLVED_KABUTO_PUZZLE
	setflag FLAG_J_ENGINE_UNLOCKED_UNOWNS_A_TO_K
	setflag FLAG_J_RUINS_OF_ALPH_KABUTO_CHAMBER_RECEPTIONIST
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
	applymovement OBJ_EVENT_ID_PLAYER, J_RuinsOfAlphKabutoChamberSkyfallTopMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_M_TELEPORT
	waitse
	delay 20
	return
J_RuinsOfAlphKabutoChamberScientistScript::
	faceplayer
	setvar VAR_0x8004, 14
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 26, J_RuinsOfAlphKabutoChamberScientistScript_AllUnownCaught
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WALL_OPENED_IN_KABUTO_CHAMBER, J_L122
	setvar VAR_RESULT, 1
J_L122:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphKabutoChamberScientistScript_WallOpen
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SOLVED_KABUTO_PUZZLE, J_L123
	setvar VAR_RESULT, 1
J_L123:
	goto_if_eq VAR_RESULT, 0, J_RuinsOfAlphKabutoChamberScientistScript_PuzzleIncomplete
	message J_RuinsOfAlphKabutoChamberScientistTremorText
	waitmessage
	waitbuttonpress
J_RuinsOfAlphKabutoChamberScientistScript_PuzzleIncomplete:
	message J_RuinsOfAlphKabutoChamberScientistCrypticText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 2, DIR_NORTH
	return
J_RuinsOfAlphKabutoChamberScientistScript_WallOpen:
	message J_RuinsOfAlphKabutoChamberScientistHoleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphKabutoChamberScientistScript_AllUnownCaught:
	message J_RuinsOfAlphResearchCenterScientist1Text_GotAllUnown
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphKabutoChamberAncientReplica::
	message J_RuinsOfAlphKabutoChamberAncientReplicaText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphKabutoChamberDescriptionSign::
	message J_RuinsOfAlphKabutoChamberDescriptionText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphKabutoChamberWallPatternLeft::
	message J_RuinsOfAlphKabutoChamberWallPatternLeftText
	waitmessage
	setvar VAR_RESULT, 0
	closemessage
	return
J_RuinsOfAlphKabutoChamberWallPatternRight::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WALL_OPENED_IN_KABUTO_CHAMBER, J_L124
	setvar VAR_RESULT, 1
J_L124:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphKabutoChamberWallPatternRight_WallOpen
	message J_RuinsOfAlphKabutoChamberWallPatternRightText
	waitmessage
	setvar VAR_RESULT, 0
	closemessage
	return
J_RuinsOfAlphKabutoChamberWallPatternRight_WallOpen:
	message J_RuinsOfAlphKabutoChamberWallHoleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphKabutoChamberSkyfallTopMovement::
	step_end
J_RuinsOfAlphKabutoChamberReceptionistText::
	.string "Welcome to this\nchamber.\pThere are sliding\npanels that depict\pa POKéMON drawn by\nthe ancients.\pSlide the panels\naround to form the\lpicture.\pTo the right is a\ndescription of the\lPOKéMON.\pScientists in the\nback are examining\psome newly found\npatterns.$"
J_RuinsOfAlphKabutoChamberScientistCrypticText::
	.string "Recently, strange,\ncryptic patterns\lhave appeared.\pIt's odd. They\nweren't here a\llittle while ago…\pYou should take a\nlook at the walls.$"
J_RuinsOfAlphKabutoChamberScientistHoleText::
	.string "Ah! Here's another\nhuge hole!\pIt's big enough to\ngo through!$"
J_RuinsOfAlphKabutoChamberScientistTremorText::
	.string "That tremor was\npretty scary!\pBut I'm more\nconcerned about\lthis wall here…$"
J_RuinsOfAlphKabutoChamberUnusedText::
	.string "The patterns on\nthe wall appear to\lbe words!\pAnd those sliding\nstone panels seem\pto be signals of\nsome kind.\pI think they make\nPOKéMON appear,\pbut it's not clear\nyet…$"
J_RuinsOfAlphKabutoChamberWallPatternLeftText::
	.string "Patterns appeared\non the walls…$"
J_RuinsOfAlphKabutoChamberUnownText::
	.string "It's UNOWN text!$"
J_RuinsOfAlphKabutoChamberWallPatternRightText::
	.string "Patterns appeared\non the walls…$"
J_RuinsOfAlphKabutoChamberWallHoleText::
	.string "There's a big hole\nin the wall!$"
J_RuinsOfAlphKabutoChamberAncientReplicaText::
	.string "It's a replica of\nan ancient POKé-\lMON.$"
J_RuinsOfAlphKabutoChamberDescriptionText::
	.string "A POKéMON that hid\non the sea floor.\pEyes on its back\nscanned the area.$"
J_RuinsOfAlphKabutoChamber_MapEvents::
