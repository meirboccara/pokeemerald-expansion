@ KJH: translated from pokecrystal maps/MahoganyTown.asm by kjh_tools/johto

JohtoMahoganyTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoMahoganyTown_OnTransition
	.byte 0

JohtoMahoganyTown_OnTransition:
	call J_MahoganyTownFlypointCallback
	end

J_W_MahoganyTownPokefanMScript::
	lock
	call J_MahoganyTownPokefanMScript
	release
	end

J_W_MahoganyTownGrampsScript::
	lock
	call J_MahoganyTownGrampsScript
	release
	end

J_W_MahoganyTownFisherScript::
	lock
	call J_MahoganyTownFisherScript
	release
	end

J_W_MahoganyTownLassScript::
	lock
	call J_MahoganyTownLassScript
	release
	end

J_C_MahoganyTownTryARageCandyBarScript::
	lockall
	call J_MahoganyTownTryARageCandyBarScript
	releaseall
	end

J_S_MahoganyTownSign::
	lockall
	call J_MahoganyTownSign
	releaseall
	end

J_S_MahoganyTownRagecandybarSign::
	lockall
	call J_MahoganyTownRagecandybarSign
	releaseall
	end

J_S_MahoganyGymSign::
	lockall
	call J_MahoganyGymSign
	releaseall
	end

J_S_MahoganyTownPokecenterSign::
	lockall
	call J_MahoganyTownPokecenterSign
	releaseall
	end

J_MahoganyTown_MapScripts::
J_MahoganyTownNoop1Scene::
	return
J_MahoganyTownNoop2Scene::
	return
J_MahoganyTownFlypointCallback::
	setflag FLAG_J_ENGINE_FLYPOINT_MAHOGANY
	return
J_MahoganyTownTryARageCandyBarScript::
	applymovement 1, J_Movement_Exclamation
	waitmovement 0
	applymovement 1, J_MahoganyTownRageCandyBarMerchantBlocksYouMovement
	waitmovement 1
	applymovement OBJ_EVENT_ID_PLAYER, J_MahoganyTownPlayerStepLeftMovement
	applymovement 1, J_MahoganyTownPlayerStepLeftMovement
	waitmovement 1
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	call J_RageCandyBarMerchantScript
	applymovement 1, J_MahoganyTownRageCandyBarMerchantReturnsMovement
	waitmovement 1
	return
J_MahoganyTownPokefanMScript::
	faceplayer
J_RageCandyBarMerchantScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_ROCKET_HIDEOUT, J_L58
	setvar VAR_RESULT, 1
J_L58:
	goto_if_ne VAR_RESULT, 0, J_RageCandyBarMerchantScript_ClearedRocketHideout
	call J_RageCandyBarMerchantScript_SellRageCandyBars
	return
J_RageCandyBarMerchantScript_ClearedRocketHideout:
	message J_RageCandyBarMerchantSoldOutText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RageCandyBarMerchantScript_SellRageCandyBars:
	message J_RageCandyBarMerchantTryOneText
	waitmessage
	showmoneybox 0, 0
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_RageCandyBarMerchantScript_Refused
	checkmoney 0
	goto_if_eq VAR_RESULT, TRUE, J_L59
	setvar VAR_RESULT, 2
	goto J_L60
J_L59:
	setvar VAR_RESULT, 0
J_L60:
	goto_if_eq VAR_RESULT, 2, J_RageCandyBarMerchantScript_NotEnoughMoney
	additem ITEM_LAVA_COOKIE, 1
	goto_if_eq VAR_RESULT, 0, J_RageCandyBarMerchantScript_NoRoom
	waitse
	playse SE_SHOP
	removemoney 0
	showmoneybox 0, 0
	message J_RageCandyBarMerchantSavorItText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RageCandyBarMerchantScript_NotEnoughMoney:
	message J_RageCandyBarMerchantNotEnoughMoneyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RageCandyBarMerchantScript_Refused:
	message J_RageCandyBarMerchantRefusedText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RageCandyBarMerchantScript_NoRoom:
	message J_RageCandyBarMerchantNoRoomText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyTownGrampsScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_ROCKET_HIDEOUT, J_L61
	setvar VAR_RESULT, 1
J_L61:
	goto_if_ne VAR_RESULT, 0, J_MahoganyTownGrampsScript_ClearedRocketHideout
	message J_MahoganyTownGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyTownGrampsScript_ClearedRocketHideout:
	message J_MahoganyTownGrampsText_ClearedRocketHideout
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyTownFisherScript::
	faceplayer
	message J_MahoganyTownFisherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyTownLassScript::
	faceplayer
	message J_MahoganyTownLassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyTownSign::
	message J_MahoganyTownSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyTownRagecandybarSign::
	message J_MahoganyTownRagecandybarSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyGymSign::
	message J_MahoganyGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyTownPokecenterSign::
	goto J_PokecenterSignScript
J_MahoganyTownMartSign::
	goto J_MartSignScript
J_MahoganyTownPlayerStepLeftMovement::
	walk_left
	step_end
J_MahoganyTownRageCandyBarMerchantBlocksYouMovement::
	walk_right
	walk_down
	face_left
	step_end
J_MahoganyTownRageCandyBarMerchantReturnsMovement::
	walk_up
	face_down
	step_end
J_RageCandyBarMerchantTryOneText::
	.string "Hiya, kid!\pI see you're new\nin MAHOGANY TOWN.\pSince you're new,\nyou should try a\pyummy RAGECANDY-\nBAR!\pRight now, it can\nbe yours for just\l¥0! Want one?$"
J_RageCandyBarMerchantSavorItText::
	.string "Good! Savor it!$"
J_RageCandyBarMerchantNotEnoughMoneyText::
	.string "You don't have\nenough money.$"
J_RageCandyBarMerchantRefusedText::
	.string "Oh, fine then…$"
J_RageCandyBarMerchantNoRoomText::
	.string "You don't have\nroom for this.$"
J_RageCandyBarMerchantSoldOutText::
	.string "RAGECANDYBAR's\nsold out.\pI'm packing up.\nDon't bother me,\lkiddo.$"
J_MahoganyTownGrampsText::
	.string "Are you off to see\nthe GYARADOS ram-\lpage at the LAKE?$"
J_MahoganyTownGrampsText_ClearedRocketHideout::
	.string "MAGIKARP have\nreturned to LAKE\lOF RAGE.\pThat should be\ngood news for the\langlers there.$"
J_MahoganyTownFisherText::
	.string "Since you came\nthis far, take the\ptime to do some\nsightseeing.\pYou should head\nnorth and check\pout LAKE OF RAGE\nright now.$"
J_MahoganyTownLassText::
	.string "Visit Grandma's\nshop. She sells\pstuff that nobody\nelse has.$"
J_MahoganyTownSignText::
	.string "MAHOGANY TOWN\pWelcome to the\nHome of the Ninja$"
J_MahoganyTownRagecandybarSignText::
	.string "While visiting\nMAHOGANY TOWN, try\la RAGECANDYBAR!$"
J_MahoganyGymSignText::
	.string "MAHOGANY TOWN\nPOKéMON GYM\lLEADER: PRYCE\pThe Teacher of\nWinter's Harshness$"
J_MahoganyTown_MapEvents::
