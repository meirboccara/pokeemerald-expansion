@ KJH: translated from pokecrystal maps/Route38.asm by kjh_tools/johto

JohtoRoute38_MapScripts::
	.byte 0

J_T_TrainerSchoolboyChad1::
	trainerbattle_single TRAINER_J_SCHOOLBOY_CHAD1, J_SchoolboyChad1SeenText, J_SchoolboyChad1BeatenText
	call J_TrainerSchoolboyChad1_Script
	release
	end

J_T_TrainerLassDana1::
	trainerbattle_single TRAINER_J_LASS_DANA1, J_LassDana1SeenText, J_LassDana1BeatenText
	call J_TrainerLassDana1_Script
	release
	end

J_T_TrainerBirdKeeperToby::
	trainerbattle_single TRAINER_J_BIRD_KEEPER_TOBY, J_BirdKeeperTobySeenText, J_BirdKeeperTobyBeatenText
	call J_TrainerBirdKeeperToby_Script
	release
	end

J_T_TrainerBeautyValerie::
	trainerbattle_single TRAINER_J_BEAUTY_VALERIE, J_BeautyValerieSeenText, J_BeautyValerieBeatenText
	call J_TrainerBeautyValerie_Script
	release
	end

J_T_TrainerSailorHarry::
	trainerbattle_single TRAINER_J_SAILOR_HARRY, J_SailorHarrySeenText, J_SailorHarryBeatenText
	call J_TrainerSailorHarry_Script
	release
	end

J_W_Route38FruitTree::
	lock
	call J_Route38FruitTree
	release
	end

J_T_TrainerBeautyOlivia::
	trainerbattle_single TRAINER_J_BEAUTY_OLIVIA, J_BeautyOliviaSeenText, J_BeautyOliviaBeatenText
	call J_TrainerBeautyOlivia_Script
	release
	end

J_S_Route38Sign::
	lockall
	call J_Route38Sign
	releaseall
	end

J_S_Route38TrainerTips::
	lockall
	call J_Route38TrainerTips
	releaseall
	end

J_Route38_MapScripts::
J_TrainerBirdKeeperToby::
J_TrainerBirdKeeperToby_Script:
	message J_BirdKeeperTobyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSailorHarry::
J_TrainerSailorHarry_Script:
	message J_SailorHarryAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerLassDana1::
J_TrainerLassDana1_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_DANA_READY_FOR_REMATCH, J_L17
	setvar VAR_RESULT, 1
J_L17:
	goto_if_ne VAR_RESULT, 0, J_TrainerLassDana1_DanaRematch
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_DANA_HAS_THUNDERSTONE, J_L18
	setvar VAR_RESULT, 1
J_L18:
	goto_if_ne VAR_RESULT, 0, J_TrainerLassDana1_TryGiveThunderstone
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerLassDana1_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_DANA_ASKED_FOR_PHONE_NUMBER, J_L19
	setvar VAR_RESULT, 1
J_L19:
	goto_if_ne VAR_RESULT, 0, J_TrainerLassDana1_SecondTimeAsking
	message J_LassDanaMoomooMilkText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_DANA_ASKED_FOR_PHONE_NUMBER
	call J_TrainerLassDana1_AskNumber1F
	goto J_TrainerLassDana1_AskForPhoneNumber
J_TrainerLassDana1_SecondTimeAsking:
	call J_TrainerLassDana1_AskNumber2F
J_TrainerLassDana1_AskForPhoneNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerLassDana1_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerLassDana1_DeclinedPhoneNumber
	bufferstring STR_VAR_1, J_TrainerName_LASS_DANA1
	call J_TrainerLassDana1_RegisteredPhoneNumber
	goto J_TrainerLassDana1_NumberAccepted
J_TrainerLassDana1_DanaRematch:
	call J_TrainerLassDana1_Rematch
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 4, J_TrainerLassDana1_Fight4
	goto_if_eq VAR_RESULT, 3, J_TrainerLassDana1_Fight3
	goto_if_eq VAR_RESULT, 2, J_TrainerLassDana1_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerLassDana1_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerLassDana1_LoadFight0
J_TrainerLassDana1_Fight4:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L20
	setvar VAR_RESULT, 1
J_L20:
	goto_if_ne VAR_RESULT, 0, J_TrainerLassDana1_LoadFight4
J_TrainerLassDana1_Fight3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L21
	setvar VAR_RESULT, 1
J_L21:
	goto_if_ne VAR_RESULT, 0, J_TrainerLassDana1_LoadFight3
J_TrainerLassDana1_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L22
	setvar VAR_RESULT, 1
J_L22:
	goto_if_ne VAR_RESULT, 0, J_TrainerLassDana1_LoadFight2
J_TrainerLassDana1_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_CIANWOOD, J_L23
	setvar VAR_RESULT, 1
J_L23:
	goto_if_ne VAR_RESULT, 0, J_TrainerLassDana1_LoadFight1
