@ KJH: translated from pokecrystal maps/DayCare.asm by kjh_tools/johto

JohtoDayCare_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoDayCare_OnTransition
	.byte 0

JohtoDayCare_OnTransition:
	call J_DayCareEggCheckCallback
	end

J_W_DayCareManScript_Inside::
	lock
	call J_DayCareManScript_Inside
	release
	end

J_W_DayCareLadyScript::
	lock
	call J_DayCareLadyScript
	release
	end

J_S_DayCareBookshelf::
	lockall
	call J_DayCareBookshelf
	releaseall
	end

J_DayCare_MapScripts::
J_DayCareEggCheckCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_DAY_CARE_MAN_HAS_EGG, J_L566
	setvar VAR_RESULT, 1
J_L566:
	goto_if_ne VAR_RESULT, 0, J_DayCareEggCheckCallback_PutDayCareManOutside
	clearflag FLAG_J_DAY_CARE_MAN_IN_DAY_CARE
	setflag FLAG_J_DAY_CARE_MAN_ON_ROUTE_34
	return
J_DayCareEggCheckCallback_PutDayCareManOutside:
	setflag FLAG_J_DAY_CARE_MAN_IN_DAY_CARE
	clearflag FLAG_J_DAY_CARE_MAN_ON_ROUTE_34
	return
J_DayCareManScript_Inside::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_ODD_EGG, J_L567
	setvar VAR_RESULT, 1
J_L567:
	goto_if_ne VAR_RESULT, 0, J_DayCareManScript_Inside_AlreadyHaveOddEgg
	message J_DayCareManText_GiveOddEgg
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_0x8004, 1
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 6, J_DayCareManScript_Inside_PartyFull
	giveegg SPECIES_PICHU
	message J_DayCareText_GotOddEgg
	waitmessage
	playse SE_SUCCESS
	waitse
	message J_DayCareText_DescribeOddEgg
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_GOT_ODD_EGG
	return
J_DayCareManScript_Inside_PartyFull:
	message J_DayCareText_PartyFull
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DayCareManScript_Inside_AlreadyHaveOddEgg:
	setvar VAR_RESULT, 0
	waitbuttonpress
	closemessage
	return
J_DayCareLadyScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_DAY_CARE_MAN_HAS_EGG, J_L568
	setvar VAR_RESULT, 1
J_L568:
	goto_if_ne VAR_RESULT, 0, J_DayCareLadyScript_HusbandWasLookingForYou
	setvar VAR_RESULT, 0
	waitbuttonpress
	closemessage
	return
J_DayCareLadyScript_HusbandWasLookingForYou:
	message J_Text_GrampsLookingForYou
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DayCareBookshelf::
	goto J_DifficultBookshelfScript
J_Text_GrampsLookingForYou::
	.string "Gramps was looking\nfor you.$"
J_Text_DayCareManTalksAboutEggTicket::
	.string "I'm the DAY-CARE\nMAN.\pThere's something\nnew in GOLDENROD\pcalled the TRADE\nCORNER.\pI was given an EGG\nTICKET that can be\ptraded in for a\nODD EGG.\pBut since we run a\nDAY-CARE, we don't\pneed it. You may\nas well have it.$"
J_DayCareManText_GiveOddEgg::
	.string "I'm the DAY-CARE\nMAN.\pDo you know about\nEGGS?\pI was raising\nPOKéMON with my\lwife, you see.\pWe were shocked to\nfind an EGG!\pHow incredible is\nthat?\pWell, wouldn't you\nlike this EGG?\pThen fine, this is\nyours to keep!$"
J_DayCareText_ComeAgain::
	.string "Come again.$"
J_DayCareText_GotOddEgg::
	.string "{PLAYER} received\nODD EGG!$"
J_DayCareText_DescribeOddEgg::
	.string "I found that when\nI was caring for\psomeone's POKéMON\nbefore.\pBut the trainer\ndidn't want the\pEGG, so I'd kept\nit around.$"
J_DayCareText_PartyFull::
	.string "You've no room for\nthis.$"
J_DayCare_MapEvents::
