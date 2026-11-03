@ KJH: translated from pokecrystal maps/OlivinePokecenter1F.asm by kjh_tools/johto

JohtoOlivinePokecenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoOlivinePokecenter1F_OnTransition
	.byte 0

JohtoOlivinePokecenter1F_OnTransition:
	setrespawn HEAL_LOCATION_J_OLIVINE
	end

J_W_OlivinePokecenter1FNurseScript::
	lock
	call J_OlivinePokecenter1FNurseScript
	release
	end

J_W_OlivinePokecenter1FFishingGuruScript::
	lock
	call J_OlivinePokecenter1FFishingGuruScript
	release
	end

J_W_OlivinePokecenter1FFisherScript::
	lock
	call J_OlivinePokecenter1FFisherScript
	release
	end

J_W_OlivinePokecenter1FTeacherScript::
	lock
	call J_OlivinePokecenter1FTeacherScript
	release
	end

J_OlivinePokecenter1F_MapScripts::
J_OlivinePokecenter1FNurseScript::
	goto J_Std_Nurse
J_OlivinePokecenter1FFishingGuruScript::
	goto J_HappinessCheckScript
J_OlivinePokecenter1FFisherScript::
	faceplayer
	message J_OlivinePokecenter1FFisherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivinePokecenter1FTeacherScript::
	faceplayer
	message J_OlivinePokecenter1FTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivinePokecenter1FFisherText::
	.string "The SAILOR in the\nOLIVINE CAFE next\pdoor is really\ngenerous.\pHe taught my\nPOKéMON STRENGTH.\pNow it can move\nbig boulders.$"
J_OlivinePokecenter1FTeacherText::
	.string "There's a person\nin CIANWOOD CITY\lacross the sea.\pI heard him brag-\nging about his\lrare POKéMON.$"
J_OlivinePokecenter1F_MapEvents::
