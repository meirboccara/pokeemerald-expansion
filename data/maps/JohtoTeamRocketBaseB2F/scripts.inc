@ KJH: translated from pokecrystal maps/TeamRocketBaseB2F.asm by kjh_tools/johto

JohtoTeamRocketBaseB2F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, JohtoTeamRocketBaseB2F_OnLoad
	.byte 0

JohtoTeamRocketBaseB2F_OnLoad:
	call J_TeamRocketBaseB2FTransmitterDoorCallback
	end

J_W_RocketElectrode1::
	lock
	call J_RocketElectrode1
	release
	end

J_W_RocketElectrode2::
	lock
	call J_RocketElectrode2
	release
	end

J_W_RocketElectrode3::
	lock
	call J_RocketElectrode3
	release
	end

J_T_TrainerGruntM17::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_17, J_GruntM17SeenText, J_GruntM17BeatenText
	call J_TrainerGruntM17_Script
	release
	end

J_T_TrainerGruntM18::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_18, J_GruntM18SeenText, J_GruntM18BeatenText
	call J_TrainerGruntM18_Script
	release
	end

J_T_TrainerGruntM19::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_19, J_GruntM19SeenText, J_GruntM19BeatenText
	call J_TrainerGruntM19_Script
	release
	end

J_C_LanceHealsScript1::
	lockall
	call J_LanceHealsScript1
	releaseall
	end

J_C_LanceHealsScript2::
	lockall
	call J_LanceHealsScript2
	releaseall
	end

J_C_RocketBaseBossFLeft::
	lockall
	call J_RocketBaseBossFLeft
	releaseall
	end

J_C_RocketBaseBossFRight::
	lockall
	call J_RocketBaseBossFRight
	releaseall
	end

J_C_RocketBaseCantLeaveScript::
	lockall
	call J_RocketBaseCantLeaveScript
	releaseall
	end

J_C_RocketBaseLancesSideScript::
	lockall
	call J_RocketBaseLancesSideScript
	releaseall
	end

J_S_TeamRocketBaseB2FLockedDoor::
	lockall
	goto_if_set FLAG_J_OPENED_DOOR_TO_ROCKET_HIDEOUT_TRANSMITTER, J_L694
	call J_TeamRocketBaseB2FLockedDoor_Script
J_L694:
	releaseall
	end

J_S_TeamRocketBaseB2FTransmitterScript::
	lockall
	call J_TeamRocketBaseB2FTransmitterScript
	releaseall
	end

J_TeamRocketBaseB2F_MapScripts::
J_TeamRocketBaseB2FNoop1Scene::
	return
J_TeamRocketBaseB2FNoop2Scene::
	return
J_TeamRocketBaseB2FNoop3Scene::
	return
J_TeamRocketBaseB2FNoop4Scene::
	return
J_TeamRocketBaseB2FTransmitterDoorCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_OPENED_DOOR_TO_ROCKET_HIDEOUT_TRANSMITTER, J_L192
	setvar VAR_RESULT, 1
J_L192:
	goto_if_ne VAR_RESULT, 0, J_TeamRocketBaseB2FTransmitterDoorCallback_OpenDoor
	return
J_TeamRocketBaseB2FTransmitterDoorCallback_OpenDoor:
	setmetatile 14, 12, 4, FALSE
	setmetatile 15, 12, 4, FALSE
	setmetatile 14, 13, 4, FALSE
	setmetatile 15, 13, 4, FALSE
	return
J_RocketBaseBossFLeft::
	setobjectxyperm 3, 9, 13
	goto J_RocketBaseBossFScript
J_RocketBaseBossFRight::
	setobjectxyperm 2, 21, 16
	setobjectxyperm 1, 21, 16
	setobjectxyperm 4, 10, 13
	setobjectxyperm 3, 10, 13
