@ KJH: translated from pokecrystal maps/MahoganyGym.asm by kjh_tools/johto

JohtoMahoganyGym_MapScripts::
	.byte 0

J_W_MahoganyGymPryceScript::
	lock
	call J_MahoganyGymPryceScript
	release
	end

J_T_TrainerSkierRoxanne::
	trainerbattle_single TRAINER_J_SKIER_ROXANNE, J_SkierRoxanneSeenText, J_SkierRoxanneBeatenText
	call J_TrainerSkierRoxanne_Script
	release
	end

J_T_TrainerBoarderRonald::
	trainerbattle_single TRAINER_J_BOARDER_RONALD, J_BoarderRonaldSeenText, J_BoarderRonaldBeatenText
	call J_TrainerBoarderRonald_Script
	release
	end

J_T_TrainerSkierClarissa::
	trainerbattle_single TRAINER_J_SKIER_CLARISSA, J_SkierClarissaSeenText, J_SkierClarissaBeatenText
	call J_TrainerSkierClarissa_Script
	release
	end

J_T_TrainerBoarderBrad::
	trainerbattle_single TRAINER_J_BOARDER_BRAD, J_BoarderBradSeenText, J_BoarderBradBeatenText
	call J_TrainerBoarderBrad_Script
	release
	end

J_T_TrainerBoarderDouglas::
	trainerbattle_single TRAINER_J_BOARDER_DOUGLAS, J_BoarderDouglasSeenText, J_BoarderDouglasBeatenText
	call J_TrainerBoarderDouglas_Script
	release
	end

J_W_MahoganyGymGuideScript::
	lock
	call J_MahoganyGymGuideScript
	release
	end

J_S_MahoganyGymStatue::
	lockall
	call J_MahoganyGymStatue
	releaseall
	end

J_MahoganyGym_MapScripts::
J_MahoganyGymPryceScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_PRYCE, J_L34
	setvar VAR_RESULT, 1
J_L34:
	goto_if_ne VAR_RESULT, 0, J_MahoganyGymPryceScript_FightDone
	message J_PryceText_Intro
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_J_PRYCE_PRYCE1, J_PryceText_Impressed
	setflag FLAG_J_BEAT_PRYCE
	message J_Text_ReceivedGlacierBadge
	waitmessage
	playse SE_SUCCESS
	waitse
	setflag FLAG_JOHTO_BADGE07_GET
	setvar VAR_0x8004, 7
	special KJH_CrystalReadVar
	call J_MahoganyGymActivateRockets
J_MahoganyGymPryceScript_FightDone:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM16_ICY_WIND, J_L35
	setvar VAR_RESULT, 1
J_L35:
	goto_if_ne VAR_RESULT, 0, J_PryceScript_Defeat
	setflag (TRAINER_FLAGS_START + TRAINER_J_SKIER_ROXANNE)
	setflag (TRAINER_FLAGS_START + TRAINER_J_SKIER_CLARISSA)
	setflag (TRAINER_FLAGS_START + TRAINER_J_BOARDER_RONALD)
	setflag (TRAINER_FLAGS_START + TRAINER_J_BOARDER_BRAD)
	setflag (TRAINER_FLAGS_START + TRAINER_J_BOARDER_DOUGLAS)
	message J_PryceText_GlacierBadgeSpeech
	waitmessage
	waitbuttonpress
	giveitem ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, 0, J_MahoganyGym_NoRoomForIcyWind
	setflag FLAG_J_GOT_TM16_ICY_WIND
	message J_PryceText_IcyWindSpeech
	waitmessage
	waitbuttonpress
	closemessage
	return
J_PryceScript_Defeat::
	message J_PryceText_CherishYourPokemon
	waitmessage
	waitbuttonpress
J_MahoganyGym_NoRoomForIcyWind::
	closemessage
	return
J_MahoganyGymActivateRockets::
	goto_if_eq VAR_RESULT, 7, J_MahoganyGymActivateRockets_RadioTowerRockets
	goto_if_eq VAR_RESULT, 6, J_MahoganyGymActivateRockets_GoldenrodRockets
	return
J_MahoganyGymActivateRockets_GoldenrodRockets:
	goto J_GoldenrodRocketsScript
J_MahoganyGymActivateRockets_RadioTowerRockets:
	goto J_RadioTowerRocketsScript
J_TrainerSkierRoxanne::
J_TrainerSkierRoxanne_Script:
	message J_SkierRoxanneAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSkierClarissa::
J_TrainerSkierClarissa_Script:
	message J_SkierClarissaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBoarderRonald::
J_TrainerBoarderRonald_Script:
	message J_BoarderRonaldAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBoarderBrad::
