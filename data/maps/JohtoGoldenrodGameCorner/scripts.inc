@ KJH: translated from pokecrystal maps/GoldenrodGameCorner.asm by kjh_tools/johto

JohtoGoldenrodGameCorner_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoGoldenrodGameCorner_OnTransition
	.byte 0

JohtoGoldenrodGameCorner_OnTransition:
	call J_GoldenrodGameCornerMoveTutorCallback
	end

J_W_GoldenrodGameCornerCoinVendorScript::
	lock
	call J_GoldenrodGameCornerCoinVendorScript
	release
	end

J_W_GoldenrodGameCornerTMVendorScript::
	lock
	call J_GoldenrodGameCornerTMVendorScript
	release
	end

J_W_GoldenrodGameCornerPrizeMonVendorScript::
	lock
	call J_GoldenrodGameCornerPrizeMonVendorScript
	release
	end

J_W_GoldenrodGameCornerPharmacistScript::
	lock
	call J_GoldenrodGameCornerPharmacistScript
	release
	end

J_W_GoldenrodGameCornerPokefanM1Script::
	lock
	call J_GoldenrodGameCornerPokefanM1Script
	release
	end

J_W_GoldenrodGameCornerCooltrainerMScript::
	lock
	call J_GoldenrodGameCornerCooltrainerMScript
	release
	end

J_W_GoldenrodGameCornerPokefanFScript::
	lock
	call J_GoldenrodGameCornerPokefanFScript
	release
	end

J_W_GoldenrodGameCornerCooltrainerFScript::
	lock
	call J_GoldenrodGameCornerCooltrainerFScript
	release
	end

J_W_GoldenrodGameCornerGentlemanScript::
	lock
	call J_GoldenrodGameCornerGentlemanScript
	release
	end

J_W_GoldenrodGameCornerPokefanM2Script::
	lock
	call J_GoldenrodGameCornerPokefanM2Script
	release
	end

J_W_MoveTutorInsideScript::
	lock
	call J_MoveTutorInsideScript
	release
	end

J_S_GoldenrodGameCornerSlotsMachineScript::
	lockall
	call J_GoldenrodGameCornerSlotsMachineScript
	releaseall
	end

J_S_GoldenrodGameCornerLuckySlotsMachineScript::
	lockall
	call J_GoldenrodGameCornerLuckySlotsMachineScript
	releaseall
	end

J_S_GoldenrodGameCornerCardFlipMachineScript::
	lockall
	call J_GoldenrodGameCornerCardFlipMachineScript
	releaseall
	end

J_S_GoldenrodGameCornerLeftTheirDrinkScript::
	lockall
	call J_GoldenrodGameCornerLeftTheirDrinkScript
	releaseall
	end

J_GoldenrodGameCorner_MapScripts::
J_GoldenrodGameCornerMoveTutorCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L552
	setvar VAR_RESULT, 1
J_L552:
	goto_if_eq VAR_RESULT, 0, J_GoldenrodGameCornerMoveTutorCallback_finish
	checkitem ITEM_COIN_CASE, 1
	goto_if_eq VAR_RESULT, 0, J_GoldenrodGameCornerMoveTutorCallback_move_tutor_inside
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 3, J_GoldenrodGameCornerMoveTutorCallback_move_tutor_outside
	goto_if_eq VAR_RESULT, 6, J_GoldenrodGameCornerMoveTutorCallback_move_tutor_outside
J_GoldenrodGameCornerMoveTutorCallback_move_tutor_inside:
	clearflag FLAG_J_GOLDENROD_GAME_CORNER_MOVE_TUTOR
	return
J_GoldenrodGameCornerMoveTutorCallback_move_tutor_outside:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_DAILY_MOVE_TUTOR, J_L553
	setvar VAR_RESULT, 1
J_L553:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodGameCornerMoveTutorCallback_finish
	setflag FLAG_J_GOLDENROD_GAME_CORNER_MOVE_TUTOR
J_GoldenrodGameCornerMoveTutorCallback_finish:
	return
J_MoveTutorInsideScript::
	faceplayer
	message J_MoveTutorInsideText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 12, DIR_EAST
	return
J_GoldenrodGameCornerCoinVendorScript::
	goto J_Std_Nop
J_GoldenrodGameCornerTMVendorScript::
	faceplayer
	message J_GoldenrodGameCornerPrizeVendorIntroText
	waitmessage
	waitbuttonpress
	checkitem ITEM_COIN_CASE, 1
	goto_if_eq VAR_RESULT, 0, J_GoldenrodGameCornerPrizeVendor_NoCoinCaseScript
	message J_GoldenrodGameCornerPrizeVendorWhichPrizeText
	waitmessage
