@ KJH: translated from pokecrystal maps/TinTower1F.asm by kjh_tools/johto

JohtoTinTower1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoTinTower1F_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, JohtoTinTower1F_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoTinTower1F_OnFrame
	.byte 0

JohtoTinTower1F_OnTransition:
	call J_TinTower1FNPCsCallback
	end

JohtoTinTower1F_OnLoad:
	call J_TinTower1FStairsCallback
	end

JohtoTinTower1F_OnFrame:
	map_script_2 VAR_J_SCENE_TIN_TOWER_1F, 0, J_SC_TinTower1FSuicuneBattleScene
	.2byte 0

J_W_TinTower1FEusine::
	lock
	call J_TinTower1FEusine
	release
	end

J_W_TinTower1FSage1Script::
	lock
	call J_TinTower1FSage1Script
	release
	end

J_W_TinTower1FSage2Script::
	lock
	call J_TinTower1FSage2Script
	release
	end

J_W_TinTower1FSage3Script::
	lock
	call J_TinTower1FSage3Script
	release
	end

J_W_TinTower1FSage4Script::
	lock
	call J_TinTower1FSage4Script
	release
	end

J_W_TinTower1FSage5Script::
	lock
	call J_TinTower1FSage5Script
	release
	end

J_W_TinTower1FSage6Script::
	lock
	call J_TinTower1FSage6Script
	release
	end

J_SC_TinTower1FSuicuneBattleScene::
	lockall
	call J_TinTower1FSuicuneBattleScene
	releaseall
	end

J_TinTower1F_MapScripts::
J_TinTower1FSuicuneBattleScene::
	call J_TinTower1FSuicuneBattleScript
	return
J_TinTower1FNoopScene::
	return
J_TinTower1FNPCsCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_RAINBOW_WING, J_L63
	setvar VAR_RESULT, 1
J_L63:
	goto_if_ne VAR_RESULT, 0, J_TinTower1FNPCsCallback_GotRainbowWing
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L64
	setvar VAR_RESULT, 1
J_L64:
	goto_if_eq VAR_RESULT, 0, J_TinTower1FNPCsCallback_FaceBeasts
	special KJH_BeastsCheck
	goto_if_eq VAR_RESULT, 0, J_TinTower1FNPCsCallback_FaceBeasts
	clearflag FLAG_J_TIN_TOWER_1F_WISE_TRIO_2
	setflag FLAG_J_TIN_TOWER_1F_WISE_TRIO_1
J_TinTower1FNPCsCallback_GotRainbowWing:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOUGHT_HO_OH, J_L65
	setvar VAR_RESULT, 1
J_L65:
	goto_if_eq VAR_RESULT, 0, J_TinTower1FNPCsCallback_Done
	clearflag FLAG_J_TIN_TOWER_1F_EUSINE
J_TinTower1FNPCsCallback_Done:
	return
J_TinTower1FNPCsCallback_FaceBeasts:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOUGHT_SUICUNE, J_L66
	setvar VAR_RESULT, 1
J_L66:
	goto_if_ne VAR_RESULT, 0, J_TinTower1FNPCsCallback_FoughtSuicune
	clearflag FLAG_J_TIN_TOWER_1F_SUICUNE
	setvar VAR_RESULT, 243
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TinTower1FNPCsCallback_NoRaikou
	clearflag FLAG_J_TIN_TOWER_1F_RAIKOU
	goto J_TinTower1FNPCsCallback_CheckEntei
J_TinTower1FNPCsCallback_NoRaikou:
	setflag FLAG_J_TIN_TOWER_1F_RAIKOU
J_TinTower1FNPCsCallback_CheckEntei:
	setvar VAR_RESULT, 244
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TinTower1FNPCsCallback_NoEntei
	clearflag FLAG_J_TIN_TOWER_1F_ENTEI
	goto J_TinTower1FNPCsCallback_BeastsDone
J_TinTower1FNPCsCallback_NoEntei:
	setflag FLAG_J_TIN_TOWER_1F_ENTEI
