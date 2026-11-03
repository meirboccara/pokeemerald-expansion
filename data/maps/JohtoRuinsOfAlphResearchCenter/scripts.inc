@ KJH: translated from pokecrystal maps/RuinsOfAlphResearchCenter.asm by kjh_tools/johto

JohtoRuinsOfAlphResearchCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoRuinsOfAlphResearchCenter_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoRuinsOfAlphResearchCenter_OnFrame
	.byte 0

JohtoRuinsOfAlphResearchCenter_OnTransition:
	call J_RuinsOfAlphResearchCenterScientistCallback
	end

JohtoRuinsOfAlphResearchCenter_OnFrame:
	map_script_2 VAR_J_SCENE_RUINS_OF_ALPH_RESEARCH_CENTER, 1, J_SC_RuinsOfAlphResearchCenterGetUnownDexScene
	.2byte 0

J_W_RuinsOfAlphResearchCenterScientist1Script::
	lock
	call J_RuinsOfAlphResearchCenterScientist1Script
	release
	end

J_W_RuinsOfAlphResearchCenterScientist2Script::
	lock
	call J_RuinsOfAlphResearchCenterScientist2Script
	release
	end

J_W_RuinsOfAlphResearchCenterScientist3Script::
	lock
	call J_RuinsOfAlphResearchCenterScientist3Script
	release
	end

J_S_RuinsOfAlphResearchCenterBookshelf::
	lockall
	call J_RuinsOfAlphResearchCenterBookshelf
	releaseall
	end

J_S_RuinsOfAlphResearchCenterComputer::
	lockall
	call J_RuinsOfAlphResearchCenterComputer
	releaseall
	end

J_S_RuinsOfAlphResearchCenterPrinter::
	lockall
	call J_RuinsOfAlphResearchCenterPrinter
	releaseall
	end

J_SC_RuinsOfAlphResearchCenterGetUnownDexScene::
	lockall
	call J_RuinsOfAlphResearchCenterGetUnownDexScene
	releaseall
	end

J_RuinsOfAlphResearchCenter_MapScripts::
J_RuinsOfAlphResearchCenterNoopScene::
	return
J_RuinsOfAlphResearchCenterGetUnownDexScene::
	call J_RuinsOfAlphResearchCenterGetUnownDexScript
	return
J_RuinsOfAlphResearchCenterScientistCallback::
	copyvar VAR_RESULT, VAR_J_SCENE_RUINS_OF_ALPH_RESEARCH_CENTER
	goto_if_eq VAR_RESULT, 0, J_RuinsOfAlphResearchCenterScientistCallback_ShowScientist
	return
J_RuinsOfAlphResearchCenterScientistCallback_ShowScientist:
	setobjectxyperm 3, 3, 7
	clearflag FLAG_J_RUINS_OF_ALPH_RESEARCH_CENTER_SCIENTIST
	return
J_RuinsOfAlphResearchCenterGetUnownDexScript::
	applymovement 3, J_RuinsOfAlphResearchCenterApproachesComputerMovement
	waitmovement 3
	playse SE_PC_ON
	delay 60
	playse SE_BALL_OPEN
	delay 30
	playse SE_SELECT
	delay 30
	playse SE_SHOP
	delay 30
	turnobject 3, DIR_SOUTH
	message J_RuinsOfAlphResearchCenterModifiedDexText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, J_RuinsOfAlphResearchCenterApproachesPlayerMovement
	waitmovement 3
	message J_RuinsOfAlphResearchCenterDexUpgradedText
	waitmessage
	playse SE_SUCCESS
	waitse
	setflag FLAG_J_ENGINE_UNOWN_DEX
	message J_RuinsOfAlphResearchCenterScientist3Text
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, J_RuinsOfAlphResearchCenterLeavesPlayerMovement
	waitmovement 3
	setvar VAR_J_SCENE_RUINS_OF_ALPH_RESEARCH_CENTER, 0
	fadedefaultbgm
	return
