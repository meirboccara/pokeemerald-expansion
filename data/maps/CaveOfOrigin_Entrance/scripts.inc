CaveOfOrigin_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, CaveOfOrigin_Entrance_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, CaveOfOrigin_Entrance_OnTransition
	.byte 0

@ KJH (ENG-10): Maxie, Archie and Giovanni wait here once the 8th badge is won (data/scripts/kjh_story.inc)
CaveOfOrigin_Entrance_OnTransition:
	call KJH_EventScript_Story_ShowdownSetup
	end

CaveOfOrigin_Entrance_OnResume:
	setescapewarp MAP_SOOTOPOLIS_CITY, 31, 17
	end

