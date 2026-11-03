@ KJH: translated from pokecrystal maps/GoldenrodDeptStore6F.asm by kjh_tools/johto

JohtoGoldenrodDeptStore6F_MapScripts::
	.byte 0

J_W_GoldenrodDeptStore6FLassScript::
	lock
	call J_GoldenrodDeptStore6FLassScript
	release
	end

J_W_GoldenrodDeptStore6FSuperNerdScript::
	lock
	call J_GoldenrodDeptStore6FSuperNerdScript
	release
	end

J_S_GoldenrodDeptStore6FDirectory::
	lockall
	call J_GoldenrodDeptStore6FDirectory
	releaseall
	end

J_S_GoldenrodDeptStore6FElevatorButton::
	lockall
	call J_GoldenrodDeptStore6FElevatorButton
	releaseall
	end

J_S_GoldenrodVendingMachine::
	lockall
	call J_GoldenrodVendingMachine
	releaseall
	end

J_GoldenrodDeptStore6F_MapScripts::
J_GoldenrodVendingMachine::
	message J_GoldenrodVendingText
	waitmessage
J_GoldenrodVendingMachine_Start:
	showmoneybox 0, 0
	setvar VAR_RESULT, 1
	goto_if_eq VAR_RESULT, 1, J_GoldenrodVendingMachine_FreshWater
	goto_if_eq VAR_RESULT, 2, J_GoldenrodVendingMachine_SodaPop
	goto_if_eq VAR_RESULT, 3, J_GoldenrodVendingMachine_Lemonade
	closemessage
	return
J_GoldenrodVendingMachine_FreshWater:
	checkmoney 0
	goto_if_eq VAR_RESULT, TRUE, J_L540
	setvar VAR_RESULT, 2
	goto J_L541
J_L540:
	setvar VAR_RESULT, 0
J_L541:
	goto_if_eq VAR_RESULT, 2, J_GoldenrodVendingMachine_NotEnoughMoney
	additem ITEM_FRESH_WATER, 1
	goto_if_eq VAR_RESULT, 0, J_GoldenrodVendingMachine_NotEnoughSpace
	removemoney 0
	bufferitemname STR_VAR_1, ITEM_POTION
	goto J_GoldenrodVendingMachine_VendItem
J_GoldenrodVendingMachine_SodaPop:
	checkmoney 0
	goto_if_eq VAR_RESULT, TRUE, J_L542
	setvar VAR_RESULT, 2
	goto J_L543
J_L542:
	setvar VAR_RESULT, 0
J_L543:
	goto_if_eq VAR_RESULT, 2, J_GoldenrodVendingMachine_NotEnoughMoney
	additem ITEM_SODA_POP, 1
	goto_if_eq VAR_RESULT, 0, J_GoldenrodVendingMachine_NotEnoughSpace
	removemoney 0
	bufferitemname STR_VAR_1, ITEM_POTION
	goto J_GoldenrodVendingMachine_VendItem
J_GoldenrodVendingMachine_Lemonade:
	checkmoney 0
	goto_if_eq VAR_RESULT, TRUE, J_L544
	setvar VAR_RESULT, 2
	goto J_L545
J_L544:
	setvar VAR_RESULT, 0
J_L545:
	goto_if_eq VAR_RESULT, 2, J_GoldenrodVendingMachine_NotEnoughMoney
	additem ITEM_LEMONADE, 1
	goto_if_eq VAR_RESULT, 0, J_GoldenrodVendingMachine_NotEnoughSpace
	removemoney 0
	bufferitemname STR_VAR_1, ITEM_POTION
	goto J_GoldenrodVendingMachine_VendItem
J_GoldenrodVendingMachine_VendItem:
	delay 10
	playse SE_DOOR
	message J_GoldenrodClangText
	waitmessage
	waitbuttonpress
	goto J_GoldenrodVendingMachine_Start
J_GoldenrodVendingMachine_NotEnoughMoney:
	message J_GoldenrodVendingNoMoneyText
	waitmessage
	waitbuttonpress
	goto J_GoldenrodVendingMachine_Start
J_GoldenrodVendingMachine_NotEnoughSpace:
	message J_GoldenrodVendingNoSpaceText
	waitmessage
	waitbuttonpress
	goto J_GoldenrodVendingMachine_Start
J_GoldenrodVendingMachine_MenuHeader:
J_GoldenrodVendingMachine_MenuData:
	.string "FRESH WATER  ¥0$"
	.string "SODA POP     ¥0$"
	.string "LEMONADE     ¥0$"
	.string "CANCEL$"
J_GoldenrodDeptStore6FLassScript::
	faceplayer
	message J_GoldenrodDeptStore6FLassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore6FSuperNerdScript::
	faceplayer
	message J_GoldenrodDeptStore6FSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore6FDirectory::
	message J_GoldenrodDeptStore6FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore6FElevatorButton::
	goto J_Std_Nop
J_GoldenrodVendingText::
	.string "A vending machine!\nHere's the menu.$"
J_GoldenrodClangText::
	.string "Clang! A can of\n{STR_VAR_1}\lpopped out!$"
J_GoldenrodVendingNoMoneyText::
	.string "Oops, not enough\nmoney.$"
J_GoldenrodVendingNoSpaceText::
	.string "There's no more\nroom for stuff.$"
J_GoldenrodDeptStore6FLassText::
	.string "Do you listen to\nLUCKY CHANNEL?\pIf you want to\nwin, trade POKéMON\pwith as many peo-\nple as possible to\pget different ID\nnumbers.$"
J_GoldenrodDeptStore6FSuperNerdText::
	.string "If you're tired,\ntry the vending\lmachine's drinks.\pYour POKéMON will\nlove them too.$"
J_GoldenrodDeptStore6FDirectoryText::
	.string "Take a Break from\nShopping!\p6F TRANQUIL SQUARE$"
J_GoldenrodDeptStore6F_MapEvents::
