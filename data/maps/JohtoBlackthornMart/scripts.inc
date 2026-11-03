@ KJH: translated from pokecrystal maps/BlackthornMart.asm by kjh_tools/johto

JohtoBlackthornMart_MapScripts::
	.byte 0

J_W_BlackthornMartClerkScript::
	lock
	call J_BlackthornMartClerkScript
	release
	end

J_W_BlackthornMartCooltrainerMScript::
	lock
	call J_BlackthornMartCooltrainerMScript
	release
	end

J_W_BlackthornMartBlackBeltScript::
	lock
	call J_BlackthornMartBlackBeltScript
	release
	end

J_BlackthornMart_MapScripts::
J_BlackthornMartClerkScript::
	pokemart J_Mart_MART_BLACKTHORN
	closemessage
	return
J_BlackthornMartCooltrainerMScript::
	faceplayer
	message J_BlackthornMartCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornMartBlackBeltScript::
	faceplayer
	message J_BlackthornMartBlackBeltText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornMartCooltrainerMText::
	.string "You can't buy MAX\nREVIVE, but it\pfully restores a\nfainted POKéMON.\pBeware--it won't\nrestore PP, the\pPOWER POINTS\nneeded for moves.$"
J_BlackthornMartBlackBeltText::
	.string "MAX REPEL keeps\nweak POKéMON away\lfrom you.\pIt's the longest\nlasting of the\lREPEL sprays.$"
J_BlackthornMart_MapEvents::
