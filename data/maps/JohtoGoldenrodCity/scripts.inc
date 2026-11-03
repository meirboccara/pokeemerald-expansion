@ KJH: translated from pokecrystal maps/GoldenrodCity.asm by kjh_tools/johto

JohtoGoldenrodCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoGoldenrodCity_OnTransition
	.byte 0

JohtoGoldenrodCity_OnTransition:
	call J_GoldenrodCityFlypointAndFloriaCallback
	call J_GoldenrodCityMoveTutorCallback
	end

J_W_GoldenrodCityPokefanMScript::
	lock
	call J_GoldenrodCityPokefanMScript
	release
	end

J_W_GoldenrodCityYoungster1Script::
	lock
	call J_GoldenrodCityYoungster1Script
	release
	end

J_W_GoldenrodCityCooltrainerF1Script::
	lock
	call J_GoldenrodCityCooltrainerF1Script
	release
	end

J_W_GoldenrodCityCooltrainerF2Script::
	lock
	call J_GoldenrodCityCooltrainerF2Script
	release
	end

J_W_GoldenrodCityYoungster2Script::
	lock
	call J_GoldenrodCityYoungster2Script
	release
	end

J_W_GoldenrodCityLassScript::
	lock
	call J_GoldenrodCityLassScript
	release
	end

J_W_GoldenrodCityGrampsScript::
	lock
	call J_GoldenrodCityGrampsScript
	release
	end

J_W_GoldenrodCityRocketScoutScript::
	lock
	call J_GoldenrodCityRocketScoutScript
	release
	end

J_W_GoldenrodCityRocket1Script::
	lock
	call J_GoldenrodCityRocket1Script
	release
	end

J_W_GoldenrodCityRocket2Script::
	lock
	call J_GoldenrodCityRocket2Script
	release
	end

J_W_GoldenrodCityRocket3Script::
	lock
	call J_GoldenrodCityRocket3Script
	release
	end

J_W_GoldenrodCityRocket4Script::
	lock
	call J_GoldenrodCityRocket4Script
	release
	end

J_W_GoldenrodCityRocket5Script::
	lock
	call J_GoldenrodCityRocket5Script
	release
	end

J_W_GoldenrodCityRocket6Script::
	lock
	call J_GoldenrodCityRocket6Script
	release
	end

J_W_MoveTutorScript::
	lock
	call J_MoveTutorScript
	release
	end

J_S_GoldenrodCityStationSign::
	lockall
	call J_GoldenrodCityStationSign
	releaseall
	end

J_S_GoldenrodCityRadioTowerSign::
	lockall
	call J_GoldenrodCityRadioTowerSign
	releaseall
	end

J_S_GoldenrodDeptStoreSign::
	lockall
	call J_GoldenrodDeptStoreSign
	releaseall
	end

J_S_GoldenrodGymSign::
	lockall
	call J_GoldenrodGymSign
	releaseall
	end

J_S_GoldenrodCitySign::
	lockall
	call J_GoldenrodCitySign
	releaseall
	end

J_S_GoldenrodCityBikeShopSign::
	lockall
	call J_GoldenrodCityBikeShopSign
	releaseall
	end

J_S_GoldenrodCityGameCornerSign::
	lockall
	call J_GoldenrodCityGameCornerSign
	releaseall
	end

J_S_GoldenrodCityNameRaterSign::
	lockall
	call J_GoldenrodCityNameRaterSign
	releaseall
	end

J_S_GoldenrodCityUndergroundSignNorth::
	lockall
	call J_GoldenrodCityUndergroundSignNorth
	releaseall
	end

J_S_GoldenrodCityUndergroundSignSouth::
	lockall
	call J_GoldenrodCityUndergroundSignSouth
	releaseall
	end

J_S_GoldenrodCityPokecenterSign::
	lockall
	call J_GoldenrodCityPokecenterSign
	releaseall
	end

J_S_GoldenrodCityFlowerShopSign::
	lockall
	call J_GoldenrodCityFlowerShopSign
	releaseall
	end

J_GoldenrodCity_MapScripts::
J_GoldenrodCityFlypointAndFloriaCallback::
	setflag FLAG_J_ENGINE_FLYPOINT_GOLDENROD
	setflag FLAG_J_ENGINE_REACHED_GOLDENROD
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_MET_FLORIA, J_L512
	setvar VAR_RESULT, 1
J_L512:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodCityFlypointAndFloriaCallback_FloriaDone
	clearflag FLAG_J_FLORIA_AT_SUDOWOODO
