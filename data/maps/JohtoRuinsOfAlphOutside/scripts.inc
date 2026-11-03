@ KJH: translated from pokecrystal maps/RuinsOfAlphOutside.asm by kjh_tools/johto

JohtoRuinsOfAlphOutside_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoRuinsOfAlphOutside_OnTransition
	.byte 0

JohtoRuinsOfAlphOutside_OnTransition:
	call J_RuinsOfAlphOutsideScientistCallback
	end

J_T_TrainerPsychicNathan::
	trainerbattle_single TRAINER_J_PSYCHIC_T_NATHAN, J_PsychicNathanSeenText, J_PsychicNathanBeatenText
	call J_TrainerPsychicNathan_Script
	release
	end

J_W_RuinsOfAlphOutsideScientistScript::
	lock
	call J_RuinsOfAlphOutsideScientistScript
	release
	end

J_W_RuinsOfAlphOutsideFisherScript::
	lock
	call J_RuinsOfAlphOutsideFisherScript
	release
	end

J_W_RuinsOfAlphOutsideYoungster1Script::
	lock
	call J_RuinsOfAlphOutsideYoungster1Script
	release
	end

J_W_RuinsOfAlphOutsideYoungster2Script::
	lock
	call J_RuinsOfAlphOutsideYoungster2Script
	release
	end

J_C_RuinsOfAlphOutsideScientistScene1::
	lockall
	call J_RuinsOfAlphOutsideScientistScene1
	releaseall
	end

J_C_RuinsOfAlphOutsideScientistScene2::
	lockall
	call J_RuinsOfAlphOutsideScientistScene2
	releaseall
	end

J_S_RuinsOfAlphOutsideMysteryChamberSign::
	lockall
	call J_RuinsOfAlphOutsideMysteryChamberSign
	releaseall
	end

J_S_RuinsOfAlphSign::
	lockall
	call J_RuinsOfAlphSign
	releaseall
	end

J_S_RuinsOfAlphResearchCenterSign::
	lockall
	call J_RuinsOfAlphResearchCenterSign
	releaseall
	end

J_RuinsOfAlphOutside_MapScripts::
J_RuinsOfAlphOutsideNoop1Scene::
	return
J_RuinsOfAlphOutsideNoop2Scene::
	return
J_RuinsOfAlphOutsideScientistCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_UNOWN_DEX, J_L112
	setvar VAR_RESULT, 1
J_L112:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphOutsideScientistCallback_NoScientist
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_MADE_UNOWN_APPEAR_IN_RUINS, J_L113
	setvar VAR_RESULT, 1
J_L113:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphOutsideScientistCallback_MaybeScientist
	goto J_RuinsOfAlphOutsideScientistCallback_NoScientist
J_RuinsOfAlphOutsideScientistCallback_MaybeScientist:
	setvar VAR_0x8004, 14
	special KJH_CrystalReadVar
	goto_if_gt VAR_RESULT, 2, J_RuinsOfAlphOutsideScientistCallback_YesScientist
	goto J_RuinsOfAlphOutsideScientistCallback_NoScientist
J_RuinsOfAlphOutsideScientistCallback_YesScientist:
	clearflag FLAG_J_RUINS_OF_ALPH_OUTSIDE_SCIENTIST
	setvar VAR_J_SCENE_RUINS_OF_ALPH_OUTSIDE, 1
	return
J_RuinsOfAlphOutsideScientistCallback_NoScientist:
	setflag FLAG_J_RUINS_OF_ALPH_OUTSIDE_SCIENTIST
	setvar VAR_J_SCENE_RUINS_OF_ALPH_OUTSIDE, 0
	return
J_RuinsOfAlphOutsideScientistScene1::
	turnobject 2, DIR_NORTH
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	goto J_RuinsOfAlphOutsideScientistSceneContinue
J_RuinsOfAlphOutsideScientistScene2::
	turnobject 2, DIR_WEST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	goto J_RuinsOfAlphOutsideScientistSceneContinue
J_RuinsOfAlphOutsideScientistScript::
	faceplayer
