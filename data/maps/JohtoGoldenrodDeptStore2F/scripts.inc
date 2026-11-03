@ KJH: translated from pokecrystal maps/GoldenrodDeptStore2F.asm by kjh_tools/johto

JohtoGoldenrodDeptStore2F_MapScripts::
	.byte 0

J_W_GoldenrodDeptStore2FClerk1Script::
	lock
	call J_GoldenrodDeptStore2FClerk1Script
	release
	end

J_W_GoldenrodDeptStore2FClerk2Script::
	lock
	call J_GoldenrodDeptStore2FClerk2Script
	release
	end

J_W_GoldenrodDeptStore2FYoungsterScript::
	lock
	call J_GoldenrodDeptStore2FYoungsterScript
	release
	end

J_W_GoldenrodDeptStore2FCooltrainerFScript::
	lock
	call J_GoldenrodDeptStore2FCooltrainerFScript
	release
	end

J_W_GoldenrodDeptStore2FGentlemanScript::
	lock
	call J_GoldenrodDeptStore2FGentlemanScript
	release
	end

J_S_GoldenrodDeptStore2FDirectory::
	lockall
	call J_GoldenrodDeptStore2FDirectory
	releaseall
	end

J_S_GoldenrodDeptStore2FElevatorButton::
	lockall
	call J_GoldenrodDeptStore2FElevatorButton
	releaseall
	end

J_GoldenrodDeptStore2F_MapScripts::
J_GoldenrodDeptStore2FClerk1Script::
	faceplayer
	pokemart J_Mart_MART_GOLDENROD_2F_1
	closemessage
	return
J_GoldenrodDeptStore2FClerk2Script::
	faceplayer
	pokemart J_Mart_MART_GOLDENROD_2F_2
	closemessage
	return
J_GoldenrodDeptStore2FYoungsterScript::
	faceplayer
	message J_GoldenrodDeptStore2FYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore2FCooltrainerFScript::
	faceplayer
	message J_GoldenrodDeptStore2FCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore2FGentlemanScript::
	faceplayer
	message J_GoldenrodDeptStore2FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore2FDirectory::
	message J_GoldenrodDeptStore2FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore2FElevatorButton::
	goto J_Std_Nop
J_GoldenrodDeptStore2FUnusedText1::
	.string "We intend to sell\nitems for POKéMON\lto hold.\pThis is a free\ngift. Have a POKé-\lMON hold it.$"
J_GoldenrodDeptStore2FUnusedText2::
	.string "By giving POKéMON\nitems to hold, I\pbet trainers will\ndevelop new battle\ltechniques.$"
J_GoldenrodDeptStore2FYoungsterText::
	.string "POKéGEAR can store\nup to ten phone\lnumbers.\pIt's hard to de-\ncide which numbers\lto keep.$"
J_GoldenrodDeptStore2FCooltrainerFText::
	.string "I got my ABRA at\nthe GAME CORNER.\pNow it's my best\npartner.$"
J_GoldenrodDeptStore2FGentlemanText::
	.string "This DEPT.STORE\nmakes me realize\pthat GOLDENROD is\na big city.\pThe selection here\nis unmatched any-\lwhere else.$"
J_GoldenrodDeptStore2FDirectoryText::
	.string "Your Travel\nCompanion\p2F TRAINER'S\n   MARKET$"
J_GoldenrodDeptStore2F_MapEvents::