J_GoldenrodCityFlypointAndFloriaCallback_FloriaDone:
	return
J_GoldenrodCityMoveTutorCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L513
	setvar VAR_RESULT, 1
J_L513:
	goto_if_eq VAR_RESULT, 0, J_GoldenrodCityMoveTutorCallback_MoveTutorDone
	checkitem ITEM_COIN_CASE, 1
	goto_if_eq VAR_RESULT, 0, J_GoldenrodCityMoveTutorCallback_MoveTutorDisappear
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 3, J_GoldenrodCityMoveTutorCallback_MoveTutorAppear
	goto_if_eq VAR_RESULT, 6, J_GoldenrodCityMoveTutorCallback_MoveTutorAppear
J_GoldenrodCityMoveTutorCallback_MoveTutorDisappear:
	setflag FLAG_J_GOLDENROD_CITY_MOVE_TUTOR
	return
J_GoldenrodCityMoveTutorCallback_MoveTutorAppear:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_DAILY_MOVE_TUTOR, J_L514
	setvar VAR_RESULT, 1
J_L514:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodCityMoveTutorCallback_MoveTutorDone
	clearflag FLAG_J_GOLDENROD_CITY_MOVE_TUTOR
J_GoldenrodCityMoveTutorCallback_MoveTutorDone:
	return
J_MoveTutorScript::
	faceplayer
	message J_GoldenrodCityMoveTutorAskTeachAMoveText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_MoveTutorScript_Refused
	showcoinsbox 0, 0
	message J_GoldenrodCityMoveTutorAsk4000CoinsOkayText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_MoveTutorScript_Refused2
	checkcoins VAR_0x8005
	setvar VAR_RESULT, 0
	goto_if_ge VAR_0x8005, 4000, J_L515
	setvar VAR_RESULT, 2
J_L515:
	goto_if_eq VAR_RESULT, 2, J_MoveTutorScript_NotEnoughMoney
	message J_GoldenrodCityMoveTutorWhichMoveShouldITeachText
	waitmessage
	setvar VAR_RESULT, 1
	goto_if_eq VAR_RESULT, 1, J_MoveTutorScript_Flamethrower
	goto_if_eq VAR_RESULT, 2, J_MoveTutorScript_Thunderbolt
	goto_if_eq VAR_RESULT, 3, J_MoveTutorScript_IceBeam
	goto J_MoveTutorScript_Incompatible
J_MoveTutorScript_Flamethrower:
	setvar VAR_RESULT, 1
	message J_GoldenrodCityMoveTutorMoveText
	waitmessage
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_MoveTutorScript_TeachMove
	goto J_MoveTutorScript_Incompatible
J_MoveTutorScript_Thunderbolt:
	setvar VAR_RESULT, 2
	message J_GoldenrodCityMoveTutorMoveText
	waitmessage
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_MoveTutorScript_TeachMove
	goto J_MoveTutorScript_Incompatible
J_MoveTutorScript_IceBeam:
	setvar VAR_RESULT, 3
	message J_GoldenrodCityMoveTutorMoveText
	waitmessage
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_MoveTutorScript_TeachMove
	goto J_MoveTutorScript_Incompatible
J_MoveTutorScript_MoveMenuHeader:
J_MoveTutorScript_MenuData:
	.string "FLAMETHROWER$"
	.string "THUNDERBOLT$"
	.string "ICE BEAM$"
	.string "CANCEL$"
J_MoveTutorScript_Refused:
	message J_GoldenrodCityMoveTutorAwwButTheyreAmazingText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MoveTutorScript_Refused2:
	message J_GoldenrodCityMoveTutorHmTooBadText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MoveTutorScript_TeachMove:
	message J_GoldenrodCityMoveTutorIfYouUnderstandYouveMadeItText
	waitmessage
	waitbuttonpress
	removecoins 4000
	waitse
	playse SE_SHOP
	showcoinsbox 0, 0
	message J_GoldenrodCityMoveTutorFarewellKidText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 2, J_MoveTutorScript_WalkAroundPlayer
	applymovement 15, J_GoldenrodCityMoveTutorEnterGameCornerMovement
	waitmovement 15
	goto J_MoveTutorScript_GoInside
J_MoveTutorScript_WalkAroundPlayer:
	applymovement 15, J_GoldenrodCityMoveTutorWalkAroundPlayerThenEnterGameCornerMovement
	waitmovement 15