J_TinTower1FNPCsCallback_BeastsDone:
	return
J_TinTower1FNPCsCallback_FoughtSuicune:
	setflag FLAG_J_TIN_TOWER_1F_SUICUNE
	setflag FLAG_J_TIN_TOWER_1F_RAIKOU
	setflag FLAG_J_TIN_TOWER_1F_ENTEI
	clearflag FLAG_J_TIN_TOWER_1F_WISE_TRIO_1
	setflag FLAG_J_TIN_TOWER_1F_WISE_TRIO_2
	return
J_TinTower1FStairsCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_RAINBOW_WING, J_L67
	setvar VAR_RESULT, 1
J_L67:
	goto_if_ne VAR_RESULT, 0, J_TinTower1FStairsCallback_DontHideStairs
	setmetatile 10, 2, 2, FALSE
	setmetatile 11, 2, 2, FALSE
	setmetatile 10, 3, 2, FALSE
	setmetatile 11, 3, 2, FALSE
J_TinTower1FStairsCallback_DontHideStairs:
	return
J_TinTower1FSuicuneBattleScript::
	applymovement OBJ_EVENT_ID_PLAYER, J_TinTower1FPlayerEntersMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 15
	setvar VAR_RESULT, 243
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TinTower1FSuicuneBattleScript_Next1
	applymovement 2, J_TinTower1FRaikouApproachesMovement
	waitmovement 2
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playmoncry SPECIES_RAIKOU, CRY_MODE_NORMAL
	waitmoncry
	delay 10
	playse SE_WARP_OUT
	applymovement 2, J_TinTower1FRaikouLeavesMovement
	waitmovement 2
	@ KJH: object 2 stays (static legendary)
	playse SE_EXIT
	waitse
J_TinTower1FSuicuneBattleScript_Next1:
	setvar VAR_RESULT, 244
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TinTower1FSuicuneBattleScript_Next2
	applymovement 3, J_TinTower1FEnteiApproachesMovement
	waitmovement 3
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	playmoncry SPECIES_ENTEI, CRY_MODE_NORMAL
	waitmoncry
	delay 10
	playse SE_WARP_OUT
	applymovement 3, J_TinTower1FEnteiLeavesMovement
	waitmovement 3
	@ KJH: object 3 stays (static legendary)
	playse SE_EXIT
	waitse
J_TinTower1FSuicuneBattleScript_Next2:
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 10
	applymovement OBJ_EVENT_ID_PLAYER, J_TinTower1FPlayerBacksUpMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement 1, J_TinTower1FSuicuneApproachesMovement
	waitmovement 1
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	waitmoncry
	delay 20
	setwildbattle SPECIES_SUICUNE, 75
	kjh_legendaryboss @ KJH (CF-13)
	dowildbattle
	removeobject 1
	setflag FLAG_J_FOUGHT_SUICUNE
	setflag FLAG_J_SAW_SUICUNE_ON_ROUTE_42
	setvar VAR_J_SCENE_ROUTE_42, 0
	setflag FLAG_J_SAW_SUICUNE_ON_ROUTE_36
	setvar VAR_J_SCENE_ROUTE_36, 0
	setflag FLAG_J_SAW_SUICUNE_AT_CIANWOOD_CITY
	setvar VAR_J_SCENE_CIANWOOD_CITY, 0
	setvar VAR_J_SCENE_TIN_TOWER_1F, 1
	clearflag FLAG_J_SET_WHEN_FOUGHT_HO_OH
	delay 20
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	playbgm MUS_RG_ENCOUNTER_BOY, FALSE
	playse SE_DOOR
	setobjectxyperm 4, 10, 15
	addobject 4
	applymovement 4, J_TinTower1FEusineEntersMovement
	waitmovement 4
	playse SE_DOOR
	setobjectxyperm 5, 9, 15
	addobject 5
	applymovement 5, J_TinTower1FSage1EntersMovement
	waitmovement 5
	playse SE_DOOR
	setobjectxyperm 6, 9, 15
	addobject 6
	applymovement 6, J_TinTower1FSage2EntersMovement
	waitmovement 6
	playse SE_DOOR
	setobjectxyperm 7, 9, 15
	addobject 7
	applymovement 7, J_TinTower1FSage3EntersMovement
	waitmovement 7
	setobjectxyperm 5, 7, 13
	setobjectxyperm 6, 9, 13
	setobjectxyperm 7, 11, 13
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	message J_TinTower1FEusineSuicuneText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 4, J_TinTower1FEusineLeavesMovement
	waitmovement 4
	playse SE_EXIT
	removeobject 4
	waitse
	fadeoutbgm 0
	delay 20
	fadedefaultbgm
	return
