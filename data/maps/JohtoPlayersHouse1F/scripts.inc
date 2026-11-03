@ KJH: translated from pokecrystal maps/PlayersHouse1F.asm by kjh_tools/johto

JohtoPlayersHouse1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoPlayersHouse1F_OnTransition
	.byte 0

JohtoPlayersHouse1F_OnTransition:
	setrespawn HEAL_LOCATION_J_NEW_BARK_TOWN
	end

J_W_MomScript::
	lock
	call J_MomScript
	release
	end

J_W_NeighborScript::
	lock
	call J_NeighborScript
	release
	end

J_C_MeetMomLeftScript::
	lockall
	call J_MeetMomLeftScript
	releaseall
	end

J_C_MeetMomRightScript::
	lockall
	call J_MeetMomRightScript
	releaseall
	end

J_S_PlayersHouse1FStoveScript::
	lockall
	call J_PlayersHouse1FStoveScript
	releaseall
	end

J_S_PlayersHouse1FSinkScript::
	lockall
	call J_PlayersHouse1FSinkScript
	releaseall
	end

J_S_PlayersHouse1FFridgeScript::
	lockall
	call J_PlayersHouse1FFridgeScript
	releaseall
	end

J_S_PlayersHouse1FTVScript::
	lockall
	call J_PlayersHouse1FTVScript
	releaseall
	end

J_PlayersHouse1F_MapScripts::
J_PlayersHouse1FNoop1Scene::
	return
J_PlayersHouse1FNoop2Scene::
	return
J_MeetMomLeftScript::
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1
J_MeetMomRightScript::
	playbgm MUS_RG_SLOW_PALLET, FALSE
	applymovement 1, J_Movement_Exclamation
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L645
	setvar VAR_RESULT, 1
J_L645:
	goto_if_eq VAR_RESULT, 0, J_MeetMomRightScript_OnRight
	applymovement 1, J_MomTurnsTowardPlayerMovement
	waitmovement 1
	goto J_MeetMomScript
J_MeetMomRightScript_OnRight:
	applymovement 1, J_MomWalksToPlayerMovement
	waitmovement 1
J_MeetMomScript::
	message J_ElmsLookingForYouText
	waitmessage
	waitbuttonpress
	bufferstring STR_VAR_2, J_PokegearName
	call J_PlayersHouse1FReceiveItemStd
	setflag FLAG_J_ENGINE_POKEGEAR
	setflag FLAG_J_ENGINE_PHONE_CARD
	setvar VAR_J_SCENE_PLAYERS_HOUSE_1F, 1
	setflag FLAG_J_PLAYERS_HOUSE_MOM_1
	clearflag FLAG_J_PLAYERS_HOUSE_MOM_2
	message J_MomGivesPokegearText
	waitmessage
	waitbuttonpress
J_MeetMomScript_SetDayOfWeek:
	message J_IsItDSTText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_MeetMomScript_WrongDay
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_MeetMomScript_SetDayOfWeek
	goto J_MeetMomScript_DayOfWeekDone
J_MeetMomScript_WrongDay:
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_MeetMomScript_SetDayOfWeek
J_MeetMomScript_DayOfWeekDone:
	message J_ComeHomeForDSTText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_MeetMomScript_ExplainPhone
	goto J_MeetMomScript_KnowPhone
J_MeetMomScript_KnowPhone:
	message J_KnowTheInstructionsText
	waitmessage
	waitbuttonpress
	goto J_MeetMomScript_FinishPhone
J_MeetMomScript_ExplainPhone:
	message J_DontKnowTheInstructionsText
	waitmessage
	waitbuttonpress
	goto J_MeetMomScript_FinishPhone
J_MeetMomScript_FinishPhone:
	message J_InstructionsNextText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_1, J_L646
	setvar VAR_RESULT, 1
J_L646:
	goto_if_ne VAR_RESULT, 0, J_MeetMomScript_FromRight
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2, J_L647
	setvar VAR_RESULT, 1
J_L647:
	goto_if_eq VAR_RESULT, 0, J_MeetMomScript_FromLeft
	goto J_MeetMomScript_Finish
J_MeetMomScript_FromRight:
	applymovement 1, J_MomTurnsBackMovement
	waitmovement 1
	goto J_MeetMomScript_Finish
J_MeetMomScript_FromLeft:
	applymovement 1, J_MomWalksBackMovement
	waitmovement 1
	goto J_MeetMomScript_Finish
J_MeetMomScript_Finish:
	fadedefaultbgm
	turnobject 1, DIR_WEST
	return
J_MeetMomTalkedScript::
	playbgm MUS_RG_SLOW_PALLET, FALSE
	goto J_MeetMomScript
J_PokegearName::
	.string "POKéGEAR$"
J_PlayersHouse1FReceiveItemStd::
	goto J_ReceiveItemScript
	return
J_MomScript::
	faceplayer
	setflag FLAG_J_TEMPORARY_UNTIL_MAP_RELOAD_2
	copyvar VAR_RESULT, VAR_J_SCENE_PLAYERS_HOUSE_1F
	goto_if_eq VAR_RESULT, 0, J_MeetMomTalkedScript
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FIRST_TIME_BANKING_WITH_MOM, J_L648
	setvar VAR_RESULT, 1
J_L648:
	goto_if_ne VAR_RESULT, 0, J_MomScript_FirstTimeBanking
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TALKED_TO_MOM_AFTER_MYSTERY_EGG_QUEST, J_L649
	setvar VAR_RESULT, 1
