@ KJH: translated from pokecrystal maps/Route34.asm by kjh_tools/johto

JohtoRoute34_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoRoute34_OnTransition
	.byte 0

JohtoRoute34_OnTransition:
	call J_Route34EggCheckCallback
	end

J_T_TrainerCamperTodd1::
	trainerbattle_single TRAINER_J_CAMPER_TODD1, J_CamperTodd1SeenText, J_CamperTodd1BeatenText
	call J_TrainerCamperTodd1_Script
	release
	end

J_T_TrainerYoungsterSamuel::
	trainerbattle_single TRAINER_J_YOUNGSTER_SAMUEL, J_YoungsterSamuelSeenText, J_YoungsterSamuelBeatenText
	call J_TrainerYoungsterSamuel_Script
	release
	end

J_T_TrainerYoungsterIan::
	trainerbattle_single TRAINER_J_YOUNGSTER_IAN, J_YoungsterIanSeenText, J_YoungsterIanBeatenText
	call J_TrainerYoungsterIan_Script
	release
	end

J_T_TrainerPicnickerGina1::
	trainerbattle_single TRAINER_J_PICNICKER_GINA1, J_PicnickerGina1SeenText, J_PicnickerGina1BeatenText
	call J_TrainerPicnickerGina1_Script
	release
	end

J_W_OfficerKeithScript::
	lock
	call J_OfficerKeithScript
	release
	end

J_T_TrainerPokefanmBrandon::
	trainerbattle_single TRAINER_J_POKEFANM_BRANDON, J_PokefanmBrandonSeenText, J_PokefanmBrandonBeatenText
	call J_TrainerPokefanmBrandon_Script
	release
	end

J_W_DayCareManScript_Outside::
	lock
	call J_DayCareManScript_Outside
	release
	end

J_W_DayCareMon1Script::
	lock
	call J_DayCareMon1Script
	release
	end

J_W_DayCareMon2Script::
	lock
	call J_DayCareMon2Script
	release
	end

J_T_TrainerCooltrainerfIrene::
	trainerbattle_single TRAINER_J_COOLTRAINERF_IRENE, J_CooltrainerfIreneSeenText, J_CooltrainerfIreneBeatenText
	call J_TrainerCooltrainerfIrene_Script
	release
	end

J_T_TrainerCooltrainerfJenn::
	trainerbattle_single TRAINER_J_COOLTRAINERF_JENN, J_CooltrainerfJennSeenText, J_CooltrainerfJennBeatenText
	call J_TrainerCooltrainerfJenn_Script
	release
	end

J_T_TrainerCooltrainerfKate::
	trainerbattle_single TRAINER_J_COOLTRAINERF_KATE, J_CooltrainerfKateSeenText, J_CooltrainerfKateBeatenText
	call J_TrainerCooltrainerfKate_Script
	release
	end

J_S_Route34Sign::
	lockall
	call J_Route34Sign
	releaseall
	end

J_S_Route34TrainerTips::
	lockall
	call J_Route34TrainerTips
	releaseall
	end

J_S_DayCareSign::
	lockall
	call J_DayCareSign
	releaseall
	end

J_Route34_MapScripts::
J_Route34EggCheckCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_DAY_CARE_MAN_HAS_EGG, J_L491
	setvar VAR_RESULT, 1
J_L491:
	goto_if_ne VAR_RESULT, 0, J_Route34EggCheckCallback_PutDayCareManOutside
	clearflag FLAG_J_DAY_CARE_MAN_IN_DAY_CARE
	setflag FLAG_J_DAY_CARE_MAN_ON_ROUTE_34
	goto J_Route34EggCheckCallback_CheckMon1
J_Route34EggCheckCallback_PutDayCareManOutside:
	setflag FLAG_J_DAY_CARE_MAN_IN_DAY_CARE
	clearflag FLAG_J_DAY_CARE_MAN_ON_ROUTE_34
	goto J_Route34EggCheckCallback_CheckMon1
J_Route34EggCheckCallback_CheckMon1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_DAY_CARE_MAN_HAS_MON, J_L492
	setvar VAR_RESULT, 1
J_L492:
	goto_if_eq VAR_RESULT, 0, J_Route34EggCheckCallback_HideMon1
	clearflag FLAG_J_DAY_CARE_MON_1
	goto J_Route34EggCheckCallback_CheckMon2
J_Route34EggCheckCallback_HideMon1:
	setflag FLAG_J_DAY_CARE_MON_1
	goto J_Route34EggCheckCallback_CheckMon2