J_GoldenrodGameCornerTMVendor_LoopScript::
	showcoinsbox 0, 0
	setvar VAR_RESULT, 1
	goto_if_eq VAR_RESULT, 1, J_GoldenrodGameCornerTMVendor_LoopScript_Thunder
	goto_if_eq VAR_RESULT, 2, J_GoldenrodGameCornerTMVendor_LoopScript_Blizzard
	goto_if_eq VAR_RESULT, 3, J_GoldenrodGameCornerTMVendor_LoopScript_FireBlast
	goto J_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript
J_GoldenrodGameCornerTMVendor_LoopScript_Thunder:
	checkcoins VAR_0x8005
	setvar VAR_RESULT, 0
	goto_if_ge VAR_0x8005, 0, J_L554
	setvar VAR_RESULT, 2
J_L554:
	goto_if_eq VAR_RESULT, 2, J_GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript
	bufferitemname STR_VAR_1, ITEM_POTION
	call J_GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript
	goto_if_eq VAR_RESULT, 0, J_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript
	additem ITEM_TM25, 1
	goto_if_eq VAR_RESULT, 0, J_GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript
	removecoins 0
	goto J_GoldenrodGameCornerTMVendor_FinishScript
J_GoldenrodGameCornerTMVendor_LoopScript_Blizzard:
	checkcoins VAR_0x8005
	setvar VAR_RESULT, 0
	goto_if_ge VAR_0x8005, 0, J_L555
	setvar VAR_RESULT, 2
J_L555:
	goto_if_eq VAR_RESULT, 2, J_GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript
	bufferitemname STR_VAR_1, ITEM_POTION
	call J_GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript
	goto_if_eq VAR_RESULT, 0, J_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript
	additem ITEM_TM14, 1
	goto_if_eq VAR_RESULT, 0, J_GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript
	removecoins 0
	goto J_GoldenrodGameCornerTMVendor_FinishScript
J_GoldenrodGameCornerTMVendor_LoopScript_FireBlast:
	checkcoins VAR_0x8005
	setvar VAR_RESULT, 0
	goto_if_ge VAR_0x8005, 0, J_L556
	setvar VAR_RESULT, 2
J_L556:
	goto_if_eq VAR_RESULT, 2, J_GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript
	bufferitemname STR_VAR_1, ITEM_POTION
	call J_GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript
	goto_if_eq VAR_RESULT, 0, J_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript
	additem ITEM_TM38, 1
	goto_if_eq VAR_RESULT, 0, J_GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript
	removecoins 0
	goto J_GoldenrodGameCornerTMVendor_FinishScript
J_GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript::
	message J_GoldenrodGameCornerPrizeVendorConfirmPrizeText
	waitmessage
	yesnobox 20, 8
	return
J_GoldenrodGameCornerTMVendor_FinishScript::
	waitse
	playse SE_SHOP
	message J_GoldenrodGameCornerPrizeVendorHereYouGoText
	waitmessage
	waitbuttonpress
	goto J_GoldenrodGameCornerTMVendor_LoopScript
J_GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript::
	message J_GoldenrodGameCornerPrizeVendorNeedMoreCoinsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript::
	message J_GoldenrodGameCornerPrizeVendorNoMoreRoomText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript::
	message J_GoldenrodGameCornerPrizeVendorQuitText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodGameCornerPrizeVendor_NoCoinCaseScript::
	message J_GoldenrodGameCornerPrizeVendorNoCoinCaseText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodGameCornerTMVendorMenuHeader::
J_GoldenrodGameCornerTMVendorMenuHeader_MenuData:
	.string "TM25    $"
	.string "TM14    $"
	.string "TM38    $"
	.string "CANCEL$"
J_GoldenrodGameCornerPrizeMonVendorScript::
	faceplayer
	message J_GoldenrodGameCornerPrizeVendorIntroText
	waitmessage
	waitbuttonpress
	checkitem ITEM_COIN_CASE, 1
	goto_if_eq VAR_RESULT, 0, J_GoldenrodGameCornerPrizeVendor_NoCoinCaseScript
