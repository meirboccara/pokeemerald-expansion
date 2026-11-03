@ KJH: translated from pokecrystal maps/KurtsHouse.asm by kjh_tools/johto

JohtoKurtsHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoKurtsHouse_OnTransition
	.byte 0

JohtoKurtsHouse_OnTransition:
	call J_KurtsHouseKurtCallback
	end

J_W_Kurt1::
	lock
	call J_Kurt1
	release
	end

J_W_KurtsGranddaughter1::
	lock
	call J_KurtsGranddaughter1
	release
	end

J_W_KurtsHouseSlowpoke::
	lock
	call J_KurtsHouseSlowpoke
	release
	end

J_W_Kurt2::
	lock
	call J_Kurt2
	release
	end

J_W_KurtsGranddaughter2::
	lock
	call J_KurtsGranddaughter2
	release
	end

J_S_KurtsHouseRadio::
	lockall
	call J_KurtsHouseRadio
	releaseall
	end

J_S_KurtsHouseOakPhoto::
	lockall
	call J_KurtsHouseOakPhoto
	releaseall
	end

J_S_KurtsHouseBookshelf::
	lockall
	call J_KurtsHouseBookshelf
	releaseall
	end

J_S_KurtsHouseCelebiStatue::
	lockall
	call J_KurtsHouseCelebiStatue
	releaseall
	end

J_KurtsHouse_MapScripts::
J_KurtsHouseKurtCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_SLOWPOKE_WELL, J_L323
	setvar VAR_RESULT, 1
J_L323:
	goto_if_eq VAR_RESULT, 0, J_KurtsHouseKurtCallback_Done
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOREST_IS_RESTLESS, J_L324
	setvar VAR_RESULT, 1
J_L324:
	goto_if_ne VAR_RESULT, 0, J_KurtsHouseKurtCallback_Done
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_KURT_MAKING_BALLS, J_L325
	setvar VAR_RESULT, 1
J_L325:
	goto_if_ne VAR_RESULT, 0, J_KurtsHouseKurtCallback_MakingBalls
	setflag FLAG_J_KURTS_HOUSE_KURT_2
	clearflag FLAG_J_KURTS_HOUSE_KURT_1
	setflag FLAG_J_KURTS_HOUSE_GRANDDAUGHTER_2
	clearflag FLAG_J_KURTS_HOUSE_GRANDDAUGHTER_1
	return
J_KurtsHouseKurtCallback_MakingBalls:
	setflag FLAG_J_KURTS_HOUSE_KURT_1
	clearflag FLAG_J_KURTS_HOUSE_KURT_2
	setflag FLAG_J_KURTS_HOUSE_GRANDDAUGHTER_1
	clearflag FLAG_J_KURTS_HOUSE_GRANDDAUGHTER_2
J_KurtsHouseKurtCallback_Done:
	return
J_Kurt1::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_KURT_GAVE_YOU_LURE_BALL, J_L326
	setvar VAR_RESULT, 1
J_L326:
	goto_if_ne VAR_RESULT, 0, J_Kurt1_GotLureBall
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_SLOWPOKE_WELL, J_L327
	setvar VAR_RESULT, 1
J_L327:
	goto_if_ne VAR_RESULT, 0, J_Kurt1_ClearedSlowpokeWell
	message J_KurtsHouseKurtMakingBallsMustWaitText
	waitmessage
	waitbuttonpress
	closemessage
	fadeoutbgm 0
	setflag FLAG_J_AZALEA_TOWN_SLOWPOKETAIL_ROCKET
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 1, J_Kurt1_RunAround
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	playse SE_M_FLY
	applymovement 1, J_KurtsHouseKurtExitHouseMovement
	waitmovement 1
	playse SE_EXIT
	removeobject 1
	waitse
	fadedefaultbgm
	return
J_Kurt1_RunAround:
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	playse SE_M_FLY
	applymovement 1, J_KurtsHouseKurtGoAroundPlayerThenExitHouseMovement
	waitmovement 1
	playse SE_EXIT
	removeobject 1
	waitse
	fadedefaultbgm
	return
J_Kurt1_ClearedSlowpokeWell:
	message J_KurtsHouseKurtHonoredToMakeBallsText
	waitmessage
	waitbuttonpress
	giveitem ITEM_NET_BALL, 1
	goto_if_eq VAR_RESULT, 0, J_Kurt1_NoRoomForBall
	setflag FLAG_J_KURT_GAVE_YOU_LURE_BALL
