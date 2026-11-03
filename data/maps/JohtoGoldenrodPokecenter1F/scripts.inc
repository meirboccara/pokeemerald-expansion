@ KJH: translated from pokecrystal maps/GoldenrodPokecenter1F.asm by kjh_tools/johto

JohtoGoldenrodPokecenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoGoldenrodPokecenter1F_OnTransition
	.byte 0

JohtoGoldenrodPokecenter1F_OnTransition:
	setrespawn HEAL_LOCATION_J_GOLDENROD
	end

J_W_GoldenrodPokecenter1FNurseScript::
	lock
	call J_GoldenrodPokecenter1FNurseScript
	release
	end

J_W_GoldenrodPokecenter1FGameboyKidScript::
	lock
	call J_GoldenrodPokecenter1FGameboyKidScript
	release
	end

J_W_GoldenrodPokecenter1FLassScript::
	lock
	call J_GoldenrodPokecenter1FLassScript
	release
	end

J_W_GoldenrodPokecenter1FPokefanF::
	lock
	call J_GoldenrodPokecenter1FPokefanF
	release
	end

J_C_GoldenrodPokecenter1F_GSBallSceneLeft::
	lockall
	call J_GoldenrodPokecenter1F_GSBallSceneLeft
	releaseall
	end

J_C_GoldenrodPokecenter1F_GSBallSceneRight::
	lockall
	call J_GoldenrodPokecenter1F_GSBallSceneRight
	releaseall
	end

J_GoldenrodPokecenter1F_MapScripts::
J_GoldenrodPokecenter1FNurseScript::
	goto J_Std_Nurse
J_GoldenrodPokecenter1F_GSBallSceneLeft::
	setvar VAR_RESULT, 11
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 11, J_GoldenrodPokecenter1F_GSBallSceneLeft_gsball
	return
J_GoldenrodPokecenter1F_GSBallSceneLeft_gsball:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_GS_BALL_FROM_GOLDENROD_POKEMON_CENTER, J_L560
	setvar VAR_RESULT, 1
J_L560:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodPokecenter1F_GSBallSceneLeft_cancel
	playse SE_EXIT
	setobjectxyperm 2, 0, 7
	removeobject 2
	addobject 2
	playbgm MUS_RG_FOLLOW_ME, FALSE
	applymovement 2, J_GoldenrodPokeCenter1FLinkReceptionistApproachPlayerAtLeftDoorwayTileMovement
	waitmovement 2
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	message J_GoldenrodPokeCenter1FLinkReceptionistPleaseAcceptGSBallText
	waitmessage
	waitbuttonpress
	bufferstring STR_VAR_2, J_ItemName_GS_BALL
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message J_Text_ReceivedKeyItem
	waitmessage
	waitfanfare
	setflag FLAG_J_HAS_GS_BALL
	setvar VAR_RESULT, 1
	setflag FLAG_J_GOT_GS_BALL_FROM_GOLDENROD_POKEMON_CENTER
	setflag FLAG_J_CAN_GIVE_GS_BALL_TO_KURT
	message J_GoldenrodPokeCenter1FLinkReceptionistPleaseDoComeAgainText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, J_GoldenrodPokeCenter1FLinkReceptionistWalkToStairsFromLeftDoorwayTileMovement
	waitmovement 2
	fadedefaultbgm
	removeobject 2
	playse SE_EXIT
J_GoldenrodPokecenter1F_GSBallSceneLeft_cancel:
	return
J_GoldenrodPokecenter1F_GSBallSceneRight::
	setvar VAR_RESULT, 11
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 11, J_GoldenrodPokecenter1F_GSBallSceneRight_gsball
	return
J_GoldenrodPokecenter1F_GSBallSceneRight_gsball:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_GS_BALL_FROM_GOLDENROD_POKEMON_CENTER, J_L561
	setvar VAR_RESULT, 1