J_RocketBaseBossFScript::
	addobject 2
	addobject 1
	message J_RocketBaseExecutiveFHoldItText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, J_RocketBasePlayerApproachesBossFMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	applymovement 2, J_RocketBaseBossFApproachesPlayerMovement
	waitmovement 2
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	applymovement 1, J_RocketBaseGruntApproachesPlayerMovement
	waitmovement 1
	message J_RocketBaseBossFThrashText
	waitmessage
	waitbuttonpress
	closemessage
	playmoncry SPECIES_DRAGONITE, CRY_MODE_NORMAL
	waitmoncry
	turnobject 2, DIR_WEST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	addobject 4
	applymovement 4, J_RocketBaseDragoniteAttacksMovement
	waitmovement 4
	applymovement 2, J_RocketBaseBossFHitMovement
	waitmovement 2
	applymovement 1, J_RocketBaseGruntProtectsBossFMovement
	waitmovement 1
	addobject 3
	applymovement 3, J_RocketBaseLanceApproachesBossFMovement
	waitmovement 3
	message J_RocketBaseLanceShareFunText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement 2, J_RocketBaseBossFFacesPlayerMovement
	waitmovement 2
	message J_RocketBaseBossDontMeddleText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_RocketBaseGruntBattlesLanceMovement
	waitmovement 1
	applymovement 2, J_RocketBaseBossFBattlesPlayerMovement
	waitmovement 2
	setvar VAR_LAST_TALKED, 2
	trainerbattle_no_intro TRAINER_J_EXECUTIVEF_EXECUTIVEF_2, J_RocketBaseBossWinText
	removeobject 4
	setflag FLAG_J_TEAM_ROCKET_BASE_B2F_EXECUTIVE
	setflag FLAG_J_TEAM_ROCKET_BASE_B2F_GRUNT_WITH_EXECUTIVE
	setflag FLAG_J_TEAM_ROCKET_BASE_B2F_LANCE
	setflag FLAG_J_BEAT_ROCKET_EXECUTIVEF_2
	message J_RocketBaseBossRetreatText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 1
	removeobject 2
	removeobject 11
	removeobject 12
	removeobject 13
	delay 15
	fadescreen FADE_FROM_BLACK
	setvar VAR_J_SCENE_TEAM_ROCKET_BASE_B2F, 2
	clearflag FLAG_J_TEAM_ROCKET_BASE_B2F_LANCE
	turnobject 3, DIR_SOUTH
	message J_RocketBaseLancePostBattleText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, J_RocketBaseLanceChecksPlayerMovement
	waitmovement 3
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	message J_RocketBaseLancePowerOffText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, J_RocketBaseLanceApproachesMachineMovement
	applymovement OBJ_EVENT_ID_PLAYER, J_RocketBaseLanceApproachesMachineMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement 3
	applymovement 3, J_RocketBaseLancePacesMovement
	waitmovement 3
	message J_RockerBaseLanceElectrodeFaintText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, J_RocketBaseLanceApproachesElectrodesMovement
	waitmovement 3
	removeobject 3
J_RocketBaseCantLeaveScript::
	applymovement OBJ_EVENT_ID_PLAYER, J_RocketBasePlayerCantLeaveElectrodesMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	return
J_RocketBaseLancesSideScript::
	message J_RocketBaseLancesSideText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_RocketBasePlayerCantGoRightMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	return
J_LanceHealsScript1::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	goto J_LanceHealsCommon
J_LanceHealsScript2::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	turnobject 3, DIR_WEST
J_LanceHealsCommon::
	message J_LanceHealsText1
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_WHITE
	playse SE_USE_ITEM
	special HealPlayerParty
	fadescreen FADE_FROM_WHITE
	message J_LanceHealsText2
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_J_SCENE_TEAM_ROCKET_BASE_B2F, 1
	setflag FLAG_J_LANCE_HEALED_YOU_IN_TEAM_ROCKET_BASE
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 3, J_LanceHealsCommon_FacingRight
	applymovement 3, J_RocketBaseLanceLeavesAfterHealMovement
	waitmovement 3
	removeobject 3
	return
