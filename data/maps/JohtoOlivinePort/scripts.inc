@ KJH: translated from pokecrystal maps/OlivinePort.asm by kjh_tools/johto

JohtoOlivinePort_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoOlivinePort_OnFrame
	.byte 0

JohtoOlivinePort_OnFrame:
	map_script_2 VAR_J_SCENE_OLIVINE_PORT, 1, J_SC_OlivinePortLeaveShipScene
	.2byte 0

J_W_OlivinePortSailorAtGangwayScript::
	lock
	call J_OlivinePortSailorAtGangwayScript
	release
	end

J_W_OlivinePortSailorBeforeHOFScript::
	lock
	call J_OlivinePortSailorBeforeHOFScript
	release
	end

J_W_OlivinePortSailorAfterHOFScript::
	lock
	call J_OlivinePortSailorAfterHOFScript
	release
	end

J_W_OlivinePortFishingGuru1Script::
	lock
	call J_OlivinePortFishingGuru1Script
	release
	end

J_W_OlivinePortFishingGuru2Script::
	lock
	call J_OlivinePortFishingGuru2Script
	release
	end

J_W_OlivinePortYoungsterScript::
	lock
	call J_OlivinePortYoungsterScript
	release
	end

J_W_OlivinePortCooltrainerFScript::
	lock
	call J_OlivinePortCooltrainerFScript
	release
	end

J_C_OlivinePortWalkUpToShipScript::
	lockall
	call J_OlivinePortWalkUpToShipScript
	releaseall
	end

J_SC_OlivinePortLeaveShipScene::
	lockall
	call J_OlivinePortLeaveShipScene
	releaseall
	end

J_OlivinePort_MapScripts::
J_OlivinePortNoopScene::
	return
J_OlivinePortLeaveShipScene::
	call J_OlivinePortLeaveShipScript
	return
J_OlivinePortLeaveShipScript::
	applymovement OBJ_EVENT_ID_PLAYER, J_OlivinePortLeaveFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	addobject 1
	setvar VAR_J_SCENE_OLIVINE_PORT, 0
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1
	return
J_OlivinePortSailorAtGangwayScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L569
	setvar VAR_RESULT, 1
J_L569:
	goto_if_ne VAR_RESULT, 0, J_OlivinePortAlreadyRodeScript
	message J_OlivinePortSailorGetOnBoardText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 1, DIR_SOUTH
	delay 10
	playse SE_EXIT
	removeobject 1
	waitse
	applymovement OBJ_EVENT_ID_PLAYER, J_OlivinePortEnterFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_EXIT
	fadescreen FADE_TO_WHITE
	waitse
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FAST_SHIP_FIRST_TIME, J_L570
	setvar VAR_RESULT, 1
J_L570:
	goto_if_eq VAR_RESULT, 0, J_OlivinePortSailorAtGangwayScript_FirstTime
	clearflag FLAG_J_FAST_SHIP_PASSENGERS_EASTBOUND
	setflag FLAG_J_FAST_SHIP_PASSENGERS_WESTBOUND
	clearflag FLAG_J_BEAT_COOLTRAINERM_SEAN
	clearflag FLAG_J_BEAT_COOLTRAINERF_CAROL
	clearflag FLAG_J_BEAT_GENTLEMAN_EDWARD
	clearflag FLAG_J_BEAT_BEAUTY_CASSIE
	clearflag FLAG_J_BEAT_PSYCHIC_RODNEY
	clearflag FLAG_J_BEAT_SUPER_NERD_SHAWN
	clearflag FLAG_J_BEAT_SAILOR_GARRETT
	clearflag FLAG_J_BEAT_FISHER_JONAH
	clearflag FLAG_J_BEAT_BLACKBELT_WAI
J_OlivinePortSailorAtGangwayScript_FirstTime:
	clearflag FLAG_J_FAST_SHIP_DESTINATION_OLIVINE
	addobject 1
	return
