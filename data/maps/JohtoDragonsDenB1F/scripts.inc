@ KJH: translated from pokecrystal maps/DragonsDenB1F.asm by kjh_tools/johto

JohtoDragonsDenB1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoDragonsDenB1F_OnTransition
	.byte 0

JohtoDragonsDenB1F_OnTransition:
	call J_DragonsDenB1FCheckRivalCallback
	end

J_W_DragonsDenB1FDragonFangScript::
	lock
	call J_DragonsDenB1FDragonFangScript
	release
	end

J_W_DragonsDenB1FRivalScript::
	lock
	call J_DragonsDenB1FRivalScript
	release
	end

J_T_TrainerCooltrainermDarin::
	trainerbattle_single TRAINER_J_COOLTRAINERM_DARIN, J_CooltrainermDarinSeenText, J_CooltrainermDarinBeatenText
	call J_TrainerCooltrainermDarin_Script
	release
	end

J_T_TrainerCooltrainerfCara::
	trainerbattle_single TRAINER_J_COOLTRAINERF_CARA, J_CooltrainerfCaraSeenText, J_CooltrainerfCaraBeatenText
	call J_TrainerCooltrainerfCara_Script
	release
	end

J_T_TrainerTwinsLeaandpia1::
	trainerbattle_single TRAINER_J_TWINS_LEAANDPIA1, J_TwinsLeaandpia1SeenText, J_TwinsLeaandpia1BeatenText
	call J_TrainerTwinsLeaandpia1_Script
	release
	end

J_T_TrainerTwinsLeaandpia2::
	trainerbattle_single TRAINER_J_TWINS_LEAANDPIA1, J_TwinsLeaandpia2SeenText, J_TwinsLeaandpia2BeatenText
	call J_TrainerTwinsLeaandpia2_Script
	release
	end

J_C_DragonsDenB1F_ClairScene::
	lockall
	call J_DragonsDenB1F_ClairScene
	releaseall
	end

J_S_DragonShrineSignpost::
	lockall
	call J_DragonShrineSignpost
	releaseall
	end

J_DragonsDenB1F_MapScripts::
J_DragonsDenB1FNoop1Scene::
	return
J_DragonsDenB1FNoop2Scene::
	return
J_DragonsDenB1FCheckRivalCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_RIVAL_IN_MT_MOON, J_L244
	setvar VAR_RESULT, 1
J_L244:
	goto_if_ne VAR_RESULT, 0, J_DragonsDenB1FCheckRivalCallback_CheckDay
	setflag FLAG_J_RIVAL_DRAGONS_DEN
	return
J_DragonsDenB1FCheckRivalCallback_CheckDay:
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 2, J_DragonsDenB1FCheckRivalCallback_AppearRival
	goto_if_eq VAR_RESULT, 4, J_DragonsDenB1FCheckRivalCallback_AppearRival
	setflag FLAG_J_RIVAL_DRAGONS_DEN
	return
J_DragonsDenB1FCheckRivalCallback_AppearRival:
	clearflag FLAG_J_RIVAL_DRAGONS_DEN
	return
J_DragonsDenB1F_ClairScene::
	addobject 2
	message J_ClairText_Wait
	waitmessage
	delay 30
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playbgm MUS_RG_ENCOUNTER_GYM_LEADER, FALSE
	applymovement 2, J_MovementDragonsDen_ClairWalksToYou
	waitmovement 2
	message J_ClairText_GiveDragonbreathDragonDen
	waitmessage
	waitbuttonpress
	additem ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, 0, J_DragonsDenB1F_ClairScene_BagFull
	bufferitemname STR_VAR_1, ITEM_POTION
	message J_Text_ReceivedTM24
	waitmessage
	playse SE_SUCCESS
	waitse
	setflag FLAG_J_GOT_TM24_DRAGONBREATH
	message J_ClairText_DescribeDragonbreathDragonDen
	waitmessage
	waitbuttonpress
	message J_ClairText_WhatsTheMatterDragonDen
	waitmessage
	waitbuttonpress
	closemessage
	goto J_DragonsDenB1F_ClairScene_FinishClair
J_DragonsDenB1F_ClairScene_BagFull:
	message J_ClairText_NoRoom
	waitmessage
	waitbuttonpress
	closemessage
J_DragonsDenB1F_ClairScene_FinishClair:
	applymovement 2, J_MovementDragonsDen_ClairWalksAway
	waitmovement 2
	fadeoutbgm 0
	delay 30
	fadedefaultbgm
	removeobject 2
	setvar VAR_J_SCENE_DRAGONS_DEN_B1F, 0
	return
J_TrainerCooltrainermDarin::
J_TrainerCooltrainermDarin_Script:
	message J_CooltrainermDarinAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainerfCara::
J_TrainerCooltrainerfCara_Script:
	message J_CooltrainerfCaraAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerTwinsLeaandpia1::
J_TrainerTwinsLeaandpia1_Script:
	message J_TwinsLeaandpia1AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerTwinsLeaandpia2::
J_TrainerTwinsLeaandpia2_Script:
	message J_TwinsLeaandpia2AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DragonsDenB1FDragonFangScript::
	additem ITEM_DRAGON_FANG, 1
	goto_if_eq VAR_RESULT, 0, J_DragonsDenB1FDragonFangScript_BagFull
	removeobject 1
	bufferitemname STR_VAR_1, ITEM_POTION
	message J_Text_FoundDragonFang
	waitmessage
	playse SE_SUCCESS
	waitse
	closemessage
	return