J_MoveTutorScript_GoInside:
	playse SE_DOOR
	removeobject 15
	clearflag FLAG_J_GOLDENROD_GAME_CORNER_MOVE_TUTOR
	setflag FLAG_J_ENGINE_DAILY_MOVE_TUTOR
	waitse
	return
J_MoveTutorScript_Incompatible:
	message J_GoldenrodCityMoveTutorBButText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MoveTutorScript_NotEnoughMoney:
	message J_GoldenrodCityMoveTutorYouDontHaveEnoughCoinsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityPokefanMScript::
	faceplayer
	message J_GoldenrodCityPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityYoungster1Script::
	faceplayer
	message J_GoldenrodCityYoungster1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityCooltrainerF1Script::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L516
	setvar VAR_RESULT, 1
J_L516:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodCityCooltrainerF1Script_ClearedRadioTower
	message J_GoldenrodCityCooltrainerF1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityCooltrainerF1Script_ClearedRadioTower:
	message J_GoldenrodCityCooltrainerF1Text_ClearedRadioTower
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityCooltrainerF2Script::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_RADIO_CARD, J_L517
	setvar VAR_RESULT, 1
J_L517:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodCityCooltrainerF2Script_GotRadioCard
	message J_GoldenrodCityCooltrainerF2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityCooltrainerF2Script_GotRadioCard:
	message J_GoldenrodCityCooltrainerF2Text_GotRadioCard
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityYoungster2Script::
	faceplayer
	message J_GoldenrodCityYoungster2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityLassScript::
	faceplayer
	message J_GoldenrodCityLassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityGrampsScript::
	faceplayer
	message J_GoldenrodCityGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityRocketScoutScript::
	message J_GoldenrodCityRocketScoutText1
	waitmessage
	waitbuttonpress
	faceplayer
	message J_GoldenrodCityRocketScoutText2
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 8, DIR_NORTH
	return
J_GoldenrodCityRocket1Script::
	faceplayer
	message J_GoldenrodCityRocket1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityRocket2Script::
	faceplayer
	message J_GoldenrodCityRocket2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityRocket3Script::
	faceplayer
	message J_GoldenrodCityRocket3Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityRocket4Script::
	faceplayer
	message J_GoldenrodCityRocket4Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityRocket5Script::
	faceplayer
	message J_GoldenrodCityRocket5Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityRocket6Script::
	faceplayer
	message J_GoldenrodCityRocket6Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityStationSign::
	message J_GoldenrodCityStationSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityRadioTowerSign::
	message J_GoldenrodCityRadioTowerSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStoreSign::
	message J_GoldenrodDeptStoreSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodGymSign::
	message J_GoldenrodGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCitySign::
	message J_GoldenrodCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityBikeShopSign::
	message J_GoldenrodCityBikeShopSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityGameCornerSign::
	message J_GoldenrodCityGameCornerSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityNameRaterSign::
	message J_GoldenrodCityNameRaterSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityUndergroundSignNorth::
	message J_GoldenrodCityUndergroundSignNorthText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityUndergroundSignSouth::
	message J_GoldenrodCityUndergroundSignSouthText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityPokecenterSign::
	goto J_PokecenterSignScript
J_GoldenrodCityFlowerShopSign::
	message J_GoldenrodCityFlowerShopSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodCityMoveTutorEnterGameCornerMovement::
	walk_right
	walk_right
	walk_up
	step_end
J_GoldenrodCityMoveTutorWalkAroundPlayerThenEnterGameCornerMovement::
	walk_down
	walk_right
	walk_right
	walk_up
	walk_up
	step_end
J_GoldenrodCityPokefanMText::
	.string "They built the new\nRADIO TOWER to\preplace the old,\ncreaky one.$"
J_GoldenrodCityYoungster1Text::
	.string "I know there's a\nnew BIKE SHOP, but\pI can't find it\nanywhere.$"
J_GoldenrodCityCooltrainerF1Text::
	.string "Is that man in\nblack dressed up\plike a TEAM ROCKET\nmember? How silly!$"
J_GoldenrodCityCooltrainerF1Text_ClearedRadioTower::
	.string "Was that man in\nblack really part\pof TEAM ROCKET? I\ncan't believe it!$"
J_GoldenrodCityCooltrainerF2Text::
	.string "The RADIO TOWER in\nGOLDENROD CITY is\la landmark.\pThey're running a\npromotional cam- \lpaign right now.\pThey'll modify\nyour POKéGEAR,\pso it can also\nserve as a radio.$"
