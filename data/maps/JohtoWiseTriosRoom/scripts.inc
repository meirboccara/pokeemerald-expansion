@ KJH: translated from pokecrystal maps/WiseTriosRoom.asm by kjh_tools/johto

JohtoWiseTriosRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoWiseTriosRoom_OnTransition
	.byte 0

JohtoWiseTriosRoom_OnTransition:
	call J_WiseTriosRoomWiseTrioCallback
	end

J_W_WiseTriosRoomSage1Script::
	lock
	call J_WiseTriosRoomSage1Script
	release
	end

J_W_WiseTriosRoomSage2Script::
	lock
	call J_WiseTriosRoomSage2Script
	release
	end

J_W_WiseTriosRoomSage3Script::
	lock
	call J_WiseTriosRoomSage3Script
	release
	end

J_T_TrainerSageGaku::
	trainerbattle_single TRAINER_J_SAGE_GAKU, J_SageGakuSeenText, J_SageGakuBeatenText
	call J_TrainerSageGaku_Script
	release
	end

J_T_TrainerSageMasa::
	trainerbattle_single TRAINER_J_SAGE_MASA, J_SageMasaSeenText, J_SageMasaBeatenText
	call J_TrainerSageMasa_Script
	release
	end

J_T_TrainerSageKoji::
	trainerbattle_single TRAINER_J_SAGE_KOJI, J_SageKojiSeenText, J_SageKojiBeatenText
	call J_TrainerSageKoji_Script
	release
	end

J_C_WiseTriosRoom_CannotEnterTinTowerScript::
	lockall
	call J_WiseTriosRoom_CannotEnterTinTowerScript
	releaseall
	end

J_WiseTriosRoom_MapScripts::
J_WiseTriosRoomNoop1Scene::
	return
J_WiseTriosRoomNoop2Scene::
	return
J_WiseTriosRoomWiseTrioCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOUGHT_SUICUNE, J_L273
	setvar VAR_RESULT, 1
J_L273:
	goto_if_ne VAR_RESULT, 0, J_WiseTriosRoomWiseTrioCallback_NoWiseTrio
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_KOJI_ALLOWS_YOU_PASSAGE_TO_TIN_TOWER, J_L274
	setvar VAR_RESULT, 1
J_L274:
	goto_if_ne VAR_RESULT, 0, J_WiseTriosRoomWiseTrioCallback_WiseTrio2
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_CLEAR_BELL, J_L275
	setvar VAR_RESULT, 1
J_L275:
	goto_if_ne VAR_RESULT, 0, J_WiseTriosRoomWiseTrioCallback_WiseTrio2
	clearflag FLAG_J_WISE_TRIOS_ROOM_WISE_TRIO_1
	setflag FLAG_J_WISE_TRIOS_ROOM_WISE_TRIO_2
	return
J_WiseTriosRoomWiseTrioCallback_WiseTrio2:
	setflag FLAG_J_WISE_TRIOS_ROOM_WISE_TRIO_1
	clearflag FLAG_J_WISE_TRIOS_ROOM_WISE_TRIO_2
	return
J_WiseTriosRoomWiseTrioCallback_NoWiseTrio:
	setflag FLAG_J_WISE_TRIOS_ROOM_WISE_TRIO_1
	setflag FLAG_J_WISE_TRIOS_ROOM_WISE_TRIO_2
	return
J_WiseTriosRoomSage1Script::
	faceplayer
	message J_WiseTriosRoomSage1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_WiseTriosRoomSage2Script::
	faceplayer
	message J_WiseTriosRoomSage2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_WiseTriosRoomSage3Script::
	faceplayer
	message J_WiseTriosRoomSage3Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_WiseTriosRoom_CannotEnterTinTowerScript::
	turnobject 3, DIR_NORTH
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement 3, J_Movement_Exclamation
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, J_WiseTriosRoomSageBlocksPlayerMovement
	applymovement 3, J_WiseTriosRoomSageBlocksPlayerMovement
	waitmovement 3
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	message J_WiseTriosRoomSage3BlocksExitText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 3, J_WiseTriosRoomSageReturnsMovement
	waitmovement 3
	turnobject 3, DIR_WEST
	return
J_TrainerSageGaku::
J_TrainerSageGaku_Script:
	message J_SageGakuAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSageMasa::
J_TrainerSageMasa_Script:
	message J_SageMasaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSageKoji::
J_TrainerSageKoji_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_KOJI_ALLOWS_YOU_PASSAGE_TO_TIN_TOWER, J_L276
	setvar VAR_RESULT, 1
