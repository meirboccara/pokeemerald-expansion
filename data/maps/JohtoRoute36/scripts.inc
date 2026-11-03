@ KJH: translated from pokecrystal maps/Route36.asm by kjh_tools/johto

JohtoRoute36_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoRoute36_OnTransition
	.byte 0

JohtoRoute36_OnTransition:
	call J_Route36ArthurCallback
	end

J_T_TrainerPsychicMark::
	trainerbattle_single TRAINER_J_PSYCHIC_T_MARK, J_PsychicMarkSeenText, J_PsychicMarkBeatenText
	call J_TrainerPsychicMark_Script
	release
	end

J_T_TrainerSchoolboyAlan1::
	trainerbattle_single TRAINER_J_SCHOOLBOY_ALAN1, J_SchoolboyAlan1SeenText, J_SchoolboyAlan1BeatenText
	call J_TrainerSchoolboyAlan1_Script
	release
	end

J_W_SudowoodoScript::
	lock
	call J_SudowoodoScript
	release
	end

J_W_Route36LassScript::
	lock
	call J_Route36LassScript
	release
	end

J_W_Route36RockSmashGuyScript::
	lock
	call J_Route36RockSmashGuyScript
	release
	end

J_W_Route36FruitTree::
	lock
	call J_Route36FruitTree
	release
	end

J_W_ArthurScript::
	lock
	call J_ArthurScript
	release
	end

J_W_Route36FloriaScript::
	lock
	call J_Route36FloriaScript
	release
	end

J_C_Route36SuicuneScript::
	lockall
	call J_Route36SuicuneScript
	releaseall
	end

J_S_Route36TrainerTips2::
	lockall
	call J_Route36TrainerTips2
	releaseall
	end

J_S_RuinsOfAlphNorthSign::
	lockall
	call J_RuinsOfAlphNorthSign
	releaseall
	end

J_S_Route36Sign::
	lockall
	call J_Route36Sign
	releaseall
	end

J_S_Route36TrainerTips1::
	lockall
	call J_Route36TrainerTips1
	releaseall
	end

J_Route36_MapScripts::
J_Route36Noop1Scene::
	return
J_Route36Noop2Scene::
	return
J_Route36ArthurCallback::
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 4, J_Route36ArthurCallback_ArthurAppears
	setflag FLAG_J_ROUTE_36_ARTHUR_OF_THURSDAY
	return
J_Route36ArthurCallback_ArthurAppears:
	clearflag FLAG_J_ROUTE_36_ARTHUR_OF_THURSDAY
	return
J_Route36SuicuneScript::
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	delay 15
	playse SE_WARP_OUT
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	applymovement 9, J_Route36SuicuneMovement
	waitmovement 9
	removeobject 9
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	delay 10
	setvar VAR_J_SCENE_ROUTE_36, 0
	clearflag FLAG_J_SAW_SUICUNE_AT_CIANWOOD_CITY
	setvar VAR_J_SCENE_CIANWOOD_CITY, 1
	return
J_SudowoodoScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_SQUIRTBOTTLE, J_L431
	setvar VAR_RESULT, 1
J_L431:
	goto_if_ne VAR_RESULT, 0, J_SudowoodoScript_Fight
	waitse
	playse SE_M_SANDSTORM
	applymovement 3, J_SudowoodoShakeMovement
	waitmovement 3
	return
J_SudowoodoScript_Fight:
	message J_UseSquirtbottleText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_DidntUseSquirtbottleScript
	closemessage
J_WateredWeirdTreeScript::
	message J_UsedSquirtbottleText
	waitmessage
	waitbuttonpress
	closemessage
	waitse
	playse SE_M_SANDSTORM
	applymovement 3, J_SudowoodoShakeMovement
	waitmovement 3
	message J_SudowoodoAttackedText
	waitmessage
	waitbuttonpress
	closemessage
	setwildbattle SPECIES_SUDOWOODO, 20
	dowildbattle
	setflag FLAG_J_FOUGHT_SUDOWOODO
	goto_if_eq VAR_RESULT, 2, J_DidntCatchSudowoodo
	removeobject 3
	return
J_DidntUseSquirtbottleScript::
	closemessage
	return
J_DidntCatchSudowoodo::
	applymovement 3, J_WeirdTreeMovement_Flee
	waitmovement 3
	removeobject 3
	return
J_Route36FloriaScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TALKED_TO_FLORIA_AT_FLOWER_SHOP, J_L432
	setvar VAR_RESULT, 1
