@ KJH: translated from pokecrystal maps/RadioTower1F.asm by kjh_tools/johto

JohtoRadioTower1F_MapScripts::
	.byte 0

J_W_RadioTower1FReceptionistScript::
	lock
	call J_RadioTower1FReceptionistScript
	release
	end

J_W_RadioTower1FLassScript::
	lock
	call J_RadioTower1FLassScript
	release
	end

J_W_RadioTower1FYoungsterScript::
	lock
	call J_RadioTower1FYoungsterScript
	release
	end

J_T_TrainerGruntM3::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_3, J_GruntM3SeenText, J_GruntM3BeatenText
	call J_TrainerGruntM3_Script
	release
	end

J_W_RadioTower1FLuckyNumberManScript::
	lock
	call J_RadioTower1FLuckyNumberManScript
	release
	end

J_W_RadioTower1FRadioCardWomanScript::
	lock
	call J_RadioTower1FRadioCardWomanScript
	release
	end

J_S_RadioTower1FDirectory::
	lockall
	call J_RadioTower1FDirectory
	releaseall
	end

J_S_RadioTower1FLuckyChannelSign::
	lockall
	call J_RadioTower1FLuckyChannelSign
	releaseall
	end

J_RadioTower1F_MapScripts::
J_RadioTower1FReceptionistScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_ROCKETS_IN_RADIO_TOWER, J_L86
	setvar VAR_RESULT, 1
J_L86:
	goto_if_ne VAR_RESULT, 0, J_RadioTower1FReceptionistScript_Rockets
	message J_RadioTower1FReceptionistWelcomeText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower1FReceptionistScript_Rockets:
	message J_RadioTower1FReceptionistNoToursText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower1FLuckyNumberManScript::
	faceplayer
	message J_RadioTower1FLuckyNumberManAskToPlayText
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_RadioTower1FLuckyNumberManScript_skip
	setvar VAR_RESULT, 0
J_RadioTower1FLuckyNumberManScript_skip:
	setvar VAR_RESULT, 0
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_LUCKY_NUMBER_SHOW, J_L87
	setvar VAR_RESULT, 1
J_L87:
	goto_if_ne VAR_RESULT, 0, J_RadioTower1FLuckyNumberManScript_GameOver
	message J_RadioTower1FLuckyNumberManThisWeeksIdIsText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 5, J_RadioTower1FLuckyNumberManGoToPCMovement
	waitmovement 5
	message J_RadioTower1FLuckyNumberManCheckIfMatchText
	waitmessage
	waitbuttonpress
	waitse
	message J_RadioTower1FLuckyNumberManDotDotDotText
	waitmessage
	playse SE_SUCCESS
	waitse
	waitbuttonpress
	setvar VAR_RESULT, 0
	closemessage
	applymovement 5, J_RadioTower1FLuckyNumberManReturnToPlayerMovement
	waitmovement 5
	goto_if_eq VAR_RESULT, 1, J_RadioTower1FLuckyNumberManScript_FirstPlace
	goto_if_eq VAR_RESULT, 2, J_RadioTower1FLuckyNumberManScript_SecondPlace
	goto_if_eq VAR_RESULT, 3, J_RadioTower1FLuckyNumberManScript_ThirdPlace
	goto J_RadioTower1FLuckyNumberManScript_NoPrize
J_RadioTower1FLuckyNumberManScript_GameOver:
	message J_RadioTower1FLuckyNumberManComeAgainText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower1FLuckyNumberManScript_FirstPlace:
	message J_RadioTower1FLuckyNumberManPerfectMatchText
	waitmessage
	playse SE_SUCCESS
	waitse
	waitbuttonpress
	additem ITEM_MASTER_BALL, 1
	goto_if_eq VAR_RESULT, 0, J_RadioTower1FLuckyNumberManScript_BagFull
	setflag FLAG_J_ENGINE_LUCKY_NUMBER_SHOW
	goto J_RadioTower1FLuckyNumberManScript_GameOver
J_RadioTower1FLuckyNumberManScript_SecondPlace:
	message J_RadioTower1FLuckyNumberManOkayMatchText
	waitmessage
	playse SE_SUCCESS
	waitse
	waitbuttonpress
	additem ITEM_EXP_SHARE, 1
	goto_if_eq VAR_RESULT, 0, J_RadioTower1FLuckyNumberManScript_BagFull
	setflag FLAG_J_ENGINE_LUCKY_NUMBER_SHOW
	goto J_RadioTower1FLuckyNumberManScript_GameOver
