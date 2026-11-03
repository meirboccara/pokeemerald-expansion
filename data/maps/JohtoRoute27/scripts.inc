@ KJH: translated from pokecrystal maps/Route27.asm by kjh_tools/johto

JohtoRoute27_MapScripts::
	.byte 0

J_T_TrainerCooltrainermBlake::
	trainerbattle_single TRAINER_J_COOLTRAINERM_BLAKE, J_CooltrainermBlakeSeenText, J_CooltrainermBlakeBeatenText
	call J_TrainerCooltrainermBlake_Script
	release
	end

J_T_TrainerCooltrainermBrian::
	trainerbattle_single TRAINER_J_COOLTRAINERM_BRIAN, J_CooltrainermBrianSeenText, J_CooltrainermBrianBeatenText
	call J_TrainerCooltrainermBrian_Script
	release
	end

J_T_TrainerCooltrainerfReena::
	trainerbattle_single TRAINER_J_COOLTRAINERF_REENA1, J_CooltrainerfReenaSeenText, J_CooltrainerfReenaBeatenText
	call J_TrainerCooltrainerfReena_Script
	release
	end

J_T_TrainerCooltrainerfMegan::
	trainerbattle_single TRAINER_J_COOLTRAINERF_MEGAN, J_CooltrainerfMeganSeenText, J_CooltrainerfMeganBeatenText
	call J_TrainerCooltrainerfMegan_Script
	release
	end

J_T_TrainerPsychicGilbert::
	trainerbattle_single TRAINER_J_PSYCHIC_T_GILBERT, J_PsychicGilbertSeenText, J_PsychicGilbertBeatenText
	call J_TrainerPsychicGilbert_Script
	release
	end

J_T_TrainerBirdKeeperJose2::
	trainerbattle_single TRAINER_J_BIRD_KEEPER_JOSE2, J_BirdKeeperJose2SeenText, J_BirdKeeperJose2BeatenText
	call J_TrainerBirdKeeperJose2_Script
	release
	end

J_W_Route27FisherScript::
	lock
	call J_Route27FisherScript
	release
	end

J_C_FirstStepIntoKantoLeftScene::
	lockall
	call J_FirstStepIntoKantoLeftScene
	releaseall
	end

J_C_FirstStepIntoKantoRightScene::
	lockall
	call J_FirstStepIntoKantoRightScene
	releaseall
	end

J_S_TohjoFallsSign::
	lockall
	call J_TohjoFallsSign
	releaseall
	end

J_Route27_MapScripts::
J_Route27Noop1Scene::
	return
J_Route27Noop2Scene::
	return
J_FirstStepIntoKantoLeftScene::
	turnobject 9, DIR_WEST
	applymovement 9, J_Movement_Exclamation
	waitmovement 0
	applymovement 9, J_Route27FisherStepLeftTwiceMovement
	waitmovement 9
	goto J_FirstStepIntoKantoScene_Continue
J_FirstStepIntoKantoRightScene::
	turnobject 9, DIR_WEST
	applymovement 9, J_Movement_Exclamation
	waitmovement 0
	applymovement 9, J_Route27FisherStepLeftOnceMovement
	waitmovement 9
J_FirstStepIntoKantoScene_Continue::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	message J_Route27FisherHeyText
	waitmessage
	waitbuttonpress
	message J_Route27FisherText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_J_SCENE_ROUTE_27, 1
	return
J_Route27FisherScript::
	faceplayer
	message J_Route27FisherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPsychicGilbert::
J_TrainerPsychicGilbert_Script:
	message J_PsychicGilbertAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBirdKeeperJose2::
J_TrainerBirdKeeperJose2_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_JOSE_READY_FOR_REMATCH, J_L604
	setvar VAR_RESULT, 1
J_L604:
	goto_if_ne VAR_RESULT, 0, J_TrainerBirdKeeperJose2_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_JOSE_HAS_STAR_PIECE, J_L605
	setvar VAR_RESULT, 1
J_L605:
	goto_if_ne VAR_RESULT, 0, J_TrainerBirdKeeperJose2_HasStarPiece
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerBirdKeeperJose2_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_JOSE_ASKED_FOR_PHONE_NUMBER, J_L606
	setvar VAR_RESULT, 1
J_L606:
	goto_if_ne VAR_RESULT, 0, J_TrainerBirdKeeperJose2_AskedAlready
	message J_BirdKeeperJose2AfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_JOSE_ASKED_FOR_PHONE_NUMBER
	call J_TrainerBirdKeeperJose2_AskNumber1
	goto J_TrainerBirdKeeperJose2_AskForNumber
