@ KJH: translated from pokecrystal maps/GoldenrodUndergroundWarehouse.asm by kjh_tools/johto

JohtoGoldenrodUndergroundWarehouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoGoldenrodUndergroundWarehouse_OnTransition
	.byte 0

JohtoGoldenrodUndergroundWarehouse_OnTransition:
	call J_GoldenrodUndergroundWarehouseResetSwitchesCallback
	end

J_T_TrainerGruntM24::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_24, J_GruntM24SeenText, J_GruntM24BeatenText
	call J_TrainerGruntM24_Script
	release
	end

J_T_TrainerGruntM14::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_14, J_GruntM14SeenText, J_GruntM14BeatenText
	call J_TrainerGruntM14_Script
	release
	end

J_T_TrainerGruntM15::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_15, J_GruntM15SeenText, J_GruntM15BeatenText
	call J_TrainerGruntM15_Script
	release
	end

J_W_GoldenrodUndergroundWarehouseDirectorScript::
	lock
	call J_GoldenrodUndergroundWarehouseDirectorScript
	release
	end

J_GoldenrodUndergroundWarehouse_MapScripts::
J_GoldenrodUndergroundWarehouseResetSwitchesCallback::
	clearflag FLAG_J_SWITCH_1
	clearflag FLAG_J_SWITCH_2
	clearflag FLAG_J_SWITCH_3
	clearflag FLAG_J_EMERGENCY_SWITCH
	clearflag FLAG_J_DOOR_1_OPEN
	clearflag FLAG_J_DOOR_2_OPEN
	clearflag FLAG_J_DOOR_3_OPEN
	clearflag FLAG_J_DOOR_4_OPEN
	clearflag FLAG_J_DOOR_5_OPEN
	clearflag FLAG_J_DOOR_6_OPEN
	clearflag FLAG_J_DOOR_7_OPEN
	clearflag FLAG_J_DOOR_8_OPEN
	clearflag FLAG_J_DOOR_9_OPEN
	clearflag FLAG_J_DOOR_10_OPEN
	clearflag FLAG_J_DOOR_11_OPEN
	setvar VAR_RESULT, 0
	copyvar VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS, VAR_RESULT
	return
J_TrainerGruntM24::
J_TrainerGruntM24_Script:
	message J_GruntM24AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM14::
J_TrainerGruntM14_Script:
	message J_GruntM14AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM15::
J_TrainerGruntM15_Script:
	message J_GruntM15AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodUndergroundWarehouseDirectorScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RECEIVED_CARD_KEY, J_L238
	setvar VAR_RESULT, 1
J_L238:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodUndergroundWarehouseDirectorScript_GotCardKey
	message J_DirectorIntroText
	waitmessage
	waitbuttonpress
	bufferstring STR_VAR_2, J_ItemName_CARD_KEY
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message J_Text_ReceivedKeyItem
	waitmessage
	waitfanfare
	setflag FLAG_J_HAS_CARD_KEY
	setvar VAR_RESULT, 1
	setflag FLAG_J_RECEIVED_CARD_KEY
	setflag FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_1
	clearflag FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_2
	clearflag FLAG_J_GOLDENROD_DEPT_STORE_B1F_LAYOUT_3
	message J_DirectorCardKeyText
	waitmessage
	waitbuttonpress
J_GoldenrodUndergroundWarehouseDirectorScript_GotCardKey:
	message J_DirectorAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodUndergroundWarehouseMaxEther::
	finditem ITEM_MAX_ETHER, 1
	return
J_GoldenrodUndergroundWarehouseTMSleepTalk::
	finditem ITEM_RARE_CANDY, 1
	return
J_GoldenrodUndergroundWarehouseUltraBall::
	finditem ITEM_ULTRA_BALL, 1
	return
J_GruntM24SeenText::
	.string "How did you get\nthis far?\pI guess it can't\nbe helped. I'll\ldispose of you.$"
J_GruntM24BeatenText::
	.string "I got disposed of…$"
J_GruntM24AfterBattleText::
	.string "TEAM ROCKET will\nkeep going, wait-\ling for the return\lof GIOVANNI.\pWe'll do whatever\nit takes.$"
J_GruntM14SeenText::
	.string "You're not going\nany farther!\pI don't show mercy\nto my enemies, not\leven brats!$"
J_GruntM14BeatenText::
	.string "Blast it!$"
J_GruntM14AfterBattleText::
	.string "I lost…\pPlease forgive me,\nGIOVANNI!$"
J_GruntM15SeenText::
	.string "Hyuck-hyuck-hyuck!\nI remember you!\pYou got me good\nat our hideout!$"
J_GruntM15BeatenText::
	.string "Hyuck-hyuck-hyuck!\nSo, that's how?$"
J_GruntM15AfterBattleText::
	.string "Hyuck-hyuck-hyuck!\nThat was a blast!\lI'll remember you!$"
J_DirectorIntroText::
	.string "DIRECTOR: Who?\nWhat? You came to\lrescue me?\pThank you!\pThe RADIO TOWER!\pWhat's happening\nthere?\pTaken over by TEAM\nROCKET?\pHere. Take this\nCARD KEY.$"
J_DirectorCardKeyText::
	.string "DIRECTOR: Use that\nto open the shut-\lters on 3F.$"
J_DirectorAfterText::
	.string "I'm begging you to\nhelp.\pThere's no telling\nwhat they'll do if\pthey control the\ntransmitter.\pThey may even be\nable to control\pPOKéMON using a\nspecial signal!\pYou're the only\none I can call on.\pPlease save the\nRADIO TOWER…\pAnd all the POKé-\nMON nationwide!$"
J_GoldenrodUndergroundWarehouse_MapEvents::
