@ KJH: translated from pokecrystal maps/NationalPark.asm by kjh_tools/johto

JohtoNationalPark_MapScripts::
	.byte 0

J_W_NationalParkLassScript::
	lock
	call J_NationalParkLassScript
	release
	end

J_W_NationalParkPokefanFScript::
	lock
	call J_NationalParkPokefanFScript
	release
	end

J_W_NationalParkTeacher1Script::
	lock
	call J_NationalParkTeacher1Script
	release
	end

J_W_NationalParkYoungster1Script::
	lock
	call J_NationalParkYoungster1Script
	release
	end

J_W_NationalParkYoungster2Script::
	lock
	call J_NationalParkYoungster2Script
	release
	end

J_W_NationalParkTeacher2Script::
	lock
	call J_NationalParkTeacher2Script
	release
	end

J_W_NationalParkPersian::
	lock
	call J_NationalParkPersian
	release
	end

J_T_TrainerSchoolboyJack1::
	trainerbattle_single TRAINER_J_SCHOOLBOY_JACK1, J_SchoolboyJack1SeenText, J_SchoolboyJack1BeatenText
	call J_TrainerSchoolboyJack1_Script
	release
	end

J_T_TrainerPokefanfBeverly1::
	trainerbattle_single TRAINER_J_POKEFANF_BEVERLY1, J_PokefanfBeverly1SeenText, J_PokefanfBeverly1BeatenText
	call J_TrainerPokefanfBeverly1_Script
	release
	end

J_T_TrainerPokefanmWilliam::
	trainerbattle_single TRAINER_J_POKEFANM_WILLIAM, J_PokefanmWilliamSeenText, J_PokefanmWilliamBeatenText
	call J_TrainerPokefanmWilliam_Script
	release
	end

J_T_TrainerLassKrise::
	trainerbattle_single TRAINER_J_LASS_KRISE, J_LassKriseSeenText, J_LassKriseBeatenText
	call J_TrainerLassKrise_Script
	release
	end

J_W_NationalParkGameboyKidScript::
	lock
	call J_NationalParkGameboyKidScript
	release
	end

J_S_NationalParkRelaxationSquareSign::
	lockall
	call J_NationalParkRelaxationSquareSign
	releaseall
	end

J_S_NationalParkBattleNoticeSign::
	lockall
	call J_NationalParkBattleNoticeSign
	releaseall
	end

J_S_NationalParkTrainerTipsSign::
	lockall
	call J_NationalParkTrainerTipsSign
	releaseall
	end

J_NationalPark_MapScripts::
J_NationalParkLassScript::
	faceplayer
	message J_NationalParkLassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NationalParkPokefanFScript::
	faceplayer
	message J_NationalParkPokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NationalParkTeacher1Script::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_QUICK_CLAW, J_L77
	setvar VAR_RESULT, 1
J_L77:
	goto_if_ne VAR_RESULT, 0, J_NationalParkTeacher1Script_GotQuickClaw
	message J_NationalParkTeacher1Text
	waitmessage
	waitbuttonpress
	giveitem ITEM_QUICK_CLAW, 1
	goto_if_eq VAR_RESULT, 0, J_NationalParkTeacher1Script_NoRoom
	setflag FLAG_J_GOT_QUICK_CLAW
J_NationalParkTeacher1Script_GotQuickClaw:
	message J_NationalParkTeacher1Text_GotQuickClaw
	waitmessage
	waitbuttonpress
J_NationalParkTeacher1Script_NoRoom:
	closemessage
	return
J_NationalParkYoungster1Script::
	faceplayer
	message J_NationalParkYoungster1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NationalParkYoungster2Script::
	faceplayer
	message J_NationalParkYoungster2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NationalParkTeacher2Script::
	faceplayer
	message J_NationalParkTeacher2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NationalParkPersian::
	faceplayer
	message J_NationalParkPersianText
	waitmessage
	playmoncry SPECIES_PERSIAN, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_NationalParkGameboyKidScript::
	faceplayer
	message J_NationalParkGameboyKidText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 13, DIR_SOUTH
	return
J_TrainerSchoolboyJack1::
J_TrainerSchoolboyJack1_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_JACK_READY_FOR_REMATCH, J_L78
	setvar VAR_RESULT, 1
J_L78:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyJack1_Rematch
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyJack1_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_JACK_ASKED_FOR_PHONE_NUMBER, J_L79
	setvar VAR_RESULT, 1
J_L79:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyJack1_AskAgain
	message J_SchoolboyJackTradeMonText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_JACK_ASKED_FOR_PHONE_NUMBER
	call J_TrainerSchoolboyJack1_AskNumber1
	goto J_TrainerSchoolboyJack1_RequestNumber
J_TrainerSchoolboyJack1_AskAgain:
	call J_TrainerSchoolboyJack1_AskNumber2
