@ KJH: translated from pokecrystal maps/WhirlIslandLugiaChamber.asm by kjh_tools/johto

JohtoWhirlIslandLugiaChamber_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoWhirlIslandLugiaChamber_OnTransition
	.byte 0

JohtoWhirlIslandLugiaChamber_OnTransition:
	call J_WhirlIslandLugiaChamberLugiaCallback
	end

J_W_Lugia::
	lock
	call J_Lugia
	release
	end

J_WhirlIslandLugiaChamber_MapScripts::
J_WhirlIslandLugiaChamberLugiaCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOUGHT_LUGIA, J_L241
	setvar VAR_RESULT, 1
J_L241:
	goto_if_ne VAR_RESULT, 0, J_WhirlIslandLugiaChamberLugiaCallback_NoAppear
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_SILVER_WING, J_L242
	setvar VAR_RESULT, 1
J_L242:
	goto_if_ne VAR_RESULT, 0, J_WhirlIslandLugiaChamberLugiaCallback_Appear
	goto J_WhirlIslandLugiaChamberLugiaCallback_NoAppear
J_WhirlIslandLugiaChamberLugiaCallback_Appear:
	clearflag FLAG_J_WHIRL_ISLAND_LUGIA_CHAMBER_LUGIA
	return
J_WhirlIslandLugiaChamberLugiaCallback_NoAppear:
	setflag FLAG_J_WHIRL_ISLAND_LUGIA_CHAMBER_LUGIA
	return
J_Lugia::
	faceplayer
	message J_LugiaText
	waitmessage
	playmoncry SPECIES_LUGIA, CRY_MODE_NORMAL
	waitmoncry
	delay 15
	closemessage
	setflag FLAG_J_FOUGHT_LUGIA
	setwildbattle SPECIES_LUGIA, 95
	kjh_legendaryboss @ KJH (CF-13)
	dowildbattle
	removeobject 1
	return
J_LugiaText::
	.string "Gyaaas!$"
J_WhirlIslandLugiaChamber_MapEvents::
