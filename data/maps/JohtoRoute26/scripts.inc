@ KJH: translated from pokecrystal maps/Route26.asm by kjh_tools/johto

JohtoRoute26_MapScripts::
	.byte 0

J_T_TrainerCooltrainermJake::
	trainerbattle_single TRAINER_J_COOLTRAINERM_JAKE, J_CooltrainermJakeSeenText, J_CooltrainermJakeBeatenText
	call J_TrainerCooltrainermJake_Script
	release
	end

J_T_TrainerCooltrainermGaven3::
	trainerbattle_single TRAINER_J_COOLTRAINERM_GAVEN3, J_CooltrainermGaven3SeenText, J_CooltrainermGaven3BeatenText
	call J_TrainerCooltrainermGaven3_Script
	release
	end

J_T_TrainerCooltrainerfJoyce::
	trainerbattle_single TRAINER_J_COOLTRAINERF_JOYCE, J_CooltrainerfJoyceSeenText, J_CooltrainerfJoyceBeatenText
	call J_TrainerCooltrainerfJoyce_Script
	release
	end

J_T_TrainerCooltrainerfBeth1::
	trainerbattle_single TRAINER_J_COOLTRAINERF_BETH1, J_CooltrainerfBeth1SeenText, J_CooltrainerfBeth1BeatenText
	call J_TrainerCooltrainerfBeth1_Script
	release
	end

J_T_TrainerPsychicRichard::
	trainerbattle_single TRAINER_J_PSYCHIC_T_RICHARD, J_PsychicRichardSeenText, J_PsychicRichardBeatenText
	call J_TrainerPsychicRichard_Script
	release
	end

J_T_TrainerFisherScott::
	trainerbattle_single TRAINER_J_FISHER_SCOTT, J_FisherScottSeenText, J_FisherScottBeatenText
	call J_TrainerFisherScott_Script
	release
	end

J_W_Route26FruitTree::
	lock
	call J_Route26FruitTree
	release
	end

J_S_Route26Sign::
	lockall
	call J_Route26Sign
	releaseall
	end

J_Route26_MapScripts::
J_TrainerCooltrainermJake::
J_TrainerCooltrainermJake_Script:
	message J_CooltrainermJakeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainermGaven3::
J_TrainerCooltrainermGaven3_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_GAVEN_READY_FOR_REMATCH, J_L596
	setvar VAR_RESULT, 1
J_L596:
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainermGaven3_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainermGaven3_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVEN_ASKED_FOR_PHONE_NUMBER, J_L597
	setvar VAR_RESULT, 1
J_L597:
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainermGaven3_AskedAlready
	message J_CooltrainermGavenAfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_GAVEN_ASKED_FOR_PHONE_NUMBER
	call J_TrainerCooltrainermGaven3_AskNumber1
	goto J_TrainerCooltrainermGaven3_AskForNumber
J_TrainerCooltrainermGaven3_AskedAlready:
	call J_TrainerCooltrainermGaven3_AskNumber2
J_TrainerCooltrainermGaven3_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerCooltrainermGaven3_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerCooltrainermGaven3_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_COOLTRAINERM_GAVEN3
	call J_TrainerCooltrainermGaven3_RegisteredNumber
	goto J_TrainerCooltrainermGaven3_NumberAccepted
J_TrainerCooltrainermGaven3_WantsBattle:
	call J_TrainerCooltrainermGaven3_Rematch
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 2, J_TrainerCooltrainermGaven3_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerCooltrainermGaven3_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerCooltrainermGaven3_LoadFight0
J_TrainerCooltrainermGaven3_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L598
	setvar VAR_RESULT, 1
J_L598:
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainermGaven3_LoadFight2
J_TrainerCooltrainermGaven3_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L599
	setvar VAR_RESULT, 1
J_L599:
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainermGaven3_LoadFight1
J_TrainerCooltrainermGaven3_LoadFight0:
	trainerbattle_no_intro TRAINER_J_COOLTRAINERM_GAVEN3, J_CooltrainermGaven3BeatenText
	clearflag FLAG_J_ENGINE_GAVEN_READY_FOR_REMATCH
	return
J_TrainerCooltrainermGaven3_LoadFight1:
	trainerbattle_no_intro TRAINER_J_COOLTRAINERM_GAVEN1, J_Text_Empty
	clearflag FLAG_J_ENGINE_GAVEN_READY_FOR_REMATCH
	return
J_TrainerCooltrainermGaven3_LoadFight2:
	trainerbattle_no_intro TRAINER_J_COOLTRAINERM_GAVEN2, J_Text_Empty
	clearflag FLAG_J_ENGINE_GAVEN_READY_FOR_REMATCH
	return
J_TrainerCooltrainermGaven3_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerCooltrainermGaven3_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerCooltrainermGaven3_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerCooltrainermGaven3_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerCooltrainermGaven3_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerCooltrainermGaven3_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerCooltrainermGaven3_Rematch:
	goto J_Std_Nop
	return
J_TrainerCooltrainerfJoyce::
J_TrainerCooltrainerfJoyce_Script:
	message J_CooltrainerfJoyceAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainerfBeth1::
J_TrainerCooltrainerfBeth1_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_BETH_READY_FOR_REMATCH, J_L600
	setvar VAR_RESULT, 1
J_L600:
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainerfBeth1_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainerfBeth1_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BETH_ASKED_FOR_PHONE_NUMBER, J_L601
	setvar VAR_RESULT, 1