J_L649:
	goto_if_ne VAR_RESULT, 0, J_MomScript_BankOfMom
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_MYSTERY_EGG_TO_ELM, J_L650
	setvar VAR_RESULT, 1
J_L650:
	goto_if_ne VAR_RESULT, 0, J_MomScript_GaveMysteryEgg
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_KJH_GOT_JOHTO_STARTER, J_L651
	setvar VAR_RESULT, 1
J_L651:
	goto_if_ne VAR_RESULT, 0, J_MomScript_GotAPokemon
	message J_HurryUpElmIsWaitingText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MomScript_GotAPokemon:
	message J_SoWhatWasProfElmsErrandText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MomScript_FirstTimeBanking:
	message J_ImBehindYouText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MomScript_GaveMysteryEgg:
	setflag FLAG_J_FIRST_TIME_BANKING_WITH_MOM
J_MomScript_BankOfMom:
	setflag FLAG_J_TALKED_TO_MOM_AFTER_MYSTERY_EGG_QUEST
	setvar VAR_RESULT, 0
	waitbuttonpress
	closemessage
	return
J_NeighborScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_NeighborScript_MornScript
	setvar VAR_RESULT, 1
	goto_if_ne VAR_RESULT, 0, J_NeighborScript_DayScript
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_NeighborScript_NiteScript
J_NeighborScript_MornScript:
	message J_NeighborMornIntroText
	waitmessage
	waitbuttonpress
	goto J_NeighborScript_Main
J_NeighborScript_DayScript:
	message J_NeighborDayIntroText
	waitmessage
	waitbuttonpress
	goto J_NeighborScript_Main
J_NeighborScript_NiteScript:
	message J_NeighborNiteIntroText
	waitmessage
	waitbuttonpress
	goto J_NeighborScript_Main
J_NeighborScript_Main:
	message J_NeighborText
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 5, DIR_EAST
	return
J_PlayersHouse1FTVScript::
	message J_PlayersHouse1FTVText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_PlayersHouse1FStoveScript::
	message J_PlayersHouse1FStoveText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_PlayersHouse1FSinkScript::
	message J_PlayersHouse1FSinkText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_PlayersHouse1FFridgeScript::
	message J_PlayersHouse1FFridgeText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MomTurnsTowardPlayerMovement::
	face_right
	step_end
J_MomWalksToPlayerMovement::
	walk_slow_right
	step_end
J_MomTurnsBackMovement::
	face_left
	step_end
J_MomWalksBackMovement::
	walk_slow_left
	step_end
J_ElmsLookingForYouText::
	.string "Oh, {PLAYER}…! Our\nneighbor, PROF.\pELM, was looking\nfor you.\pHe said he wanted\nyou to do some-\lthing for him.\pOh! I almost for-\ngot! Your POKéMON\pGEAR is back from\nthe repair shop.\pHere you go!$"
J_MomGivesPokegearText::
	.string "POKéMON GEAR, or\njust POKéGEAR.\pIt's essential if\nyou want to be a\lgood trainer.\pOh, the day of the\nweek isn't set.\pYou mustn't forget\nthat!$"
J_IsItDSTText::
	.string "Is it Daylight\nSaving Time now?$"
J_ComeHomeForDSTText::
	.string "Come home to\nadjust your clock\pfor Daylight\nSaving Time.\pBy the way, do you\nknow how to use\lthe PHONE?$"
J_KnowTheInstructionsText::
	.string "Don't you just\nturn the POKéGEAR\pon and select the\nPHONE icon?$"
J_DontKnowTheInstructionsText::
	.string "I'll read the\ninstructions.\pTurn the POKéGEAR\non and select the\lPHONE icon.$"
J_InstructionsNextText::
	.string "Phone numbers are\nstored in memory.\pJust choose a name\nyou want to call.\pGee, isn't that\nconvenient?$"
J_HurryUpElmIsWaitingText::
	.string "PROF.ELM is wait-\ning for you.\pHurry up, baby!$"
J_SoWhatWasProfElmsErrandText::
	.string "So, what was PROF.\nELM's errand?\p…\pThat does sound\nchallenging.\pBut, you should be\nproud that people\lrely on you.$"
J_ImBehindYouText::
	.string "{PLAYER}, do it!\pI'm behind you all\nthe way!$"
J_NeighborMornIntroText::
	.string "Good morning,\n{PLAYER}!\pI'm visiting!$"
J_NeighborDayIntroText::
	.string "Hello, {PLAYER}!\nI'm visiting!$"
J_NeighborNiteIntroText::
	.string "Good evening,\n{PLAYER}!\pI'm visiting!$"
J_NeighborText::
	.string "{PLAYER}, have you\nheard?\pMy daughter is\nadamant about\pbecoming PROF.\nELM's assistant.\pShe really loves\nPOKéMON!$"
J_PlayersHouse1FStoveText::
	.string "Mom's specialty!\pCINNABAR VOLCANO\nBURGER!$"
J_PlayersHouse1FSinkText::
	.string "The sink is spot-\nless. Mom likes it\lclean.$"
J_PlayersHouse1FFridgeText::
	.string "Let's see what's\nin the fridge…\pFRESH WATER and\ntasty LEMONADE!$"
J_PlayersHouse1FTVText::
	.string "There's a movie on\nTV: Stars dot the\psky as two boys\nride on a train…\pI'd better get\nrolling too!$"
J_PlayersHouse1F_MapEvents::
