@ KJH: translated from pokecrystal maps/SlowpokeWellB1F.asm by kjh_tools/johto

JohtoSlowpokeWellB1F_MapScripts::
	.byte 0

J_T_TrainerGruntM29::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_29, J_GruntM29SeenText, J_GruntM29BeatenText
	call J_TrainerGruntM29_Script
	release
	end

J_T_TrainerGruntM1::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_1, J_GruntM1SeenText, J_GruntM1BeatenText
	call J_TrainerGruntM1_Script
	release
	end

J_T_TrainerGruntM2::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_2, J_GruntM2SeenText, J_GruntM2BeatenText
	call J_TrainerGruntM2_Script
	release
	end

J_T_TrainerGruntF1::
	trainerbattle_single TRAINER_J_GRUNTF_GRUNTF_1, J_GruntF1SeenText, J_GruntF1BeatenText
	call J_TrainerGruntF1_Script
	release
	end

J_W_SlowpokeWellB1FSlowpokeWithMailScript::
	lock
	call J_SlowpokeWellB1FSlowpokeWithMailScript
	release
	end

J_W_SlowpokeWellB1FTaillessSlowpokeScript::
	lock
	call J_SlowpokeWellB1FTaillessSlowpokeScript
	release
	end

J_W_SlowpokeWellB1FKurtScript::
	lock
	call J_SlowpokeWellB1FKurtScript
	release
	end

J_W_SlowpokeWellB1FBoulder::
	lock
	call J_SlowpokeWellB1FBoulder
	release
	end

J_SlowpokeWellB1F_MapScripts::
J_SlowpokeWellB1FKurtScript::
	faceplayer
	message J_SlowpokeWellB1FKurtText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM29::
J_TrainerGruntM29_Script:
	message J_GruntM29AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM1::
J_TrainerGruntM1_Script:
	message J_TrainerGruntM1WhenTalkText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 1
	removeobject 2
	removeobject 3
	removeobject 4
	delay 15
	fadescreen FADE_FROM_BLACK
	removeobject 7
	setobjectxyperm 7, 11, 6
	addobject 7
	applymovement 7, J_KurtSlowpokeWellVictoryMovementData
	waitmovement 7
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	message J_KurtLeaveSlowpokeWellText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_CLEARED_SLOWPOKE_WELL
	setvar VAR_J_SCENE_AZALEA_TOWN, 1
	clearflag FLAG_J_ILEX_FOREST_APPRENTICE
	clearflag FLAG_J_ILEX_FOREST_FARFETCHD
	setflag FLAG_J_CHARCOAL_KILN_FARFETCH_D
	setflag FLAG_J_CHARCOAL_KILN_APPRENTICE
	setflag FLAG_J_SLOWPOKE_WELL_SLOWPOKES
	setflag FLAG_J_SLOWPOKE_WELL_KURT
	clearflag FLAG_J_AZALEA_TOWN_SLOWPOKES
	clearflag FLAG_J_KURTS_HOUSE_SLOWPOKE
	clearflag FLAG_J_KURTS_HOUSE_KURT_1
	fadescreen FADE_TO_WHITE
	special HealPlayerParty
	delay 15
	warp MAP_JOHTO_KURTS_HOUSE, 3, 3
	waitstate
	return
J_TrainerGruntM2::
J_TrainerGruntM2_Script:
	message J_GruntM2AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntF1::
J_TrainerGruntF1_Script:
	message J_GruntF1AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SlowpokeWellB1FSlowpokeWithMailScript::
	faceplayer
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
	waitmoncry
	message J_SlowpokeWellB1FSlowpokeWithMailText
	waitmessage
	yesnobox 20, 8
	goto_if_ne VAR_RESULT, 0, J_SlowpokeWellB1FSlowpokeWithMailScript_ReadMail
	closemessage
	return
J_SlowpokeWellB1FSlowpokeWithMailScript_ReadMail:
	message J_SlowpokeWellB1FSlowpokeMailText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SlowpokeWellB1FTaillessSlowpokeScript::
	faceplayer
	message J_SlowpokeWellB1FTaillessSlowpokeText
	waitmessage
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_SlowpokeWellB1FBoulder::
	goto EventScript_StrengthBoulder
J_SlowpokeWellB1FSuperPotion::
	finditem ITEM_SUPER_POTION, 1
	return
J_KurtSlowpokeWellVictoryMovementData::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	delay_8
	delay_8
	delay_8
	walk_left
	walk_up
	walk_up
	delay_8
	delay_8
	delay_8
	face_left
	step_end
J_SlowpokeWellB1FKurtText::
	.string "KURT: Hey there,\n{PLAYER}!\pThe guard up top\ntook off when I\lshouted at him.\pBut then I took a\ntumble down the\lWELL.\pI slammed down\nhard on my back,\lso I can't move.\pRats! If I were\nfit, my POKéMON\pwould've punished\nthem…\pAh, it can't be\nhelped.\p{PLAYER}, show them\nhow gutsy you are\lin my place!$"
J_KurtLeaveSlowpokeWellText::
	.string "KURT: Way to go,\n{PLAYER}!\pTEAM ROCKET has\ntaken off.\pMy back's better\ntoo. Let's get out\lof here.$"
J_GruntM29SeenText::
	.string "Darn! I was stand-\ning guard up top\pwhen some old coot\nyelled at me.\pHe startled me so\nmuch that I fell\ldown here.\pI think I'll vent\nmy anger by taking\lit out on you!$"
J_GruntM29BeatenText::
	.string "Arrgh! This is NOT\nmy day!$"
J_GruntM29AfterBattleText::
	.string "Sure, we've been\nhacking the tails\poff SLOWPOKE and\nselling them.\pEverything we do\nis for profit.\pThat's right!\nWe're TEAM ROCKET,\pand we'll do any-\nthing for money!$"
J_GruntM1SeenText::
	.string "What do you want?\pIf you interrupt\nour work, don't\lexpect any mercy!$"
J_GruntM1BeatenText::
	.string "You did OK today,\nbut wait till next\ltime!$"
J_TrainerGruntM1WhenTalkText::
	.string "Yeah, TEAM ROCKET\nwas broken up\lthree years ago.\pBut we continued\nour activities\lunderground.\pNow you can have\nfun watching us\lstir up trouble!$"
J_GruntM2SeenText::
	.string "Quit taking SLOW-\nPOKETAILS?\pIf we obeyed you,\nTEAM ROCKET's rep\lwould be ruined!$"
J_GruntM2BeatenText::
	.string "Just…\nToo strong…$"
J_GruntM2AfterBattleText::
	.string "We need the money,\nbut selling SLOW-\lPOKETAILS?\pIt's tough being a\nROCKET GRUNT!$"
J_GruntF1SeenText::
	.string "Stop taking TAILS?\pYeah, just try to\ndefeat all of us!$"
J_GruntF1BeatenText::
	.string "You rotten brat!$"
J_GruntF1AfterBattleText::
	.string "SLOWPOKETAILS\ngrow back fast!\pWhat's wrong with\nselling them?$"
J_SlowpokeWellB1FSlowpokeWithMailText::
	.string "A SLOWPOKE with\nits TAIL cut off…\pHuh? It has MAIL.\nRead it?$"
J_SlowpokeWellB1FSlowpokeMailText::
	.string "{PLAYER} read the\nMAIL.\pBe good and look\nafter the house\pwith Grandpa and\nSLOWPOKE.\pLove, Dad$"
J_SlowpokeWellB1FTaillessSlowpokeText::
	.string "A SLOWPOKE with\nits TAIL cut off…$"
J_SlowpokeWellB1F_MapEvents::