J_DragonsDenB1FDragonFangScript_BagFull:
	bufferitemname STR_VAR_1, ITEM_POTION
	message J_Text_FoundDragonFang
	waitmessage
	waitbuttonpress
	message J_Text_NoRoomForDragonFang
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DragonsDenB1FRivalScript::
	playbgm MUS_RG_ENCOUNTER_RIVAL, FALSE
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L245
	setvar VAR_RESULT, 1
J_L245:
	goto_if_ne VAR_RESULT, 0, J_DragonsDenB1FRivalScript_RivalTalkAgain
	message J_RivalText_Training1
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1
	fadedefaultbgm
	return
J_DragonsDenB1FRivalScript_RivalTalkAgain:
	message J_RivalText_Training2
	waitmessage
	waitbuttonpress
	closemessage
	fadedefaultbgm
	return
J_DragonShrineSignpost::
	message J_DragonShrineSignpostText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DragonsDenB1FCalcium::
	finditem ITEM_CALCIUM, 1
	return
J_DragonsDenB1FMaxElixer::
	finditem ITEM_MAX_ELIXIR, 1
	return
J_DragonsDenB1FHiddenRevive::
	finditem ITEM_REVIVE
	return
J_DragonsDenB1FHiddenMaxPotion::
	finditem ITEM_MAX_POTION
	return
J_DragonsDenB1FHiddenMaxElixer::
	finditem ITEM_MAX_ELIXIR
	return
J_MovementDragonsDen_ClairWalksToYou::
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_slow_right
	step_end
J_MovementDragonsDen_ClairWalksAway::
	walk_slow_left
	walk_slow_left
	walk_slow_left
	walk_slow_left
	step_end
J_ClairText_Wait::
	.string "Wait!$"
J_ClairText_GiveDragonbreathDragonDen::
	.string "CLAIR: I'm sorry\nabout this.\pHere, take this as\nmy apology.$"
J_Text_ReceivedTM24::
	.string "{PLAYER} received\nTM24.$"
J_ClairText_DescribeDragonbreathDragonDen::
	.string "That contains\nDRAGONBREATH.\pNo, it doesn't\nhave anything to\ldo with my breath.\pIf you don't want\nit, you don't have\lto take it.$"
J_ClairText_NoRoom::
	.string "Oh? You don't have\nany room for this.\pI'm going back to\nthe GYM, so make\proom, then come\nsee me there.$"
J_ClairText_WhatsTheMatterDragonDen::
	.string "CLAIR: What's the\nmatter? Aren't you\pgoing on to the\nPOKéMON LEAGUE?\pDo you know how to\nget there?\pFrom here, go to\nNEW BARK TOWN.\pThen SURF east to\nPOKéMON LEAGUE.\pThe route there is\nvery tough.\pDon't you dare\nlose at the POKé-\lMON LEAGUE!\pIf you do, I'll\nfeel even worse\pabout having lost\nto you!\pGive it everything\nyou've got.$"
J_DragonShrineSignpostText::
	.string "DRAGON SHRINE\pA shrine honoring\nthe dragon POKéMON\psaid to have lived\nin DRAGON'S DEN.$"
J_RivalText_Training1::
	.string "…\nWhat? {PLAYER}?\p…No, I won't\nbattle you now…\pMy POKéMON aren't\nready to beat you.\pI can't push them\ntoo hard now.\pI have to be dis-\nciplined to become\pthe greatest POKé-\nMON trainer…$"
J_RivalText_Training2::
	.string "…\pWhew…\pLearn to stay out\nof my way…$"
J_CooltrainermDarinSeenText::
	.string "You! How dare you\nenter uninvited!$"
J_CooltrainermDarinBeatenText::
	.string "S-strong!$"
J_CooltrainermDarinAfterBattleText::
	.string "The SHRINE ahead\nis home to the\pMASTER of our\ndragon-user clan.\pYou're not allowed\nto just go in!$"
J_CooltrainerfCaraSeenText::
	.string "You shouldn't be\nin here!$"
J_CooltrainerfCaraBeatenText::
	.string "Oh yikes, I lost!$"
J_CooltrainerfCaraAfterBattleText::
	.string "Soon I'm going to\nget permission\pfrom our MASTER to\nuse dragons.\pWhen I do, I'm\ngoing to become an\padmirable dragon\ntrainer and gain\pour MASTER's\napproval.$"
J_TwinsLeaandpia1SeenText::
	.string "It's a stranger we\ndon't know.$"
J_TwinsLeaandpia1BeatenText::
	.string "Ouchies.$"
J_TwinsLeaandpia1AfterBattleText::
	.string "It was like having\nto battle LANCE.$"
J_TwinsLeaandpia2SeenText::
	.string "Who are you?$"
J_TwinsLeaandpia2BeatenText::
	.string "Meanie.$"
J_TwinsLeaandpia2AfterBattleText::
	.string "We'll tell on you.\pMASTER will be\nangry with you.$"
J_Text_FoundDragonFang::
	.string "{PLAYER} found\n{STR_VAR_1}!$"
J_Text_NoRoomForDragonFang::
	.string "But {PLAYER} can't\ncarry any more\litems.$"
J_DragonsDenB1F_MapEvents::