J_RadioTower1FLuckyNumberManScript_ThirdPlace:
	message J_RadioTower1FLuckyNumberManWeakMatchText
	waitmessage
	playse SE_SUCCESS
	waitse
	waitbuttonpress
	additem ITEM_PP_UP, 1
	goto_if_eq VAR_RESULT, 0, J_RadioTower1FLuckyNumberManScript_BagFull
	setflag FLAG_J_ENGINE_LUCKY_NUMBER_SHOW
	goto J_RadioTower1FLuckyNumberManScript_GameOver
J_RadioTower1FLuckyNumberManScript_NoPrize:
	message J_RadioTower1FLuckyNumberManNoneOfYourIDNumbersMatchText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower1FLuckyNumberManScript_BagFull:
	message J_RadioTower1FLuckyNumberManNoRoomForYourPrizeText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower1FRadioCardWomanScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_RADIO_CARD, J_L88
	setvar VAR_RESULT, 1
J_L88:
	goto_if_ne VAR_RESULT, 0, J_RadioTower1FRadioCardWomanScript_GotCard
	message J_RadioTower1FRadioCardWomanOfferQuizText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_RadioTower1FRadioCardWomanScript_NoQuiz
	message J_RadioTower1FRadioCardWomanQuestion1Text
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_RadioTower1FRadioCardWomanScript_WrongAnswer
	playse SE_DING_DONG
	waitse
	message J_RadioTower1FRadioCardWomanQuestion2Text
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_RadioTower1FRadioCardWomanScript_WrongAnswer
	playse SE_DING_DONG
	waitse
	message J_RadioTower1FRadioCardWomanQuestion3Text
	waitmessage
	yesnobox 20, 8
	goto_if_ne VAR_RESULT, 0, J_RadioTower1FRadioCardWomanScript_WrongAnswer
	playse SE_DING_DONG
	waitse
	message J_RadioTower1FRadioCardWomanQuestion4Text
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_RadioTower1FRadioCardWomanScript_WrongAnswer
	playse SE_DING_DONG
	waitse
	message J_RadioTower1FRadioCardWomanQuestion5Text
	waitmessage
	yesnobox 20, 8
	goto_if_ne VAR_RESULT, 0, J_RadioTower1FRadioCardWomanScript_WrongAnswer
	playse SE_DING_DONG
	waitse
	message J_RadioTower1FRadioCardWomanYouWinText
	waitmessage
	waitbuttonpress
	bufferstring STR_VAR_2, J_RadioTower1FRadioCardWomanScript_RadioCardText
	call J_RadioTower1FRadioCardWomanScript_ReceiveItem
	message J_RadioTower1FPokegearIsARadioText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_ENGINE_RADIO_CARD
J_RadioTower1FRadioCardWomanScript_GotCard:
	message J_RadioTower1FRadioCardWomanTuneInText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower1FRadioCardWomanScript_RadioCardText:
	.string "RADIO CARD$"
J_RadioTower1FRadioCardWomanScript_ReceiveItem:
	goto J_ReceiveItemScript
	return
J_RadioTower1FRadioCardWomanScript_WrongAnswer:
	playse SE_FAILURE
	message J_RadioTower1FRadioCardWomanWrongAnswerText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower1FRadioCardWomanScript_NoQuiz:
	message J_RadioTower1FRadioCardWomanNotTakingQuizText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower1FLassScript::
	faceplayer
	message J_RadioTower1FLassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower1FYoungsterScript::
	faceplayer
	message J_RadioTower1FYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM3::
J_TrainerGruntM3_Script:
	message J_GruntM3AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower1FDirectory::
	message J_RadioTower1FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower1FLuckyChannelSign::
	message J_RadioTower1FLuckyChannelSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower1FLuckyNumberManGoToPCMovement::
	walk_right
	face_up
	step_end
J_RadioTower1FLuckyNumberManReturnToPlayerMovement::
	walk_left
	face_up
	step_end
J_RadioTower1FReceptionistWelcomeText::
	.string "Welcome!$"
J_RadioTower1FReceptionistNoToursText::
	.string "Hello. I'm sorry,\nbut we're not\loffering any tours\ltoday.$"
J_RadioTower1FLuckyNumberManAskToPlayText::
	.string "Hi, are you here\nfor the LUCKY NUM-\lBER SHOW?\pWant me to check\nthe ID numbers of\lyour POKéMON?\pIf you get lucky,\nyou win a prize.$"
J_RadioTower1FLuckyNumberManThisWeeksIdIsText::
	.string "This week's ID\nnumber is {STR_VAR_1}.$"