J_RuinsOfAlphResearchCenterScientist3Script::
	faceplayer
	setvar VAR_0x8004, 14
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 26, J_RuinsOfAlphResearchCenterScientist3Script_PrinterAvailable
	message J_RuinsOfAlphResearchCenterScientist3Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphResearchCenterScientist3Script_PrinterAvailable:
	message J_RuinsOfAlphResearchCenterScientist3_PrinterAvailable
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphResearchCenterScientist1Script::
	faceplayer
	setvar VAR_0x8004, 14
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 26, J_RuinsOfAlphResearchCenterScientist1Script_GotAllUnown
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_UNOWN_DEX, J_L133
	setvar VAR_RESULT, 1
J_L133:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphResearchCenterScientist1Script_GotUnownDex
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_MADE_UNOWN_APPEAR_IN_RUINS, J_L134
	setvar VAR_RESULT, 1
J_L134:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphResearchCenterScientist1Script_UnownAppeared
	message J_RuinsOfAlphResearchCenterScientist1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphResearchCenterScientist1Script_UnownAppeared:
	message J_RuinsOfAlphResearchCenterScientist1Text_UnownAppeared
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphResearchCenterScientist1Script_GotUnownDex:
	message J_RuinsOfAlphResearchCenterScientist1Text_GotUnownDex
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphResearchCenterScientist1Script_GotAllUnown:
	message J_RuinsOfAlphResearchCenterScientist1Text_GotAllUnown
	waitmessage
	waitbuttonpress
	closemessage
	clearflag FLAG_J_RUINS_OF_ALPH_OUTSIDE_TOURIST_YOUNGSTERS
	return
J_RuinsOfAlphResearchCenterScientist2Script::
	faceplayer
	setvar VAR_0x8004, 14
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 26, J_RuinsOfAlphResearchCenterScientist2Script_GotAllUnown
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_MADE_UNOWN_APPEAR_IN_RUINS, J_L135
	setvar VAR_RESULT, 1
J_L135:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphResearchCenterScientist2Script_UnownAppeared
	message J_RuinsOfAlphResearchCenterScientist2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphResearchCenterScientist2Script_UnownAppeared:
	message J_RuinsOfAlphResearchCenterScientist2Text_UnownAppeared
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphResearchCenterScientist2Script_GotAllUnown:
	message J_RuinsOfAlphResearchCenterScientist2Text_GotAllUnown
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphResearchCenterComputer::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RUINS_OF_ALPH_RESEARCH_CENTER_SCIENTIST, J_L136
	setvar VAR_RESULT, 1
J_L136:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphResearchCenterComputer_SkipChecking
	setvar VAR_0x8004, 14
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 26, J_RuinsOfAlphResearchCenterComputer_GotAllUnown
J_RuinsOfAlphResearchCenterComputer_SkipChecking:
	message J_RuinsOfAlphResearchCenterComputerText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphResearchCenterComputer_GotAllUnown:
	message J_RuinsOfAlphResearchCenterComputerText_GotAllUnown
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphResearchCenterPrinter::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RUINS_OF_ALPH_RESEARCH_CENTER_SCIENTIST, J_L137
	setvar VAR_RESULT, 1
J_L137:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphResearchCenterPrinter_SkipChecking
	setvar VAR_0x8004, 14
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 26, J_RuinsOfAlphResearchCenterPrinter_PrinterAvailable
J_RuinsOfAlphResearchCenterPrinter_SkipChecking:
	message J_RuinsOfAlphResearchCenterPrinterText_DoesntWork
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphResearchCenterPrinter_PrinterAvailable:
	message J_RuinsOfAlphResearchCenterUnownPrinterText
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	closemessage
	return
J_RuinsOfAlphResearchCenterPhoto::
	message J_RuinsOfAlphResearchCenterProfSilktreePhotoText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphResearchCenterBookshelf::
	message J_RuinsOfAlphResearchCenterAcademicBooksText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphResearchCenterApproachesComputerMovement::
	walk_up
	walk_up
	walk_left
	face_up
	step_end
J_RuinsOfAlphResearchCenterApproachesPlayerMovement::
	walk_down
	step_end