J_GoldenrodGameCornerPrizeMonVendorScript_loop:
	message J_GoldenrodGameCornerPrizeVendorWhichPrizeText
	waitmessage
	showcoinsbox 0, 0
	setvar VAR_RESULT, 1
	goto_if_eq VAR_RESULT, 1, J_GoldenrodGameCornerPrizeMonVendorScript_Abra
	goto_if_eq VAR_RESULT, 2, J_GoldenrodGameCornerPrizeMonVendorScript_Cubone
	goto_if_eq VAR_RESULT, 3, J_GoldenrodGameCornerPrizeMonVendorScript_Wobbuffet
	goto J_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript
J_GoldenrodGameCornerPrizeMonVendorScript_Abra:
	checkcoins VAR_0x8005
	setvar VAR_RESULT, 0
	goto_if_ge VAR_0x8005, 0, J_L557
	setvar VAR_RESULT, 2
J_L557:
	goto_if_eq VAR_RESULT, 2, J_GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript
	setvar VAR_0x8004, 1
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 6, J_GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript
	call J_GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript
	goto_if_eq VAR_RESULT, 0, J_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript
	waitse
	playse SE_SHOP
	message J_GoldenrodGameCornerPrizeVendorHereYouGoText
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 63
	setvar VAR_RESULT, 0
	givemon SPECIES_ABRA, 5, ITEM_NONE
	setflag FLAG_SYS_POKEMON_GET
	bufferspeciesname STR_VAR_1, SPECIES_ABRA
	playfanfare MUS_LEVEL_UP
	message J_Text_ReceivedMon
	waitmessage
	waitfanfare
	setvar VAR_RESULT, 1
	removecoins 0
	goto J_GoldenrodGameCornerPrizeMonVendorScript_loop
J_GoldenrodGameCornerPrizeMonVendorScript_Cubone:
	checkcoins VAR_0x8005
	setvar VAR_RESULT, 0
	goto_if_ge VAR_0x8005, 0, J_L558
	setvar VAR_RESULT, 2
J_L558:
	goto_if_eq VAR_RESULT, 2, J_GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript
	setvar VAR_0x8004, 1
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 6, J_GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript
	call J_GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript
	goto_if_eq VAR_RESULT, 0, J_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript
	waitse
	playse SE_SHOP
	message J_GoldenrodGameCornerPrizeVendorHereYouGoText
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 104
	setvar VAR_RESULT, 0
	givemon SPECIES_CUBONE, 15, ITEM_NONE
	setflag FLAG_SYS_POKEMON_GET
	bufferspeciesname STR_VAR_1, SPECIES_CUBONE
	playfanfare MUS_LEVEL_UP
	message J_Text_ReceivedMon
	waitmessage
	waitfanfare
	setvar VAR_RESULT, 1
	removecoins 0
	goto J_GoldenrodGameCornerPrizeMonVendorScript_loop
J_GoldenrodGameCornerPrizeMonVendorScript_Wobbuffet:
	checkcoins VAR_0x8005
	setvar VAR_RESULT, 0
	goto_if_ge VAR_0x8005, 0, J_L559
	setvar VAR_RESULT, 2
J_L559:
	goto_if_eq VAR_RESULT, 2, J_GoldenrodGameCornerPrizeVendor_NotEnoughCoinsScript
	setvar VAR_0x8004, 1
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 6, J_GoldenrodGameCornerPrizeMonVendor_NoRoomForPrizeScript
	call J_GoldenrodGameCornerPrizeVendor_ConfirmPurchaseScript
	goto_if_eq VAR_RESULT, 0, J_GoldenrodGameCornerPrizeVendor_CancelPurchaseScript
	waitse
	playse SE_SHOP
	message J_GoldenrodGameCornerPrizeVendorHereYouGoText
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 202
	setvar VAR_RESULT, 0
	givemon SPECIES_WOBBUFFET, 15, ITEM_NONE
	setflag FLAG_SYS_POKEMON_GET
	bufferspeciesname STR_VAR_1, SPECIES_WOBBUFFET
	playfanfare MUS_LEVEL_UP
	message J_Text_ReceivedMon
	waitmessage
	waitfanfare
	setvar VAR_RESULT, 1
	removecoins 0
	goto J_GoldenrodGameCornerPrizeMonVendorScript_loop
J_GoldenrodGameCornerPrizeMonVendorScript_MenuHeader:
J_GoldenrodGameCornerPrizeMonVendorScript_MenuData:
	.string "ABRA       $"
	.string "CUBONE     $"
	.string "WOBBUFFET  $"
	.string "CANCEL$"
J_GoldenrodGameCornerPharmacistScript::
	faceplayer
	message J_GoldenrodGameCornerPharmacistText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject VAR_LAST_TALKED, DIR_WEST
	return
