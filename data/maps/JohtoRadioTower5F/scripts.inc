@ KJH: translated from pokecrystal maps/RadioTower5F.asm by kjh_tools/johto

JohtoRadioTower5F_MapScripts::
	.byte 0

J_W_Director::
	lock
	call J_Director
	release
	end

J_T_TrainerExecutivef1::
	trainerbattle_single TRAINER_J_EXECUTIVEF_EXECUTIVEF_1, J_Executivef1SeenText, J_Executivef1BeatenText
	call J_TrainerExecutivef1_Script
	release
	end

J_W_Ben::
	lock
	call J_Ben
	release
	end

J_C_FakeDirectorScript::
	lockall
	call J_FakeDirectorScript
	releaseall
	end

J_C_RadioTower5FRocketBossScript::
	lockall
	call J_RadioTower5FRocketBossScript
	releaseall
	end

J_S_RadioTower5FDirectorsOfficeSign::
	lockall
	call J_RadioTower5FDirectorsOfficeSign
	releaseall
	end

J_S_RadioTower5FStudio1Sign::
	lockall
	call J_RadioTower5FStudio1Sign
	releaseall
	end

J_S_RadioTower5FBookshelf::
	lockall
	call J_RadioTower5FBookshelf
	releaseall
	end

J_RadioTower5F_MapScripts::
J_RadioTower5FNoop1Scene::
	return
J_RadioTower5FNoop2Scene::
	return
J_RadioTower5FNoop3Scene::
	return
J_FakeDirectorScript::
	turnobject 1, DIR_NORTH
	applymovement 1, J_Movement_Exclamation
	waitmovement 0
	message J_FakeDirectorTextBefore1
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_FakeDirectorMovement
	waitmovement 1
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	message J_FakeDirectorTextBefore2
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_LAST_TALKED, 1
	trainerbattle_no_intro TRAINER_J_EXECUTIVEM_EXECUTIVEM_3, J_FakeDirectorWinText
	message J_FakeDirectorTextAfter
	waitmessage
	waitbuttonpress
	bufferstring STR_VAR_2, J_ItemName_BASEMENT_KEY
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message J_Text_ReceivedKeyItem
	waitmessage
	waitfanfare
	setflag FLAG_J_HAS_BASEMENT_KEY
	setvar VAR_RESULT, 1
	closemessage
	setvar VAR_J_SCENE_RADIO_TOWER_5F, 1
	setflag FLAG_J_BEAT_ROCKET_EXECUTIVEM_3
	return
J_Director::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L111
	setvar VAR_RESULT, 1
J_L111:
	goto_if_ne VAR_RESULT, 0, J_Director_TrueDirector
	message J_FakeDirectorTextAfter
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Director_TrueDirector:
	message J_RadioTower5FDirectorText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerExecutivef1::
J_TrainerExecutivef1_Script:
	message J_Executivef1AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower5FRocketBossScript::
	applymovement OBJ_EVENT_ID_PLAYER, J_RadioTower5FPlayerTwoStepsLeftMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	turnobject 2, DIR_EAST
	message J_RadioTower5FRocketBossBeforeText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_LAST_TALKED, 2
	trainerbattle_no_intro TRAINER_J_EXECUTIVEM_EXECUTIVEM_1, J_RadioTower5FRocketBossWinText
	message J_RadioTower5FRocketBossAfterText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 2
	removeobject 3
	delay 15
	fadescreen FADE_FROM_BLACK
	setflag FLAG_J_BEAT_ROCKET_EXECUTIVEM_1
	setflag FLAG_J_CLEARED_RADIO_TOWER
	clearflag FLAG_KJH_HIDE_OLIVINE_ADMINS
	clearflag FLAG_J_ENGINE_ROCKETS_IN_RADIO_TOWER
	setflag FLAG_J_GOLDENROD_CITY_ROCKET_SCOUT
	setflag FLAG_J_GOLDENROD_CITY_ROCKET_TAKEOVER
	setflag FLAG_J_RADIO_TOWER_ROCKET_TAKEOVER
	clearflag FLAG_J_MAHOGANY_MART_OWNERS
	clearflag FLAG_J_ENGINE_ROCKETS_IN_MAHOGANY
	clearflag FLAG_J_GOLDENROD_CITY_CIVILIANS
	clearflag FLAG_J_RADIO_TOWER_CIVILIANS_AFTER
	setflag FLAG_J_BLACKTHORN_CITY_SUPER_NERD_BLOCKS_GYM
	clearflag FLAG_J_BLACKTHORN_CITY_SUPER_NERD_DOES_NOT_BLOCK_GYM
	fadedefaultbgm
	removeobject 1
	setobjectxyperm 1, 12, 0
	addobject 1
	applymovement 1, J_RadioTower5FDirectorWalksIn
	waitmovement 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	message J_RadioTower5FDirectorThankYouText
	waitmessage
	waitbuttonpress
	bufferstring STR_VAR_2, J_ItemName_CLEAR_BELL
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message J_Text_ReceivedKeyItem
	waitmessage
	waitfanfare
	setflag FLAG_J_HAS_CLEAR_BELL
	setvar VAR_RESULT, 1
	message J_RadioTower5FDirectorDescribeClearBellText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_J_SCENE_RADIO_TOWER_5F, 2
	setvar VAR_J_SCENE_ECRUTEAK_TIN_TOWER_ENTRANCE, 0
	setflag FLAG_J_GOT_CLEAR_BELL
	setflag FLAG_J_TEAM_ROCKET_DISBANDED
	goto J_RadioTower5FRocketBossScript_UselessJump
