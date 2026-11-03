@ KJH: translated from pokecrystal maps/GoldenrodMagnetTrainStation.asm by kjh_tools/johto

JohtoGoldenrodMagnetTrainStation_MapScripts::
	.byte 0

J_W_GoldenrodMagnetTrainStationOfficerScript::
	lock
	call J_GoldenrodMagnetTrainStationOfficerScript
	release
	end

J_W_GoldenrodMagnetTrainStationGentlemanScript::
	lock
	call J_GoldenrodMagnetTrainStationGentlemanScript
	release
	end

J_C_Script_ArriveFromSaffron::
	lockall
	call J_Script_ArriveFromSaffron
	releaseall
	end

J_GoldenrodMagnetTrainStation_MapScripts::
J_GoldenrodMagnetTrainStationNoopScene::
	return
J_GoldenrodMagnetTrainStationOfficerScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L527
	setvar VAR_RESULT, 1
J_L527:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodMagnetTrainStationOfficerScript_MagnetTrainToSaffron
	message J_GoldenrodMagnetTrainStationOfficerTheTrainHasntComeInText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodMagnetTrainStationOfficerScript_MagnetTrainToSaffron:
	message J_GoldenrodMagnetTrainStationOfficerAreYouComingAboardText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_GoldenrodMagnetTrainStationOfficerScript_DecidedNotToRide
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_PASS, J_L528
	setvar VAR_RESULT, 1
J_L528:
	goto_if_eq VAR_RESULT, 0, J_GoldenrodMagnetTrainStationOfficerScript_PassNotInBag
	message J_GoldenrodMagnetTrainStationOfficerRightThisWayText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_GoldenrodMagnetTrainStationOfficerApproachTrainDoorMovement
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, J_GoldenrodMagnetTrainStationPlayerApproachAndEnterTrainMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	setvar VAR_RESULT, 0
	setvar VAR_RESULT, 0
	applymovement OBJ_EVENT_ID_PLAYER, J_GoldenrodMagnetTrainStationOfficerScript_MovementBoardTheTrain
	waitmovement OBJ_EVENT_ID_PLAYER
	return
J_GoldenrodMagnetTrainStationOfficerScript_MovementBoardTheTrain:
	face_down
	step_end
J_GoldenrodMagnetTrainStationOfficerScript_PassNotInBag:
	message J_GoldenrodMagnetTrainStationOfficerYouDontHaveARailPassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodMagnetTrainStationOfficerScript_DecidedNotToRide:
	message J_GoldenrodMagnetTrainStationOfficerHopeToSeeYouAgainText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Script_ArriveFromSaffron::
	applymovement 1, J_GoldenrodMagnetTrainStationOfficerApproachTrainDoorMovement
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, J_GoldenrodMagnetTrainStationPlayerLeaveTrainAndEnterStationMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, J_GoldenrodMagnetTrainStationOfficerReturnToBoardingGateMovement
	waitmovement 1
	message J_GoldenrodMagnetTrainStationOfficerArrivedInGoldenrodText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodMagnetTrainStationGentlemanScript::
	faceplayer
	message J_GoldenrodMagnetTrainStationGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodMagnetTrainStationOfficerApproachTrainDoorMovement::
	walk_up
	walk_up
	walk_right
	face_left
	step_end
J_GoldenrodMagnetTrainStationOfficerReturnToBoardingGateMovement::
	walk_left
	walk_down
	walk_down
	step_end
J_GoldenrodMagnetTrainStationPlayerApproachAndEnterTrainMovement::
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end
J_GoldenrodMagnetTrainStationPlayerLeaveTrainAndEnterStationMovement::
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	face_up
	step_end
J_GoldenrodMagnetTrainStationOfficerTheTrainHasntComeInText::
	.string "The train hasn't\ncome in…\pI know! I'll carry\nthe passengers on\lmy back!\pThat won't work.$"
J_GoldenrodMagnetTrainStationOfficerAreYouComingAboardText::
	.string "We'll soon depart\nfor SAFFRON.\pAre you coming\naboard?$"
J_GoldenrodMagnetTrainStationOfficerRightThisWayText::
	.string "May I see your\nrail PASS, please?\pOK. Right this\nway, please.$"
J_GoldenrodMagnetTrainStationOfficerYouDontHaveARailPassText::
	.string "Sorry. You don't\nhave a rail PASS.$"
J_GoldenrodMagnetTrainStationOfficerHopeToSeeYouAgainText::
	.string "We hope to see you\nagain!$"
J_GoldenrodMagnetTrainStationOfficerArrivedInGoldenrodText::
	.string "We have arrived in\nGOLDENROD.\pWe hope to see you\nagain.$"
J_GoldenrodMagnetTrainStationGentlemanText::
	.string "I'm the PRESIDENT.\pMy dream was to\nbuild a train that\pis faster than any\nPOKéMON.\pIt really brings\nJOHTO much closer\lto KANTO.$"
J_GoldenrodMagnetTrainStation_MapEvents::
