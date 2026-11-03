@ KJH: translated from pokecrystal maps/Route38EcruteakGate.asm by kjh_tools/johto

JohtoRoute38EcruteakGate_MapScripts::
	.byte 0

J_W_Route38EcruteakGateOfficerScript::
	lock
	call J_Route38EcruteakGateOfficerScript
	release
	end

J_Route38EcruteakGate_MapScripts::
J_Route38EcruteakGateOfficerScript::
	faceplayer
	message J_Route38EcruteakGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route38EcruteakGateOfficerText::
	.string "Where did you say\nyou're from?\pNEW BARK TOWN?\pPROF.ELM lives\nover there, right?\pYou've come a long\nway to get here.$"
J_Route38EcruteakGate_MapEvents::
