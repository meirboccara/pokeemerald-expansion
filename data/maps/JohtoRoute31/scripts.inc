@ KJH: translated from pokecrystal maps/Route31.asm by kjh_tools/johto

JohtoRoute31_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoRoute31_OnTransition
	.byte 0

JohtoRoute31_OnTransition:
	call J_Route31CheckMomCallCallback
	end

J_W_Route31MailRecipientScript::
	lock
	call J_Route31MailRecipientScript
	release
	end

J_W_Route31YoungsterScript::
	lock
	call J_Route31YoungsterScript
	release
	end

J_T_TrainerBugCatcherWade1::
	trainerbattle_single TRAINER_J_BUG_CATCHER_WADE1, J_BugCatcherWade1SeenText, J_BugCatcherWade1BeatenText
	call J_TrainerBugCatcherWade1_Script
	release
	end

J_W_Route31CooltrainerMScript::
	lock
	call J_Route31CooltrainerMScript
	release
	end

J_W_Route31FruitTree::
	lock
	call J_Route31FruitTree
	release
	end

J_S_Route31Sign::
	lockall
	call J_Route31Sign
	releaseall
	end

J_S_DarkCaveSign::
	lockall
	call J_DarkCaveSign
	releaseall
	end

J_Route31_MapScripts::
J_Route31CheckMomCallCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TALKED_TO_MOM_AFTER_MYSTERY_EGG_QUEST, J_L667
	setvar VAR_RESULT, 1
J_L667:
	goto_if_eq VAR_RESULT, 0, J_Route31CheckMomCallCallback_DoMomCall
	return
J_Route31CheckMomCallCallback_DoMomCall:
	return
J_TrainerBugCatcherWade1::
J_TrainerBugCatcherWade1_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_WADE_READY_FOR_REMATCH, J_L668
	setvar VAR_RESULT, 1
J_L668:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherWade1_WadeRematch
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_WADE_HAS_ITEM, J_L669
	setvar VAR_RESULT, 1
J_L669:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherWade1_WadeItem
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherWade1_AcceptedNumberSTD
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WADE_ASKED_FOR_PHONE_NUMBER, J_L670
	setvar VAR_RESULT, 1
J_L670:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherWade1_AskAgain
	message J_BugCatcherWade1AfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_WADE_ASKED_FOR_PHONE_NUMBER
	call J_TrainerBugCatcherWade1_AskPhoneNumberSTD
	goto J_TrainerBugCatcherWade1_Continue
J_TrainerBugCatcherWade1_AskAgain:
	call J_TrainerBugCatcherWade1_AskAgainSTD
J_TrainerBugCatcherWade1_Continue:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerBugCatcherWade1_PhoneFullSTD
	goto_if_eq VAR_RESULT, 2, J_TrainerBugCatcherWade1_DeclinedNumberSTD
	bufferstring STR_VAR_1, J_TrainerName_BUG_CATCHER_WADE1
	call J_TrainerBugCatcherWade1_RegisterNumberSTD
	goto J_TrainerBugCatcherWade1_AcceptedNumberSTD
J_TrainerBugCatcherWade1_WadeRematch:
	call J_TrainerBugCatcherWade1_RematchSTD
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 4, J_TrainerBugCatcherWade1_Fight4
	goto_if_eq VAR_RESULT, 3, J_TrainerBugCatcherWade1_Fight3
	goto_if_eq VAR_RESULT, 2, J_TrainerBugCatcherWade1_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerBugCatcherWade1_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerBugCatcherWade1_LoadFight0
J_TrainerBugCatcherWade1_Fight4:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L671
	setvar VAR_RESULT, 1
J_L671:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherWade1_LoadFight4
J_TrainerBugCatcherWade1_Fight3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L672
	setvar VAR_RESULT, 1
J_L672:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherWade1_LoadFight3
J_TrainerBugCatcherWade1_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_MAHOGANY, J_L673
	setvar VAR_RESULT, 1
J_L673:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherWade1_LoadFight2
J_TrainerBugCatcherWade1_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_GOLDENROD, J_L674
	setvar VAR_RESULT, 1
J_L674:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherWade1_LoadFight1
J_TrainerBugCatcherWade1_LoadFight0:
	trainerbattle_no_intro TRAINER_J_BUG_CATCHER_WADE1, J_BugCatcherWade1BeatenText
	clearflag FLAG_J_ENGINE_WADE_READY_FOR_REMATCH
	return