J_Route34EggCheckCallback_CheckMon2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_DAY_CARE_LADY_HAS_MON, J_L493
	setvar VAR_RESULT, 1
J_L493:
	goto_if_eq VAR_RESULT, 0, J_Route34EggCheckCallback_HideMon2
	clearflag FLAG_J_DAY_CARE_MON_2
	return
J_Route34EggCheckCallback_HideMon2:
	setflag FLAG_J_DAY_CARE_MON_2
	return
J_DayCareManScript_Outside::
	faceplayer
	setvar VAR_RESULT, 0
	waitbuttonpress
	closemessage
	goto_if_eq VAR_RESULT, 1, J_DayCareManScript_Outside_end_fail
	clearflag FLAG_J_ENGINE_DAY_CARE_MAN_HAS_EGG
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 3, J_DayCareManScript_Outside_walk_around_player
	applymovement 7, J_Route34MovementData_DayCareManWalksBackInside
	waitmovement 7
	playse SE_DOOR
	removeobject 7
J_DayCareManScript_Outside_end_fail:
	return
J_DayCareManScript_Outside_walk_around_player:
	applymovement 7, J_Route34MovementData_DayCareManWalksBackInside_WalkAroundPlayer
	waitmovement 7
	playse SE_DOOR
	removeobject 7
	return
J_DayCareMon1Script::
	setvar VAR_RESULT, 0
	closemessage
	return
J_DayCareMon2Script::
	setvar VAR_RESULT, 0
	closemessage
	return
J_TrainerCamperTodd1::
J_TrainerCamperTodd1_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_TODD_READY_FOR_REMATCH, J_L494
	setvar VAR_RESULT, 1
J_L494:
	goto_if_ne VAR_RESULT, 0, J_TrainerCamperTodd1_Rematch
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_GOLDENROD_DEPT_STORE_SALE_IS_ON, J_L495
	setvar VAR_RESULT, 1
J_L495:
	goto_if_ne VAR_RESULT, 0, J_TrainerCamperTodd1_SaleIsOn
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerCamperTodd1_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TODD_ASKED_FOR_PHONE_NUMBER, J_L496
	setvar VAR_RESULT, 1
J_L496:
	goto_if_ne VAR_RESULT, 0, J_TrainerCamperTodd1_AskAgain
	message J_CamperTodd1AfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_TODD_ASKED_FOR_PHONE_NUMBER
	call J_TrainerCamperTodd1_AskNumber
	goto J_TrainerCamperTodd1_FinishAsk
J_TrainerCamperTodd1_AskAgain:
	call J_TrainerCamperTodd1_AskNumber2
J_TrainerCamperTodd1_FinishAsk:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerCamperTodd1_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerCamperTodd1_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_CAMPER_TODD1
	call J_TrainerCamperTodd1_RegisteredNumber
	goto J_TrainerCamperTodd1_NumberAccepted
J_TrainerCamperTodd1_Rematch:
	call J_TrainerCamperTodd1_RematchStd
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 4, J_TrainerCamperTodd1_Fight4
	goto_if_eq VAR_RESULT, 3, J_TrainerCamperTodd1_Fight3
	goto_if_eq VAR_RESULT, 2, J_TrainerCamperTodd1_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerCamperTodd1_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerCamperTodd1_LoadFight0
J_TrainerCamperTodd1_Fight4:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L497
	setvar VAR_RESULT, 1
J_L497:
	goto_if_ne VAR_RESULT, 0, J_TrainerCamperTodd1_LoadFight4
J_TrainerCamperTodd1_Fight3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L498
	setvar VAR_RESULT, 1
J_L498:
	goto_if_ne VAR_RESULT, 0, J_TrainerCamperTodd1_LoadFight3
J_TrainerCamperTodd1_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_BLACKTHORN, J_L499
	setvar VAR_RESULT, 1
J_L499:
	goto_if_ne VAR_RESULT, 0, J_TrainerCamperTodd1_LoadFight2
J_TrainerCamperTodd1_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_CIANWOOD, J_L500
	setvar VAR_RESULT, 1
J_L500:
	goto_if_ne VAR_RESULT, 0, J_TrainerCamperTodd1_LoadFight1
J_TrainerCamperTodd1_LoadFight0:
	trainerbattle_no_intro TRAINER_J_CAMPER_TODD1, J_CamperTodd1BeatenText
	clearflag FLAG_J_ENGINE_TODD_READY_FOR_REMATCH
	return
J_TrainerCamperTodd1_LoadFight1:
	trainerbattle_no_intro TRAINER_J_CAMPER_TODD2, J_Text_Empty
	clearflag FLAG_J_ENGINE_TODD_READY_FOR_REMATCH
	return
