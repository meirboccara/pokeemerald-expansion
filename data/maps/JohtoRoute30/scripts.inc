@ KJH: translated from pokecrystal maps/Route30.asm by kjh_tools/johto

JohtoRoute30_MapScripts::
	.byte 0

J_W_YoungsterJoey_ImportantBattleScript::
	lock
	call J_YoungsterJoey_ImportantBattleScript
	release
	end

J_T_TrainerYoungsterJoey::
	trainerbattle_single TRAINER_J_YOUNGSTER_JOEY1, J_YoungsterJoey1SeenText, J_YoungsterJoey1BeatenText
	call J_TrainerYoungsterJoey_Script
	release
	end

J_T_TrainerYoungsterMikey::
	trainerbattle_single TRAINER_J_YOUNGSTER_MIKEY, J_YoungsterMikeySeenText, J_YoungsterMikeyBeatenText
	call J_TrainerYoungsterMikey_Script
	release
	end

J_T_TrainerBugCatcherDon::
	trainerbattle_single TRAINER_J_BUG_CATCHER_DON, J_BugCatcherDonSeenText, J_BugCatcherDonBeatenText
	call J_TrainerBugCatcherDon_Script
	release
	end

J_W_Route30YoungsterScript::
	lock
	call J_Route30YoungsterScript
	release
	end

J_W_Route30FruitTree1::
	lock
	call J_Route30FruitTree1
	release
	end

J_W_Route30FruitTree2::
	lock
	call J_Route30FruitTree2
	release
	end

J_W_Route30CooltrainerFScript::
	lock
	call J_Route30CooltrainerFScript
	release
	end

J_S_Route30Sign::
	lockall
	call J_Route30Sign
	releaseall
	end

J_S_MrPokemonsHouseDirectionsSign::
	lockall
	call J_MrPokemonsHouseDirectionsSign
	releaseall
	end

J_S_MrPokemonsHouseSign::
	lockall
	call J_MrPokemonsHouseSign
	releaseall
	end

J_S_Route30TrainerTips::
	lockall
	call J_Route30TrainerTips
	releaseall
	end

J_Route30_MapScripts::
J_YoungsterJoey_ImportantBattleScript::
	waitse
	playbgm MUS_RG_VS_TRAINER, FALSE
	message J_Text_UseTackle
	waitmessage
	delay 30
	closemessage
	playse SE_M_COMET_PUNCH
	applymovement 7, J_Route30_JoeysRattataAttacksMovement
	waitmovement 7
	faceplayer
	message J_Text_ThisIsABigBattle
	waitmessage
	waitbuttonpress
	turnobject 1, DIR_NORTH
	closemessage
	playse SE_M_COMET_PUNCH
	applymovement 6, J_Route30_MikeysRattataAttacksMovement
	waitmovement 6
	fadedefaultbgm
	return
J_TrainerYoungsterJoey::
J_TrainerYoungsterJoey_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_JOEY_READY_FOR_REMATCH, J_L658
	setvar VAR_RESULT, 1
J_L658:
	goto_if_ne VAR_RESULT, 0, J_TrainerYoungsterJoey_Rematch
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerYoungsterJoey_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_JOEY_ASKED_FOR_PHONE_NUMBER, J_L659
	setvar VAR_RESULT, 1
J_L659:
	goto_if_ne VAR_RESULT, 0, J_TrainerYoungsterJoey_AskAgain
	message J_YoungsterJoey1AfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_JOEY_ASKED_FOR_PHONE_NUMBER
	call J_TrainerYoungsterJoey_AskNumber1
	goto J_TrainerYoungsterJoey_RequestNumber
J_TrainerYoungsterJoey_AskAgain:
	call J_TrainerYoungsterJoey_AskNumber2
J_TrainerYoungsterJoey_RequestNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerYoungsterJoey_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerYoungsterJoey_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_YOUNGSTER_JOEY1
	call J_TrainerYoungsterJoey_RegisteredNumber
	goto J_TrainerYoungsterJoey_NumberAccepted
