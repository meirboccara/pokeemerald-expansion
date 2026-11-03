@ KJH: translated from pokecrystal maps/CianwoodCity.asm by kjh_tools/johto

JohtoCianwoodCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoCianwoodCity_OnTransition
	.byte 0

JohtoCianwoodCity_OnTransition:
	call J_CianwoodCityFlypointAndSuicuneCallback
	end

J_W_CianwoodCityYoungster::
	lock
	call J_CianwoodCityYoungster
	release
	end

J_W_CianwoodCityPokefanM::
	lock
	call J_CianwoodCityPokefanM
	release
	end

J_W_CianwoodCityLass::
	lock
	call J_CianwoodCityLass
	release
	end

J_W_CianwoodCityRock::
	lock
	call J_CianwoodCityRock
	release
	end

J_W_CianwoodCityChucksWife::
	lock
	call J_CianwoodCityChucksWife
	release
	end

J_C_CianwoodCitySuicuneAndEusine::
	lockall
	call J_CianwoodCitySuicuneAndEusine
	releaseall
	end

J_S_CianwoodCitySign::
	lockall
	call J_CianwoodCitySign
	releaseall
	end

J_S_CianwoodGymSign::
	lockall
	call J_CianwoodGymSign
	releaseall
	end

J_S_CianwoodPokecenterSign::
	lockall
	call J_CianwoodPokecenterSign
	releaseall
	end

J_S_CianwoodPharmacySign::
	lockall
	call J_CianwoodPharmacySign
	releaseall
	end

J_S_CianwoodPhotoStudioSign::
	lockall
	call J_CianwoodPhotoStudioSign
	releaseall
	end

J_S_CianwoodPokeSeerSign::
	lockall
	call J_CianwoodPokeSeerSign
	releaseall
	end

J_CianwoodCity_MapScripts::
J_CianwoodCityNoop1Scene::
	return
J_CianwoodCityNoop2Scene::
	return
J_CianwoodCityFlypointAndSuicuneCallback::
	setflag FLAG_J_ENGINE_FLYPOINT_CIANWOOD
	setflag FLAG_J_EUSINE_IN_BURNED_TOWER
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOUGHT_EUSINE, J_L583
	setvar VAR_RESULT, 1
J_L583:
	goto_if_eq VAR_RESULT, 0, J_CianwoodCityFlypointAndSuicuneCallback_Done
	setflag FLAG_J_CIANWOOD_CITY_EUSINE
J_CianwoodCityFlypointAndSuicuneCallback_Done:
	return
J_CianwoodCitySuicuneAndEusine::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	delay 15
	playse SE_WARP_OUT
	applymovement 12, J_CianwoodCitySuicuneApproachMovement
	waitmovement 12
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	delay 15
	playse SE_WARP_OUT
	applymovement 12, J_CianwoodCitySuicuneDepartMovement
	waitmovement 12
	removeobject 12
	delay 10
	setvar VAR_J_SCENE_CIANWOOD_CITY, 0
	clearflag FLAG_J_SAW_SUICUNE_ON_ROUTE_42
	setvar VAR_J_SCENE_ROUTE_42, 1
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOUGHT_EUSINE, J_L584
	setvar VAR_RESULT, 1
J_L584:
	goto_if_ne VAR_RESULT, 0, J_CianwoodCitySuicuneAndEusine_Done
	setflag FLAG_J_FOUGHT_EUSINE
	playbgm MUS_RG_ENCOUNTER_BOY, FALSE
	addobject 11
	applymovement 11, J_CianwoodCityEusineApproachMovement
	waitmovement 11
	message J_EusineSuicuneText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_LAST_TALKED, 11
	trainerbattle_no_intro TRAINER_J_MYSTICALMAN_EUSINE, J_EusineBeatenText
	playbgm MUS_RG_ENCOUNTER_BOY, FALSE
	message J_EusineAfterText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 11, J_CianwoodCityEusineDepartMovement
	waitmovement 11
	removeobject 11
	delay 20
	fadeoutbgm 0
	fadedefaultbgm
	delay 10
J_CianwoodCitySuicuneAndEusine_Done:
	return
J_CianwoodCityChucksWife::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_HM02_FLY, J_L585
	setvar VAR_RESULT, 1
J_L585:
	goto_if_ne VAR_RESULT, 0, J_CianwoodCityChucksWife_GotFly
	message J_ChucksWifeEasierToFlyText
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_CHUCK, J_L586
	setvar VAR_RESULT, 1
J_L586:
	goto_if_ne VAR_RESULT, 0, J_CianwoodCityChucksWife_BeatChuck
	message J_ChucksWifeBeatChuckText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodCityChucksWife_BeatChuck:
	message J_ChucksWifeGiveHMText
	waitmessage
	waitbuttonpress
	giveitem ITEM_HM02, 1
	goto_if_eq VAR_RESULT, 0, J_CianwoodCityChucksWife_Done
	setflag FLAG_J_GOT_HM02_FLY
	message J_ChucksWifeFlySpeechText
	waitmessage
	waitbuttonpress
