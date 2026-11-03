@ KJH: translated from pokecrystal maps/TeamRocketBaseB3F.asm by kjh_tools/johto

JohtoTeamRocketBaseB3F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, JohtoTeamRocketBaseB3F_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoTeamRocketBaseB3F_OnFrame
	.byte 0

JohtoTeamRocketBaseB3F_OnLoad:
	call J_TeamRocketBaseB3FCheckGiovanniDoorCallback
	end

JohtoTeamRocketBaseB3F_OnFrame:
	map_script_2 VAR_J_SCENE_TEAM_ROCKET_BASE_B3F, 0, J_SC_TeamRocketBaseB3FLanceGetsPasswordScene
	.2byte 0

J_W_LanceGetPasswordScript::
	lock
	call J_LanceGetPasswordScript
	release
	end

J_W_RocketBaseMurkrow::
	lock
	call J_RocketBaseMurkrow
	release
	end

J_T_SlowpokeTailGrunt::
	trainerbattle_single TRAINER_J_GRUNTF_GRUNTF_5, J_GruntF5SeenText, J_GruntF5BeatenText
	call J_GruntF5Script
	release
	end

J_T_RaticateTailGrunt::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_28, J_GruntM28SeenText, J_GruntM28BeatenText
	call J_GruntM28Script
	release
	end

J_T_TrainerScientistRoss::
	trainerbattle_single TRAINER_J_SCIENTIST_ROSS, J_ScientistRossSeenText, J_ScientistRossBeatenText
	call J_TrainerScientistRoss_Script
	release
	end

J_T_TrainerScientistMitch::
	trainerbattle_single TRAINER_J_SCIENTIST_MITCH, J_ScientistMitchSeenText, J_ScientistMitchBeatenText
	call J_TrainerScientistMitch_Script
	release
	end

J_W_TeamRocketBaseB3FRocketScript::
	lock
	call J_TeamRocketBaseB3FRocketScript
	release
	end

J_C_RocketBaseBossLeft::
	lockall
	call J_RocketBaseBossLeft
	releaseall
	end

J_C_RocketBaseBossRight::
	lockall
	call J_RocketBaseBossRight
	releaseall
	end

J_C_RocketBaseRival::
	lockall
	call J_RocketBaseRival
	releaseall
	end

J_S_TeamRocketBaseB3FLockedDoor::
	lockall
	goto_if_set FLAG_J_OPENED_DOOR_TO_GIOVANNIS_OFFICE, J_L696
	call J_TeamRocketBaseB3FLockedDoor_Script
J_L696:
	releaseall
	end

J_S_TeamRocketBaseB3FOathScript::
	lockall
	call J_TeamRocketBaseB3FOathScript
	releaseall
	end

J_SC_TeamRocketBaseB3FLanceGetsPasswordScene::
	lockall
	call J_TeamRocketBaseB3FLanceGetsPasswordScene
	releaseall
	end

J_TeamRocketBaseB3F_MapScripts::
J_TeamRocketBaseB3FLanceGetsPasswordScene::
	call J_LanceGetPasswordScript
	return
J_TeamRocketBaseB3FNoop1Scene::
	return
J_TeamRocketBaseB3FNoop2Scene::
	return
J_TeamRocketBaseB3FNoop3Scene::
	return
J_TeamRocketBaseB3FCheckGiovanniDoorCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_OPENED_DOOR_TO_GIOVANNIS_OFFICE, J_L204
	setvar VAR_RESULT, 1
J_L204:
	goto_if_ne VAR_RESULT, 0, J_TeamRocketBaseB3FCheckGiovanniDoorCallback_OpenSesame
	return
J_TeamRocketBaseB3FCheckGiovanniDoorCallback_OpenSesame:
	setmetatile 10, 8, 4, FALSE
	setmetatile 11, 8, 4, FALSE
	setmetatile 10, 9, 4, FALSE
	setmetatile 11, 9, 4, FALSE
	return
J_LanceGetPasswordScript::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	delay 5
	turnobject 3, DIR_EAST
	delay 20
	applymovement 1, J_RocketBaseLanceApproachesPlayerMovement
	waitmovement 1
	message J_LanceGetPasswordText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_RocketBaseLanceLeavesMovement
	waitmovement 1
	removeobject 1
	setvar VAR_J_SCENE_TEAM_ROCKET_BASE_B3F, 1
	return
J_RocketBaseRival::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	fadeoutbgm 0
	addobject 9
	applymovement 9, J_RocketBaseRivalEnterMovement
	waitmovement 9
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playbgm MUS_RG_ENCOUNTER_RIVAL, FALSE
	message J_RocketBaseRivalText
	waitmessage
	waitbuttonpress
	closemessage
	playse SE_M_COMET_PUNCH
	applymovement OBJ_EVENT_ID_PLAYER, J_RocketBaseRivalShovesPlayerMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 9, J_RocketBaseRivalLeavesMovement
	waitmovement 9
	removeobject 9
	setvar VAR_J_SCENE_TEAM_ROCKET_BASE_B3F, 2
	fadedefaultbgm
	return
