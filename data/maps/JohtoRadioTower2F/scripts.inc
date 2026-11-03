@ KJH: translated from pokecrystal maps/RadioTower2F.asm by kjh_tools/johto

JohtoRadioTower2F_MapScripts::
	.byte 0

J_W_RadioTower2FSuperNerdScript::
	lock
	call J_RadioTower2FSuperNerdScript
	release
	end

J_W_RadioTower2FTeacherScript::
	lock
	call J_RadioTower2FTeacherScript
	release
	end

J_T_TrainerGruntM4::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_4, J_GruntM4SeenText, J_GruntM4BeatenText
	call J_TrainerGruntM4_Script
	release
	end

J_T_TrainerGruntM5::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_5, J_GruntM5SeenText, J_GruntM5BeatenText
	call J_TrainerGruntM5_Script
	release
	end

J_T_TrainerGruntM6::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_6, J_GruntM6SeenText, J_GruntM6BeatenText
	call J_TrainerGruntM6_Script
	release
	end

J_T_TrainerGruntF2::
	trainerbattle_single TRAINER_J_GRUNTF_GRUNTF_2, J_GruntF2SeenText, J_GruntF2BeatenText
	call J_TrainerGruntF2_Script
	release
	end

J_W_RadioTower2FBlackBelt1Script::
	lock
	call J_RadioTower2FBlackBelt1Script
	release
	end

J_W_RadioTower2FBlackBelt2Script::
	lock
	call J_RadioTower2FBlackBelt2Script
	release
	end

J_W_RadioTowerJigglypuff::
	lock
	call J_RadioTowerJigglypuff
	release
	end

J_W_Buena::
	lock
	call J_Buena
	release
	end

J_W_RadioTowerBuenaPrizeReceptionist::
	lock
	call J_RadioTowerBuenaPrizeReceptionist
	release
	end

J_S_RadioTower2FSalesSign::
	lockall
	call J_RadioTower2FSalesSign
	releaseall
	end

J_S_RadioTower2FOaksPKMNTalkSign::
	lockall
	call J_RadioTower2FOaksPKMNTalkSign
	releaseall
	end

J_S_RadioTower2FBookshelf::
	lockall
	call J_RadioTower2FBookshelf
	releaseall
	end

J_S_RadioTower2FPokemonRadioSign::
	lockall
	call J_RadioTower2FPokemonRadioSign
	releaseall
	end

J_RadioTower2F_MapScripts::
J_RadioTower2FNoopScene::
	return
J_RadioTower2FSuperNerdScript::
	faceplayer
	message J_RadioTower2FSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower2FTeacherScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_ROCKETS_IN_RADIO_TOWER, J_L89
	setvar VAR_RESULT, 1
J_L89:
	goto_if_ne VAR_RESULT, 0, J_RadioTower2FTeacherScript_Rockets
	message J_RadioTower2FTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower2FTeacherScript_Rockets:
	message J_RadioTower2FTeacherText_Rockets
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTowerJigglypuff::
	message J_RadioTowerJigglypuffText
	waitmessage
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_RadioTower2FBlackBelt1Script::
	faceplayer
	message J_RadioTower2FBlackBelt1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower2FBlackBelt2Script::
	faceplayer
	message J_RadioTower2FBlackBelt2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM4::
J_TrainerGruntM4_Script:
	message J_GruntM4AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM5::
J_TrainerGruntM5_Script:
	message J_GruntM5AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM6::
J_TrainerGruntM6_Script:
	message J_GruntM6AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntF2::
J_TrainerGruntF2_Script:
	message J_GruntF2AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Buena::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_ROCKETS_IN_RADIO_TOWER, J_L90
	setvar VAR_RESULT, 1
J_L90:
	goto_if_ne VAR_RESULT, 0, J_Buena_MidRocketTakeover
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_MET_BUENA, J_L91
	setvar VAR_RESULT, 1
J_L91:
	goto_if_eq VAR_RESULT, 0, J_Buena_Introduction
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_BUENAS_PASSWORD_2, J_L92
	setvar VAR_RESULT, 1
J_L92:
	goto_if_ne VAR_RESULT, 0, J_Buena_PlayedAlready
	setvar VAR_0x8004, 10
	special KJH_CrystalReadVar
	goto_if_lt VAR_RESULT, 18, J_Buena_TooEarly
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_BUENAS_PASSWORD, J_L93
	setvar VAR_RESULT, 1
J_L93:
	goto_if_eq VAR_RESULT, 0, J_Buena_TuneIn
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_BLUE_CARD, J_L94
	setvar VAR_RESULT, 1
