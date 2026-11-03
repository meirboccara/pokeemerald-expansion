@ KJH: translated from pokecrystal maps/GoldenrodGym.asm by kjh_tools/johto

JohtoGoldenrodGym_MapScripts::
	.byte 0

J_W_GoldenrodGymWhitneyScript::
	lock
	call J_GoldenrodGymWhitneyScript
	release
	end

J_T_TrainerLassCarrie::
	trainerbattle_single TRAINER_J_LASS_CARRIE, J_LassCarrieSeenText, J_LassCarrieBeatenText
	call J_TrainerLassCarrie_Script
	release
	end

J_T_TrainerLassBridget::
	trainerbattle_single TRAINER_J_LASS_BRIDGET, J_LassBridgetSeenText, J_LassBridgetBeatenText
	call J_TrainerLassBridget_Script
	release
	end

J_T_TrainerBeautyVictoria::
	trainerbattle_single TRAINER_J_BEAUTY_VICTORIA, J_BeautyVictoriaSeenText, J_BeautyVictoriaBeatenText
	call J_TrainerBeautyVictoria_Script
	release
	end

J_T_TrainerBeautySamantha::
	trainerbattle_single TRAINER_J_BEAUTY_SAMANTHA, J_BeautySamanthaSeenText, J_BeautySamanthaBeatenText
	call J_TrainerBeautySamantha_Script
	release
	end

J_W_GoldenrodGymGuideScript::
	lock
	call J_GoldenrodGymGuideScript
	release
	end

J_C_WhitneyCriesScript::
	lockall
	call J_WhitneyCriesScript
	releaseall
	end

J_S_GoldenrodGymStatue::
	lockall
	call J_GoldenrodGymStatue
	releaseall
	end

J_GoldenrodGym_MapScripts::
J_GoldenrodGymNoop1Scene::
	return
J_GoldenrodGymNoop2Scene::
	return
J_GoldenrodGymWhitneyScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_WHITNEY, J_L518
	setvar VAR_RESULT, 1
J_L518:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodGymWhitneyScript_FightDone
	message J_WhitneyBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_J_WHITNEY_WHITNEY1, J_WhitneyShouldntBeSoSeriousText
	setflag FLAG_J_BEAT_WHITNEY
	setflag FLAG_J_MADE_WHITNEY_CRY
	setvar VAR_J_SCENE_GOLDENROD_GYM, 1
	setflag (TRAINER_FLAGS_START + TRAINER_J_BEAUTY_VICTORIA)
	setflag (TRAINER_FLAGS_START + TRAINER_J_BEAUTY_SAMANTHA)
	setflag (TRAINER_FLAGS_START + TRAINER_J_LASS_CARRIE)
	setflag (TRAINER_FLAGS_START + TRAINER_J_LASS_BRIDGET)
J_GoldenrodGymWhitneyScript_FightDone:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_MADE_WHITNEY_CRY, J_L519
	setvar VAR_RESULT, 1
J_L519:
	goto_if_eq VAR_RESULT, 0, J_GoldenrodGymWhitneyScript_StoppedCrying
	message J_WhitneyYouMeanieText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodGymWhitneyScript_StoppedCrying:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM45_ATTRACT, J_L520
	setvar VAR_RESULT, 1
J_L520:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodGymWhitneyScript_GotAttract
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE03_GET, J_L521
	setvar VAR_RESULT, 1
J_L521:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodGymWhitneyScript_GotPlainBadge
	message J_WhitneyWhatDoYouWantText
	waitmessage
	waitbuttonpress
	waitse
	message J_PlayerReceivedPlainBadgeText
	waitmessage
	playse SE_SUCCESS
	waitse
	setflag FLAG_JOHTO_BADGE03_GET
	setvar VAR_0x8004, 7
	special KJH_CrystalReadVar
	call J_GoldenrodGymActivateRockets
J_GoldenrodGymWhitneyScript_GotPlainBadge:
	message J_WhitneyPlainBadgeText
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM45, 1
	goto_if_eq VAR_RESULT, 0, J_GoldenrodGymWhitneyScript_NoRoomForAttract
	setflag FLAG_J_GOT_TM45_ATTRACT
	message J_WhitneyAttractText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodGymWhitneyScript_GotAttract:
	message J_WhitneyGoodCryText
	waitmessage
	waitbuttonpress
J_GoldenrodGymWhitneyScript_NoRoomForAttract:
	closemessage
	return
J_GoldenrodGymActivateRockets::
	goto_if_eq VAR_RESULT, 7, J_GoldenrodGymActivateRockets_RadioTowerRockets
	goto_if_eq VAR_RESULT, 6, J_GoldenrodGymActivateRockets_GoldenrodRockets
	return
J_GoldenrodGymActivateRockets_GoldenrodRockets:
	goto J_GoldenrodRocketsScript
J_GoldenrodGymActivateRockets_RadioTowerRockets:
	goto J_RadioTowerRocketsScript
