@ KJH: translated from pokecrystal maps/Route42.asm by kjh_tools/johto

JohtoRoute42_MapScripts::
	.byte 0

J_T_TrainerFisherTully::
	trainerbattle_single TRAINER_J_FISHER_TULLY1, J_FisherTullySeenText, J_FisherTullyBeatenText
	call J_TrainerFisherTully_Script
	release
	end

J_T_TrainerHikerBenjamin::
	trainerbattle_single TRAINER_J_HIKER_BENJAMIN, J_HikerBenjaminSeenText, J_HikerBenjaminBeatenText
	call J_TrainerHikerBenjamin_Script
	release
	end

J_T_TrainerPokemaniacShane::
	trainerbattle_single TRAINER_J_POKEMANIAC_SHANE, J_PokemaniacShaneSeenText, J_PokemaniacShaneBeatenText
	call J_TrainerPokemaniacShane_Script
	release
	end

J_W_Route42FruitTree1::
	lock
	call J_Route42FruitTree1
	release
	end

J_W_Route42FruitTree2::
	lock
	call J_Route42FruitTree2
	release
	end

J_W_Route42FruitTree3::
	lock
	call J_Route42FruitTree3
	release
	end

J_C_Route42SuicuneScript::
	lockall
	call J_Route42SuicuneScript
	releaseall
	end

J_S_Route42Sign1::
	lockall
	call J_Route42Sign1
	releaseall
	end

J_S_MtMortarSign1::
	lockall
	call J_MtMortarSign1
	releaseall
	end

J_S_MtMortarSign2::
	lockall
	call J_MtMortarSign2
	releaseall
	end

J_S_Route42Sign2::
	lockall
	call J_Route42Sign2
	releaseall
	end

J_Route42_MapScripts::
J_Route42Noop1Scene::
	return
J_Route42Noop2Scene::
	return
J_Route42SuicuneScript::
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	delay 15
	playse SE_WARP_OUT
	applymovement 9, J_Route42SuicuneMovement
	waitmovement 9
	removeobject 9
	delay 10
	setvar VAR_J_SCENE_ROUTE_42, 0
	clearflag FLAG_J_SAW_SUICUNE_ON_ROUTE_36
	setvar VAR_J_SCENE_ROUTE_36, 1
	return
J_TrainerFisherTully::
J_TrainerFisherTully_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_TULLY_READY_FOR_REMATCH, J_L38
	setvar VAR_RESULT, 1
J_L38:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherTully_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_TULLY_HAS_WATER_STONE, J_L39
	setvar VAR_RESULT, 1
J_L39:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherTully_HasWaterStone
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherTully_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TULLY_ASKED_FOR_PHONE_NUMBER, J_L40
	setvar VAR_RESULT, 1
J_L40:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherTully_AskedAlready
	message J_FisherTullyAfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_TULLY_ASKED_FOR_PHONE_NUMBER
	call J_TrainerFisherTully_AskNumber1
	goto J_TrainerFisherTully_AskForNumber
J_TrainerFisherTully_AskedAlready:
	call J_TrainerFisherTully_AskNumber2
J_TrainerFisherTully_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerFisherTully_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerFisherTully_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_FISHER_TULLY1
	call J_TrainerFisherTully_RegisteredNumber
	goto J_TrainerFisherTully_NumberAccepted
J_TrainerFisherTully_WantsBattle:
	call J_TrainerFisherTully_Rematch
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 3, J_TrainerFisherTully_Fight3
	goto_if_eq VAR_RESULT, 2, J_TrainerFisherTully_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerFisherTully_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerFisherTully_LoadFight0
J_TrainerFisherTully_Fight3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L41
	setvar VAR_RESULT, 1
J_L41:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherTully_LoadFight3
J_TrainerFisherTully_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L42
	setvar VAR_RESULT, 1
J_L42:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherTully_LoadFight2
J_TrainerFisherTully_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_ROCKET_HIDEOUT, J_L43
	setvar VAR_RESULT, 1
J_L43:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherTully_LoadFight1
J_TrainerFisherTully_LoadFight0:
	trainerbattle_no_intro TRAINER_J_FISHER_TULLY1, J_FisherTullyBeatenText
	clearflag FLAG_J_ENGINE_TULLY_READY_FOR_REMATCH
	return
