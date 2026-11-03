@ KJH: translated from pokecrystal maps/GoldenrodUnderground.asm by kjh_tools/johto

JohtoGoldenrodUnderground_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoGoldenrodUnderground_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, JohtoGoldenrodUnderground_OnLoad
	.byte 0

JohtoGoldenrodUnderground_OnTransition:
	call J_GoldenrodUndergroundResetSwitchesCallback
	call J_GoldenrodUndergroundCheckDayOfWeekCallback
	end

JohtoGoldenrodUnderground_OnLoad:
	call J_GoldenrodUndergroundCheckBasementKeyCallback
	end

J_T_TrainerSupernerdEric::
	trainerbattle_single TRAINER_J_SUPER_NERD_ERIC, J_SupernerdEricSeenText, J_SupernerdEricBeatenText
	call J_TrainerSupernerdEric_Script
	release
	end

J_T_TrainerSupernerdTeru::
	trainerbattle_single TRAINER_J_SUPER_NERD_TERU, J_SupernerdTeruSeenText, J_SupernerdTeruBeatenText
	call J_TrainerSupernerdTeru_Script
	release
	end

J_T_TrainerPokemaniacIssac::
	trainerbattle_single TRAINER_J_POKEMANIAC_ISSAC, J_PokemaniacIssacSeenText, J_PokemaniacIssacBeatenText
	call J_TrainerPokemaniacIssac_Script
	release
	end

J_T_TrainerPokemaniacDonald::
	trainerbattle_single TRAINER_J_POKEMANIAC_DONALD, J_PokemaniacDonaldSeenText, J_PokemaniacDonaldBeatenText
	call J_TrainerPokemaniacDonald_Script
	release
	end

J_W_BargainMerchantScript::
	lock
	call J_BargainMerchantScript
	release
	end

J_W_OlderHaircutBrotherScript::
	lock
	call J_OlderHaircutBrotherScript
	release
	end

J_W_YoungerHaircutBrotherScript::
	lock
	call J_YoungerHaircutBrotherScript
	release
	end

J_W_BitterMerchantScript::
	lock
	call J_BitterMerchantScript
	release
	end

J_S_BasementDoorScript::
	lockall
	call J_BasementDoorScript
	releaseall
	end

J_S_GoldenrodUndergroundNoEntrySign::
	lockall
	call J_GoldenrodUndergroundNoEntrySign
	releaseall
	end

J_GoldenrodUnderground_MapScripts::
J_GoldenrodUndergroundResetSwitchesCallback::
	clearflag FLAG_J_SWITCH_1
	clearflag FLAG_J_SWITCH_2
	clearflag FLAG_J_SWITCH_3
	clearflag FLAG_J_EMERGENCY_SWITCH
	clearflag FLAG_J_DOOR_1_OPEN
	clearflag FLAG_J_DOOR_2_OPEN
	clearflag FLAG_J_DOOR_3_OPEN
	clearflag FLAG_J_DOOR_4_OPEN
	clearflag FLAG_J_DOOR_5_OPEN
	clearflag FLAG_J_DOOR_6_OPEN
	clearflag FLAG_J_DOOR_7_OPEN
	clearflag FLAG_J_DOOR_8_OPEN
	clearflag FLAG_J_DOOR_9_OPEN
	clearflag FLAG_J_DOOR_10_OPEN
	clearflag FLAG_J_DOOR_11_OPEN
	setvar VAR_RESULT, 0
	copyvar VAR_J_MEM_UNDERGROUNDSWITCHPOSITIONS, VAR_RESULT
	return
J_GoldenrodUndergroundCheckBasementKeyCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_USED_BASEMENT_KEY, J_L213
	setvar VAR_RESULT, 1
J_L213:
	goto_if_eq VAR_RESULT, 0, J_GoldenrodUndergroundCheckBasementKeyCallback_LockBasementDoor
	return
J_GoldenrodUndergroundCheckBasementKeyCallback_LockBasementDoor:
	setmetatile 18, 6, 30, TRUE
	setmetatile 19, 6, 20, TRUE
	setmetatile 18, 7, 5, FALSE
	setmetatile 19, 7, 5, FALSE
	return