J_TrainerCamperTodd1_LoadFight2:
	trainerbattle_no_intro TRAINER_J_CAMPER_TODD3, J_Text_Empty
	clearflag FLAG_J_ENGINE_TODD_READY_FOR_REMATCH
	return
J_TrainerCamperTodd1_LoadFight3:
	trainerbattle_no_intro TRAINER_J_CAMPER_TODD4, J_Text_Empty
	clearflag FLAG_J_ENGINE_TODD_READY_FOR_REMATCH
	return
J_TrainerCamperTodd1_LoadFight4:
	trainerbattle_no_intro TRAINER_J_CAMPER_TODD5, J_Text_Empty
	clearflag FLAG_J_ENGINE_TODD_READY_FOR_REMATCH
	return
J_TrainerCamperTodd1_SaleIsOn:
	message J_CamperToddSaleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCamperTodd1_AskNumber:
	goto J_Std_Nop
	return
J_TrainerCamperTodd1_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerCamperTodd1_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerCamperTodd1_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerCamperTodd1_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerCamperTodd1_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerCamperTodd1_RematchStd:
	goto J_Std_Nop
	return
J_TrainerPicnickerGina1::
J_TrainerPicnickerGina1_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_GINA_READY_FOR_REMATCH, J_L501
	setvar VAR_RESULT, 1
J_L501:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerGina1_Rematch
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_GINA_HAS_LEAF_STONE, J_L502
	setvar VAR_RESULT, 1
J_L502:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerGina1_LeafStone
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerGina1_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GINA_ASKED_FOR_PHONE_NUMBER, J_L503
	setvar VAR_RESULT, 1
J_L503:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerGina1_AskAgain
	message J_PicnickerGina1AfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_GINA_ASKED_FOR_PHONE_NUMBER
	call J_TrainerPicnickerGina1_AskNumber1
	goto J_TrainerPicnickerGina1_FinishAsk
J_TrainerPicnickerGina1_AskAgain:
	call J_TrainerPicnickerGina1_AskNumber2
J_TrainerPicnickerGina1_FinishAsk:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerPicnickerGina1_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerPicnickerGina1_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_PICNICKER_GINA1
	call J_TrainerPicnickerGina1_RegisteredNumber
	goto J_TrainerPicnickerGina1_NumberAccepted
J_TrainerPicnickerGina1_Rematch:
	call J_TrainerPicnickerGina1_RematchStd
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 4, J_TrainerPicnickerGina1_Fight4
	goto_if_eq VAR_RESULT, 3, J_TrainerPicnickerGina1_Fight3
	goto_if_eq VAR_RESULT, 2, J_TrainerPicnickerGina1_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerPicnickerGina1_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerPicnickerGina1_LoadFight0
J_TrainerPicnickerGina1_Fight4:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L504
	setvar VAR_RESULT, 1
J_L504:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerGina1_LoadFight4
J_TrainerPicnickerGina1_Fight3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L505
	setvar VAR_RESULT, 1
J_L505:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerGina1_LoadFight3
J_TrainerPicnickerGina1_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L506
	setvar VAR_RESULT, 1
J_L506:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerGina1_LoadFight2
J_TrainerPicnickerGina1_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_MAHOGANY, J_L507
	setvar VAR_RESULT, 1
J_L507:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerGina1_LoadFight1
J_TrainerPicnickerGina1_LoadFight0:
	trainerbattle_no_intro TRAINER_J_PICNICKER_GINA1, J_PicnickerGina1BeatenText
	clearflag FLAG_J_ENGINE_GINA_READY_FOR_REMATCH
	return
J_TrainerPicnickerGina1_LoadFight1:
	trainerbattle_no_intro TRAINER_J_PICNICKER_GINA2, J_Text_Empty
	clearflag FLAG_J_ENGINE_GINA_READY_FOR_REMATCH
	return
J_TrainerPicnickerGina1_LoadFight2:
	trainerbattle_no_intro TRAINER_J_PICNICKER_GINA3, J_Text_Empty
	clearflag FLAG_J_ENGINE_GINA_READY_FOR_REMATCH
	return
J_TrainerPicnickerGina1_LoadFight3:
	trainerbattle_no_intro TRAINER_J_PICNICKER_GINA4, J_Text_Empty
	clearflag FLAG_J_ENGINE_GINA_READY_FOR_REMATCH
	return
J_TrainerPicnickerGina1_LoadFight4:
	trainerbattle_no_intro TRAINER_J_PICNICKER_GINA5, J_Text_Empty
	clearflag FLAG_J_ENGINE_GINA_READY_FOR_REMATCH
	return
