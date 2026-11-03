@ KJH: translated from pokecrystal maps/Route32.asm by kjh_tools/johto

JohtoRoute32_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoRoute32_OnTransition
	.byte 0

JohtoRoute32_OnTransition:
	call J_Route32FriedaCallback
	end

J_T_TrainerFisherJustin::
	trainerbattle_single TRAINER_J_FISHER_JUSTIN, J_FisherJustinSeenText, J_FisherJustinBeatenText
	call J_TrainerFisherJustin_Script
	release
	end

J_T_TrainerFisherRalph1::
	trainerbattle_single TRAINER_J_FISHER_RALPH1, J_FisherRalph1SeenText, J_FisherRalph1BeatenText
	call J_TrainerFisherRalph1_Script
	release
	end

J_T_TrainerFisherHenry::
	trainerbattle_single TRAINER_J_FISHER_HENRY, J_FisherHenrySeenText, J_FisherHenryBeatenText
	call J_TrainerFisherHenry_Script
	release
	end

J_T_TrainerYoungsterAlbert::
	trainerbattle_single TRAINER_J_YOUNGSTER_ALBERT, J_YoungsterAlbertSeenText, J_YoungsterAlbertBeatenText
	call J_TrainerYoungsterAlbert_Script
	release
	end

J_T_TrainerYoungsterGordon::
	trainerbattle_single TRAINER_J_YOUNGSTER_GORDON, J_YoungsterGordonSeenText, J_YoungsterGordonBeatenText
	call J_TrainerYoungsterGordon_Script
	release
	end

J_T_TrainerCamperRoland::
	trainerbattle_single TRAINER_J_CAMPER_ROLAND, J_CamperRolandSeenText, J_CamperRolandBeatenText
	call J_TrainerCamperRoland_Script
	release
	end

J_T_TrainerPicnickerLiz1::
	trainerbattle_single TRAINER_J_PICNICKER_LIZ1, J_PicnickerLiz1SeenText, J_PicnickerLiz1BeatenText
	call J_TrainerPicnickerLiz1_Script
	release
	end

J_W_Route32CooltrainerMScript::
	lock
	call J_Route32CooltrainerMScript
	release
	end

J_T_TrainerBirdKeeperPeter::
	trainerbattle_single TRAINER_J_BIRD_KEEPER_PETER, J_BirdKeeperPeterSeenText, J_BirdKeeperPeterBeatenText
	call J_TrainerBirdKeeperPeter_Script
	release
	end

J_W_SlowpokeTailSalesmanScript::
	lock
	call J_SlowpokeTailSalesmanScript
	release
	end

J_W_Route32RoarTMGuyScript::
	lock
	call J_Route32RoarTMGuyScript
	release
	end

J_W_FriedaScript::
	lock
	call J_FriedaScript
	release
	end

J_C_Route32CooltrainerMStopsYouScene::
	lockall
	call J_Route32CooltrainerMStopsYouScene
	releaseall
	end

J_C_Route32WannaBuyASlowpokeTailScript::
	lockall
	call J_Route32WannaBuyASlowpokeTailScript
	releaseall
	end

J_S_Route32Sign::
	lockall
	call J_Route32Sign
	releaseall
	end

J_S_Route32RuinsSign::
	lockall
	call J_Route32RuinsSign
	releaseall
	end

J_S_Route32UnionCaveSign::
	lockall
	call J_Route32UnionCaveSign
	releaseall
	end

J_S_Route32PokecenterSign::
	lockall
	call J_Route32PokecenterSign
	releaseall
	end

J_Route32_MapScripts::
J_Route32Noop1Scene::
	return
J_Route32Noop2Scene::
	return
J_Route32Noop3Scene::
	return
J_Route32FriedaCallback::
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 5, J_Route32FriedaCallback_FriedaAppears
	setflag FLAG_J_ROUTE_32_FRIEDA_OF_FRIDAY
	return
J_Route32FriedaCallback_FriedaAppears:
	clearflag FLAG_J_ROUTE_32_FRIEDA_OF_FRIDAY
	return
J_Route32CooltrainerMScript::
	faceplayer
J_Route32CooltrainerMContinueScene::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_MIRACLE_SEED_IN_ROUTE_32, J_L403
	setvar VAR_RESULT, 1