J_RadioTower5FRocketBossScript_UselessJump:
	applymovement 1, J_RadioTower5FDirectorWalksOut
	waitmovement 1
	playse SE_EXIT
	removeobject 1
	return
J_Ben::
	faceplayer
	message J_BenText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower5FUltraBall::
	finditem ITEM_ULTRA_BALL, 1
	return
J_RadioTower5FDirectorsOfficeSign::
	message J_RadioTower5FDirectorsOfficeSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower5FStudio1Sign::
	message J_RadioTower5FStudio1SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower5FBookshelf::
	goto J_MagazineBookshelfScript
J_FakeDirectorMovement::
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end
J_RadioTower5FDirectorWalksIn::
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_left
	step_end
J_RadioTower5FDirectorWalksOut::
	walk_right
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end
J_RadioTower5FPlayerTwoStepsLeftMovement::
	walk_left
	walk_left
	step_end
J_FakeDirectorTextBefore1::
	.string "Y-you! You came to\nrescue me?$"
J_FakeDirectorTextBefore2::
	.string "Is that what you\nwere expecting?\pWrong!\nI'm an imposter!\pI pretended to be\nthe real thing to\pprepare for our\ntakeover.\pDo you want to\nknow where we hid\lthe real DIRECTOR?\pSure, I'll tell\nyou. But only if\lyou can beat me!$"
J_FakeDirectorWinText::
	.string "OK, OK. I'll tell\nyou where he is.$"
J_FakeDirectorTextAfter::
	.string "We stashed the\nreal DIRECTOR in\pthe UNDERGROUND\nWAREHOUSE.\pIt's at the far\nend of the UNDER-\lGROUND.\pBut I doubt you'll\nget that far.$"
J_Executivef1SeenText::
	.string "Remember me from\nthe HIDEOUT in\lMAHOGANY TOWN?\pI lost then, but I\nwon't this time.$"
J_Executivef1BeatenText::
	.string "This can't be\nhappening!\pI fought hard, but\nI still lost…$"
J_Executivef1AfterBattleText::
	.string "{PLAYER}, isn't it?\pA brat like you\nwon't appreciate\pthe magnificence\nof TEAM ROCKET.\pThat's too bad.\nI really admire\lyour power.$"
J_RadioTower5FRocketBossBeforeText::
	.string "Oh? You made it this far?\n"
	.string "Wait… I know that face.\p"
	.string "You're the brat who crushed\n"
	.string "GIOVANNI in KANTO!\p"
	.string "We took over this RADIO TOWER to\n"
	.string "call our BOSS back from his\l"
	.string "solo training.\p"
	.string "TEAM ROCKET will regain its\n"
	.string "former glory!\p"
	.string "I won't let you ruin it\n"
	.string "a second time!$"
J_RadioTower5FRocketBossWinText::
	.string "No! Forgive me,\nGIOVANNI!$"
J_RadioTower5FRocketBossAfterText::
	.string "How could this be?\n"
	.string "Our dreams have come to naught.\p"
	.string "…Heh. But you are too late.\n"
	.string "GIOVANNI heard our message.\p"
	.string "His answer came from far to the\n"
	.string "south… from HOENN.\p"
	.string "Like GIOVANNI did before me, I will\n"
	.string "disband TEAM ROCKET here today.\p"
	.string "Farewell.$"
J_RadioTower5FDirectorThankYouText::
	.string "DIRECTOR: {PLAYER},\nthank you!\pYour courageous\nactions have saved\pPOKéMON nation-\nwide.\pI know it's not\nmuch, but please\ltake this.$"
J_RadioTower5FDirectorDescribeClearBellText::
	.string "There used to be a\ntower right here\lin GOLDENROD CITY.\pBut it was old and\ncreaky.\pSo we replaced it\nwith our RADIO\lTOWER.\pWe dug up that\nbell during\lconstruction.\pI heard that all\nsorts of POKéMON\plived in GOLDENROD\nin the past.\pPerhaps…\pThat bell has some\nconnection to the\pTIN TOWER in\nECRUTEAK CITY…\pAh!\pThat reminds me…\pI overheard TEAM\nROCKET whispering.\pApparently, some-\nthing is going on\lat the TIN TOWER.\pI have no idea\nwhat is happening,\pbut you might look\ninto it.\pOK, I better go to\nmy OFFICE.$"
J_RadioTower5FDirectorText::
	.string "DIRECTOR: Hello,\n{PLAYER}!\pYou know, I love\nPOKéMON.\pI built this RADIO\nTOWER so I could\pexpress my love\nof POKéMON.\pIt would be nice\nif people enjoyed\lour programs.$"
J_BenText::
	.string "BEN: Do you listen\nto our music?$"
J_RadioTower5FDirectorsOfficeSignText::
	.string "5F DIRECTOR'S\n   OFFICE$"
J_RadioTower5FStudio1SignText::
	.string "5F STUDIO 1$"
J_RadioTower5F_MapEvents::
