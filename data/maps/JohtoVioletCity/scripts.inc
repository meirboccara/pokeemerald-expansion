@ KJH: translated from pokecrystal maps/VioletCity.asm by kjh_tools/johto

JohtoVioletCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoVioletCity_OnTransition
	.byte 0

JohtoVioletCity_OnTransition:
	call J_VioletCityFlypointCallback
	end

J_W_VioletCityEarlScript::
	lock
	call J_VioletCityEarlScript
	release
	end

J_W_VioletCityLassScript::
	lock
	call J_VioletCityLassScript
	release
	end

J_W_VioletCitySuperNerdScript::
	lock
	call J_VioletCitySuperNerdScript
	release
	end

J_W_VioletCityGrampsScript::
	lock
	call J_VioletCityGrampsScript
	release
	end

J_W_VioletCityYoungsterScript::
	lock
	call J_VioletCityYoungsterScript
	release
	end

J_W_VioletCityFruitTree::
	lock
	call J_VioletCityFruitTree
	release
	end

J_S_VioletCitySign::
	lockall
	call J_VioletCitySign
	releaseall
	end

J_S_VioletGymSign::
	lockall
	call J_VioletGymSign
	releaseall
	end

J_S_SproutTowerSign::
	lockall
	call J_SproutTowerSign
	releaseall
	end

J_S_EarlsPokemonAcademySign::
	lockall
	call J_EarlsPokemonAcademySign
	releaseall
	end

J_S_VioletCityPokecenterSign::
	lockall
	call J_VioletCityPokecenterSign
	releaseall
	end

J_S_VioletCityMartSign::
	lockall
	call J_VioletCityMartSign
	releaseall
	end

J_VioletCity_MapScripts::
J_VioletCityFlypointCallback::
	setflag FLAG_J_ENGINE_FLYPOINT_VIOLET
	return
J_VioletCityEarlScript::
	applymovement 1, J_VioletCitySpinningEarl_MovementData
	waitmovement 1
	faceplayer
	message J_Text_EarlAsksIfYouBeatFalkner
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_VioletCityEarlScript_FollowEarl
	goto J_VioletCityEarlScript_PointlessJump
J_VioletCityEarlScript_PointlessJump:
	message J_Text_VeryNiceIndeed
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletCityEarlScript_FollowEarl:
	message J_Text_FollowEarl
	waitmessage
	waitbuttonpress
	closemessage
	playbgm MUS_RG_FOLLOW_ME, FALSE
	applymovement 1, J_VioletCityFollowEarl_MovementData
	applymovement OBJ_EVENT_ID_PLAYER, J_VioletCityFollowEarl_MovementData
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	applymovement 1, J_VioletCitySpinningEarl_MovementData
	applymovement OBJ_EVENT_ID_PLAYER, J_VioletCitySpinningEarl_MovementData
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement 1
	fadedefaultbgm
	message J_Text_HereTeacherIAm
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_VioletCitySpinningEarl_MovementData
	waitmovement 1
	applymovement 1, J_VioletCityFinishFollowEarl_MovementData
	waitmovement 1
	playse SE_DOOR
	removeobject 1
	clearflag FLAG_J_EARLS_ACADEMY_EARL
	waitse
	return
J_VioletCityLassScript::
	faceplayer
	message J_VioletCityLassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletCitySuperNerdScript::
	faceplayer
	message J_VioletCitySuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletCityGrampsScript::
	faceplayer
	message J_VioletCityGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletCityYoungsterScript::
	faceplayer
	message J_VioletCityYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletCitySign::
	message J_VioletCitySignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletGymSign::
	message J_VioletGymSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SproutTowerSign::
	message J_SproutTowerSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EarlsPokemonAcademySign::
	message J_EarlsPokemonAcademySignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletCityPokecenterSign::
	goto J_PokecenterSignScript
J_VioletCityMartSign::
	goto J_MartSignScript
J_VioletCityPPUp::
	finditem ITEM_PP_UP, 1
	return
J_VioletCityRareCandy::
	finditem ITEM_RARE_CANDY, 1
	return
J_VioletCityFruitTree::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_VioletCityHiddenHyperPotion::
	finditem ITEM_HYPER_POTION
	return
J_VioletCityFollowEarl_MovementData::
	walk_fast_down
	walk_fast_down
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	walk_fast_down
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	walk_fast_up
	face_down
	step_end
J_VioletCityFinishFollowEarl_MovementData::
	walk_up
	step_end
J_VioletCitySpinningEarl_MovementData::
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	face_down
	step_end
J_Text_EarlAsksIfYouBeatFalkner::
	.string "Hello!\nYou are trainer?\pBattle GYM LEADER,\nwin you did?$"
J_Text_VeryNiceIndeed::
	.string "Ooh, la la!\nVery indeed nice!$"
J_Text_FollowEarl::
	.string "Is that so? Then\nstudy shall you!\lFollow me!$"
J_Text_HereTeacherIAm::
	.string "Here, teacher I\nam. Good it is\lyou study here!$"
J_VioletCityLassText::
	.string "Ghosts are rumored\nto appear in\lSPROUT TOWER.\pThey said normal-\ntype POKéMON moves\phad no effect on\nghosts.$"
J_VioletCitySuperNerdText::
	.string "Hey, you're a\nPOKéMON trainer?\pIf you beat the\nGYM LEADER here,\pyou'll be ready\nfor prime time!$"
J_VioletCityGrampsText::
	.string "FALKNER, from the\nVIOLET POKéMON\pGYM, is a fine\ntrainer!\pHe inherited his\nfather's gym and\phas done a great\njob with it.$"
J_VioletCityYoungsterText::
	.string "I saw a wiggly\ntree up ahead!\pIf you touch it,\nit squirms and\ldances! Cool!$"
J_VioletCitySignText::
	.string "VIOLET CITY\pThe City of\nNostalgic Scents$"
J_VioletGymSignText::
	.string "VIOLET CITY\nPOKéMON GYM\lLEADER: FALKNER\pThe Elegant Master\nof Flying POKéMON$"
J_SproutTowerSignText::
	.string "SPROUT TOWER\pExperience the\nWay of POKéMON$"
J_EarlsPokemonAcademySignText::
	.string "EARL'S POKéMON\nACADEMY$"
J_VioletCity_MapEvents::
