@ KJH: translated from pokecrystal maps/IlexForestAzaleaGate.asm by kjh_tools/johto

JohtoIlexForestAzaleaGate_MapScripts::
	.byte 0

J_W_IlexForestAzaleaGateOfficerScript::
	lock
	call J_IlexForestAzaleaGateOfficerScript
	release
	end

J_W_IlexForestAzaleaGateGrannyScript::
	lock
	call J_IlexForestAzaleaGateGrannyScript
	release
	end

J_IlexForestAzaleaGate_MapScripts::
J_IlexForestAzaleaGateOfficerScript::
	faceplayer
	message J_IlexForestAzaleaGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_IlexForestAzaleaGateGrannyScript::
	faceplayer
	message J_IlexForestAzaleaGateGrannyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_IlexForestAzaleaGateOfficerText::
	.string "ILEX FOREST is\nbig. Be careful!\lDon't get lost.$"
J_IlexForestAzaleaGateGrannyText::
	.string "The FOREST is\nwatched over by\lits protector.\pStay out of\nmischief!$"
J_IlexForestAzaleaGate_MapEvents::
