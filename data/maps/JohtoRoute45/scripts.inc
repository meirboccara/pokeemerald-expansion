@ KJH: translated from pokecrystal maps/Route45.asm by kjh_tools/johto

JohtoRoute45_MapScripts::
	.byte 0

J_T_TrainerHikerErik::
	trainerbattle_single TRAINER_J_HIKER_ERIK, J_HikerErikSeenText, J_HikerErikBeatenText
	call J_TrainerHikerErik_Script
	release
	end

J_T_TrainerHikerMichael::
	trainerbattle_single TRAINER_J_HIKER_MICHAEL, J_HikerMichaelSeenText, J_HikerMichaelBeatenText
	call J_TrainerHikerMichael_Script
	release
	end

J_T_TrainerHikerParry::
	trainerbattle_single TRAINER_J_HIKER_PARRY3, J_HikerParry3SeenText, J_HikerParry3BeatenText
	call J_TrainerHikerParry_Script
	release
	end

J_T_TrainerHikerTimothy::
	trainerbattle_single TRAINER_J_HIKER_TIMOTHY, J_HikerTimothySeenText, J_HikerTimothyBeatenText
	call J_TrainerHikerTimothy_Script
	release
	end

J_T_TrainerBlackbeltKenji::
	trainerbattle_single TRAINER_J_BLACKBELT_T_KENJI3, J_BlackbeltKenji3SeenText, J_BlackbeltKenji3BeatenText
	call J_TrainerBlackbeltKenji_Script
	release
	end

J_T_TrainerCooltrainermRyan::
	trainerbattle_single TRAINER_J_COOLTRAINERM_RYAN, J_CooltrainermRyanSeenText, J_CooltrainermRyanBeatenText
	call J_TrainerCooltrainermRyan_Script
	release
	end

J_T_TrainerCooltrainerfKelly::
	trainerbattle_single TRAINER_J_COOLTRAINERF_KELLY, J_CooltrainerfKellySeenText, J_CooltrainerfKellyBeatenText
	call J_TrainerCooltrainerfKelly_Script
	release
	end

J_W_Route45FruitTree::
	lock
	call J_Route45FruitTree
	release
	end

J_W_TrainerCamperQuentin::
	lock
	call J_TrainerCamperQuentin
	release
	end

J_S_Route45Sign::
	lockall
	call J_Route45Sign
	releaseall
	end

J_Route45_MapScripts::
J_TrainerBlackbeltKenji::
J_TrainerBlackbeltKenji_Script:
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerBlackbeltKenji_Registered
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_KENJI_ASKED_FOR_PHONE_NUMBER, J_L299
	setvar VAR_RESULT, 1
J_L299:
	goto_if_ne VAR_RESULT, 0, J_TrainerBlackbeltKenji_AskedAlready
	setvar VAR_RESULT, 0
	message J_BlackbeltKenjiAfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_KENJI_ASKED_FOR_PHONE_NUMBER
	call J_Route45AskNumber1M
	goto J_TrainerBlackbeltKenji_AskForNumber
J_TrainerBlackbeltKenji_AskedAlready:
	call J_Route45AskNumber2M
J_TrainerBlackbeltKenji_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_Route45PhoneFullM
	goto_if_eq VAR_RESULT, 2, J_Route45NumberDeclinedM
	bufferstring STR_VAR_1, J_TrainerName_BLACKBELT_T_KENJI3
	call J_Route45RegisteredNumberM
	goto J_Route45NumberAcceptedM
J_TrainerBlackbeltKenji_Registered:
	setvar VAR_0x8004, 26
	special KJH_CrystalReadVar
	goto_if_ne VAR_RESULT, 1, J_Route45NumberAcceptedM
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerBlackbeltKenji_Morning
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerBlackbeltKenji_Night
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_KENJI_ON_BREAK, J_L300
	setvar VAR_RESULT, 1
J_L300:
	goto_if_eq VAR_RESULT, 0, J_Route45NumberAcceptedM
	call J_Route45GiftM
	giveitem ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerBlackbeltKenji_NoRoom
	clearflag FLAG_J_KENJI_ON_BREAK
	setvar VAR_RESULT, 0
	goto J_Route45NumberAcceptedM
J_TrainerBlackbeltKenji_Morning:
	message J_BlackbeltKenjiMorningText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBlackbeltKenji_Night:
	message J_BlackbeltKenjiNightText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBlackbeltKenji_NoRoom:
	goto J_Route45PackFullM
J_Route45AskNumber1M::
	goto J_Std_Nop
	return
J_Route45AskNumber2M::
	goto J_Std_Nop
	return
J_Route45RegisteredNumberM::
	goto J_Std_Nop
	return
J_Route45NumberAcceptedM::
	goto J_Std_Nop
	return
