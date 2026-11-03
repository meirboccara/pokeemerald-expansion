@ KJH: translated from pokecrystal maps/Route44.asm by kjh_tools/johto

JohtoRoute44_MapScripts::
	.byte 0

J_T_TrainerFisherWilton1::
	trainerbattle_single TRAINER_J_FISHER_WILTON1, J_FisherWilton1SeenText, J_FisherWilton1BeatenText
	call J_TrainerFisherWilton1_Script
	release
	end

J_T_TrainerFisherEdgar::
	trainerbattle_single TRAINER_J_FISHER_EDGAR, J_FisherEdgarSeenText, J_FisherEdgarBeatenText
	call J_TrainerFisherEdgar_Script
	release
	end

J_T_TrainerPsychicPhil::
	trainerbattle_single TRAINER_J_PSYCHIC_T_PHIL, J_PsychicPhilSeenText, J_PsychicPhilBeatenText
	call J_TrainerPsychicPhil_Script
	release
	end

J_T_TrainerPokemaniacZach::
	trainerbattle_single TRAINER_J_POKEMANIAC_ZACH, J_PokemaniacZachSeenText, J_PokemaniacZachBeatenText
	call J_TrainerPokemaniacZach_Script
	release
	end

J_T_TrainerBirdKeeperVance1::
	trainerbattle_single TRAINER_J_BIRD_KEEPER_VANCE1, J_BirdKeeperVance1SeenText, J_BirdKeeperVance1BeatenText
	call J_TrainerBirdKeeperVance1_Script
	release
	end

J_T_TrainerCooltrainermAllen::
	trainerbattle_single TRAINER_J_COOLTRAINERM_ALLEN, J_CooltrainermAllenSeenText, J_CooltrainermAllenBeatenText
	call J_TrainerCooltrainermAllen_Script
	release
	end

J_T_TrainerCooltrainerfCybil::
	trainerbattle_single TRAINER_J_COOLTRAINERF_CYBIL, J_CooltrainerfCybilSeenText, J_CooltrainerfCybilBeatenText
	call J_TrainerCooltrainerfCybil_Script
	release
	end

J_W_Route44FruitTree::
	lock
	call J_Route44FruitTree
	release
	end

J_S_Route44Sign1::
	lockall
	call J_Route44Sign1
	releaseall
	end

J_S_Route44Sign2::
	lockall
	call J_Route44Sign2
	releaseall
	end

J_Route44_MapScripts::
J_TrainerBirdKeeperVance1::
J_TrainerBirdKeeperVance1_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_VANCE_READY_FOR_REMATCH, J_L44
	setvar VAR_RESULT, 1
J_L44:
	goto_if_ne VAR_RESULT, 0, J_TrainerBirdKeeperVance1_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_Route44NumberAcceptedM
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_VANCE_ASKED_FOR_PHONE_NUMBER, J_L45
	setvar VAR_RESULT, 1
J_L45:
	goto_if_ne VAR_RESULT, 0, J_TrainerBirdKeeperVance1_AskedAlready
	message J_BirdKeeperVanceLegendaryBirdsText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_VANCE_ASKED_FOR_PHONE_NUMBER
	call J_Route44AskNumber1M
	goto J_TrainerBirdKeeperVance1_AskForNumber
J_TrainerBirdKeeperVance1_AskedAlready:
	call J_Route44AskNumber2M
J_TrainerBirdKeeperVance1_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_Route44PhoneFullM
	goto_if_eq VAR_RESULT, 2, J_Route44NumberDeclinedM
	bufferstring STR_VAR_1, J_TrainerName_BIRD_KEEPER_VANCE1
	call J_Route44RegisteredNumberM
	goto J_Route44NumberAcceptedM
J_TrainerBirdKeeperVance1_WantsBattle:
	call J_Route44RematchM
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 2, J_TrainerBirdKeeperVance1_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerBirdKeeperVance1_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerBirdKeeperVance1_LoadFight0
J_TrainerBirdKeeperVance1_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L46
	setvar VAR_RESULT, 1
