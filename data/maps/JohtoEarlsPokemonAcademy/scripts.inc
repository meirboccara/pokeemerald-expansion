@ KJH: translated from pokecrystal maps/EarlsPokemonAcademy.asm by kjh_tools/johto

JohtoEarlsPokemonAcademy_MapScripts::
	.byte 0

J_W_AcademyEarl::
	lock
	call J_AcademyEarl
	release
	end

J_W_EarlsPokemonAcademyYoungster1Script::
	lock
	call J_EarlsPokemonAcademyYoungster1Script
	release
	end

J_W_EarlsPokemonAcademyGameboyKid1Script::
	lock
	call J_EarlsPokemonAcademyGameboyKid1Script
	release
	end

J_W_EarlsPokemonAcademyGameboyKid2Script::
	lock
	call J_EarlsPokemonAcademyGameboyKid2Script
	release
	end

J_W_EarlsPokemonAcademyYoungster2Script::
	lock
	call J_EarlsPokemonAcademyYoungster2Script
	release
	end

J_W_AcademyNotebook::
	lock
	call J_AcademyNotebook
	release
	end

J_S_AcademyBookshelf::
	lockall
	call J_AcademyBookshelf
	releaseall
	end

J_S_AcademyBlackboard::
	lockall
	call J_AcademyBlackboard
	releaseall
	end

J_EarlsPokemonAcademy_MapScripts::
J_AcademyEarl::
	applymovement 1, J_AcademyEarlSpinMovement
	waitmovement 1
	faceplayer
	message J_AcademyEarlIntroText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_AcademyEarl_Part1
	message J_AcademyEarlTeachHowToWinText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_AcademyEarl_Done
J_AcademyEarl_Part1:
	message J_AcademyEarlTeachMoreText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_AcademyEarl_Done
	message J_AcademyEarlTeachHowToRaiseWellText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AcademyEarl_Done:
	message J_AcademyEarlNoMoreToTeachText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EarlsPokemonAcademyYoungster1Script::
	faceplayer
	message J_EarlsPokemonAcademyYoungster1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EarlsPokemonAcademyGameboyKid1Script::
	faceplayer
	message J_EarlsPokemonAcademyGameboyKid1Text
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 3, DIR_SOUTH
	return
J_EarlsPokemonAcademyGameboyKid2Script::
	faceplayer
	message J_EarlsPokemonAcademyGameboyKid2Text
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 4, DIR_SOUTH
	return
J_EarlsPokemonAcademyYoungster2Script::
	faceplayer
	message J_EarlsPokemonAcademyYoungster2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AcademyBlackboard::
	message J_AcademyBlackboardText
	waitmessage
J_AcademyBlackboard_Loop:
	setvar VAR_RESULT, 1
	goto_if_eq VAR_RESULT, 1, J_AcademyBlackboard_Poison
	goto_if_eq VAR_RESULT, 2, J_AcademyBlackboard_Paralysis
	goto_if_eq VAR_RESULT, 3, J_AcademyBlackboard_Sleep
	goto_if_eq VAR_RESULT, 4, J_AcademyBlackboard_Burn
	goto_if_eq VAR_RESULT, 5, J_AcademyBlackboard_Freeze
	closemessage
	return
J_AcademyBlackboard_Poison:
	message J_AcademyPoisonText
	waitmessage
	waitbuttonpress
	goto J_AcademyBlackboard_Loop
J_AcademyBlackboard_Paralysis:
	message J_AcademyParalysisText
	waitmessage
	waitbuttonpress
	goto J_AcademyBlackboard_Loop
J_AcademyBlackboard_Sleep:
	message J_AcademySleepText
	waitmessage
	waitbuttonpress
	goto J_AcademyBlackboard_Loop
J_AcademyBlackboard_Burn:
	message J_AcademyBurnText
	waitmessage
	waitbuttonpress
	goto J_AcademyBlackboard_Loop
J_AcademyBlackboard_Freeze:
	message J_AcademyFreezeText
	waitmessage
	waitbuttonpress
	goto J_AcademyBlackboard_Loop
J_AcademyBlackboard_BlackboardMenuHeader:
J_AcademyBlackboard_MenuData:
J_AcademyBlackboard_Text:
	.string "PSN$"
	.string "PAR$"
	.string "SLP$"
	.string "BRN$"
	.string "FRZ$"
	.string "QUIT$"
J_AcademyNotebook::
	message J_AcademyNotebookText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_AcademyNotebook_Done
	message J_AcademyNotebookText1
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_AcademyNotebook_Done
	message J_AcademyNotebookText2
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_AcademyNotebook_Done
	message J_AcademyNotebookText3
	waitmessage
	waitbuttonpress
