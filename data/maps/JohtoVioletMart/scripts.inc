@ KJH: translated from pokecrystal maps/VioletMart.asm by kjh_tools/johto

JohtoVioletMart_MapScripts::
	.byte 0

J_W_VioletMartClerkScript::
	lock
	call J_VioletMartClerkScript
	release
	end

J_W_VioletMartGrannyScript::
	lock
	call J_VioletMartGrannyScript
	release
	end

J_W_VioletMartCooltrainerMScript::
	lock
	call J_VioletMartCooltrainerMScript
	release
	end

J_VioletMart_MapScripts::
J_VioletMartClerkScript::
	pokemart J_Mart_MART_VIOLET
	closemessage
	return
J_VioletMartGrannyScript::
	faceplayer
	message J_VioletMartGrannyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletMartCooltrainerMScript::
	faceplayer
	message J_VioletMartCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletMartGrannyText::
	.string "When you first\ncatch a POKéMON,\lit may be weak.\pBut it will even-\ntually grow to be\lstrong.\pIt's important to\ntreat POKéMON with\llove.$"
J_VioletMartCooltrainerMText::
	.string "POKéMON can hold\nitems like POTION\land ANTIDOTE.\pBut they don't\nappear to know how\pto use manmade\nitems.$"
J_VioletMart_MapEvents::
