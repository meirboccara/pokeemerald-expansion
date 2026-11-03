@ KJH: translated from pokecrystal maps/MrPokemonsHouse.asm by kjh_tools/johto

JohtoMrPokemonsHouse_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoMrPokemonsHouse_OnFrame
	.byte 0

JohtoMrPokemonsHouse_OnFrame:
	map_script_2 VAR_J_SCENE_MR_POKEMONS_HOUSE, 0, J_SC_MrPokemonsHouseMeetMrPokemonScene
	.2byte 0

J_W_MrPokemonsHouse_MrPokemonScript::
	lock
	call J_MrPokemonsHouse_MrPokemonScript
	release
	end

J_S_MrPokemonsHouse_ForeignMagazines::
	lockall
	call J_MrPokemonsHouse_ForeignMagazines
	releaseall
	end

J_S_MrPokemonsHouse_BrokenComputer::
	lockall
	call J_MrPokemonsHouse_BrokenComputer
	releaseall
	end

J_S_MrPokemonsHouse_StrangeCoins::
	lockall
	call J_MrPokemonsHouse_StrangeCoins
	releaseall
	end

J_SC_MrPokemonsHouseMeetMrPokemonScene::
	lockall
	call J_MrPokemonsHouseMeetMrPokemonScene
	releaseall
	end

J_MrPokemonsHouse_MapScripts::
J_MrPokemonsHouseMeetMrPokemonScene::
	call J_MrPokemonsHouseMrPokemonEventScript
	return
J_MrPokemonsHouseNoopScene::
	return
J_MrPokemonsHouseMrPokemonEventScript::
	applymovement 1, J_Movement_Exclamation
	waitmovement 0
	turnobject 1, DIR_SOUTH
	message J_MrPokemonIntroText1
	waitmessage
	waitbuttonpress
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, J_MrPokemonsHouse_PlayerWalksToMrPokemon
	waitmovement OBJ_EVENT_ID_PLAYER
	message J_MrPokemonIntroText2
	waitmessage
	waitbuttonpress
	waitse
	setflag FLAG_J_HAS_MYSTERY_EGG
	setvar VAR_RESULT, 1
	message J_MrPokemonsHouse_GotEggText
	waitmessage
	playse SE_SUCCESS
	waitse
	setflag FLAG_J_GOT_MYSTERY_EGG_FROM_MR_POKEMON
	message J_MrPokemonIntroText3
	waitmessage
	waitbuttonpress
	turnobject 1, DIR_EAST
	message J_MrPokemonIntroText4
	waitmessage
	waitbuttonpress
	turnobject 1, DIR_SOUTH
	turnobject 2, DIR_WEST
	message J_MrPokemonIntroText5
	waitmessage
	waitbuttonpress
	closemessage
	goto J_MrPokemonsHouse_OakScript
J_MrPokemonsHouse_MrPokemonScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HAS_RED_SCALE, J_L690
	setvar VAR_RESULT, 1
J_L690:
	goto_if_ne VAR_RESULT, 0, J_MrPokemonsHouse_MrPokemonScript_RedScale
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_MYSTERY_EGG_TO_ELM, J_L691
	setvar VAR_RESULT, 1
J_L691:
	goto_if_ne VAR_RESULT, 0, J_MrPokemonsHouse_MrPokemonScript_AlwaysNewDiscoveries
	message J_MrPokemonText_ImDependingOnYou
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MrPokemonsHouse_MrPokemonScript_AlwaysNewDiscoveries:
	message J_MrPokemonText_AlwaysNewDiscoveries
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MrPokemonsHouse_MrPokemonScript_RedScale:
	message J_MrPokemonText_GimmeTheScale
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_MrPokemonsHouse_MrPokemonScript_refused
	giveitem ITEM_SOOTHE_BELL, 1 @ KJH (LV-7): the Exp. Share is gone
	goto_if_eq VAR_RESULT, 0, J_MrPokemonsHouse_MrPokemonScript_full
	clearflag FLAG_J_HAS_RED_SCALE
	setvar VAR_RESULT, 1
	goto J_MrPokemonsHouse_MrPokemonScript_AlwaysNewDiscoveries
J_MrPokemonsHouse_MrPokemonScript_refused:
	message J_MrPokemonText_Disappointed
	waitmessage
	waitbuttonpress
J_MrPokemonsHouse_MrPokemonScript_full:
	closemessage
	return
J_MrPokemonsHouse_OakScript::
	playbgm MUS_RG_OAK, FALSE
	applymovement 2, J_MrPokemonsHouse_OakWalksToPlayer
	waitmovement 2
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	message J_MrPokemonsHouse_OakText1
	waitmessage
	waitbuttonpress
	waitse
	message J_MrPokemonsHouse_GetDexText
	waitmessage
	playse SE_SUCCESS
	waitse
	setflag FLAG_SYS_POKEDEX_GET
	message J_MrPokemonsHouse_OakText2
	waitmessage
	waitbuttonpress
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement 2, J_MrPokemonsHouse_OakExits
	waitmovement 2
	playse SE_EXIT
	removeobject 2
	waitse
	fadedefaultbgm
	delay 15
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	message J_MrPokemonsHouse_MrPokemonHealText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_BLACK
	playbgm MUS_RG_HEAL, FALSE
	special HealPlayerParty
	delay 60
	fadescreen FADE_FROM_BLACK
	fadedefaultbgm
	message J_MrPokemonText_ImDependingOnYou
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_RIVAL_NEW_BARK_TOWN
	setflag FLAG_J_PLAYERS_HOUSE_1F_NEIGHBOR
	clearflag FLAG_J_PLAYERS_NEIGHBORS_HOUSE_NEIGHBOR
	setvar VAR_J_SCENE_MR_POKEMONS_HOUSE, 1
	setvar VAR_J_SCENE_CHERRYGROVE_CITY, 1
	setvar VAR_J_SCENE_ELMS_LAB, 3
	clearflag FLAG_J_COP_IN_ELMS_LAB
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TOTODILE_FROM_ELM, J_L692
	setvar VAR_RESULT, 1