J_L276:
	goto_if_ne VAR_RESULT, 0, J_TrainerSageKoji_KojiAllowsPassage
	delay 10
	applymovement 6, J_Movement_Exclamation
	waitmovement 0
	message J_SageKojiAfterBattleQuestionText
	waitmessage
	waitbuttonpress
	message J_SageKojiAfterBattleSpeechText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 6, J_WiseTriosRoomSageAllowsPassageMovement
	waitmovement 6
	turnobject 6, DIR_NORTH
	setflag FLAG_J_KOJI_ALLOWS_YOU_PASSAGE_TO_TIN_TOWER
	setvar VAR_J_SCENE_WISE_TRIOS_ROOM, 1
	return
J_TrainerSageKoji_KojiAllowsPassage:
	message J_SageKojiAfterBattleFinalText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_WiseTriosRoomSageBlocksPlayerMovement::
	walk_left
	walk_left
	step_end
J_WiseTriosRoomSageReturnsMovement::
	walk_right
	walk_down
	step_end
J_WiseTriosRoomSageAllowsPassageMovement::
	walk_right
	walk_down
	step_end
J_WiseTriosRoomSage1Text::
	.string "Astounding…\pSUICUNE, ENTEI and\nRAIKOU have arisen\lfrom their sleep…\pIs the legend\ncoming true?$"
J_WiseTriosRoomSage2Text::
	.string "We train at the\nBURNED TOWER, but\pwe've never heard\nof a hole opening\pup there before.\nIt must have been\pdeliberately made\nby someone.$"
J_WiseTriosRoomSage3BlocksExitText::
	.string "TIN TOWER may be\nentered by those\pbearing ECRUTEAK's\nGYM BADGE.\pHowever, now that\nSUICUNE, RAIKOU\pand ENTEI have\narisen, I ask you\pto refrain from\nentering!$"
J_WiseTriosRoomSage3Text::
	.string "We, the WISE TRIO,\nare the protectors\pof the legendary\nPOKéMON.$"
J_SageGakuSeenText::
	.string "Legend has it that\nupon the emergence\pof a trainer who\nhas the ability to\ptouch the souls of\nPOKéMON, a POKéMON\pwill come forth to\nput that trainer\pto test at the TIN\nTOWER.\pThe legend has\ncome true!\pThe legendary\nPOKéMON SUICUNE\lhas arrived!\pWe, the WISE TRIO,\nshall test your\pworthiness to go\ninside!$"
J_SageGakuBeatenText::
	.string "Stronger than we\nthought? Perhaps…$"
J_SageGakuAfterBattleText::
	.string "Ah, so it is you\nwho claim to have\pseen SUICUNE,\nENTEI and RAIKOU\lwhile they slept?\pUnbelievable!\pLegend has it that\nthey can't be seen\lwhile they sleep…$"
J_SageMasaSeenText::
	.string "Can you be trusted\nwith the truth?\pI must ascertain\nyour worthiness.$"
J_SageMasaBeatenText::
	.string "…I will tell you\nthe truth…$"
J_SageMasaAfterBattleText::
	.string "In the past, there\nwere two nine-tier\ltowers here.\pThe BRASS TOWER,\nwhich was said to\pawaken POKéMON,\nand the TIN TOWER,\pwhere POKéMON were\nsaid to rest.\pThe view from the\ntops of the TOWERS\pmust have been\nmagnificent.\pAt the time, an\nimmense, silver-\pcolored POKéMON\nwas said to make\pits roost atop the\nBRASS TOWER.\pHowever…\pAbout 150 years\nago, a lightning\pbolt struck one of\nthe TOWERS.\pIt was engulfed in\nflames that raged\lfor three days.\pA sudden downpour\nfinally put out\lthe blaze.\pAnd that is how\nthe BURNED TOWER\lcame to be.$"
J_SageKojiSeenText::
	.string "Let me see your\npower!$"
J_SageKojiBeatenText::
	.string "Too strong!\nWhy?$"
J_SageKojiAfterBattleQuestionText::
	.string "You… Are you the\ntrainer who is\pawaited by the\nlegendary POKéMON?$"
J_SageKojiAfterBattleSpeechText::
	.string "I see…\pWe, the WISE TRIO,\nhave been given \pthe responsibility\nof protecting the\plegendary POKéMON.\nWe are to allow\ppassage only to\nthose people who\ppossess the power\nand soul of truth.\pPlease, do go on\nand enter the TIN\lTOWER ahead.\pSUICUNE will put\nyou to the test.$"
J_SageKojiAfterBattleFinalText::
	.string "Please, do go on.\pSUICUNE will put\nyou to the test.$"
J_WiseTriosRoom_MapEvents::