J_TrainerPicnickerGina1_LeafStone:
	call J_TrainerPicnickerGina1_Gift
	giveitem ITEM_LEAF_STONE, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerPicnickerGina1_BagFull
	clearflag FLAG_J_ENGINE_GINA_HAS_LEAF_STONE
	setflag FLAG_J_GINA_GAVE_LEAF_STONE
	goto J_TrainerPicnickerGina1_NumberAccepted
J_TrainerPicnickerGina1_BagFull:
	goto J_TrainerPicnickerGina1_PackFull
J_TrainerPicnickerGina1_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerPicnickerGina1_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerPicnickerGina1_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerPicnickerGina1_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerPicnickerGina1_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerPicnickerGina1_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerPicnickerGina1_RematchStd:
	goto J_Std_Nop
	return
J_TrainerPicnickerGina1_Gift:
	goto J_Std_Nop
	return
J_TrainerPicnickerGina1_PackFull:
	goto J_Std_Nop
	return
J_OfficerKeithScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_OfficerKeithScript_NoFight
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_OFFICER_KEITH, J_L508
	setvar VAR_RESULT, 1
J_L508:
	goto_if_ne VAR_RESULT, 0, J_OfficerKeithScript_AfterScript
	playbgm MUS_RG_ENCOUNTER_BOY, FALSE
	message J_OfficerKeithSeenText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_J_OFFICER_KEITH, J_OfficerKeithWinText
	setflag FLAG_J_BEAT_OFFICER_KEITH
	closemessage
	return
J_OfficerKeithScript_AfterScript:
	message J_OfficerKeithAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OfficerKeithScript_NoFight:
	message J_OfficerKeithDaytimeText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerYoungsterSamuel::
J_TrainerYoungsterSamuel_Script:
	message J_YoungsterSamuelAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerYoungsterIan::
J_TrainerYoungsterIan_Script:
	message J_YoungsterIanAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPokefanmBrandon::
J_TrainerPokefanmBrandon_Script:
	message J_PokefanmBrandonAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainerfIrene::
J_TrainerCooltrainerfIrene_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_SOFT_SAND_FROM_KATE, J_L509
	setvar VAR_RESULT, 1
J_L509:
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainerfIrene_GotSoftSand
	message J_CooltrainerfIreneAfterText1
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainerfIrene_GotSoftSand:
	message J_CooltrainerfIreneAfterText2
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainerfJenn::
J_TrainerCooltrainerfJenn_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_SOFT_SAND_FROM_KATE, J_L510
	setvar VAR_RESULT, 1
J_L510:
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainerfJenn_GotSoftSand
	message J_CooltrainerfJennAfterText1
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainerfJenn_GotSoftSand:
	message J_CooltrainerfJennAfterText2
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainerfKate::
J_TrainerCooltrainerfKate_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_SOFT_SAND_FROM_KATE, J_L511
	setvar VAR_RESULT, 1
J_L511:
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainerfKate_GotSoftSand
	message J_CooltrainerfKateOfferSoftSandText
	waitmessage
	waitbuttonpress
	giveitem ITEM_SOFT_SAND, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerCooltrainerfKate_BagFull
	setflag FLAG_J_GOT_SOFT_SAND_FROM_KATE
J_TrainerCooltrainerfKate_GotSoftSand:
	message J_CooltrainerfKateAfterText
	waitmessage
	waitbuttonpress
J_TrainerCooltrainerfKate_BagFull:
	closemessage
	return
J_Route34IlexForestSign::
	message J_Route34IlexForestSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route34Sign::
	message J_Route34SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route34TrainerTips::
	message J_Route34TrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DayCareSign::
	message J_DayCareSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route34Nugget::
	finditem ITEM_NUGGET, 1
	return
J_Route34HiddenRareCandy::
	finditem ITEM_RARE_CANDY
	return
J_Route34HiddenSuperPotion::
	finditem ITEM_SUPER_POTION
	return
J_Route34MovementData_DayCareManWalksBackInside::
	walk_slow_left
	walk_slow_left
	walk_slow_up
	step_end
J_Route34MovementData_DayCareManWalksBackInside_WalkAroundPlayer::
	walk_slow_down
	walk_slow_left
	walk_slow_left
	walk_slow_up
	walk_slow_up
	step_end
J_YoungsterSamuelSeenText::
	.string "This is where I do\nmy training!$"
J_YoungsterSamuelBeatenText::
	.string "Beaten by a\npassing stranger!$"
