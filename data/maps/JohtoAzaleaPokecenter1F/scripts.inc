@ KJH: translated from pokecrystal maps/AzaleaPokecenter1F.asm by kjh_tools/johto

JohtoAzaleaPokecenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoAzaleaPokecenter1F_OnTransition
	.byte 0

JohtoAzaleaPokecenter1F_OnTransition:
	setrespawn HEAL_LOCATION_J_AZALEA
	end

J_W_AzaleaPokecenter1FNurseScript::
	lock
	call J_AzaleaPokecenter1FNurseScript
	release
	end

J_W_AzaleaPokecenter1FGentlemanScript::
	lock
	call J_AzaleaPokecenter1FGentlemanScript
	release
	end

J_W_AzaleaPokecenter1FFishingGuruScript::
	lock
	call J_AzaleaPokecenter1FFishingGuruScript
	release
	end

J_W_AzaleaPokecenter1FPokefanFScript::
	lock
	call J_AzaleaPokecenter1FPokefanFScript
	release
	end

J_AzaleaPokecenter1F_MapScripts::
J_AzaleaPokecenter1FNoopScene::
	return
J_AzaleaPokecenter1FNurseScript::
	goto J_Std_Nurse
J_AzaleaPokecenter1FGentlemanScript::
	faceplayer
	message J_AzaleaPokecenter1FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaPokecenter1FFishingGuruScript::
	faceplayer
	message J_AzaleaPokecenter1FFishingGuruText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaPokecenter1FPokefanFScript::
	faceplayer
	message J_AzaleaPokecenter1FPokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaPokecenter1FGentlemanText::
	.string "Do your POKéMON\nknow HM moves?\pThose moves can\nbe used even if\pyour POKéMON has\nfainted.$"
J_AzaleaPokecenter1FUnusedText::
	.string "This BILL guy\ncreated the system\pfor storing\nPOKéMON in a PC.\pBILL's PC can\nstore up to 20\lPOKéMON per BOX.$"
J_AzaleaPokecenter1FFishingGuruText::
	.string "BILL's PC can\nstore up to 20\lPOKéMON per BOX.$"
J_AzaleaPokecenter1FPokefanFText::
	.string "Do you know about\nAPRICORNS?\pCrack one open,\nhollow it out and\pfit it with a\nspecial device.\pThen you can catch\nPOKéMON with it.\pBefore POKé BALLS\nwere invented,\peveryone used\nAPRICORNS.$"
J_AzaleaPokecenter1F_MapEvents::
