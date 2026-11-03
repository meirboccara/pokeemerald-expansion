@ KJH: translated from pokecrystal maps/EcruteakTinTowerEntrance.asm by kjh_tools/johto

JohtoEcruteakTinTowerEntrance_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoEcruteakTinTowerEntrance_OnTransition
	.byte 0

JohtoEcruteakTinTowerEntrance_OnTransition:
	call J_EcruteakTinTowerEntranceInitializeSagesCallback
	end

J_W_EcruteakTinTowerEntranceSageScript::
	lock
	call J_EcruteakTinTowerEntranceSageScript
	release
	end

J_W_EcruteakTinTowerEntranceWanderingSageScript::
	lock
	call J_EcruteakTinTowerEntranceWanderingSageScript
	release
	end

J_W_EcruteakTinTowerEntranceGrampsScript::
	lock
	call J_EcruteakTinTowerEntranceGrampsScript
	release
	end

J_C_EcruteakTinTowerEntranceSageBlocksLeft::
	lockall
	call J_EcruteakTinTowerEntranceSageBlocksLeft
	releaseall
	end

J_C_EcruteakTinTowerEntranceSageBlocksRight::
	lockall
	call J_EcruteakTinTowerEntranceSageBlocksRight
	releaseall
	end

J_EcruteakTinTowerEntrance_MapScripts::
J_EcruteakTinTowerEntranceNoop1Scene::
	return
J_EcruteakTinTowerEntranceNoop2Scene::
	return
J_EcruteakTinTowerEntranceInitializeSagesCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOUGHT_SUICUNE, J_L261
	setvar VAR_RESULT, 1
J_L261:
	goto_if_ne VAR_RESULT, 0, J_EcruteakTinTowerEntranceInitializeSagesCallback_DontBlockTower
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_KOJI_ALLOWS_YOU_PASSAGE_TO_TIN_TOWER, J_L262
	setvar VAR_RESULT, 1
J_L262:
	goto_if_ne VAR_RESULT, 0, J_EcruteakTinTowerEntranceInitializeSagesCallback_DontBlockTower
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L263
	setvar VAR_RESULT, 1
J_L263:
	goto_if_ne VAR_RESULT, 0, J_EcruteakTinTowerEntranceInitializeSagesCallback_BlockTower
	return
J_EcruteakTinTowerEntranceInitializeSagesCallback_BlockTower:
	clearflag FLAG_J_RANG_CLEAR_BELL_1
	setflag FLAG_J_RANG_CLEAR_BELL_2
	setflag FLAG_J_ECRUTEAK_TIN_TOWER_ENTRANCE_WANDERING_SAGE
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_CLEAR_BELL, J_L264
	setvar VAR_RESULT, 1
J_L264:
	goto_if_ne VAR_RESULT, 0, J_EcruteakTinTowerEntranceInitializeSagesCallback_NoClearBell
	setvar VAR_J_SCENE_ECRUTEAK_TIN_TOWER_ENTRANCE, 0
J_EcruteakTinTowerEntranceInitializeSagesCallback_NoClearBell:
	return
J_EcruteakTinTowerEntranceInitializeSagesCallback_DontBlockTower:
	clearflag FLAG_J_ECRUTEAK_TIN_TOWER_ENTRANCE_WANDERING_SAGE
	return
J_EcruteakTinTowerEntranceSageBlocksLeft::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RANG_CLEAR_BELL_2, J_L265
	setvar VAR_RESULT, 1
J_L265:
	goto_if_ne VAR_RESULT, 0, J_EcruteakTinTowerEntranceAlreadyBlocked
	applymovement 2, J_EcruteakTinTowerEntranceSageBlocksLeftMovement
	waitmovement 2
	setobjectxyperm 1, 4, 6
	addobject 1
	delay 5
	removeobject 2
	return
J_EcruteakTinTowerEntranceSageBlocksRight::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RANG_CLEAR_BELL_1, J_L266
	setvar VAR_RESULT, 1
J_L266:
	goto_if_ne VAR_RESULT, 0, J_EcruteakTinTowerEntranceAlreadyBlocked
	applymovement 1, J_EcruteakTinTowerEntranceSageBlocksRightMovement
	waitmovement 1
	setobjectxyperm 2, 5, 6
	addobject 2
	delay 5
	removeobject 1
	return
J_EcruteakTinTowerEntranceAlreadyBlocked::
	return
J_EcruteakTinTowerEntranceSageScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L267
	setvar VAR_RESULT, 1
J_L267:
	goto_if_ne VAR_RESULT, 0, J_EcruteakTinTowerEntranceSageScript_CheckForClearBell
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE04_GET, J_L268
	setvar VAR_RESULT, 1