J_TinTower1FSage1Script::
	faceplayer
	message J_TinTower1FSage1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TinTower1FSage2Script::
	faceplayer
	message J_TinTower1FSage2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TinTower1FSage3Script::
	faceplayer
	message J_TinTower1FSage3Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TinTower1FSage4Script::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOUGHT_HO_OH, J_L68
	setvar VAR_RESULT, 1
J_L68:
	goto_if_ne VAR_RESULT, 0, J_TinTower1FSage4Script_FoughtHoOh
	faceplayer
	message J_TinTower1FSage4Text1
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TinTower1FSage4Script_FoughtHoOh:
	faceplayer
	message J_TinTower1FSage4Text2
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TinTower1FSage5Script::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOUGHT_HO_OH, J_L69
	setvar VAR_RESULT, 1
J_L69:
	goto_if_ne VAR_RESULT, 0, J_TinTower1FSage5Script_FoughtHoOh
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_RAINBOW_WING, J_L70
	setvar VAR_RESULT, 1
J_L70:
	goto_if_ne VAR_RESULT, 0, J_TinTower1FSage5Script_GotRainbowWing
	message J_TinTower1FSage5Text1
	waitmessage
	waitbuttonpress
	bufferstring STR_VAR_2, J_ItemName_RAINBOW_WING
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message J_Text_ReceivedKeyItem
	waitmessage
	waitfanfare
	setflag FLAG_J_HAS_RAINBOW_WING
	setvar VAR_RESULT, 1
	closemessage
	special DrawWholeMapView
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 4
	special ShakeScreen
	delay 40
	waitse
	playse SE_M_STRENGTH
	setmetatile 10, 2, 5, FALSE
	setmetatile 11, 2, 2, FALSE
	setmetatile 10, 3, 2, FALSE
	setmetatile 11, 3, 2, FALSE
	special DrawWholeMapView
	setflag FLAG_J_GOT_RAINBOW_WING
	closemessage
J_TinTower1FSage5Script_GotRainbowWing:
	message J_TinTower1FSage5Text2
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TinTower1FSage5Script_FoughtHoOh:
	message J_TinTower1FSage5Text3
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TinTower1FSage6Script::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOUGHT_HO_OH, J_L71
	setvar VAR_RESULT, 1
J_L71:
	goto_if_ne VAR_RESULT, 0, J_TinTower1FSage6Script_FoughtHoOh
	faceplayer
	message J_TinTower1FSage6Text1
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TinTower1FSage6Script_FoughtHoOh:
	faceplayer
	message J_TinTower1FSage6Text2
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TinTower1FEusine::
	faceplayer
	message J_TinTower1FEusineHoOhText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TinTower1FPlayerEntersMovement::
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end
J_TinTower1FRaikouApproachesMovement::
	jump_down
	step_end
J_TinTower1FRaikouLeavesMovement::
	jump_down
	jump_right
	jump_down
	step_end
J_TinTower1FEnteiApproachesMovement::
	jump_down
	step_end
J_TinTower1FEnteiLeavesMovement::
	jump_down
	jump_left
	jump_down
	step_end
J_TinTower1FSuicuneApproachesMovement::
	jump_down
	step_end
J_TinTower1FPlayerBacksUpMovement::
	lock_facing_direction
	walk_fast_down
	unlock_facing_direction
	step_end