J_LanceHealsCommon_FacingRight:
	applymovement 3, J_RocketBaseLanceLeavesAfterHealRightMovement
	waitmovement 3
	removeobject 3
	return
J_TrainerGruntM17::
J_TrainerGruntM17_Script:
	message J_GruntM17AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM18::
J_TrainerGruntM18_Script:
	message J_GruntM18AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM19::
J_TrainerGruntM19_Script:
	message J_GruntM19AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RocketElectrode1::
	playmoncry SPECIES_ELECTRODE, CRY_MODE_NORMAL
	waitmoncry
	setwildbattle SPECIES_ELECTRODE, 23
	dowildbattle
	goto_if_ne VAR_RESULT, 0, J_TeamRocketBaseB2FReloadMap
	removeobject 5
	removeobject 8
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_B2F_ELECTRODE_1, J_L193
	setvar VAR_RESULT, 1
J_L193:
	goto_if_eq VAR_RESULT, 0, J_TeamRocketBaseB2FReloadMap
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_B2F_ELECTRODE_2, J_L194
	setvar VAR_RESULT, 1
J_L194:
	goto_if_eq VAR_RESULT, 0, J_TeamRocketBaseB2FReloadMap
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_B2F_ELECTRODE_3, J_L195
	setvar VAR_RESULT, 1
J_L195:
	goto_if_eq VAR_RESULT, 0, J_TeamRocketBaseB2FReloadMap
	fadedefaultbgm
	applymovement OBJ_EVENT_ID_PLAYER, J_RocketBasePlayerLeavesElectrodesMovement1
	waitmovement OBJ_EVENT_ID_PLAYER
	goto J_RocketBaseElectrodeScript
J_RocketElectrode2::
	playmoncry SPECIES_ELECTRODE, CRY_MODE_NORMAL
	waitmoncry
	setwildbattle SPECIES_ELECTRODE, 23
	dowildbattle
	goto_if_ne VAR_RESULT, 0, J_TeamRocketBaseB2FReloadMap
	removeobject 6
	removeobject 9
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_B2F_ELECTRODE_1, J_L196
	setvar VAR_RESULT, 1
J_L196:
	goto_if_eq VAR_RESULT, 0, J_TeamRocketBaseB2FReloadMap
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_B2F_ELECTRODE_2, J_L197
	setvar VAR_RESULT, 1
J_L197:
	goto_if_eq VAR_RESULT, 0, J_TeamRocketBaseB2FReloadMap
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_B2F_ELECTRODE_3, J_L198
	setvar VAR_RESULT, 1
J_L198:
	goto_if_eq VAR_RESULT, 0, J_TeamRocketBaseB2FReloadMap
	fadedefaultbgm
	applymovement OBJ_EVENT_ID_PLAYER, J_RocketBasePlayerLeavesElectrodesMovement2
	waitmovement OBJ_EVENT_ID_PLAYER
	goto J_RocketBaseElectrodeScript
J_RocketElectrode3::
	playmoncry SPECIES_ELECTRODE, CRY_MODE_NORMAL
	waitmoncry
	setwildbattle SPECIES_ELECTRODE, 23
	dowildbattle
	goto_if_ne VAR_RESULT, 0, J_TeamRocketBaseB2FReloadMap
	removeobject 7
	removeobject 10
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_B2F_ELECTRODE_1, J_L199
	setvar VAR_RESULT, 1
J_L199:
	goto_if_eq VAR_RESULT, 0, J_TeamRocketBaseB2FReloadMap
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_B2F_ELECTRODE_2, J_L200
	setvar VAR_RESULT, 1
J_L200:
	goto_if_eq VAR_RESULT, 0, J_TeamRocketBaseB2FReloadMap
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_B2F_ELECTRODE_3, J_L201
	setvar VAR_RESULT, 1
