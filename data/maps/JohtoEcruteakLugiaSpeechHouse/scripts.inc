@ KJH: translated from pokecrystal maps/EcruteakLugiaSpeechHouse.asm by kjh_tools/johto

JohtoEcruteakLugiaSpeechHouse_MapScripts::
	.byte 0

J_W_EcruteakLugiaSpeechHouseGrampsScript::
	lock
	call J_EcruteakLugiaSpeechHouseGrampsScript
	release
	end

J_W_EcruteakLugiaSpeechHouseYoungsterScript::
	lock
	call J_EcruteakLugiaSpeechHouseYoungsterScript
	release
	end

J_S_LugiaSpeechHouseRadio::
	lockall
	call J_LugiaSpeechHouseRadio
	releaseall
	end

J_EcruteakLugiaSpeechHouse_MapScripts::
J_EcruteakLugiaSpeechHouseGrampsScript::
	faceplayer
	message J_EcruteakLugiaSpeechHouseGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakLugiaSpeechHouseYoungsterScript::
	faceplayer
	message J_EcruteakLugiaSpeechHouseYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_LugiaSpeechHouseRadio::
	goto J_Radio2Script
J_EcruteakLugiaSpeechHouseGrampsText::
	.string "This happened when\nI was young.\pThe sky suddenly\nturned black. A\pgiant flying POKé-\nMON was blocking\lout the sun.\pI wonder what that\nPOKéMON was? \pIt was like a bird\nand a dragon.$"
J_EcruteakLugiaSpeechHouseYoungsterText::
	.string "Is there really a\nPOKéMON that big?\pIf it exists, it\nmust be powerful.$"
J_EcruteakLugiaSpeechHouse_MapEvents::