J_TrainerBugCatcherWade1_LoadFight1:
	trainerbattle_no_intro TRAINER_J_BUG_CATCHER_WADE2, J_Text_Empty
	clearflag FLAG_J_ENGINE_WADE_READY_FOR_REMATCH
	return
J_TrainerBugCatcherWade1_LoadFight2:
	trainerbattle_no_intro TRAINER_J_BUG_CATCHER_WADE3, J_Text_Empty
	clearflag FLAG_J_ENGINE_WADE_READY_FOR_REMATCH
	return
J_TrainerBugCatcherWade1_LoadFight3:
	trainerbattle_no_intro TRAINER_J_BUG_CATCHER_WADE4, J_Text_Empty
	clearflag FLAG_J_ENGINE_WADE_READY_FOR_REMATCH
	return
J_TrainerBugCatcherWade1_LoadFight4:
	trainerbattle_no_intro TRAINER_J_BUG_CATCHER_WADE5, J_Text_Empty
	clearflag FLAG_J_ENGINE_WADE_READY_FOR_REMATCH
	return
J_TrainerBugCatcherWade1_WadeItem:
	call J_TrainerBugCatcherWade1_ItemSTD
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WADE_HAS_BERRY, J_L675
	setvar VAR_RESULT, 1
J_L675:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherWade1_Berry
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WADE_HAS_PSNCUREBERRY, J_L676
	setvar VAR_RESULT, 1
J_L676:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherWade1_Psncureberry
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WADE_HAS_PRZCUREBERRY, J_L677
	setvar VAR_RESULT, 1
J_L677:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherWade1_Przcureberry
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_WADE_HAS_BITTER_BERRY, J_L678
	setvar VAR_RESULT, 1
J_L678:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherWade1_BitterBerry
J_TrainerBugCatcherWade1_Berry:
	giveitem ITEM_ORAN_BERRY, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerBugCatcherWade1_PackFull
	goto J_TrainerBugCatcherWade1_Done
J_TrainerBugCatcherWade1_Psncureberry:
	giveitem ITEM_PECHA_BERRY, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerBugCatcherWade1_PackFull
	goto J_TrainerBugCatcherWade1_Done
J_TrainerBugCatcherWade1_Przcureberry:
	giveitem ITEM_CHERI_BERRY, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerBugCatcherWade1_PackFull
	goto J_TrainerBugCatcherWade1_Done
J_TrainerBugCatcherWade1_BitterBerry:
	giveitem ITEM_PERSIM_BERRY, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerBugCatcherWade1_PackFull
J_TrainerBugCatcherWade1_Done:
	clearflag FLAG_J_ENGINE_WADE_HAS_ITEM
	goto J_TrainerBugCatcherWade1_AcceptedNumberSTD
J_TrainerBugCatcherWade1_PackFull:
	goto J_TrainerBugCatcherWade1_PackFullSTD
J_TrainerBugCatcherWade1_AskPhoneNumberSTD:
	goto J_Std_Nop
	return
J_TrainerBugCatcherWade1_AskAgainSTD:
	goto J_Std_Nop
	return
J_TrainerBugCatcherWade1_RegisterNumberSTD:
	goto J_Std_Nop
	return
J_TrainerBugCatcherWade1_AcceptedNumberSTD:
	goto J_Std_Nop
	return
J_TrainerBugCatcherWade1_DeclinedNumberSTD:
	goto J_Std_Nop
	return
J_TrainerBugCatcherWade1_PhoneFullSTD:
	goto J_Std_Nop
	return
J_TrainerBugCatcherWade1_RematchSTD:
	goto J_Std_Nop
	return
J_TrainerBugCatcherWade1_ItemSTD:
	goto J_Std_Nop
	return
J_TrainerBugCatcherWade1_PackFullSTD:
	goto J_Std_Nop
	return
J_Route31MailRecipientScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM50_NIGHTMARE, J_L679
	setvar VAR_RESULT, 1
J_L679:
	goto_if_ne VAR_RESULT, 0, J_Route31MailRecipientScript_DescribeNightmare
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_KENYA, J_L680
	setvar VAR_RESULT, 1
