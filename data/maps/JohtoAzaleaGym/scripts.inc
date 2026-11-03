@ KJH: translated from pokecrystal maps/AzaleaGym.asm by kjh_tools/johto

JohtoAzaleaGym_MapScripts::
	.byte 0

J_W_AzaleaGymBugsyScript::
	lock
	call J_AzaleaGymBugsyScript
	release
	end

J_T_TrainerBugCatcherBenny::
	trainerbattle_single TRAINER_J_BUG_CATCHER_BUG_CATCHER_BENNY, J_BugCatcherBennySeenText, J_BugCatcherBennyBeatenText
	call J_TrainerBugCatcherBenny_AfterScript
	release
	end

J_T_TrainerBugCatcherAl::
	trainerbattle_single TRAINER_J_BUG_CATCHER_AL, J_BugCatcherAlSeenText, J_BugCatcherAlBeatenText
	call J_TrainerBugCatcherAl_AfterScript
	release
	end

J_T_TrainerBugCatcherJosh::
	trainerbattle_single TRAINER_J_BUG_CATCHER_JOSH, J_BugCatcherJoshSeenText, J_BugCatcherJoshBeatenText
	call J_TrainerBugCatcherJosh_AfterScript
	release
	end

J_T_TrainerTwinsAmyandmay1::
	trainerbattle_single TRAINER_J_TWINS_AMYANDMAY1, J_TwinsAmyandmay1SeenText, J_TwinsAmyandmay1BeatenText
	call J_TrainerTwinsAmyandmay1_AfterScript
	release
	end

J_T_TrainerTwinsAmyandmay2::
	trainerbattle_single TRAINER_J_TWINS_AMYANDMAY2, J_TwinsAmyandmay2SeenText, J_TwinsAmyandmay2BeatenText
	call J_TrainerTwinsAmyandmay2_AfterScript
	release
	end

J_W_AzaleaGymGuideScript::
	lock
	call J_AzaleaGymGuideScript
	release
	end

J_S_AzaleaGymStatue::
	lockall
	call J_AzaleaGymStatue
	releaseall
	end

J_AzaleaGym_MapScripts::
J_AzaleaGymBugsyScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_BUGSY, J_L360
	setvar VAR_RESULT, 1
J_L360:
	goto_if_ne VAR_RESULT, 0, J_AzaleaGymBugsyScript_FightDone
	message J_BugsyText_INeverLose
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_J_BUGSY_BUGSY1, J_BugsyText_ResearchIncomplete
	setflag FLAG_J_BEAT_BUGSY
	message J_Text_ReceivedHiveBadge
	waitmessage
	playse SE_SUCCESS
	waitse
	setflag FLAG_JOHTO_BADGE02_GET
	setvar VAR_0x8004, 7
	special KJH_CrystalReadVar
	call J_AzaleaGymActivateRockets
J_AzaleaGymBugsyScript_FightDone:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM49_FURY_CUTTER, J_L361
	setvar VAR_RESULT, 1
J_L361:
	goto_if_ne VAR_RESULT, 0, J_AzaleaGymBugsyScript_GotFuryCutter
	setflag (TRAINER_FLAGS_START + TRAINER_J_TWINS_AMYANDMAY2)
	setflag (TRAINER_FLAGS_START + TRAINER_J_BUG_CATCHER_BUG_CATCHER_BENNY)
	setflag (TRAINER_FLAGS_START + TRAINER_J_BUG_CATCHER_AL)
	setflag (TRAINER_FLAGS_START + TRAINER_J_BUG_CATCHER_JOSH)
	message J_BugsyText_HiveBadgeSpeech
	waitmessage
	waitbuttonpress
	giveitem ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, 0, J_AzaleaGymBugsyScript_NoRoomForFuryCutter
	setflag FLAG_J_GOT_TM49_FURY_CUTTER
	message J_BugsyText_FuryCutterSpeech
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaGymBugsyScript_GotFuryCutter:
	message J_BugsyText_BugMonsAreDeep
	waitmessage
	waitbuttonpress
J_AzaleaGymBugsyScript_NoRoomForFuryCutter:
	closemessage
	return
J_AzaleaGymActivateRockets::
	goto_if_eq VAR_RESULT, 7, J_AzaleaGymActivateRockets_RadioTowerRockets
	goto_if_eq VAR_RESULT, 6, J_AzaleaGymActivateRockets_GoldenrodRockets
	return
J_AzaleaGymActivateRockets_GoldenrodRockets:
	goto J_GoldenrodRocketsScript
J_AzaleaGymActivateRockets_RadioTowerRockets:
	goto J_RadioTowerRocketsScript
J_TrainerTwinsAmyandmay1::
J_TrainerTwinsAmyandmay1_AfterScript:
	message J_TwinsAmyandmay1AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerTwinsAmyandmay2::
J_TrainerTwinsAmyandmay2_AfterScript:
	message J_TwinsAmyandmay2AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBugCatcherBenny::