J_L201:
	goto_if_eq VAR_RESULT, 0, J_TeamRocketBaseB2FReloadMap
	fadedefaultbgm
	applymovement OBJ_EVENT_ID_PLAYER, J_RocketBasePlayerLeavesElectrodesMovement3
	waitmovement OBJ_EVENT_ID_PLAYER
	goto J_RocketBaseElectrodeScript
J_TeamRocketBaseB2FReloadMap::
	return
J_RocketBaseElectrodeScript::
	setobjectxyperm 3, 18, 6
	addobject 3
	applymovement 3, J_RocketBaseLanceLeavesElectrodesMovement
	waitmovement 3
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	message J_RocketBaseLanceElectrodeDoneText
	waitmessage
	waitbuttonpress
	giveitem ITEM_RARE_CANDY, 1
	setflag FLAG_J_GOT_HM06_WHIRLPOOL
	message J_RocketBaseLanceWhirlpoolText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 3, DIR_SOUTH
	message J_RocketBaseLanceMonMasterText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement 3, J_RocketBaseLanceLeavesBaseMovement
	waitmovement 3
	removeobject 3
	setflag FLAG_J_CLEARED_ROCKET_HIDEOUT
	clearflag FLAG_J_ENGINE_ROCKET_SIGNAL_ON_CH20
	setflag FLAG_J_ROUTE_43_GATE_ROCKETS
	setflag FLAG_J_MAHOGANY_TOWN_POKEFAN_M_BLOCKS_GYM
	setvar VAR_J_SCENE_TEAM_ROCKET_BASE_B2F, 3
	clearflag FLAG_J_LAKE_OF_RAGE_CIVILIANS
	setflag FLAG_J_TURNED_OFF_SECURITY_CAMERAS
	setflag FLAG_J_SECURITY_CAMERA_1
	setflag FLAG_J_SECURITY_CAMERA_2
	setflag FLAG_J_SECURITY_CAMERA_3
	setflag FLAG_J_SECURITY_CAMERA_4
	setflag FLAG_J_SECURITY_CAMERA_5
	return
J_TeamRocketBaseB2FLockedDoor::
J_TeamRocketBaseB2FLockedDoor_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_LEARNED_HAIL_GIOVANNI, J_L202
	setvar VAR_RESULT, 1
J_L202:
	goto_if_ne VAR_RESULT, 0, J_TeamRocketBaseB2FLockedDoor_KnowsPassword
	message J_RocketBaseDoorNoPasswordText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TeamRocketBaseB2FLockedDoor_KnowsPassword:
	message J_RocketBaseDoorKnowPasswordText
	waitmessage
	waitbuttonpress
	playse SE_DOOR
	setmetatile 14, 12, 4, FALSE
	setmetatile 15, 12, 4, FALSE
	setmetatile 14, 13, 4, FALSE
	setmetatile 15, 13, 4, FALSE
	special DrawWholeMapView
	closemessage
	setflag FLAG_J_OPENED_DOOR_TO_ROCKET_HIDEOUT_TRANSMITTER
	waitse
	return
J_TeamRocketBaseB2FTransmitterScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_ROCKET_HIDEOUT, J_L203
	setvar VAR_RESULT, 1
J_L203:
	goto_if_ne VAR_RESULT, 0, J_TeamRocketBaseB2FTransmitterScript_Deactivated
	message J_RocketBaseB2FTransmitterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TeamRocketBaseB2FTransmitterScript_Deactivated:
	message J_RocketBaseB2FDeactivateTransmitterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TeamRocketBaseB2FTMThief::
	finditem ITEM_TM46, 1
	return
J_TeamRocketBaseB2FHiddenFullHeal::
	finditem ITEM_FULL_HEAL
	return
J_RocketBaseLanceLeavesAfterHealMovement::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end
J_RocketBaseLanceLeavesAfterHealRightMovement::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end
J_RocketBasePlayerApproachesBossFMovement::
	walk_down
	walk_down
	walk_down
	face_right
	step_end