J_L432:
	goto_if_ne VAR_RESULT, 0, J_Route36FloriaScript_SecondTimeTalking
	setflag FLAG_J_MET_FLORIA
	message J_FloriaText1
	waitmessage
	waitbuttonpress
	closemessage
	clearflag FLAG_J_FLORIA_AT_FLOWER_SHOP
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 1, J_Route36FloriaScript_Up
	applymovement 8, J_FloriaMovement1
	waitmovement 8
	removeobject 8
	return
J_Route36FloriaScript_Up:
	applymovement 8, J_FloriaMovement2
	waitmovement 8
	removeobject 8
	return
J_Route36FloriaScript_SecondTimeTalking:
	message J_FloriaText2
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36RockSmashGuyScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM08_ROCK_SMASH, J_L433
	setvar VAR_RESULT, 1
J_L433:
	goto_if_ne VAR_RESULT, 0, J_Route36RockSmashGuyScript_AlreadyGotRockSmash
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOUGHT_SUDOWOODO, J_L434
	setvar VAR_RESULT, 1
J_L434:
	goto_if_ne VAR_RESULT, 0, J_Route36RockSmashGuyScript_ClearedSudowoodo
	message J_RockSmashGuyText1
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36RockSmashGuyScript_ClearedSudowoodo:
	message J_RockSmashGuyText2
	waitmessage
	waitbuttonpress
	giveitem ITEM_HM06, 1
	goto_if_eq VAR_RESULT, 0, J_Route36RockSmashGuyScript_NoRoomForTM
	setflag FLAG_J_GOT_TM08_ROCK_SMASH
J_Route36RockSmashGuyScript_AlreadyGotRockSmash:
	message J_RockSmashGuyText3
	waitmessage
	waitbuttonpress
J_Route36RockSmashGuyScript_NoRoomForTM:
	closemessage
	return
J_Route36LassScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOUGHT_SUDOWOODO, J_L435
	setvar VAR_RESULT, 1
J_L435:
	goto_if_ne VAR_RESULT, 0, J_Route36LassScript_ClearedSudowoodo
	message J_Route36LassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36LassScript_ClearedSudowoodo:
	message J_Route36LassText_ClearedSudowoodo
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSchoolboyAlan1::
J_TrainerSchoolboyAlan1_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_ALAN_READY_FOR_REMATCH, J_L436
	setvar VAR_RESULT, 1
J_L436:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyAlan1_ChooseRematch
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_ALAN_HAS_FIRE_STONE, J_L437
	setvar VAR_RESULT, 1
J_L437:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyAlan1_GiveFireStone
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyAlan1_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ALAN_ASKED_FOR_PHONE_NUMBER, J_L438
	setvar VAR_RESULT, 1
J_L438:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyAlan1_AskAgainForPhoneNumber
	message J_SchoolboyAlanBooksText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_ALAN_ASKED_FOR_PHONE_NUMBER
	call J_TrainerSchoolboyAlan1_AskNumber1
	goto J_TrainerSchoolboyAlan1_ContinueAskForPhoneNumber
J_TrainerSchoolboyAlan1_AskAgainForPhoneNumber:
	call J_TrainerSchoolboyAlan1_AskNumber2
J_TrainerSchoolboyAlan1_ContinueAskForPhoneNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerSchoolboyAlan1_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerSchoolboyAlan1_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_SCHOOLBOY_ALAN1
	call J_TrainerSchoolboyAlan1_RegisteredNumber
	goto J_TrainerSchoolboyAlan1_NumberAccepted
J_TrainerSchoolboyAlan1_ChooseRematch:
	call J_TrainerSchoolboyAlan1_Rematch
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 4, J_TrainerSchoolboyAlan1_Fight4
	goto_if_eq VAR_RESULT, 3, J_TrainerSchoolboyAlan1_Fight3
	goto_if_eq VAR_RESULT, 2, J_TrainerSchoolboyAlan1_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerSchoolboyAlan1_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerSchoolboyAlan1_LoadFight0
J_TrainerSchoolboyAlan1_Fight4:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L439
	setvar VAR_RESULT, 1
J_L439:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyAlan1_LoadFight4
J_TrainerSchoolboyAlan1_Fight3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L440
	setvar VAR_RESULT, 1
J_L440:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyAlan1_LoadFight3
J_TrainerSchoolboyAlan1_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_BLACKTHORN, J_L441
	setvar VAR_RESULT, 1
