@ KJH: translated from pokecrystal maps/GoldenrodDeptStoreB1F.asm by kjh_tools/johto

JohtoGoldenrodDeptStoreB1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoGoldenrodDeptStoreB1F_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, JohtoGoldenrodDeptStoreB1F_OnLoad
	.byte 0

JohtoGoldenrodDeptStoreB1F_OnTransition:
	call J_GoldenRodDeptStoreUnblockCallback
	end

JohtoGoldenrodDeptStoreB1F_OnLoad:
	call J_GoldenRodDeptStoreB1FClearBoxesCallback
	end

J_W_GoldenrodDeptStoreB1FBlackBelt1Script::
	lock
	call J_GoldenrodDeptStoreB1FBlackBelt1Script
	release
	end

J_W_GoldenrodDeptStoreB1FBlackBelt2Script::
	lock
	call J_GoldenrodDeptStoreB1FBlackBelt2Script
	release
	end

J_W_GoldenrodDeptStoreB1FBlackBelt3Script::
	lock
	call J_GoldenrodDeptStoreB1FBlackBelt3Script
	release
	end

J_W_GoldenrodDeptStoreB1FMachopScript::
	lock
	call J_GoldenrodDeptStoreB1FMachopScript
	release
	end

J_GoldenrodDeptStoreB1F_MapScripts::
J_GoldenRodDeptStoreB1FClearBoxesCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RECEIVED_CARD_KEY, J_L235
	setvar VAR_RESULT, 1
J_L235:
	goto_if_ne VAR_RESULT, 0, J_GoldenRodDeptStoreB1FClearBoxesCallback_GotCardKey
	goto J_GoldenRodDeptStoreB1FClearBoxesCallback_Continue
J_GoldenRodDeptStoreB1FClearBoxesCallback_GotCardKey:
	setmetatile 16, 4, 6, FALSE
	setmetatile 17, 4, 6, FALSE
	setmetatile 16, 5, 6, FALSE
	setmetatile 17, 5, 6, FALSE
	goto J_GoldenRodDeptStoreB1FClearBoxesCallback_Continue
J_GoldenRodDeptStoreB1FClearBoxesCallback_Continue:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_2, J_L236
	setvar VAR_RESULT, 1
J_L236:
	goto_if_ne VAR_RESULT, 0, J_GoldenRodDeptStoreB1FClearBoxesCallback_Layout2
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_3, J_L237
	setvar VAR_RESULT, 1
J_L237:
	goto_if_ne VAR_RESULT, 0, J_GoldenRodDeptStoreB1FClearBoxesCallback_Layout3
	setmetatile 10, 8, 6, FALSE
	setmetatile 11, 8, 6, FALSE
	setmetatile 10, 9, 6, FALSE
	setmetatile 11, 9, 6, FALSE
	return
J_GoldenRodDeptStoreB1FClearBoxesCallback_Layout2:
	setmetatile 4, 10, 6, FALSE
	setmetatile 5, 10, 6, FALSE
	setmetatile 4, 11, 6, FALSE
	setmetatile 5, 11, 6, FALSE
	return
J_GoldenRodDeptStoreB1FClearBoxesCallback_Layout3:
	setmetatile 10, 12, 6, FALSE
	setmetatile 11, 12, 6, FALSE
	setmetatile 10, 13, 6, FALSE
	setmetatile 11, 13, 6, FALSE
	return
J_GoldenRodDeptStoreUnblockCallback::
	clearflag FLAG_J_GOLDENROD_UNDERGROUND_WAREHOUSE_BLOCKED_OFF
	return
J_GoldenrodDeptStoreB1FBlackBelt1Script::
	faceplayer
	message J_GoldenrodDeptStoreB1FBlackBelt1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStoreB1FBlackBelt2Script::
	faceplayer
	message J_GoldenrodDeptStoreB1FBlackBelt2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStoreB1FBlackBelt3Script::
	faceplayer
	message J_GoldenrodDeptStoreB1FBlackBelt3Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStoreB1FMachopScript::
	message J_GoldenrodDeptStoreB1FMachokeText
	waitmessage
	playmoncry SPECIES_MACHOKE, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStoreB1FEther::
	finditem ITEM_ETHER, 1
	return
J_GoldenrodDeptStoreB1FAmuletCoin::
	finditem ITEM_AMULET_COIN, 1
	return
J_GoldenrodDeptStoreB1FBurnHeal::
	finditem ITEM_BURN_HEAL, 1
	return
J_GoldenrodDeptStoreB1FUltraBall::
	finditem ITEM_ULTRA_BALL, 1
	return
J_GoldenrodDeptStoreB1FBlackBelt1Text::
	.string "Hey, kid! You're\nholding us up!\pOur policy is to\nwork behind the\pscenes where no\none can see us!$"
J_GoldenrodDeptStoreB1FBlackBelt2Text::
	.string "I lose my passion\nfor work if some-\lone's watching.\pCome on, kid,\nscoot!$"
J_GoldenrodDeptStoreB1FBlackBelt3Text::
	.string "Oohah! Oohah!\pThe stuff on the\nground's junk.\pTake it if you\nwant it!$"
J_GoldenrodDeptStoreB1FMachokeText::
	.string "MACHOKE: Maaacho!$"
J_GoldenrodDeptStoreB1F_MapEvents::