J_L692:
	goto_if_ne VAR_RESULT, 0, J_MrPokemonsHouse_OakScript_RivalTakesChikorita
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_CHIKORITA_FROM_ELM, J_L693
	setvar VAR_RESULT, 1
J_L693:
	goto_if_ne VAR_RESULT, 0, J_MrPokemonsHouse_OakScript_RivalTakesCyndaquil
	setflag FLAG_J_TOTODILE_POKEBALL_IN_ELMS_LAB
	return
J_MrPokemonsHouse_OakScript_RivalTakesChikorita:
	setflag FLAG_J_CHIKORITA_POKEBALL_IN_ELMS_LAB
	return
J_MrPokemonsHouse_OakScript_RivalTakesCyndaquil:
	setflag FLAG_J_CYNDAQUIL_POKEBALL_IN_ELMS_LAB
	return
J_MrPokemonsHouse_ForeignMagazines::
	message J_MrPokemonsHouse_ForeignMagazinesText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MrPokemonsHouse_BrokenComputer::
	message J_MrPokemonsHouse_BrokenComputerText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MrPokemonsHouse_StrangeCoins::
	message J_MrPokemonsHouse_StrangeCoinsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MrPokemonsHouse_PlayerWalksToMrPokemon::
	walk_right
	walk_up
	step_end
J_MrPokemonsHouse_OakWalksToPlayer::
	walk_down
	walk_left
	walk_left
	step_end
J_MrPokemonsHouse_OakExits::
	walk_down
	walk_left
	face_down
	delay_2
	step_end
J_MrPokemonIntroText1::
	.string "Hello, hello! You\nmust be {PLAYER}.\pPROF.ELM said that\nyou would visit.$"
J_MrPokemonIntroText2::
	.string "This is what I\nwant PROF.ELM to\lexamine.$"
J_MrPokemonsHouse_GotEggText::
	.string "{PLAYER} received\nMYSTERY EGG.$"
J_MrPokemonIntroText3::
	.string "I know a couple\nwho run a POKéMON\lDAY-CARE service.\pThey gave me that\nEGG.\pI was intrigued,\nso I sent mail to\lPROF.ELM.\pFor POKéMON evolu-\ntion, PROF.ELM is\lthe authority.$"
J_MrPokemonIntroText4::
	.string "Even PROF.OAK here\nrecognizes that.$"
J_MrPokemonIntroText5::
	.string "If my assumption\nis correct, PROF.\lELM will know it.$"
J_MrPokemonsHouse_MrPokemonHealText::
	.string "You are returning\nto PROF.ELM?\pHere. Your POKéMON\nshould have some\lrest.$"
J_MrPokemonText_ImDependingOnYou::
	.string "I'm depending on\nyou!$"
J_MrPokemonText_AlwaysNewDiscoveries::
	.string "Life is delight-\nful! Always, new\pdiscoveries to be\nmade!$"
J_MrPokemonsHouse_OakText1::
	.string "OAK: Aha! So\nyou're {PLAYER}!\pI'm OAK! A POKéMON\nresearcher.\pI was just visit-\ning my old friend\lMR.POKéMON.\pI heard you were\nrunning an errand\pfor PROF.ELM, so I\nwaited here.\pOh! What's this?\nA rare POKéMON!\pLet's see…\pHm, I see!\pI understand why\nPROF.ELM gave you\pa POKéMON for this\nerrand.\pTo researchers\nlike PROF.ELM and\pI, POKéMON are our\nfriends.\pHe saw that you\nwould treat your\pPOKéMON with love\nand care.\p…Ah!\pYou seem to be\ndependable.\pHow would you like\nto help me out?\pSee? This is the\nlatest version of\lPOKéDEX.\pIt automatically\nrecords data on\pPOKéMON you've\nseen or caught.\pIt's a hi-tech\nencyclopedia!$"
J_MrPokemonsHouse_GetDexText::
	.string "{PLAYER} received\nPOKéDEX!$"
J_MrPokemonsHouse_OakText2::
	.string "Go meet many kinds\nof POKéMON and\pcomplete that\nPOKéDEX!\pBut I've stayed\ntoo long.\pI have to get to\nGOLDENROD for my\lusual radio show.\p{PLAYER}, I'm\ncounting on you!$"
J_MrPokemonText_GimmeTheScale::
	.string "Hm? That SCALE!\nWhat's that?\lA red GYARADOS?\pThat's rare! \nI, I want it…\p{PLAYER}, would you\ncare to trade it?\pI can offer this\nSOOTHE BELL I got\lfrom PROF.OAK.$"
J_MrPokemonText_Disappointed::
	.string "That's disappoint-\ning. That happens\lto be very rare.$"
J_MrPokemonsHouse_ForeignMagazinesText::
	.string "It's packed with\nforeign magazines.\pCan't even read\ntheir titles…$"
J_MrPokemonsHouse_BrokenComputerText::
	.string "It's a big com-\nputer. Hmm. It's\lbroken.$"
J_MrPokemonsHouse_StrangeCoinsText::
	.string "A whole pile of\nstrange coins!\pMaybe they're from\nanother country…$"
J_MrPokemonsHouse_MapEvents::