J_Kurt1_GotLureBall:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L328
	setvar VAR_RESULT, 1
J_L328:
	goto_if_ne VAR_RESULT, 0, J_Kurt1_WaitForApricorns
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_KURT_RED_APRICORN, J_L329
	setvar VAR_RESULT, 1
J_L329:
	goto_if_ne VAR_RESULT, 0, J_Kurt1_GiveLevelBall
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_KURT_BLU_APRICORN, J_L330
	setvar VAR_RESULT, 1
J_L330:
	goto_if_ne VAR_RESULT, 0, J_Kurt1_GiveLureBall
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_KURT_YLW_APRICORN, J_L331
	setvar VAR_RESULT, 1
J_L331:
	goto_if_ne VAR_RESULT, 0, J_Kurt1_GiveMoonBall
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_KURT_GRN_APRICORN, J_L332
	setvar VAR_RESULT, 1
J_L332:
	goto_if_ne VAR_RESULT, 0, J_Kurt1_GiveFriendBall
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_KURT_WHT_APRICORN, J_L333
	setvar VAR_RESULT, 1
J_L333:
	goto_if_ne VAR_RESULT, 0, J_Kurt1_GiveFastBall
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_KURT_BLK_APRICORN, J_L334
	setvar VAR_RESULT, 1
J_L334:
	goto_if_ne VAR_RESULT, 0, J_Kurt1_GiveHeavyBall
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_KURT_PNK_APRICORN, J_L335
	setvar VAR_RESULT, 1
J_L335:
	goto_if_ne VAR_RESULT, 0, J_Kurt1_GiveLoveBall
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CAN_GIVE_GS_BALL_TO_KURT, J_L336
	setvar VAR_RESULT, 1
J_L336:
	goto_if_ne VAR_RESULT, 0, J_Kurt1_CanGiveGSBallToKurt
J_Kurt1_NoGSBall:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2, J_L337
	setvar VAR_RESULT, 1
J_L337:
	goto_if_ne VAR_RESULT, 0, J_Kurt1_CheckApricorns
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_3, J_L338
	setvar VAR_RESULT, 1
J_L338:
	goto_if_ne VAR_RESULT, 0, J_Kurt1_CheckApricorns
	message J_KurtsHouseKurtBallsFromApricornsText
	waitmessage
	waitbuttonpress
J_Kurt1_CheckApricorns:
	checkitem ITEM_POKE_BALL, 1
	goto_if_ne VAR_RESULT, 0, J_Kurt1_AskApricorn
	checkitem ITEM_POKE_BALL, 1
	goto_if_ne VAR_RESULT, 0, J_Kurt1_AskApricorn
	checkitem ITEM_POKE_BALL, 1
	goto_if_ne VAR_RESULT, 0, J_Kurt1_AskApricorn
	checkitem ITEM_POKE_BALL, 1
	goto_if_ne VAR_RESULT, 0, J_Kurt1_AskApricorn
	checkitem ITEM_POKE_BALL, 1
	goto_if_ne VAR_RESULT, 0, J_Kurt1_AskApricorn
	checkitem ITEM_POKE_BALL, 1
	goto_if_ne VAR_RESULT, 0, J_Kurt1_AskApricorn
	checkitem ITEM_POKE_BALL, 1
	goto_if_ne VAR_RESULT, 0, J_Kurt1_AskApricorn
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2, J_L339
	setvar VAR_RESULT, 1
J_L339:
	goto_if_ne VAR_RESULT, 0, J_Kurt1_ThatTurnedOutGreat
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_3, J_L340
	setvar VAR_RESULT, 1
J_L340:
	goto_if_ne VAR_RESULT, 0, J_Kurt1_IMakeBallsFromApricorns
	closemessage
	return