J_YoungsterSamuelMobileText::
	.string "Have you been to\nGOLDENROD CITY?\pWeren't you amazed\nby how they've\pchanged the\nPOKéMON CENTER?$"
J_YoungsterSamuelAfterText::
	.string "I'm going to train\neven harder.\pAfter all, I'm\ntrying to become\la GYM LEADER.$"
J_YoungsterIanSeenText::
	.string "I'm the best in my\nclass at POKéMON.$"
J_YoungsterIanBeatenText::
	.string "No! There are bet-\nter trainers…$"
J_YoungsterIanAfterText::
	.string "I'm trying hard so\nI can be the star\lin my class.$"
J_CamperTodd1SeenText::
	.string "I'm confident in\nmy ability to\lraise POKéMON.\pWant to see?$"
J_CamperTodd1BeatenText::
	.string "Did I screw up my\ntraining?$"
J_CamperTodd1AfterText::
	.string "Maybe I should\ntake one to a DAY-\pCARE. Or maybe use\nsome items…$"
J_CamperToddSaleText::
	.string "Shopping under the\nsky!\pIt feels so nice\nup on a rooftop.$"
J_PicnickerGina1SeenText::
	.string "Are you a trainer?\pLet's have a\npractice battle.$"
J_PicnickerGina1BeatenText::
	.string "Oh, no! I just\ncan't win…$"
J_PicnickerGina1AfterText::
	.string "You're too strong\nto be a practice\lpartner.$"
J_OfficerKeithSeenText::
	.string "Who goes there?\nWhat are you up\lto?$"
J_OfficerKeithWinText::
	.string "You're a tough\nlittle kid.$"
J_OfficerKeithAfterText::
	.string "Yep, I see nothing\nwrong today. You\pbe good and stay\nout of trouble.$"
J_OfficerKeithDaytimeText::
	.string "I'm on patrol for\nsuspicious indi-\lviduals.$"
J_PokefanmBrandonSeenText::
	.string "I just got my\nPOKéMON back from\lDAY-CARE.\pLet's see how much\nstronger it got!$"
J_PokefanmBrandonBeatenText::
	.string "Why does it end\nthis way?$"
J_PokefanmBrandonAfterText::
	.string "My POKéMON knew\nmoves I didn't\lknow it had.\pThat confounded me\nto no end!$"
J_CooltrainerfIreneSeenText::
	.string "IRENE: Kyaaah!\nSomeone found us!$"
J_CooltrainerfIreneBeatenText::
	.string "IRENE: Ohhh!\nToo strong!$"
J_CooltrainerfIreneAfterText1::
	.string "IRENE: My sister\nKATE will get you\lfor this!$"
J_CooltrainerfIreneAfterText2::
	.string "IRENE: Isn't this\nbeach great?\pIt's our secret\nlittle getaway!$"
J_CooltrainerfJennSeenText::
	.string "JENN: You can't\nbeat IRENE and go\lunpunished!$"
J_CooltrainerfJennBeatenText::
	.string "JENN: So sorry,\nIRENE! Sis!$"
J_CooltrainerfJennAfterText1::
	.string "JENN: Don't get\ncocky! My sister\lKATE is tough!$"
J_CooltrainerfJennAfterText2::
	.string "JENN: Sunlight\nmakes your body\lstronger.$"
J_CooltrainerfKateSeenText::
	.string "KATE: You sure\nwere mean to my\llittle sisters!$"
J_CooltrainerfKateBeatenText::
	.string "KATE: No! I can't\nbelieve I lost.$"
J_CooltrainerfKateOfferSoftSandText::
	.string "KATE: You're too\nstrong. I didn't\lstand a chance.\pHere. You deserve\nthis.$"
J_CooltrainerfKateAfterText::
	.string "KATE: I'm sorry we\njumped you.\pWe never expected\nanyone to find us\phere. You sure\nstartled us.$"
J_Route34IlexForestSignText::
	.string "ILEX FOREST\nTHROUGH THE GATE$"
J_Route34SignText::
	.string "ROUTE 34\pGOLDENROD CITY -\nAZALEA TOWN\pILEX FOREST\nSOMEWHERE BETWEEN$"
J_Route34TrainerTipsText::
	.string "TRAINER TIPS\pBERRY trees grow\nnew BERRIES\levery day.\pMake a note of\nwhich trees bear\lwhich BERRIES.$"
J_DayCareSignText::
	.string "DAY-CARE\pLET US RAISE YOUR\nPOKéMON FOR YOU!$"
J_Route34_MapEvents::