J_L94:
	goto_if_eq VAR_RESULT, 0, J_Buena_NoBlueCard
	setvar VAR_0x8004, 24
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J_Buena_BlueCardCapped0
	playbgm MUS_SCHOOL, FALSE
	message J_RadioTower2FBuenaDoYouKnowPasswordText
	waitmessage
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_Buena_ForgotPassword
	message J_RadioTower2FBuenaJoinTheShowText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 10, DIR_EAST
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	goto_if_ne VAR_RESULT, 3, J_Buena_DontNeedToMove
	applymovement OBJ_EVENT_ID_PLAYER, J_RadioTower2FPlayerWalksToMicrophoneMovement
	waitmovement OBJ_EVENT_ID_PLAYER
J_Buena_DontNeedToMove:
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	message J_RadioTower2FBuenaEveryoneSayPasswordText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 10, DIR_SOUTH
	special DrawWholeMapView
	setvar VAR_RESULT, 0
	closemessage
	goto_if_eq VAR_RESULT, 0, J_Buena_WrongAnswer
	message J_RadioTower2FBuenaCorrectAnswerText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_0x8004, 24
	special KJH_CrystalReadVar
	addvar VAR_RESULT, 1
	waitse
	playse SE_SHOP
	setflag FLAG_J_ENGINE_BUENAS_PASSWORD_2
	delay 20
	turnobject 10, DIR_EAST
	message J_RadioTower2FBuenaThanksForComingText
	waitmessage
	waitbuttonpress
	closemessage
	fadeoutbgm 0
	delay 20
	fadedefaultbgm
	setvar VAR_0x8004, 24
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J_Buena_BlueCardCapped1
	return
J_Buena_Introduction:
	message J_RadioTower2FBuenaShowIntroductionText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_MET_BUENA
	bufferstring STR_VAR_2, J_ItemName_BLUE_CARD
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message J_Text_ReceivedKeyItem
	waitmessage
	waitfanfare
	setflag FLAG_J_HAS_BLUE_CARD
	setvar VAR_RESULT, 1
J_Buena_TuneIn:
	message J_RadioTower2FBuenaTuneInToMyShowText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_Buena_Registered0
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUENA_OFFERED_HER_PHONE_NUMBER, J_L95
	setvar VAR_RESULT, 1
J_L95:
	goto_if_ne VAR_RESULT, 0, J_Buena_OfferedNumberBefore
J_Buena_Registered0:
	turnobject 10, DIR_EAST
	return
J_Buena_ForgotPassword:
	message J_RadioTower2FBuenaComeBackAfterListeningText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 10, DIR_EAST
	fadeoutbgm 0
	delay 20
	fadedefaultbgm
	return
J_Buena_PlayedAlready:
	message J_RadioTower2FBuenaAlreadyPlayedText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_Buena_Registered1
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUENA_OFFERED_HER_PHONE_NUMBER, J_L96
	setvar VAR_RESULT, 1
J_L96:
	goto_if_ne VAR_RESULT, 0, J_Buena_OfferedNumberBefore
J_Buena_Registered1:
	turnobject 10, DIR_EAST
	delay 10
	return
J_Buena_WrongAnswer:
	setflag FLAG_J_ENGINE_BUENAS_PASSWORD_2
	message J_RadioTower2FBuenaDidYouForgetText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 10, DIR_EAST
	delay 20
	message J_RadioTower2FBuenaThanksForComingText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 10, DIR_EAST
	fadeoutbgm 0
	delay 20
	fadedefaultbgm
	return
J_Buena_MidRocketTakeover:
	message J_RadioTower2FBuenaPasswordIsHelpText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Buena_NoBlueCard:
	message J_RadioTower2FBuenaNoBlueCardText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_Buena_Registered2
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUENA_OFFERED_HER_PHONE_NUMBER_NO_BLUE_CARD, J_L97
	setvar VAR_RESULT, 1
J_L97:
	goto_if_ne VAR_RESULT, 0, J_Buena_OfferedNumberBefore
J_Buena_Registered2:
	turnobject 10, DIR_EAST
	return
J_Buena_BlueCardCapped0:
	message J_RadioTower2FBuenaCardIsFullText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_Buena_Registered3
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUENA_OFFERED_HER_PHONE_NUMBER_NO_BLUE_CARD, J_L98
	setvar VAR_RESULT, 1
J_L98:
	goto_if_ne VAR_RESULT, 0, J_Buena_OfferedNumberBefore
J_Buena_Registered3:
	turnobject 10, DIR_EAST
	return
J_Buena_TooEarly:
	message J_RadioTower2FBuenaTuneInAfterSixText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_Buena_Registered4
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUENA_OFFERED_HER_PHONE_NUMBER, J_L99
	setvar VAR_RESULT, 1
J_L99:
	goto_if_ne VAR_RESULT, 0, J_Buena_OfferedNumberBefore
J_Buena_Registered4:
	return
