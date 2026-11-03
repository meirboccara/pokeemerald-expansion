@ KJH: translated from pokecrystal maps/GoldenrodDeptStore1F.asm by kjh_tools/johto

JohtoGoldenrodDeptStore1F_MapScripts::
	.byte 0

J_W_GoldenrodDeptStore1FReceptionistScript::
	lock
	call J_GoldenrodDeptStore1FReceptionistScript
	release
	end

J_W_GoldenrodDeptStore1FPokefanFScript::
	lock
	call J_GoldenrodDeptStore1FPokefanFScript
	release
	end

J_W_GoldenrodDeptStore1FBugCatcherScript::
	lock
	call J_GoldenrodDeptStore1FBugCatcherScript
	release
	end

J_W_GoldenrodDeptStore1FGentlemanScript::
	lock
	call J_GoldenrodDeptStore1FGentlemanScript
	release
	end

J_S_GoldenrodDeptStore1FDirectory::
	lockall
	call J_GoldenrodDeptStore1FDirectory
	releaseall
	end

J_S_GoldenrodDeptStore1FElevatorButton::
	lockall
	call J_GoldenrodDeptStore1FElevatorButton
	releaseall
	end

J_GoldenrodDeptStore1F_MapScripts::
J_GoldenrodDeptStore1FReceptionistScript::
	faceplayer
	message J_GoldenrodDeptStore1FReceptionistText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore1FGentlemanScript::
	faceplayer
	message J_GoldenrodDeptStore1FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore1FPokefanFScript::
	faceplayer
	message J_GoldenrodDeptStore1FPokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore1FBugCatcherScript::
	faceplayer
	message J_GoldenrodDeptStore1FBugCatcherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore1FDirectory::
	message J_GoldenrodDeptStore1FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore1FElevatorButton::
	goto J_Std_Nop
J_GoldenrodDeptStore1FReceptionistText::
	.string "Welcome to GOLDEN-\nROD DEPT.STORE.$"
J_GoldenrodDeptStore1FGentlemanText::
	.string "The DEPT.STORE\nhas a decent se-\llection.\pBut some items\nare only available\pas GAME CORNER\nprizes.$"
J_GoldenrodDeptStore1FPokefanFText::
	.string "I'm raring to shop\nagain today!$"
J_GoldenrodDeptStore1FBugCatcherText::
	.string "Mom's good at\nbargain hunting.\pShe always buys\nstuff at lower\lprices.$"
J_GoldenrodDeptStore1FDirectoryText::
	.string "1F SERVICE COUNTER\p2F TRAINER'S\n   MARKET\p3F BATTLE\n   COLLECTION\p4F MEDICINE BOX\p5F TM CORNER\p6F TRANQUIL SQUARE\pROOFTOP LOOKOUT$"
J_GoldenrodDeptStore1F_MapEvents::