J_TrainerSchoolboyJack1_RequestNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerSchoolboyJack1_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerSchoolboyJack1_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_SCHOOLBOY_JACK1
	call J_TrainerSchoolboyJack1_RegisteredNumber
	goto J_TrainerSchoolboyJack1_NumberAccepted
J_TrainerSchoolboyJack1_Rematch:
	call J_TrainerSchoolboyJack1_RematchStd
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 4, J_TrainerSchoolboyJack1_Fight4
	goto_if_eq VAR_RESULT, 3, J_TrainerSchoolboyJack1_Fight3
	goto_if_eq VAR_RESULT, 2, J_TrainerSchoolboyJack1_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerSchoolboyJack1_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerSchoolboyJack1_LoadFight0
J_TrainerSchoolboyJack1_Fight4:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L80
	setvar VAR_RESULT, 1
J_L80:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyJack1_LoadFight4
J_TrainerSchoolboyJack1_Fight3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L81
	setvar VAR_RESULT, 1
J_L81:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyJack1_LoadFight3
J_TrainerSchoolboyJack1_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L82
	setvar VAR_RESULT, 1
J_L82:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyJack1_LoadFight2
J_TrainerSchoolboyJack1_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_OLIVINE, J_L83
	setvar VAR_RESULT, 1
J_L83:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyJack1_LoadFight1
J_TrainerSchoolboyJack1_LoadFight0:
	trainerbattle_no_intro TRAINER_J_SCHOOLBOY_JACK1, J_SchoolboyJack1BeatenText
	clearflag FLAG_J_ENGINE_JACK_READY_FOR_REMATCH
	return
J_TrainerSchoolboyJack1_LoadFight1:
	trainerbattle_no_intro TRAINER_J_SCHOOLBOY_JACK2, J_Text_Empty
	clearflag FLAG_J_ENGINE_JACK_READY_FOR_REMATCH
	return
J_TrainerSchoolboyJack1_LoadFight2:
	trainerbattle_no_intro TRAINER_J_SCHOOLBOY_JACK3, J_Text_Empty
	clearflag FLAG_J_ENGINE_JACK_READY_FOR_REMATCH
	return
J_TrainerSchoolboyJack1_LoadFight3:
	trainerbattle_no_intro TRAINER_J_SCHOOLBOY_JACK4, J_Text_Empty
	clearflag FLAG_J_ENGINE_JACK_READY_FOR_REMATCH
	return
J_TrainerSchoolboyJack1_LoadFight4:
	trainerbattle_no_intro TRAINER_J_SCHOOLBOY_JACK5, J_Text_Empty
	clearflag FLAG_J_ENGINE_JACK_READY_FOR_REMATCH
	return
J_TrainerSchoolboyJack1_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerSchoolboyJack1_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerSchoolboyJack1_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerSchoolboyJack1_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerSchoolboyJack1_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerSchoolboyJack1_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerSchoolboyJack1_RematchStd:
	goto J_Std_Nop
	return
J_TrainerPokefanmWilliam::
J_TrainerPokefanmWilliam_Script:
	message J_PokefanmWilliamAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPokefanfBeverly1::
J_TrainerPokefanfBeverly1_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_BEVERLY_HAS_NUGGET, J_L84
	setvar VAR_RESULT, 1
J_L84:
	goto_if_ne VAR_RESULT, 0, J_TrainerPokefanfBeverly1_GiveNugget
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerPokefanfBeverly1_NumberAccepted
	setvar VAR_0x8004, SPECIES_MARILL
	special KJH_CheckPartySpecies
	goto_if_eq VAR_RESULT, 0, J_TrainerPokefanfBeverly1_NoMarill
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEVERLY_ASKED_FOR_PHONE_NUMBER, J_L85
	setvar VAR_RESULT, 1
J_L85:
	goto_if_ne VAR_RESULT, 0, J_TrainerPokefanfBeverly1_AskAgain
	message J_PokefanBeverlyCuteMonText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_BEVERLY_ASKED_FOR_PHONE_NUMBER
	call J_TrainerPokefanfBeverly1_AskNumber1
	goto J_TrainerPokefanfBeverly1_RequestNumber
J_TrainerPokefanfBeverly1_AskAgain:
	call J_TrainerPokefanfBeverly1_AskNumber2
J_TrainerPokefanfBeverly1_RequestNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerPokefanfBeverly1_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerPokefanfBeverly1_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_POKEFANF_BEVERLY1
	call J_TrainerPokefanfBeverly1_RegisteredNumber
	goto J_TrainerPokefanfBeverly1_NumberAccepted
J_TrainerPokefanfBeverly1_GiveNugget:
	call J_TrainerPokefanfBeverly1_Gift
	giveitem ITEM_NUGGET, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerPokefanfBeverly1_NoRoom
	clearflag FLAG_J_ENGINE_BEVERLY_HAS_NUGGET
	goto J_TrainerPokefanfBeverly1_NumberAccepted