J_TrainerBugCatcherBenny_AfterScript:
	message J_BugCatcherBennyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBugCatcherAl::
J_TrainerBugCatcherAl_AfterScript:
	message J_BugCatcherAlAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBugCatcherJosh::
J_TrainerBugCatcherJosh_AfterScript:
	message J_BugCatcherJoshAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaGymGuideScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_BUGSY, J_L362
	setvar VAR_RESULT, 1
J_L362:
	goto_if_ne VAR_RESULT, 0, J_AzaleaGymGuideScript_AzaleaGymGuideWinScript
	message J_AzaleaGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaGymGuideScript_AzaleaGymGuideWinScript:
	message J_AzaleaGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_AzaleaGymStatue::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE02_GET, J_L363
	setvar VAR_RESULT, 1
J_L363:
	goto_if_ne VAR_RESULT, 0, J_AzaleaGymStatue_Beaten
	goto J_GymStatue1Script
J_AzaleaGymStatue_Beaten:
	bufferstring STR_VAR_2, J_TrainerName_BUGSY_BUGSY1
	goto J_GymStatue2Script
J_BugsyText_INeverLose::
	.string "I'm BUGSY!\nI never lose when\pit comes to bug\nPOKéMON.\pMy research is\ngoing to make me\pthe authority on\nbug POKéMON!\pLet me demonstrate\nwhat I've learned\lfrom my studies.$"
J_BugsyText_ResearchIncomplete::
	.string "Whoa, amazing!\nYou're an expert\lon POKéMON!\pMy research isn't\ncomplete yet.\pOK, you win. Take\nthis BADGE.$"
J_Text_ReceivedHiveBadge::
	.string "{PLAYER} received\nHIVEBADGE.$"
J_BugsyText_HiveBadgeSpeech::
	.string "Do you know the\nbenefits of HIVE-\lBADGE?\pIf you have it,\nPOKéMON up to L30\pwill obey you,\neven traded ones.\pPOKéMON that know\nCUT will be able\pto use it outside\nof battle too.\pHere, I also want\nyou to have this.$"
J_BugsyText_FuryCutterSpeech::
	.string "TM49 contains\nFURY CUTTER.\pIf you don't miss,\nit gets stronger\levery turn.\pThe longer your\nbattle goes, the\lbetter it gets.\pIsn't that great?\nI discovered it!$"
J_BugsyText_BugMonsAreDeep::
	.string "Bug POKéMON are\ndeep. There are\pmany mysteries to\nbe explored.\pStudy your favor-\nites thoroughly.$"
J_BugCatcherBennySeenText::
	.string "Bug POKéMON evolve\nyoung. So they get\pstronger that much\nfaster.$"
J_BugCatcherBennyBeatenText::
	.string "Just evolving\nisn't enough!$"
J_BugCatcherBennyAfterBattleText::
	.string "POKéMON become\nstronger if they\levolve. Really!$"
J_BugCatcherAlSeenText::
	.string "Bug POKéMON are\ncool and tough!\pI'll prove it to\nyou!$"
J_BugCatcherAlBeatenText::
	.string "You proved how\ntough you are…$"
J_BugCatcherAlAfterBattleText::
	.string "They're so cool,\nbut most girls\pdon't like bug\nPOKéMON.\pI don't know why…$"
J_BugCatcherJoshSeenText::
	.string "You saved all the\nSLOWPOKE? Whew,\lyou're mighty!\pBut my grown-up\nPOKéMON are pretty\ltough too!$"
J_BugCatcherJoshBeatenText::
	.string "Urrgggh!$"
J_BugCatcherJoshAfterBattleText::
	.string "I guess I should\nteach them better\lmoves…$"
J_TwinsAmyandmay1SeenText::
	.string "AMY: Hi! Are you\nchallenging the\lLEADER? No way!$"
J_TwinsAmyandmay1BeatenText::
	.string "AMY & MAY: Oh,\ndouble goodness!$"
J_TwinsAmyandmay1AfterBattleText::
	.string "AMY: You're\nreally strong!$"
J_TwinsAmyandmay2SeenText::
	.string "MAY: You want to\nsee the LEADER?\lWe come first!$"
J_TwinsAmyandmay2BeatenText::
	.string "AMY & MAY: Oh,\ndouble goodness!$"
J_TwinsAmyandmay2AfterBattleText::
	.string "MAY: Our bug POKé-\nMON lost! Oh, what\la shame.$"
J_AzaleaGymGuideText::
	.string "Yo, challenger!\pBUGSY's young, but\nhis knowledge of\pbug POKéMON is for\nreal.\pIt's going to be\ntough without my\ladvice.\pLet's see… Bug\nPOKéMON don't like\lfire.\pFlying-type moves\nare super-effec-\ltive too.$"
J_AzaleaGymGuideWinText::
	.string "Well done! That\nwas a great clash\pof talented young\ntrainers.\pWith people like\nyou, the future of\lPOKéMON is bright!$"
J_AzaleaGym_MapEvents::