J_L403:
	goto_if_ne VAR_RESULT, 0, J_Route32CooltrainerMContinueScene_GotMiracleSeed
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE01_GET, J_L404
	setvar VAR_RESULT, 1
J_L404:
	goto_if_eq VAR_RESULT, 0, J_Route32CooltrainerMContinueScene_DontHaveZephyrBadge
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TOGEPI_EGG_FROM_ELMS_AIDE, J_L405
	setvar VAR_RESULT, 1
J_L405:
	goto_if_ne VAR_RESULT, 0, J_Route32CooltrainerMContinueScene_GiveMiracleSeed
	message J_Route32CooltrainerMText_AideIsWaiting
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route32CooltrainerMContinueScene_GoToSproutTower:
	message J_Route32CooltrainerMText_UnusedSproutTower
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route32CooltrainerMContinueScene_GiveMiracleSeed:
	message J_Route32CooltrainerMText_HaveThisSeed
	waitmessage
	waitbuttonpress
	giveitem ITEM_MIRACLE_SEED, 1
	goto_if_eq VAR_RESULT, 0, J_Route32CooltrainerMContinueScene_BagFull
	setflag FLAG_J_GOT_MIRACLE_SEED_IN_ROUTE_32
	goto J_Route32CooltrainerMContinueScene_GotMiracleSeed
J_Route32CooltrainerMContinueScene_DontHaveZephyrBadge:
	message J_Route32CooltrainerMText_VioletGym
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route32CooltrainerMContinueScene_GotMiracleSeed:
	message J_Route32CooltrainerMText_ExperiencesShouldBeUseful
	waitmessage
	waitbuttonpress
J_Route32CooltrainerMContinueScene_BagFull:
	closemessage
	return
J_Route32CooltrainerMStopsYouScene::
	turnobject 8, DIR_WEST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	message J_Route32CooltrainerMText_WhatsTheHurry
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Route32CooltrainerMPushesYouBackToViolet
	applymovement 8, J_Movement_Route32CooltrainerMPushesYouBackToViolet
	waitmovement 8
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	call J_Route32CooltrainerMContinueScene
	applymovement 8, J_Movement_Route32CooltrainerMReset1
	waitmovement 8
	applymovement 8, J_Movement_Route32CooltrainerMReset2
	waitmovement 8
	return
J_Route32RoarTMGuyScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM05_ROAR, J_L406
	setvar VAR_RESULT, 1
J_L406:
	goto_if_ne VAR_RESULT, 0, J_Route32RoarTMGuyScript_AlreadyHaveRoar
	message J_Text_RoarIntro
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM05, 1
	goto_if_eq VAR_RESULT, 0, J_Route32RoarTMGuyScript_Finish
	setflag FLAG_J_GOT_TM05_ROAR
J_Route32RoarTMGuyScript_AlreadyHaveRoar:
	message J_Text_RoarOutro
	waitmessage
	waitbuttonpress
J_Route32RoarTMGuyScript_Finish:
	closemessage
	return
J_Route32WannaBuyASlowpokeTailScript::
	turnobject 10, DIR_SOUTH
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	goto J__OfferToSellSlowpokeTail
J_SlowpokeTailSalesmanScript::
	faceplayer
J__OfferToSellSlowpokeTail::
	setvar VAR_J_SCENE_ROUTE_32, 2
	message J_Text_MillionDollarSlowpokeTail
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J__OfferToSellSlowpokeTail_refused
	message J_Text_ThoughtKidsWereLoaded
	waitmessage
	waitbuttonpress
	closemessage
	return
J__OfferToSellSlowpokeTail_refused:
	message J_Text_RefusedToBuySlowpokeTail
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCamperRoland::
J_TrainerCamperRoland_Script:
	message J_CamperRolandAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerFisherJustin::
J_TrainerFisherJustin_Script:
	message J_FisherJustinAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerFisherRalph1::
J_TrainerFisherRalph1_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_RALPH_READY_FOR_REMATCH, J_L407
	setvar VAR_RESULT, 1
J_L407:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherRalph1_Rematch
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_QWILFISH_SWARM, J_L408
	setvar VAR_RESULT, 1
J_L408:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherRalph1_Swarm
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherRalph1_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RALPH_ASKED_FOR_PHONE_NUMBER, J_L409
	setvar VAR_RESULT, 1