J_L561:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodPokecenter1F_GSBallSceneRight_cancel
	playse SE_EXIT
	setobjectxyperm 2, 0, 7
	removeobject 2
	addobject 2
	playbgm MUS_RG_FOLLOW_ME, FALSE
	applymovement 2, J_GoldenrodPokeCenter1FLinkReceptionistApproachPlayerAtRightDoorwayTileMovement
	waitmovement 2
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	message J_GoldenrodPokeCenter1FLinkReceptionistPleaseAcceptGSBallText
	waitmessage
	waitbuttonpress
	bufferstring STR_VAR_2, J_ItemName_GS_BALL
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message J_Text_ReceivedKeyItem
	waitmessage
	waitfanfare
	setflag FLAG_J_HAS_GS_BALL
	setvar VAR_RESULT, 1
	setflag FLAG_J_GOT_GS_BALL_FROM_GOLDENROD_POKEMON_CENTER
	setflag FLAG_J_CAN_GIVE_GS_BALL_TO_KURT
	message J_GoldenrodPokeCenter1FLinkReceptionistPleaseDoComeAgainText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 2, J_GoldenrodPokeCenter1FLinkReceptionistWalkToStairsFromRightDoorwayTileMovement
	waitmovement 2
	fadedefaultbgm
	removeobject 2
	playse SE_EXIT
J_GoldenrodPokecenter1F_GSBallSceneRight_cancel:
	return
J_GoldenrodPokecenter1FGameboyKidScript::
	faceplayer
	message J_GoldenrodPokecenter1FGameboyKidText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodPokecenter1FLassScript::
	faceplayer
	message J_GoldenrodPokecenter1FLassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodPokecenter1FPokefanF::
	faceplayer
	message J_GoldenrodPokecenter1FPokefanFDoYouHaveEonMailText
	waitmessage
	waitbuttonpress
	message J_GoldenrodPokecenter1FAskGiveAwayAnEonMailText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_GoldenrodPokecenter1FPokefanF_NoEonMail
	removeitem ITEM_BEAD_MAIL, 1
	goto_if_eq VAR_RESULT, 0, J_GoldenrodPokecenter1FPokefanF_NoEonMail
	message J_GoldenrodPokecenter1FPlayerGaveAwayTheEonMailText
	waitmessage
	waitbuttonpress
	message J_GoldenrodPokecenter1FPokefanFThisIsForYouText
	waitmessage
	waitbuttonpress
	giveitem ITEM_REVIVE, 1
	goto_if_eq VAR_RESULT, 0, J_GoldenrodPokecenter1FPokefanF_NoRoom
	message J_GoldenrodPokecenter1FPokefanFDaughterWillBeDelightedText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodPokecenter1FPokefanF_NoEonMail:
	message J_GoldenrodPokecenter1FPokefanFTooBadText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodPokecenter1FPokefanF_NoRoom:
	additem ITEM_BEAD_MAIL, 1
	message J_GoldenrodPokecenter1FPokefanFAnotherTimeThenText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodPokeCenter1FLinkReceptionistApproachPlayerAtLeftDoorwayTileMovement::
	walk_up
	walk_right
	walk_right
	walk_right
	face_down
	step_end
J_GoldenrodPokeCenter1FLinkReceptionistWalkToStairsFromLeftDoorwayTileMovement::
	walk_left
	walk_left
	walk_left
	walk_down
	step_end
J_GoldenrodPokeCenter1FLinkReceptionistApproachPlayerAtRightDoorwayTileMovement::
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	face_down
	step_end
J_GoldenrodPokeCenter1FLinkReceptionistWalkToStairsFromRightDoorwayTileMovement::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end
J_GoldenrodPokecomCenterWelcomeToTradeCornerText::
	.string "Hello! Welcome to\nPOKéCOM CENTER\lTRADE CORNER.\pYou can trade\nPOKéMON with other\lpeople far away.$"
J_GoldenrodPokecomCenterWeMustHoldYourMonText::
	.string "To make a trade,\nwe must hold your\lPOKéMON.\pWould you like to\ntrade?$"
J_GoldenrodPokecomCenterWhatMonDoYouWantText::
	.string "What kind of\nPOKéMON do you\lwant in return?$"
