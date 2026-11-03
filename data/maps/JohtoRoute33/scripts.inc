@ KJH: translated from pokecrystal maps/Route33.asm by kjh_tools/johto

JohtoRoute33_MapScripts::
	.byte 0

J_T_TrainerHikerAnthony::
	trainerbattle_single TRAINER_J_HIKER_ANTHONY2, J_HikerAnthony2SeenText, J_HikerAnthony2BeatenText
	call J_TrainerHikerAnthony_Script
	release
	end

J_W_Route33LassScript::
	lock
	call J_Route33LassScript
	release
	end

J_W_Route33FruitTree::
	lock
	call J_Route33FruitTree
	release
	end

J_S_Route33Sign::
	lockall
	call J_Route33Sign
	releaseall
	end

J_Route33_MapScripts::
J_Route33LassScript::
	faceplayer
	message J_Route33LassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerHikerAnthony::
J_TrainerHikerAnthony_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_ANTHONY_READY_FOR_REMATCH, J_L364
	setvar VAR_RESULT, 1
J_L364:
	goto_if_ne VAR_RESULT, 0, J_TrainerHikerAnthony_Rematch
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_DUNSPARCE_SWARM, J_L365
	setvar VAR_RESULT, 1
J_L365:
	goto_if_ne VAR_RESULT, 0, J_TrainerHikerAnthony_Swarm
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerHikerAnthony_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ANTHONY_ASKED_FOR_PHONE_NUMBER, J_L366
	setvar VAR_RESULT, 1
J_L366:
	goto_if_ne VAR_RESULT, 0, J_TrainerHikerAnthony_AskAgain
	message J_HikerAnthony2AfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_ANTHONY_ASKED_FOR_PHONE_NUMBER
	call J_TrainerHikerAnthony_AskNumber1
	goto J_TrainerHikerAnthony_AskForPhoneNumber
J_TrainerHikerAnthony_AskAgain:
	call J_TrainerHikerAnthony_AskNumber2
J_TrainerHikerAnthony_AskForPhoneNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerHikerAnthony_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerHikerAnthony_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_HIKER_ANTHONY2
	call J_TrainerHikerAnthony_RegisteredNumber
	goto J_TrainerHikerAnthony_NumberAccepted
J_TrainerHikerAnthony_Rematch:
	call J_TrainerHikerAnthony_RematchStd
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 4, J_TrainerHikerAnthony_Fight4
	goto_if_eq VAR_RESULT, 3, J_TrainerHikerAnthony_Fight3
	goto_if_eq VAR_RESULT, 2, J_TrainerHikerAnthony_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerHikerAnthony_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerHikerAnthony_LoadFight0
J_TrainerHikerAnthony_Fight4:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L367
	setvar VAR_RESULT, 1
J_L367:
	goto_if_ne VAR_RESULT, 0, J_TrainerHikerAnthony_LoadFight4
J_TrainerHikerAnthony_Fight3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L368
	setvar VAR_RESULT, 1
J_L368:
	goto_if_ne VAR_RESULT, 0, J_TrainerHikerAnthony_LoadFight3
J_TrainerHikerAnthony_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L369
	setvar VAR_RESULT, 1
J_L369:
	goto_if_ne VAR_RESULT, 0, J_TrainerHikerAnthony_LoadFight2
J_TrainerHikerAnthony_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_OLIVINE, J_L370
	setvar VAR_RESULT, 1
J_L370:
	goto_if_ne VAR_RESULT, 0, J_TrainerHikerAnthony_LoadFight1
J_TrainerHikerAnthony_LoadFight0:
	trainerbattle_no_intro TRAINER_J_HIKER_ANTHONY2, J_HikerAnthony2BeatenText
	clearflag FLAG_J_ENGINE_ANTHONY_READY_FOR_REMATCH
	return
J_TrainerHikerAnthony_LoadFight1:
	trainerbattle_no_intro TRAINER_J_HIKER_ANTHONY1, J_Text_Empty
	clearflag FLAG_J_ENGINE_ANTHONY_READY_FOR_REMATCH
	return
J_TrainerHikerAnthony_LoadFight2:
	trainerbattle_no_intro TRAINER_J_HIKER_ANTHONY3, J_Text_Empty
	clearflag FLAG_J_ENGINE_ANTHONY_READY_FOR_REMATCH
	return
J_TrainerHikerAnthony_LoadFight3:
	trainerbattle_no_intro TRAINER_J_HIKER_ANTHONY4, J_Text_Empty
	clearflag FLAG_J_ENGINE_ANTHONY_READY_FOR_REMATCH
	return
J_TrainerHikerAnthony_LoadFight4:
	trainerbattle_no_intro TRAINER_J_HIKER_ANTHONY5, J_Text_Empty
	clearflag FLAG_J_ENGINE_ANTHONY_READY_FOR_REMATCH
	return
J_TrainerHikerAnthony_Swarm:
	message J_HikerAnthonyDunsparceText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerHikerAnthony_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerHikerAnthony_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerHikerAnthony_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerHikerAnthony_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerHikerAnthony_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerHikerAnthony_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerHikerAnthony_RematchStd:
	goto J_Std_Nop
	return
J_Route33Sign::
	message J_Route33SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route33FruitTree::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_HikerAnthony2SeenText::
	.string "I came through the\ntunnel, but I\pstill have plenty\nof energy left.$"
J_HikerAnthony2BeatenText::
	.string "Whoa! You've got\nmore zip than me!$"
J_HikerAnthony2AfterText::
	.string "We HIKERS are at\nour best in the\lmountains.$"
J_HikerAnthonyDunsparceText::
	.string "Hey, did you get a\nDUNSPARCE?\pI caught one too.\pTake a look at it\nin the light. It's\lgot a funny face!$"
J_Route33LassText::
	.string "Pant, pant…\pI finally got\nthrough that cave.\pIt was much bigger\nthan I'd expected.\pI got too tired to\nexplore the whole\pthing, so I came\noutside.$"
J_Route33SignText::
	.string "ROUTE 33$"
J_Route33_MapEvents::
