@ KJH: translated from pokecrystal maps/VioletGym.asm by kjh_tools/johto

JohtoVioletGym_MapScripts::
	.byte 0

J_W_VioletGymFalknerScript::
	lock
	call J_VioletGymFalknerScript
	release
	end

J_T_TrainerBirdKeeperRod::
	trainerbattle_single TRAINER_J_BIRD_KEEPER_ROD, J_BirdKeeperRodSeenText, J_BirdKeeperRodBeatenText
	call J_TrainerBirdKeeperRod_Script
	release
	end

J_T_TrainerBirdKeeperAbe::
	trainerbattle_single TRAINER_J_BIRD_KEEPER_ABE, J_BirdKeeperAbeSeenText, J_BirdKeeperAbeBeatenText
	call J_TrainerBirdKeeperAbe_Script
	release
	end

J_W_VioletGymGuideScript::
	lock
	call J_VioletGymGuideScript
	release
	end

J_S_VioletGymStatue::
	lockall
	call J_VioletGymStatue
	releaseall
	end

J_VioletGym_MapScripts::
J_VioletGymFalknerScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_FALKNER, J_L448
	setvar VAR_RESULT, 1
J_L448:
	goto_if_ne VAR_RESULT, 0, J_VioletGymFalknerScript_FightDone
	message J_FalknerIntroText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_J_FALKNER_FALKNER1, J_FalknerWinLossText
	setflag FLAG_J_BEAT_FALKNER
	message J_ReceivedZephyrBadgeText
	waitmessage
	playse SE_SUCCESS
	waitse
	setflag FLAG_JOHTO_BADGE01_GET
	setvar VAR_0x8004, 7
	special KJH_CrystalReadVar
	call J_VioletGymActivateRockets
J_VioletGymFalknerScript_FightDone:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM31_MUD_SLAP, J_L449
	setvar VAR_RESULT, 1
J_L449:
	goto_if_ne VAR_RESULT, 0, J_VioletGymFalknerScript_SpeechAfterTM
	setflag (TRAINER_FLAGS_START + TRAINER_J_BIRD_KEEPER_ROD)
	setflag (TRAINER_FLAGS_START + TRAINER_J_BIRD_KEEPER_ABE)
	setvar VAR_J_SCENE_ELMS_LAB, 2
	message J_FalknerZephyrBadgeText
	waitmessage
	waitbuttonpress
	giveitem ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, 0, J_VioletGymFalknerScript_NoRoomForMudSlap
	setflag FLAG_J_GOT_TM31_MUD_SLAP
	message J_FalknerTMMudSlapText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletGymFalknerScript_SpeechAfterTM:
	message J_FalknerFightDoneText
	waitmessage
	waitbuttonpress
J_VioletGymFalknerScript_NoRoomForMudSlap:
	closemessage
	return
J_VioletGymActivateRockets::
	goto_if_eq VAR_RESULT, 7, J_VioletGymActivateRockets_RadioTowerRockets
	goto_if_eq VAR_RESULT, 6, J_VioletGymActivateRockets_GoldenrodRockets
	return
J_VioletGymActivateRockets_GoldenrodRockets:
	goto J_GoldenrodRocketsScript
J_VioletGymActivateRockets_RadioTowerRockets:
	goto J_RadioTowerRocketsScript
J_TrainerBirdKeeperRod::
J_TrainerBirdKeeperRod_Script:
	message J_BirdKeeperRodAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBirdKeeperAbe::
J_TrainerBirdKeeperAbe_Script:
	message J_BirdKeeperAbeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletGymGuideScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_FALKNER, J_L450
	setvar VAR_RESULT, 1
J_L450:
	goto_if_ne VAR_RESULT, 0, J_VioletGymGuideScript_VioletGymGuideWinScript
	message J_VioletGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletGymGuideScript_VioletGymGuideWinScript:
	message J_VioletGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletGymStatue::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE01_GET, J_L451
	setvar VAR_RESULT, 1
J_L451:
	goto_if_ne VAR_RESULT, 0, J_VioletGymStatue_Beaten
	goto J_GymStatue1Script
J_VioletGymStatue_Beaten:
	bufferstring STR_VAR_2, J_TrainerName_FALKNER_FALKNER1
	goto J_GymStatue2Script
J_FalknerIntroText::
	.string "I'm FALKNER, the\nVIOLET POKéMON GYM\lleader!\pPeople say you can\nclip flying-type\pPOKéMON's wings\nwith a jolt of\lelectricity…\pI won't allow such\ninsults to bird\lPOKéMON!\pI'll show you the\nreal power of the\pmagnificent bird\nPOKéMON!$"
J_FalknerWinLossText::
	.string "…Darn! My dad's\ncherished bird\lPOKéMON…\pAll right.\nTake this.\pIt's the official\nPOKéMON LEAGUE\lZEPHYRBADGE.$"
J_ReceivedZephyrBadgeText::
	.string "{PLAYER} received\nZEPHYRBADGE.$"
J_FalknerZephyrBadgeText::
	.string "ZEPHYRBADGE\nraises the attack\lpower of POKéMON.\pIt also enables\nPOKéMON to use\pFLASH, if they\nhave it, anytime.\pHere--take this\ntoo.$"
J_FalknerTMMudSlapText::
	.string "By using a TM, a\nPOKéMON will\pinstantly learn a\nnew move.\pAnd a TM is never\nused up--teach it\lagain and again!\pTM31 contains\nMUD-SLAP.\pIt reduces the\nenemy's accuracy\pwhile it causes\ndamage.\pIn other words, it\nis both defensive\land offensive.$"
J_FalknerFightDoneText::
	.string "There are POKéMON\nGYMS in cities and\ltowns ahead.\pYou should test\nyour skills at\lthese GYMS.\pI'm going to train\nharder to become\pthe greatest bird\nmaster!$"
J_BirdKeeperRodSeenText::
	.string "The keyword is\nguts!\pThose here are\ntraining night and\pday to become bird\nPOKéMON masters.\pCome on!$"
J_BirdKeeperRodBeatenText::
	.string "Gaaah!$"
J_BirdKeeperRodAfterBattleText::
	.string "FALKNER's skills\nare for real!\pDon't get cocky\njust because you\lbeat me!$"
J_BirdKeeperAbeSeenText::
	.string "Let me see if you\nare good enough to\lface FALKNER!$"
J_BirdKeeperAbeBeatenText::
	.string "This can't be\ntrue!$"
J_BirdKeeperAbeAfterBattleText::
	.string "This is pathetic,\nlosing to some\lrookie trainer…$"
J_VioletGymGuideText::
	.string "Hey! I'm no train-\ner but I can give\lsome advice!\pBelieve me!\nIf you believe, a\pchampionship dream\ncan come true.\pYou believe?\nThen listen.\pThe grass-type is\nweak against the\pflying-type. Keep\nthis in mind.$"
J_VioletGymGuideWinText::
	.string "Nice battle! Keep\nit up, and you'll\pbe the CHAMP in no\ntime at all!$"
J_VioletGym_MapEvents::