J_L409:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherRalph1_AskAgain
	message J_FisherRalphAfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_RALPH_ASKED_FOR_PHONE_NUMBER
	call J_TrainerFisherRalph1_AskNumber1
	goto J_TrainerFisherRalph1_AskForNumber
J_TrainerFisherRalph1_AskAgain:
	call J_TrainerFisherRalph1_AskNumber2
J_TrainerFisherRalph1_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerFisherRalph1_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerFisherRalph1_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_FISHER_RALPH1
	call J_TrainerFisherRalph1_RegisteredNumber
	goto J_TrainerFisherRalph1_NumberAccepted
J_TrainerFisherRalph1_Rematch:
	call J_TrainerFisherRalph1_RematchStd
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 4, J_TrainerFisherRalph1_Fight4
	goto_if_eq VAR_RESULT, 3, J_TrainerFisherRalph1_Fight3
	goto_if_eq VAR_RESULT, 2, J_TrainerFisherRalph1_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerFisherRalph1_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerFisherRalph1_LoadFight0
J_TrainerFisherRalph1_Fight4:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L410
	setvar VAR_RESULT, 1
J_L410:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherRalph1_LoadFight4
J_TrainerFisherRalph1_Fight3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L411
	setvar VAR_RESULT, 1
J_L411:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherRalph1_LoadFight3
J_TrainerFisherRalph1_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_LAKE_OF_RAGE, J_L412
	setvar VAR_RESULT, 1
J_L412:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherRalph1_LoadFight2
J_TrainerFisherRalph1_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_ECRUTEAK, J_L413
	setvar VAR_RESULT, 1
J_L413:
	goto_if_ne VAR_RESULT, 0, J_TrainerFisherRalph1_LoadFight1
J_TrainerFisherRalph1_LoadFight0:
	trainerbattle_no_intro TRAINER_J_FISHER_RALPH1, J_FisherRalph1BeatenText
	clearflag FLAG_J_ENGINE_RALPH_READY_FOR_REMATCH
	return
J_TrainerFisherRalph1_LoadFight1:
	trainerbattle_no_intro TRAINER_J_FISHER_RALPH2, J_Text_Empty
	clearflag FLAG_J_ENGINE_RALPH_READY_FOR_REMATCH
	return
J_TrainerFisherRalph1_LoadFight2:
	trainerbattle_no_intro TRAINER_J_FISHER_RALPH3, J_Text_Empty
	clearflag FLAG_J_ENGINE_RALPH_READY_FOR_REMATCH
	return
J_TrainerFisherRalph1_LoadFight3:
	trainerbattle_no_intro TRAINER_J_FISHER_RALPH4, J_Text_Empty
	clearflag FLAG_J_ENGINE_RALPH_READY_FOR_REMATCH
	return
J_TrainerFisherRalph1_LoadFight4:
	trainerbattle_no_intro TRAINER_J_FISHER_RALPH5, J_Text_Empty
	clearflag FLAG_J_ENGINE_RALPH_READY_FOR_REMATCH
	return
J_TrainerFisherRalph1_Swarm:
	message J_FisherRalphSwarmText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerFisherRalph1_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerFisherRalph1_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerFisherRalph1_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerFisherRalph1_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerFisherRalph1_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerFisherRalph1_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerFisherRalph1_RematchStd:
	goto J_Std_Nop
	return
J_TrainerFisherHenry::
J_TrainerFisherHenry_Script:
	message J_FisherHenryAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPicnickerLiz1::
J_TrainerPicnickerLiz1_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_LIZ_READY_FOR_REMATCH, J_L414
	setvar VAR_RESULT, 1
J_L414:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerLiz1_Rematch
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerLiz1_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_LIZ_ASKED_FOR_PHONE_NUMBER, J_L415
	setvar VAR_RESULT, 1
J_L415:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerLiz1_AskAgain
	message J_PicnickerLiz1AfterText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_LIZ_ASKED_FOR_PHONE_NUMBER
	call J_TrainerPicnickerLiz1_AskNumber1
	goto J_TrainerPicnickerLiz1_AskForNumber
J_TrainerPicnickerLiz1_AskAgain:
	call J_TrainerPicnickerLiz1_AskNumber2