J_TrainerFisherTully_LoadFight1:
	trainerbattle_no_intro TRAINER_J_FISHER_TULLY2, J_Text_Empty
	clearflag FLAG_J_ENGINE_TULLY_READY_FOR_REMATCH
	return
J_TrainerFisherTully_LoadFight2:
	trainerbattle_no_intro TRAINER_J_FISHER_TULLY3, J_Text_Empty
	clearflag FLAG_J_ENGINE_TULLY_READY_FOR_REMATCH
	return
J_TrainerFisherTully_LoadFight3:
	trainerbattle_no_intro TRAINER_J_FISHER_TULLY4, J_Text_Empty
	clearflag FLAG_J_ENGINE_TULLY_READY_FOR_REMATCH
	return
J_TrainerFisherTully_HasWaterStone:
	call J_TrainerFisherTully_Gift
	giveitem ITEM_WATER_STONE, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerFisherTully_NoRoom
	clearflag FLAG_J_ENGINE_TULLY_HAS_WATER_STONE
	setflag FLAG_J_TULLY_GAVE_WATER_STONE
	goto J_TrainerFisherTully_NumberAccepted
J_TrainerFisherTully_NoRoom:
	goto J_TrainerFisherTully_PackFull
J_TrainerFisherTully_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerFisherTully_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerFisherTully_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerFisherTully_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerFisherTully_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerFisherTully_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerFisherTully_Rematch:
	goto J_Std_Nop
	return
J_TrainerFisherTully_Gift:
	goto J_Std_Nop
	return
J_TrainerFisherTully_PackFull:
	goto J_Std_Nop
	return
J_TrainerPokemaniacShane::
J_TrainerPokemaniacShane_Script:
	message J_PokemaniacShaneAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerHikerBenjamin::
J_TrainerHikerBenjamin_Script:
	message J_HikerBenjaminAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route42Sign1::
	message J_Route42Sign1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MtMortarSign1::
	message J_MtMortarSign1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MtMortarSign2::
	message J_MtMortarSign2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route42Sign2::
	message J_Route42Sign2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route42UltraBall::
	finditem ITEM_ULTRA_BALL, 1
	return
J_Route42SuperPotion::
	finditem ITEM_SUPER_POTION, 1
	return
J_Route42FruitTree1::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_Route42FruitTree2::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_Route42FruitTree3::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_Route42HiddenMaxPotion::
	finditem ITEM_MAX_POTION
	return
J_Route42SuicuneMovement::
	jump_up
	jump_up
	jump_up
	jump_right
	jump_right
	jump_right
	step_end
J_FisherTullySeenText::
	.string "Let me demonstrate\nthe power of the\lPOKéMON I caught!$"
J_FisherTullyBeatenText::
	.string "What? That's not\nright.$"
J_FisherTullyAfterBattleText::
	.string "I want to become\nthe trainer CHAMP\pusing the POKéMON\nI caught.\pThat's the best\npart of fishing!$"
J_HikerBenjaminSeenText::
	.string "Ah, it's good to\nbe outside!\lI feel so free!$"
J_HikerBenjaminBeatenText::
	.string "Gahahah!$"
J_HikerBenjaminAfterBattleText::
	.string "Losing feels in-\nsignificant if you\plook up at the big\nsky!$"
J_PokemaniacShaneSeenText::
	.string "HEY!\pThis is my secret\nplace! Get lost,\lyou outsider!$"
J_PokemaniacShaneBeatenText::
	.string "I should have used\nmy MOON STONE…$"
J_PokemaniacShaneAfterBattleText::
	.string "You're working on\na POKéDEX?\pWow, you must know\nsome pretty rare\lPOKéMON!\pMay I please see\nit. Please?$"
J_Route42Sign1Text::
	.string "ROUTE 42\pECRUTEAK CITY -\nMAHOGANY TOWN$"
J_MtMortarSign1Text::
	.string "MT.MORTAR\pWATERFALL CAVE\nINSIDE$"
J_MtMortarSign2Text::
	.string "MT.MORTAR\pWATERFALL CAVE\nINSIDE$"
J_Route42Sign2Text::
	.string "ROUTE 42\pECRUTEAK CITY -\nMAHOGANY TOWN$"
J_Route42_MapEvents::