J_GoldenrodPokecomCenterWeWillTradeYourMonForMonText::
	.string "Fine. We will try\nto trade your\p{STR_VAR_1} for\n{STR_VAR_2}.\pWe'll have to hold\nyour POKéMON\lduring the trade.\pPlease wait while\nwe prepare the\lroom for it.$"
J_GoldenrodPokecomCenterWeWillTradeYourMonForNewText::
	.string "Fine. We will try\nto trade your\p{STR_VAR_1} for a\nPOKéMON that you\lhave never seen.\pWe'll have to hold\nyour POKéMON\lduring the trade.\pPlease wait while\nwe prepare the\lroom for it.$"
J_GoldenrodPokecomCenterYourMonHasBeenReceivedText::
	.string "Your trade POKéMON\nhas been received.\pIt will take time\nto find a trade\ppartner. Please\ncome back later.$"
J_GoldenrodPokecomCenterYouHaveOnlyOneMonText::
	.string "Oh? You have only\none POKéMON in\lyour party. \pPlease come back\nonce you've in-\lcreased the size\lof your party.$"
J_GoldenrodPokecomCenterWeHopeToSeeYouAgainText::
	.string "We hope to see you\nagain.$"
J_GoldenrodPokecomCenterCommunicationErrorText::
	.string "Communication\nerror…$"
J_GoldenrodPokecomCenterCantAcceptLastMonText::
	.string "If we accept that\nPOKéMON, what will\lyou battle with?$"
J_GoldenrodPokecomCenterCantAcceptEggText::
	.string "Sorry. We can't\naccept an EGG.$"
J_GoldenrodPokecomCenterCantAcceptAbnormalMonText::
	.string "Sorry, but your\nPOKéMON appears to\pbe abnormal. We\ncan't accept it.$"
J_GoldenrodPokecomCenterAlreadyHoldingMonText::
	.string "Oh? Aren't we\nalready holding a\lPOKéMON of yours?$"
J_GoldenrodPokecomCenterCheckingTheRoomsText::
	.string "We'll check the\nrooms.\pPlease wait.$"
J_GoldenrodPokecomCenterTradePartnerHasBeenFoundText::
	.string "Thank you for your\npatience.\pA trade partner\nhas been found.$"
J_GoldenrodPokecomCenterItsYourNewPartnerText::
	.string "It's your new\npartner.\pPlease take care\nof it with love.\pWe hope to see you\nagain.$"
J_GoldenrodPokecomCenterYourPartyIsFullText::
	.string "Uh-oh. Your party\nis already full.\pPlease come back\nwhen you have room\lin your party.$"
J_GoldenrodPokecomCenterNoTradePartnerFoundText::
	.string "It's unfortunate,\nbut no one has\pcome forward as a\ntrade partner.\pWould you like\nyour POKéMON back?$"
J_GoldenrodPokecomCenterReturnedYourMonText::
	.string "We have returned\nyour POKéMON.$"
J_GoldenrodPokecomCenterYourMonIsLonelyText::
	.string "It's unfortunate,\nbut no one has\pcome forward as a\ntrade partner.\pWe've held your\nPOKéMON for a long\ptime. As a result,\nit is very lonely.\pSorry, but we must\nreturn it to you.$"
J_GoldenrodPokecenter1FWeHopeToSeeYouAgainText_2::
	.string "We hope to see you\nagain.$"
J_GoldenrodPokecomCenterContinueToHoldYourMonText::
	.string "Fine. We will\ncontinue to hold\lyour POKéMON.$"
J_GoldenrodPokecomCenterRecentlyLeftYourMonText::
	.string "Oh? You left your\nPOKéMON with us\lonly recently.\pPlease come back\nlater.$"
J_GoldenrodPokecomCenterSaveBeforeTradeCornerText::
	.string "We'll SAVE before\nconnecting to the\lCENTER.$"
J_GoldenrodPokecomCenterWhichMonToTradeText::
	.string "Which POKéMON do\nyou want to trade?$"
J_GoldenrodPokecomCenterTradeCanceledText::
	.string "Sorry, but we must\ncancel the trade.$"