J_Buena_BlueCardCapped1:
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_Buena_HasNumber
	delay 20
	turnobject 10, DIR_SOUTH
	delay 15
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 15
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUENA_OFFERED_HER_PHONE_NUMBER_NO_BLUE_CARD, J_L100
	setvar VAR_RESULT, 1
J_L100:
	goto_if_ne VAR_RESULT, 0, J_Buena_OfferedNumberBefore
	applymovement 10, J_Movement_Exclamation
	waitmovement 0
	setflag FLAG_J_BUENA_OFFERED_HER_PHONE_NUMBER_NO_BLUE_CARD
	setflag FLAG_J_BUENA_OFFERED_HER_PHONE_NUMBER
	message J_RadioTower2FBuenaOfferPhoneNumberText
	waitmessage
	goto J_Buena_AskForNumber
J_Buena_OfferedNumberBefore:
	message J_RadioTower2FBuenaOfferNumberAgainText
	waitmessage
J_Buena_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_Buena_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_Buena_NumberDeclined
	message J_RadioTower2FRegisteredBuenasNumberText
	waitmessage
	playse SE_SUCCESS
	waitse
	waitbuttonpress
	message J_RadioTower2FBuenaCallMeText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 10, DIR_EAST
	return
J_Buena_NumberDeclined:
	message J_RadioTower2FBuenaSadRejectedText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 10, DIR_EAST
	return
J_Buena_PhoneFull:
	message J_RadioTower2FBuenaYourPhoneIsFullText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 10, DIR_EAST
J_Buena_HasNumber:
	return
J_RadioTowerBuenaPrizeReceptionist::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_BLUE_CARD, J_L101
	setvar VAR_RESULT, 1
J_L101:
	goto_if_eq VAR_RESULT, 0, J_RadioTowerBuenaPrizeReceptionist_NoCard
	message J_RadioTower2FBuenaReceptionistPointsForPrizesText
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	closemessage
	return
J_RadioTowerBuenaPrizeReceptionist_NoCard:
	message J_RadioTower2FBuenaReceptionistNoCardText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower2FSalesSign::
	message J_RadioTower2FSalesSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower2FOaksPKMNTalkSign::
	message J_RadioTower2FOaksPKMNTalkSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower2FPokemonRadioSign::
	message J_RadioTower2FPokemonRadioSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RadioTower2FBookshelf::
	goto J_MagazineBookshelfScript
J_RadioTower2FPlayerWalksToMicrophoneMovement::
	walk_slow_down
	walk_slow_right
	step_end
J_RadioTower2FSuperNerdText::
	.string "You can listen to\nthe radio any-\lwhere. Tune in!$"
J_RadioTower2FTeacherText::
	.string "Lullabies on the\nradio may make\lPOKéMON sleep.$"
J_RadioTower2FTeacherText_Rockets::
	.string "Why would they\nwant to take over\lthe RADIO TOWER?$"
J_RadioTowerJigglypuffText::
	.string "JIGGLYPUFF:\nJiggly…$"
J_RadioTower2FBlackBelt1Text::
	.string "Sorry. Authorized\npersonnel only\lbeyond this point.\pIt wasn't that way\nbefore.\pThere's something\nwrong with the\lDIRECTOR…$"
J_RadioTower2FBlackBelt2Text::
	.string "Feel free to look\naround anywhere.\pThe DIRECTOR is\nnice again, just\las he was before.$"
J_GruntM4SeenText::
	.string "Three years ago,\nTEAM ROCKET was\lforced to disband.\pBut we're making a\ncomeback here!$"
J_GruntM4BeatenText::
	.string "Gwah! Don't get\ncute!$"
J_GruntM4AfterBattleText::
	.string "We won't let you\nruin our plans\lfor our comeback!$"
J_GruntM5SeenText::
	.string "We're TEAM ROCKET,\nthe exploiters of\lPOKéMON!\pWe love being\nevil! Scared?$"
J_GruntM5BeatenText::
	.string "You think you're a\nhero?$"
J_GruntM5AfterBattleText::
	.string "We're not always\nevil. We just do\lwhatever we like.$"
J_GruntM6SeenText::
	.string "Hey, hey! Keep out\nof our way!$"
J_GruntM6BeatenText::
	.string "Arggh. I give up.$"
J_GruntM6AfterBattleText::
	.string "Our EXECUTIVES are\ntrying to take\lthis place over.\pThey have some big\nplan. I wonder\lwhat that is?$"
J_GruntF2SeenText::
	.string "Hahaha!\pHow boring.\nIt was far too\peasy to take over\nthis place!\pCome on, keep me\namused!$"
J_GruntF2BeatenText::
	.string "Wh-who are you?$"
