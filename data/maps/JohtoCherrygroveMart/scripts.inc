@ KJH: translated from pokecrystal maps/CherrygroveMart.asm by kjh_tools/johto

JohtoCherrygroveMart_MapScripts::
	.byte 0

J_W_CherrygroveMartClerkScript::
	lock
	call J_CherrygroveMartClerkScript
	release
	end

J_W_CherrygroveMartCooltrainerMScript::
	lock
	call J_CherrygroveMartCooltrainerMScript
	release
	end

J_W_CherrygroveMartYoungsterScript::
	lock
	call J_CherrygroveMartYoungsterScript
	release
	end

J_CherrygroveMart_MapScripts::
J_CherrygroveMartClerkScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_MYSTERY_EGG_TO_ELM, J_L686
	setvar VAR_RESULT, 1
J_L686:
	goto_if_ne VAR_RESULT, 0, J_CherrygroveMartClerkScript_PokeBallsInStock
	pokemart J_Mart_MART_CHERRYGROVE
	closemessage
	return
J_CherrygroveMartClerkScript_PokeBallsInStock:
	pokemart J_Mart_MART_CHERRYGROVE_DEX
	closemessage
	return
J_CherrygroveMartCooltrainerMScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_MYSTERY_EGG_TO_ELM, J_L687
	setvar VAR_RESULT, 1
J_L687:
	goto_if_ne VAR_RESULT, 0, J_CherrygroveMartCooltrainerMScript_PokeBallsInStock
	message J_CherrygroveMartCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CherrygroveMartCooltrainerMScript_PokeBallsInStock:
	message J_CherrygroveMartCooltrainerMText_PokeBallsInStock
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CherrygroveMartYoungsterScript::
	faceplayer
	message J_CherrygroveMartYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CherrygroveMartCooltrainerMText::
	.string "They're fresh out\nof POKé BALLS!\pWhen will they get\nmore of them?$"
J_CherrygroveMartCooltrainerMText_PokeBallsInStock::
	.string "POKé BALLS are in\nstock! Now I can\lcatch POKéMON!$"
J_CherrygroveMartYoungsterText::
	.string "When I was walking\nin the grass, a\pbug POKéMON poi-\nsoned my POKéMON!\pI just kept going,\nbut then my\lPOKéMON fainted.\pYou should keep an\nANTIDOTE with you.$"
J_CherrygroveMart_MapEvents::
