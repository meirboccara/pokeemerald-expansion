@ KJH: translated from pokecrystal maps/GoldenrodDeptStoreElevator.asm by kjh_tools/johto

JohtoGoldenrodDeptStoreElevator_MapScripts::
	.byte 0

J_S_GoldenrodDeptStoreElevatorScript::
	lockall
	call J_GoldenrodDeptStoreElevatorScript
	releaseall
	end

J_GoldenrodDeptStoreElevator_MapScripts::
J_GoldenrodDeptStoreElevatorScript::
	closemessage
	goto_if_eq VAR_RESULT, 0, J_GoldenrodDeptStoreElevatorScript_Done
	delay 5
	playse SE_ELEVATOR
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 4
	special ShakeScreen
	delay 40
	waitse
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOLDENROD_UNDERGROUND_WAREHOUSE_BLOCKED_OFF, J_L546
	setvar VAR_RESULT, 1
J_L546:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodDeptStoreElevatorScript_Done
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_1, J_L547
	setvar VAR_RESULT, 1
J_L547:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodDeptStoreElevatorScript_BoxLayout1
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_2, J_L548
	setvar VAR_RESULT, 1
J_L548:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodDeptStoreElevatorScript_BoxLayout2
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_3, J_L549
	setvar VAR_RESULT, 1
J_L549:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodDeptStoreElevatorScript_BoxLayout3
J_GoldenrodDeptStoreElevatorScript_BoxLayout3:
	setflag FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_1
	clearflag FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_2
	clearflag FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_3
	return
J_GoldenrodDeptStoreElevatorScript_BoxLayout1:
	clearflag FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_1
	setflag FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_2
	clearflag FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_3
	return
J_GoldenrodDeptStoreElevatorScript_BoxLayout2:
	clearflag FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_1
	clearflag FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_2
	setflag FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_3
	return
J_GoldenrodDeptStoreElevatorScript_Done:
	return
J_GoldenrodDeptStoreElevatorData::
J_GoldenrodDeptStoreElevator_MapEvents::