J_OlivinePortAlreadyRodeScript::
	message J_OlivinePortCantBoardText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivinePortWalkUpToShipScript::
	turnobject 3, DIR_EAST
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L571
	setvar VAR_RESULT, 1
J_L571:
	goto_if_ne VAR_RESULT, 0, J_OlivinePortWalkUpToShipScript_skip
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2, J_L572
	setvar VAR_RESULT, 1
J_L572:
	goto_if_ne VAR_RESULT, 0, J_OlivinePortWalkUpToShipScript_skip
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FAST_SHIP_FIRST_TIME, J_L573
	setvar VAR_RESULT, 1
J_L573:
	goto_if_eq VAR_RESULT, 0, J_OlivinePortWalkUpToShipScript_FirstTime
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J_OlivinePortWalkUpToShipScript_NextShipMonday
	goto_if_eq VAR_RESULT, 6, J_OlivinePortWalkUpToShipScript_NextShipMonday
	goto_if_eq VAR_RESULT, 2, J_OlivinePortWalkUpToShipScript_NextShipFriday
	goto_if_eq VAR_RESULT, 3, J_OlivinePortWalkUpToShipScript_NextShipFriday
	goto_if_eq VAR_RESULT, 4, J_OlivinePortWalkUpToShipScript_NextShipFriday
J_OlivinePortWalkUpToShipScript_FirstTime:
	message J_OlivinePortAskBoardText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_OlivinePortNotRidingMoveAwayScript
	message J_OlivinePortAskTicketText
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_S_S_TICKET, J_L574
	setvar VAR_RESULT, 1
J_L574:
	goto_if_eq VAR_RESULT, 0, J_OlivinePortWalkUpToShipScript_NoTicket
	message J_OlivinePortFlashTicketText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2
	applymovement OBJ_EVENT_ID_PLAYER, J_OlivinePortApproachFastShipFirstTimeMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	goto J_OlivinePortSailorAtGangwayScript
J_OlivinePortWalkUpToShipScript_NoTicket:
	message J_OlivinePortNoTicketText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_OlivinePortCannotEnterFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	return
J_OlivinePortWalkUpToShipScript_NextShipMonday:
	message J_OlivinePortMondayShipText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_OlivinePortCannotEnterFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	return
J_OlivinePortWalkUpToShipScript_NextShipFriday:
	message J_OlivinePortFridayShipText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_OlivinePortCannotEnterFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	return
J_OlivinePortWalkUpToShipScript_skip:
	return
J_OlivinePortNotRidingScript::
	message J_OlivinePortComeAgainText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivinePortNotRidingMoveAwayScript::
	message J_OlivinePortComeAgainText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_OlivinePortCannotEnterFastShipMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	return
J_OlivinePortSailorAfterHOFScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L575
	setvar VAR_RESULT, 1
J_L575:
	goto_if_ne VAR_RESULT, 0, J_OlivinePortAlreadyRodeScript
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FAST_SHIP_FIRST_TIME, J_L576
	setvar VAR_RESULT, 1
J_L576:
	goto_if_eq VAR_RESULT, 0, J_OlivinePortSailorAfterHOFScript_FirstTime
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J_OlivinePortSailorAfterHOFScript_NextShipMonday
	goto_if_eq VAR_RESULT, 6, J_OlivinePortSailorAfterHOFScript_NextShipMonday
	goto_if_eq VAR_RESULT, 2, J_OlivinePortSailorAfterHOFScript_NextShipFriday
	goto_if_eq VAR_RESULT, 3, J_OlivinePortSailorAfterHOFScript_NextShipFriday
	goto_if_eq VAR_RESULT, 4, J_OlivinePortSailorAfterHOFScript_NextShipFriday
J_OlivinePortSailorAfterHOFScript_FirstTime:
	message J_OlivinePortAskBoardText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_OlivinePortNotRidingScript
	message J_OlivinePortAskTicketText
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_S_S_TICKET, J_L577
	setvar VAR_RESULT, 1