J_GoldenrodUndergroundCheckDayOfWeekCallback::
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 1, J_GoldenrodUndergroundCheckDayOfWeekCallback_Monday
	goto_if_eq VAR_RESULT, 2, J_GoldenrodUndergroundCheckDayOfWeekCallback_Tuesday
	goto_if_eq VAR_RESULT, 3, J_GoldenrodUndergroundCheckDayOfWeekCallback_Wednesday
	goto_if_eq VAR_RESULT, 4, J_GoldenrodUndergroundCheckDayOfWeekCallback_Thursday
	goto_if_eq VAR_RESULT, 5, J_GoldenrodUndergroundCheckDayOfWeekCallback_Friday
	goto_if_eq VAR_RESULT, 6, J_GoldenrodUndergroundCheckDayOfWeekCallback_Saturday
	setflag FLAG_J_GOLDENROD_UNDERGROUND_GRAMPS
	setflag FLAG_J_GOLDENROD_UNDERGROUND_OLDER_HAIRCUT_BROTHER
	clearflag FLAG_J_GOLDENROD_UNDERGROUND_YOUNGER_HAIRCUT_BROTHER
	clearflag FLAG_J_GOLDENROD_UNDERGROUND_GRANNY
	return
J_GoldenrodUndergroundCheckDayOfWeekCallback_Monday:
	setflag FLAG_J_GOLDENROD_UNDERGROUND_GRAMPS
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_GoldenrodUndergroundCheckDayOfWeekCallback_NotMondayMorning
	clearflag FLAG_J_GOLDENROD_UNDERGROUND_GRAMPS
J_GoldenrodUndergroundCheckDayOfWeekCallback_NotMondayMorning:
	setflag FLAG_J_GOLDENROD_UNDERGROUND_OLDER_HAIRCUT_BROTHER
	setflag FLAG_J_GOLDENROD_UNDERGROUND_YOUNGER_HAIRCUT_BROTHER
	setflag FLAG_J_GOLDENROD_UNDERGROUND_GRANNY
	return
J_GoldenrodUndergroundCheckDayOfWeekCallback_Tuesday:
	setflag FLAG_J_GOLDENROD_UNDERGROUND_GRAMPS
	clearflag FLAG_J_GOLDENROD_UNDERGROUND_OLDER_HAIRCUT_BROTHER
	setflag FLAG_J_GOLDENROD_UNDERGROUND_YOUNGER_HAIRCUT_BROTHER
	setflag FLAG_J_GOLDENROD_UNDERGROUND_GRANNY
	return
J_GoldenrodUndergroundCheckDayOfWeekCallback_Wednesday:
	setflag FLAG_J_GOLDENROD_UNDERGROUND_GRAMPS
	setflag FLAG_J_GOLDENROD_UNDERGROUND_OLDER_HAIRCUT_BROTHER
	clearflag FLAG_J_GOLDENROD_UNDERGROUND_YOUNGER_HAIRCUT_BROTHER
	setflag FLAG_J_GOLDENROD_UNDERGROUND_GRANNY
	return
J_GoldenrodUndergroundCheckDayOfWeekCallback_Thursday:
	setflag FLAG_J_GOLDENROD_UNDERGROUND_GRAMPS
	clearflag FLAG_J_GOLDENROD_UNDERGROUND_OLDER_HAIRCUT_BROTHER
	setflag FLAG_J_GOLDENROD_UNDERGROUND_YOUNGER_HAIRCUT_BROTHER
	setflag FLAG_J_GOLDENROD_UNDERGROUND_GRANNY
	return
J_GoldenrodUndergroundCheckDayOfWeekCallback_Friday:
	setflag FLAG_J_GOLDENROD_UNDERGROUND_GRAMPS
	setflag FLAG_J_GOLDENROD_UNDERGROUND_OLDER_HAIRCUT_BROTHER
	clearflag FLAG_J_GOLDENROD_UNDERGROUND_YOUNGER_HAIRCUT_BROTHER
	setflag FLAG_J_GOLDENROD_UNDERGROUND_GRANNY
	return
