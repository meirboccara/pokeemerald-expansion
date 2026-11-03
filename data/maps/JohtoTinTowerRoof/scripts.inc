@ KJH: translated from pokecrystal maps/TinTowerRoof.asm by kjh_tools/johto

JohtoTinTowerRoof_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoTinTowerRoof_OnTransition
	.byte 0

JohtoTinTowerRoof_OnTransition:
	call J_TinTowerRoofHoOhCallback
	end

J_W_TinTowerHoOh::
	lock
	call J_TinTowerHoOh
	release
	end

J_TinTowerRoof_MapScripts::
J_TinTowerRoofHoOhCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOUGHT_HO_OH, J_L578
	setvar VAR_RESULT, 1
J_L578:
	goto_if_ne VAR_RESULT, 0, J_TinTowerRoofHoOhCallback_NoAppear
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_RAINBOW_WING, J_L579
	setvar VAR_RESULT, 1
J_L579:
	goto_if_ne VAR_RESULT, 0, J_TinTowerRoofHoOhCallback_Appear
	goto J_TinTowerRoofHoOhCallback_NoAppear
J_TinTowerRoofHoOhCallback_Appear:
	clearflag FLAG_J_TIN_TOWER_ROOF_HO_OH
	return
J_TinTowerRoofHoOhCallback_NoAppear:
	setflag FLAG_J_TIN_TOWER_ROOF_HO_OH
	return
J_TinTowerHoOh::
	faceplayer
	message J_HoOhText
	waitmessage
	playmoncry SPECIES_HO_OH, CRY_MODE_NORMAL
	waitmoncry
	delay 15
	closemessage
	setflag FLAG_J_FOUGHT_HO_OH
	setwildbattle SPECIES_HO_OH, 80
	dowildbattle
	removeobject 1
	setflag FLAG_J_SET_WHEN_FOUGHT_HO_OH
	return
J_HoOhText::
	.string "Shaoooh!$"
J_TinTowerRoof_MapEvents::
