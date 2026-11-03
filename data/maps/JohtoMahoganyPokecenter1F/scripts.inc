@ KJH: translated from pokecrystal maps/MahoganyPokecenter1F.asm by kjh_tools/johto

JohtoMahoganyPokecenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoMahoganyPokecenter1F_OnTransition
	.byte 0

JohtoMahoganyPokecenter1F_OnTransition:
	setrespawn HEAL_LOCATION_J_MAHOGANY
	end

J_W_MahoganyPokecenter1FNurseScript::
	lock
	call J_MahoganyPokecenter1FNurseScript
	release
	end

J_W_MahoganyPokecenter1FPokefanMScript::
	lock
	call J_MahoganyPokecenter1FPokefanMScript
	release
	end

J_W_MahoganyPokecenter1FYoungsterScript::
	lock
	call J_MahoganyPokecenter1FYoungsterScript
	release
	end

J_W_MahoganyPokecenter1FCooltrainerFScript::
	lock
	call J_MahoganyPokecenter1FCooltrainerFScript
	release
	end

J_MahoganyPokecenter1F_MapScripts::
J_MahoganyPokecenter1FNurseScript::
	goto J_Std_Nurse
J_MahoganyPokecenter1FPokefanMScript::
	faceplayer
	message J_MahoganyPokecenter1FPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyPokecenter1FYoungsterScript::
	faceplayer
	message J_MahoganyPokecenter1FYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyPokecenter1FCooltrainerFScript::
	faceplayer
	message J_MahoganyPokecenter1FCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyPokecenter1FPokefanMText::
	.string "What's this? TEAM\nROCKET has come\lback?\pI saw some men in\nblack at LAKE OF\lRAGE…$"
J_MahoganyPokecenter1FYoungsterText::
	.string "I stop my POKéMON\nfrom evolving too\learly.\pI make them learn\ncertain moves be-\lfore I let them\levolve.$"
J_MahoganyPokecenter1FCooltrainerFText::
	.string "POKéMON do become\nstronger when they\pevolve, but they\nalso learn moves\lmore slowly.$"
J_MahoganyPokecenter1F_MapEvents::
