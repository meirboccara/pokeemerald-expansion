@ KJH: translated from pokecrystal maps/BurnedTower1F.asm by kjh_tools/johto

JohtoBurnedTower1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, JohtoBurnedTower1F_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoBurnedTower1F_OnFrame
	.byte 0

JohtoBurnedTower1F_OnLoad:
	call J_BurnedTower1FHoleAndLadderCallback
	end

JohtoBurnedTower1F_OnFrame:
	map_script_2 VAR_J_SCENE_BURNED_TOWER_1F, 0, J_SC_BurnedTower1FMeetEusineScene
	.2byte 0

J_W_BurnedTower1FRock::
	lock
	call J_BurnedTower1FRock
	release
	end

J_W_BurnedTower1FEusineScript::
	lock
	call J_BurnedTower1FEusineScript
	release
	end

J_W_BurnedTower1FMortyScript::
	lock
	call J_BurnedTower1FMortyScript
	release
	end

J_C_BurnedTowerRivalBattleScript::
	lockall
	call J_BurnedTowerRivalBattleScript
	releaseall
	end

J_SC_BurnedTower1FMeetEusineScene::
	lockall
	call J_BurnedTower1FMeetEusineScene
	releaseall
	end

J_BurnedTower1F_MapScripts::
J_BurnedTower1FMeetEusineScene::
	call J_BurnedTower1FMeetEusineScript
	return
J_BurnedTower1FNoop1Scene::
	return
J_BurnedTower1FNoop2Scene::
	return
J_BurnedTower1FHoleAndLadderCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HOLE_IN_BURNED_TOWER, J_L72
	setvar VAR_RESULT, 1
J_L72:
	goto_if_ne VAR_RESULT, 0, J_BurnedTower1FHoleAndLadderCallback_KeepHoleOpen
	setmetatile 10, 8, 40, TRUE
	setmetatile 11, 8, 40, TRUE
	setmetatile 10, 9, 2, FALSE
	setmetatile 11, 9, 2, FALSE
J_BurnedTower1FHoleAndLadderCallback_KeepHoleOpen:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RELEASED_THE_BEASTS, J_L73
	setvar VAR_RESULT, 1
J_L73:
	goto_if_ne VAR_RESULT, 0, J_BurnedTower1FHoleAndLadderCallback_HideBasement
	setmetatile 6, 14, 2, FALSE
	setmetatile 7, 14, 2, FALSE
	setmetatile 6, 15, 2, FALSE
	setmetatile 7, 15, 2, FALSE
J_BurnedTower1FHoleAndLadderCallback_HideBasement:
	return
J_BurnedTower1FMeetEusineScript::
	turnobject 2, DIR_SOUTH
	applymovement 2, J_Movement_Exclamation
	waitmovement 0
	applymovement 2, J_BurnedTower1FEusineMovement
	waitmovement 2
	message J_BurnedTower1FEusineIntroText
	waitmessage
	waitbuttonpress
	closemessage
	setobjectxyperm 2, 9, 14
	setvar VAR_J_SCENE_BURNED_TOWER_1F, 1
	return
J_BurnedTowerRivalBattleScript::
	applymovement 3, J_Movement_Exclamation
	waitmovement 0
	fadeoutbgm 0
	delay 15
	turnobject 3, DIR_EAST
	delay 15
	applymovement OBJ_EVENT_ID_PLAYER, J_BurnedTowerMovement_PlayerWalksToRival
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 3, J_BurnedTowerMovement_RivalWalksToPlayer
	waitmovement 3
	playbgm MUS_RG_ENCOUNTER_RIVAL, FALSE
	message J_BurnedTowerRival_BeforeText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TOTODILE_FROM_ELM, J_L74
	setvar VAR_RESULT, 1
J_L74:
	goto_if_ne VAR_RESULT, 0, J_BurnedTowerRivalBattleScript_totodile
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_CHIKORITA_FROM_ELM, J_L75
	setvar VAR_RESULT, 1
J_L75:
	goto_if_ne VAR_RESULT, 0, J_BurnedTowerRivalBattleScript_chikorita
	setvar VAR_LAST_TALKED, 3
	trainerbattle_no_intro TRAINER_J_RIVAL1_RIVAL1_3_TOTODILE, J_BurnedTowerRival_WinText
	goto J_BurnedTowerRivalBattleScript_returnfrombattle