J_TrainerLassCarrie::
J_TrainerLassCarrie_Script:
	message J_LassCarrieAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_WhitneyCriesScript::
	applymovement 3, J_Movement_Exclamation
	waitmovement 0
	applymovement 3, J_BridgetWalksUpMovement
	waitmovement 3
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	message J_BridgetWhitneyCriesText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, J_BridgetWalksAwayMovement
	waitmovement 3
	setvar VAR_J_SCENE_GOLDENROD_GYM, 0
	clearflag FLAG_J_MADE_WHITNEY_CRY
	return
J_TrainerLassBridget::
J_TrainerLassBridget_Script:
	message J_LassBridgetAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBeautyVictoria::
J_TrainerBeautyVictoria_Script:
	message J_BeautyVictoriaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBeautySamantha::
J_TrainerBeautySamantha_Script:
	message J_BeautySamanthaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodGymGuideScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_WHITNEY, J_L522
	setvar VAR_RESULT, 1
J_L522:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodGymGuideScript_GoldenrodGymGuideWinScript
	message J_GoldenrodGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodGymGuideScript_GoldenrodGymGuideWinScript:
	message J_GoldenrodGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodGymStatue::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE03_GET, J_L523
	setvar VAR_RESULT, 1
J_L523:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodGymStatue_Beaten
	goto J_GymStatue1Script
J_GoldenrodGymStatue_Beaten:
	bufferstring STR_VAR_2, J_TrainerName_WHITNEY_WHITNEY1
	goto J_GymStatue2Script
J_BridgetWalksUpMovement::
	walk_left
	face_up
	step_end
J_BridgetWalksAwayMovement::
	walk_right
	face_left
	step_end
J_WhitneyBeforeText::
	.string "Hi! I'm WHITNEY!\pEveryone was into\nPOKéMON, so I got\linto it too!\pPOKéMON are\nsuper-cute!\pYou want to bat-\ntle? I'm warning\lyou--I'm good!$"
J_WhitneyShouldntBeSoSeriousText::
	.string "Sob…\p…Waaaaaaah!\nYou're mean!\pYou shouldn't be\nso serious! You…\lyou child, you!$"
J_WhitneyYouMeanieText::
	.string "Waaaaah!\pWaaaaah!\p…Snivel, hic…\n…You meanie!$"
J_WhitneyWhatDoYouWantText::
	.string "…Sniff…\pWhat? What do you\nwant? A BADGE?\pOh, right.\nI forgot. Here's\lPLAINBADGE.$"
J_PlayerReceivedPlainBadgeText::
	.string "{PLAYER} received\nPLAINBADGE.$"
J_WhitneyPlainBadgeText::
	.string "PLAINBADGE lets\nyour POKéMON use\pSTRENGTH outside\nof battle.\pIt also boosts\nyour POKéMON's\lSPEED.\pOh, you can have\nthis too!$"
J_WhitneyAttractText::
	.string "It's ATTRACT!\nIt makes full use\pof a POKéMON's\ncharm.\pIsn't it just per-\nfect for a cutie\llike me?$"
J_WhitneyGoodCryText::
	.string "Ah, that was a\ngood cry!\pCome for a visit\nagain! Bye-bye!$"
J_LassCarrieSeenText::
	.string "Don't let my\nPOKéMON's cute\plooks fool you.\nThey can whip you!$"
J_LassCarrieBeatenText::
	.string "Darn… I thought\nyou were weak…$"
J_LassCarrieAfterBattleText::
	.string "Do my POKéMON\nthink I'm cute?$"
J_LassBridgetSeenText::
	.string "I like cute POKé-\nMON better than\lstrong POKéMON.\pBut I have strong\nand cute POKéMON!$"
J_LassBridgetBeatenText::
	.string "Oh, no, no, no!$"
J_LassBridgetAfterBattleText::
	.string "I'm trying to beat\nWHITNEY, but…\lIt's depressing.\pI'm okay! If I\nlose, I'll just\ptry harder next\ntime!$"
J_BridgetWhitneyCriesText::
	.string "Oh, no. You made\nWHITNEY cry.\pIt's OK. She'll\nstop soon. She\palways cries when\nshe loses.$"
J_BeautyVictoriaSeenText::
	.string "Oh, you are a cute\nlittle trainer! \pI like you, but I\nwon't hold back!$"
J_BeautyVictoriaBeatenText::
	.string "Let's see… Oops,\nit's over?$"
J_BeautyVictoriaAfterBattleText::
	.string "Wow, you must be\ngood to beat me!\lKeep it up!$"
J_BeautySamanthaSeenText::
	.string "Give it your best\nshot, or I'll take\lyou down!$"
J_BeautySamanthaBeatenText::
	.string "No! Oh, MEOWTH,\nI'm so sorry!$"
J_BeautySamanthaAfterBattleText::
	.string "I taught MEOWTH\nmoves for taking\lon any type…$"
J_GoldenrodGymGuideText::
	.string "Yo! CHAMP in\nmaking!\pThis GYM is home\nto normal-type\lPOKéMON trainers.\pI recommend you\nuse fighting-type\lPOKéMON.$"
J_GoldenrodGymGuideWinText::
	.string "You won? Great! I\nwas busy admiring\lthe ladies here.$"
J_GoldenrodGym_MapEvents::