J_TinTower1FEusineEntersMovement::
	walk_up
	walk_up
	walk_up
	face_left
	step_end
J_TinTower1FEusineLeavesMovement::
	walk_down
	walk_down
	walk_down
	step_end
J_TinTower1FSage1EntersMovement::
	walk_up
	walk_up
	walk_left
	walk_left
	face_up
	step_end
J_TinTower1FSage2EntersMovement::
	walk_up
	walk_up
	step_end
J_TinTower1FSage3EntersMovement::
	walk_up
	walk_right
	walk_right
	walk_up
	step_end
J_TinTower1FEusineSuicuneText::
	.string "EUSINE: Awesome!\nToo awesome, even!\pI've never seen a\nbattle that great.\pThat was truly\ninspiring to see.\pSUICUNE was tough,\nbut you were even\pmore incredible,\n{PLAYER}.\pI heard SUICUNE's\nmystic power\psummons a rainbow-\ncolored POKéMON.\pMaybe, just maybe,\nwhat went on today\pwill cause that\nPOKéMON to appear.\pI'm going to study\nthe legends more.\pThanks for showing\nme that fantastic\lbattle.\pLater, {PLAYER}!$"
J_TinTower1FSage1Text::
	.string "According to\nlegend…\pWhen the souls of\nPOKéMON and humans\pcommune, from the\nheavens descends a\pPOKéMON of rainbow\ncolors…\pCould it mean the\nlegendary POKéMON\pare testing us\nhumans?$"
J_TinTower1FSage2Text::
	.string "When the BRASS\nTOWER burned down,\pthree nameless\nPOKéMON were said\pto have perished.\nIt was tragic.\pHowever…\pA rainbow-colored\nPOKéMON…\pIn other words…\pHO-OH descended\nfrom the sky and\pgave new life to\nthe three POKéMON.\pThey are…\pSUICUNE, ENTEI and\nRAIKOU.\pThat is what they\nsay.$"
J_TinTower1FSage3Text::
	.string "The two TOWERS are\nsaid to have been\pbuilt to foster\nfriendship and\phope between POKé-\nMON and people.\pThat was 700 years\nago, but the ideal\pstill remains\nimportant today.$"
J_TinTower1FSage4Text1::
	.string "HO-OH appears to\nhave descended\pupon this, the TIN\nTOWER!$"
J_TinTower1FSage5Text1::
	.string "This will protect\nyou. Take it.$"
J_TinTower1FSage5Text2::
	.string "Now, go.$"
J_TinTower1FSage6Text1::
	.string "I believe you are\nbeing tested.\pFree your mind\nfrom uncertainty,\land advance.$"
J_TinTower1FEusineHoOhText::
	.string "I knew it.\pI knew you'd get\nto see the POKéMON\pof rainbow colors,\n{PLAYER}.\pIt happened just\nas I envisioned.\pMy research isn't\nbad, I might say.\pI'm going to keep\nstudying POKéMON\pto become a famous\nPOKéMANIAC!$"
J_TinTower1FSage4Text2::
	.string "The legendary\nPOKéMON are said\pto embody three\npowers…\pThe lightning that\nstruck the TOWER.\pThe fire that\nburned the TOWER.\pAnd the rain that\nput out the fire…$"
J_TinTower1FSage5Text3::
	.string "When the legendary\nPOKéMON appeared…\pThey struck terror\nin those who saw\ltheir rise.\pAnd…\pSome even took to\nfutile attacks.\pThe legendary\nPOKéMON, knowing\ptheir own power,\nfled, ignoring the\lfrightened people.$"
J_TinTower1FSage6Text2::
	.string "Of the legendary\nPOKéMON, SUICUNE\pis said to be the\nclosest to HO-OH.\pI hear there may\nalso be a link to\pPOKéMON known as\nUNOWN.\pThe POKéMON UNOWN\nmust be sharing a\pcooperative bond\nwith SUICUNE.$"
J_TinTower1F_MapEvents::