J_GoldenrodPokecomCenterEggTicketText::
	.string "Oh!\pI see you have an\nEGG TICKET!\pIt's a coupon that\nspecial people can\predeem for a\nspecial POKéMON!$"
J_GoldenrodPokecomCenterOddEggBriefingText::
	.string "Let me give you a\nquick briefing.\pTrades held at the\nTRADE CORNER are\pbetween two\ntrainers who don't\pknow each other's\nidentity.\pAs a result, it\nmay take time.\pHowever, an ODD\nEGG is available\ljust for you.\pIt will be sent to\nyou right away.\pPlease choose one\nof the rooms in\pthe CENTER.\nAn ODD EGG will be\psent from the\nchosen room.$"
J_GoldenrodPokecomCenterPleaseWaitAMomentText::
	.string "Please wait a\nmoment.$"
J_GoldenrodPokecomCenterHereIsYourOddEggText::
	.string "Thank you for\nwaiting.\pWe received your\nODD EGG.\pHere it is!\pPlease raise it\nwith loving care.$"
J_GoldenrodPokecomCenterNoEggTicketServiceText::
	.string "I'm awfully sorry.\pThe EGG TICKET\nexchange service\lisn't running now.$"
J_GoldenrodPokecomCenterNewsMachineText::
	.string "It's a POKéMON\nNEWS MACHINE.$"
J_GoldenrodPokecomCenterWhatToDoText::
	.string "What would you\nlike to do?$"
J_GoldenrodPokecomCenterNewsMachineExplanationText::
	.string "POKéMON NEWS is\nnews compiled from\pthe SAVE files of\nPOKéMON trainers.\pWhen reading the\nNEWS, your SAVE\pfile may be sent\nout.\pThe SAVE file data\nwill contain your\padventure log and\nmobile profile.\pYour phone number\nwill not be sent.\pThe contents of\nthe NEWS will vary\pdepending on the\nSAVE files sent by\pyou and the other\nPOKéMON trainers.\pYou might even be\nin the NEWS!$"
J_GoldenrodPokecomCenterWouldYouLikeTheNewsText::
	.string "Would you like to\nget the NEWS?$"
J_GoldenrodPokecomCenterReadingTheLatestNewsText::
	.string "Reading the latest\nNEWS… Please wait.$"
J_GoldenrodPokecomCenterNoOldNewsText::
	.string "There is no old\nNEWS…$"
J_GoldenrodPokecomCenterCorruptedNewsDataText::
	.string "The NEWS data is\ncorrupted.\pPlease download\nthe NEWS again.$"
J_GoldenrodPokecomCenterMakingPreparationsText::
	.string "We're making\npreparations.\pPlease come back\nlater.$"
J_GoldenrodPokecomCenterSaveBeforeNewsMachineText::
	.string "We will SAVE your\nprogress before\pstarting the NEWS\nMACHINE.$"
J_GoldenrodPokecomCenterPerson1Text::
	.string "Whoa, this POKéMON\nCENTER is huge.\pThey just built\nthis place. They\pinstalled lots of\nnew machines too.$"
J_GoldenrodPokecomCenterPerson2Text::
	.string "I thought up a fun\nnew thing for the\lTRADE CORNER!\pI make a PIDGEY\nhold MAIL, then\pput it up for\ntrade for another\lone!\pIf everyone did\nthat, MAIL could\pbe traded with all\nsorts of people!\pI call it PIDGEY\nMAIL!\pIf it becomes\npopular, I might\pmake lots of new\nfriends!$"
J_GoldenrodPokecomCenterPerson3Text::
	.string "They said you can\ntrade POKéMON with\ptotal strangers up\nhere.\pBut they're still\nadjusting things.$"
J_GoldenrodPokecomCenterPerson4Text::
	.string "Some girl I don't\nknow sent me her\pHOPPIP.\nYou should trade\pfor a POKéMON that\nyou want.$"
J_GoldenrodPokecomCenterPerson5Text::
	.string "I received a\nfemale HOPPIP, but\lits named STANLEY!\pThat's my dad's\nname!$"
