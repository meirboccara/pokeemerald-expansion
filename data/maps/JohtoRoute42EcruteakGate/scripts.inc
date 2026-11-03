@ KJH: translated from pokecrystal maps/Route42EcruteakGate.asm by kjh_tools/johto

JohtoRoute42EcruteakGate_MapScripts::
	.byte 0

J_W_Route42EcruteakGateOfficerScript::
	lock
	call J_Route42EcruteakGateOfficerScript
	release
	end

J_Route42EcruteakGate_MapScripts::
J_Route42EcruteakGateOfficerScript::
	faceplayer
	message J_Route42EcruteakGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route42EcruteakGateOfficerText::
	.string "MT.MORTAR is like\na maze inside.\pBe careful. Don't\nget lost in there.$"
J_Route42EcruteakGate_MapEvents::
