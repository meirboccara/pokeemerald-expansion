@ KJH: translated from pokecrystal maps/PlayersHouse2F.asm by kjh_tools/johto

JohtoPlayersHouse2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoPlayersHouse2F_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, JohtoPlayersHouse2F_OnLoad
	.byte 0

JohtoPlayersHouse2F_OnTransition:
	call J_PlayersHouse2FInitializeRoomCallback
	end

JohtoPlayersHouse2F_OnLoad:
	call J_PlayersHouse2FSetUpTileDecorationsCallback
	end

J_W_PlayersHouseGameConsoleScript::
	lock
	call J_PlayersHouseGameConsoleScript
	release
	end

J_W_PlayersHouseDoll1Script::
	lock
	call J_PlayersHouseDoll1Script
	release
	end

J_W_PlayersHouseDoll2Script::
	lock
	call J_PlayersHouseDoll2Script
	release
	end

J_W_PlayersHouseBigDollScript::
	lock
	call J_PlayersHouseBigDollScript
	release
	end

J_S_PlayersHousePCScript::
	lockall
	call J_PlayersHousePCScript
	releaseall
	end

J_S_PlayersHouseRadioScript::
	lockall
	call J_PlayersHouseRadioScript
	releaseall
	end

J_S_PlayersHouseBookshelfScript::
	lockall
	call J_PlayersHouseBookshelfScript
	releaseall
	end

J_S_PlayersHousePosterScript::
	lockall
	goto_if_unset FLAG_J_PLAYERS_ROOM_POSTER, J_L698
	call J_PlayersHousePosterScript_Script
J_L698:
	releaseall
	end

J_PlayersHouse2F_MapScripts::
J_PlayersHouse2FNoopScene::
	return
J_PlayersHouse2FInitializeRoomCallback::
	setvar VAR_RESULT, 0
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_8
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_INITIALIZED_EVENTS, J_L652
	setvar VAR_RESULT, 1
J_L652:
	goto_if_ne VAR_RESULT, 0, J_PlayersHouse2FInitializeRoomCallback_SkipInitialization
	goto J_InitializeEventsScript
	return
J_PlayersHouse2FInitializeRoomCallback_SkipInitialization:
	return
J_PlayersHouse2FSetUpTileDecorationsCallback::
	setvar VAR_RESULT, 0
	return
J_PlayersHouseDoll1Script::
J_PlayersHouseDoll2Script::
J_PlayersHouseBigDollScript::
J_PlayersHouseGameConsoleScript::
J_PlayersHousePosterScript::
J_PlayersHousePosterScript_Script:
J_PlayersHouseRadioScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_KJH_GOT_JOHTO_STARTER, J_L653
	setvar VAR_RESULT, 1
J_L653:
	goto_if_ne VAR_RESULT, 0, J_PlayersHouseRadioScript_NormalRadio
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_LISTENED_TO_INITIAL_RADIO, J_L654
	setvar VAR_RESULT, 1
J_L654:
	goto_if_ne VAR_RESULT, 0, J_PlayersHouseRadioScript_AbbreviatedRadio
	playbgm MUS_SCHOOL, FALSE
	message J_PlayersRadioText1
	waitmessage
	delay 45
	message J_PlayersRadioText2
	waitmessage
	delay 45
	message J_PlayersRadioText3
	waitmessage
	delay 45
	fadenewbgm MUS_RG_PALLET
	message J_PlayersRadioText4
	waitmessage
	delay 45
	closemessage
	setflag FLAG_J_LISTENED_TO_INITIAL_RADIO
	return
J_PlayersHouseRadioScript_NormalRadio:
	goto J_Radio1Script
J_PlayersHouseRadioScript_AbbreviatedRadio:
	message J_PlayersRadioText4
	waitmessage
	delay 45
	closemessage
	return
J_PlayersHouseBookshelfScript::
	goto J_PictureBookshelfScript
J_PlayersHousePCScript::
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_PlayersHousePCScript_Warp
	closemessage
	return
J_PlayersHousePCScript_Warp:
	return
J_PlayersRadioText1::
	.string "PROF.OAK'S POKéMON\nTALK! Please tune\lin next time!$"
J_PlayersRadioText2::
	.string "POKéMON CHANNEL!$"
J_PlayersRadioText3::
	.string "This is DJ MARY,\nyour co-host!$"
J_PlayersRadioText4::
	.string "POKéMON!\nPOKéMON CHANNEL…$"
J_PlayersHouse2F_MapEvents::
