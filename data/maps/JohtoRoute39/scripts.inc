@ KJH: translated from pokecrystal maps/Route39.asm by kjh_tools/johto

JohtoRoute39_MapScripts::
	.byte 0

J_T_TrainerSailorEugene::
	trainerbattle_single TRAINER_J_SAILOR_EUGENE, J_SailorEugeneSeenText, J_SailorEugeneBeatenText
	call J_TrainerSailorEugene_Script
	release
	end

J_T_TrainerPokefanmDerek::
	trainerbattle_single TRAINER_J_POKEFANM_DEREK1, J_PokefanmDerekSeenText, J_PokefanmDerekBeatenText
	call J_TrainerPokefanmDerek_Script
	release
	end

J_T_TrainerPokefanfRuth::
	trainerbattle_single TRAINER_J_POKEFANF_RUTH, J_PokefanfRuthSeenText, J_PokefanfRuthBeatenText
	call J_TrainerPokefanfRuth_Script
	release
	end

J_W_Route39Miltank::
	lock
	call J_Route39Miltank
	release
	end

J_T_TrainerPsychicNorman::
	trainerbattle_single TRAINER_J_PSYCHIC_T_NORMAN, J_PsychicNormanSeenText, J_PsychicNormanBeatenText
	call J_TrainerPsychicNorman_Script
	release
	end

J_W_Route39FruitTree::
	lock
	call J_Route39FruitTree
	release
	end

J_W_TrainerPokefanfJaime::
	lock
	call J_TrainerPokefanfJaime
	release
	end

J_S_Route39TrainerTips::
	lockall
	call J_Route39TrainerTips
	releaseall
	end

J_S_MoomooFarmSign::
	lockall
	call J_MoomooFarmSign
	releaseall
	end

J_S_Route39Sign::
	lockall
	call J_Route39Sign
	releaseall
	end

J_Route39_MapScripts::
J_Route39Miltank::
	message J_Route39MiltankText
	waitmessage
	playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_TrainerPokefanmDerek::
J_TrainerPokefanmDerek_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_DEREK_HAS_NUGGET, J_L30
	setvar VAR_RESULT, 1
J_L30:
	goto_if_ne VAR_RESULT, 0, J_TrainerPokefanmDerek_HasNugget
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerPokefanmDerek_NumberAccepted
	setvar VAR_0x8004, SPECIES_PIKACHU
	special KJH_CheckPartySpecies
	goto_if_eq VAR_RESULT, 0, J_TrainerPokefanmDerek_WantsPikachu
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_DEREK_ASKED_FOR_PHONE_NUMBER, J_L31
	setvar VAR_RESULT, 1
J_L31:
	goto_if_ne VAR_RESULT, 0, J_TrainerPokefanmDerek_AskedAlready
	message J_PokefanMDerekText_NotBragging
	waitmessage
	waitbuttonpress
	setflag FLAG_J_DEREK_ASKED_FOR_PHONE_NUMBER
	call J_TrainerPokefanmDerek_AskNumber1
	goto J_TrainerPokefanmDerek_AskForNumber
J_TrainerPokefanmDerek_AskedAlready:
	call J_TrainerPokefanmDerek_AskNumber2
J_TrainerPokefanmDerek_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerPokefanmDerek_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerPokefanmDerek_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_POKEFANM_DEREK1
	call J_TrainerPokefanmDerek_RegisteredNumber
	goto J_TrainerPokefanmDerek_NumberAccepted
J_TrainerPokefanmDerek_HasNugget:
	call J_TrainerPokefanmDerek_Gift
	giveitem ITEM_NUGGET, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerPokefanmDerek_NoRoom
	clearflag FLAG_J_ENGINE_DEREK_HAS_NUGGET
	goto J_TrainerPokefanmDerek_NumberAccepted
J_TrainerPokefanmDerek_NoRoom:
	goto J_TrainerPokefanmDerek_PackFull
J_TrainerPokefanmDerek_WantsPikachu:
	message J_PokefanMDerekPikachuIsItText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPokefanmDerek_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerPokefanmDerek_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerPokefanmDerek_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerPokefanmDerek_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerPokefanmDerek_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerPokefanmDerek_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerPokefanmDerek_Gift:
	goto J_Std_Nop
	return
