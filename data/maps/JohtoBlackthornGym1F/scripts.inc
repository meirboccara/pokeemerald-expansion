@ KJH: translated from pokecrystal maps/BlackthornGym1F.asm by kjh_tools/johto

JohtoBlackthornGym1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, JohtoBlackthornGym1F_OnLoad
	.byte 0

JohtoBlackthornGym1F_OnLoad:
	call J_BlackthornGym1FBouldersCallback
	end

J_W_BlackthornGymClairScript::
	lock
	call J_BlackthornGymClairScript
	release
	end

J_T_TrainerCooltrainermMike::
	trainerbattle_single TRAINER_J_COOLTRAINERM_MIKE, J_CooltrainermMikeSeenText, J_CooltrainermMikeBeatenText
	call J_TrainerCooltrainermMike_Script
	release
	end

J_T_TrainerCooltrainermPaul::
	trainerbattle_single TRAINER_J_COOLTRAINERM_PAUL, J_CooltrainermPaulSeenText, J_CooltrainermPaulBeatenText
	call J_TrainerCooltrainermPaul_Script
	release
	end

J_T_TrainerCooltrainerfLola::
	trainerbattle_single TRAINER_J_COOLTRAINERF_LOLA, J_CooltrainerfLolaSeenText, J_CooltrainerfLolaBeatenText
	call J_TrainerCooltrainerfLola_Script
	release
	end

J_W_BlackthornGymGuideScript::
	lock
	call J_BlackthornGymGuideScript
	release
	end

J_S_BlackthornGymStatue::
	lockall
	call J_BlackthornGymStatue
	releaseall
	end

J_BlackthornGym1F_MapScripts::
J_BlackthornGym1FBouldersCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BOULDER_IN_BLACKTHORN_GYM_1, J_L291
	setvar VAR_RESULT, 1
J_L291:
	goto_if_eq VAR_RESULT, 0, J_BlackthornGym1FBouldersCallback_skip1
	setmetatile 8, 2, 25, TRUE
	setmetatile 9, 2, 5, FALSE
	setmetatile 8, 3, 46, FALSE
	setmetatile 9, 3, 5, FALSE
J_BlackthornGym1FBouldersCallback_skip1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BOULDER_IN_BLACKTHORN_GYM_2, J_L292
	setvar VAR_RESULT, 1
J_L292:
	goto_if_eq VAR_RESULT, 0, J_BlackthornGym1FBouldersCallback_skip2
	setmetatile 2, 4, 24, TRUE
	setmetatile 3, 4, 5, FALSE
	setmetatile 2, 5, 46, FALSE
	setmetatile 3, 5, 34, TRUE
J_BlackthornGym1FBouldersCallback_skip2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BOULDER_IN_BLACKTHORN_GYM_3, J_L293
	setvar VAR_RESULT, 1
J_L293:
	goto_if_eq VAR_RESULT, 0, J_BlackthornGym1FBouldersCallback_skip3
	setmetatile 8, 6, 25, TRUE
	setmetatile 9, 6, 5, FALSE
	setmetatile 8, 7, 46, FALSE
	setmetatile 9, 7, 5, FALSE
J_BlackthornGym1FBouldersCallback_skip3:
	return
J_BlackthornGymClairScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L294
	setvar VAR_RESULT, 1
J_L294:
	goto_if_ne VAR_RESULT, 0, J_BlackthornGymClairScript_AlreadyGotBadge
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_CLAIR, J_L295
	setvar VAR_RESULT, 1
J_L295:
	goto_if_ne VAR_RESULT, 0, J_BlackthornGymClairScript_FightDone
	message J_ClairIntroText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_J_CLAIR_CLAIR1, J_ClairWinText
	setflag FLAG_J_BEAT_CLAIR
	message J_ClairText_GoToDragonsDen
	waitmessage
	waitbuttonpress
	closemessage
	setflag (TRAINER_FLAGS_START + TRAINER_J_COOLTRAINERM_PAUL)
	setflag (TRAINER_FLAGS_START + TRAINER_J_COOLTRAINERM_CODY)
	setflag (TRAINER_FLAGS_START + TRAINER_J_COOLTRAINERM_MIKE)
	setflag (TRAINER_FLAGS_START + TRAINER_J_COOLTRAINERF_FRAN)
	setflag (TRAINER_FLAGS_START + TRAINER_J_COOLTRAINERF_LOLA)
	clearflag FLAG_J_MAHOGANY_MART_OWNERS
	setflag FLAG_J_BLACKTHORN_CITY_GRAMPS_BLOCKS_DRAGONS_DEN
	clearflag FLAG_J_BLACKTHORN_CITY_GRAMPS_NOT_BLOCKING_DRAGONS_DEN
	return
J_BlackthornGymClairScript_FightDone:
	message J_ClairText_TooMuchToExpect
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornGymClairScript_AlreadyGotBadge:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM24_DRAGONBREATH, J_L296
	setvar VAR_RESULT, 1
J_L296:
	goto_if_ne VAR_RESULT, 0, J_BlackthornGymClairScript_GotTM24
	message J_BlackthornGymClairText_YouKeptMeWaiting
	waitmessage
	waitbuttonpress
	additem ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, 0, J_BlackthornGymClairScript_BagFull
	bufferitemname STR_VAR_1, ITEM_POTION
	message J_BlackthornGymText_ReceivedTM24
	waitmessage
	playse SE_SUCCESS
	waitse
	setflag FLAG_J_GOT_TM24_DRAGONBREATH
	message J_BlackthornGymClairText_DescribeTM24
	waitmessage
	waitbuttonpress
	goto J_BlackthornGymClairScript_GotTM24