J_RuinsOfAlphResearchCenterLeavesPlayerMovement::
	walk_up
	step_end
J_RuinsOfAlphResearchCenterModifiedDexText::
	.string "Done!\pI modified your\nPOKéDEX.\pI added an\noptional POKéDEX\pto store UNOWN\ndata.\pIt records them in\nthe sequence that\lthey were caught.$"
J_RuinsOfAlphResearchCenterDexUpgradedText::
	.string "{PLAYER}'s POKéDEX\nwas upgraded.$"
J_RuinsOfAlphResearchCenterScientist3Text::
	.string "The UNOWN you\ncatch will all be\lrecorded.\pCheck to see how\nmany kinds exist.$"
J_RuinsOfAlphResearchCenterScientist3_PrinterAvailable::
	.string "You caught all the\nUNOWN variations?\pThat's a great\nachievement!\pI've set up the\nprinter here for\lhandling UNOWN.\pFeel free to use\nit anytime.$"
J_RuinsOfAlphResearchCenterScientist1Text::
	.string "The RUINS are\nabout 1500 years\lold.\pBut it's not known\nwhy they were\lbuilt--or by whom.$"
J_RuinsOfAlphResearchCenterScientist1Text_GotUnownDex::
	.string "I wonder how many\nkinds of POKéMON\lare in the RUINS?$"
J_RuinsOfAlphResearchCenterScientist1Text_UnownAppeared::
	.string "POKéMON appeared\nin the RUINS?\pThat's incredible\nnews!\pWe'll need to\ninvestigate this.$"
J_RuinsOfAlphResearchCenterScientist1Text_GotAllUnown::
	.string "Our investigation,\nwith your help, is\pgiving us insight\ninto the RUINS.\pThe RUINS appear\nto have been built\pas a habitat for\nPOKéMON.$"
J_RuinsOfAlphResearchCenterScientist2Text::
	.string "There are odd pat-\nterns drawn on the\pwalls of the\nRUINS.\pThey must be the\nkeys for unravel-\ling the mystery\lof the RUINS.$"
J_RuinsOfAlphResearchCenterScientist2Text_UnownAppeared::
	.string "The strange POKé-\nMON you saw in the\lRUINS?\pThey appear to be\nvery much like the\pdrawings on the\nwalls there.\pHmm…\pThat must mean\nthere are many\lkinds of them…$"
J_RuinsOfAlphResearchCenterUnusedText1::
	.string "We think something\ncaused the cryptic\ppatterns to appear\nin the RUINS.\pWe've focused our\nstudies on that.$"
J_RuinsOfAlphResearchCenterUnusedText2::
	.string "According to my\nresearch…\pThose mysterious\npatterns appeared\pwhen the POKéCOM\nCENTER was built.\pIt must mean that\nradio waves have\psome sort of a\nlink…$"
J_RuinsOfAlphResearchCenterScientist2Text_GotAllUnown::
	.string "Why did those\nancient patterns\pappear on the wall\nnow?\pThe mystery\ndeepens…$"
J_RuinsOfAlphResearchCenterComputerText::
	.string "RUINS OF ALPH\pExploration\nYear 10$"
J_RuinsOfAlphResearchCenterComputerText_GotAllUnown::
	.string "Mystery POKéMON\nName: UNOWN\pA total of 26\nkinds found.$"
J_RuinsOfAlphResearchCenterPrinterText_DoesntWork::
	.string "This doesn't seem\nto work yet.$"
J_RuinsOfAlphResearchCenterUnownPrinterText::
	.string "UNOWN may be\nprinted out.$"
J_RuinsOfAlphResearchCenterProfSilktreePhotoText::
	.string "It's a photo of\nthe RESEARCH\pCENTER'S founder,\nPROF.SILKTREE.$"
J_RuinsOfAlphResearchCenterAcademicBooksText::
	.string "There are many\nacademic books.\pAncient Ruins…\nMysteries of the\lAncients…$"
J_RuinsOfAlphResearchCenter_MapEvents::