J_L268:
	goto_if_ne VAR_RESULT, 0, J_EcruteakTinTowerEntranceSageScript_BlockPassage_GotFogBadge
	message J_EcruteakTinTowerEntranceSageText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakTinTowerEntranceSageScript_BlockPassage_GotFogBadge:
	message J_EcruteakTinTowerEntranceSageText_GotFogBadge
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakTinTowerEntranceSageScript_CheckForClearBell:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_KOJI_ALLOWS_YOU_PASSAGE_TO_TIN_TOWER, J_L269
	setvar VAR_RESULT, 1
J_L269:
	goto_if_ne VAR_RESULT, 0, J_EcruteakTinTowerEntranceSageScript_AllowedThrough
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L270
	setvar VAR_RESULT, 1
J_L270:
	goto_if_ne VAR_RESULT, 0, J_EcruteakTinTowerEntranceSageScript_RangClearBell
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_CLEAR_BELL, J_L271
	setvar VAR_RESULT, 1
J_L271:
	goto_if_ne VAR_RESULT, 0, J_EcruteakTinTowerEntranceSageScript_GotClearBell
	message J_EcruteakTinTowerEntranceSageText_NoClearBell
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakTinTowerEntranceSageScript_GotClearBell:
	message J_EcruteakTinTowerEntranceSageText_HearsClearBell
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_J_SCENE_ECRUTEAK_TIN_TOWER_ENTRANCE, 1
	setflag FLAG_J_RANG_CLEAR_BELL_2
	clearflag FLAG_J_RANG_CLEAR_BELL_1
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1
	return
J_EcruteakTinTowerEntranceSageScript_AllowedThrough:
	message J_EcruteakTinTowerEntranceSageText_PleaseDoGoOn
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakTinTowerEntranceSageScript_RangClearBell:
	message J_EcruteakTinTowerEntranceSageText_HeardClearBell
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakTinTowerEntranceWanderingSageScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_CLEAR_BELL, J_L272
	setvar VAR_RESULT, 1
J_L272:
	goto_if_ne VAR_RESULT, 0, J_EcruteakTinTowerEntranceWanderingSageScript_GotClearBell
	message J_EcruteakTinTowerEntranceWanderingSageText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakTinTowerEntranceWanderingSageScript_GotClearBell:
	message J_EcruteakTinTowerEntranceWanderingSageText_GotClearBell
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakTinTowerEntranceGrampsScript::
	faceplayer
	message J_EcruteakTinTowerEntranceGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakTinTowerEntranceSageBlocksLeftMovement::
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	face_down
	step_end
J_EcruteakTinTowerEntranceSageBlocksRightMovement::
	lock_facing_direction
	walk_fast_right
	unlock_facing_direction
	face_down
	step_end
J_EcruteakTinTowerEntranceSageText::
	.string "TIN TOWER is off\nlimits to anyone\pwithout ECRUTEAK\nGYM's BADGE.\pSorry, but you'll\nhave to leave.$"
J_EcruteakTinTowerEntranceSageText_GotFogBadge::
	.string "TIN TOWER is off\nlimits to anyone\pwithout ECRUTEAK\nGYM's BADGE.\pAh!\pECRUTEAK's GYM\nBADGE! Please, go\lright through.$"
J_EcruteakTinTowerEntranceSageText_NoClearBell::
	.string "A momentous event\nhas occurred.\pI beg your pardon,\nbut I must ask you\lto leave.\p…What soothes the\nsoul…\pThe WISE TRIO say\nthings that are so\pvery difficult to\nunderstand…$"
J_EcruteakTinTowerEntranceSageText_HearsClearBell::
	.string "A momentous event\nhas occurred.\pI beg your pardon,\nbut I must ask you\lto leave.\p………………\pAh!\pThe sound of that\nCLEAR BELL!\pIt… It's sublime!\pI've never heard\nso beautiful a\lsound before!\pThat bell's chime\nis indicative of\lthe bearer's soul.\pYou…\pYou may be able to\nmake it through\lTIN TOWER.\pPlease, do go on.$"
J_EcruteakTinTowerEntranceSageText_PleaseDoGoOn::
	.string "Please, do go on.$"
J_EcruteakTinTowerEntranceSageText_HeardClearBell::
	.string "That bell's chime\nis indicative of\lthe bearer's soul.\pYou…\pYou may be able to\nmake it through\lTIN TOWER.\pPlease, do go on.$"
J_EcruteakTinTowerEntranceWanderingSageText::
	.string "The TIN TOWER\nahead is a nine-\ptier tower of\ndivine beauty.\pIt soothes the\nsoul of all who\lsee it.$"
J_EcruteakTinTowerEntranceWanderingSageText_GotClearBell::
	.string "The TIN TOWER\nshook! A POKéMON\pmust have returned\nto the top!$"
J_EcruteakTinTowerEntranceGrampsText::
	.string "Two towers…\nTwo POKéMON…\pBut when one\nburned down, both\pPOKéMON flew away,\nnever to return.$"
J_EcruteakTinTowerEntrance_MapEvents::