J_TeamRocketBaseB3FRocketScript::
	faceplayer
	message J_TeamRocketBaseB3FRocketText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RocketBaseBossLeft::
	applymovement OBJ_EVENT_ID_PLAYER, J_RocketBasePlayerApproachesBossLeftMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	goto J_RocketBaseBoss
J_RocketBaseBossRight::
	applymovement OBJ_EVENT_ID_PLAYER, J_RocketBasePlayerApproachesBossRightMovement
	waitmovement OBJ_EVENT_ID_PLAYER
J_RocketBaseBoss::
	delay 30
	applymovement 2, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	turnobject 2, DIR_SOUTH
	message J_ExecutiveM4BeforeText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, J_RocketBaseBossApproachesPlayerMovement
	waitmovement 2
	setvar VAR_LAST_TALKED, 2
	trainerbattle_no_intro TRAINER_J_EXECUTIVEM_EXECUTIVEM_4, J_ExecutiveM4BeatenText
	setflag FLAG_J_BEAT_ROCKET_EXECUTIVEM_4
	message J_ExecutiveM4AfterText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, J_RocketBaseBossHitsTableMovement
	waitmovement 2
	playse SE_M_COMET_PUNCH
	applymovement 2, J_RocketBaseBossLeavesMovement
	waitmovement 2
	removeobject 2
	setvar VAR_J_SCENE_TEAM_ROCKET_BASE_B3F, 3
	return
J_RocketBaseMurkrow::
	message J_RocketBaseMurkrowText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_LEARNED_HAIL_GIOVANNI
	return
J_SlowpokeTailGrunt::
J_GruntF5Script::
	message J_GruntF5AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_LEARNED_SLOWPOKETAIL
	return
J_RaticateTailGrunt::
J_GruntM28Script::
	message J_GruntM28AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_LEARNED_RATICATE_TAIL
	return
J_TrainerScientistRoss::
J_TrainerScientistRoss_Script:
	message J_ScientistRossAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerScientistMitch::
J_TrainerScientistMitch_Script:
	message J_ScientistMitchAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TeamRocketBaseB3FLockedDoor::
J_TeamRocketBaseB3FLockedDoor_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_LEARNED_SLOWPOKETAIL, J_L205
	setvar VAR_RESULT, 1
J_L205:
	goto_if_eq VAR_RESULT, 0, J_TeamRocketBaseB3FLockedDoor_NeedsPassword
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_LEARNED_RATICATE_TAIL, J_L206
	setvar VAR_RESULT, 1
J_L206:
	goto_if_eq VAR_RESULT, 0, J_TeamRocketBaseB3FLockedDoor_NeedsPassword
	goto J_TeamRocketBaseB3FLockedDoor_OpenSesame
J_TeamRocketBaseB3FLockedDoor_NeedsPassword:
	message J_TeamRocketBaseB3FLockedDoorNeedsPasswordText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TeamRocketBaseB3FLockedDoor_OpenSesame:
	message J_TeamRocketBaseB3FLockedDoorOpenSesameText
	waitmessage
	waitbuttonpress
	playse SE_DOOR
	setmetatile 10, 8, 4, FALSE
	setmetatile 11, 8, 4, FALSE
	setmetatile 10, 9, 4, FALSE
	setmetatile 11, 9, 4, FALSE
	special DrawWholeMapView
	closemessage
	setflag FLAG_J_OPENED_DOOR_TO_GIOVANNIS_OFFICE
	waitse
	return
J_TeamRocketBaseB3FOathScript::
	goto J_TeamRocketOathScript
J_TeamRocketBaseB3FProtein::
	finditem ITEM_PROTEIN, 1
	return
J_TeamRocketBaseB3FXSpecial::
	finditem ITEM_POTION, 1
	return
J_TeamRocketBaseB3FFullHeal::
	finditem ITEM_FULL_HEAL, 1
	return
J_TeamRocketBaseB3FIceHeal::
	finditem ITEM_ICE_HEAL, 1
	return
J_TeamRocketBaseB3FUltraBall::
	finditem ITEM_ULTRA_BALL, 1
	return
J_RocketBaseLanceApproachesPlayerMovement::
	walk_right
	step_end
J_RocketBaseLanceLeavesMovement::
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end
J_RocketBasePlayerApproachesBossLeftMovement::
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	face_up
	step_end
J_RocketBasePlayerApproachesBossRightMovement::
	walk_up
	walk_up
	walk_left
	walk_up
	walk_left
	walk_left
	face_up
	step_end
