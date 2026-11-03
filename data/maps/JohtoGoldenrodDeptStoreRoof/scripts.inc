@ KJH: translated from pokecrystal maps/GoldenrodDeptStoreRoof.asm by kjh_tools/johto

JohtoGoldenrodDeptStoreRoof_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoGoldenrodDeptStoreRoof_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, JohtoGoldenrodDeptStoreRoof_OnLoad
	.byte 0

JohtoGoldenrodDeptStoreRoof_OnTransition:
	call J_GoldenrodDeptStoreRoofCheckSaleChangeClerkCallback
	end

JohtoGoldenrodDeptStoreRoof_OnLoad:
	call J_GoldenrodDeptStoreRoofCheckSaleChangeBlockCallback
	end

J_W_GoldenrodDeptStoreRoofClerkScript::
	lock
	call J_GoldenrodDeptStoreRoofClerkScript
	release
	end

J_W_GoldenrodDeptStoreRoofPokefanFScript::
	lock
	call J_GoldenrodDeptStoreRoofPokefanFScript
	release
	end

J_W_GoldenrodDeptStoreRoofFisherScript::
	lock
	call J_GoldenrodDeptStoreRoofFisherScript
	release
	end

J_W_GoldenrodDeptStoreRoofTwinScript::
	lock
	call J_GoldenrodDeptStoreRoofTwinScript
	release
	end

J_W_GoldenrodDeptStoreRoofSuperNerdScript::
	lock
	call J_GoldenrodDeptStoreRoofSuperNerdScript
	release
	end

J_W_GoldenrodDeptStoreRoofPokefanMScript::
	lock
	call J_GoldenrodDeptStoreRoofPokefanMScript
	release
	end

J_W_GoldenrodDeptStoreRoofTeacherScript::
	lock
	call J_GoldenrodDeptStoreRoofTeacherScript
	release
	end

J_W_GoldenrodDeptStoreRoofBugCatcherScript::
	lock
	call J_GoldenrodDeptStoreRoofBugCatcherScript
	release
	end

J_S_Binoculars1::
	lockall
	call J_Binoculars1
	releaseall
	end

J_S_Binoculars2::
	lockall
	call J_Binoculars2
	releaseall
	end

J_S_Binoculars3::
	lockall
	call J_Binoculars3
	releaseall
	end

J_S_PokeDollVendingMachine::
	lockall
	call J_PokeDollVendingMachine
	releaseall
	end

J_GoldenrodDeptStoreRoof_MapScripts::
J_GoldenrodDeptStoreRoofCheckSaleChangeBlockCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_GOLDENROD_DEPT_STORE_SALE_IS_ON, J_L550
	setvar VAR_RESULT, 1
J_L550:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodDeptStoreRoofCheckSaleChangeBlockCallback_SaleIsOn
	return
J_GoldenrodDeptStoreRoofCheckSaleChangeBlockCallback_SaleIsOn:
	setmetatile 0, 2, 76, TRUE
	setmetatile 1, 2, 77, TRUE
	setmetatile 0, 3, 78, TRUE
	setmetatile 1, 3, 79, TRUE
	setmetatile 0, 4, 80, FALSE
	setmetatile 1, 4, 81, TRUE
	setmetatile 0, 5, 82, TRUE
	setmetatile 1, 5, 83, TRUE
	return
J_GoldenrodDeptStoreRoofCheckSaleChangeClerkCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_GOLDENROD_DEPT_STORE_SALE_IS_ON, J_L551
	setvar VAR_RESULT, 1
J_L551:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodDeptStoreRoofCheckSaleChangeClerkCallback_ChangeClerk
	setflag FLAG_J_GOLDENROD_SALE_OFF
	clearflag FLAG_J_GOLDENROD_SALE_ON
	return
J_GoldenrodDeptStoreRoofCheckSaleChangeClerkCallback_ChangeClerk:
	clearflag FLAG_J_GOLDENROD_SALE_OFF
	setflag FLAG_J_GOLDENROD_SALE_ON
	return
J_GoldenrodDeptStoreRoofClerkScript::
	pokemart J_Mart_0
	closemessage
	return
J_GoldenrodDeptStoreRoofPokefanFScript::
	faceplayer
	message J_GoldenrodDeptStoreRoofPokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStoreRoofFisherScript::
	faceplayer
	message J_GoldenrodDeptStoreRoofFisherText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 3, DIR_NORTH
	return
J_GoldenrodDeptStoreRoofTwinScript::
	faceplayer
	message J_GoldenrodDeptStoreRoofTwinText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStoreRoofSuperNerdScript::
	message J_GoldenrodDeptStoreRoofSuperNerdOhWowText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 5, DIR_NORTH
	message J_GoldenrodDeptStoreRoofSuperNerdQuitBotheringMeText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 5, DIR_EAST
	return
J_GoldenrodDeptStoreRoofPokefanMScript::
	faceplayer
	message J_GoldenrodDeptStoreRoofPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStoreRoofTeacherScript::
	faceplayer
	message J_GoldenrodDeptStoreRoofTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStoreRoofBugCatcherScript::
	faceplayer
	message J_GoldenrodDeptStoreRoofBugCatcherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Binoculars1::
	message J_Binoculars1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Binoculars2::
	message J_Binoculars2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Binoculars3::
	message J_Binoculars3Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_PokeDollVendingMachine::
	message J_PokeDollVendingMachineText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStoreRoofPokefanFText::
	.string "Whew, I'm tired.\pI sometimes come\nup to the rooftop\pto take a break\nfrom shopping.$"
J_GoldenrodDeptStoreRoofFisherText::
	.string "Pardon? Who says\nan adult can't get\linto this?\pI'm going to be\nback every day to\pcollect all the\ndolls!$"
J_GoldenrodDeptStoreRoofTwinText::
	.string "They have bargain\nsales here every\lso often.$"
J_GoldenrodDeptStoreRoofSuperNerdOhWowText::
	.string "Oh, wow!$"
J_GoldenrodDeptStoreRoofSuperNerdQuitBotheringMeText::
	.string "Will you quit\nbothering me?$"
J_GoldenrodDeptStoreRoofPokefanMText::
	.string "There's something\nI really want, but\pI don't have the\nnecessary cash…\pMaybe I'll sell\noff the BERRIES\lI've collected…$"
J_GoldenrodDeptStoreRoofTeacherText::
	.string "Oh, everything is\nso cheap!\pI bought so much,\nmy PACK's crammed!$"
J_GoldenrodDeptStoreRoofBugCatcherText::
	.string "My POKéMON always\nget paralyzed or\ppoisoned when the\nchips are down…\pSo I came to buy\nsome FULL HEAL.\pI wonder if\nthere's any left?$"
J_Binoculars1Text::
	.string "These binoculars\nlet me see far\paway. Maybe I can\nsee my own house.\pIs it the one with\nthe green roof?$"
J_Binoculars2Text::
	.string "Hey! Some trainers\nare battling on\lthe road!\pA POKéMON fired a\nflurry of leaves!\pThat makes me feel\nlike battling\lright now!$"
J_Binoculars3Text::
	.string "A FISHER caught a\nlot of MAGIKARP…\pThey're SPLASHing\nat the same time!\pLook at the water\ngoing everywhere!$"
J_PokeDollVendingMachineText::
	.string "A vending machine\nfor POKéMON dolls?\pInsert money, then\nturn the crank…\pBut it's almost\nempty…$"
J_GoldenrodDeptStoreRoof_MapEvents::