J_TrainerPicnickerLiz1_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerPicnickerLiz1_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerPicnickerLiz1_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_PICNICKER_LIZ1
	call J_TrainerPicnickerLiz1_RegisteredNumber
	goto J_TrainerPicnickerLiz1_NumberAccepted
J_TrainerPicnickerLiz1_Rematch:
	call J_TrainerPicnickerLiz1_RematchStd
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 4, J_TrainerPicnickerLiz1_Fight4
	goto_if_eq VAR_RESULT, 3, J_TrainerPicnickerLiz1_Fight3
	goto_if_eq VAR_RESULT, 2, J_TrainerPicnickerLiz1_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerPicnickerLiz1_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerPicnickerLiz1_LoadFight0
J_TrainerPicnickerLiz1_Fight4:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L416
	setvar VAR_RESULT, 1
J_L416:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerLiz1_LoadFight4
J_TrainerPicnickerLiz1_Fight3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L417
	setvar VAR_RESULT, 1
J_L417:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerLiz1_LoadFight3
J_TrainerPicnickerLiz1_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_ROCKET_HIDEOUT, J_L418
	setvar VAR_RESULT, 1
J_L418:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerLiz1_LoadFight2
J_TrainerPicnickerLiz1_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_ECRUTEAK, J_L419
	setvar VAR_RESULT, 1
J_L419:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerLiz1_LoadFight1
J_TrainerPicnickerLiz1_LoadFight0:
	trainerbattle_no_intro TRAINER_J_PICNICKER_LIZ1, J_PicnickerLiz1BeatenText
	clearflag FLAG_J_ENGINE_LIZ_READY_FOR_REMATCH
	return
J_TrainerPicnickerLiz1_LoadFight1:
	trainerbattle_no_intro TRAINER_J_PICNICKER_LIZ2, J_Text_Empty
	clearflag FLAG_J_ENGINE_LIZ_READY_FOR_REMATCH
	return
J_TrainerPicnickerLiz1_LoadFight2:
	trainerbattle_no_intro TRAINER_J_PICNICKER_LIZ3, J_Text_Empty
	clearflag FLAG_J_ENGINE_LIZ_READY_FOR_REMATCH
	return
J_TrainerPicnickerLiz1_LoadFight3:
	trainerbattle_no_intro TRAINER_J_PICNICKER_LIZ4, J_Text_Empty
	clearflag FLAG_J_ENGINE_LIZ_READY_FOR_REMATCH
	return
J_TrainerPicnickerLiz1_LoadFight4:
	trainerbattle_no_intro TRAINER_J_PICNICKER_LIZ5, J_Text_Empty
	clearflag FLAG_J_ENGINE_LIZ_READY_FOR_REMATCH
	return
J_TrainerPicnickerLiz1_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerPicnickerLiz1_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerPicnickerLiz1_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerPicnickerLiz1_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerPicnickerLiz1_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerPicnickerLiz1_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerPicnickerLiz1_RematchStd:
	goto J_Std_Nop
	return
J_TrainerYoungsterAlbert::
J_TrainerYoungsterAlbert_Script:
	message J_YoungsterAlbertAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerYoungsterGordon::
J_TrainerYoungsterGordon_Script:
	message J_YoungsterGordonAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBirdKeeperPeter::
J_TrainerBirdKeeperPeter_Script:
	message J_BirdKeeperPeterAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_FriedaScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_POISON_BARB_FROM_FRIEDA, J_L420
	setvar VAR_RESULT, 1
J_L420:
	goto_if_ne VAR_RESULT, 0, J_FriedaScript_Friday
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_ne VAR_RESULT, 5, J_FriedaScript_NotFriday
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_MET_FRIEDA_OF_FRIDAY, J_L421
	setvar VAR_RESULT, 1
J_L421:
	goto_if_ne VAR_RESULT, 0, J_FriedaScript_MetFrieda
	message J_MeetFriedaText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_MET_FRIEDA_OF_FRIDAY
J_FriedaScript_MetFrieda:
	message J_FriedaGivesGiftText
	waitmessage
	waitbuttonpress
	giveitem ITEM_POISON_BARB, 1
	goto_if_eq VAR_RESULT, 0, J_FriedaScript_Done
	setflag FLAG_J_GOT_POISON_BARB_FROM_FRIEDA
	message J_FriedaGaveGiftText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_FriedaScript_Friday:
	message J_FriedaFridayText
	waitmessage
	waitbuttonpress