J_CianwoodCityChucksWife_GotFly:
	message J_ChucksWifeChubbyText
	waitmessage
	waitbuttonpress
J_CianwoodCityChucksWife_Done:
	closemessage
	return
J_CianwoodCityYoungster::
	faceplayer
	message J_CianwoodCityYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodCityPokefanM::
	faceplayer
	message J_CianwoodCityPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodCityLass::
	faceplayer
	message J_CianwoodCityLassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodCityUnusedScript::
	faceplayer
	message J_CianwoodCityUnusedText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodCitySign::
	message J_CianwoodCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodGymSign::
	message J_CianwoodGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodPharmacySign::
	message J_CianwoodPharmacySignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodPhotoStudioSign::
	message J_CianwoodPhotoStudioSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodPokeSeerSign::
	message J_CianwoodPokeSeerSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodPokecenterSign::
	goto J_PokecenterSignScript
J_CianwoodCityRock::
	goto EventScript_RockSmash
J_CianwoodCityHiddenRevive::
	finditem ITEM_REVIVE
	return
J_CianwoodCityHiddenMaxEther::
	finditem ITEM_MAX_ETHER
	return
J_CianwoodCitySuicuneApproachMovement::
	jump_down
	jump_down
	jump_right
	step_end
J_CianwoodCitySuicuneDepartMovement::
	jump_right
	jump_up
	jump_right
	jump_right
	step_end
J_CianwoodCityEusineApproachMovement::
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
J_CianwoodCityEusineDepartMovement::
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
J_ChucksWifeEasierToFlyText::
	.string "You crossed the\nsea to get here?\pThat must have\nbeen hard.\pIt would be much\neasier if your\pPOKéMON knew how\nto FLY…$"
J_ChucksWifeBeatChuckText::
	.string "But you can't use\nFLY without this\lcity's GYM BADGE.\pIf you beat the\nGYM LEADER here,\lcome see me.\pI'll have a nice\ngift for you.$"
J_ChucksWifeGiveHMText::
	.string "That's CIANWOOD's\nGYM BADGE!\pThen you should\ntake this HM.$"
J_ChucksWifeFlySpeechText::
	.string "Teach FLY to your\nPOKéMON.\pYou will be able\nto FLY instantly\pto anywhere you \nhave visited.$"
J_ChucksWifeChubbyText::
	.string "My husband lost to\nyou, so he needs\lto train harder.\pThat's good, since\nhe was getting a\llittle chubby.$"
J_CianwoodCityYoungsterText::
	.string "If you use FLY,\nyou can get back\pto OLIVINE in-\nstantly.$"
J_CianwoodCityPokefanMText::
	.string "Boulders to the\nnorth of town can\lbe crushed.\pThey may be hiding\nsomething.\pYour POKéMON could\nuse ROCK SMASH to\lbreak them.$"
J_CianwoodCityLassText::
	.string "CHUCK, the GYM\nLEADER, spars with\phis fighting POKé-\nMON.$"
J_CianwoodCityUnusedText::
	.string "There are several\nislands between\lhere and OLIVINE.\pA mythical sea\ncreature supposed-\lly lives there.$"
J_EusineSuicuneText::
	.string "EUSINE: Yo,\n{PLAYER}.\pWasn't that\nSUICUNE just now?\pI only caught a\nquick glimpse, but\pI thought I saw\nSUICUNE running on\lthe waves.\pSUICUNE is beau-\ntiful and grand.\pAnd it races\nthrough towns and\proads at simply\nawesome speeds.\pIt's wonderful…\pI want to see\nSUICUNE up close…\pI've decided.\pI'll battle you as\na trainer to earn\lSUICUNE's respect!\pCome on, {PLAYER}.\nLet's battle now!$"
J_EusineBeatenText::
	.string "I hate to admit\nit, but you win.$"
J_EusineAfterText::
	.string "You're amazing,\n{PLAYER}!\pNo wonder POKéMON\ngravitate to you.\pI get it now.\pI'm going to keep\nsearching for\lSUICUNE.\pI'm sure we'll see\neach other again.\pSee you around!$"
J_CianwoodCitySignText::
	.string "CIANWOOD CITY\pA Port Surrounded\nby Rough Seas$"
J_CianwoodGymSignText::
	.string "CIANWOOD CITY\nPOKéMON GYM\pLEADER: CHUCK\pHis Roaring Fists\nDo the Talking$"
J_CianwoodPharmacySignText::
	.string "500 Years of\nTradition\pCIANWOOD CITY\nPHARMACY\pWe Await Your\nMedicinal Queries$"
J_CianwoodPhotoStudioSignText::
	.string "CIANWOOD CITY\nPHOTO STUDIO\pTake a Snapshot as\na Keepsake!$"
J_CianwoodPokeSeerSignText::
	.string "THE POKé SEER\nAHEAD$"
J_CianwoodCity_MapEvents::