J_GoldenrodGameCornerPokefanM1Script::
	faceplayer
	message J_GoldenrodGameCornerPokefanM1Text
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 6, DIR_EAST
	return
J_GoldenrodGameCornerCooltrainerMScript::
	faceplayer
	message J_GoldenrodGameCornerCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 7, DIR_WEST
	return
J_GoldenrodGameCornerPokefanFScript::
	faceplayer
	message J_GoldenrodGameCornerPokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 8, DIR_EAST
	return
J_GoldenrodGameCornerCooltrainerFScript::
	faceplayer
	message J_GoldenrodGameCornerCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodGameCornerGentlemanScript::
	faceplayer
	message J_GoldenrodGameCornerGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 10, DIR_EAST
	return
J_GoldenrodGameCornerPokefanM2Script::
	faceplayer
	message J_GoldenrodGameCornerPokefanM2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodGameCornerLeftTheirDrinkScript::
	message J_GoldenrodGameCornerLeftTheirDrinkText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodGameCornerSlotsMachineScript::
	random 6
	goto_if_eq VAR_RESULT, 0, J_GoldenrodGameCornerLuckySlotsMachineScript
	special DrawWholeMapView
	setvar VAR_RESULT, 0
	setvar VAR_RESULT, 0
	closemessage
	return
J_GoldenrodGameCornerLuckySlotsMachineScript::
	special DrawWholeMapView
	setvar VAR_RESULT, 1
	setvar VAR_RESULT, 0
	closemessage
	return
J_GoldenrodGameCornerCardFlipMachineScript::
	special DrawWholeMapView
	setvar VAR_RESULT, 0
	closemessage
	return
J_GoldenrodGameCornerPrizeVendorIntroText::
	.string "Welcome!\pWe exchange your\ngame coins for\lfabulous prizes!$"
J_GoldenrodGameCornerPrizeVendorWhichPrizeText::
	.string "Which prize would\nyou like?$"
J_GoldenrodGameCornerPrizeVendorConfirmPrizeText::
	.string "{STR_VAR_1}.\nIs that right?$"
J_GoldenrodGameCornerPrizeVendorHereYouGoText::
	.string "Here you go!$"
J_GoldenrodGameCornerPrizeVendorNeedMoreCoinsText::
	.string "Sorry! You need\nmore coins.$"
J_GoldenrodGameCornerPrizeVendorNoMoreRoomText::
	.string "Sorry. You can't\ncarry any more.$"
J_GoldenrodGameCornerPrizeVendorQuitText::
	.string "OK. Please save\nyour coins and\lcome again!$"
J_GoldenrodGameCornerPrizeVendorNoCoinCaseText::
	.string "Oh? You don't have\na COIN CASE.$"
J_GoldenrodGameCornerPharmacistText::
	.string "This machine looks\nthe same as the\lothers.$"
	.string "I always play this\nslot machine. It\ppays out more than\nothers, I think.$"
J_GoldenrodGameCornerPokefanM1Text::
	.string "These machines\nseem different\pfrom the ones at\nCELADON CITY!$"
	.string "I just love this\nnew slot machine.\pIt's more of a\nchallenge than the\lones in CELADON.$"
J_GoldenrodGameCornerCooltrainerMText::
	.string "Nothing is certain\nin this area.$"
	.string "Life is a gamble.\nI'm going to flip\lcards till I drop!$"
J_GoldenrodGameCornerPokefanFText::
	.string "Card flip…\pDifferent from the\nother machines.$"
	.string "\pI prefer it over\nthe slots because\pit's easier to\nfigure the odds.\pBut the payout is\nmuch lower.$"
J_GoldenrodGameCornerCooltrainerFText::
	.string "I won't quit until\nI win!$"
J_GoldenrodGameCornerGentlemanText::
	.string "I taught BLIZZARD\nto my POKéMON.\pIt was hard to get\nenough coins for\pit, but it was\nworth it.$"
J_GoldenrodGameCornerPokefanM2Text::
	.string "COIN CASE? I threw\nit away in the\lUNDERGROUND.$"
	.string "I couldn't win at\nthe slots, and I\pblew it on card\nflipping…\pI got so furious,\nI tossed out my\pCOIN CASE in the\nUNDERGROUND.$"
J_MoveTutorInsideText::
	.string "Wahahah! The coins\nkeep rolling in!$"
J_GoldenrodGameCornerLeftTheirDrinkText::
	.string "Someone left their\ndrink.\pIt smells sweet.$"
J_GoldenrodGameCorner_MapEvents::