J_BurnedTowerRivalBattleScript_totodile:
	setvar VAR_LAST_TALKED, 3
	trainerbattle_no_intro TRAINER_J_RIVAL1_RIVAL1_3_CHIKORITA, J_BurnedTowerRival_WinText
	goto J_BurnedTowerRivalBattleScript_returnfrombattle
J_BurnedTowerRivalBattleScript_chikorita:
	setvar VAR_LAST_TALKED, 3
	trainerbattle_no_intro TRAINER_J_RIVAL1_RIVAL1_3_CYNDAQUIL, J_BurnedTowerRival_WinText
	goto J_BurnedTowerRivalBattleScript_returnfrombattle
J_BurnedTowerRivalBattleScript_returnfrombattle:
	playbgm MUS_RG_RIVAL_EXIT, FALSE
	message J_BurnedTowerRival_AfterText1
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_J_SCENE_BURNED_TOWER_1F, 2
	setflag FLAG_J_RIVAL_BURNED_TOWER
	fadeoutbgm 0
	delay 15
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 4
	special ShakeScreen
	delay 40
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playse SE_DOOR
	waitse
	setmetatile 10, 8, 40, TRUE
	setmetatile 11, 8, 40, TRUE
	setmetatile 10, 9, 41, FALSE
	setmetatile 11, 9, 2, FALSE
	special DrawWholeMapView
	delay 15
	applymovement OBJ_EVENT_ID_PLAYER, J_BurnedTower1FMovement_PlayerStartsToFall
	waitmovement OBJ_EVENT_ID_PLAYER
	playse SE_M_TELEPORT
	applymovement 3, J_Movement_Exclamation
	waitmovement 0
	message J_BurnedTowerRival_AfterText2
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_HOLE_IN_BURNED_TOWER
	delay 15
	return
J_BurnedTower1FEusineScript::
	faceplayer
	message J_BurnedTower1FEusineText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BurnedTower1FMortyScript::
	faceplayer
	message J_BurnedTower1FMortyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BurnedTower1FRock::
	goto EventScript_RockSmash
J_BurnedTower1FHiddenEther::
	finditem ITEM_ETHER
	return
J_BurnedTower1FHiddenUltraBall::
	finditem ITEM_ULTRA_BALL
	return
J_BurnedTower1FHPUp::
	finditem ITEM_HP_UP, 1
	return
J_BurnedTowerMovement_PlayerWalksToRival::
	walk_left
	step_end
J_BurnedTowerMovement_RivalWalksToPlayer::
	walk_right
	step_end
J_BurnedTower1FMovement_PlayerStartsToFall::
	step_end
J_BurnedTower1FEusineMovement::
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end
J_BurnedTowerRival_BeforeText::
	.string "…… …… ……\p…Oh, it's you.\pI came looking for\nsome legendary\pPOKéMON that they\nsay roosts here.\pBut there's\nnothing here!\pNothing after all\nthe trouble of\pcoming to this\ndump? No way!\pIt's all your\nfault!$"
J_BurnedTowerRival_WinText::
	.string "…Humph!\pThis is why I hate\nbattling wimps.\pThere's no\nchallenge in it.$"
J_BurnedTowerRival_AfterText1::
	.string "…Aw, whatever.\pYou would never be\nable to catch a\plegendary POKéMON\nanyway.$"
J_BurnedTowerRival_LossText::
	.string "…Humph!\pThis is why I hate\nbattling wimps.\pIt's just a waste\nof my time.$"
J_BurnedTowerRival_AfterText2::
	.string "Humph!\pWhat are you doing\nfalling into a\phole? Some genius\nyou are!\pServes you right!$"
J_BurnedTower1FEusineIntroText::
	.string "EUSINE: My name's\nEUSINE.\pI'm on the trail\nof a POKéMON named\lSUICUNE.\pAnd you are…?\p{PLAYER}? Glad to\nmeet you!\pI heard rumors\nthat SUICUNE is in\pthis BURNED TOWER,\nso I came to look.\pBut where exactly\ncould it be?$"
J_BurnedTower1FEusineText::
	.string "EUSINE: I heard\nthat SUICUNE is in\pthis BURNED TOWER,\nso I came to look.\pBut where exactly\ncould it be?$"
J_BurnedTower1FMortyText::
	.string "MORTY: ECRUTEAK's\nGYM LEADER has to\pstudy what are\nsaid to be the\plegendary POKéMON\n--SUICUNE, ENTEI\land RAIKOU.\pEUSINE is here, so\nI've decided to\pinvestigate the\nTOWER with him.$"
J_BurnedTower1F_MapEvents::