J_L680:
	goto_if_ne VAR_RESULT, 0, J_Route31MailRecipientScript_TryGiveKenya
	message J_Text_Route31SleepyMan
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route31MailRecipientScript_TryGiveKenya:
	message J_Text_Route31SleepyManGotMail
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_Route31MailRecipientScript_WrongMail
	goto_if_eq VAR_RESULT, 2, J_Route31MailRecipientScript_Refused
	goto_if_eq VAR_RESULT, 3, J_Route31MailRecipientScript_NoMail
	goto_if_eq VAR_RESULT, 4, J_Route31MailRecipientScript_LastMon
	message J_Text_Route31HandOverMailMon
	waitmessage
	waitbuttonpress
	message J_Text_Route31ReadingMail
	waitmessage
	waitbuttonpress
	setflag FLAG_J_GAVE_KENYA
	giveitem ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, 0, J_Route31MailRecipientScript_NoRoomForItems
	setflag FLAG_J_GOT_TM50_NIGHTMARE
J_Route31MailRecipientScript_DescribeNightmare:
	message J_Text_Route31DescribeNightmare
	waitmessage
	waitbuttonpress
J_Route31MailRecipientScript_NoRoomForItems:
	closemessage
	return
J_Route31MailRecipientScript_WrongMail:
	message J_Text_Route31WrongMail
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route31MailRecipientScript_NoMail:
	message J_Text_Route31MissingMail
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route31MailRecipientScript_Refused:
	message J_Text_Route31DeclinedToHandOverMail
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route31MailRecipientScript_LastMon:
	message J_Text_Route31CantTakeLastMon
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ReceivedSpearowMailText::
	.string "DARK CAVE leads$"
	.string "\nto another road$"
J_Route31YoungsterScript::
	faceplayer
	message J_Route31YoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route31Sign::
	message J_Route31SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DarkCaveSign::
	message J_DarkCaveSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route31CooltrainerMScript::
	faceplayer
	message J_Route31CooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route31FruitTree::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_Route31Potion::
	finditem ITEM_POTION, 1
	return
J_Route31PokeBall::
	finditem ITEM_POKE_BALL, 1
	return
J_Route31CooltrainerMText::
	.string "DARK CAVE…\pIf POKéMON could\nlight it up, I'd\lexplore it.$"
J_BugCatcherWade1SeenText::
	.string "I caught a bunch\nof POKéMON. Let me\lbattle with you!$"
J_BugCatcherWade1BeatenText::
	.string "Awwwww…$"
J_BugCatcherWade1AfterText::
	.string "You can catch\nPOKéMON even if\pyou have six with\nyou.\pIf you catch one,\nit'll go to your\lBOX automatically.$"
J_Text_Route31SleepyMan::
	.string "… Hnuurg… Huh?\pI walked too far\ntoday looking for\lPOKéMON.\pMy feet hurt and\nI'm sleepy…\pIf I were a wild\nPOKéMON, I'd be\leasy to catch…\p…Zzzz…$"
J_Text_Route31SleepyManGotMail::
	.string "…Zzzz… Huh?\pWhat's that? You\nhave MAIL for me?$"
J_Text_Route31HandOverMailMon::
	.string "{PLAYER} handed\nover the POKéMON\lholding the MAIL.$"
J_Text_Route31ReadingMail::
	.string "Let's see…\p…DARK CAVE leads\nto another road…\pThat's good to\nknow.\pThanks for bring-\ning this to me.\pMy friend's a good\nguy, and you're\lswell too!\pI'd like to do\nsomething good in\lreturn too!\pI know! I want you\nto have this!$"
J_Text_Route31DescribeNightmare::
	.string "TM50 is NIGHTMARE.\pIt's a wicked move\nthat steadily cuts\pthe HP of a sleep-\ning enemy.\pOoooh…\nThat's scary…\pI don't want to\nhave bad dreams.$"
J_Text_Route31WrongMail::
	.string "This MAIL isn't\nfor me.$"
J_Text_Route31MissingMail::
	.string "Why is this POKé-\nMON so special?\pIt doesn't have\nany MAIL.$"
J_Text_Route31DeclinedToHandOverMail::
	.string "What? You don't\nwant anything?$"
J_Text_Route31CantTakeLastMon::
	.string "If I take that\nPOKéMON from you,\pwhat are you going\nto use in battle?$"
J_Route31YoungsterText::
	.string "I found a good\nPOKéMON in DARK\lCAVE.\pI'm going to raise\nit to take on\lFALKNER.\pHe's the leader of\nVIOLET CITY's GYM.$"
J_Route31SignText::
	.string "ROUTE 31\pVIOLET CITY -\nCHERRYGROVE CITY$"
J_DarkCaveSignText::
	.string "DARK CAVE$"
J_Route31_MapEvents::
