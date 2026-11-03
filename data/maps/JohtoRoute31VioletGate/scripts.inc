@ KJH: translated from pokecrystal maps/Route31VioletGate.asm by kjh_tools/johto

JohtoRoute31VioletGate_MapScripts::
	.byte 0

J_W_Route31VioletGateOfficerScript::
	lock
	call J_Route31VioletGateOfficerScript
	release
	end

J_W_Route31VioletGateCooltrainerFScript::
	lock
	call J_Route31VioletGateCooltrainerFScript
	release
	end

J_Route31VioletGate_MapScripts::
J_Route31VioletGateOfficerScript::
	faceplayer
	message J_Route31VioletGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route31VioletGateCooltrainerFScript::
	faceplayer
	message J_Route31VioletGateCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route31VioletGateOfficerText::
	.string "Hi there!\nDid you visit\lSPROUT TOWER?$"
J_Route31VioletGateCooltrainerFText::
	.string "I came too far\nout. I'd better\lphone home!$"
J_Route31VioletGate_MapEvents::