J_Kurt1_IMakeBallsFromApricorns:
	message J_KurtsHouseKurtBallsFromApricornsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Kurt1_AskApricorn:
	message J_KurtsHouseKurtAskYouHaveAnApricornText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_3
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_Kurt1_Cancel
	goto_if_eq VAR_RESULT, 89, J_Kurt1_Blu
	goto_if_eq VAR_RESULT, 92, J_Kurt1_Ylw
	goto_if_eq VAR_RESULT, 93, J_Kurt1_Grn
	goto_if_eq VAR_RESULT, 97, J_Kurt1_Wht
	goto_if_eq VAR_RESULT, 99, J_Kurt1_Blk
	goto_if_eq VAR_RESULT, 101, J_Kurt1_Pnk
	setflag FLAG_J_GAVE_KURT_RED_APRICORN
	goto J_Kurt1_GaveKurtApricorns
J_Kurt1_Blu:
	setflag FLAG_J_GAVE_KURT_BLU_APRICORN
	goto J_Kurt1_GaveKurtApricorns
J_Kurt1_Ylw:
	setflag FLAG_J_GAVE_KURT_YLW_APRICORN
	goto J_Kurt1_GaveKurtApricorns
J_Kurt1_Grn:
	setflag FLAG_J_GAVE_KURT_GRN_APRICORN
	goto J_Kurt1_GaveKurtApricorns
J_Kurt1_Wht:
	setflag FLAG_J_GAVE_KURT_WHT_APRICORN
	goto J_Kurt1_GaveKurtApricorns
J_Kurt1_Blk:
	setflag FLAG_J_GAVE_KURT_BLK_APRICORN
	goto J_Kurt1_GaveKurtApricorns
J_Kurt1_Pnk:
	setflag FLAG_J_GAVE_KURT_PNK_APRICORN
	goto J_Kurt1_GaveKurtApricorns
J_Kurt1_GaveKurtApricorns:
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1
	setflag FLAG_J_ENGINE_KURT_MAKING_BALLS
J_Kurt1_WaitForApricorns:
	message J_KurtsHouseKurtItWillTakeADayText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Kurt1_Cancel:
	message J_KurtsHouseKurtThatsALetdownText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Kurt1__ThatTurnedOutGreat:
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2
J_Kurt1_ThatTurnedOutGreat:
	message J_KurtsHouseKurtTurnedOutGreatText
	waitmessage
	waitbuttonpress
J_Kurt1_NoRoomForBall:
	closemessage
	return
J_Kurt1_GiveLevelBall:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_KURT_MAKING_BALLS, J_L341
	setvar VAR_RESULT, 1
J_L341:
	goto_if_ne VAR_RESULT, 0, J_KurtMakingBallsScript
	message J_KurtsHouseKurtJustFinishedYourBallText
	waitmessage
	waitbuttonpress
	giveitem ITEM_GREAT_BALL, 1
	goto_if_eq VAR_RESULT, 0, J_Kurt1_NoRoomForBall
	clearflag FLAG_J_GAVE_KURT_RED_APRICORN
	goto J_Kurt1__ThatTurnedOutGreat
J_Kurt1_GiveLureBall:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_KURT_MAKING_BALLS, J_L342
	setvar VAR_RESULT, 1
J_L342:
	goto_if_ne VAR_RESULT, 0, J_KurtMakingBallsScript
	message J_KurtsHouseKurtJustFinishedYourBallText
	waitmessage
	waitbuttonpress
	giveitem ITEM_NET_BALL, 1
	goto_if_eq VAR_RESULT, 0, J_Kurt1_NoRoomForBall
	clearflag FLAG_J_GAVE_KURT_BLU_APRICORN
	goto J_Kurt1__ThatTurnedOutGreat
J_Kurt1_GiveMoonBall:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_KURT_MAKING_BALLS, J_L343
	setvar VAR_RESULT, 1
J_L343:
	goto_if_ne VAR_RESULT, 0, J_KurtMakingBallsScript
	message J_KurtsHouseKurtJustFinishedYourBallText
	waitmessage
	waitbuttonpress
	giveitem ITEM_ULTRA_BALL, 1
	goto_if_eq VAR_RESULT, 0, J_Kurt1_NoRoomForBall
	clearflag FLAG_J_GAVE_KURT_YLW_APRICORN
	goto J_Kurt1__ThatTurnedOutGreat
J_Kurt1_GiveFriendBall:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_KURT_MAKING_BALLS, J_L344
	setvar VAR_RESULT, 1