J_FriedaScript_Done:
	closemessage
	return
J_FriedaScript_NotFriday:
	message J_FriedaNotFridayText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route32GreatBall::
	finditem ITEM_GREAT_BALL, 1
	return
J_Route32Repel::
	finditem ITEM_REPEL, 1
	return
J_Route32Sign::
	message J_Route32SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route32RuinsSign::
	message J_Route32RuinsSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route32UnionCaveSign::
	message J_Route32UnionCaveSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route32PokecenterSign::
	goto J_PokecenterSignScript
J_Route32HiddenGreatBall::
	finditem ITEM_GREAT_BALL
	return
J_Route32HiddenSuperPotion::
	finditem ITEM_SUPER_POTION
	return
J_Movement_Route32CooltrainerMPushesYouBackToViolet::
	walk_up
	walk_up
	step_end
J_Movement_Route32CooltrainerMReset1::
	walk_down
	step_end
J_Movement_Route32CooltrainerMReset2::
	walk_right
	step_end
J_Route32CooltrainerMText_WhatsTheHurry::
	.string "Wait up!\nWhat's the hurry?$"
J_Route32CooltrainerMText_AideIsWaiting::
	.string "{PLAYER}, right?\nSome guy wearing\pglasses was look-\ning for you.\pSee for yourself.\nHe's waiting for\pyou at the POKéMON\nCENTER.$"
J_Route32CooltrainerMText_UnusedSproutTower::
	.string "Have you gone to\nSPROUT TOWER?\pIf you ever visit\nVIOLET CITY, \pthey'll expect you\nto train there.\pThat's basic for\ntrainers. Go to\lSPROUT TOWER!$"
J_Route32CooltrainerMText_VioletGym::
	.string "Have you gone to\nthe POKéMON GYM?\pYou can test your\nPOKéMON and your-\lself there.\pIt's a rite of\npassage for all\ltrainers!$"
J_Route32CooltrainerMText_HaveThisSeed::
	.string "You have some good\nPOKéMON there.\pIt must be from\nthe training you\pgave them around\nVIOLET CITY.\pThe training at\nthe GYM must have\pbeen especially\nhelpful.\pAs a souvenir of\nVIOLET CITY, take\lthis.\pIt increases the\npower of grass-\ltype moves.$"
J_Route32CooltrainerMText_ExperiencesShouldBeUseful::
	.string "Your experiences\nin VIOLET CITY\pshould be useful\nfor your journey.$"
J_Text_MillionDollarSlowpokeTail::
	.string "How would you like\nto have this\ptasty, nutritious\nSLOWPOKETAIL?\pFor you right now,\njust ¥1,000,000!\pYou'll want this!$"
J_Text_ThoughtKidsWereLoaded::
	.string "Tch! I thought\nkids these days\lwere loaded…$"
J_Text_RefusedToBuySlowpokeTail::
	.string "You don't want it?\nThen scram. Shoo!$"
J_FisherJustinSeenText::
	.string "Whoa!\pYou made me lose\nthat fish!$"
J_FisherJustinBeatenText::
	.string "Sploosh!$"
J_FisherJustinAfterText::
	.string "Calm, collected…\nThe essence of\pfishing and POKé-\nMON is the same.$"
J_FisherRalph1SeenText::
	.string "I'm really good at\nboth fishing and\lPOKéMON.\pI'm not about to\nlose to any kid!$"
J_FisherRalph1BeatenText::
	.string "Tch! I tried to\nrush things…$"
J_FisherRalphAfterText::
	.string "Fishing is a life-\nlong passion.\pPOKéMON are life-\nlong friends!$"
J_FisherRalphSwarmText::
	.string "One, two, three…\nMuahahaha, what a\pgreat haul!\nI'm done! Go ahead\pand catch as many\nas you can, kid!$"
J_Route32UnusedFisher1SeenText::
	.string "I keep catching\nthe same POKéMON…\pMaybe a battle\nwill turn things\laround for me.$"
J_Route32UnusedFisher1BeatenText::
	.string "Nothing ever goes\nright for me now…$"
