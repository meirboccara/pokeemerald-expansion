@ KJH: translated from pokecrystal maps/SilverCaveOutside.asm by kjh_tools/johto

JohtoSilverCaveOutside_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoSilverCaveOutside_OnTransition
	.byte 0

JohtoSilverCaveOutside_OnTransition:
	call J_SilverCaveOutsideFlypointCallback
	end

J_S_MtSilverPokecenterSign::
	lockall
	call J_MtSilverPokecenterSign
	releaseall
	end

J_S_MtSilverSign::
	lockall
	call J_MtSilverSign
	releaseall
	end

J_SilverCaveOutside_MapScripts::
J_SilverCaveOutsideFlypointCallback::
	setflag FLAG_J_ENGINE_FLYPOINT_SILVER_CAVE
	return
J_MtSilverPokecenterSign::
	goto J_PokecenterSignScript
J_MtSilverSign::
	message J_MtSilverSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SilverCaveOutsideHiddenFullRestore::
	finditem ITEM_FULL_RESTORE
	return
J_MtSilverSignText::
	.string "MT.SILVER$"
J_SilverCaveOutside_MapEvents::