J_GoldenrodUndergroundCheckDayOfWeekCallback_Saturday:
	setflag FLAG_J_GOLDENROD_UNDERGROUND_GRAMPS
	clearflag FLAG_J_GOLDENROD_UNDERGROUND_OLDER_HAIRCUT_BROTHER
	setflag FLAG_J_GOLDENROD_UNDERGROUND_YOUNGER_HAIRCUT_BROTHER
	clearflag FLAG_J_GOLDENROD_UNDERGROUND_GRANNY
	return
J_TrainerSupernerdEric::
J_TrainerSupernerdEric_Script:
	message J_SupernerdEricAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSupernerdTeru::
J_TrainerSupernerdTeru_Script:
	message J_SupernerdTeruAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPokemaniacIssac::
J_TrainerPokemaniacIssac_Script:
	message J_PokemaniacIssacAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPokemaniacDonald::
J_TrainerPokemaniacDonald_Script:
	message J_PokemaniacDonaldAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BitterMerchantScript::
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J_BitterMerchantScript_Open
	goto_if_eq VAR_RESULT, 6, J_BitterMerchantScript_Open
	goto J_GoldenrodUndergroundScript_ShopClosed
J_BitterMerchantScript_Open:
	pokemart J_Mart_MART_UNDERGROUND
	closemessage
	return
J_BargainMerchantScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_GOLDENROD_UNDERGROUND_MERCHANT_CLOSED, J_L214
	setvar VAR_RESULT, 1
J_L214:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodUndergroundScript_ShopClosed
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 1, J_BargainMerchantScript_CheckMorn
	goto J_GoldenrodUndergroundScript_ShopClosed
J_BargainMerchantScript_CheckMorn:
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_GoldenrodUndergroundScript_ShopClosed
	pokemart J_Mart_0
	closemessage
	return
J_OlderHaircutBrotherScript::
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 2, J_OlderHaircutBrotherScript_DoHaircut
	goto_if_eq VAR_RESULT, 4, J_OlderHaircutBrotherScript_DoHaircut
	goto_if_eq VAR_RESULT, 6, J_OlderHaircutBrotherScript_DoHaircut
	goto J_GoldenrodUndergroundScript_ShopClosed
J_OlderHaircutBrotherScript_DoHaircut:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_GOLDENROD_UNDERGROUND_GOT_HAIRCUT, J_L215
	setvar VAR_RESULT, 1
J_L215:
	goto_if_ne VAR_RESULT, 0, J_OlderHaircutBrotherScript_AlreadyGotHaircut
	showmoneybox 0, 0
	message J_GoldenrodUndergroundOlderHaircutBrotherOfferHaircutText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_OlderHaircutBrotherScript_Refused
	checkmoney 0
	goto_if_eq VAR_RESULT, TRUE, J_L216
	setvar VAR_RESULT, 2
	goto J_L217
J_L216:
	setvar VAR_RESULT, 0
J_L217:
	goto_if_eq VAR_RESULT, 2, J_OlderHaircutBrotherScript_NotEnoughMoney
	message J_GoldenrodUndergroundOlderHaircutBrotherAskWhichMonText
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_OlderHaircutBrotherScript_Refused
	goto_if_eq VAR_RESULT, 1, J_OlderHaircutBrotherScript_Refused
	setflag FLAG_J_ENGINE_GOLDENROD_UNDERGROUND_GOT_HAIRCUT
	goto_if_eq VAR_RESULT, 2, J_OlderHaircutBrotherScript_two
	goto_if_eq VAR_RESULT, 3, J_OlderHaircutBrotherScript_three
	goto J_OlderHaircutBrotherScript_else
J_OlderHaircutBrotherScript_two:
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1
	clearflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2
	clearflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_3
	goto J_OlderHaircutBrotherScript_then
J_OlderHaircutBrotherScript_three:
	clearflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2
	clearflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_3
	goto J_OlderHaircutBrotherScript_then