J_Route32UnusedFisher1AfterText::
	.string "How come the guy\nnext to me catches\lgood POKéMON?$"
J_Route32UnusedFisher2SeenText::
	.string "Heh, I'm on a roll\ntoday. How about a\lbattle, kid?$"
J_Route32UnusedFisher2BeatenText::
	.string "Oof. I wasn't\nlucky that time.$"
J_Route32UnusedFisher2AfterText::
	.string "You have to have a\ngood ROD if you\pwant to catch good\nPOKéMON.$"
J_FisherHenrySeenText::
	.string "My POKéMON?\nFreshly caught!$"
J_FisherHenryBeatenText::
	.string "SPLASH?$"
J_FisherHenryAfterText::
	.string "Freshly caught\nPOKéMON are no\pmatch for properly\nraised ones.$"
J_YoungsterAlbertSeenText::
	.string "I haven't seen you\naround before.\pSo you think you\nare pretty tough?$"
J_YoungsterAlbertBeatenText::
	.string "You're strong!$"
J_YoungsterAlbertAfterText::
	.string "I'm going to try\nto be the best\lwith my favorites.\pI'm not using the\nsame tough POKéMON\las everyone else.$"
J_YoungsterGordonSeenText::
	.string "I found some good\nPOKéMON in the\lgrass!\pI think they'll do\nit for me!$"
J_YoungsterGordonBeatenText::
	.string "Darn. I thought I\ncould win.$"
J_YoungsterGordonAfterText::
	.string "The grass is full\nof clingy things.$"
J_CamperRolandSeenText::
	.string "That glance…\nIt's intriguing.$"
J_CamperRolandBeatenText::
	.string "Hmmm. This is\ndisappointing.$"
J_CamperRolandAfterText::
	.string "If you don't want\nto battle, just\lavoid eye contact.$"
J_PicnickerLiz1SeenText::
	.string "Uh-huh. Yeah, and\nyou know…\pPardon? Battle?\nI'm on the phone.\pOh, all right. But\nmake it fast.$"
J_PicnickerLiz1BeatenText::
	.string "Oh! I've got to\nrelieve my anger!$"
J_PicnickerLiz1AfterText::
	.string "I was having a\nnice chat too.$"
J_BirdKeeperPeterSeenText::
	.string "That BADGE! It's\nfrom VIOLET CITY!\pYou beat FALKNER?$"
J_BirdKeeperPeterBeatenText::
	.string "I know what my\nweaknesses are.$"
J_BirdKeeperPeterAfterText::
	.string "I should train\nagain at the GYM\lin VIOLET CITY.$"
J_Route32UnusedText::
	.string "The fishermen\nyelled at me for\lbugging them…$"
J_Text_RoarIntro::
	.string "WROOOOAR!\nPEOPLE RUN WHEN I\pROAR! BUT YOU\nCAME LOOKING!\pTHAT PLEASES ME!\nNOW TAKE THIS!$"
J_Text_RoarOutro::
	.string "WROOOAR!\nIT'S ROAR!\pEVEN POKéMON RUN\nFROM A GOOD ROAR!$"
J_MeetFriedaText::
	.string "FRIEDA: Yahoo!\nIt's Friday!\pI'm FRIEDA of\nFriday!\pNice to meet you!$"
J_FriedaGivesGiftText::
	.string "Here's a POISON\nBARB for you!$"
J_FriedaGaveGiftText::
	.string "FRIEDA: Give it to\na POKéMON that has\lpoison-type moves.\pOh!\pIt's wicked!\pYou'll be shocked\nhow good it makes\lpoison moves!$"
J_FriedaFridayText::
	.string "FRIEDA: Hiya! What\nday do you like?\pI love Friday. No\ndoubt about it!\pDon't you think\nit's great too?$"
J_FriedaNotFridayText::
	.string "FRIEDA: Isn't it\nFriday today?\pIt's so boring\nwhen it's not!$"
J_Route32SignText::
	.string "ROUTE 32\pVIOLET CITY -\nAZALEA TOWN$"
J_Route32RuinsSignText::
	.string "RUINS OF ALPH\nEAST ENTRANCE$"
J_Route32UnionCaveSignText::
	.string "UNION CAVE\nAHEAD$"
J_Route32_MapEvents::