J_Route45NumberDeclinedM::
	goto J_Std_Nop
	return
J_Route45PhoneFullM::
	goto J_Std_Nop
	return
J_Route45RematchM::
	goto J_Std_Nop
	return
J_Route45GiftM::
	goto J_Std_Nop
	return
J_Route45PackFullM::
	goto J_Std_Nop
	return
J_HikerParryHasIron::
	setflag FLAG_J_PARRY_IRON
	goto J_Std_Nop
	return
J_Route45RematchGiftM::
	goto J_Std_Nop
	return
J_TrainerHikerErik::
J_TrainerHikerErik_Script:
	message J_HikerErikAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerHikerMichael::
J_TrainerHikerMichael_Script:
	message J_HikerMichaelAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerHikerParry::
J_TrainerHikerParry_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_PARRY_READY_FOR_REMATCH, J_L301
	setvar VAR_RESULT, 1
J_L301:
	goto_if_ne VAR_RESULT, 0, J_TrainerHikerParry_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_Route45NumberAcceptedM
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_PARRY_ASKED_FOR_PHONE_NUMBER, J_L302
	setvar VAR_RESULT, 1
J_L302:
	goto_if_ne VAR_RESULT, 0, J_TrainerHikerParry_AskedAlready
	message J_HikerParryAfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_PARRY_ASKED_FOR_PHONE_NUMBER
	call J_Route45AskNumber1M
	goto J_TrainerHikerParry_AskForNumber
J_TrainerHikerParry_AskedAlready:
	call J_Route45AskNumber2M
J_TrainerHikerParry_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_Route45PhoneFullM
	goto_if_eq VAR_RESULT, 2, J_Route45NumberDeclinedM
	bufferstring STR_VAR_1, J_TrainerName_HIKER_PARRY1
	call J_Route45RegisteredNumberM
	goto J_Route45NumberAcceptedM
J_TrainerHikerParry_WantsBattle:
	call J_Route45RematchM
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 2, J_TrainerHikerParry_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerHikerParry_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerHikerParry_LoadFight0
J_TrainerHikerParry_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L303
	setvar VAR_RESULT, 1
J_L303:
	goto_if_ne VAR_RESULT, 0, J_TrainerHikerParry_LoadFight2
J_TrainerHikerParry_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L304
	setvar VAR_RESULT, 1
J_L304:
	goto_if_ne VAR_RESULT, 0, J_TrainerHikerParry_LoadFight1
J_TrainerHikerParry_LoadFight0:
	trainerbattle_no_intro TRAINER_J_HIKER_PARRY3, J_HikerParry3BeatenText
	clearflag FLAG_J_ENGINE_PARRY_READY_FOR_REMATCH
	return
J_TrainerHikerParry_LoadFight1:
	trainerbattle_no_intro TRAINER_J_HIKER_PARRY1, J_Text_Empty
	clearflag FLAG_J_ENGINE_PARRY_READY_FOR_REMATCH
	return
J_TrainerHikerParry_LoadFight2:
	trainerbattle_no_intro TRAINER_J_HIKER_PARRY2, J_Text_Empty
	clearflag FLAG_J_ENGINE_PARRY_READY_FOR_REMATCH
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_PARRY_IRON, J_L305
	setvar VAR_RESULT, 1
J_L305:
	goto_if_ne VAR_RESULT, 0, J_TrainerHikerParry_HasIron
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_IRON_FROM_PARRY, J_L306
	setvar VAR_RESULT, 1
J_L306:
	goto_if_ne VAR_RESULT, 0, J_TrainerHikerParry_GotIron
	call J_Route45RematchGiftM
	giveitem ITEM_IRON, 1
	goto_if_eq VAR_RESULT, 0, J_HikerParryHasIron
	setflag FLAG_J_GOT_IRON_FROM_PARRY
	goto J_Route45NumberAcceptedM
J_TrainerHikerParry_GotIron:
	return
J_TrainerHikerParry_HasIron:
	message J_HikerParryGivesIronText
	waitmessage
	waitbuttonpress
	giveitem ITEM_IRON, 1
	goto_if_eq VAR_RESULT, 0, J_HikerParryHasIron
	clearflag FLAG_J_PARRY_IRON
	setflag FLAG_J_GOT_IRON_FROM_PARRY
	goto J_Route45NumberAcceptedM
J_TrainerHikerTimothy::
J_TrainerHikerTimothy_Script:
	message J_HikerTimothyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainermRyan::
J_TrainerCooltrainermRyan_Script:
	message J_CooltrainermRyanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainerfKelly::
J_TrainerCooltrainerfKelly_Script:
	message J_CooltrainerfKellyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCamperQuentin::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_CAMPER_QUENTIN, J_L307
	setvar VAR_RESULT, 1