J_TrainerLassDana1_LoadFight0:
	trainerbattle_no_intro TRAINER_J_LASS_DANA1, J_LassDana1BeatenText
	clearflag FLAG_J_ENGINE_DANA_READY_FOR_REMATCH
	return
J_TrainerLassDana1_LoadFight1:
	trainerbattle_no_intro TRAINER_J_LASS_DANA2, J_Text_Empty
	clearflag FLAG_J_ENGINE_DANA_READY_FOR_REMATCH
	return
J_TrainerLassDana1_LoadFight2:
	trainerbattle_no_intro TRAINER_J_LASS_DANA3, J_Text_Empty
	clearflag FLAG_J_ENGINE_DANA_READY_FOR_REMATCH
	return
J_TrainerLassDana1_LoadFight3:
	trainerbattle_no_intro TRAINER_J_LASS_DANA4, J_Text_Empty
	clearflag FLAG_J_ENGINE_DANA_READY_FOR_REMATCH
	return
J_TrainerLassDana1_LoadFight4:
	trainerbattle_no_intro TRAINER_J_LASS_DANA5, J_Text_Empty
	clearflag FLAG_J_ENGINE_DANA_READY_FOR_REMATCH
	return
J_TrainerLassDana1_TryGiveThunderstone:
	call J_TrainerLassDana1_Gift
	giveitem ITEM_THUNDER_STONE, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerLassDana1_NoRoomForThunderstone
	clearflag FLAG_J_ENGINE_DANA_HAS_THUNDERSTONE
	setflag FLAG_J_DANA_GAVE_THUNDERSTONE
	goto J_TrainerLassDana1_NumberAccepted
J_TrainerLassDana1_NoRoomForThunderstone:
	goto J_TrainerLassDana1_PackFull
J_TrainerLassDana1_AskNumber1F:
	goto J_Std_Nop
	return
J_TrainerLassDana1_AskNumber2F:
	goto J_Std_Nop
	return
J_TrainerLassDana1_RegisteredPhoneNumber:
	goto J_Std_Nop
	return
J_TrainerLassDana1_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerLassDana1_DeclinedPhoneNumber:
	goto J_Std_Nop
	return
J_TrainerLassDana1_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerLassDana1_Rematch:
	goto J_Std_Nop
	return
J_TrainerLassDana1_Gift:
	goto J_Std_Nop
	return
J_TrainerLassDana1_PackFull:
	goto J_Std_Nop
	return
J_TrainerSchoolboyChad1::
J_TrainerSchoolboyChad1_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_CHAD_READY_FOR_REMATCH, J_L24
	setvar VAR_RESULT, 1
J_L24:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyChad1_ChadRematch
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyChad1_HaveChadsNumber
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CHAD_ASKED_FOR_PHONE_NUMBER, J_L25
	setvar VAR_RESULT, 1
J_L25:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyChad1_SecondTimeAsking
	message J_SchoolboyChadSoManyTestsText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_CHAD_ASKED_FOR_PHONE_NUMBER
	call J_TrainerSchoolboyChad1_AskPhoneNumber1
	goto J_TrainerSchoolboyChad1_AskToRegisterNumber
J_TrainerSchoolboyChad1_SecondTimeAsking:
	call J_TrainerSchoolboyChad1_AskPhoneNumber2
J_TrainerSchoolboyChad1_AskToRegisterNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerSchoolboyChad1_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerSchoolboyChad1_SaidNo
	bufferstring STR_VAR_1, J_TrainerName_SCHOOLBOY_CHAD1
	call J_TrainerSchoolboyChad1_RegisteredChad
	goto J_TrainerSchoolboyChad1_HaveChadsNumber
J_TrainerSchoolboyChad1_ChadRematch:
	call J_TrainerSchoolboyChad1_Rematch
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 4, J_TrainerSchoolboyChad1_Fight4
	goto_if_eq VAR_RESULT, 3, J_TrainerSchoolboyChad1_Fight3
	goto_if_eq VAR_RESULT, 2, J_TrainerSchoolboyChad1_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerSchoolboyChad1_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerSchoolboyChad1_LoadFight0
J_TrainerSchoolboyChad1_Fight4:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L26
	setvar VAR_RESULT, 1
J_L26:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyChad1_LoadFight4
J_TrainerSchoolboyChad1_Fight3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L27
	setvar VAR_RESULT, 1
J_L27:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyChad1_LoadFight3
J_TrainerSchoolboyChad1_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L28
	setvar VAR_RESULT, 1
J_L28:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyChad1_LoadFight2
J_TrainerSchoolboyChad1_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_MAHOGANY, J_L29
	setvar VAR_RESULT, 1
J_L29:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyChad1_LoadFight1
J_TrainerSchoolboyChad1_LoadFight0:
	trainerbattle_no_intro TRAINER_J_SCHOOLBOY_CHAD1, J_SchoolboyChad1BeatenText
	clearflag FLAG_J_ENGINE_CHAD_READY_FOR_REMATCH
	return
