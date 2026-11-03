@ KJH: translated from pokecrystal maps/Route43MahoganyGate.asm by kjh_tools/johto

JohtoRoute43MahoganyGate_MapScripts::
	.byte 0

J_W_Route43MahoganyGateOfficer::
	lock
	call J_Route43MahoganyGateOfficer
	release
	end

J_Route43MahoganyGate_MapScripts::
J_Route43MahoganyGateOfficer::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_ROCKET_HIDEOUT, J_L379
	setvar VAR_RESULT, 1
J_L379:
	goto_if_ne VAR_RESULT, 0, J_Route43MahoganyGateOfficer_RocketsCleared
	message J_Route43MahoganyGateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route43MahoganyGateOfficer_RocketsCleared:
	message J_Route43MahoganyGateOfficerRocketsClearedText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route43MahoganyGateOfficerText::
	.string "Only people headed\nup to LAKE OF RAGE\phave been through\nhere lately.$"
J_Route43MahoganyGateOfficerRocketsClearedText::
	.string "Nobody goes up to\nLAKE OF RAGE these\ldays.$"
J_Route43MahoganyGate_MapEvents::