J_GoldenrodPokecomCenterPerson6Text::
	.string "What is the NEWS\nMACHINE?\pDoes it get news\nfrom a wider area\lthan the radio?$"
J_GoldenrodPokecomCenterPerson7Text::
	.string "The POKéCOM CENTER\nwill link with all\pPOKéMON CENTERS in\na wireless net.\pThat must mean\nI'll be able to\plink with all\nsorts of people.$"
J_GoldenrodPokecomCenterPerson8Text::
	.string "The machines here\ncan't be used yet.\pStill, it's nice\ncoming to a trendy\pplace before other\npeople.$"
J_GoldenrodPokecomCenterPerson9Text::
	.string "My friend was in\nthe NEWS a while\pback. I was really\nsurprised!$"
J_GoldenrodPokecomCenterPerson10Text::
	.string "I get anxious if I\ndon't check out\lthe latest NEWS!$"
J_GoldenrodPokecomCenterPerson11Text::
	.string "If I get in the\nNEWS and become\pfamous, I bet I'll\nbe adored.\pI wonder how I\ncould get in the\lNEWS?$"
J_GoldenrodPokecenter1FGameboyKidText::
	.string "The COLOSSEUM\nupstairs is for\llink battles.\pBattle records are\nposted on the\pwall, so I can't\nafford to lose.$"
J_GoldenrodPokecomCenterPerson12Text::
	.string "I came over here\nwhen I got word\pthat GOLDENROD's\nPOKéMON CENTER has\pnew machines that\nno one's ever seen\lbefore.\pBut it looks like\nthey're still busy\pwith all their\npreparations…$"
J_GoldenrodPokecomCenterPerson13Text::
	.string "Just seeing all\nthese new things\phere makes me feel\nyounger!$"
J_GoldenrodPokecenter1FLassText::
	.string "A stronger\nPOKéMON doesn't\lalways win.\pAfter all, it may\nhave a type dis-\ladvantage.\pI don't think\nthere is a single\pPOKéMON that is\nthe toughest.$"
J_GoldenrodPokeCenter1FLinkReceptionistPleaseAcceptGSBallText::
	.string "{PLAYER}, isn't it?\pCongratulations!\pAs a special deal,\na GS BALL has been\lsent just for you!\pPlease accept it!$"
J_GoldenrodPokeCenter1FLinkReceptionistPleaseDoComeAgainText::
	.string "Please do come\nagain!$"
J_GoldenrodPokecomCenterSignText::
	.string "POKéCOM CENTER\n1F INFORMATION\pLeft:\nADMINISTRATION\pCenter:\nTRADE CORNER\pRight:\nPOKéMON NEWS$"
J_GoldenrodPokecomCenterNewsMachineNotYetText::
	.string "It's a POKéMON\nNEWS MACHINE!\pIt's not in\noperation yet…$"
J_GoldenrodPokecenter1FPokefanFDoYouHaveEonMailText::
	.string "Oh my, your pack\nlooks so heavy!\pOh! Do you happen\nto have something\lnamed EON MAIL?\pMy daughter is\nafter one.\pYou can part with\none, can't you?$"
J_GoldenrodPokecenter1FAskGiveAwayAnEonMailText::
	.string "Give away an EON\nMAIL?$"
J_GoldenrodPokecenter1FPokefanFThisIsForYouText::
	.string "Oh, that's great!\nThank you, honey!\pHere, this is for\nyou in return!$"
J_GoldenrodPokecenter1FPokefanFDaughterWillBeDelightedText::
	.string "My daughter will\nbe delighted!$"
J_GoldenrodPokecenter1FPokefanFTooBadText::
	.string "Oh? You don't have\none? Too bad.$"
J_GoldenrodPokecenter1FPokefanFAnotherTimeThenText::
	.string "Oh… Well, another\ntime, then.$"
J_GoldenrodPokecenter1FPlayerGaveAwayTheEonMailText::
	.string "{PLAYER} gave away\nthe EON MAIL.$"
J_GoldenrodPokecenter1F_MapEvents::