J_GoldenrodCityCooltrainerF2Text_GotRadioCard::
	.string "Oh, your POKéGEAR\nworks as a radio!$"
J_GoldenrodCityYoungster2Text::
	.string "E-he-he-he…\pI got in trouble\nfor playing in the\pbasement of the\nDEPT.STORE.$"
J_GoldenrodCityLassText::
	.string "The man at that\nhouse rates your\lPOKéMON names.\pHe can even rename\nyour POKéMON.$"
J_GoldenrodCityGrampsText::
	.string "Whew! This is one\nbig town. I don't\pknow where any-\nthing is.$"
J_GoldenrodCityRocketScoutText1::
	.string "So this is the\nRADIO TOWER…$"
J_GoldenrodCityRocketScoutText2::
	.string "What do you want,\nyou pest? Scram!$"
J_GoldenrodCityRocket1Text::
	.string "Stay out of the\nway! Beat it!$"
J_GoldenrodCityRocket2Text::
	.string "Take over the\nRADIO TOWER…\pWhat? It's none of\nyour business!$"
J_GoldenrodCityRocket3Text::
	.string "POKéMON? They're\nnothing more than\ptools for making\nmoney!$"
J_GoldenrodCityRocket4Text::
	.string "Our dream will\nsoon come true…\pIt was such a long\nstruggle…$"
J_GoldenrodCityRocket5Text::
	.string "Hey, brat! You\ndon't belong here!\lGet lost!$"
J_GoldenrodCityRocket6Text::
	.string "Come taste the\ntrue terror of\lTEAM ROCKET!$"
J_GoldenrodCityStationSignText::
	.string "GOLDENROD CITY\nSTATION$"
J_GoldenrodCityRadioTowerSignText::
	.string "GOLDENROD CITY\nRADIO TOWER$"
J_GoldenrodDeptStoreSignText::
	.string "Full Selection of\nPOKéMON Goods!\pGOLDENROD CITY\nDEPT.STORE$"
J_GoldenrodGymSignText::
	.string "GOLDENROD CITY\nPOKéMON GYM\lLEADER: WHITNEY\pThe Incredibly\nPretty Girl!$"
J_GoldenrodCitySignText::
	.string "GOLDENROD CITY\pThe Festive City\nof Opulent Charm$"
J_GoldenrodCityBikeShopSignText::
	.string "The World is a\nCycle Path!\lBIKE SHOP$"
J_GoldenrodCityGameCornerSignText::
	.string "Your Playground!\pGOLDENROD CITY\nGAME CORNER$"
J_GoldenrodCityNameRaterSignText::
	.string "NAME RATER\pGet Your POKéMON\nNicknames Rated$"
J_GoldenrodCityUndergroundSignNorthText::
	.string "UNDERGROUND\nENTRANCE$"
J_GoldenrodCityUndergroundSignSouthText::
	.string "UNDERGROUND\nENTRANCE$"
J_GoldenrodCityPokeComCenterSignText::
	.string "For Mobile Tips!\nPOKéCOM CENTER$"
J_GoldenrodCityFlowerShopSignText::
	.string "Blooming Beautiful\nFLOWER SHOP$"
J_GoldenrodCityMoveTutorAskTeachAMoveText::
	.string "I can teach your\nPOKéMON amazing\pmoves if you'd\nlike.\pShould I teach a\nnew move?$"
J_GoldenrodCityMoveTutorAsk4000CoinsOkayText::
	.string "It will cost you\n4000 coins. Okay?$"
J_GoldenrodCityMoveTutorAwwButTheyreAmazingText::
	.string "Aww… But they're\namazing…$"
J_GoldenrodCityMoveTutorWhichMoveShouldITeachText::
	.string "Wahahah! You won't\nregret it!\pWhich move should\nI teach?$"
J_GoldenrodCityMoveTutorHmTooBadText::
	.string "Hm, too bad. I'll\nhave to get some\lcash from home…$"
J_GoldenrodCityMoveTutorIfYouUnderstandYouveMadeItText::
	.string "If you understand\nwhat's so amazing\pabout this move,\nyou've made it as\la trainer.$"
J_GoldenrodCityMoveTutorFarewellKidText::
	.string "Wahahah!\nFarewell, kid!$"
J_GoldenrodCityMoveTutorBButText::
	.string "B-but…$"
J_GoldenrodCityMoveTutorYouDontHaveEnoughCoinsText::
	.string "…You don't have\nenough coins here…$"
J_GoldenrodCityMoveTutorMoveText::
	.string "$"
J_GoldenrodCity_MapEvents::