J_TrainerBirdKeeperJose2_AskedAlready:
	call J_TrainerBirdKeeperJose2_AskNumber2
J_TrainerBirdKeeperJose2_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerBirdKeeperJose2_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerBirdKeeperJose2_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_BIRD_KEEPER_JOSE2
	call J_TrainerBirdKeeperJose2_RegisteredNumber
	goto J_TrainerBirdKeeperJose2_NumberAccepted
J_TrainerBirdKeeperJose2_WantsBattle:
	call J_TrainerBirdKeeperJose2_Rematch
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 2, J_TrainerBirdKeeperJose2_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerBirdKeeperJose2_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerBirdKeeperJose2_LoadFight0
J_TrainerBirdKeeperJose2_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L607
	setvar VAR_RESULT, 1
J_L607:
	goto_if_ne VAR_RESULT, 0, J_TrainerBirdKeeperJose2_LoadFight2
J_TrainerBirdKeeperJose2_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L608
	setvar VAR_RESULT, 1
J_L608:
	goto_if_ne VAR_RESULT, 0, J_TrainerBirdKeeperJose2_LoadFight1
J_TrainerBirdKeeperJose2_LoadFight0:
	trainerbattle_no_intro TRAINER_J_BIRD_KEEPER_JOSE2, J_BirdKeeperJose2BeatenText
	clearflag FLAG_J_ENGINE_JOSE_READY_FOR_REMATCH
	return
J_TrainerBirdKeeperJose2_LoadFight1:
	trainerbattle_no_intro TRAINER_J_BIRD_KEEPER_JOSE1, J_Text_Empty
	clearflag FLAG_J_ENGINE_JOSE_READY_FOR_REMATCH
	return
J_TrainerBirdKeeperJose2_LoadFight2:
	trainerbattle_no_intro TRAINER_J_BIRD_KEEPER_JOSE3, J_Text_Empty
	clearflag FLAG_J_ENGINE_JOSE_READY_FOR_REMATCH
	return
J_TrainerBirdKeeperJose2_HasStarPiece:
	call J_TrainerBirdKeeperJose2_Gift
	giveitem ITEM_STAR_PIECE, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerBirdKeeperJose2_NoRoom
	clearflag FLAG_J_ENGINE_JOSE_HAS_STAR_PIECE
	goto J_TrainerBirdKeeperJose2_NumberAccepted
J_TrainerBirdKeeperJose2_NoRoom:
	goto J_TrainerBirdKeeperJose2_PackFull
J_TrainerBirdKeeperJose2_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerBirdKeeperJose2_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerBirdKeeperJose2_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerBirdKeeperJose2_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerBirdKeeperJose2_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerBirdKeeperJose2_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerBirdKeeperJose2_Rematch:
	goto J_Std_Nop
	return
J_TrainerBirdKeeperJose2_Gift:
	goto J_Std_Nop
	return
J_TrainerBirdKeeperJose2_PackFull:
	goto J_Std_Nop
	return
J_TrainerCooltrainermBlake::
J_TrainerCooltrainermBlake_Script:
	message J_CooltrainermBlakeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainermBrian::
J_TrainerCooltrainermBrian_Script:
	message J_CooltrainermBrianAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainerfReena::
J_TrainerCooltrainerfReena_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_REENA_READY_FOR_REMATCH, J_L609
	setvar VAR_RESULT, 1
J_L609:
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainerfReena_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainerfReena_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_REENA_ASKED_FOR_PHONE_NUMBER, J_L610
	setvar VAR_RESULT, 1
J_L610:
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainerfReena_AskedAlready
	message J_CooltrainerfReenaAfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_REENA_ASKED_FOR_PHONE_NUMBER
	call J_TrainerCooltrainerfReena_AskNumber1
	goto J_TrainerCooltrainerfReena_AskForNumber
J_TrainerCooltrainerfReena_AskedAlready:
	call J_TrainerCooltrainerfReena_AskNumber2
J_TrainerCooltrainerfReena_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerCooltrainerfReena_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerCooltrainerfReena_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_COOLTRAINERF_REENA1
	call J_TrainerCooltrainerfReena_RegisteredNumber
	goto J_TrainerCooltrainerfReena_NumberAccepted
J_TrainerCooltrainerfReena_WantsBattle:
	call J_TrainerCooltrainerfReena_Rematch
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 2, J_TrainerCooltrainerfReena_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerCooltrainerfReena_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerCooltrainerfReena_LoadFight0
J_TrainerCooltrainerfReena_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L611
	setvar VAR_RESULT, 1
J_L611:
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainerfReena_LoadFight2
J_TrainerCooltrainerfReena_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L612
	setvar VAR_RESULT, 1