J_RocketBaseBossFApproachesPlayerMovement::
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	face_down
	step_end
J_RocketBaseGruntApproachesPlayerMovement::
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	step_end
J_RocketBaseDragoniteAttacksMovement::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end
J_RocketBaseBossFHitMovement::
	lock_facing_direction
	jump_2_right
	unlock_facing_direction
	step_end
J_RocketBaseBossFFacesPlayerMovement::
	walk_slow_down
	face_left
	step_end
J_RocketBaseLanceApproachesBossFMovement::
	walk_right
	walk_right
	walk_right
	step_end
J_RocketBaseBossFBattlesPlayerMovement::
	walk_fast_left
	step_end
J_RocketBaseGruntBattlesLanceMovement::
	walk_fast_left
	step_end
J_RocketBaseGruntProtectsBossFMovement::
	walk_fast_left
	walk_fast_up
	face_left
	step_end
J_RocketBaseLanceChecksPlayerMovement::
	walk_right
	walk_right
	face_down
	step_end
J_RocketBaseLanceApproachesMachineMovement::
	walk_up
	walk_up
	walk_up
	step_end
J_RocketBaseLancePacesMovement::
	delay_8
	walk_left
	walk_left
	face_up
	delay_8
	walk_right
	walk_right
	walk_right
	walk_right
	face_up
	delay_8
	walk_left
	walk_left
	face_down
	step_end
J_RocketBaseLanceApproachesElectrodesMovement::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
J_RocketBasePlayerCantLeaveElectrodesMovement::
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end
J_RocketBasePlayerCantGoRightMovement::
	walk_left
	step_end
J_RocketBaseLanceLeavesElectrodesMovement::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end
J_RocketBaseLanceLeavesBaseMovement::
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end
J_RocketBasePlayerLeavesElectrodesMovement1::
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end
J_RocketBasePlayerLeavesElectrodesMovement2::
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end
J_RocketBasePlayerLeavesElectrodesMovement3::
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end
J_RocketBaseExecutiveFHoldItText::
	.string "Hold it right\nthere!$"
J_RocketBaseBossFThrashText::
	.string "We can't have a\nbrat like you on\lthe loose.\pIt's harmful to\nTEAM ROCKET's\lpride, you see.\pHowever strong you\nmay be, you can't\ptake both of us at\nthe same time.\pSorry, baby. Now\nget ready to be\lthrashed.$"
J_RocketBaseLanceShareFunText::
	.string "Hey! Don't be so\nselfish. Spread\lthe fun around.$"
J_RocketBaseBossDontMeddleText::
	.string "What? You had an\naccomplice?\pWhere is your\nsense of honor?\pAs the interim\nboss in place of\pGIOVANNI, I'll\nshow you how wrong\pit is to meddle\nwith TEAM ROCKET!$"
J_RocketBaseBossWinText::
	.string "Tch, you really\nare strong.\pIt's too bad.\pIf you were to\njoin TEAM ROCKET,\pyou could become\nan EXECUTIVE.$"
J_RocketBaseBossRetreatText::
	.string "…This hideout is\ndone for…\pBut that's fine.\nThe broadcast ex-\lperiment was a\ltotal success.\pIt doesn't matter\nwhat happens to\lthis hideout now.\pWe have much big-\nger plans.\pYou'll come to\nappreciate TEAM\pROCKET's true\npower soon enough.\pEnjoy yourself\nwhile you can…\pFufufufu…$"
J_RocketBaseLancePostBattleText::
	.string "LANCE: That did\nit. We defeated\pall the ROCKETS\nhere.\pBut I'm concerned\nabout the young\pguy I battled in\nthe process…$"
J_RocketBaseLancePowerOffText::
	.string "Sorry, {PLAYER}.\nI saw how well you\pwere doing, so I\njust hung back.\pNow all there is\nleft to do is to\pturn off that odd\nradio signal.$"
