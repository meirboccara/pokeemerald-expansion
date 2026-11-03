@ KJH: translated from pokecrystal maps/Route36RuinsOfAlphGate.asm by kjh_tools/johto

JohtoRoute36RuinsOfAlphGate_MapScripts::
	.byte 0

J_W_Route36RuinsOfAlphGateOfficerScript::
	lock
	call J_Route36RuinsOfAlphGateOfficerScript
	release
	end

J_W_Route36RuinsOfAlphGateGrampsScript::
	lock
	call J_Route36RuinsOfAlphGateGrampsScript
	release
	end

J_Route36RuinsOfAlphGate_MapScripts::
J_Route36RuinsOfAlphGateOfficerScript::
	faceplayer
	message J_Route36RuinsOfAlphGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36RuinsOfAlphGateGrampsScript::
	faceplayer
	message J_Route36RuinsOfAlphGateGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36RuinsOfAlphGateOfficerText::
	.string "Don't you wonder\nwho'd make some-\lthing like this?\lAnd why?$"
J_Route36RuinsOfAlphGateGrampsText::
	.string "Did you see that\nstrange tree in\lthe road?\pThat may explain\nwhy fewer people\pare visiting the\nRUINS OF ALPH.$"
J_Route36RuinsOfAlphGate_MapEvents::
