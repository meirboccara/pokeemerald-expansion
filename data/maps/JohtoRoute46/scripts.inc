@ KJH: translated from pokecrystal maps/Route46.asm by kjh_tools/johto

JohtoRoute46_MapScripts::
	.byte 0

J_T_TrainerHikerBailey::
	trainerbattle_single TRAINER_J_HIKER_BAILEY, J_HikerBaileySeenText, J_HikerBaileyBeatenText
	call J_TrainerHikerBailey_Script
	release
	end

J_T_TrainerCamperTed::
	trainerbattle_single TRAINER_J_CAMPER_TED, J_CamperTedSeenText, J_CamperTedBeatenText
	call J_TrainerCamperTed_Script
	release
	end

J_T_TrainerPicnickerErin1::
	trainerbattle_single TRAINER_J_PICNICKER_ERIN1, J_PicnickerErin1SeenText, J_PicnickerErin1BeatenText
	call J_TrainerPicnickerErin1_Script
	release
	end

J_W_Route46FruitTree1::
	lock
	call J_Route46FruitTree1
	release
	end

J_W_Route46FruitTree2::
	lock
	call J_Route46FruitTree2
	release
	end

J_S_Route46Sign::
	lockall
	call J_Route46Sign
	releaseall
	end

J_Route46_MapScripts::
J_TrainerCamperTed::
J_TrainerCamperTed_Script:
	message J_CamperTedAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPicnickerErin1::
J_TrainerPicnickerErin1_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_ERIN_READY_FOR_REMATCH, J_L308
	setvar VAR_RESULT, 1
J_L308:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerErin1_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_Route46NumberAcceptedF
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ERIN_ASKED_FOR_PHONE_NUMBER, J_L309
	setvar VAR_RESULT, 1
J_L309:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerErin1_AskedAlready
	message J_PicnickerErinAfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_ERIN_ASKED_FOR_PHONE_NUMBER
	call J_Route46AskNumber1F
	goto J_TrainerPicnickerErin1_AskForNumber
J_TrainerPicnickerErin1_AskedAlready:
	call J_Route46AskNumber2F
J_TrainerPicnickerErin1_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_Route46PhoneFullF
	goto_if_eq VAR_RESULT, 2, J_Route46NumberDeclinedF
	bufferstring STR_VAR_1, J_TrainerName_PICNICKER_ERIN1
	call J_Route46RegisteredNumberF
	goto J_Route46NumberAcceptedF
J_TrainerPicnickerErin1_WantsBattle:
	call J_Route46RematchF
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 2, J_TrainerPicnickerErin1_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerPicnickerErin1_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerPicnickerErin1_LoadFight0
J_TrainerPicnickerErin1_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L310
	setvar VAR_RESULT, 1
J_L310:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerErin1_LoadFight2
J_TrainerPicnickerErin1_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L311
	setvar VAR_RESULT, 1
J_L311:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerErin1_LoadFight1
J_TrainerPicnickerErin1_LoadFight0:
	trainerbattle_no_intro TRAINER_J_PICNICKER_ERIN1, J_PicnickerErin1BeatenText
	clearflag FLAG_J_ENGINE_ERIN_READY_FOR_REMATCH
	return
J_TrainerPicnickerErin1_LoadFight1:
	trainerbattle_no_intro TRAINER_J_PICNICKER_ERIN2, J_Text_Empty
	clearflag FLAG_J_ENGINE_ERIN_READY_FOR_REMATCH
	return
J_TrainerPicnickerErin1_LoadFight2:
	trainerbattle_no_intro TRAINER_J_PICNICKER_ERIN3, J_Text_Empty
	clearflag FLAG_J_ENGINE_ERIN_READY_FOR_REMATCH
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ERIN_CALCIUM, J_L312
	setvar VAR_RESULT, 1
J_L312:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerErin1_HasCalcium
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_CALCIUM_FROM_ERIN, J_L313
	setvar VAR_RESULT, 1
J_L313:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerErin1_GotCalciumAlready
	call J_Route46RematchGiftF
	giveitem ITEM_CALCIUM, 1
	goto_if_eq VAR_RESULT, 0, J_ErinNoRoomForCalcium
	setflag FLAG_J_GOT_CALCIUM_FROM_ERIN
	goto J_Route46NumberAcceptedF
J_TrainerPicnickerErin1_GotCalciumAlready:
	return
J_TrainerPicnickerErin1_HasCalcium:
	message J_PicnickerErin2BeatenText
	waitmessage
	waitbuttonpress
	giveitem ITEM_CALCIUM, 1
	goto_if_eq VAR_RESULT, 0, J_ErinNoRoomForCalcium
	clearflag FLAG_J_ERIN_CALCIUM
	setflag FLAG_J_GOT_CALCIUM_FROM_ERIN
	goto J_Route46NumberAcceptedF
J_Route46AskNumber1F::
	goto J_Std_Nop
	return
J_Route46AskNumber2F::
	goto J_Std_Nop
	return
J_Route46RegisteredNumberF::
	goto J_Std_Nop
	return
J_Route46NumberAcceptedF::
	goto J_Std_Nop
	return
J_Route46NumberDeclinedF::
	goto J_Std_Nop
	return
J_Route46PhoneFullF::
	goto J_Std_Nop
	return
J_Route46RematchF::
	goto J_Std_Nop
	return
J_ErinNoRoomForCalcium::
	setflag FLAG_J_ERIN_CALCIUM
	goto J_Std_Nop
	return
J_Route46RematchGiftF::
	goto J_Std_Nop
	return
J_TrainerHikerBailey::
J_TrainerHikerBailey_Script:
	message J_HikerBaileyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route46Sign::
	message J_Route46SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route46XSpeed::
	finditem ITEM_X_SPEED, 1
	return
J_Route46FruitTree1::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_Route46FruitTree2::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_HikerBaileySeenText::
	.string "Awright! I'll show\nyou the power of\lmountain POKéMON!$"
J_HikerBaileyBeatenText::
	.string "Mercy! You showed\nme your power!$"
J_HikerBaileyAfterBattleText::
	.string "It's over. I don't\nmind. We HIKERS\lare like that.$"
J_CamperTedSeenText::
	.string "I'm raising POKé-\nMON too!\pWill you battle\nwith me?$"
J_CamperTedBeatenText::
	.string "Wha…?$"
J_CamperTedAfterBattleText::
	.string "I did my best but\ncame up short.\pNo excuses--I\nadmit I lost.$"
J_PicnickerErin1SeenText::
	.string "I raise POKéMON\ntoo!\pWill you battle\nwith me?$"
J_PicnickerErin1BeatenText::
	.string "Oh, rats!$"
J_PicnickerErinAfterBattleText::
	.string "I've been to many\nGYMS, but the GYM\pin GOLDENROD is my\nfavorite.\pIt's filled with\npretty flowers!$"
J_PicnickerErin2BeatenText::
	.string "Aww… I keep losing\nall the time!\pI'll just have to\ntry harder!\pAnyway, thanks for\nbattling me again\pand again. Here's\nthat present from\lthe other time.$"
J_Route46SignText::
	.string "ROUTE 46\nMOUNTAIN RD. AHEAD$"
J_Route46_MapEvents::
