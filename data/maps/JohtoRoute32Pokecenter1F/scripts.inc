@ KJH: translated from pokecrystal maps/Route32Pokecenter1F.asm by kjh_tools/johto

JohtoRoute32Pokecenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoRoute32Pokecenter1F_OnTransition
	.byte 0

JohtoRoute32Pokecenter1F_OnTransition:
	setrespawn HEAL_LOCATION_J_ROUTE_32
	end

J_W_Route32Pokecenter1FNurseScript::
	lock
	call J_Route32Pokecenter1FNurseScript
	release
	end

J_W_Route32Pokecenter1FFishingGuruScript::
	lock
	call J_Route32Pokecenter1FFishingGuruScript
	release
	end

J_W_Route32Pokecenter1FCooltrainerFScript::
	lock
	call J_Route32Pokecenter1FCooltrainerFScript
	release
	end

J_Route32Pokecenter1F_MapScripts::
J_Route32Pokecenter1FNurseScript::
	goto J_Std_Nurse
J_Route32Pokecenter1FFishingGuruScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_OLD_ROD, J_L453
	setvar VAR_RESULT, 1
J_L453:
	goto_if_ne VAR_RESULT, 0, J_Route32Pokecenter1FFishingGuruScript_GotOldRod
	message J_Route32Pokecenter1FFishingGuruText_Question
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_Route32Pokecenter1FFishingGuruScript_Refused
	message J_Route32Pokecenter1FFishingGuruText_Yes
	waitmessage
	waitbuttonpress
	giveitem ITEM_OLD_ROD, 1
	message J_Route32Pokecenter1FFishingGuruText_GiveOldRod
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_GOT_OLD_ROD
	return
J_Route32Pokecenter1FFishingGuruScript_Refused:
	message J_Route32Pokecenter1FFishingGuruText_No
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route32Pokecenter1FFishingGuruScript_GotOldRod:
	message J_Route32Pokecenter1FFishingGuruText_After
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route32Pokecenter1FCooltrainerFScript::
	faceplayer
	message J_Route32Pokecenter1FCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route32Pokecenter1FFishingGuruText_Question::
	.string "This is a great\nfishing spot.\pYou saw people\nfishing? How\labout you?\pWould you like one\nof my RODS?$"
J_Route32Pokecenter1FFishingGuruText_Yes::
	.string "Heh, that's good\nto hear.\pNow you're an\nangler too!$"
J_Route32Pokecenter1FFishingGuruText_GiveOldRod::
	.string "Fishing is great!\pIf there's water,\nbe it the sea or a\pstream, try out\nyour ROD.$"
J_Route32Pokecenter1FFishingGuruText_No::
	.string "Oh. That's rather\ndisappointing…$"
J_Route32Pokecenter1FFishingGuruText_After::
	.string "Yo, kid. How are\nthey biting?$"
J_Route32Pokecenter1FCooltrainerFText::
	.string "What should I make\nmy POKéMON hold?\pMaybe an item that\nincreases ATTACK\lpower…$"
J_Route32Pokecenter1F_MapEvents::