J_RockerBaseLanceElectrodeFaintText::
	.string "It's this machine\nthat's causing all\lthe problems.\pI don't see a\nswitch on it…\pWe have no choice.\nWe have to make\pall the ELECTRODE\nfaint.\pThat should stop\nthis machine from\ptransmitting that\nstrange signal.\pIt's no fault of\nthe POKéMON, so it\pmakes me feel\nguilty.\p{PLAYER}, let's\nsplit the job.$"
J_RocketBaseLancesSideText::
	.string "LANCE: Leave this\nside to me.$"
J_RocketBaseLanceElectrodeDoneText::
	.string "LANCE: That odd\nsignal has finally\lstopped.\pThe LAKE should be\nback to normal.\pYou're the hero!\nLet me thank you\pon behalf of all\nthe POKéMON.\pOh, yes. You\nshould take this.\pI found it here,\nbut I don't have\lany need for it.$"
J_RocketBaseReceivedHM06Text::
	.string "{PLAYER} received\nHM06.$"
J_RocketBaseLanceWhirlpoolText::
	.string "That's WHIRLPOOL.\nTeach it to a\pPOKéMON to get\nacross wild water.\pBut keep this in\nmind.\pYou can use that\nout of battle only\pwith the BADGE\nfrom MAHOGANY GYM.$"
J_RocketBaseLanceMonMasterText::
	.string "{PLAYER}…\pThe journey to be-\ncoming the POKéMON\pMASTER is long and\ndifficult.\pKnowing that, will\nyou keep going?\p…\pI see. No, you're\nright.\pIf you would give\nup that easily,\pyou would have\nnever chased that\pdream in the first\nplace.\pI look forward to\nseeing you again!$"
J_LanceHealsText1::
	.string "LANCE: Are you all\nright?\pYour POKéMON are\nhurt and tired.\pHere, give them\nsome of my medi-\lcine.$"
J_LanceHealsText2::
	.string "LANCE: {PLAYER},\nlet's give it our\lbest for POKéMON.$"
J_GruntM17SeenText::
	.string "The door won't\nopen?\pWell, duh.\nIt has to have a\ppassword that only\nTEAM ROCKET knows.$"
J_GruntM17BeatenText::
	.string "What? I lost?$"
J_GruntM17AfterBattleText::
	.string "Heh, I'm just a\nGRUNT.\pI don't know the\npassword. Too bad\lfor you.$"
J_GruntM18SeenText::
	.string "Oh, a kid? I don't\nreally like this,\pbut eliminate you\nI must.$"
J_GruntM18BeatenText::
	.string "I knew I'd lose…$"
J_GruntM18AfterBattleText::
	.string "I got wiped out on\nthe last mission\lby a kid too.\pWhen we were ab-\nducting POKéMON,\pthis kid with long\nred hair and mean-\plooking eyes just\ncreamed me…$"
J_GruntM19SeenText::
	.string "You rotten little\npest!$"
J_GruntM19BeatenText::
	.string "Grrrr…$"
J_GruntM19AfterBattleText::
	.string "Heh, only the boss\nknows the password\lfor that door.\pWhere's the boss?\nWho knows? Go look\lfor yourself.$"
J_RocketBaseDoorNoPasswordText::
	.string "The door's closed…\pIt needs a pass-\nword to open.$"
J_RocketBaseDoorKnowPasswordText::
	.string "The door's closed…\p{PLAYER} entered\nthe password.\pThe door opened!$"
J_RocketBaseB2FTransmitterText::
	.string "It's the radio\ntransmitter that's\psending the\nsinister signal.\pIt's working at\nfull capacity.$"
J_RocketBaseB2FDeactivateTransmitterText::
	.string "The radio trans-\nmitter has finally\pstopped its evil\nbroadcast.$"
J_TeamRocketBaseB2F_MapEvents::
