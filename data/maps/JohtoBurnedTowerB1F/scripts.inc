@ KJH: translated from pokecrystal maps/BurnedTowerB1F.asm by kjh_tools/johto

JohtoBurnedTowerB1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, JohtoBurnedTowerB1F_OnLoad
	.byte 0

JohtoBurnedTowerB1F_OnLoad:
	call J_BurnedTowerB1FLadderCallback
	end

J_W_BurnedTowerB1FBoulder::
	lock
	call J_BurnedTowerB1FBoulder
	release
	end

J_W_BurnedTowerB1FEusine::
	lock
	call J_BurnedTowerB1FEusine
	release
	end

J_C_ReleaseTheBeasts::
	lockall
	call J_ReleaseTheBeasts
	releaseall
	end

J_BurnedTowerB1F_MapScripts::
J_BurnedTowerB1FNoop1Scene::
	return
J_BurnedTowerB1FNoop2Scene::
	return
J_BurnedTowerB1FLadderCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RELEASED_THE_BEASTS, J_L76
	setvar VAR_RESULT, 1
J_L76:
	goto_if_ne VAR_RESULT, 0, J_BurnedTowerB1FLadderCallback_HideLadder
	setmetatile 6, 14, 10, FALSE
	setmetatile 7, 14, 10, FALSE
	setmetatile 6, 15, 10, FALSE
	setmetatile 7, 15, 10, FALSE
J_BurnedTowerB1FLadderCallback_HideLadder:
	return
J_ReleaseTheBeasts::
	playbgm MUS_NONE, FALSE
	delay 30
	addobject 2
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 5
	removeobject 5
	delay 15
	playmoncry SPECIES_RAIKOU, CRY_MODE_NORMAL
	waitmoncry
	addobject 3
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 5
	removeobject 6
	delay 15
	playmoncry SPECIES_ENTEI, CRY_MODE_NORMAL
	waitmoncry
	addobject 4
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 5
	removeobject 7
	delay 15
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	waitmoncry
	delay 15
	playse SE_WARP_OUT
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement 2, J_BurnedTowerRaikouMovement
	waitmovement 2
	removeobject 2
	waitse
	playse SE_WARP_OUT
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement 3, J_BurnedTowerEnteiMovement
	waitmovement 3
	removeobject 3
	waitse
	delay 15
	playse SE_WARP_OUT
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	applymovement 4, J_BurnedTowerSuicuneMovement1
	waitmovement 4
	playse SE_WARP_OUT
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement 4, J_BurnedTowerSuicuneMovement2
	waitmovement 4
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 20
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	waitmoncry
	delay 30
	playse SE_WARP_OUT
	applymovement 4, J_BurnedTowerSuicuneMovement3
	waitmovement 4
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	removeobject 4
	waitse
	fadedefaultbgm
	setvar VAR_J_SCENE_BURNED_TOWER_B1F, 1
	setflag FLAG_J_RELEASED_THE_BEASTS
	setvar VAR_J_SCENE_ECRUTEAK_GYM, 1
	setvar VAR_J_SCENE_CIANWOOD_CITY, 1
	clearflag FLAG_J_SAW_SUICUNE_AT_CIANWOOD_CITY
	setflag FLAG_J_ECRUTEAK_GYM_GRAMPS
	clearflag FLAG_J_ECRUTEAK_CITY_GRAMPS
	setflag FLAG_J_BURNED_TOWER_MORTY
	setflag FLAG_J_BURNED_TOWER_1F_EUSINE
	addobject 9
	special DrawWholeMapView
	setmetatile 6, 14, 10, FALSE
	setmetatile 7, 14, 10, FALSE
	setmetatile 6, 15, 10, FALSE
	setmetatile 7, 15, 18, FALSE
	special DrawWholeMapView
	closemessage
	setvar VAR_J_SCENE_BURNED_TOWER_B1F, 1
	return
J_BurnedTowerB1FEusine::
	faceplayer
	message J_BurnedTowerB1FEusineText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 1, J_BurnedTowerB1FEusine_Movement2
	applymovement 9, J_BurnedTowerB1FEusineMovement1
	waitmovement 9
	goto J_BurnedTowerB1FEusine_Finish
J_BurnedTowerB1FEusine_Movement2:
	applymovement 9, J_BurnedTowerB1FEusineMovement2
	waitmovement 9
J_BurnedTowerB1FEusine_Finish:
	removeobject 9
	playse SE_EXIT
	waitse
	return
J_BurnedTowerB1FTMEndure::
	finditem ITEM_RARE_CANDY, 1
	return
J_BurnedTowerB1FBoulder::
	goto EventScript_StrengthBoulder
J_BurnedTowerRaikouMovement::
	jump_down
	jump_left
	step_end
J_BurnedTowerEnteiMovement::
	jump_right
	jump_down
	jump_right
	step_end
J_BurnedTowerSuicuneMovement1::
	jump_right
	jump_down
	jump_down
	jump_left
	step_end
J_BurnedTowerSuicuneMovement2::
	jump_left
	jump_up
	walk_fast_up
	jump_right
	step_end
J_BurnedTowerUnusedMovement::
	walk_fast_down
	step_end
J_BurnedTowerSuicuneMovement3::
	walk_fast_up
	jump_right
	jump_down
	jump_down
	jump_down
	jump_down
	step_end
J_BurnedTowerB1FEusineMovement2::
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_down
	step_end
J_BurnedTowerB1FEusineMovement1::
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end
J_BurnedTowerB1FEusineText::
	.string "EUSINE: I dug a\nhole here, too…\pI was shocked!\pSUICUNE raced by\nlike a blur, right\pin front of my\neyes!\pFor ten years I\nchased SUICUNE,\pand I finally got\nto see it.\pI'm all choked up!\p{PLAYER}, I owe\nthis all to you!\pThank you!\pI heard that the\nlegendary POKéMON\pof ECRUTEAK test\nchosen humans by\pallowing them to\nget close.\pI'm going to track\nSUICUNE.\p{PLAYER}, let's\nmeet again!\pFarewell!$"
J_BurnedTowerB1F_MapEvents::