J_TrainerYoungsterJoey_Rematch:
	call J_TrainerYoungsterJoey_RematchStd
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 4, J_TrainerYoungsterJoey_Fight4
	goto_if_eq VAR_RESULT, 3, J_TrainerYoungsterJoey_Fight3
	goto_if_eq VAR_RESULT, 2, J_TrainerYoungsterJoey_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerYoungsterJoey_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerYoungsterJoey_LoadFight0
J_TrainerYoungsterJoey_Fight4:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L660
	setvar VAR_RESULT, 1
J_L660:
	goto_if_ne VAR_RESULT, 0, J_TrainerYoungsterJoey_LoadFight4
J_TrainerYoungsterJoey_Fight3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L661
	setvar VAR_RESULT, 1
J_L661:
	goto_if_ne VAR_RESULT, 0, J_TrainerYoungsterJoey_LoadFight3
J_TrainerYoungsterJoey_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_OLIVINE, J_L662
	setvar VAR_RESULT, 1
J_L662:
	goto_if_ne VAR_RESULT, 0, J_TrainerYoungsterJoey_LoadFight2
J_TrainerYoungsterJoey_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_GOLDENROD, J_L663
	setvar VAR_RESULT, 1
J_L663:
	goto_if_ne VAR_RESULT, 0, J_TrainerYoungsterJoey_LoadFight1
J_TrainerYoungsterJoey_LoadFight0:
	trainerbattle_no_intro TRAINER_J_YOUNGSTER_JOEY1, J_YoungsterJoey1BeatenText
	clearflag FLAG_J_ENGINE_JOEY_READY_FOR_REMATCH
	return
J_TrainerYoungsterJoey_LoadFight1:
	trainerbattle_no_intro TRAINER_J_YOUNGSTER_JOEY2, J_Text_Empty
	clearflag FLAG_J_ENGINE_JOEY_READY_FOR_REMATCH
	return
J_TrainerYoungsterJoey_LoadFight2:
	trainerbattle_no_intro TRAINER_J_YOUNGSTER_JOEY3, J_Text_Empty
	clearflag FLAG_J_ENGINE_JOEY_READY_FOR_REMATCH
	return
J_TrainerYoungsterJoey_LoadFight3:
	trainerbattle_no_intro TRAINER_J_YOUNGSTER_JOEY4, J_Text_Empty
	clearflag FLAG_J_ENGINE_JOEY_READY_FOR_REMATCH
	return
J_TrainerYoungsterJoey_LoadFight4:
	trainerbattle_no_intro TRAINER_J_YOUNGSTER_JOEY5, J_Text_Empty
	clearflag FLAG_J_ENGINE_JOEY_READY_FOR_REMATCH
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_JOEY_HP_UP, J_L664
	setvar VAR_RESULT, 1
J_L664:
	goto_if_ne VAR_RESULT, 0, J_TrainerYoungsterJoey_GiveHPUp
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_HP_UP_FROM_JOEY, J_L665
	setvar VAR_RESULT, 1
J_L665:
	goto_if_ne VAR_RESULT, 0, J_TrainerYoungsterJoey_done
	call J_TrainerYoungsterJoey_RematchGift
	giveitem ITEM_HP_UP, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerYoungsterJoey_PackFull
	setflag FLAG_J_GOT_HP_UP_FROM_JOEY
	goto J_TrainerYoungsterJoey_NumberAccepted
J_TrainerYoungsterJoey_done:
	return
J_TrainerYoungsterJoey_GiveHPUp:
	message J_YoungsterJoeyText_GiveHPUpAfterBattle
	waitmessage
	waitbuttonpress
	giveitem ITEM_HP_UP, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerYoungsterJoey_PackFull
	clearflag FLAG_J_JOEY_HP_UP
	setflag FLAG_J_GOT_HP_UP_FROM_JOEY
	goto J_TrainerYoungsterJoey_NumberAccepted
J_TrainerYoungsterJoey_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerYoungsterJoey_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerYoungsterJoey_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerYoungsterJoey_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerYoungsterJoey_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerYoungsterJoey_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerYoungsterJoey_RematchStd:
	goto J_Std_Nop
	return
J_TrainerYoungsterJoey_PackFull:
	setflag FLAG_J_JOEY_HP_UP
	goto J_Std_Nop
	return
J_TrainerYoungsterJoey_RematchGift:
	goto J_Std_Nop
	return