J_OlderHaircutBrotherScript_else:
	clearflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1
	clearflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_3
	goto J_OlderHaircutBrotherScript_then
J_OlderHaircutBrotherScript_then:
	removemoney 0
	showmoneybox 0, 0
	message J_GoldenrodUndergroundOlderHaircutBrotherWatchItBecomeBeautifulText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_WHITE
	playbgm MUS_RG_HEAL, FALSE
	delay 60
	fadescreen FADE_FROM_WHITE
	fadedefaultbgm
	message J_GoldenrodUndergroundOlderHaircutBrotherAllDoneText
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L218
	setvar VAR_RESULT, 1
J_L218:
	goto_if_ne VAR_RESULT, 0, J_EitherHaircutBrotherScript_SlightlyHappier
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2, J_L219
	setvar VAR_RESULT, 1
J_L219:
	goto_if_ne VAR_RESULT, 0, J_EitherHaircutBrotherScript_Happier
	goto J_EitherHaircutBrotherScript_MuchHappier
J_OlderHaircutBrotherScript_Refused:
	message J_GoldenrodUndergroundOlderHaircutBrotherThatsAShameText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlderHaircutBrotherScript_NotEnoughMoney:
	message J_GoldenrodUndergroundOlderHaircutBrotherYoullNeedMoreMoneyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlderHaircutBrotherScript_AlreadyGotHaircut:
	message J_GoldenrodUndergroundOlderHaircutBrotherOneHaircutADayText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_YoungerHaircutBrotherScript::
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J_YoungerHaircutBrotherScript_DoHaircut
	goto_if_eq VAR_RESULT, 3, J_YoungerHaircutBrotherScript_DoHaircut
	goto_if_eq VAR_RESULT, 5, J_YoungerHaircutBrotherScript_DoHaircut
	goto J_GoldenrodUndergroundScript_ShopClosed
J_YoungerHaircutBrotherScript_DoHaircut:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_GOLDENROD_UNDERGROUND_GOT_HAIRCUT, J_L220
	setvar VAR_RESULT, 1
J_L220:
	goto_if_ne VAR_RESULT, 0, J_YoungerHaircutBrotherScript_AlreadyGotHaircut
	showmoneybox 0, 0
	message J_GoldenrodUndergroundYoungerHaircutBrotherOfferHaircutText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_YoungerHaircutBrotherScript_Refused
	checkmoney 0
	goto_if_eq VAR_RESULT, TRUE, J_L221
	setvar VAR_RESULT, 2
	goto J_L222
J_L221:
	setvar VAR_RESULT, 0
J_L222:
	goto_if_eq VAR_RESULT, 2, J_YoungerHaircutBrotherScript_NotEnoughMoney
	message J_GoldenrodUndergroundYoungerHaircutBrotherAskWhichMonText
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_YoungerHaircutBrotherScript_Refused
	goto_if_eq VAR_RESULT, 1, J_YoungerHaircutBrotherScript_Refused
	setflag FLAG_J_ENGINE_GOLDENROD_UNDERGROUND_GOT_HAIRCUT
	goto_if_eq VAR_RESULT, 2, J_YoungerHaircutBrotherScript_two
	goto_if_eq VAR_RESULT, 3, J_YoungerHaircutBrotherScript_three
	goto J_YoungerHaircutBrotherScript_else
J_YoungerHaircutBrotherScript_two:
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1
	clearflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2
	clearflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_3
	goto J_YoungerHaircutBrotherScript_then
J_YoungerHaircutBrotherScript_three:
	clearflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2
	clearflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_3
	goto J_YoungerHaircutBrotherScript_then
J_YoungerHaircutBrotherScript_else:
	clearflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1
	clearflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_3
	goto J_YoungerHaircutBrotherScript_then
J_YoungerHaircutBrotherScript_then:
	removemoney 0
	showmoneybox 0, 0
	message J_GoldenrodUndergroundYoungerHaircutBrotherIllMakeItLookCoolText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_WHITE
	playbgm MUS_RG_HEAL, FALSE
	delay 60
	fadescreen FADE_FROM_WHITE
	fadedefaultbgm
	message J_GoldenrodUndergroundYoungerHaircutBrotherAllDoneText
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L223
	setvar VAR_RESULT, 1