J_TrainerSchoolboyChad1_LoadFight1:
	trainerbattle_no_intro TRAINER_J_SCHOOLBOY_CHAD2, J_Text_Empty
	clearflag FLAG_J_ENGINE_CHAD_READY_FOR_REMATCH
	return
J_TrainerSchoolboyChad1_LoadFight2:
	trainerbattle_no_intro TRAINER_J_SCHOOLBOY_CHAD3, J_Text_Empty
	clearflag FLAG_J_ENGINE_CHAD_READY_FOR_REMATCH
	return
J_TrainerSchoolboyChad1_LoadFight3:
	trainerbattle_no_intro TRAINER_J_SCHOOLBOY_CHAD4, J_Text_Empty
	clearflag FLAG_J_ENGINE_CHAD_READY_FOR_REMATCH
	return
J_TrainerSchoolboyChad1_LoadFight4:
	trainerbattle_no_intro TRAINER_J_SCHOOLBOY_CHAD5, J_Text_Empty
	clearflag FLAG_J_ENGINE_CHAD_READY_FOR_REMATCH
	return
J_TrainerSchoolboyChad1_AskPhoneNumber1:
	goto J_Std_Nop
	return
J_TrainerSchoolboyChad1_AskPhoneNumber2:
	goto J_Std_Nop
	return
J_TrainerSchoolboyChad1_RegisteredChad:
	goto J_Std_Nop
	return
J_TrainerSchoolboyChad1_HaveChadsNumber:
	goto J_Std_Nop
	return
J_TrainerSchoolboyChad1_SaidNo:
	goto J_Std_Nop
	return
J_TrainerSchoolboyChad1_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerSchoolboyChad1_Rematch:
	goto J_Std_Nop
	return
J_TrainerBeautyValerie::
J_TrainerBeautyValerie_Script:
	message J_BeautyValerieAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBeautyOlivia::
J_TrainerBeautyOlivia_Script:
	message J_BeautyOliviaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route38Sign::
	message J_Route38SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route38TrainerTips::
	message J_Route38TrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route38FruitTree::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_BirdKeeperTobySeenText::
	.string "Fly high into the\nsky, my beloved\lbird POKéMON!$"
J_BirdKeeperTobyBeatenText::
	.string "I feel like just\nflying away now.$"
J_BirdKeeperTobyAfterBattleText::
	.string "I plan to train in\nCIANWOOD CITY to\pteach my POKéMON\nhow to FLY.$"
J_SchoolboyChad1SeenText::
	.string "Let me try some-\nthing I learned\ltoday.$"
J_SchoolboyChad1BeatenText::
	.string "I didn't study\nenough, I guess.$"
J_SchoolboyChadSoManyTestsText::
	.string "I have to take so\nmany tests, I\pdon't have much\ntime for POKéMON.\pSo when I do get\nto play, I really\lconcentrate.$"
J_LassDana1SeenText::
	.string "You seem to be\ngood at POKéMON.\pIf you are, how\nabout giving me\lsome advice?$"
J_LassDana1BeatenText::
	.string "I see. So you can\nbattle that way.$"
J_LassDanaMoomooMilkText::
	.string "I know something\ngood!\pMOOMOO FARM's milk\nis famous for its\lflavor.$"
J_BeautyValerieSeenText::
	.string "Hi! Aren't you a\ncute trainer!\pMay I see your\nPOKéMON?$"
J_BeautyValerieBeatenText::
	.string "I'm glad I got to\nsee your POKéMON!$"
J_BeautyValerieAfterBattleText::
	.string "When I see POKé-\nMON, it seems to\lsoothe my nerves.$"
J_SailorHarrySeenText::
	.string "I've been over-\nseas, so I know\pabout all sorts of\nPOKéMON!$"
J_SailorHarryBeatenText::
	.string "Your skill is\nworld class!$"
J_SailorHarryAfterBattleText::
	.string "All kinds of peo-\nple around the\pworld live happily\nwith POKéMON.$"
J_BeautyOliviaSeenText::
	.string "Don't you think my\nPOKéMON and I are\lbeautiful?$"
J_BeautyOliviaBeatenText::
	.string "We drink MOOMOO\nMILK every day.$"
J_BeautyOliviaAfterBattleText::
	.string "MOOMOO MILK is\ngood for beauty\pand health, but\ninconveniently,\pthey only sell a\nbottle at a time.$"
J_Route38SignText::
	.string "ROUTE 38\pOLIVINE CITY -\nECRUTEAK CITY$"
J_Route38TrainerTipsText::
	.string "TRAINER TIPS\pIf a POKéMON is\ntrying to evolve,\lyou can stop it.\pPress the B But-\nton during evolu-\ltion.\pThat startles the\nPOKéMON and stops\lits evolution.$"
J_Route38_MapEvents::