J_L344:
	goto_if_ne VAR_RESULT, 0, J_KurtMakingBallsScript
	message J_KurtsHouseKurtJustFinishedYourBallText
	waitmessage
	waitbuttonpress
	giveitem ITEM_GREAT_BALL, 1
	goto_if_eq VAR_RESULT, 0, J_Kurt1_NoRoomForBall
	clearflag FLAG_J_GAVE_KURT_GRN_APRICORN
	goto J_Kurt1__ThatTurnedOutGreat
J_Kurt1_GiveFastBall:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_KURT_MAKING_BALLS, J_L345
	setvar VAR_RESULT, 1
J_L345:
	goto_if_ne VAR_RESULT, 0, J_KurtMakingBallsScript
	message J_KurtsHouseKurtJustFinishedYourBallText
	waitmessage
	waitbuttonpress
	giveitem ITEM_GREAT_BALL, 1
	goto_if_eq VAR_RESULT, 0, J_Kurt1_NoRoomForBall
	clearflag FLAG_J_GAVE_KURT_WHT_APRICORN
	goto J_Kurt1__ThatTurnedOutGreat
J_Kurt1_GiveHeavyBall:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_KURT_MAKING_BALLS, J_L346
	setvar VAR_RESULT, 1
J_L346:
	goto_if_ne VAR_RESULT, 0, J_KurtMakingBallsScript
	message J_KurtsHouseKurtJustFinishedYourBallText
	waitmessage
	waitbuttonpress
	giveitem ITEM_GREAT_BALL, 1
	goto_if_eq VAR_RESULT, 0, J_Kurt1_NoRoomForBall
	clearflag FLAG_J_GAVE_KURT_BLK_APRICORN
	goto J_Kurt1__ThatTurnedOutGreat
J_Kurt1_GiveLoveBall:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_KURT_MAKING_BALLS, J_L347
	setvar VAR_RESULT, 1
J_L347:
	goto_if_ne VAR_RESULT, 0, J_KurtMakingBallsScript
	message J_KurtsHouseKurtJustFinishedYourBallText
	waitmessage
	waitbuttonpress
	giveitem ITEM_GREAT_BALL, 1
	goto_if_eq VAR_RESULT, 0, J_Kurt1_NoRoomForBall
	clearflag FLAG_J_GAVE_KURT_PNK_APRICORN
	goto J_Kurt1__ThatTurnedOutGreat
J_Kurt1_CanGiveGSBallToKurt:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_GS_BALL_TO_KURT, J_L348
	setvar VAR_RESULT, 1
J_L348:
	goto_if_ne VAR_RESULT, 0, J_Kurt1_GaveGSBallToKurt
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_GS_BALL, J_L349
	setvar VAR_RESULT, 1
J_L349:
	goto_if_eq VAR_RESULT, 0, J_Kurt1_NoGSBall
	message J_KurtsHouseKurtWhatIsThatText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_GAVE_GS_BALL_TO_KURT
	clearflag FLAG_J_HAS_GS_BALL
	setvar VAR_RESULT, 1
	setflag FLAG_J_ENGINE_KURT_MAKING_BALLS
	return
J_Kurt1_GaveGSBallToKurt:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_KURT_MAKING_BALLS, J_L350
	setvar VAR_RESULT, 1
J_L350:
	goto_if_eq VAR_RESULT, 0, J_Kurt1_NotMakingBalls
	message J_KurtsHouseKurtImCheckingItNowText
	waitmessage
	waitbuttonpress
	message J_KurtsHouseKurtAhHaISeeText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Kurt1_NotMakingBalls:
	message J_KurtsHouseKurtThisBallStartedToShakeText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_FOREST_IS_RESTLESS
	clearflag FLAG_J_CAN_GIVE_GS_BALL_TO_KURT
	clearflag FLAG_J_GAVE_GS_BALL_TO_KURT
	fadeoutbgm 0
	delay 20
	applymovement 1, J_Movement_Exclamation
	waitmovement 0
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 1, J_Kurt1_GSBallRunAround
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	playse SE_M_FLY
	applymovement 1, J_KurtsHouseKurtExitHouseMovement
	waitmovement 1
	goto J_Kurt1_KurtHasLeftTheBuilding
J_Kurt1_GSBallRunAround:
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	playse SE_M_FLY
	applymovement 1, J_KurtsHouseKurtGoAroundPlayerThenExitHouseMovement
	waitmovement 1