J_TrainerBoarderBrad_Script:
	message J_BoarderBradAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBoarderDouglas::
J_TrainerBoarderDouglas_Script:
	message J_BoarderDouglasAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyGymGuideScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_PRYCE, J_L36
	setvar VAR_RESULT, 1
J_L36:
	goto_if_ne VAR_RESULT, 0, J_MahoganyGymGuideScript_MahoganyGymGuideWinScript
	message J_MahoganyGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyGymGuideScript_MahoganyGymGuideWinScript:
	message J_MahoganyGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyGymStatue::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE07_GET, J_L37
	setvar VAR_RESULT, 1
J_L37:
	goto_if_ne VAR_RESULT, 0, J_MahoganyGymStatue_Beaten
	goto J_GymStatue1Script
J_MahoganyGymStatue_Beaten:
	bufferstring STR_VAR_2, J_TrainerName_PRYCE_PRYCE1
	goto J_GymStatue2Script
J_PryceText_Intro::
	.string "POKéMON have many\nexperiences in\ptheir lives, just \nlike we do. \pI, too, have seen\nand suffered much\lin my life.\pSince I am your\nelder, let me show\lyou what I mean.\pI have been with\nPOKéMON since\pbefore you were\nborn.\pI do not lose\neasily.\pI, PRYCE--the\nwinter trainer--\pshall demonstrate\nmy power!$"
J_PryceText_Impressed::
	.string "Ah, I am impressed\nby your prowess.\pWith your strong\nwill, I know you\pwill overcome all\nlife's obstacles.\pYou are worthy of\nthis BADGE!$"
J_Text_ReceivedGlacierBadge::
	.string "{PLAYER} received\nGLACIERBADGE.$"
J_PryceText_GlacierBadgeSpeech::
	.string "That BADGE will\nraise the SPECIAL\lstats of POKéMON.\pIt also lets your\nPOKéMON use WHIRL-\lPOOL to get across\lreal whirlpools.\pAnd this… This is\na gift from me!$"
J_PryceText_IcyWindSpeech::
	.string "That TM contains\nICY WIND.\pIt inflicts damage\nand lowers speed.\pIt demonstrates\nthe harshness of\lwinter.$"
J_PryceText_CherishYourPokemon::
	.string "When the ice and\nsnow melt, spring\larrives.\pYou and your POKé-\nMON will be to-\pgether for many\nyears to come.\pCherish your time\ntogether!$"
J_BoarderRonaldSeenText::
	.string "I'll freeze your\nPOKéMON, so you\lcan't do a thing!$"
J_BoarderRonaldBeatenText::
	.string "Darn. I couldn't\ndo a thing.$"
J_BoarderRonaldAfterBattleText::
	.string "I think there's a\nmove a POKéMON\pcan use while it's\nfrozen.$"
J_BoarderBradSeenText::
	.string "This GYM has a\nslippery floor.\pIt's fun, isn't\nit?\pBut hey--we're\nnot playing games\lhere!$"
J_BoarderBradBeatenText::
	.string "Do you see how\nserious we are?$"
J_BoarderBradAfterBattleText::
	.string "This GYM is great.\nI love boarding\lwith my POKéMON!$"
J_BoarderDouglasSeenText::
	.string "I know PRYCE's\nsecret.$"
J_BoarderDouglasBeatenText::
	.string "OK. I'll tell you\nPRYCE's secret.$"
J_BoarderDouglasAfterBattleText::
	.string "The secret behind\nPRYCE's power…\pHe meditates under\na waterfall daily\pto strengthen his\nmind and body.$"
J_SkierRoxanneSeenText::
	.string "To get to PRYCE,\nour GYM LEADER,\pyou need to think\nbefore you skate.$"
J_SkierRoxanneBeatenText::
	.string "I wouldn't lose to\nyou in skiing!$"
J_SkierRoxanneAfterBattleText::
	.string "If you don't skate\nwith precision,\pyou won't get far\nin this GYM.$"
J_SkierClarissaSeenText::
	.string "Check out my\nparallel turn!$"
J_SkierClarissaBeatenText::
	.string "No! You made me\nwipe out!$"
J_SkierClarissaAfterBattleText::
	.string "I shouldn't have\nbeen bragging\labout my skiing…$"
J_MahoganyGymGuideText::
	.string "PRYCE is a veteran\nwho has trained\pPOKéMON for some\n50 years.\pHe's said to be\ngood at freezing\popponents with\nice-type moves.\pThat means you\nshould melt him\pwith your burning\nambition!$"
J_MahoganyGymGuideWinText::
	.string "PRYCE is some-\nthing, but you're\lsomething else!\pThat was a hot\nbattle that\pbridged the gen-\neration gap!$"
J_MahoganyGym_MapEvents::
