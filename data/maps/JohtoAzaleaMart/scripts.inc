@ KJH: translated from pokecrystal maps/AzaleaMart.asm by kjh_tools/johto

JohtoAzaleaMart_MapScripts::
	.byte 0

J_W_AzaleaMartClerkScript::
	lock
	call J_AzaleaMartClerkScript
	release
	end

J_W_AzaleaMartCooltrainerMScript::
	lock
	call J_AzaleaMartCooltrainerMScript
	release
	end

J_W_AzaleaMartBugCatcherScript::
	lock
	call J_AzaleaMartBugCatcherScript
	release
	end

J_AzaleaMart_MapScripts::
J_AzaleaMartClerkScript::
	pokemart J_Mart_MART_AZALEA
	closemessage
	return
J_AzaleaMartCooltrainerMScript::
	faceplayer
	message J_AzaleaMartCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaMartBugCatcherScript::
	faceplayer
	message J_AzaleaMartBugCatcherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaMartCooltrainerMText::
	.string "There's no GREAT\nBALL here. POKé\pBALLS will have\nto do.\pI wish KURT would\nmake me some of\lhis custom BALLS.$"
J_AzaleaMartBugCatcherText::
	.string "A GREAT BALL is\nbetter for catch-\ling POKéMON than a\lPOKé BALL.\pBut KURT's might\nbe better some-\ltimes.$"
J_AzaleaMart_MapEvents::