J_Kurt1_KurtHasLeftTheBuilding:
	playse SE_EXIT
	removeobject 1
	clearflag FLAG_J_AZALEA_TOWN_KURT
	waitse
	fadedefaultbgm
	setvar VAR_J_SCENE_AZALEA_TOWN, 2
	return
J_Kurt2::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_GS_BALL_TO_KURT, J_L351
	setvar VAR_RESULT, 1
J_L351:
	goto_if_ne VAR_RESULT, 0, J_KurtScript_ImCheckingItNow
J_KurtMakingBallsScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BUGGING_KURT_TOO_MUCH, J_L352
	setvar VAR_RESULT, 1
J_L352:
	goto_if_eq VAR_RESULT, 0, J_Script_FirstTimeBuggingKurt
	message J_KurtsHouseKurtDontBotherMeText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 4, DIR_NORTH
	return
J_Script_FirstTimeBuggingKurt::
	message J_KurtsHouseKurtGranddaughterHelpingWorkFasterText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 4, DIR_NORTH
	setflag FLAG_J_BUGGING_KURT_TOO_MUCH
	return
J_KurtScript_ImCheckingItNow::
	message J_KurtsHouseKurtImCheckingItNowText
	waitmessage
	waitbuttonpress
	turnobject 4, DIR_NORTH
	message J_KurtsHouseKurtAhHaISeeText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_KurtsGranddaughter1::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L353
	setvar VAR_RESULT, 1
J_L353:
	goto_if_ne VAR_RESULT, 0, J_KurtsGranddaughter2Subscript
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2, J_L354
	setvar VAR_RESULT, 1
J_L354:
	goto_if_ne VAR_RESULT, 0, J_KurtsGranddaughterFunScript
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOREST_IS_RESTLESS, J_L355
	setvar VAR_RESULT, 1
J_L355:
	goto_if_ne VAR_RESULT, 0, J_KurtsGranddaughter1_Lonely
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FAST_SHIP_FIRST_TIME, J_L356
	setvar VAR_RESULT, 1
J_L356:
	goto_if_ne VAR_RESULT, 0, J_KurtsGranddaughter1_Dad
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_SLOWPOKE_WELL, J_L357
	setvar VAR_RESULT, 1
J_L357:
	goto_if_ne VAR_RESULT, 0, J_KurtsGranddaughter1_SlowpokeBack
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_AZALEA_TOWN_SLOWPOKETAIL_ROCKET, J_L358
	setvar VAR_RESULT, 1
J_L358:
	goto_if_ne VAR_RESULT, 0, J_KurtsGranddaughter1_Lonely
	message J_KurtsGranddaughterSlowpokeGoneText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_KurtsGranddaughter1_SlowpokeBack:
	message J_KurtsGranddaughterSlowpokeBackText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_KurtsGranddaughter1_Lonely:
	message J_KurtsGranddaughterLonelyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_KurtsGranddaughter1_Dad:
	message J_KurtsGranddaughterDadText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_KurtsGranddaughter2::
	faceplayer
J_KurtsGranddaughter2Subscript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_GS_BALL_TO_KURT, J_L359
	setvar VAR_RESULT, 1
J_L359:
	goto_if_ne VAR_RESULT, 0, J_KurtsGranddaughter2Subscript_GSBall
	message J_KurtsGranddaughterHelpText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 5, DIR_EAST
	return
J_KurtsGranddaughter2Subscript_GSBall:
	message J_KurtsGranddaughterGSBallText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 5, DIR_EAST
	return
J_KurtsGranddaughterFunScript::
	message J_KurtsGranddaughterFunText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_KurtsHouseSlowpoke::
	faceplayer
	message J_KurtsHouseSlowpokeText
	waitmessage
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_KurtsHouseOakPhoto::
	message J_KurtsHouseOakPhotoText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_KurtsHouseCelebiStatue::
	message J_KurtsHouseCelebiStatueText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_KurtsHouseBookshelf::
	goto J_DifficultBookshelfScript
J_KurtsHouseRadio::
	goto J_Radio2Script