J_AcademyNotebook_Done:
	closemessage
	return
J_AcademyStickerMachine::
	message J_AcademyStickerMachineText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AcademyBookshelf::
	goto J_DifficultBookshelfScript
J_AcademyEarlSpinMovement::
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	step_end
J_AcademyEarlIntroText::
	.string "EARL, I am!\pWonderful are\nPOKéMON, yes!\pTeach you I will\nto be a better\ltrainer!\pWhat you want to\nknow? Want to be\la winner is you?$"
J_AcademyEarlTeachHowToWinText::
	.string "Good! Teach you,\nI will!\pIn battle, POKéMON\ntop on list jump\lout first!\pChange order in\nlist, make battle\leasy, maybe!\pMore from me you\nwant to hear?$"
J_AcademyEarlTeachMoreText::
	.string "So, want to know\nhow to raise\lPOKéMON well?$"
J_AcademyEarlTeachHowToRaiseWellText::
	.string "Fine! Teach you,\nI will!\pIf POKéMON come\nout in battle even\pbriefly, some EXP.\nPoints it gets.\pAt top of list put\nweak POKéMON.\pSwitch in battle\nquick!\pThis way, weak\nPOKéMON strong\lbecome!$"
J_AcademyEarlNoMoreToTeachText::
	.string "Oh! Smart student\nyou are! Nothing\lmore do I teach!\pGood to POKéMON\nyou must be!$"
J_EarlsPokemonAcademyYoungster1Text::
	.string "I'm taking notes\nof the teacher's\llecture.\pI'd better copy\nthe stuff on the\lblackboard too.$"
J_EarlsPokemonAcademyGameboyKid1Text::
	.string "I traded my best\nPOKéMON to the\lguy beside me.$"
J_EarlsPokemonAcademyGameboyKid2Text::
	.string "Huh? The POKéMON I\njust got is hold-\ling something!$"
J_EarlsPokemonAcademyYoungster2Text::
	.string "A POKéMON holding\na BERRY will heal\litself in battle.\pMany other items\ncan be held by\lPOKéMON…\pIt sure is tough\ntaking notes…$"
J_AcademyBlackboardText::
	.string "The blackboard\ndescribes POKéMON\pstatus changes in\nbattle.$"
J_AcademyBlackboardText2::
	.string "Read which topic?$"
J_AcademyPoisonText::
	.string "If poisoned, a\nPOKéMON steadily\lloses HP.\pPoison lingers\nafter the battle,\pand HP is lost as\nyou walk.\pTo cure it, use an\nANTIDOTE.$"
J_AcademyParalysisText::
	.string "Paralysis reduces\nspeed and may\lprevent movement.\pIt remains after\nbattle, so use\la PARLYZ HEAL.$"
J_AcademySleepText::
	.string "If asleep, your\nPOKéMON can't make\la move.\pA sleeping POKéMON\ndoesn't wake up\lafter battle.\pWake it up with\nan AWAKENING.$"
J_AcademyBurnText::
	.string "A burn steadily\nconsumes HP.\pIt also reduces\nattack power.\pA burn lingers\nafter battle.\pUse a BURN HEAL as\nthe cure.$"
J_AcademyFreezeText::
	.string "If your POKéMON is\nfrozen, it can't\ldo a thing.\pIt remains frozen\nafter battle.\pThaw it out with\nan ICE HEAL.$"
J_AcademyNotebookText::
	.string "It's this kid's\nnotebook…\pCatch POKéMON\nusing POKé BALLS.\pUp to six can be\nin your party.\pKeep reading?$"
J_AcademyNotebookText1::
	.string "Before throwing a\nPOKé BALL, weaken\lthe target first.\pA poisoned or\nburned POKéMON is\leasier to catch.\pKeep reading?$"
J_AcademyNotebookText2::
	.string "Some moves may\ncause confusion.\pConfusion may make\na POKéMON attack\litself.\pLeaving battle\nclears up any\lconfusion.\pKeep reading?$"
J_AcademyNotebookText3::
	.string "People who catch\nand use POKéMON\pin battle are\nPOKéMON trainers.\pThey are expected\nto visit POKéMON\pGYMS and defeat\nother trainers.\pThe next page\nis… Blank!\pBoy: E-he-he…\pI haven't written\nanymore…$"
J_AcademyStickerMachineText::
	.string "This super machine\nprints data out as\pstickers!$"
J_EarlsPokemonAcademy_MapEvents::
