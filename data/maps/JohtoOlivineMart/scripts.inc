@ KJH: translated from pokecrystal maps/OlivineMart.asm by kjh_tools/johto

JohtoOlivineMart_MapScripts::
	.byte 0

J_W_OlivineMartClerkScript::
	lock
	call J_OlivineMartClerkScript
	release
	end

J_W_OlivineMartCooltrainerFScript::
	lock
	call J_OlivineMartCooltrainerFScript
	release
	end

J_W_OlivineMartLassScript::
	lock
	call J_OlivineMartLassScript
	release
	end

J_OlivineMart_MapScripts::
J_OlivineMartClerkScript::
	pokemart J_Mart_MART_OLIVINE
	closemessage
	return
J_OlivineMartCooltrainerFScript::
	faceplayer
	message J_OlivineMartCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineMartLassScript::
	faceplayer
	message J_OlivineMartLassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineMartCooltrainerFText::
	.string "Do your POKéMON\nalready know the\pmove for carrying\npeople on water?$"
J_OlivineMartLassText::
	.string "My BUTTERFREE came\nfrom my boyfriend\loverseas.\pIt carried some\nMAIL from him.\pWant to know what\nit says?\pLet's see… Nope!\nIt's a secret!$"
J_OlivineMart_MapEvents::