J_KurtsHouseKurtExitHouseMovement::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end
J_KurtsHouseKurtGoAroundPlayerThenExitHouseMovement::
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end
J_KurtsHouseKurtMakingBallsMustWaitText::
	.string "Hm? Who are you?\p{PLAYER}, eh? You\nwant me to make\lsome BALLS?\pSorry, but that'll\nhave to wait.\pDo you know TEAM\nROCKET? Ah, don't\pworry. I'll tell\nyou anyhow.\pTEAM ROCKET's an\nevil gang that\puses POKéMON for\ntheir dirty work.\pThey're supposed\nto have disbanded\lthree years ago.\pAnyway, they're at\nthe WELL, cutting\poff SLOWPOKETAILS\nfor sale!\pSo I'm going to\ngo give them a\llesson in pain!\pHang on, SLOWPOKE!\nOld KURT is on his\lway!$"
J_KurtsHouseKurtHonoredToMakeBallsText::
	.string "KURT: Hi, {PLAYER}!\pYou handled your-\nself like a real\lhero at the WELL.\pI like your style!\pI would be honored\nto make BALLS for\pa trainer like\nyou.\pThis is all I have\nnow, but take it.$"
J_KurtsHouseKurtBallsFromApricornsText::
	.string "KURT: I make BALLS\nfrom APRICORNS.\pCollect them from\ntrees and bring\l'em to me.\pI'll make BALLS\nout of them.$"
J_KurtsHouseKurtAskYouHaveAnApricornText::
	.string "KURT: You have an\nAPRICORN for me?\pFine! I'll turn it\ninto a BALL.$"
J_KurtsHouseKurtItWillTakeADayText::
	.string "KURT: It'll take a\nday to make you a\pBALL. Come back\nfor it later.$"
J_KurtsHouseKurtThatsALetdownText::
	.string "KURT: Oh…\nThat's a letdown.$"
J_KurtsHouseKurtDontBotherMeText::
	.string "KURT: I'm working!\nDon't bother me!$"
J_KurtsHouseKurtJustFinishedYourBallText::
	.string "KURT: Ah, {PLAYER}!\nI just finished\lyour BALL. Here!$"
J_KurtsHouseKurtTurnedOutGreatText::
	.string "KURT: That turned\nout great.\pTry catching\nPOKéMON with it.$"
J_KurtsHouseKurtGranddaughterHelpingWorkFasterText::
	.string "KURT: Now that my\ngranddaughter is\phelping me, I can\nwork much faster.$"
J_KurtsHouseKurtWhatIsThatText::
	.string "Wh-what is that?\pI've never seen\none before.\pIt looks a lot\nlike a POKé BALL,\pbut it appears to\nbe something else.\pLet me check it\nfor you.$"
J_KurtsHouseKurtImCheckingItNowText::
	.string "I'm checking it\nnow.$"
J_KurtsHouseKurtAhHaISeeText::
	.string "Ah-ha! I see!\nSo…$"
J_KurtsHouseKurtThisBallStartedToShakeText::
	.string "{PLAYER}!\pThis BALL started\nto shake while I\lwas checking it.\pThere must be\nsomething to this!$"
J_KurtsGranddaughterSlowpokeGoneText::
	.string "The SLOWPOKE are\ngone… Were they\ptaken away by bad\npeople?$"
J_KurtsGranddaughterLonelyText::
	.string "Grandpa's gone…\nI'm so lonely…$"
J_KurtsGranddaughterSlowpokeBackText::
	.string "The SLOWPOKE my\ndad gave me came\pback! Its TAIL is\ngrowing back too!$"
J_KurtsGranddaughterDadText::
	.string "Dad works at SILPH\nwhere he studies\lPOKé BALLS.\pI have to stay\nhome with Grandpa\land SLOWPOKE.$"
J_KurtsGranddaughterHelpText::
	.string "I get to help\nGrandpa now!\pWe'll make good\nBALLS for you, so\lplease wait!$"
J_KurtsGranddaughterFunText::
	.string "It's fun to make\nBALLS!$"
J_KurtsGranddaughterGSBallText::
	.string "Grandpa's checking\na BALL right now.\pSo I'm waiting\ntill he's done.$"
J_KurtsHouseSlowpokeText::
	.string "SLOWPOKE: …\nYawn?$"
J_KurtsHouseOakPhotoText::
	.string "…A young PROF.\nOAK?$"
J_KurtsHouseCelebiStatueText::
	.string "It's a statue of\nthe forest's pro-\ltector.$"
J_KurtsHouse_MapEvents::