J_L601:
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainerfBeth1_AskedAlready
	message J_CooltrainerfBethAfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_BETH_ASKED_FOR_PHONE_NUMBER
	call J_TrainerCooltrainerfBeth1_AskNumber1
	goto J_TrainerCooltrainerfBeth1_AskForNumber
J_TrainerCooltrainerfBeth1_AskedAlready:
	call J_TrainerCooltrainerfBeth1_AskNumber2
J_TrainerCooltrainerfBeth1_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerCooltrainerfBeth1_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerCooltrainerfBeth1_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_COOLTRAINERF_BETH1
	call J_TrainerCooltrainerfBeth1_RegisteredNumber
	goto J_TrainerCooltrainerfBeth1_NumberAccepted
J_TrainerCooltrainerfBeth1_WantsBattle:
	call J_TrainerCooltrainerfBeth1_Rematch
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 2, J_TrainerCooltrainerfBeth1_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerCooltrainerfBeth1_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerCooltrainerfBeth1_LoadFight0
J_TrainerCooltrainerfBeth1_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L602
	setvar VAR_RESULT, 1
J_L602:
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainerfBeth1_LoadFight2
J_TrainerCooltrainerfBeth1_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L603
	setvar VAR_RESULT, 1
J_L603:
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainerfBeth1_LoadFight1
J_TrainerCooltrainerfBeth1_LoadFight0:
	trainerbattle_no_intro TRAINER_J_COOLTRAINERF_BETH1, J_CooltrainerfBeth1BeatenText
	clearflag FLAG_J_ENGINE_BETH_READY_FOR_REMATCH
	return
J_TrainerCooltrainerfBeth1_LoadFight1:
	trainerbattle_no_intro TRAINER_J_COOLTRAINERF_BETH2, J_Text_Empty
	clearflag FLAG_J_ENGINE_BETH_READY_FOR_REMATCH
	return
J_TrainerCooltrainerfBeth1_LoadFight2:
	trainerbattle_no_intro TRAINER_J_COOLTRAINERF_BETH3, J_Text_Empty
	clearflag FLAG_J_ENGINE_BETH_READY_FOR_REMATCH
	return
J_TrainerCooltrainerfBeth1_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerCooltrainerfBeth1_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerCooltrainerfBeth1_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerCooltrainerfBeth1_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerCooltrainerfBeth1_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerCooltrainerfBeth1_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerCooltrainerfBeth1_Rematch:
	goto J_Std_Nop
	return
J_TrainerPsychicRichard::
J_TrainerPsychicRichard_Script:
	message J_PsychicRichardAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerFisherScott::
J_TrainerFisherScott_Script:
	message J_FisherScottAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route26Sign::
	message J_Route26SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route26FruitTree::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_Route26MaxElixer::
	finditem ITEM_MAX_ELIXIR, 1
	return
J_CooltrainermJakeSeenText::
	.string "I'm making my\nfinal preparations\pfor the POKéMON\nLEAGUE.$"
J_CooltrainermJakeBeatenText::
	.string "I blew it!$"
J_CooltrainermJakeAfterBattleText::
	.string "It's going to be\ntough to win at\lthe LEAGUE.\pI need to do some\nmore training.\pI hear that the\nLEAGUE's ELITE\pFOUR are tougher\nthan GYM LEADERS.$"
J_CooltrainermGaven3SeenText::
	.string "By experiencing\ntough battles, you\lgain power.$"
J_CooltrainermGaven3BeatenText::
	.string "Gaah! Life is even\ntougher!$"
J_CooltrainermGavenAfterText::
	.string "To get to POKéMON\nLEAGUE, you have\pto get through\nVICTORY ROAD.\pBut VICTORY ROAD\nis tough.\pPractically nobody\ngoes there!$"
J_CooltrainerfJoyceSeenText::
	.string "Since you've come\nthis far, you must\lbe good.\pI'm going to give\nthis battle every-\lthing I've got!$"
J_CooltrainerfJoyceBeatenText::
	.string "No! I don't\nbelieve this!$"
J_CooltrainerfJoyceAfterBattleText::
	.string "I've defeated\neight GYM LEADERS,\pso I was feeling\nconfident.\pI'll have to try\nharder next time.$"
J_CooltrainerfBeth1SeenText::
	.string "I lost to a train-\ner named {RIVAL}.\pHe was really\nstrong, but…\pIt was as if he\nabsolutely had to\lwin at any cost.\pI felt sorry for\nhis POKéMON.$"
J_CooltrainerfBeth1BeatenText::
	.string "POKéMON aren't\ntools of war.$"
J_CooltrainerfBethAfterText::
	.string "POKéMON are in-\nvaluable, lifelong\lpartners.$"
J_PsychicRichardSeenText::
	.string "Wow, look at all\nthose BADGES!\lI'm impressed.\pBut you're not\nsatisfied by just\pcollecting them,\nright?$"
J_PsychicRichardBeatenText::
	.string "Good battle!$"
J_PsychicRichardAfterBattleText::
	.string "People and POKéMON\ngrow from their\lexperiences.\pDon't get lazy and\ncomplacent.$"
J_FisherScottSeenText::
	.string "I'm feeling great\ntoday!\pI feel like I\ncould boot even\lthe LEAGUE CHAMP!$"
J_FisherScottBeatenText::
	.string "No! Not in this\nbattle!$"
J_FisherScottAfterBattleText::
	.string "Just like in fish-\ning, it's all over\pin POKéMON if you\ngive up.$"
J_Route26SignText::
	.string "ROUTE 26\pPOKéMON LEAGUE\nRECEPTION GATE$"
J_Route26_MapEvents::