J_RadioTower1FLuckyNumberManCheckIfMatchText::
	.string "Let's see if you\nhave a match.$"
J_RadioTower1FLuckyNumberManDotDotDotText::
	.string "……\n……$"
J_RadioTower1FLuckyNumberManComeAgainText::
	.string "Please come back\nnext week for the\lnext LUCKY NUMBER.$"
J_RadioTower1FLuckyNumberManPerfectMatchText::
	.string "Wow! You have a\nperfect match of\lall five numbers!\pWe have a grand\nprize winner!\pYou have won a\nMASTER BALL!$"
J_RadioTower1FLuckyNumberManOkayMatchText::
	.string "Hey! You've\nmatched the last\lthree numbers!\pYou've won second\nprize, an EXP.\lSHARE!$"
J_RadioTower1FLuckyNumberManWeakMatchText::
	.string "Ooh, you've\nmatched the last\ltwo numbers.\pYou've won third\nprize, a PP UP.$"
J_RadioTower1FLuckyNumberManNoneOfYourIDNumbersMatchText::
	.string "Nope, none of your\nID numbers match.$"
J_RadioTower1FLuckyNumberManNoRoomForYourPrizeText::
	.string "You've got no room\nfor your prize.\pMake room and come\nback right away.$"
J_RadioTower1FRadioCardWomanOfferQuizText::
	.string "We have a special\nquiz campaign on\lright now.\pAnswer five ques-\ntions correctly to\lwin a RADIO CARD.\pSlide it into your\nPOKéGEAR to play\pthe radio anytime,\nanywhere.\pWould you like to\ntake the quiz?$"
J_RadioTower1FRadioCardWomanQuestion1Text::
	.string "Question 1:\pIs there a POKéMON\nthat appears only\lin the morning?$"
J_RadioTower1FRadioCardWomanQuestion2Text::
	.string "Correct!\nQuestion 2:\pIs this statement\ncorrect?\pYou can't buy a\nBERRY at a MART.$"
J_RadioTower1FRadioCardWomanQuestion3Text::
	.string "Bull's-eye!\nQuestion 3:\pDoes HM01 contain\nthe move FLASH?$"
J_RadioTower1FRadioCardWomanQuestion4Text::
	.string "So far so good!\nQuestion 4:\pIs FALKNER the\nVIOLET GYM LEADER\pwho uses bird\nPOKéMON?$"
J_RadioTower1FRadioCardWomanQuestion5Text::
	.string "Wow! Right again!\nHere's the final\lquestion:\pDo GOLDENROD GAME\nCORNER's slots\phave CHARMANDER\non their reels?$"
J_RadioTower1FRadioCardWomanYouWinText::
	.string "Bingo! You got it!\nCongratulations!\pHere's your prize,\na RADIO CARD!$"
J_RadioTower1FPokegearIsARadioText::
	.string "{PLAYER}'s POKéGEAR\ncan now double as\la radio!$"
J_RadioTower1FRadioCardWomanTuneInText::
	.string "Please tune in to\nour radio shows.$"
J_RadioTower1FRadioCardWomanWrongAnswerText::
	.string "Oh, dear.\nSorry, but you\pgot it wrong.\nPlease try again!$"
J_RadioTower1FRadioCardWomanNotTakingQuizText::
	.string "Oh. I see. Please\nsee me if you\lchange your mind.$"
J_RadioTower1FLassText::
	.string "BEN is a fabulous\nDJ.\pHis sweet voice\nmakes me melt!$"
J_RadioTower1FYoungsterText::
	.string "I love MARY, from\nPOKéMON TALK.\pI only know what\nshe sounds like,\lthough.$"
J_GruntM3SeenText::
	.string "We've finally\ntaken over the\lRADIO TOWER!\pNow everyone will\nget to experience\pthe true terror of\nTEAM ROCKET!\pWe'll show you\nhow scary we are!$"
J_GruntM3BeatenText::
	.string "Too strong! We\nmust watch you…$"
J_GruntM3AfterBattleText::
	.string "You're too strong.\pOur plan could be\nruined. I must\lwarn the others…$"
J_RadioTower1FDirectoryText::
	.string "1F RECEPTION\n2F SALES\p3F PERSONNEL\n4F PRODUCTION\p5F DIRECTOR'S\n   OFFICE$"
J_RadioTower1FLuckyChannelSignText::
	.string "LUCKY CHANNEL!\pWin with POKéMON\nID numbers!\pTrade your POKéMON\nto collect differ-\lent ID numbers!$"
J_RadioTower1F_MapEvents::