J_L577:
	goto_if_eq VAR_RESULT, 0, J_OlivinePortSailorAfterHOFScript_NoTicket
	message J_OlivinePortFlashTicketText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 3, J_OlivinePortSailorAfterHOFScript_Right
	applymovement OBJ_EVENT_ID_PLAYER, J_OlivinePortApproachFastShipAfterHOFMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	goto J_OlivinePortSailorAtGangwayScript
J_OlivinePortSailorAfterHOFScript_Right:
	applymovement OBJ_EVENT_ID_PLAYER, J_OlivinePortApproachFastShipAfterHOFRightMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	goto J_OlivinePortSailorAtGangwayScript
J_OlivinePortSailorAfterHOFScript_NoTicket:
	message J_OlivinePortNoTicketText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivinePortSailorAfterHOFScript_NextShipMonday:
	message J_OlivinePortMondayShipText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivinePortSailorAfterHOFScript_NextShipFriday:
	message J_OlivinePortFridayShipText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivinePortSailorBeforeHOFScript::
	faceplayer
	message J_OlivinePortSailorBeforeHOFText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivinePortFishingGuru1Script::
	faceplayer
	message J_OlivinePortFishingGuru1Text
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 4, DIR_NORTH
	return
J_OlivinePortFishingGuru2Script::
	faceplayer
	message J_OlivinePortFishingGuru2Text
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 5, DIR_NORTH
	return
J_OlivinePortYoungsterScript::
	faceplayer
	message J_OlivinePortYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 6, DIR_SOUTH
	return
J_OlivinePortCooltrainerFScript::
	faceplayer
	message J_OlivinePortCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 7, DIR_SOUTH
	return
J_OlivinePortHiddenProtein::
	finditem ITEM_PROTEIN
	return
J_OlivinePortEnterFastShipMovement::
	walk_down
	step_end
J_OlivinePortLeaveFastShipMovement::
	walk_up
	step_end
J_OlivinePortCannotEnterFastShipMovement::
	walk_right
	face_left
	step_end
J_OlivinePortApproachFastShipFirstTimeMovement::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
J_OlivinePortApproachFastShipAfterHOFMovement::
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
J_OlivinePortApproachFastShipAfterHOFRightMovement::
	walk_up
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
J_OlivinePortSailorGetOnBoardText::
	.string "We're departing\nsoon. Please get\lon board.$"
J_OlivinePortCantBoardText::
	.string "Sorry. You can't\nboard now.$"
J_OlivinePortAskBoardText::
	.string "Welcome to FAST\nSHIP S.S.AQUA.\pWill you be board-\ning today?$"
J_OlivinePortAskTicketText::
	.string "May I see your\nS.S.TICKET?$"
J_OlivinePortComeAgainText::
	.string "We hope to see you\nagain!$"
J_OlivinePortFlashTicketText::
	.string "{PLAYER} flashed\nthe S.S.TICKET.\pThat's it.\nThank you!$"
J_OlivinePortNoTicketText::
	.string "{PLAYER} tried to\nshow the S.S.\lTICKET…\p…But no TICKET!\pSorry!\nYou may board only\pif you have an\nS.S.TICKET.$"
J_OlivinePortMondayShipText::
	.string "The FAST SHIP will\nsail next Monday.$"
J_OlivinePortFridayShipText::
	.string "The FAST SHIP will\nsail next Friday.$"
J_OlivinePortFishingGuru1Text::
	.string "SHELLDER are easy\nto catch here.\pThey're kind of\nrare elsewhere.$"
J_OlivinePortFishingGuru2Text::
	.string "How many RODS do\nyou have?\pDifferent RODS\ncatch different\lPOKéMON.$"
J_OlivinePortYoungsterText::
	.string "S.S.AQUA uses jets\nto skim over the\lwaves!$"
J_OlivinePortCooltrainerFText::
	.string "There are lots of\nPOKéMON in KANTO.\pI wish I could go…$"
J_OlivinePortSailorBeforeHOFText::
	.string "We don't want you\nto fall into the\psea, so you're not\nallowed in.$"
J_OlivinePort_MapEvents::
