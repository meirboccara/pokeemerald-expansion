@ KJH: translated from pokecrystal maps/OlivineLighthouse6F.asm by kjh_tools/johto

JohtoOlivineLighthouse6F_MapScripts::
	.byte 0

J_W_OlivineLighthouseJasmine::
	lock
	call J_OlivineLighthouseJasmine
	release
	end

J_W_OlivineLighthouseAmphy::
	lock
	call J_OlivineLighthouseAmphy
	release
	end

J_OlivineLighthouse6F_MapScripts::
J_OlivineLighthouseJasmine::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_SECRETPOTION, J_L147
	setvar VAR_RESULT, 1
J_L147:
	goto_if_ne VAR_RESULT, 0, J_OlivineLighthouseJasmine_BroughtSecretpotion
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_JASMINE_EXPLAINED_AMPHYS_SICKNESS, J_L148
	setvar VAR_RESULT, 1
J_L148:
	goto_if_ne VAR_RESULT, 0, J_OlivineLighthouseJasmine_ExplainedSickness
	message J_JasmineCianwoodPharmacyText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_JASMINE_EXPLAINED_AMPHYS_SICKNESS
J_OlivineLighthouseJasmine_ExplainedSickness:
	message J_JasmineGetSomeMedicineText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineLighthouseJasmine_BroughtSecretpotion:
	message J_JasmineCureAmphyText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_OlivineLighthouseJasmine_Refused
	message J_PlayerHandedSecretpotionText
	waitmessage
	waitbuttonpress
	clearflag FLAG_J_HAS_SECRETPOTION
	setvar VAR_RESULT, 1
	message J_JasmineDontBeOffendedText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 1, DIR_EAST
	delay 15
	turnobject 2, DIR_WEST
	playbgm MUS_RG_HEAL, FALSE
	message J_JasmineAmphyHowAreYouFeelingText
	waitmessage
	delay 60
	waitbuttonpress
	closemessage
	fadedefaultbgm
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	waitmoncry
	fadescreen FADE_TO_WHITE
	delay 10
	fadescreen FADE_FROM_WHITE
	message J_AmphyPaluPaluluText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 2, DIR_EAST
	delay 10
	turnobject 2, DIR_WEST
	delay 10
	turnobject 2, DIR_EAST
	delay 10
	turnobject 2, DIR_WEST
	delay 10
	faceplayer
	message J_JasmineThankYouText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_JASMINE_RETURNED_TO_GYM
	clearflag FLAG_J_OLIVINE_GYM_JASMINE
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J_OlivineLighthouseJasmine_FacingDown
	goto_if_eq VAR_RESULT, 3, J_OlivineLighthouseJasmine_FacingRight
	applymovement 1, J_OlivineLighthouseJasmineLeavesUpMovement
	waitmovement 1
	removeobject 1
	return
J_OlivineLighthouseJasmine_FacingDown:
	applymovement 1, J_OlivineLighthouseJasmineLeavesDownMovement
	waitmovement 1
	removeobject 1
	return
J_OlivineLighthouseJasmine_FacingRight:
	applymovement 1, J_OlivineLighthouseJasmineLeavesRightMovement
	waitmovement 1
	removeobject 1
	return
J_OlivineLighthouseJasmine_Refused:
	message J_JasmineISeeText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 1, DIR_EAST
	delay 15
	turnobject 2, DIR_WEST
	message J_JasmineAmphyHangOnText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineLighthouseJasmine_Unused:
	return
J_OlivineLighthouseAmphy::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_JASMINE_RETURNED_TO_GYM, J_L149
	setvar VAR_RESULT, 1
J_L149:
	goto_if_ne VAR_RESULT, 0, J_OlivineLighthouseAmphy_HealthyNow
	message J_AmphyPalPalooText
	waitmessage
	setvar VAR_RESULT, 181
	waitbuttonpress
	message J_AmphyBreathingLaboredText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineLighthouseAmphy_HealthyNow:
	message J_AmphyPaluPaluluText
	waitmessage
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_WHITE
	fadescreen FADE_FROM_WHITE
	fadescreen FADE_TO_WHITE
	fadescreen FADE_FROM_WHITE
	return
J_OlivineLighthouse6FSuperPotion::
	finditem ITEM_SUPER_POTION, 1
	return
J_OlivineLighthouseJasmineLeavesUpMovement::
	walk_slow_up
	walk_slow_up
	walk_slow_right
	walk_slow_up
	walk_slow_up
	delay_8
	delay_8
	step_end
J_OlivineLighthouseJasmineLeavesDownMovement::
	walk_slow_down
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_slow_up
	walk_slow_right
	walk_slow_right
	walk_slow_right
	step_end
J_OlivineLighthouseJasmineLeavesRightMovement::
	walk_slow_up
	walk_slow_up
	walk_slow_right
	walk_slow_up
	walk_slow_up
	walk_slow_up
	delay_8
	step_end
J_JasmineCianwoodPharmacyText::
	.string "JASMINE: … This\nPOKéMON always\pkept the sea lit\nat night.\p…But it suddenly\ngot sick… It's\lgasping for air…\p…I understand\nthat there is a\pwonderful PHARMACY\nin CIANWOOD…\pBut that's across\nthe sea…\pAnd I can't leave\nAMPHY unattended…$"
J_JasmineGetSomeMedicineText::
	.string "…May I ask you to\nget some medicine\lfor me? Please?$"
J_JasmineCureAmphyText::
	.string "JASMINE: …Will\nthat medicine cure\lAMPHY?$"
J_PlayerHandedSecretpotionText::
	.string "{PLAYER} handed the\nSECRETPOTION to\lJASMINE.$"
J_JasmineDontBeOffendedText::
	.string "JASMINE: …Um,\nplease don't be\loffended…\p…AMPHY will not\ntake anything from\lanyone but me…$"
J_JasmineAmphyHowAreYouFeelingText::
	.string "JASMINE: …\pAMPHY, how are you\nfeeling?$"
J_JasmineThankYouText::
	.string "JASMINE: …Oh, I'm\nso relieved…\pThis is just so\nwonderful…\pThank you so very,\nvery much.\p…I will return to\nthe GYM…$"
J_JasmineISeeText::
	.string "JASMINE: …I see…$"
J_JasmineAmphyHangOnText::
	.string "…AMPHY, hang on!$"
J_AmphyPalPalooText::
	.string "AMPHY: …\n…Pa… paloo…$"
J_AmphyBreathingLaboredText::
	.string "Its breathing is\nterribly labored…$"
J_AmphyPaluPaluluText::
	.string "AMPHY: Palu!\nPalulu!$"
J_OlivineLighthouse6F_MapEvents::
