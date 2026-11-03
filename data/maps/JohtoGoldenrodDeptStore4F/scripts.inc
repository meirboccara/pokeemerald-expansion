@ KJH: translated from pokecrystal maps/GoldenrodDeptStore4F.asm by kjh_tools/johto

JohtoGoldenrodDeptStore4F_MapScripts::
	.byte 0

J_W_GoldenrodDeptStore4FClerkScript::
	lock
	call J_GoldenrodDeptStore4FClerkScript
	release
	end

J_W_GoldenrodDeptStore4FCooltrainerMScript::
	lock
	call J_GoldenrodDeptStore4FCooltrainerMScript
	release
	end

J_W_GoldenrodDeptStore4FBugCatcherScript::
	lock
	call J_GoldenrodDeptStore4FBugCatcherScript
	release
	end

J_W_GoldenrodDeptStore4FGameboyKidScript::
	lock
	call J_GoldenrodDeptStore4FGameboyKidScript
	release
	end

J_S_GoldenrodDeptStore4FDirectory::
	lockall
	call J_GoldenrodDeptStore4FDirectory
	releaseall
	end

J_S_GoldenrodDeptStore4FElevatorButton::
	lockall
	call J_GoldenrodDeptStore4FElevatorButton
	releaseall
	end

J_GoldenrodDeptStore4F_MapScripts::
J_GoldenrodDeptStore4FClerkScript::
	faceplayer
	pokemart J_Mart_MART_GOLDENROD_4F
	closemessage
	return
J_GoldenrodDeptStore4FCooltrainerMScript::
	faceplayer
	message J_GoldenrodDeptStore4FCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore4FBugCatcherScript::
	faceplayer
	message J_GoldenrodDeptStore4FBugCatcherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore4FGameboyKidScript::
	faceplayer
	message J_GoldenrodDeptStore4FGameboyKidText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 4, DIR_SOUTH
	return
J_GoldenrodDeptStore4FDirectory::
	message J_GoldenrodDeptStore4FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore4FElevatorButton::
	goto J_Std_Nop
J_GoldenrodDeptStore4FCooltrainerMText::
	.string "Hey. I love strong\nPOKéMON.\pI feed them PRO-\nTEIN to crank up\ltheir ATTACK.$"
J_GoldenrodDeptStore4FBugCatcherText::
	.string "IRON adds to your\nPOKéMON's DEFENSE.$"
J_GoldenrodDeptStore4FGameboyKidText::
	.string "Some POKéMON\nevolve only by\pbeing traded via a\nGame Link cable.\pI know of four:\nMACHOKE, KADABRA,\pHAUNTER and, um,\nGRAVELER.\pI heard there are\nothers too.$"
J_GoldenrodDeptStore4FDirectoryText::
	.string "Let Us Pump Up\nYour POKéMON!\p4F MEDICINE BOX$"
J_GoldenrodDeptStore4F_MapEvents::