J_L46:
	goto_if_ne VAR_RESULT, 0, J_TrainerBirdKeeperVance1_LoadFight2
J_TrainerBirdKeeperVance1_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L47
	setvar VAR_RESULT, 1
J_L47:
	goto_if_ne VAR_RESULT, 0, J_TrainerBirdKeeperVance1_LoadFight1
J_TrainerBirdKeeperVance1_LoadFight0:
	trainerbattle_no_intro TRAINER_J_BIRD_KEEPER_VANCE1, J_BirdKeeperVance1BeatenText
	clearflag FLAG_J_ENGINE_VANCE_READY_FOR_REMATCH
	return
J_TrainerBirdKeeperVance1_LoadFight1:
	trainerbattle_no_intro TRAINER_J_BIRD_KEEPER_VANCE2, J_Text_Empty
	clearflag FLAG_J_ENGINE_VANCE_READY_FOR_REMATCH
	return
J_TrainerBirdKeeperVance1_LoadFight2:
	trainerbattle_no_intro TRAINER_J_BIRD_KEEPER_VANCE3, J_Text_Empty
	clearflag FLAG_J_ENGINE_VANCE_READY_FOR_REMATCH
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_VANCE_CARBOS, J_L48
	setvar VAR_RESULT, 1
J_L48:
	goto_if_ne VAR_RESULT, 0, J_TrainerBirdKeeperVance1_Carbos
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_CARBOS_FROM_VANCE, J_L49
	setvar VAR_RESULT, 1
J_L49:
	goto_if_ne VAR_RESULT, 0, J_TrainerBirdKeeperVance1_ReceivedCarbosBefore
	call J_Route44RematchGiftM
	giveitem ITEM_CARBOS, 1
	goto_if_eq VAR_RESULT, 0, J_VancePackFull
	setflag FLAG_J_GOT_CARBOS_FROM_VANCE
	goto J_Route44NumberAcceptedM
J_TrainerBirdKeeperVance1_ReceivedCarbosBefore:
	return
J_TrainerBirdKeeperVance1_Carbos:
	message J_BirdKeeperVance2BeatenText
	waitmessage
	waitbuttonpress
	giveitem ITEM_CARBOS, 1
	goto_if_eq VAR_RESULT, 0, J_VancePackFull
	clearflag FLAG_J_VANCE_CARBOS
	setflag FLAG_J_GOT_CARBOS_FROM_VANCE
	goto J_Route44NumberAcceptedM
J_Route44AskNumber1M::
	goto J_Std_Nop
	return
J_Route44AskNumber2M::
	goto J_Std_Nop
	return
J_Route44RegisteredNumberM::
	goto J_Std_Nop
	return
J_Route44NumberAcceptedM::
	goto J_Std_Nop
	return
J_Route44NumberDeclinedM::
	goto J_Std_Nop
	return
J_Route44PhoneFullM::
	goto J_Std_Nop
	return
J_Route44RematchM::
	goto J_Std_Nop
	return
J_Route44GiftM::
	goto J_Std_Nop
	return
J_Route44PackFullM::
	goto J_Std_Nop
	return
J_VancePackFull::
	setflag FLAG_J_VANCE_CARBOS
	goto J_Std_Nop
	return
J_Route44RematchGiftM::
	goto J_Std_Nop
	return
J_TrainerPsychicPhil::
J_TrainerPsychicPhil_Script:
	message J_PsychicPhilAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerFisherWilton1::
J_TrainerFisherWilton1_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_WILTON_READY_FOR_REMATCH, J_L50
	setvar VAR_RESULT, 1
J_L50:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherWilton1_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_WILTON_HAS_ITEM, J_L51
	setvar VAR_RESULT, 1
