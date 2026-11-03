@ KJH: translated from pokecrystal maps/BlackthornPokecenter1F.asm by kjh_tools/johto

JohtoBlackthornPokecenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoBlackthornPokecenter1F_OnTransition
	.byte 0

JohtoBlackthornPokecenter1F_OnTransition:
	setrespawn HEAL_LOCATION_J_BLACKTHORN
	end

J_W_BlackthornPokecenter1FNurseScript::
	lock
	call J_BlackthornPokecenter1FNurseScript
	release
	end

J_W_BlackthornPokecenter1FGentlemanScript::
	lock
	call J_BlackthornPokecenter1FGentlemanScript
	release
	end

J_W_BlackthornPokecenter1FTwinScript::
	lock
	call J_BlackthornPokecenter1FTwinScript
	release
	end

J_W_BlackthornPokecenter1FCooltrainerMScript::
	lock
	call J_BlackthornPokecenter1FCooltrainerMScript
	release
	end

J_BlackthornPokecenter1F_MapScripts::
J_BlackthornPokecenter1FNurseScript::
	goto J_Std_Nurse
J_BlackthornPokecenter1FGentlemanScript::
	faceplayer
	message J_BlackthornPokecenter1FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornPokecenter1FTwinScript::
	faceplayer
	message J_BlackthornPokecenter1FTwinText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornPokecenter1FCooltrainerMScript::
	goto J_HappinessCheckScript
J_BlackthornPokecenter1FGentlemanText::
	.string "Deep inside far-\noff INDIGO PLATEAU\pis the POKéMON\nLEAGUE.\pI hear the best\ntrainers gather\pthere from around\nthe country.$"
J_BlackthornPokecenter1FTwinText::
	.string "There was this\nmove I just had\pto teach my POKé-\nMON.\pSo I got the MOVE\nDELETER to make it\lforget an HM move.$"
J_BlackthornPokecenter1F_MapEvents::