J_L223:
	goto_if_ne VAR_RESULT, 0, J_EitherHaircutBrotherScript_SlightlyHappier
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2, J_L224
	setvar VAR_RESULT, 1
J_L224:
	goto_if_ne VAR_RESULT, 0, J_EitherHaircutBrotherScript_Happier
	goto J_EitherHaircutBrotherScript_MuchHappier
J_YoungerHaircutBrotherScript_Refused:
	message J_GoldenrodUndergroundYoungerHaircutBrotherHowDisappointingText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_YoungerHaircutBrotherScript_NotEnoughMoney:
	message J_GoldenrodUndergroundYoungerHaircutBrotherShortOnFundsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_YoungerHaircutBrotherScript_AlreadyGotHaircut:
	message J_GoldenrodUndergroundYoungerHaircutBrotherOneHaircutADayText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EitherHaircutBrotherScript_SlightlyHappier::
	message J_HaircutBrosText_SlightlyHappier
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EitherHaircutBrotherScript_Happier::
	message J_HaircutBrosText_Happier
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EitherHaircutBrotherScript_MuchHappier::
	message J_HaircutBrosText_MuchHappier
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BasementDoorScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_USED_BASEMENT_KEY, J_L225
	setvar VAR_RESULT, 1
J_L225:
	goto_if_ne VAR_RESULT, 0, J_BasementDoorScript_Open
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_BASEMENT_KEY, J_L226
	setvar VAR_RESULT, 1
J_L226:
	goto_if_ne VAR_RESULT, 0, J_BasementDoorScript_Unlock
	message J_GoldenrodUndergroundTheDoorsLockedText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BasementDoorScript_Unlock:
	playse SE_SHOP
	message J_GoldenrodUndergroundBasementKeyOpenedDoorText
	waitmessage
	waitbuttonpress
	closemessage
	setmetatile 18, 6, 19, FALSE
	setmetatile 19, 6, 20, TRUE
	setmetatile 18, 7, 5, FALSE
	setmetatile 19, 7, 5, FALSE
	special DrawWholeMapView
	closemessage
	setflag FLAG_J_USED_BASEMENT_KEY
	return
J_BasementDoorScript_Open:
	message J_GoldenrodUndergroundTheDoorIsOpenText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodUndergroundScript_ShopClosed::
	message J_GoldenrodUndergroundWeAreNotOpenTodayText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodUndergroundCoinCase::
	finditem ITEM_COIN_CASE, 1
	return
J_GoldenrodUndergroundNoEntrySign::
	message J_GoldenrodUndergroundNoEntryText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodUndergroundHiddenParlyzHeal::
	finditem ITEM_PARALYZE_HEAL
	return
J_GoldenrodUndergroundHiddenSuperPotion::
	finditem ITEM_SUPER_POTION
	return
J_GoldenrodUndergroundHiddenAntidote::
	finditem ITEM_ANTIDOTE
	return
J_SupernerdEricSeenText::
	.string "I got booted out\nof the GAME COR-\lNER.\pI was trying to\ncheat using my\lPOKéMON…$"
J_SupernerdEricBeatenText::
	.string "…Grumble…$"
J_SupernerdEricAfterBattleText::
	.string "I guess I have to\ndo things fair and\lsquare…$"
J_SupernerdTeruSeenText::
	.string "Do you consider\ntype alignments in\lbattle?\pIf you know your\ntype advantages,\pyou'll do better\nin battle.$"
J_SupernerdTeruBeatenText::
	.string "Ow, ow, ow!$"
J_SupernerdTeruAfterBattleText::
	.string "I know my POKéMON\ntype alignments.\pBut I only use one\ntype of POKéMON.$"
J_PokemaniacIssacSeenText::
	.string "My POKéMON just\ngot a haircut!\pI'll show you how\nstrong it is!$"
J_PokemaniacIssacBeatenText::
	.string "Aiyeeee!$"
