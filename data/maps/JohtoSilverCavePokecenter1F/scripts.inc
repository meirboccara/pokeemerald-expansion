@ KJH: translated from pokecrystal maps/SilverCavePokecenter1F.asm by kjh_tools/johto

JohtoSilverCavePokecenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoSilverCavePokecenter1F_OnTransition
	.byte 0

JohtoSilverCavePokecenter1F_OnTransition:
	setrespawn HEAL_LOCATION_J_SILVER_CAVE
	end

J_W_SilverCavePokecenter1FNurseScript::
	lock
	call J_SilverCavePokecenter1FNurseScript
	release
	end

J_W_SilverCavePokecenter1FGrannyScript::
	lock
	call J_SilverCavePokecenter1FGrannyScript
	release
	end

J_SilverCavePokecenter1F_MapScripts::
J_SilverCavePokecenter1FNurseScript::
	goto J_Std_Nurse
J_SilverCavePokecenter1FGrannyScript::
	faceplayer
	message J_SilverCavePokecenter1FGrannyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SilverCavePokecenter1FGrannyText::
	.string "Trainers who seek\npower climb MT.\pSILVER despite its\nmany dangers…\pWith their trusted\nPOKéMON, they must\pfeel they can go\nanywhere…$"
J_SilverCavePokecenter1F_MapEvents::