J_L51:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherWilton1_HasItem
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_Route44NumberAcceptedM
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WILTON_ASKED_FOR_PHONE_NUMBER, J_L52
	setvar VAR_RESULT, 1
J_L52:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherWilton1_AskedAlready
	message J_FisherWiltonHugePoliwagText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_WILTON_ASKED_FOR_PHONE_NUMBER
	call J_Route44AskNumber1M
	goto J_TrainerFisherWilton1_AskForNumber
J_TrainerFisherWilton1_AskedAlready:
	call J_Route44AskNumber2M
J_TrainerFisherWilton1_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_Route44PhoneFullM
	goto_if_eq VAR_RESULT, 2, J_Route44NumberDeclinedM
	bufferstring STR_VAR_1, J_TrainerName_FISHER_WILTON1
	call J_Route44RegisteredNumberM
	goto J_Route44NumberAcceptedM
J_TrainerFisherWilton1_WantsBattle:
	call J_Route44RematchM
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 2, J_TrainerFisherWilton1_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerFisherWilton1_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerFisherWilton1_LoadFight0
J_TrainerFisherWilton1_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L53
	setvar VAR_RESULT, 1
J_L53:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherWilton1_LoadFight2
J_TrainerFisherWilton1_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L54
	setvar VAR_RESULT, 1
J_L54:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherWilton1_LoadFight1
J_TrainerFisherWilton1_LoadFight0:
	trainerbattle_no_intro TRAINER_J_FISHER_WILTON1, J_FisherWilton1BeatenText
	clearflag FLAG_J_ENGINE_WILTON_READY_FOR_REMATCH
	return
J_TrainerFisherWilton1_LoadFight1:
	trainerbattle_no_intro TRAINER_J_FISHER_WILTON2, J_Text_Empty
	clearflag FLAG_J_ENGINE_WILTON_READY_FOR_REMATCH
	return
J_TrainerFisherWilton1_LoadFight2:
	trainerbattle_no_intro TRAINER_J_FISHER_WILTON3, J_Text_Empty
	clearflag FLAG_J_ENGINE_WILTON_READY_FOR_REMATCH
	return
J_TrainerFisherWilton1_HasItem:
	call J_Route44GiftM
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WILTON_HAS_ULTRA_BALL, J_L55
	setvar VAR_RESULT, 1
J_L55:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherWilton1_UltraBall
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WILTON_HAS_GREAT_BALL, J_L56
	setvar VAR_RESULT, 1
J_L56:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherWilton1_GreatBall
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WILTON_HAS_POKE_BALL, J_L57
	setvar VAR_RESULT, 1
J_L57:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherWilton1_PokeBall
J_TrainerFisherWilton1_UltraBall:
	giveitem ITEM_ULTRA_BALL, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerFisherWilton1_Route44PackFullM
	goto J_TrainerFisherWilton1_ItemReceived
J_TrainerFisherWilton1_GreatBall:
	giveitem ITEM_GREAT_BALL, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerFisherWilton1_Route44PackFullM
	goto J_TrainerFisherWilton1_ItemReceived
J_TrainerFisherWilton1_PokeBall:
	giveitem ITEM_POKE_BALL, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerFisherWilton1_Route44PackFullM
J_TrainerFisherWilton1_ItemReceived:
	clearflag FLAG_J_ENGINE_WILTON_HAS_ITEM
	goto J_Route44NumberAcceptedM
J_TrainerFisherWilton1_Route44PackFullM:
	goto J_Route44PackFullM
J_TrainerFisherEdgar::
J_TrainerFisherEdgar_Script:
	message J_FisherEdgarAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainerfCybil::
J_TrainerCooltrainerfCybil_Script:
	message J_CooltrainerfCybilAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPokemaniacZach::
J_TrainerPokemaniacZach_Script:
	message J_PokemaniacZachAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainermAllen::
