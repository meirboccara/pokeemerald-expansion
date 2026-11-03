@ KJH: translated from pokecrystal maps/Route32RuinsOfAlphGate.asm by kjh_tools/johto

JohtoRoute32RuinsOfAlphGate_MapScripts::
	.byte 0

J_W_Route32RuinsOfAlphGateOfficerScript::
	lock
	call J_Route32RuinsOfAlphGateOfficerScript
	release
	end

J_W_Route32RuinsOfAlphGatePokefanMScript::
	lock
	call J_Route32RuinsOfAlphGatePokefanMScript
	release
	end

J_W_Route32RuinsOfAlphGateYoungsterScript::
	lock
	call J_Route32RuinsOfAlphGateYoungsterScript
	release
	end

J_Route32RuinsOfAlphGate_MapScripts::
J_Route32RuinsOfAlphGateOfficerScript::
	faceplayer
	message J_Route32RuinsOfAlphGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route32RuinsOfAlphGatePokefanMScript::
	faceplayer
	message J_Route32RuinsOfAlphGatePokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route32RuinsOfAlphGateYoungsterScript::
	faceplayer
	message J_Route32RuinsOfAlphGateYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route32RuinsOfAlphGateOfficerText::
	.string "RUINS OF ALPH\pA Look-and-Touch\nTourist Site\pTry the sliding\nstone panels!$"
J_Route32RuinsOfAlphGatePokefanMText::
	.string "You're studying\nthe RUINS?\pI see a scientist\nin the making.$"
J_Route32RuinsOfAlphGateYoungsterText::
	.string "There are drawings\non stone panels.\pI tried moving\nthem. I wonder\lwhat they are.$"
J_Route32RuinsOfAlphGate_MapEvents::