J_PokemaniacIssacAfterBattleText::
	.string "Your POKéMON will\nlike you more if\pyou give them\nhaircuts.$"
J_PokemaniacDonaldSeenText::
	.string "I think you have\nsome rare POKéMON\lwith you.\pLet me see them!$"
J_PokemaniacDonaldBeatenText::
	.string "Gaah! I lost!\nThat makes me mad!$"
J_PokemaniacDonaldAfterBattleText::
	.string "Are you making a\nPOKéDEX? Here's a\lhot tip.\pThe HIKER on ROUTE\n33, ANTHONY, is a\lgood guy.\pHe'll phone you if\nhe sees any rare\lPOKéMON.$"
J_GoldenrodUndergroundTheDoorsLockedText::
	.string "The door's locked…$"
J_GoldenrodUndergroundTheDoorIsOpenText::
	.string "The door is open.$"
J_GoldenrodUndergroundBasementKeyOpenedDoorText::
	.string "The BASEMENT KEY\nopened the door.$"
J_GoldenrodUndergroundOlderHaircutBrotherOfferHaircutText::
	.string "Welcome!\pI run the POKéMON\nSALON!\pI'm the older and\nbetter of the two\lHAIRCUT BROTHERS.\pI can make your\nPOKéMON beautiful\lfor just ¥0.\pWould you like me\nto do that?$"
J_GoldenrodUndergroundOlderHaircutBrotherAskWhichMonText::
	.string "Which POKéMON\nshould I work on?$"
J_GoldenrodUndergroundOlderHaircutBrotherWatchItBecomeBeautifulText::
	.string "OK! Watch it\nbecome beautiful!$"
J_GoldenrodUndergroundOlderHaircutBrotherAllDoneText::
	.string "There! All done!$"
J_GoldenrodUndergroundOlderHaircutBrotherThatsAShameText::
	.string "Is that right?\nThat's a shame!$"
J_GoldenrodUndergroundOlderHaircutBrotherYoullNeedMoreMoneyText::
	.string "You'll need more\nmoney than that.$"
J_GoldenrodUndergroundOlderHaircutBrotherOneHaircutADayText::
	.string "I do only one\nhaircut a day. I'm\ldone for today.$"
J_GoldenrodUndergroundYoungerHaircutBrotherOfferHaircutText::
	.string "Welcome to the\nPOKéMON SALON!\pI'm the younger\nand less expen-\lsive of the two\lHAIRCUT BROTHERS.\pI'll spiff up your\nPOKéMON for just\l¥0.\pSo? How about it?$"
J_GoldenrodUndergroundYoungerHaircutBrotherAskWhichMonText::
	.string "OK, which POKéMON\nshould I do?$"
J_GoldenrodUndergroundYoungerHaircutBrotherIllMakeItLookCoolText::
	.string "OK! I'll make it\nlook cool!$"
J_GoldenrodUndergroundYoungerHaircutBrotherAllDoneText::
	.string "There we go!\nAll done!$"
J_GoldenrodUndergroundYoungerHaircutBrotherHowDisappointingText::
	.string "No? \nHow disappointing!$"
J_GoldenrodUndergroundYoungerHaircutBrotherShortOnFundsText::
	.string "You're a little\nshort on funds.$"
J_GoldenrodUndergroundYoungerHaircutBrotherOneHaircutADayText::
	.string "I can do only one\nhaircut a day.\pSorry, but I'm all\ndone for today.$"
J_HaircutBrosText_SlightlyHappier::
	.string "{STR_VAR_1} looks a\nlittle happier.$"
J_HaircutBrosText_Happier::
	.string "{STR_VAR_1} looks\nhappy.$"
J_HaircutBrosText_MuchHappier::
	.string "{STR_VAR_1} looks\ndelighted!$"
J_GoldenrodUndergroundWeAreNotOpenTodayText::
	.string "We're not open\ntoday.$"
J_GoldenrodUndergroundNoEntryText::
	.string "NO ENTRY BEYOND\nTHIS POINT$"
J_GoldenrodUnderground_MapEvents::