J_BlackthornGymClairScript_BagFull:
	message J_BlackthornGymClairText_BagFull
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornGymClairScript_GotTM24:
	message J_BlackthornGymClairText_League
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainermPaul::
J_TrainerCooltrainermPaul_Script:
	message J_CooltrainermPaulAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainermMike::
J_TrainerCooltrainermMike_Script:
	message J_CooltrainermMikeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainerfLola::
J_TrainerCooltrainerfLola_Script:
	message J_CooltrainerfLolaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornGymGuideScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_CLAIR, J_L297
	setvar VAR_RESULT, 1
J_L297:
	goto_if_ne VAR_RESULT, 0, J_BlackthornGymGuideScript_BlackthornGymGuideWinScript
	message J_BlackthornGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornGymGuideScript_BlackthornGymGuideWinScript:
	message J_BlackthornGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornGymStatue::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L298
	setvar VAR_RESULT, 1
J_L298:
	goto_if_ne VAR_RESULT, 0, J_BlackthornGymStatue_Beaten
	goto J_GymStatue1Script
J_BlackthornGymStatue_Beaten:
	bufferstring STR_VAR_2, J_TrainerName_CLAIR_CLAIR1
	goto J_GymStatue2Script
J_ClairIntroText::
	.string "I am CLAIR.\pThe world's best\ndragon master.\pI can hold my own\nagainst even the\pPOKéMON LEAGUE's\nELITE FOUR.\pDo you still want\nto take me on?\p…Fine.\nLet's do it!\pAs a GYM LEADER,\nI will use my full\ppower against any\nopponent!$"
J_ClairWinText::
	.string "I lost?\pI don't believe\nit. There must be\lsome mistake…$"
J_ClairText_GoToDragonsDen::
	.string "I won't admit\nthis.\pI may have lost,\nbut you're still\pnot ready for the\nPOKéMON LEAGUE.\pI know. You should\ntake the dragon\luser challenge.\pBehind this GYM is\na place called\lDRAGON'S DEN.\pThere is a small\nshrine at its\pcenter.\nGo there.\pIf you can prove\nthat you've lost\pyour lazy ideals,\nI will recognize\pyou as a trainer\nworthy of a GYM\lBADGE!$"
J_ClairText_TooMuchToExpect::
	.string "What's the matter?\pIs it too much to\nexpect of you?$"
J_BlackthornGymClairText_YouKeptMeWaiting::
	.string "You've kept me\nwaiting!\pHere! Take this!$"
J_BlackthornGymText_ReceivedTM24::
	.string "{PLAYER} received\nTM24.$"
J_BlackthornGymClairText_DescribeTM24::
	.string "That contains\nDRAGONBREATH.\pNo, it doesn't\nhave anything to\ldo with my breath.\pIf you don't want\nit, you don't have\lto take it.$"
J_BlackthornGymClairText_BagFull::
	.string "What is this? You\ndon't have room?$"
J_BlackthornGymClairText_League::
	.string "What's the matter?\pAren't you headed\nto the POKéMON\lLEAGUE?\pDon't you know\nwhere it is?\pFrom here, go to\nNEW BARK TOWN.\pThen SURF east.\nThe route there is\lvery tough.\pDon't you dare\nlose at the POKé-\lMON LEAGUE!\pIf you do, I'll\nfeel even worse\pabout having lost\nto you!\pGive it every-\nthing you've got.$"
J_CooltrainermPaulSeenText::
	.string "Your first battle\nagainst dragons?\pI'll show you how\ntough they are!$"
J_CooltrainermPaulBeatenText::
	.string "My dragon POKéMON\nlost?$"
J_CooltrainermPaulAfterBattleText::
	.string "LANCE told you\nthat he'd like to\psee you again?\nNot a chance!$"
J_CooltrainermMikeSeenText::
	.string "My chance of\nlosing? Not even\lone percent!$"
J_CooltrainermMikeBeatenText::
	.string "That's odd.$"
J_CooltrainermMikeAfterBattleText::
	.string "I know my short-\ncomings now.\pThanks for showing\nme!$"
J_CooltrainerfLolaSeenText::
	.string "Dragons are sacred\nPOKéMON.\pThey are full of\nlife energy.\pIf you're not\nserious, you won't\pbe able to beat\nthem.$"
J_CooltrainerfLolaBeatenText::
	.string "Way to go!$"
J_CooltrainerfLolaAfterBattleText::
	.string "Dragons are weak\nagainst dragon-\ltype moves.$"
J_BlackthornGymGuideText::
	.string "Yo! CHAMP in\nmaking!\pIt's been a long\njourney, but we\pare almost done!\nCount on me!\pCLAIR uses the\nmythical and sac-\lred dragon-type\lPOKéMON.\pYou can't damage\nthem very easily.\pBut you know,\nthey're supposed\pto be weak against\nice-type moves.$"
J_BlackthornGymGuideWinText::
	.string "You were great to\nbeat CLAIR!\pAll that's left is\nthe POKéMON LEAGUE\lchallenge.\pYou're on the way\nto becoming the\lPOKéMON CHAMPION!$"
J_BlackthornGym1F_MapEvents::
