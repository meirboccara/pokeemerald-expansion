@ KJH: translated from pokecrystal maps/Route39Barn.asm by kjh_tools/johto

JohtoRoute39Barn_MapScripts::
	.byte 0

J_W_Route39BarnTwin1Script::
	lock
	call J_Route39BarnTwin1Script
	release
	end

J_W_Route39BarnTwin2Script::
	lock
	call J_Route39BarnTwin2Script
	release
	end

J_W_MoomooScript::
	lock
	call J_MoomooScript
	release
	end

J_Route39Barn_MapScripts::
J_Route39BarnTwin1Script::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HEALED_MOOMOO, J_L8
	setvar VAR_RESULT, 1
J_L8:
	goto_if_ne VAR_RESULT, 0, J_Route39BarnTwin1Script_FeedingMooMoo
	message J_Route39BarnTwinMoomooIsSickText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 1, DIR_EAST
	return
J_Route39BarnTwin1Script_FeedingMooMoo:
	message J_Route39BarnTwinWereFeedingMoomooText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 1, DIR_EAST
	return
J_Route39BarnTwin2Script::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HEALED_MOOMOO, J_L9
	setvar VAR_RESULT, 1
J_L9:
	goto_if_ne VAR_RESULT, 0, J_Route39BarnTwin2Script_FeedingMooMoo
	message J_Route39BarnTwinMoomooIsSickText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 2, DIR_WEST
	return
J_Route39BarnTwin2Script_FeedingMooMoo:
	message J_Route39BarnTwinWereFeedingMoomooText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 2, DIR_WEST
	return
J_MoomooScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HEALED_MOOMOO, J_L10
	setvar VAR_RESULT, 1
J_L10:
	goto_if_ne VAR_RESULT, 0, J_MoomooScript_HappyCow
	message J_MoomooWeakMooText
	waitmessage
	setvar VAR_RESULT, 241
	waitbuttonpress
	message J_Route39BarnItsCryIsWeakText
	waitmessage
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TALKED_TO_FARMER_ABOUT_MOOMOO, J_L11
	setvar VAR_RESULT, 1
J_L11:
	goto_if_ne VAR_RESULT, 0, J_MoomooScript_GiveBerry
	waitbuttonpress
	closemessage
	return
J_MoomooScript_GiveBerry:
	waitbuttonpress
	message J_Route39BarnAskGiveBerryText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_MoomooScript_Refused
	checkitem ITEM_ORAN_BERRY, 1
	goto_if_eq VAR_RESULT, 0, J_MoomooScript_NoBerriesInBag
	removeitem ITEM_ORAN_BERRY, 1
	copyvar VAR_RESULT, VAR_J_MEM_MOOMOOBERRIES
	addvar VAR_RESULT, 1
	copyvar VAR_J_MEM_MOOMOOBERRIES, VAR_RESULT
	goto_if_eq VAR_RESULT, 3, J_MoomooScript_ThreeBerries
	goto_if_eq VAR_RESULT, 5, J_MoomooScript_FiveBerries
	goto_if_eq VAR_RESULT, 7, J_MoomooScript_SevenBerries
	message J_Route39BarnGaveBerryText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MoomooScript_ThreeBerries:
	message J_Route39BarnGaveBerryText
	waitmessage
	waitbuttonpress
	message J_Route39BarnLittleHealthierText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MoomooScript_FiveBerries:
	message J_Route39BarnGaveBerryText
	waitmessage
	waitbuttonpress
	message J_Route39BarnQuiteHealthyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MoomooScript_SevenBerries:
	playbgm MUS_RG_HEAL, FALSE
	message J_Route39BarnGaveBerryText
	waitmessage
	delay 60
	waitbuttonpress
	fadedefaultbgm
	message J_Route39BarnTotallyHealthyText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_HEALED_MOOMOO
	return
J_MoomooScript_NoBerriesInBag:
	message J_Route39BarnNoBerriesText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MoomooScript_Refused:
	message J_Route39BarnRefusedBerryText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MoomooScript_HappyCow:
	message J_MoomooHappyMooText
	waitmessage
	playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_Route39BarnTwinMoomooIsSickText::
	.string "MOOMOO is sick…\pShe needs lots of\nBERRIES.$"
J_Route39BarnTwinWereFeedingMoomooText::
	.string "We're feeding\nMOOMOO!$"
J_MoomooWeakMooText::
	.string "MILTANK: …Moo…$"
J_Route39BarnItsCryIsWeakText::
	.string "Its cry is weak…$"
J_MoomooHappyMooText::
	.string "MILTANK: Mooo!$"
J_Route39BarnAskGiveBerryText::
	.string "Give a BERRY to\nMILTANK?$"
J_Route39BarnGaveBerryText::
	.string "{PLAYER} gave a\nBERRY to MILTANK.$"
J_Route39BarnLittleHealthierText::
	.string "MILTANK became a\nlittle healthier!$"
J_Route39BarnQuiteHealthyText::
	.string "MILTANK became\nquite healthy!$"
J_Route39BarnTotallyHealthyText::
	.string "MILTANK became\ntotally healthy!$"
J_Route39BarnNoBerriesText::
	.string "{PLAYER} has no\nBERRIES…$"
J_Route39BarnRefusedBerryText::
	.string "{PLAYER} wouldn't\ngive a BERRY.\pMILTANK looks sad.$"
J_Route39Barn_MapEvents::
