@ KJH: translated from pokecrystal maps/CherrygrovePokecenter1F.asm by kjh_tools/johto

JohtoCherrygrovePokecenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoCherrygrovePokecenter1F_OnTransition
	.byte 0

JohtoCherrygrovePokecenter1F_OnTransition:
	setrespawn HEAL_LOCATION_J_CHERRYGROVE
	end

J_W_CherrygrovePokecenter1FNurseScript::
	lock
	call J_CherrygrovePokecenter1FNurseScript
	release
	end

J_W_CherrygrovePokecenter1FFisherScript::
	lock
	call J_CherrygrovePokecenter1FFisherScript
	release
	end

J_W_CherrygrovePokecenter1FGentlemanScript::
	lock
	call J_CherrygrovePokecenter1FGentlemanScript
	release
	end

J_W_CherrygrovePokecenter1FTeacherScript::
	lock
	call J_CherrygrovePokecenter1FTeacherScript
	release
	end

J_CherrygrovePokecenter1F_MapScripts::
J_CherrygrovePokecenter1FNurseScript::
	goto J_Std_Nurse
J_CherrygrovePokecenter1FFisherScript::
	faceplayer
	message J_CherrygrovePokecenter1FFisherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CherrygrovePokecenter1FGentlemanScript::
	faceplayer
	message J_CherrygrovePokecenter1FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CherrygrovePokecenter1FTeacherScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_MYSTERY_EGG_TO_ELM, J_L688
	setvar VAR_RESULT, 1
J_L688:
	goto_if_ne VAR_RESULT, 0, J_CherrygrovePokecenter1FTeacherScript_CommCenterOpen
	message J_CherrygrovePokecenter1FTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CherrygrovePokecenter1FTeacherScript_CommCenterOpen:
	message J_CherrygrovePokecenter1FTeacherText_CommCenterOpen
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CherrygrovePokecenter1FFisherText::
	.string "It's great. I can\nstore any number\pof POKéMON, and\nit's all free.$"
J_CherrygrovePokecenter1FGentlemanText::
	.string "That PC is free\nfor any trainer\lto use.$"
J_CherrygrovePokecenter1FTeacherText::
	.string "The COMMUNICATION\nCENTER upstairs\lwas just built.\pBut they're still\nfinishing it up.$"
J_CherrygrovePokecenter1FTeacherText_CommCenterOpen::
	.string "The COMMUNICATION\nCENTER upstairs\lwas just built.\pI traded POKéMON\nthere already!$"
J_CherrygrovePokecenter1F_MapEvents::