J_TrainerYoungsterMikey::
J_TrainerYoungsterMikey_Script:
	message J_YoungsterMikeyAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBugCatcherDon::
J_TrainerBugCatcherDon_Script:
	message J_BugCatcherDonAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route30YoungsterScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_MYSTERY_EGG_TO_ELM, J_L666
	setvar VAR_RESULT, 1
J_L666:
	goto_if_ne VAR_RESULT, 0, J_Route30YoungsterScript_CompletedEggQuest
	message J_Route30YoungsterText_DirectionsToMrPokemonsHouse
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route30YoungsterScript_CompletedEggQuest:
	message J_Route30YoungsterText_EveryoneIsBattling
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route30CooltrainerFScript::
	faceplayer
	message J_Route30CooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route30Sign::
	message J_Route30SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MrPokemonsHouseDirectionsSign::
	message J_MrPokemonsHouseDirectionsSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MrPokemonsHouseSign::
	message J_MrPokemonsHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route30TrainerTips::
	message J_Route30TrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route30Antidote::
	finditem ITEM_ANTIDOTE, 1
	return
J_Route30FruitTree1::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_Route30FruitTree2::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_Route30HiddenPotion::
	finditem ITEM_POTION
	return
J_Route30_JoeysRattataAttacksMovement::
	lock_facing_direction
	walk_fast_up
	walk_fast_down
	step_end
J_Route30_MikeysRattataAttacksMovement::
	lock_facing_direction
	walk_fast_down
	walk_fast_up
	step_end
J_Text_UseTackle::
	.string "Go, RATTATA!\pTACKLE!$"
J_Text_ThisIsABigBattle::
	.string "What? This is a\nbig battle!\lLeave me alone!$"
J_YoungsterJoey1SeenText::
	.string "I just lost, so\nI'm trying to find\lmore POKéMON.\pWait! You look\nweak! Come on,\llet's battle!$"
J_YoungsterJoey1BeatenText::
	.string "Ack! I lost again!\nDoggone it!$"
J_YoungsterJoey1AfterText::
	.string "Do I have to have\nmore POKéMON in\porder to battle\nbetter?\pNo! I'm sticking\nwith this one no\lmatter what!$"
J_YoungsterMikeySeenText::
	.string "You're a POKéMON\ntrainer, right?\pThen you have to\nbattle!$"
J_YoungsterMikeyBeatenText::
	.string "That's strange.\nI won before.$"
J_YoungsterMikeyAfterText::
	.string "Becoming a good\ntrainer is really\ltough.\pI'm going to bat-\ntle other people\lto get better.$"
J_BugCatcherDonSeenText::
	.string "Instead of a bug\nPOKéMON, I found\la trainer!$"
J_BugCatcherDonBeatenText::
	.string "Argh! You're too\nstrong!$"
J_BugCatcherDonAfterText::
	.string "I ran out of POKé\nBALLS while I was\lcatching POKéMON.\pI should've bought\nsome more…$"
J_Route30YoungsterText_DirectionsToMrPokemonsHouse::
	.string "MR.POKéMON's\nhouse? It's a bit\lfarther ahead.$"
J_Route30YoungsterText_EveryoneIsBattling::
	.string "Everyone's having\nfun battling!\lYou should too!$"
J_Route30CooltrainerFText::
	.string "I'm not a trainer.\pBut if you look\none in the eyes,\lprepare to battle.$"
J_Route30SignText::
	.string "ROUTE 30\pVIOLET CITY -\nCHERRYGROVE CITY$"
J_MrPokemonsHouseDirectionsSignText::
	.string "MR.POKéMON'S HOUSE\nSTRAIGHT AHEAD!$"
J_MrPokemonsHouseSignText::
	.string "MR.POKéMON'S HOUSE$"
J_Route30TrainerTipsText::
	.string "TRAINER TIPS\pNo stealing other\npeople's POKéMON!\pPOKé BALLS are to\nbe thrown only at\lwild POKéMON!$"
J_YoungsterJoeyText_GiveHPUpAfterBattle::
	.string "I lost again…\nGee, you're tough!\pOh yeah, I almost\nforgot that I had\lto give you this.\pUse it to get even\ntougher, OK?\pI'm going to get\ntougher too.$"
J_Route30_MapEvents::
