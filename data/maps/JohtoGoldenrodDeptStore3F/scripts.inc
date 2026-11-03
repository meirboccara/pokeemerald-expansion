@ KJH: translated from pokecrystal maps/GoldenrodDeptStore3F.asm by kjh_tools/johto

JohtoGoldenrodDeptStore3F_MapScripts::
	.byte 0

J_W_GoldenrodDeptStore3FClerkScript::
	lock
	call J_GoldenrodDeptStore3FClerkScript
	release
	end

J_W_GoldenrodDeptStore3FSuperNerdScript::
	lock
	call J_GoldenrodDeptStore3FSuperNerdScript
	release
	end

J_W_GoldenrodDeptStore3FRockerScript::
	lock
	call J_GoldenrodDeptStore3FRockerScript
	release
	end

J_S_GoldenrodDeptStore3FDirectory::
	lockall
	call J_GoldenrodDeptStore3FDirectory
	releaseall
	end

J_S_GoldenrodDeptStore3FElevatorButton::
	lockall
	call J_GoldenrodDeptStore3FElevatorButton
	releaseall
	end

J_GoldenrodDeptStore3F_MapScripts::
J_GoldenrodDeptStore3FClerkScript::
	faceplayer
	pokemart J_Mart_MART_GOLDENROD_3F
	closemessage
	return
J_GoldenrodDeptStore3FSuperNerdScript::
	faceplayer
	message J_GoldenrodDeptStore3FSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore3FRockerScript::
	faceplayer
	message J_GoldenrodDeptStore3FRockerText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore3FDirectory::
	message J_GoldenrodDeptStore3FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore3FElevatorButton::
	goto J_Std_Nop
J_GoldenrodDeptStore3FSuperNerdText::
	.string "I, I, I'm really\nimpatient!\pI use X SPEED in\nbattle to speed up\lmy POKéMON.$"
J_GoldenrodDeptStore3FRockerText::
	.string "Hey! When you bat-\ntle, do you use X\lSPECIAL?\pIt's awesome. It\nreally jacks up\lSPECIAL ATTACK!$"
J_GoldenrodDeptStore3FDirectoryText::
	.string "For Victory\nSeekers\p3F BATTLE\n   COLLECTION$"
J_GoldenrodDeptStore3F_MapEvents::
