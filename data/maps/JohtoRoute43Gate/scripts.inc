@ KJH: translated from pokecrystal maps/Route43Gate.asm by kjh_tools/johto

JohtoRoute43Gate_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoRoute43Gate_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoRoute43Gate_OnFrame
	.byte 0

JohtoRoute43Gate_OnTransition:
	call J_Route43GateCheckIfRocketsCallback
	end

JohtoRoute43Gate_OnFrame:
	map_script_2 VAR_J_SCENE_ROUTE_43_GATE, 0, J_SC_Route43GateRocketShakedownScene
	.2byte 0

J_W_OfficerScript_GuardWithSludgeBomb::
	lock
	call J_OfficerScript_GuardWithSludgeBomb
	release
	end

J_W_RocketScript_MakingABundle::
	lock
	call J_RocketScript_MakingABundle
	release
	end

J_SC_Route43GateRocketShakedownScene::
	lockall
	call J_Route43GateRocketShakedownScene
	releaseall
	end

J_Route43Gate_MapScripts::
J_Route43GateRocketShakedownScene::
	call J_Route43GateRocketTakeoverScript
	return
J_Route43GateNoopScene::
	return
J_Route43GateCheckIfRocketsCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_ROCKET_HIDEOUT, J_L380
	setvar VAR_RESULT, 1
J_L380:
	goto_if_ne VAR_RESULT, 0, J_Route43GateCheckIfRocketsCallback_NoRockets
	setvar VAR_J_SCENE_ROUTE_43, 0
	return
J_Route43GateCheckIfRocketsCallback_NoRockets:
	setvar VAR_J_SCENE_ROUTE_43, 1
	return
J_Route43GateRocketTakeoverScript::
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J_RocketScript_Southbound
	goto_if_eq VAR_RESULT, 1, J_RocketScript_Northbound
	setvar VAR_J_SCENE_ROUTE_43_GATE, 1
	return
J_RocketScript_Southbound::
	applymovement OBJ_EVENT_ID_PLAYER, J_PlayerStepsIn
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 3, J_Movement_Exclamation
	waitmovement 0
	applymovement 3, J_Rocket2Script_BlocksYouSouth
	waitmovement 3
	turnobject 2, DIR_NORTH
	applymovement 2, J_Movement_Exclamation
	waitmovement 0
	applymovement 2, J_Rocket1Script_BlocksYouSouth
	waitmovement 2
	message J_RocketText_TollFee
	waitmessage
	waitbuttonpress
	checkmoney -1
	goto_if_eq VAR_RESULT, TRUE, J_L381
	setvar VAR_RESULT, 2
	goto J_L382
J_L381:
	setvar VAR_RESULT, 0
J_L382:
	goto_if_eq VAR_RESULT, 0, J_RocketScript_TollSouth
	goto J_RocketScript_YoureBrokeSouth
J_RocketScript_TollSouth::
	removemoney 0
	message J_RocketText_ThankYou
	waitmessage
	goto J_RocketScript_ShakeDownSouth
J_RocketScript_YoureBrokeSouth::
	removemoney 0
	message J_RocketText_AllYouGot
	waitmessage
	goto J_RocketScript_ShakeDownSouth
J_RocketScript_ShakeDownSouth::
	waitbuttonpress
	closemessage
	applymovement 2, J_Rocket1Script_LetsYouPassSouth
	waitmovement 2
	applymovement 3, J_Rocket2Script_LetsYouPassSouth
	waitmovement 3
	setvar VAR_J_SCENE_ROUTE_43_GATE, 1
	fadedefaultbgm
	return
