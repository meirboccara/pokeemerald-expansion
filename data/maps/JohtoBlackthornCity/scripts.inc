@ KJH: translated from pokecrystal maps/BlackthornCity.asm by kjh_tools/johto

JohtoBlackthornCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoBlackthornCity_OnTransition
	.byte 0

JohtoBlackthornCity_OnTransition:
	call J_BlackthornCityFlypointCallback
	call J_BlackthornCitySantosCallback
	end

J_W_BlackthornSuperNerdScript::
	lock
	call J_BlackthornSuperNerdScript
	release
	end

J_W_BlackthornGramps1Script::
	lock
	call J_BlackthornGramps1Script
	release
	end

J_W_BlackthornGramps2Script::
	lock
	call J_BlackthornGramps2Script
	release
	end

J_W_BlackthornBlackBeltScript::
	lock
	call J_BlackthornBlackBeltScript
	release
	end

J_W_BlackthornCooltrainerF1Script::
	lock
	call J_BlackthornCooltrainerF1Script
	release
	end

J_W_BlackthornYoungsterScript::
	lock
	call J_BlackthornYoungsterScript
	release
	end

J_W_SantosScript::
	lock
	call J_SantosScript
	release
	end

J_W_BlackthornCooltrainerF2Script::
	lock
	call J_BlackthornCooltrainerF2Script
	release
	end

J_S_BlackthornCitySign::
	lockall
	call J_BlackthornCitySign
	releaseall
	end

J_S_BlackthornGymSign::
	lockall
	call J_BlackthornGymSign
	releaseall
	end

J_S_MoveDeletersHouseSign::
	lockall
	call J_MoveDeletersHouseSign
	releaseall
	end

J_S_DragonDensSign::
	lockall
	call J_DragonDensSign
	releaseall
	end

J_S_BlackthornCityTrainerTips::
	lockall
	call J_BlackthornCityTrainerTips
	releaseall
	end

J_S_BlackthornCityMartSign::
	lockall
	call J_BlackthornCityMartSign
	releaseall
	end

J_S_BlackthornCityPokecenterSign::
	lockall
	call J_BlackthornCityPokecenterSign
	releaseall
	end

J_BlackthornCity_MapScripts::
J_BlackthornCityFlypointCallback::
	setflag FLAG_J_ENGINE_FLYPOINT_BLACKTHORN
	return
J_BlackthornCitySantosCallback::
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 6, J_BlackthornCitySantosCallback_SantosAppears
	setflag FLAG_J_BLACKTHORN_CITY_SANTOS_OF_SATURDAY
	return
J_BlackthornCitySantosCallback_SantosAppears:
	clearflag FLAG_J_BLACKTHORN_CITY_SANTOS_OF_SATURDAY
	return
J_BlackthornSuperNerdScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_CLAIR, J_L314
	setvar VAR_RESULT, 1
J_L314:
	goto_if_ne VAR_RESULT, 0, J_BlackthornSuperNerdScript_BeatClair
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L315
	setvar VAR_RESULT, 1
J_L315:
	goto_if_ne VAR_RESULT, 0, J_BlackthornSuperNerdScript_ClearedRadioTower
	message J_Text_ClairIsOut
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornSuperNerdScript_ClearedRadioTower:
	message J_Text_ClairIsIn
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornSuperNerdScript_BeatClair:
	message J_Text_ClairIsBeaten
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornGramps1Script::
	faceplayer
	message J_BlackthornGrampsRefusesEntryText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornGramps2Script::
	faceplayer
	message J_BlackthornGrampsGrantsEntryText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornBlackBeltScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L316
	setvar VAR_RESULT, 1
J_L316:
	goto_if_ne VAR_RESULT, 0, J_BlackthornBlackBeltScript_ClearedRadioTower
	message J_BlackBeltText_WeirdRadio
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornBlackBeltScript_ClearedRadioTower:
	message J_BlackBeltText_VoicesInMyHead
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornCooltrainerF1Script::
	faceplayer
	message J_BlackthornCooltrainerF1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornYoungsterScript::
	faceplayer
	message J_BlackthornYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornCooltrainerF2Script::
	faceplayer
	message J_BlackthornCooltrainerF2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SantosScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_SPELL_TAG_FROM_SANTOS, J_L317
	setvar VAR_RESULT, 1
