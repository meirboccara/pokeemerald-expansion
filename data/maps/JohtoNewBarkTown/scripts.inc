@ KJH: translated from pokecrystal maps/NewBarkTown.asm by kjh_tools/johto

JohtoNewBarkTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoNewBarkTown_OnTransition
	.byte 0

JohtoNewBarkTown_OnTransition:
	call J_NewBarkTownFlypointCallback
	end

J_W_NewBarkTownTeacherScript::
	lock
	call J_NewBarkTownTeacherScript
	release
	end

J_W_NewBarkTownFisherScript::
	lock
	call J_NewBarkTownFisherScript
	release
	end

J_W_NewBarkTownRivalScript::
	lock
	call J_NewBarkTownRivalScript
	release
	end

J_C_NewBarkTown_TeacherStopsYouScene1::
	lockall
	call J_NewBarkTown_TeacherStopsYouScene1
	releaseall
	end

J_C_NewBarkTown_TeacherStopsYouScene2::
	lockall
	call J_NewBarkTown_TeacherStopsYouScene2
	releaseall
	end

J_S_NewBarkTownSign::
	lockall
	call J_NewBarkTownSign
	releaseall
	end

J_S_NewBarkTownPlayersHouseSign::
	lockall
	call J_NewBarkTownPlayersHouseSign
	releaseall
	end

J_S_NewBarkTownElmsLabSign::
	lockall
	call J_NewBarkTownElmsLabSign
	releaseall
	end

J_S_NewBarkTownElmsHouseSign::
	lockall
	call J_NewBarkTownElmsHouseSign
	releaseall
	end

J_NewBarkTown_MapScripts::
J_NewBarkTownNoop1Scene::
	return
J_NewBarkTownNoop2Scene::
	return
J_NewBarkTownFlypointCallback::
	setflag FLAG_J_ENGINE_FLYPOINT_NEW_BARK
	clearflag FLAG_J_FIRST_TIME_BANKING_WITH_MOM
	return
J_NewBarkTown_TeacherStopsYouScene1::
	playbgm MUS_RG_SLOW_PALLET, FALSE
	turnobject 1, DIR_WEST
	message J_Text_WaitPlayer
	waitmessage
	waitbuttonpress
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement 1, J_NewBarkTown_TeacherRunsToYouMovement1
	waitmovement 1
	message J_Text_WhatDoYouThinkYoureDoing
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_NewBarkTown_TeacherBringsYouBackMovement1
	applymovement OBJ_EVENT_ID_PLAYER, J_NewBarkTown_TeacherBringsYouBackMovement1
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement 1
	message J_Text_ItsDangerousToGoAlone
	waitmessage
	waitbuttonpress
	closemessage
	fadedefaultbgm
	return
J_NewBarkTown_TeacherStopsYouScene2::
	playbgm MUS_RG_SLOW_PALLET, FALSE
	turnobject 1, DIR_WEST
	message J_Text_WaitPlayer
	waitmessage
	waitbuttonpress
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement 1, J_NewBarkTown_TeacherRunsToYouMovement2
	waitmovement 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	message J_Text_WhatDoYouThinkYoureDoing
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_NewBarkTown_TeacherBringsYouBackMovement2
	applymovement OBJ_EVENT_ID_PLAYER, J_NewBarkTown_TeacherBringsYouBackMovement2
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement 1
	message J_Text_ItsDangerousToGoAlone
	waitmessage
	waitbuttonpress
	closemessage
	fadedefaultbgm
	return
J_NewBarkTownTeacherScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TALKED_TO_MOM_AFTER_MYSTERY_EGG_QUEST, J_L618
	setvar VAR_RESULT, 1
J_L618:
	goto_if_ne VAR_RESULT, 0, J_NewBarkTownTeacherScript_CallMom
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_MYSTERY_EGG_TO_ELM, J_L619
	setvar VAR_RESULT, 1
J_L619:
	goto_if_ne VAR_RESULT, 0, J_NewBarkTownTeacherScript_TellMomYoureLeaving
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_KJH_GOT_JOHTO_STARTER, J_L620
	setvar VAR_RESULT, 1