J_TrainerPokefanmDerek_PackFull:
	goto J_Std_Nop
	return
J_TrainerPokefanfRuth::
J_TrainerPokefanfRuth_Script:
	message J_PokefanfRuthAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSailorEugene::
J_TrainerSailorEugene_Script:
	message J_SailorEugeneAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPsychicNorman::
J_TrainerPsychicNorman_Script:
	message J_PsychicNormanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPokefanfJaime::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_TrainerPokefanfJaime_NotNight
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_POKEFANF_JAIME, J_L32
	setvar VAR_RESULT, 1
J_L32:
	goto_if_ne VAR_RESULT, 0, J_TrainerPokefanfJaime_Beaten
	message J_PokefanfJaimeSeenText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_J_POKEFANF_JAIME, J_PokefanfJaimeBeatenText
	setflag FLAG_J_BEAT_POKEFANF_JAIME
	closemessage
	return
J_TrainerPokefanfJaime_Beaten:
	message J_PokefanfJaimeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPokefanfJaime_NotNight:
	message J_PokefanfJaimeHopeItGetsDarkText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route39Sign::
	message J_Route39SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MoomooFarmSign::
	message J_MoomooFarmSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route39TrainerTips::
	message J_Route39TrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route39FruitTree::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_Route39HiddenNugget::
	finditem ITEM_NUGGET
	return
J_Route39MiltankText::
	.string "MILTANK: Mooo!$"
J_SailorEugeneSeenText::
	.string "I just got back to\nOLIVINE.\pSo how about a\nPOKéMON battle?$"
J_SailorEugeneBeatenText::
	.string "Awaaargh!$"
J_SailorEugeneAfterBattleText::
	.string "My POKéMON were\ncaught and raised\loverseas.\pThey're my compan-\nions on those long\lvoyages.$"
J_PokefanmDerekSeenText::
	.string "This is a good\ntime to brag about\lmy PIKACHU!$"
J_PokefanmDerekBeatenText::
	.string "I had no time to\nshow off PIKACHU…$"
J_PokefanMDerekText_NotBragging::
	.string "I'm not listening\nto your bragging!\pWe POKé FANS have\na policy of not\plistening to other\npeople brag!$"
J_PokefanfRuthSeenText::
	.string "Such darling\nPOKéMON.\pLet's show our\nPOKéMON together\lat the same time.$"
J_PokefanfRuthBeatenText::
	.string "I don't mind\nlosing.$"
J_PokefanfRuthAfterBattleText::
	.string "Do you know about\nbaby POKéMON?\pI bet they're just\nadorable!$"
J_PokefanMDerekPikachuIsItText::
	.string "PIKACHU is it!\nDon't you agree?$"
J_PsychicNormanSeenText::
	.string "Let me see what\nyour POKéMON are\lcapable of.$"
J_PsychicNormanBeatenText::
	.string "Ooh, your POKéMON\nhave potential.$"
J_PsychicNormanAfterBattleText::
	.string "You know how POKé-\nMON have different\labilities?\pPeople are like\nthat too. Every-\lone has different\lpotential.$"
J_PokefanfJaimeHopeItGetsDarkText::
	.string "Ufufufu… I hope it\ngets dark soon.$"
J_PokefanfJaimeSeenText::
	.string "You came at just\nthe right time.\pLet's battle.$"
J_PokefanfJaimeBeatenText::
	.string "Oh, how disap-\npointing…$"
J_PokefanfJaimeAfterBattleText::
	.string "I met my MEOWTH at\nnight, right here\lon ROUTE 39.\pI'm not sure why,\nbut it seems to\plike it when I\ntrain here.\pIt seems to become\nfriendlier by\ptraining here than\nanywhere else.$"
J_Route39SignText::
	.string "ROUTE 39\pOLIVINE CITY -\nECRUTEAK CITY$"
J_MoomooFarmSignText::
	.string "MOOMOO FARM\pEnjoy Our Fresh\nand Tasty Milk$"
J_Route39TrainerTipsText::
	.string "TRAINER TIPS\pUse HEADBUTT on\ntrees to shake\lPOKéMON out.\pDifferent kinds of\nPOKéMON drop out\lof trees.\pUse HEADBUTT on\nany tree you see!$"
J_Route39_MapEvents::