J_L317:
	goto_if_ne VAR_RESULT, 0, J_SantosScript_Saturday
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_ne VAR_RESULT, 6, J_SantosScript_NotSaturday
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_MET_SANTOS_OF_SATURDAY, J_L318
	setvar VAR_RESULT, 1
J_L318:
	goto_if_ne VAR_RESULT, 0, J_SantosScript_MetSantos
	message J_MeetSantosText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_MET_SANTOS_OF_SATURDAY
J_SantosScript_MetSantos:
	message J_SantosGivesGiftText
	waitmessage
	waitbuttonpress
	giveitem ITEM_SPELL_TAG, 1
	goto_if_eq VAR_RESULT, 0, J_SantosScript_Done
	setflag FLAG_J_GOT_SPELL_TAG_FROM_SANTOS
	message J_SantosGaveGiftText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SantosScript_Saturday:
	message J_SantosSaturdayText
	waitmessage
	waitbuttonpress
J_SantosScript_Done:
	closemessage
	return
J_SantosScript_NotSaturday:
	message J_SantosNotSaturdayText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornCitySign::
	message J_BlackthornCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornGymSign::
	message J_BlackthornGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MoveDeletersHouseSign::
	message J_MoveDeletersHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DragonDensSign::
	message J_DragonDensSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornCityTrainerTips::
	message J_BlackthornCityTrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornCityPokecenterSign::
	goto J_PokecenterSignScript
J_BlackthornCityMartSign::
	goto J_MartSignScript
J_Text_ClairIsOut::
	.string "I am sorry.\pCLAIR, our GYM\nLEADER, entered\pthe DRAGON'S DEN\nbehind the GYM.\pI have no idea\nwhen our LEADER\lwill return.$"
J_Text_ClairIsIn::
	.string "CLAIR, our GYM\nLEADER, is waiting\lfor you.\pHowever, it would\nbe impossible for\pa run-of-the-mill\ntrainer to win.$"
J_Text_ClairIsBeaten::
	.string "You defeated\nCLAIR?\pThat's amazing!\pI've never heard\nof her losing to\panyone other than\nLANCE.$"
J_BlackthornGrampsRefusesEntryText::
	.string "No. Only chosen\ntrainers may train\phere.\nPlease leave.$"
J_BlackthornGrampsGrantsEntryText::
	.string "If CLAIR allows\nit, her grand-\lfather--our MASTER\l--will also.\pYou may enter.$"
J_BlackBeltText_WeirdRadio::
	.string "My radio's busted?\nLately, I only get\lthis weird signal.$"
J_BlackBeltText_VoicesInMyHead::
	.string "Arooo! Voices in\nmy head!\pHuh? I'm listening\nto my radio!$"
J_BlackthornCooltrainerF1Text::
	.string "Are you going to\nmake your POKéMON\lforget some moves?$"
J_BlackthornYoungsterText::
	.string "Dragon masters all\ncome from the city\lof BLACKTHORN.$"
J_MeetSantosText::
	.string "SANTOS: …\pIt's Saturday…\pI'm SANTOS of\nSaturday…$"
J_SantosGivesGiftText::
	.string "You can have this…$"
J_SantosGaveGiftText::
	.string "SANTOS: …\pSPELL TAG…\pGhost-type moves\nget stronger…\pIt will frighten\nyou…$"
J_SantosSaturdayText::
	.string "SANTOS: …\pSee you again on\nanother Saturday…\pI won't have any\nmore gifts…$"
J_SantosNotSaturdayText::
	.string "SANTOS: Today's\nnot Saturday…$"
J_BlackthornCooltrainerF2Text::
	.string "Wow, you came\nthrough the ICE\lPATH?\pYou must be a real\nhotshot trainer!$"
J_BlackthornCitySignText::
	.string "BLACKTHORN CITY\pA Quiet Mountain\nRetreat$"
J_BlackthornGymSignText::
	.string "BLACKTHORN CITY\nPOKéMON GYM\lLEADER: CLAIR\pThe Blessed User\nof Dragon POKéMON$"
J_MoveDeletersHouseSignText::
	.string "MOVE DELETER'S\nHOUSE$"
J_DragonDensSignText::
	.string "DRAGON'S DEN\nAHEAD$"
J_BlackthornCityTrainerTipsText::
	.string "TRAINER TIPS\pA POKéMON holding\na MIRACLEBERRY\pwill cure itself\nof any status\lproblem.$"
J_BlackthornCity_MapEvents::
