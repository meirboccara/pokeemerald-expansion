@ KJH: translated from pokecrystal maps/EcruteakPokecenter1F.asm by kjh_tools/johto

JohtoEcruteakPokecenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoEcruteakPokecenter1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoEcruteakPokecenter1F_OnFrame
	.byte 0

JohtoEcruteakPokecenter1F_OnTransition:
	setrespawn HEAL_LOCATION_J_ECRUTEAK
	end

JohtoEcruteakPokecenter1F_OnFrame:
	map_script_2 VAR_J_SCENE_ECRUTEAK_POKECENTER_1F, 0, J_SC_EcruteakPokecenter1FMeetBillScene
	.2byte 0

J_W_EcruteakPokecenter1FNurseScript::
	lock
	call J_EcruteakPokecenter1FNurseScript
	release
	end

J_W_EcruteakPokecenter1FPokefanMScript::
	lock
	call J_EcruteakPokecenter1FPokefanMScript
	release
	end

J_W_EcruteakPokecenter1FCooltrainerFScript::
	lock
	call J_EcruteakPokecenter1FCooltrainerFScript
	release
	end

J_W_EcruteakPokecenter1FGymGuideScript::
	lock
	call J_EcruteakPokecenter1FGymGuideScript
	release
	end

J_SC_EcruteakPokecenter1FMeetBillScene::
	lockall
	call J_EcruteakPokecenter1FMeetBillScene
	releaseall
	end

J_EcruteakPokecenter1F_MapScripts::
J_EcruteakPokecenter1FMeetBillScene::
	call J_EcruteakPokcenter1FBillActivatesTimeCapsuleScript
	return
J_EcruteakPokecenter1FNoopScene::
	return
J_EcruteakPokcenter1FBillActivatesTimeCapsuleScript::
	delay 30
	playse SE_EXIT
	addobject 5
	waitse
	applymovement 5, J_EcruteakPokecenter1FBillMovement1
	waitmovement 5
	applymovement OBJ_EVENT_ID_PLAYER, J_EcruteakPokecenter1FPlayerMovement1
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject 1, DIR_NORTH
	delay 10
	turnobject 1, DIR_SOUTH
	delay 30
	turnobject 1, DIR_NORTH
	delay 10
	turnobject 1, DIR_SOUTH
	delay 20
	turnobject 5, DIR_SOUTH
	delay 10
	message J_EcruteakPokecenter1F_BillText1
	waitmessage
	waitbuttonpress
	goto J_EcruteakPokcenter1FBillActivatesTimeCapsuleScript_PointlessJump
J_EcruteakPokcenter1FBillActivatesTimeCapsuleScript_PointlessJump:
	message J_EcruteakPokecenter1F_BillText2
	waitmessage
	waitbuttonpress
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement 5, J_EcruteakPokecenter1FBillMovement2
	waitmovement 5
	playse SE_EXIT
	removeobject 5
	clearflag FLAG_J_MET_BILL
	setflag FLAG_J_ENGINE_TIME_CAPSULE
	setvar VAR_J_SCENE_ECRUTEAK_POKECENTER_1F, 1
	waitse
	return
J_EcruteakPokecenter1FNurseScript::
	goto J_Std_Nurse
J_EcruteakPokecenter1FPokefanMScript::
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_EcruteakPokecenter1FPokefanMScript_mobile
	faceplayer
	message J_EcruteakPokecenter1FPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakPokecenter1FPokefanMScript_mobile:
	faceplayer
	message J_EcruteakPokecenter1FPokefanMTextMobile
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakPokecenter1FCooltrainerFScript::
	faceplayer
	message J_EcruteakPokecenter1FCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakPokecenter1FGymGuideScript::
	faceplayer
	message J_EcruteakPokecenter1FGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakPokecenter1FBillMovement1::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	face_up
	step_end
J_EcruteakPokecenter1FBillMovement2::
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
J_EcruteakPokecenter1FPlayerMovement1::
	walk_up
	walk_up
	walk_up
	step_end
J_EcruteakPokecenter1F_BillText1::
	.string "Hi, I'm BILL. And\nwho are you?\pHmm, {PLAYER}, huh?\nYou've come at the\lright time.$"
J_EcruteakPokecenter1F_BillText2::
	.string "I just finished\nadjustments on my\lTIME CAPSULE.\pYou know that\nPOKéMON can be\ltraded, right?\pMy TIME CAPSULE\nwas developed to\penable trades with\nthe past.\pBut you can't send\nanything that\pdidn't exist in\nthe past.\pIf you did, the PC\nin the past would\lhave a breakdown.\pSo you have to\nremove anything\pthat wasn't around\nin the past.\pPut simply, no\nsending new moves\por new POKéMON in\nthe TIME CAPSULE.\pDon't you worry.\nI'm done with the\ladjustments.\pTomorrow, TIME\nCAPSULES will be\prunning at all\nPOKéMON CENTERS.\pI have to hurry on\nback to GOLDENROD\land see my folks.\pBuh-bye!$"
J_EcruteakPokecenter1FPokefanMText::
	.string "The way the KIMONO\nGIRLS dance is\pmarvelous. Just\nlike the way they\luse their POKéMON.$"
J_EcruteakPokecenter1FPokefanMTextMobile::
	.string "You must be hoping\nto battle more\ppeople, right?\nThere's apparently\psome place where\ntrainers gather.\pWhere, you ask?\pIt's a little past\nOLIVINE CITY.$"
J_EcruteakPokecenter1FCooltrainerFText::
	.string "MORTY, the GYM\nLEADER, is soooo\lcool.\pHis POKéMON are\nreally tough too.$"
J_EcruteakPokecenter1FGymGuideText::
	.string "LAKE OF RAGE…\pThe appearance of\na GYARADOS swarm…\pI smell a conspir-\nacy. I know it!$"
J_EcruteakPokecenter1F_MapEvents::