J_RocketScript_Northbound::
	applymovement 2, J_Movement_Exclamation
	waitmovement 0
	applymovement 2, J_Rocket1Script_BlocksYouNorth
	waitmovement 2
	turnobject 3, DIR_SOUTH
	applymovement 3, J_Movement_Exclamation
	waitmovement 0
	applymovement 3, J_Rocket2Script_BlocksYouNorth
	waitmovement 3
	message J_RocketText_TollFee
	waitmessage
	waitbuttonpress
	checkmoney -1
	goto_if_eq VAR_RESULT, TRUE, J_L383
	setvar VAR_RESULT, 2
	goto J_L384
J_L383:
	setvar VAR_RESULT, 0
J_L384:
	goto_if_eq VAR_RESULT, 0, J_RocketScript_TollNorth
	goto J_RocketScript_YoureBrokeNorth
J_RocketScript_TollNorth::
	removemoney 0
	message J_RocketText_ThankYou
	waitmessage
	goto J_RocketScript_ShakeDownNorth
J_RocketScript_YoureBrokeNorth::
	removemoney 0
	message J_RocketText_AllYouGot
	waitmessage
	goto J_RocketScript_ShakeDownNorth
J_RocketScript_ShakeDownNorth::
	waitbuttonpress
	closemessage
	applymovement 3, J_Rocket2Script_LetsYouPassNorth
	waitmovement 3
	applymovement 2, J_Rocket1Script_LetsYouPassNorth
	waitmovement 2
	setvar VAR_J_SCENE_ROUTE_43_GATE, 1
	fadedefaultbgm
	return
J_RocketScript_MakingABundle::
	faceplayer
	message J_RocketText_MakingABundle
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OfficerScript_GuardWithSludgeBomb::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM36_SLUDGE_BOMB, J_L385
	setvar VAR_RESULT, 1
J_L385:
	goto_if_ne VAR_RESULT, 0, J_OfficerScript_GuardWithSludgeBomb_GotSludgeBomb
	message J_OfficerText_FoundTM
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM36, 1
	goto_if_eq VAR_RESULT, 0, J_OfficerScript_GuardWithSludgeBomb_NoRoomForSludgeBomb
	setflag FLAG_J_GOT_TM36_SLUDGE_BOMB
	closemessage
	return
J_OfficerScript_GuardWithSludgeBomb_GotSludgeBomb:
	message J_OfficerText_AvoidGrass
	waitmessage
	waitbuttonpress
J_OfficerScript_GuardWithSludgeBomb_NoRoomForSludgeBomb:
	closemessage
	return
J_PlayerStepsIn::
	walk_down
	step_end
J_Rocket1Script_BlocksYouSouth::
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	face_up
	step_end
J_Rocket1Script_LetsYouPassSouth::
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	step_end
J_Rocket1Script_BlocksYouNorth::
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	face_down
	step_end
J_Rocket1Script_LetsYouPassNorth::
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	face_down
	step_end
J_Rocket2Script_BlocksYouSouth::
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	face_up
	step_end
J_Rocket2Script_LetsYouPassSouth::
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	face_up
	step_end
J_Rocket2Script_BlocksYouNorth::
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	face_down
	step_end
J_Rocket2Script_LetsYouPassNorth::
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	step_end
J_RocketText_TollFee::
	.string "Hold it there,\nkiddo!\pThe toll is ¥0\nto go through.$"
J_RocketText_ThankYou::
	.string "Thank you very\nmuch!$"
J_RocketText_AllYouGot::
	.string "Then pay what you\nhave, please.$"
J_RocketText_MakingABundle::
	.string "He-he-he. We're\nmaking a bundle.\pEveryone wants to\nsee what's going\pon up at LAKE OF\nRAGE.$"
J_OfficerText_FoundTM::
	.string "I got chased from\nmy post by these\lthugs in black.\pThey left this\nbehind.\pIt makes me uncom-\nfortable. Could\lyou take it away?$"
J_Text_ReceivedTM30::
	.string "{PLAYER} received\nTM30.$"
J_OfficerText_AvoidGrass::
	.string "Use this gate to\navoid walking in\lthe grass.$"
J_Route43Gate_MapEvents::
