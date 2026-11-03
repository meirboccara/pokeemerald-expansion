@ KJH: translated from pokecrystal maps/EcruteakCity.asm by kjh_tools/johto

JohtoEcruteakCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoEcruteakCity_OnTransition
	.byte 0

JohtoEcruteakCity_OnTransition:
	call J_EcruteakCityFlypointCallback
	end

J_W_EcruteakCityGramps1Script::
	lock
	call J_EcruteakCityGramps1Script
	release
	end

J_W_EcruteakCityGramps2Script::
	lock
	call J_EcruteakCityGramps2Script
	release
	end

J_W_EcruteakCityLass1Script::
	lock
	call J_EcruteakCityLass1Script
	release
	end

J_W_EcruteakCityLass2Script::
	lock
	call J_EcruteakCityLass2Script
	release
	end

J_W_EcruteakCityFisherScript::
	lock
	call J_EcruteakCityFisherScript
	release
	end

J_W_EcruteakCityYoungsterScript::
	lock
	call J_EcruteakCityYoungsterScript
	release
	end

J_W_EcruteakCityGramps3Script::
	lock
	call J_EcruteakCityGramps3Script
	release
	end

J_S_EcruteakCitySign::
	lockall
	call J_EcruteakCitySign
	releaseall
	end

J_S_TinTowerSign::
	lockall
	call J_TinTowerSign
	releaseall
	end

J_S_EcruteakGymSign::
	lockall
	call J_EcruteakGymSign
	releaseall
	end

J_S_EcruteakDanceTheaterSign::
	lockall
	call J_EcruteakDanceTheaterSign
	releaseall
	end

J_S_BurnedTowerSign::
	lockall
	call J_BurnedTowerSign
	releaseall
	end

J_S_EcruteakCityPokecenterSign::
	lockall
	call J_EcruteakCityPokecenterSign
	releaseall
	end

J_S_EcruteakCityMartSign::
	lockall
	call J_EcruteakCityMartSign
	releaseall
	end

J_EcruteakCity_MapScripts::
J_EcruteakCityFlypointCallback::
	setflag FLAG_J_ENGINE_FLYPOINT_ECRUTEAK
	return
J_EcruteakCityGramps1Script::
	faceplayer
	message J_EcruteakCityGramps1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakCityGramps2Script::
	faceplayer
	message J_EcruteakCityGramps2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakCityGramps3Script::
	faceplayer
	message J_EcruteakCityGramps3Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakCityLass1Script::
	faceplayer
	message J_EcruteakCityLass1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakCityLass2Script::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RELEASED_THE_BEASTS, J_L289
	setvar VAR_RESULT, 1
J_L289:
	goto_if_ne VAR_RESULT, 0, J_EcruteakCityLass2Script_ReleasedBeasts
	message J_EcruteakCityLass2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakCityLass2Script_ReleasedBeasts:
	message J_EcruteakCityLass2Text_ReleasedBeasts
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakCityFisherScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_JASMINE_RETURNED_TO_GYM, J_L290
	setvar VAR_RESULT, 1
J_L290:
	goto_if_ne VAR_RESULT, 0, J_EcruteakCityFisherScript_JasmineReturned
	message J_EcruteakCityFisherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakCityFisherScript_JasmineReturned:
	message J_EcruteakCityFisherText_JasmineReturned
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakCityYoungsterScript::
	faceplayer
	message J_EcruteakCityYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakCitySign::
	message J_EcruteakCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TinTowerSign::
	message J_TinTowerSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakGymSign::
	message J_EcruteakGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakDanceTheaterSign::
	message J_EcruteakDanceTheaterSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BurnedTowerSign::
	message J_BurnedTowerSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakCityPokecenterSign::
	goto J_PokecenterSignScript
J_EcruteakCityMartSign::
	goto J_MartSignScript
J_EcruteakCityHiddenHyperPotion::
	finditem ITEM_HYPER_POTION
	return
J_UnusedMissingDaughterText::
	.string "Oh, no. Oh, no…\pMy daughter is\nmissing.\pNo… She couldn't\nhave gone to the\lBURNED TOWER.\pI told her not to\ngo near it…\pPeople seem to\ndisappear there…\pOh, what should I\ndo…?$"
J_EcruteakCityGramps1Text::
	.string "ECRUTEAK used to\nhave two towers:\pone each in the\neast and west.$"
J_EcruteakCityGramps2Text::
	.string "Ah, child.\nHave you learned\pto dance like the\nKIMONO GIRLS?\pIf you go to their\nDANCE THEATER, an\podd old man will\ngive you something\lnice, I hear.$"
J_EcruteakCityLass1Text::
	.string "I'm going to prac-\ntice at the DANCE\pTHEATER. Care to\njoin me?$"
J_EcruteakCityLass2Text::
	.string "The tower that\nused to be here…\pMy grandma told me\nit used to be much\ltaller.$"
J_EcruteakCityLass2Text_ReleasedBeasts::
	.string "Three big POKéMON\nran off in differ-\lent directions.\lWhat were they?$"
J_EcruteakCityFisherText::
	.string "I heard a rumor\nabout OLIVINE\lLIGHTHOUSE.\pThe POKéMON that\nserves as the\pbeacon fell ill.\nSounds like they\lare in trouble.$"
J_EcruteakCityFisherText_JasmineReturned::
	.string "The POKéMON at\nOLIVINE LIGHTHOUSE\lhas been cured.\pBoats can safely\nsail out to sea at\lnight again.$"
J_EcruteakCityYoungsterText::
	.string "I hear POKéMON are\nrampaging at the\pLAKE OF RAGE. I'd\nlike to see that.$"
J_EcruteakCityGramps3Text::
	.string "In the distant\npast…\pThis tower burned\nin a fire. Three\pnameless POKéMON\nperished in it.\pA rainbow-colored\nPOKéMON descended\pfrom the sky and\nresurrected them…\pIt's a legend that\nhas been passed\pdown by ECRUTEAK\nGYM LEADERS.\pMe?\pI was a trainer\nway back when.\lHohoho!$"
J_EcruteakCitySignText::
	.string "ECRUTEAK CITY\nA Historical City\pWhere the Past\nMeets the Present$"
J_TinTowerSignText::
	.string "TIN TOWER\pA legendary POKé-\nMON is said to\lroost here.$"
J_EcruteakGymSignText::
	.string "ECRUTEAK CITY\nPOKéMON GYM\lLEADER: MORTY\pThe Mystic Seer of\nthe Future$"
J_EcruteakDanceTheaterSignText::
	.string "ECRUTEAK DANCE\nTHEATER$"
J_BurnedTowerSignText::
	.string "BURNED TOWER\pIt was destroyed\nby a mysterious\lfire.\pPlease stay away,\nas it is unsafe.$"
J_EcruteakCity_MapEvents::