J_GruntF2AfterBattleText::
	.string "You beat me, and\nI won't forget it!$"
J_RadioTower2FBuenaShowIntroductionText::
	.string "BUENA: Hi! I'm\nBUENA!\pDo you know about\na radio program\lcalled PASSWORD?\pIf you can tell me\nthe password from\pthe program, you\nwill earn points.\pSave up those\npoints and trade\pthem to that sweet\nyoung lady over\pthere for some\nchoice prizes!\pHere you go!\pIt's your very own\npoint card!$"
J_RadioTower2FBuenaTuneInToMyShowText::
	.string "BUENA: Tune in to\nmy PASSWORD SHOW!$"
J_RadioTower2FBuenaDoYouKnowPasswordText::
	.string "BUENA: Hi!\nDid you tune in to\lmy radio show?\pDo you remember\ntoday's password?$"
J_RadioTower2FBuenaJoinTheShowText::
	.string "BUENA: Oh, wow!\nThank you!\pWhat was your name\nagain?\p…{PLAYER}, OK!\pCome on, {PLAYER}.\nJoin the show.$"
J_RadioTower2FBuenaEveryoneSayPasswordText::
	.string "BUENA: Everyone\nready?\pI want to hear you\nshout out today's\ppassword for\n{PLAYER}!$"
J_RadioTower2FBuenaComeBackAfterListeningText::
	.string "BUENA: Come back\nafter you listen\pto my show, OK?\nCatch ya later!$"
J_RadioTower2FBuenaAlreadyPlayedText::
	.string "BUENA: Sorry…\pYou get just one\nchance each day.\pCome back tomorrow\nfor another try!$"
J_RadioTower2FBuenaCorrectAnswerText::
	.string "BUENA: YIPPEE!\nThat's right!\pYou did tune in!\nI'm so happy!\pYou earned one\npoint! Congrats!$"
J_RadioTower2FBuenaDidYouForgetText::
	.string "BUENA: Aww…\nThat's not it…\pDid you forget the\npassword?$"
J_RadioTower2FBuenaThanksForComingText::
	.string "BUENA: Yup! Our\ncontestant was\p{PLAYER}.\nThanks for coming!\pI hope all you\nlisteners will\pcome too!\nI'll be waiting!$"
J_RadioTower2FBuenaPasswordIsHelpText::
	.string "BUENA: Huh?\nToday's password?\pHELP, of course!$"
J_RadioTower2FBuenaCardIsFullText::
	.string "BUENA: Your BLUE\nCARD's full.\pTrade it in for a\nfabulous prize!$"
J_RadioTower2FBuenaTuneInAfterSixText::
	.string "BUENA: Tune in to\nPASSWORD every\pnight from six to\nmidnight!\pTune in, then drop\nin for a visit!$"
J_RadioTower2FBuenaNoBlueCardText::
	.string "BUENA: Oh? You\nforgot to bring\lyour BLUE CARD?\pI can't give you\npoints if you\ldon't have it.$"
J_RadioTower2FBuenaOfferPhoneNumberText::
	.string "BUENA: Oh! Your\nBLUE CARD reached\p0 points today!\nThat's so wild!\pHmm… There isn't a\nprize for hitting\l0 points, but…\pYou came by so\noften, {PLAYER}.\pI'll make you a\nspecial deal!\pHow would you like\nmy phone number?$"
J_RadioTower2FBuenaOfferNumberAgainText::
	.string "BUENA: {PLAYER},\ndo you want to\pregister my phone\nnumber?$"
J_RadioTower2FRegisteredBuenasNumberText::
	.string "{PLAYER} registered\nBUENA's number.$"
J_RadioTower2FBuenaCallMeText::
	.string "BUENA: I look\nforward to hearing\lfrom you!$"
J_RadioTower2FBuenaSadRejectedText::
	.string "BUENA: Aww… It's a\nspecial prize…$"
J_RadioTower2FBuenaYourPhoneIsFullText::
	.string "BUENA: {PLAYER},\nyour phone list\phas no room left\nfor me…$"
J_RadioTower2FBuenaReceptionistPointsForPrizesText::
	.string "You can cash in\nyour saved points\pfor a lovely prize\nof your choice!$"
J_RadioTower2FBuenaReceptionistNoCardText::
	.string "You can't trade in\npoints without\lyour BLUE CARD.\pDon't forget your\nBLUE CARD!$"
J_RadioTower2FSalesSignText::
	.string "2F SALES$"
J_RadioTower2FOaksPKMNTalkSignText::
	.string "PROF.OAK'S POKéMON\nTALK\pThe Hottest Show\non the Air!$"
J_RadioTower2FPokemonRadioSignText::
	.string "Anywhere, Anytime\nPOKéMON Radio$"
J_RadioTower2F_MapEvents::