J_L620:
	goto_if_ne VAR_RESULT, 0, J_NewBarkTownTeacherScript_MonIsAdorable
	message J_Text_GearIsImpressive
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NewBarkTownTeacherScript_MonIsAdorable:
	message J_Text_YourMonIsAdorable
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NewBarkTownTeacherScript_TellMomYoureLeaving:
	message J_Text_TellMomIfLeaving
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NewBarkTownTeacherScript_CallMom:
	message J_Text_CallMomOnGear
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NewBarkTownFisherScript::
	faceplayer
	message J_Text_ElmDiscoveredNewMon
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NewBarkTownRivalScript::
	message J_NewBarkTownRivalText1
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 3, DIR_WEST
	message J_NewBarkTownRivalText2
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_NewBarkTown_RivalPushesYouAwayMovement
	applymovement 3, J_NewBarkTown_RivalPushesYouAwayMovement
	waitmovement 3
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 5
	turnobject 3, DIR_SOUTH
	delay 5
	playse SE_M_COMET_PUNCH
	applymovement OBJ_EVENT_ID_PLAYER, J_NewBarkTown_RivalShovesYouOutMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 3, J_NewBarkTown_RivalReturnsToTheShadowsMovement
	waitmovement 3
	return
J_NewBarkTownSign::
	message J_NewBarkTownSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NewBarkTownPlayersHouseSign::
	message J_NewBarkTownPlayersHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NewBarkTownElmsLabSign::
	message J_NewBarkTownElmsLabSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NewBarkTownElmsHouseSign::
	message J_NewBarkTownElmsHouseSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NewBarkTown_TeacherRunsToYouMovement1::
	walk_left
	walk_left
	walk_left
	walk_left
	step_end
J_NewBarkTown_TeacherRunsToYouMovement2::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_down
	step_end
J_NewBarkTown_TeacherBringsYouBackMovement1::
	walk_right
	walk_right
	walk_right
	walk_right
	face_left
	step_end
J_NewBarkTown_TeacherBringsYouBackMovement2::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	face_left
	step_end
J_NewBarkTown_RivalPushesYouAwayMovement::
	face_up
	walk_down
	step_end
J_NewBarkTown_RivalShovesYouOutMovement::
	face_up
	lock_facing_direction
	jump_2_down
	unlock_facing_direction
	step_end
J_NewBarkTown_RivalReturnsToTheShadowsMovement::
	walk_right
	step_end
J_Text_GearIsImpressive::
	.string "Wow, your POKéGEAR\nis impressive!\pDid your mom get\nit for you?$"
J_Text_WaitPlayer::
	.string "Wait, {PLAYER}!$"
J_Text_WhatDoYouThinkYoureDoing::
	.string "What do you think\nyou're doing?$"
J_Text_ItsDangerousToGoAlone::
	.string "It's dangerous to\ngo out without a\lPOKéMON!\pWild POKéMON\njump out of the\pgrass on the way\nto the next town.$"
J_Text_YourMonIsAdorable::
	.string "Oh! Your POKéMON\nis adorable!\lI wish I had one!$"
J_Text_TellMomIfLeaving::
	.string "Hi, {PLAYER}!\nLeaving again?\pYou should tell\nyour mom if you\lare leaving.$"
J_Text_CallMomOnGear::
	.string "Call your mom on\nyour POKéGEAR to\plet her know how\nyou're doing.$"
J_Text_ElmDiscoveredNewMon::
	.string "Yo, {PLAYER}!\pI hear PROF.ELM\ndiscovered some\lnew POKéMON.$"
J_NewBarkTownRivalText1::
	.string "……\pSo this is the\nfamous ELM POKéMON\lLAB…$"
J_NewBarkTownRivalText2::
	.string "…What are you\nstaring at?$"
J_NewBarkTownSignText::
	.string "NEW BARK TOWN\pThe Town Where the\nWinds of a New\lBeginning Blow$"
J_NewBarkTownPlayersHouseSignText::
	.string "{PLAYER}'s House$"
J_NewBarkTownElmsLabSignText::
	.string "ELM POKéMON LAB$"
J_NewBarkTownElmsHouseSignText::
	.string "ELM'S HOUSE$"
J_NewBarkTown_MapEvents::