J_L612:
	goto_if_ne VAR_RESULT, 0, J_TrainerCooltrainerfReena_LoadFight1
J_TrainerCooltrainerfReena_LoadFight0:
	trainerbattle_no_intro TRAINER_J_COOLTRAINERF_REENA1, J_CooltrainerfReenaBeatenText
	clearflag FLAG_J_ENGINE_REENA_READY_FOR_REMATCH
	return
J_TrainerCooltrainerfReena_LoadFight1:
	trainerbattle_no_intro TRAINER_J_COOLTRAINERF_REENA2, J_Text_Empty
	clearflag FLAG_J_ENGINE_REENA_READY_FOR_REMATCH
	return
J_TrainerCooltrainerfReena_LoadFight2:
	trainerbattle_no_intro TRAINER_J_COOLTRAINERF_REENA3, J_Text_Empty
	clearflag FLAG_J_ENGINE_REENA_READY_FOR_REMATCH
	return
J_TrainerCooltrainerfReena_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerCooltrainerfReena_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerCooltrainerfReena_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerCooltrainerfReena_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerCooltrainerfReena_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerCooltrainerfReena_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerCooltrainerfReena_Rematch:
	goto J_Std_Nop
	return
J_TrainerCooltrainerfMegan::
J_TrainerCooltrainerfMegan_Script:
	message J_CooltrainerfMeganAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TohjoFallsSign::
	message J_TohjoFallsSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route27TMSolarbeam::
	finditem ITEM_TM22, 1
	return
J_Route27RareCandy::
	finditem ITEM_RARE_CANDY, 1
	return
J_Route27FisherStepLeftTwiceMovement::
	walk_left
	walk_left
	step_end
J_Route27FisherStepLeftOnceMovement::
	walk_left
	step_end
J_Route27FisherHeyText::
	.string "Hey!$"
J_Route27FisherText::
	.string "Do you know what\nyou just did?\pYou've taken your\nfirst step into\lKANTO.\pCheck your POKé-\nGEAR MAP and see.$"
J_CooltrainermBlakeSeenText::
	.string "You look pretty\nstrong.\lLet me battle you!$"
J_CooltrainermBlakeBeatenText::
	.string "Yow!$"
J_CooltrainermBlakeAfterBattleText::
	.string "If you prevail on\nthis harsh trek,\pthe truth will be\nrevealed!\pHeh, sorry, I just\nwanted to say\lsomething cool.$"
J_CooltrainermBrianSeenText::
	.string "Hm? You're good,\naren't you?$"
J_CooltrainermBrianBeatenText::
	.string "Just as I thought!$"
J_CooltrainermBrianAfterBattleText::
	.string "A good trainer can\nrecognize other\lgood trainers.$"
J_CooltrainerfReenaSeenText::
	.string "You shouldn't\nunderestimate the\pwild POKéMON in\nthese parts.$"
J_CooltrainerfReenaBeatenText::
	.string "Oh! You're much\ntoo strong!$"
J_CooltrainerfReenaAfterBattleText::
	.string "You're just a kid,\nbut you're not to\pbe underestimated\neither.$"
J_CooltrainerfMeganSeenText::
	.string "It's rare to see\nanyone come here.\pAre you training\non your own?$"
J_CooltrainerfMeganBeatenText::
	.string "Oh! You're really\nstrong!$"
J_CooltrainerfMeganAfterBattleText::
	.string "I'm checking out\npre- and post-\levolution POKéMON.\pEvolution really\ndoes make POKéMON\lstronger.\pBut evolved forms\nalso learn moves\llater on.$"
J_PsychicGilbertSeenText::
	.string "Don't say a thing!\pLet me guess what\nyou're thinking.\pMmmmmmm…\pI got it! You're\non the POKéMON\lLEAGUE challenge!$"
J_PsychicGilbertBeatenText::
	.string "You're too much!$"
J_PsychicGilbertAfterBattleText::
	.string "With your skills,\nyou'll do well at\lthe LEAGUE.\pThat's what my\npremonition says.$"
J_BirdKeeperJose2SeenText::
	.string "Tweet! Tweet!\nTetweet!$"
J_BirdKeeperJose2BeatenText::
	.string "Tweet!$"
J_BirdKeeperJose2AfterBattleText::
	.string "BIRD KEEPERS like\nme mimic bird\pwhistles to com-\nmand POKéMON.$"
J_TohjoFallsSignText::
	.string "TOHJO FALLS\pTHE LINK BETWEEN\nKANTO AND JOHTO$"
J_Route27_MapEvents::