J_L441:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyAlan1_LoadFight2
J_TrainerSchoolboyAlan1_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_OLIVINE, J_L442
	setvar VAR_RESULT, 1
J_L442:
	goto_if_ne VAR_RESULT, 0, J_TrainerSchoolboyAlan1_LoadFight1
J_TrainerSchoolboyAlan1_LoadFight0:
	trainerbattle_no_intro TRAINER_J_SCHOOLBOY_ALAN1, J_SchoolboyAlan1BeatenText
	clearflag FLAG_J_ENGINE_ALAN_READY_FOR_REMATCH
	return
J_TrainerSchoolboyAlan1_LoadFight1:
	trainerbattle_no_intro TRAINER_J_SCHOOLBOY_ALAN2, J_Text_Empty
	clearflag FLAG_J_ENGINE_ALAN_READY_FOR_REMATCH
	return
J_TrainerSchoolboyAlan1_LoadFight2:
	trainerbattle_no_intro TRAINER_J_SCHOOLBOY_ALAN3, J_Text_Empty
	clearflag FLAG_J_ENGINE_ALAN_READY_FOR_REMATCH
	return
J_TrainerSchoolboyAlan1_LoadFight3:
	trainerbattle_no_intro TRAINER_J_SCHOOLBOY_ALAN4, J_Text_Empty
	clearflag FLAG_J_ENGINE_ALAN_READY_FOR_REMATCH
	return
J_TrainerSchoolboyAlan1_LoadFight4:
	trainerbattle_no_intro TRAINER_J_SCHOOLBOY_ALAN5, J_Text_Empty
	clearflag FLAG_J_ENGINE_ALAN_READY_FOR_REMATCH
	return
J_TrainerSchoolboyAlan1_GiveFireStone:
	call J_TrainerSchoolboyAlan1_Gift
	giveitem ITEM_FIRE_STONE, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerSchoolboyAlan1_BagFull
	clearflag FLAG_J_ENGINE_ALAN_HAS_FIRE_STONE
	setflag FLAG_J_ALAN_GAVE_FIRE_STONE
	goto J_TrainerSchoolboyAlan1_NumberAccepted
J_TrainerSchoolboyAlan1_BagFull:
	goto J_TrainerSchoolboyAlan1_PackFull
J_TrainerSchoolboyAlan1_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerSchoolboyAlan1_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerSchoolboyAlan1_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerSchoolboyAlan1_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerSchoolboyAlan1_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerSchoolboyAlan1_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerSchoolboyAlan1_Rematch:
	goto J_Std_Nop
	return
J_TrainerSchoolboyAlan1_Gift:
	goto J_Std_Nop
	return
J_TrainerSchoolboyAlan1_PackFull:
	goto J_Std_Nop
	return
J_TrainerPsychicMark::
J_TrainerPsychicMark_Script:
	message J_PsychicMarkAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ArthurScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_HARD_STONE_FROM_ARTHUR, J_L443
	setvar VAR_RESULT, 1
J_L443:
	goto_if_ne VAR_RESULT, 0, J_ArthurScript_AlreadyGotStone
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_ne VAR_RESULT, 4, J_ArthurNotThursdayScript
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_MET_ARTHUR_OF_THURSDAY, J_L444
	setvar VAR_RESULT, 1
J_L444:
	goto_if_ne VAR_RESULT, 0, J_ArthurScript_MetArthur
	message J_MeetArthurText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_MET_ARTHUR_OF_THURSDAY
J_ArthurScript_MetArthur:
	message J_ArthurGivesGiftText
	waitmessage
	waitbuttonpress
	giveitem ITEM_HARD_STONE, 1
	goto_if_eq VAR_RESULT, 0, J_ArthurScript_BagFull
	setflag FLAG_J_GOT_HARD_STONE_FROM_ARTHUR
	message J_ArthurGaveGiftText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ArthurScript_AlreadyGotStone:
	message J_ArthurThursdayText
	waitmessage
	waitbuttonpress
J_ArthurScript_BagFull:
	closemessage
	return
J_ArthurNotThursdayScript::
	message J_ArthurNotThursdayText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36Sign::
	message J_Route36SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphNorthSign::
	message J_RuinsOfAlphNorthSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36TrainerTips1::
	message J_Route36TrainerTips1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36TrainerTips2::
	message J_Route36TrainerTips2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route36FruitTree::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_SudowoodoShakeMovement::
	step_end
J_WeirdTreeMovement_Flee::
	jump_up
	jump_up
	step_end
