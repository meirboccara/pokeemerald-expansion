@ KJH: translated from pokecrystal maps/MahoganyMart1F.asm by kjh_tools/johto

JohtoMahoganyMart1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, JohtoMahoganyMart1F_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoMahoganyMart1F_OnFrame
	.byte 0

JohtoMahoganyMart1F_OnLoad:
	call J_MahoganyMart1FStaircaseCallback
	end

JohtoMahoganyMart1F_OnFrame:
	map_script_2 VAR_J_SCENE_MAHOGANY_MART_1F, 1, J_SC_MahoganyMart1FLanceUncoversStairsScene
	.2byte 0

J_W_MahoganyMart1FPharmacistScript::
	lock
	call J_MahoganyMart1FPharmacistScript
	release
	end

J_W_MahoganyMart1FBlackBeltScript::
	lock
	call J_MahoganyMart1FBlackBeltScript
	release
	end

J_W_MahoganyMart1FGrannyScript::
	lock
	call J_MahoganyMart1FGrannyScript
	release
	end

J_SC_MahoganyMart1FLanceUncoversStairsScene::
	lockall
	call J_MahoganyMart1FLanceUncoversStairsScene
	releaseall
	end

J_MahoganyMart1F_MapScripts::
J_MahoganyMart1FNoopScene::
	return
J_MahoganyMart1FLanceUncoversStairsScene::
	call J_MahoganyMart1FLanceUncoversStaircaseScript
	return
J_MahoganyMart1FStaircaseCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_UNCOVERED_STAIRCASE_IN_MAHOGANY_MART, J_L150
	setvar VAR_RESULT, 1
J_L150:
	goto_if_ne VAR_RESULT, 0, J_MahoganyMart1FStaircaseCallback_ShowStairs
	return
J_MahoganyMart1FStaircaseCallback_ShowStairs:
	setmetatile 6, 2, 57, FALSE
	setmetatile 7, 2, 14, FALSE
	setmetatile 6, 3, 14, FALSE
	setmetatile 7, 3, 21, FALSE
	return
J_MahoganyMart1FPharmacistScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_DECIDED_TO_HELP_LANCE, J_L151
	setvar VAR_RESULT, 1
J_L151:
	goto_if_ne VAR_RESULT, 0, J_MahoganyMart1FPharmacistScript_LanceEntered
	pokemart J_Mart_MART_MAHOGANY_1
	closemessage
	return
J_MahoganyMart1FPharmacistScript_LanceEntered:
	message J_MahoganyMart1FPharmacistText_LanceEntered
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyMart1FBlackBeltScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_DECIDED_TO_HELP_LANCE, J_L152
	setvar VAR_RESULT, 1
J_L152:
	goto_if_ne VAR_RESULT, 0, J_MahoganyMart1FBlackBeltScript_LanceEntered
	message J_MahoganyMart1FBlackBeltText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyMart1FBlackBeltScript_LanceEntered:
	message J_MahoganyMart1FBlackBeltText_LanceEntered
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyMart1FLanceUncoversStaircaseScript::
	delay 15
	message J_MahoganyMart1FLanceDragoniteHyperBeamText
	waitmessage
	delay 15
	closemessage
	playse SE_M_COMET_PUNCH
	applymovement 4, J_MahoganyMart1FDragoniteTackleMovement
	waitmovement 4
	applymovement 2, J_MahoganyMart1FBlackBeltKnockedBackMovement
	waitmovement 2
	delay 15
	removeobject 4
	delay 15
	applymovement 3, J_MahoganyMart1FLanceApproachPlayerMovement
	waitmovement 3
	message J_MahoganyMart1FLanceRadioText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, J_MahoganyMart1FLanceApproachPharmacistMovement
	applymovement OBJ_EVENT_ID_PLAYER, J_MahoganyMart1FLanceApproachPharmacistMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement 3
	applymovement 1, J_MahoganyMart1FPharmacistShovedAsideMovement
	waitmovement 1
	applymovement 3, J_MahoganyMart1FLanceApproachHiddenStairsMovement
	applymovement OBJ_EVENT_ID_PLAYER, J_MahoganyMart1FLanceApproachHiddenStairsMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement 3
	message J_MahoganyMart1FLanceStairsText
	waitmessage
	waitbuttonpress
	applymovement 1, J_Movement_Exclamation
	waitmovement 0
	playse SE_FAINT
	setmetatile 6, 2, 57, FALSE
	setmetatile 7, 2, 14, FALSE
	setmetatile 6, 3, 14, FALSE
	setmetatile 7, 3, 21, FALSE
	special DrawWholeMapView
	closemessage
	setflag FLAG_J_UNCOVERED_STAIRCASE_IN_MAHOGANY_MART
	turnobject 3, DIR_WEST
	message J_MahoganyMart1FLanceSplitUpText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, J_MahoganyMart1FLanceGoDownStairsMovement
	waitmovement 3
	playse SE_EXIT
	removeobject 3
	setvar VAR_J_SCENE_MAHOGANY_MART_1F, 0
	waitse
	return
J_MahoganyMart1FGrannyScript::
	faceplayer
	pokemart J_Mart_MART_MAHOGANY_2
	closemessage
	return
J_MahoganyMart1FDragoniteTackleMovement::
	lock_facing_direction
	walk_fast_left
	walk_fast_right
	unlock_facing_direction
	step_end
J_MahoganyMart1FBlackBeltKnockedBackMovement::
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	face_down
	face_left
	face_up
	face_right
	step_end
J_MahoganyMart1FPharmacistShovedAsideMovement::
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	step_end
J_MahoganyMart1FLanceApproachPlayerMovement::
	walk_slow_left
	face_down
	step_end
J_MahoganyMart1FLanceApproachPharmacistMovement::
	walk_slow_right
	walk_slow_up
	walk_slow_up
	step_end
J_MahoganyMart1FLanceApproachHiddenStairsMovement::
	walk_slow_up
	walk_slow_right
	walk_slow_right
	step_end
J_MahoganyMart1FLanceGoDownStairsMovement::
	walk_slow_right
	step_end
J_MahoganyMart1FRageCandyBarText::
	.string "Hello, kiddo!\pHow would you like\nsome RAGECANDYBAR?\pIt's the thing to\neat in MAHOGANY!$"
J_MahoganyMart1FPharmacistText_LanceEntered::
	.string "Arrgh… You found\nthe secret stair-\lway…$"
J_MahoganyMart1FBlackBeltText::
	.string "Heheh! The experi-\nment worked like a\lcharm.\pMAGIKARP are just\nworthless, but\pGYARADOS are big\nmoneymakers.$"
J_MahoganyMart1FBlackBeltText_LanceEntered::
	.string "Urrgh…\pThat guy's dragon\nPOKéMON are tough…$"
J_MahoganyMart1FLanceDragoniteHyperBeamText::
	.string "LANCE: DRAGONITE,\nHYPER BEAM.$"
J_MahoganyMart1FLanceRadioText::
	.string "What took you,\n{PLAYER}?\pJust as I thought,\nthat strange radio\psignal is coming\nfrom here.$"
J_MahoganyMart1FLanceStairsText::
	.string "The stairs are\nright here.$"
J_MahoganyMart1FLanceSplitUpText::
	.string "LANCE: {PLAYER}, we\nshould split up to\pcheck this place.\nI'll go first.$"
J_MahoganyMart1F_MapEvents::
