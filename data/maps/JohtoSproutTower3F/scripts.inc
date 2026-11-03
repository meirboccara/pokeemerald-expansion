@ KJH: translated from pokecrystal maps/SproutTower3F.asm by kjh_tools/johto

JohtoSproutTower3F_MapScripts::
	.byte 0

J_T_TrainerSageJin::
	trainerbattle_single TRAINER_J_SAGE_JIN, J_SageJinSeenText, J_SageJinBeatenText
	call J_TrainerSageJin_Script
	release
	end

J_T_TrainerSageTroy::
	trainerbattle_single TRAINER_J_SAGE_TROY, J_SageTroySeenText, J_SageTroyBeatenText
	call J_TrainerSageTroy_Script
	release
	end

J_W_SageLiScript::
	lock
	call J_SageLiScript
	release
	end

J_T_TrainerSageNeal::
	trainerbattle_single TRAINER_J_SAGE_NEAL, J_SageNealSeenText, J_SageNealBeatenText
	call J_TrainerSageNeal_Script
	release
	end

J_C_SproutTower3FRivalScene::
	lockall
	call J_SproutTower3FRivalScene
	releaseall
	end

J_S_SproutTower3FStatue::
	lockall
	call J_SproutTower3FStatue
	releaseall
	end

J_S_SproutTower3FPainting::
	lockall
	call J_SproutTower3FPainting
	releaseall
	end

J_SproutTower3F_MapScripts::
J_SproutTower3FNoop1Scene::
	return
J_SproutTower3FNoop2Scene::
	return
J_SproutTower3FRivalScene::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	fadeoutbgm 0
	playse SE_M_COMET_PUNCH
	playse SE_ELEVATOR
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 4
	special ShakeScreen
	delay 40
	delay 15
	playse SE_M_COMET_PUNCH
	playse SE_ELEVATOR
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 4
	special ShakeScreen
	delay 40
	applymovement OBJ_EVENT_ID_PLAYER, J_SproutTower3FPlayerApproachesRivalMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 7, J_SproutTower3FRivalApproachesElderMovement
	waitmovement 7
	message J_SproutTowerElderLecturesRivalText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 7, J_Movement_Exclamation
	waitmovement 0
	turnobject 7, DIR_SOUTH
	delay 15
	applymovement 7, J_SproutTower3FRivalLeavesElderMovement
	waitmovement 7
	playbgm MUS_RG_ENCOUNTER_RIVAL, FALSE
	message J_SproutTowerRivalOnlyCareAboutStrongText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 7, DIR_NORTH
	message J_SproutTowerRivalUsedEscapeRopeText
	waitmessage
	delay 15
	closemessage
	playse SE_WARP_IN
	fadescreen FADE_TO_BLACK
	removeobject 7
	waitse
	fadescreen FADE_FROM_BLACK
	setvar VAR_J_SCENE_SPROUT_TOWER_3F, 1
	fadedefaultbgm
	return
J_SageLiScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_HM05_FLASH, J_L62
	setvar VAR_RESULT, 1
J_L62:
	goto_if_ne VAR_RESULT, 0, J_SageLiScript_GotFlash
	message J_SageLiSeenText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_J_SAGE_LI, J_SageLiBeatenText
	message J_SageLiTakeThisFlashText
	waitmessage
	waitbuttonpress
	giveitem ITEM_HM05, 1
	setflag FLAG_J_GOT_HM05_FLASH
	setflag FLAG_J_BEAT_SAGE_LI
	message J_SageLiFlashExplanationText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SageLiScript_GotFlash:
	message J_SageLiAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSageJin::
J_TrainerSageJin_Script:
	message J_SageJinAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSageTroy::
J_TrainerSageTroy_Script:
	message J_SageTroyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSageNeal::
J_TrainerSageNeal_Script:
	message J_SageNealAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SproutTower3FPainting::
	message J_SproutTower3FPaintingText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SproutTower3FStatue::
	message J_SproutTower3FStatueText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SproutTower3FPotion::
	finditem ITEM_POTION, 1
	return
J_SproutTower3FEscapeRope::
	finditem ITEM_ESCAPE_ROPE, 1
	return
J_SproutTower3FPlayerApproachesRivalMovement::
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
J_SproutTower3FRivalApproachesElderMovement::
	walk_up
	step_end
J_SproutTower3FRivalLeavesElderMovement::
	walk_right
	walk_down
	step_end
J_SproutTowerElderLecturesRivalText::
	.string "ELDER: You are in-\ndeed skilled as a\ltrainer.\pAs promised, here\nis your HM.\pBut let me say\nthis: You should\ptreat your\nPOKéMON better.\pThe way you battle\nis far too harsh.\pPOKéMON are not\ntools of war…$"
J_SproutTowerRivalOnlyCareAboutStrongText::
	.string "…\n…Humph!\pHe claims to be\nthe ELDER but\lhe's weak.\pIt stands to\nreason.\pI'd never lose to\nfools who babble\pabout being nice\nto POKéMON.\pI only care about\nstrong POKéMON\lthat can win.\pI really couldn't\ncare less about\lweak POKéMON.$"
J_SproutTowerRivalUsedEscapeRopeText::
	.string "{RIVAL} used an\nESCAPE ROPE!$"
J_SageLiSeenText::
	.string "So good of you to\ncome here!\pSPROUT TOWER is a\nplace of training.\pPeople and POKéMON\ntest their bonds\pto build a bright\nfuture together.\pI am the final\ntest.\pAllow me to check\nthe ties between\pyour POKéMON and\nyou!$"
J_SageLiBeatenText::
	.string "Ah, excellent!$"
J_SageLiTakeThisFlashText::
	.string "You and your POKé-\nMON should have\pno problem using\nthis move.\pTake this FLASH\nHM.$"
J_SageLiFlashExplanationText::
	.string "FLASH illuminates\neven the darkest\lof all places.\pBut to use it out\nof battle, you\pneed the BADGE\nfrom VIOLET's GYM.$"
J_SageLiAfterBattleText::
	.string "I hope you learn\nand grow from your\ljourney.$"
J_SageJinSeenText::
	.string "I train to find\nenlightenment in\lPOKéMON!$"
J_SageJinBeatenText::
	.string "My training is\nincomplete…$"
J_SageJinAfterBattleText::
	.string "As POKéMON grow\nstronger, so does\lthe trainer.\pNo, wait. As the\ntrainer grows\pstronger, so do\nthe POKéMON.$"
J_SageTroySeenText::
	.string "Let me see how\nmuch you trust\lyour POKéMON.$"
J_SageTroyBeatenText::
	.string "Yes, your trust is\nreal!$"
J_SageTroyAfterBattleText::
	.string "It is not far to\nthe ELDER.$"
J_SageNealSeenText::
	.string "The ELDER's HM\nlights even pitch-\lblack darkness.$"
J_SageNealBeatenText::
	.string "It is my head that\nis bright!$"
J_SageNealAfterBattleText::
	.string "Let there be light\non your journey.$"
J_SproutTower3FPaintingText::
	.string "It's a powerful\npainting of a\lBELLSPROUT.$"
J_SproutTower3FStatueText::
	.string "A POKéMON statue…\pIt looks very\ndistinguished.$"
J_SproutTower3F_MapEvents::