J_L307:
	goto_if_ne VAR_RESULT, 0, J_TrainerCamperQuentin_Defeated
	message J_CamperQuentinSeenText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_J_CAMPER_QUENTIN, J_CamperQuentinBeatenText
	setflag FLAG_J_BEAT_CAMPER_QUENTIN
	closemessage
	return
J_TrainerCamperQuentin_Defeated:
	message J_CamperQuentinAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route45DummyScript::
	message J_Route45DummyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route45Sign::
	message J_Route45SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route45FruitTree::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_Route45Nugget::
	finditem ITEM_NUGGET, 1
	return
J_Route45Revive::
	finditem ITEM_REVIVE, 1
	return
J_Route45Elixer::
	finditem ITEM_ELIXIR, 1
	return
J_Route45MaxPotion::
	finditem ITEM_MAX_POTION, 1
	return
J_Route45HiddenPpUp::
	finditem ITEM_PP_UP
	return
J_HikerErikSeenText::
	.string "Be prepared for\nanything!\pLet me see if your\nPOKéMON have been\lraised properly!$"
J_HikerErikBeatenText::
	.string "Oh, I lost that!$"
J_HikerErikAfterBattleText::
	.string "I'll head back to\nBLACKTHORN's ICE\pPATH and train\nsome more.$"
J_HikerMichaelSeenText::
	.string "Yo! You're spunky!\nBut you know what?\pWhen it comes to\nsheer spunkiness,\lI'm the man!$"
J_HikerMichaelBeatenText::
	.string "My POKéMON weren't\nspunky enough!$"
J_HikerMichaelAfterBattleText::
	.string "Boy, do I love\nHP UP! Mmmm, yum!\pI keep drinking my\nPOKéMON's!\pI can't help it!$"
J_HikerParry3SeenText::
	.string "My POKéMON are\npower packed!$"
J_HikerParry3BeatenText::
	.string "Wahahah! I'm the\nbig loser!$"
J_HikerParryAfterBattleText::
	.string "I'm not much good\nat thinking, see?\pSo, I just plow\nahead with power!$"
J_HikerTimothySeenText::
	.string "Why do I climb\nmountains?\pBecause they're\nthere.\pWhy do I train\nPOKéMON?\pBecause they're\nthere!$"
J_HikerTimothyBeatenText::
	.string "Losses…\nThey're there too!$"
J_HikerTimothyAfterBattleText::
	.string "The best thing to\never happen to me\pwas discovering\nPOKéMON.$"
J_HikerParryGivesIronText::
	.string "I just can't find\na way to win!\pKeep it up!\pOh, and take this\n--it's the gift\pyou couldn't take\nwhen we last met.$"
J_BlackbeltKenji3SeenText::
	.string "I was training\nhere alone.\pBehold the fruits\nof my labor!$"
J_BlackbeltKenji3BeatenText::
	.string "Waaaargh!$"
J_BlackbeltKenjiAfterBattleText::
	.string "This calls for\nextreme measures.\pI must take to the\nhills and train in\lsolitude.$"
J_BlackbeltKenjiMorningText::
	.string "I'm going to train\na bit more before\lI break for lunch.$"
J_BlackbeltKenjiNightText::
	.string "We had plenty of\nrest at lunch, so\pnow we're all\nready to go again!\pWe're going to\ntrain again!$"
J_CooltrainermRyanSeenText::
	.string "What are your\nthoughts on rais-\ling POKéMON?$"
J_CooltrainermRyanBeatenText::
	.string "You've won my\nrespect.$"
J_CooltrainermRyanAfterBattleText::
	.string "I see you're rais-\ning your POKéMON\lwith care.\pThe bond you build\nwill save you in\ltough situations.$"
J_CooltrainerfKellySeenText::
	.string "What is your\nbattle strategy?\pIt is foolish to\nuse strong moves\lindiscriminately.$"
J_CooltrainerfKellyBeatenText::
	.string "Fine. I lost.$"
J_CooltrainerfKellyAfterBattleText::
	.string "I'm not in favor\nof overly power-\lful moves.\pI want to win, but\nI also don't want\lto harm POKéMON.$"
J_Route45DummyText::
	.string "I'm really, really\ntough!\pIs there anywhere\nI can prove how\ltough I really am?$"
J_CamperQuentinSeenText::
	.string "I'm really, really\ntough!$"
J_CamperQuentinBeatenText::
	.string "I was tough at the\nBATTLE TOWER…$"
J_CamperQuentinAfterBattleText::
	.string "Have you been to\nthe BATTLE TOWER?\pI never, ever lose\nthere, but…$"
J_Route45SignText::
	.string "ROUTE 45\nMOUNTAIN RD. AHEAD$"
J_Route45_MapEvents::