J_RocketBaseBossApproachesPlayerMovement::
	walk_down
	step_end
J_RocketBaseBossHitsTableMovement::
	walk_fast_right
	walk_fast_right
	step_end
J_RocketBaseBossLeavesMovement::
	lock_facing_direction
	jump_left
	unlock_facing_direction
	delay_8
	delay_8
	walk_slow_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	step_end
J_RocketBaseRivalEnterMovement::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end
J_RocketBaseRivalLeavesMovement::
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
J_RocketBaseRivalShovesPlayerMovement::
	lock_facing_direction
	walk_fast_right
	unlock_facing_direction
	step_end
J_LanceGetPasswordText::
	.string "LANCE: It takes\ntwo passwords to\pget into the\nboss's quarters.\pThose passwords\nare known only to\la few ROCKETS.\pThat ROCKET there\nvery graciously\ltold me so.\p{PLAYER}, let's go\nget the passwords.$"
J_TeamRocketBaseB3FRocketText::
	.string "Urrggh… The guy\nin the cape is\lincredibly tough…$"
J_RocketBaseRivalText::
	.string "…\pDidn't I tell you\nthat I was going\pto destroy TEAM\nROCKET?\p…Tell me, who was\nthe guy in the\pcape who used\ndragon POKéMON?\pMy POKéMON were no\nmatch at all.\pI don't care that\nI lost. I can beat\phim by getting\nstronger POKéMON.\pIt's what he said\nthat bothers me…\pHe told me that\nI don't love and\ptrust my POKéMON\nenough.\pI'm furious that I\nlost to a bleeding\lheart like him.\p…Humph! I don't\nhave the time for\lthe likes of you!$"
J_ExecutiveM4BeforeText::
	.string "What? Who are you?\nThis is the office\pof our leader,\nGIOVANNI.\pSince disbanding\nTEAM ROCKET three\pyears ago, he has\nbeen in training.\pBut we're certain\nhe will be back\psome day to assume\ncommand again.\pThat's why we're\nstanding guard.\pI won't let any-\none disturb this\lplace!$"
J_ExecutiveM4BeatenText::
	.string "I… I couldn't do a\nthing…\pGIOVANNI, please\nforgive me…$"
J_ExecutiveM4AfterText::
	.string "No, I can't let\nthis affect me.\pI have to inform\nthe others…$"
J_RocketBaseMurkrowText::
	.string "MURKROW: The\npassword is…\pHAIL GIOVANNI.$"
J_GruntF5SeenText::
	.string "Do I know the\npassword?\pMaybe.\pBut no weakling's\ngoing to get it!$"
J_GruntF5BeatenText::
	.string "All right. Stop.\nI'll tell you.$"
J_GruntF5AfterBattleText::
	.string "The password to\nthe boss's room is\pSLOWPOKETAIL.\pBut it's useless\nunless you have\ltwo passwords.$"
J_GruntM28SeenText::
	.string "Hyuck-hyuck-hyuck!\pYou're challenging\nme to a battle?\pHah! You're nuts,\nbut you have guts!\pI like that!\pIf you can beat\nme, I'll tell you\pa password to the\nboss's room!$"
J_GruntM28BeatenText::
	.string "Hyuck-hyuck-hyuck!\nYou're good!$"
J_GruntM28AfterBattleText::
	.string "Hyuck-hyuck-hyuck!\pThe password to\nthe boss's room…\pUh…, I think it is\nRATICATE TAIL.$"
J_ScientistRossSeenText::
	.string "I used to work for\nSILPH, but now I\prun research for\nTEAM ROCKET.\pA meddlesome child\nlike you needs to\lbe punished.$"
J_ScientistRossBeatenText::
	.string "A mere tactical\nerror cost me…$"
J_ScientistRossAfterBattleText::
	.string "A radio signal\nthat drives POKé-\lMON mad…\pMy experiment is a\ncomplete success.\pMy promotion is\nassured. This loss\pmeans absolutely\nnothing.$"
J_ScientistMitchSeenText::
	.string "I don't care that\nPOKéMON are hurt\lby our experiment.$"
J_ScientistMitchBeatenText::
	.string "Thinking is my\nstrong suit, not\lbattling.$"
J_ScientistMitchAfterBattleText::
	.string "If we turn up the\npower of our radio\psignal for broad-\ncast nationwide…\pThe very thought\nexcites me!$"
J_TeamRocketBaseB3FLockedDoorNeedsPasswordText::
	.string "The door's closed…\pIt needs two\npasswords to open.$"
J_TeamRocketBaseB3FLockedDoorOpenSesameText::
	.string "The door's closed…\p{PLAYER} entered\nthe two passwords.\pThe door opened!$"
J_TeamRocketBaseB3F_MapEvents::