J_RuinsOfAlphOutsideScientistSceneContinue::
	message J_RuinsOfAlphOutsideScientistText
	waitmessage
	waitbuttonpress
	closemessage
	playbgm MUS_RG_FOLLOW_ME, FALSE
	applymovement 2, J_RuinsOfAlphOutsideScientistWalkToLabMovement
	applymovement OBJ_EVENT_ID_PLAYER, J_RuinsOfAlphOutsideScientistWalkToLabMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement 2
	removeobject 2
	applymovement OBJ_EVENT_ID_PLAYER, J_RuinsOfAlphOutsidePlayerEnterLabMovement
	waitmovement OBJ_EVENT_ID_PLAYER
	setvar VAR_J_SCENE_RUINS_OF_ALPH_RESEARCH_CENTER, 1
	return
J_RuinsOfAlphOutsideFisherScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TALKED_TO_RUINS_COWARD, J_L114
	setvar VAR_RESULT, 1
J_L114:
	goto_if_ne VAR_RESULT, 0, J_RuinsOfAlphOutsideFisherScript_Next
	setflag FLAG_J_TALKED_TO_RUINS_COWARD
	message J_RuinsOfAlphOutsideFisherText1
	waitmessage
	waitbuttonpress
J_RuinsOfAlphOutsideFisherScript_Next:
	message J_RuinsOfAlphOutsideFisherText2
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphOutsideYoungster1Script::
	faceplayer
	message J_RuinsOfAlphOutsideYoungster1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphOutsideYoungster2Script::
	faceplayer
	message J_RuinsOfAlphOutsideYoungster2Text
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 5, DIR_NORTH
	return
J_TrainerPsychicNathan::
J_TrainerPsychicNathan_Script:
	message J_PsychicNathanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSuperNerdStan::
J_TrainerSuperNerdStan_Script:
	message J_SuperNerdStanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphOutsideMysteryChamberSign::
	message J_RuinsOfAlphOutsideMysteryChamberSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphSign::
	message J_RuinsOfAlphSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphResearchCenterSign::
	message J_RuinsOfAlphResearchCenterSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphOutsideScientistWalkToLabMovement::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	step_end
J_RuinsOfAlphOutsidePlayerEnterLabMovement::
	walk_up
	step_end
J_RuinsOfAlphOutsideScientistText::
	.string "Hm? That's a POKé-\nDEX, isn't it?\lMay I see it?\pThere are so many\nkinds of POKéMON.\pHm? What's this?\pWhat is this\nPOKéMON?\pIt looks like the\nstrange writing on\pthe walls of the\nRUINS.\pIf those drawings\nare really POKé-\lMON, there should\lbe many more.\pI know! Let me up-\ngrade your POKé-\lDEX. Follow me.$"
J_SuperNerdStanSeenText::
	.string "What do you want?\nI'm studying--\ldon't disturb me!$"
J_SuperNerdStanBeatenText::
	.string "Sorry…\nI'm frustrated by\pour lack of real\nunderstanding…$"
J_SuperNerdStanAfterBattleText::
	.string "The RUINS are from\nabout 1500 years\lago.\pNobody knows who\nbuilt them.\pIt's also not\nknown if the POKé-\lMON statues have\lany meaning.\pIt's all one big\nmystery…$"
J_PsychicNathanSeenText::
	.string "Hmmm… This is a\nstrange place.$"
J_PsychicNathanBeatenText::
	.string "…$"
J_PsychicNathanAfterBattleText::
	.string "I like thinking\nhere.$"
J_RuinsOfAlphOutsideMysteryChamberSignText::
	.string "MYSTERY STONE\nPANEL CHAMBER$"
J_RuinsOfAlphSignText::
	.string "RUINS OF ALPH\nVISITORS WELCOME$"
J_RuinsOfAlphResearchCenterSignText::
	.string "RUINS OF ALPH\nRESEARCH CENTER\pTHE AUTHORITY ON\nTHE RUINS OF ALPH$"
J_RuinsOfAlphOutsideFisherText1::
	.string "While exploring\nthe RUINS, we\psuddenly noticed\nan odd presence.\pWe all got scared\nand ran away.\pYou should be\ncareful too.$"
J_RuinsOfAlphOutsideFisherText2::
	.string "The RUINS hide a\nhuge secret!\p…I think…$"
J_RuinsOfAlphOutsideYoungster1Text::
	.string "There are many\nkinds of UNOWN, so\pwe use them for\nour secret codes.$"
J_RuinsOfAlphOutsideYoungster2Text::
	.string "A… H… E… A… D…\nHmm…\pWhat?\pI'm decoding this\nmessage!$"
J_RuinsOfAlphOutside_MapEvents::
