@ KJH: translated from pokecrystal maps/Route34IlexForestGate.asm by kjh_tools/johto

JohtoRoute34IlexForestGate_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoRoute34IlexForestGate_OnTransition
	.byte 0

JohtoRoute34IlexForestGate_OnTransition:
	call J_Route34IsForestRestlessCallback
	end

J_W_Route34IlexForestGateTeacherScript::
	lock
	call J_Route34IlexForestGateTeacherScript
	release
	end

J_W_Route34IlexForestGateButterfreeScript::
	lock
	call J_Route34IlexForestGateButterfreeScript
	release
	end

J_W_Route34IlexForestGateLassScript::
	lock
	call J_Route34IlexForestGateLassScript
	release
	end

J_C_Route34IlexForestGateCelebiEvent::
	lockall
	call J_Route34IlexForestGateCelebiEvent
	releaseall
	end

J_Route34IlexForestGate_MapScripts::
J_Route34IsForestRestlessCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOREST_IS_RESTLESS, J_L562
	setvar VAR_RESULT, 1
J_L562:
	goto_if_eq VAR_RESULT, 0, J_Route34IsForestRestlessCallback_Normal
	setflag FLAG_J_ROUTE_34_ILEX_FOREST_GATE_TEACHER_BEHIND_COUNTER
	clearflag FLAG_J_ROUTE_34_ILEX_FOREST_GATE_TEACHER_IN_WALKWAY
	return
J_Route34IsForestRestlessCallback_Normal:
	setflag FLAG_J_ROUTE_34_ILEX_FOREST_GATE_TEACHER_IN_WALKWAY
	clearflag FLAG_J_ROUTE_34_ILEX_FOREST_GATE_TEACHER_BEHIND_COUNTER
	return
J_Route34IlexForestGateCelebiEvent::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOREST_IS_RESTLESS, J_L563
	setvar VAR_RESULT, 1
J_L563:
	goto_if_eq VAR_RESULT, 0, J_Route34IlexForestGateCelebiEvent_skip
	applymovement 4, J_Movement_Exclamation
	waitmovement 0
	turnobject 4, DIR_WEST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement OBJ_EVENT_ID_PLAYER, J_Route34IlexForestGateTeacherBlocksPlayerMovement
	applymovement 4, J_Route34IlexForestGateTeacherBlocksPlayerMovement
	waitmovement 4
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	message J_Route34IlexForestGateTeacher_ForestIsRestless
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, J_Route34IlexForestGateTeacherReturnsMovement
	waitmovement 4
J_Route34IlexForestGateCelebiEvent_skip:
	return
J_Route34IlexForestGateTeacherScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOREST_IS_RESTLESS, J_L564
	setvar VAR_RESULT, 1
J_L564:
	goto_if_ne VAR_RESULT, 0, J_Route34IlexForestGateTeacherScript_ForestIsRestless
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM12_SWEET_SCENT, J_L565
	setvar VAR_RESULT, 1
J_L565:
	goto_if_ne VAR_RESULT, 0, J_Route34IlexForestGateTeacherScript_GotSweetScent
	message J_Route34IlexForestGateTeacherText
	waitmessage
	waitbuttonpress
	giveitem ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, 0, J_Route34IlexForestGateTeacherScript_NoRoom
	setflag FLAG_J_GOT_TM12_SWEET_SCENT
J_Route34IlexForestGateTeacherScript_GotSweetScent:
	message J_Route34IlexForestGateTeacher_GotSweetScent
	waitmessage
	waitbuttonpress
J_Route34IlexForestGateTeacherScript_NoRoom:
	closemessage
	return
J_Route34IlexForestGateTeacherScript_ForestIsRestless:
	message J_Route34IlexForestGateTeacher_ForestIsRestless
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route34IlexForestGateButterfreeScript::
	message J_Route34IlexForestGateButterfreeText
	waitmessage
	playmoncry SPECIES_BUTTERFREE, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_Route34IlexForestGateLassScript::
	faceplayer
	message J_Route34IlexForestGateLassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route34IlexForestGateTeacherBlocksPlayerMovement::
	walk_up
	walk_up
	step_end
J_Route34IlexForestGateTeacherReturnsMovement::
	walk_down
	walk_right
	step_end
J_Route34IlexForestGateTeacherText::
	.string "Oh, honey. You're\nmaking a POKéDEX?\pIt must be hard if\nPOKéMON won't\pappear. Try using\nthis TM.$"
J_Route34IlexForestGateTeacher_GotSweetScent::
	.string "It's SWEET SCENT.\pUse it wherever\nPOKéMON appear.\pPOKéMON will be\nenticed by it.$"
J_Route34IlexForestGateTeacher_ForestIsRestless::
	.string "Something's wrong\nin ILEX FOREST…\pYou should stay\naway right now.$"
J_Route34IlexForestGateButterfreeText::
	.string "BUTTERFREE: Freeh!$"
J_Route34IlexForestGateLassText::
	.string "Did you see the\nshrine honoring\lthe protector?\pIt watches over\nthe FOREST from\lacross time.\pI think that it\nmust be a grass-\ltype POKéMON.$"
J_Route34IlexForestGate_MapEvents::
