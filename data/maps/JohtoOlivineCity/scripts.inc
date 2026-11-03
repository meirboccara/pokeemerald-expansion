@ KJH: translated from pokecrystal maps/OlivineCity.asm by kjh_tools/johto

JohtoOlivineCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoOlivineCity_OnTransition
	.byte 0

JohtoOlivineCity_OnTransition:
	call J_OlivineCityFlypointCallback
	end

J_W_OlivineCitySailor1Script::
	lock
	call J_OlivineCitySailor1Script
	release
	end

J_W_OlivineCityStandingYoungsterScript::
	lock
	call J_OlivineCityStandingYoungsterScript
	release
	end

J_W_OlivineCitySailor2Script::
	lock
	call J_OlivineCitySailor2Script
	release
	end

J_C_OlivineCityRivalSceneTop::
	lockall
	call J_OlivineCityRivalSceneTop
	releaseall
	end

J_C_OlivineCityRivalSceneBottom::
	lockall
	call J_OlivineCityRivalSceneBottom
	releaseall
	end

J_S_OlivineCitySign::
	lockall
	call J_OlivineCitySign
	releaseall
	end

J_S_OlivineCityPortSign::
	lockall
	call J_OlivineCityPortSign
	releaseall
	end

J_S_OlivineGymSign::
	lockall
	call J_OlivineGymSign
	releaseall
	end

J_S_OlivineLighthouseSign::
	lockall
	call J_OlivineLighthouseSign
	releaseall
	end

J_S_OlivineCityBattleTowerSign::
	lockall
	call J_OlivineCityBattleTowerSign
	releaseall
	end

J_S_OlivineCityPokecenterSign::
	lockall
	call J_OlivineCityPokecenterSign
	releaseall
	end

J_S_OlivineCityMartSign::
	lockall
	call J_OlivineCityMartSign
	releaseall
	end

J_OlivineCity_MapScripts::
J_OlivineCityNoop1Scene::
	return
J_OlivineCityNoop2Scene::
	return
J_OlivineCityFlypointCallback::
	setflag FLAG_J_ENGINE_FLYPOINT_OLIVINE
	return
J_OlivineCityRivalSceneTop::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	fadeoutbgm 0
	delay 15
	playse SE_DOOR
	addobject 4
	waitse
	applymovement 4, J_OlivineCityRivalApproachesTopMovement
	waitmovement 4
	playbgm MUS_RG_ENCOUNTER_RIVAL, FALSE
	message J_OlivineCityRivalText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_OlivineCityPlayerStepsAsideTopMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement 4, J_OlivineCityRivalLeavesTopMovement
	waitmovement 4
	setvar VAR_J_SCENE_OLIVINE_CITY, 1
	removeobject 4
	fadedefaultbgm
	return
J_OlivineCityRivalSceneBottom::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	fadeoutbgm 0
	delay 15
	playse SE_DOOR
	addobject 4
	waitse
	applymovement 4, J_OlivineCityRivalApproachesBottomMovement
	waitmovement 4
	playbgm MUS_RG_ENCOUNTER_RIVAL, FALSE
	message J_OlivineCityRivalText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_OlivineCityPlayerStepsAsideBottomMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement 4, J_OlivineCityRivalLeavesBottomMovement
	waitmovement 4
	removeobject 4
	setvar VAR_J_SCENE_OLIVINE_CITY, 1
	fadedefaultbgm
	return
J_OlivineCitySailor1Script::
	faceplayer
	message J_OlivineCitySailor1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineCityStandingYoungsterScript::
	faceplayer
	random 2
	goto_if_eq VAR_RESULT, 0, J_OlivineCityStandingYoungsterScript_FiftyFifty
	message J_OlivineCityStandingYoungsterPokegearText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineCityStandingYoungsterScript_FiftyFifty:
	message J_OlivineCityStandingYoungsterPokedexText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineCitySailor2Script::
	faceplayer
	message J_OlivineCitySailor2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineCitySign::
	message J_OlivineCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineCityPortSign::
	message J_OlivineCityPortSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineGymSign::
	message J_OlivineGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineLighthouseSign::
	message J_OlivineLighthouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineCityBattleTowerSign::
	message J_OlivineCityBattleTowerSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineCityPokecenterSign::
	goto J_PokecenterSignScript
J_OlivineCityMartSign::
	goto J_MartSignScript
J_OlivineCityRivalApproachesTopMovement::
	walk_down
	walk_right
	walk_right
	step_end
J_OlivineCityRivalApproachesBottomMovement::
	walk_down
	walk_down
	walk_right
	walk_right
	step_end
J_OlivineCityRivalLeavesTopMovement::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
J_OlivineCityRivalLeavesBottomMovement::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
J_OlivineCityPlayerStepsAsideTopMovement::
	walk_down
	face_up
	step_end
J_OlivineCityPlayerStepsAsideBottomMovement::
	walk_up
	face_down
	step_end
J_OlivineCityRivalText::
	.string "…\pYou again?\pThere's no need to\npanic. I don't\pbother with wimps\nlike you.\pSpeaking of weak-\nlings, the city's\pGYM LEADER isn't\nhere.\pSupposedly taking\ncare of a sick\pPOKéMON at the\nLIGHTHOUSE.\pHumph! Boo-hoo!\nJust let sick\lPOKéMON go!\pA POKéMON that\ncan't battle is\lworthless!\pWhy don't you go\ntrain at the\lLIGHTHOUSE?\pWho knows. It may\nmake you a bit\lless weak!$"
J_OlivineCitySailor1Text::
	.string "Dark roads are\ndangerous at\lnight.\pBut in the pitch-\nblack of night,\pthe sea is even\nmore treacherous!\pWithout the beacon\nof the LIGHTHOUSE\pto guide it, no\nship can sail.$"
J_OlivineCityStandingYoungsterPokegearText::
	.string "That thing you\nhave--it's a POKé-\lGEAR, right? Wow,\lthat's cool.$"
J_OlivineCityStandingYoungsterPokedexText::
	.string "Wow, you have a\nPOKéDEX!\pThat is just so\nawesome.$"
J_OlivineCitySailor2Text::
	.string "The sea is sweet!\pSunsets on the sea\nare marvelous!\pSing with me! \nYo-ho! Blow the\lman down!…$"
J_OlivineCitySignText::
	.string "OLIVINE CITY\pThe Port Closest\nto Foreign Lands$"
J_OlivineCityPortSignText::
	.string "OLIVINE PORT\nFAST SHIP PIER$"
J_OlivineGymSignText::
	.string "OLIVINE CITY\nPOKéMON GYM\lLEADER: JASMINE\pThe Steel-Clad\nDefense Girl$"
J_OlivineLighthouseSignText::
	.string "OLIVINE LIGHTHOUSE\nAlso known as the\lGLITTER LIGHTHOUSE$"
J_OlivineCityBattleTowerSignText::
	.string "BATTLE TOWER AHEAD\nOpening Now!$"
J_OlivineCityBattleTowerSignText_NotYetOpen::
	.string "BATTLE TOWER AHEAD$"
J_OlivineCity_MapEvents::
