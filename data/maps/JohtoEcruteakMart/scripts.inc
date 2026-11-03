@ KJH: translated from pokecrystal maps/EcruteakMart.asm by kjh_tools/johto

JohtoEcruteakMart_MapScripts::
	.byte 0

J_W_EcruteakMartClerkScript::
	lock
	call J_EcruteakMartClerkScript
	release
	end

J_W_EcruteakMartSuperNerdScript::
	lock
	call J_EcruteakMartSuperNerdScript
	release
	end

J_W_EcruteakMartGrannyScript::
	lock
	call J_EcruteakMartGrannyScript
	release
	end

J_EcruteakMart_MapScripts::
J_EcruteakMartClerkScript::
	pokemart J_Mart_MART_ECRUTEAK
	closemessage
	return
J_EcruteakMartSuperNerdScript::
	faceplayer
	message J_EcruteakMartSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakMartGrannyScript::
	faceplayer
	message J_EcruteakMartGrannyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakMartSuperNerdText::
	.string "My EEVEE evolved\ninto an ESPEON.\pBut my friend's\nEEVEE turned into\lan UMBREON.\pI wonder why? We\nboth were raising\pour EEVEE in the\nsame way…$"
J_EcruteakMartGrannyText::
	.string "If you use REVIVE,\na POKéMON that's\pfainted will wake\nright up.$"
J_EcruteakMart_MapEvents::