J_TrainerPokefanfBeverly1_NoRoom:
	goto J_TrainerPokefanfBeverly1_PackFull
J_TrainerPokefanfBeverly1_NoMarill:
	message J_PokefanFBeverlyMarillFriendText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPokefanfBeverly1_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerPokefanfBeverly1_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerPokefanfBeverly1_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerPokefanfBeverly1_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerPokefanfBeverly1_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerPokefanfBeverly1_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerPokefanfBeverly1_Gift:
	goto J_Std_Nop
	return
J_TrainerPokefanfBeverly1_PackFull:
	goto J_Std_Nop
	return
J_TrainerLassKrise::
J_TrainerLassKrise_Script:
	message J_LassKriseAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NationalParkRelaxationSquareSign::
	message J_NationalParkRelaxationSquareText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NationalParkBattleNoticeSign::
	message J_NationalParkBattleNoticeText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NationalParkTrainerTipsSign::
	message J_NationalParkTrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NationalParkParlyzHeal::
	finditem ITEM_PARALYZE_HEAL, 1
	return
J_NationalParkTMDig::
	finditem ITEM_TM28, 1
	return
J_NationalParkHiddenFullHeal::
	finditem ITEM_FULL_HEAL
	return
J_NationalParkLassText::
	.string "Look! Check out my\nbag!\pI printed out my\nfavorites from my\pPOKéDEX and stuck\nthem on my bag.$"
J_NationalParkPokefanFText::
	.string "This is MAIL I got\nfrom my daughter.\lIt cheers me up.$"
J_NationalParkTeacher1Text::
	.string "Pay attention,\nplease!\p…Oops, I have to\nquit thinking like\pa teacher all the\ntime.\pYou must be a\nPOKéMON trainer.\pSince you're work-\ning so hard, I\pwant you to have\nthis.$"
J_NationalParkTeacher1Text_GotQuickClaw::
	.string "Let a POKéMON hold\nthat QUICK CLAW.\pSometimes it will\nstrike first\lduring battle.$"
J_NationalParkYoungster1Text::
	.string "I'm playing with\nstickers I printed\lfrom my POKéDEX.$"
J_NationalParkYoungster2Text::
	.string "I get the other\nguy's POKéDEX\lsticker if I win.$"
J_NationalParkTeacher2Text::
	.string "I take walks in\nthe PARK, but I\pnever go into the\ngrass.\pTrainers always\nwant to battle…$"
J_NationalParkPersianText::
	.string "PERSIAN: Fufushaa!$"
J_NationalParkGameboyKidText::
	.string "I'm printing out\nmy POKéDEX.\pYou can also print\nout stuff like\pMAIL and your PC\nBOXES.$"
J_SchoolboyJack1SeenText::
	.string "The world of\nPOKéMON is deep.\pThere are still\nlots of things we\ldon't know.\pBut I know more\nthan you do!$"
J_SchoolboyJack1BeatenText::
	.string "Wha-wha-what?$"
J_SchoolboyJackTradeMonText::
	.string "There is a lot\nto learn.\pFor example…\pThere are 0 kinds\nof TMs.\pNo two POKéMON\nare quite alike.$"
J_PokefanfBeverly1SeenText::
	.string "My POKéMON are\nsimply darling.\pLet me tell you\nhow proud my\ldarlings make me.$"
J_PokefanfBeverly1BeatenText::
	.string "I can beat you in\npride, but…$"
J_PokefanBeverlyCuteMonText::
	.string "I must say, your\nPOKéMON are quite\lcute, too.$"
J_PokefanmWilliamSeenText::
	.string "We adore our POKé-\nMON, even if they\ldislike us.\pThat's what being\na FAN is about.$"
J_PokefanmWilliamBeatenText::
	.string "M-my POKéMON!$"
J_PokefanmWilliamAfterBattleText::
	.string "I lost the battle,\nbut my POKéMON win\pthe prize for\nbeing most lovely.$"
J_PokefanFBeverlyMarillFriendText::
	.string "My friend keeps a\nMARILL!\pI find them very\nendearing.\pOh, I wish for a\nMARILL of my own…$"
J_LassKriseSeenText::
	.string "Hello? Why are you\nstaring at me?\pOh, a battle?$"
J_LassKriseBeatenText::
	.string "…Hmmm…$"
J_LassKriseAfterBattleText::
	.string "I thought you were\nstaring at me\lbecause I'm cute!$"
J_NationalParkRelaxationSquareText::
	.string "RELAXATION SQUARE\nNATIONAL PARK$"
J_NationalParkBattleNoticeText::
	.string "What is this\nnotice?\pPlease battle only\nin the grass.\pNATIONAL PARK\nWARDEN'S OFFICE$"
J_NationalParkTrainerTipsText::
	.string "TRAINER TIPS\pPrint out MAIL by\nopening it then\lpressing START.$"
J_NationalPark_MapEvents::