J_TrainerCooltrainermAllen_Script:
	message J_CooltrainermAllenAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route44Sign1::
	message J_Route44Sign1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route44Sign2::
	message J_Route44Sign2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route44FruitTree::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_Route44MaxRevive::
	finditem ITEM_MAX_REVIVE, 1
	return
J_Route44UltraBall::
	finditem ITEM_ULTRA_BALL, 1
	return
J_Route44MaxRepel::
	finditem ITEM_MAX_REPEL, 1
	return
J_Route44HiddenElixer::
	finditem ITEM_ELIXIR
	return
J_FisherWilton1SeenText::
	.string "Aack! You made me\nlose a POLIWAG!\pWhat are you going\nto do about it?$"
J_FisherWilton1BeatenText::
	.string "Just forget about\nit.$"
J_FisherWiltonHugePoliwagText::
	.string "That POLIWAG that\ngot away…\lIt was huge.\pI swear it must've\nbeen 16 feet long!$"
J_FisherEdgarSeenText::
	.string "I fish until I\ncan't anymore.\pI also battle\nuntil I drop.\pThat's my\nrelationship\lwith my POKéMON.$"
J_FisherEdgarBeatenText::
	.string "Hmmmm… \nThis isn't right.$"
J_FisherEdgarAfterBattleText::
	.string "That's 100 wins\nto 101 losses.\pI won't battle\nagain for a while.$"
J_BirdKeeperVance1SeenText::
	.string "Do you know about\nthe legendary bird\lPOKéMON?$"
J_BirdKeeperVance1BeatenText::
	.string "Whew! You're hot\nstuff.$"
J_BirdKeeperVanceLegendaryBirdsText::
	.string "ARTICUNO, ZAPDOS\nand MOLTRES are\pthe three legend-\nary bird POKéMON.\pI heard there are\nother legendary\lbirds, though.$"
J_BirdKeeperVance2BeatenText::
	.string "Why can't I ever\nbeat you?\pOh yeah, here you\ngo. It's that gift\pI couldn't give\nyou last time.$"
J_PsychicPhilSeenText::
	.string "I'm gonna win,\nfor sure!$"
J_PsychicPhilBeatenText::
	.string "Arrgh… That's a\nshocking loss…$"
J_PsychicPhilAfterBattleText::
	.string "It's important to\nhave conviction\lon your side.$"
J_PokemaniacZachSeenText::
	.string "I'll do anything\nto get my hands on\lrare POKéMON!$"
J_PokemaniacZachBeatenText::
	.string "Oooh, your POKéMON\nare so appealing.$"
J_PokemaniacZachAfterBattleText::
	.string "If a POKéMON has\ndifferent colors\pfrom usual, it's\nmore valuable.\pWhat? You mean\nthat's not true?$"
J_CooltrainermAllenSeenText::
	.string "I can tell you're\na good trainer by\llooking at you.\pI'm good at POKé-\nMON, and I can see\lthat you are too.$"
J_CooltrainermAllenBeatenText::
	.string "Tch! It's a total\nloss on my part.$"
J_CooltrainermAllenAfterBattleText::
	.string "Wow. You have a\nlot of BADGES.\pNo wonder you're\nso tough.\pI wonder if\nECRUTEAK GYM's\pMORTY is still in\ntraining?\pHe really hammered\nme.$"
J_CooltrainerfCybilSeenText::
	.string "You look strong.\pGood trainers seek\ntough opponents\linstinctively.$"
J_CooltrainerfCybilBeatenText::
	.string "Nope! This won't\ndo at all.$"
J_CooltrainerfCybilAfterBattleText::
	.string "We all get better\nby experiencing\lmany battles.\pI battled a lot to\nbecome what I am\ltoday--an elite.$"
J_Route44Sign1Text::
	.string "ROUTE 44\nICE PATH AHEAD$"
J_Route44Sign2Text::
	.string "ROUTE 44\pMAHOGANY TOWN -\nBLACKTHORN CITY$"
J_Route44_MapEvents::