J_FloriaMovement1::
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end
J_FloriaMovement2::
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end
J_Route36SuicuneMovement::
	jump_down
	jump_down
	jump_down
	jump_right
	jump_right
	jump_right
	step_end
J_UseSquirtbottleText::
	.string "It's a weird tree.\nUse SQUIRTBOTTLE?$"
J_UsedSquirtbottleText::
	.string "{PLAYER} used the\nSQUIRTBOTTLE.$"
J_SudowoodoAttackedText::
	.string "The weird tree\ndoesn't like the\lSQUIRTBOTTLE!\pThe weird tree\nattacked!$"
J_FloriaText1::
	.string "I'm the FLOWER\nSHOP's FLORIA!\pListen, listen!\pWhen I sprinkled\nwater on that\pwiggly tree, it\njumped right up!\pIt just has to be\na POKéMON.\pI bet it would be\nshocked out of its\pdisguise if you\nsoaked it!\pI know! I'll tell\nmy sis and borrow\lher water bottle!$"
J_FloriaText2::
	.string "When I told my sis\nabout the jiggly\ptree, she said\nit's dangerous.\pIf I beat WHITNEY,\nI wonder if she'll\plend me her water\nbottle…$"
J_RockSmashGuyText1::
	.string "Wa-hey!\pI was going to\nsnap that tree\pwith my straight-\narm punch.\pBut I couldn't!\nI'm a failure!$"
J_RockSmashGuyText2::
	.string "Did you clear that\nwretched tree?\pI'm impressed!\nI want you to\lhave this.$"
J_Text_ReceivedTM08::
	.string "{PLAYER} received\nTM08.$"
J_RockSmashGuyText3::
	.string "That happens to be\nROCK SMASH.\pYou can shatter\nrocks with just a\psingle well-aimed\nsmack.\pIf any rocks are\nin your way, just\lsmash 'em up!$"
J_UnusedOddTreeText::
	.string "An odd tree is\nblocking the way\lto GOLDENROD CITY.\pI wanted to go see\nthe huge POKéMON\pCENTER they just\nopened…$"
J_Route36LassText::
	.string "An odd tree is\nblocking the way\lto GOLDENROD CITY.\pIt's preventing\nme from shopping.\pSomething should\nbe done about it.$"
J_Route36LassText_ClearedSudowoodo::
	.string "That odd tree dis-\nappeared without a\ltrace.\pOh! That tree was\nreally a POKéMON?$"
J_PsychicMarkSeenText::
	.string "I'm going to read\nyour thoughts!$"
J_PsychicMarkBeatenText::
	.string "I misread you!$"
J_PsychicMarkAfterBattleText::
	.string "I'd be strong if\nonly I could tell\pwhat my opponent\nwas thinking.$"
J_SchoolboyAlan1SeenText::
	.string "Thanks to my stud-\nies, I'm ready for\lany POKéMON!$"
J_SchoolboyAlan1BeatenText::
	.string "Oops! Computation\nerror?$"
J_SchoolboyAlanBooksText::
	.string "Darn. I study five\nhours a day too.\pThere's more to\nlearning than just\lreading books.$"
J_MeetArthurText::
	.string "ARTHUR: Who are\nyou?\pI'm ARTHUR of\nThursday.$"
J_ArthurGivesGiftText::
	.string "Here. You can have\nthis.$"
J_ArthurGaveGiftText::
	.string "ARTHUR: A POKéMON\nthat uses rock-\ptype moves should\nhold on to that.\pIt pumps up rock-\ntype attacks.$"
J_ArthurThursdayText::
	.string "ARTHUR: I'm ARTHUR\nof Thursday. I'm\pthe second son out\nof seven children.$"
J_ArthurNotThursdayText::
	.string "ARTHUR: Today's\nnot Thursday. How\ldisappointing.$"
J_Route36SignText::
	.string "ROUTE 36$"
J_RuinsOfAlphNorthSignText::
	.string "RUINS OF ALPH\nNORTH ENTRANCE$"
J_Route36TrainerTips1Text::
	.string "TRAINER TIPS\pPOKéMON stats\nvary--even within\lthe same species.\pTheir stats may be\nsimilar at first.\pHowever, differ-\nences will become\ppronounced as the\nPOKéMON grow.$"
J_Route36TrainerTips2Text::
	.string "TRAINER TIPS\pUse DIG to return\nto the entrance of\lany place.\pIt is convenient\nfor exploring\pcaves and other\nlandmarks.$"
J_Route36_MapEvents::
