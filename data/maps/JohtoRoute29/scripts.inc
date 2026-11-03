@ KJH: translated from pokecrystal maps/Route29.asm by kjh_tools/johto

JohtoRoute29_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoRoute29_OnTransition
	.byte 0

JohtoRoute29_OnTransition:
	call J_Route29TuscanyCallback
	end

J_W_CatchingTutorialDudeScript::
	lock
	call J_CatchingTutorialDudeScript
	release
	end

J_W_Route29YoungsterScript::
	lock
	call J_Route29YoungsterScript
	release
	end

J_W_Route29TeacherScript::
	lock
	call J_Route29TeacherScript
	release
	end

J_W_Route29FruitTree::
	lock
	call J_Route29FruitTree
	release
	end

J_W_Route29FisherScript::
	lock
	call J_Route29FisherScript
	release
	end

J_W_Route29CooltrainerMScript::
	lock
	call J_Route29CooltrainerMScript
	release
	end

J_W_TuscanyScript::
	lock
	call J_TuscanyScript
	release
	end

J_C_Route29Tutorial1::
	lockall
	call J_Route29Tutorial1
	releaseall
	end

J_C_Route29Tutorial2::
	lockall
	call J_Route29Tutorial2
	releaseall
	end

J_S_Route29Sign1::
	lockall
	call J_Route29Sign1
	releaseall
	end

J_S_Route29Sign2::
	lockall
	call J_Route29Sign2
	releaseall
	end

J_Route29_MapScripts::
J_Route29Noop1Scene::
	return
J_Route29Noop2Scene::
	return
J_Route29TuscanyCallback::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE01_GET, J_L613
	setvar VAR_RESULT, 1
J_L613:
	goto_if_ne VAR_RESULT, 0, J_Route29TuscanyCallback_DoesTuscanyAppear
J_Route29TuscanyCallback_TuscanyDisappears:
	setflag FLAG_J_ROUTE_29_TUSCANY_OF_TUESDAY
	return
J_Route29TuscanyCallback_DoesTuscanyAppear:
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_ne VAR_RESULT, 2, J_Route29TuscanyCallback_TuscanyDisappears
	clearflag FLAG_J_ROUTE_29_TUSCANY_OF_TUESDAY
	return
J_Route29Tutorial1::
	turnobject 1, DIR_NORTH
	applymovement 1, J_Movement_Exclamation
	waitmovement 0
	applymovement 1, J_DudeMovementData1a
	waitmovement 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	setflag FLAG_J_DUDE_TALKED_TO_YOU
	message J_CatchingTutorialIntroText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_Script_RefusedTutorial1
	closemessage
	applymovement 1, J_DudeMovementData1b
	applymovement OBJ_EVENT_ID_PLAYER, J_DudeMovementData1b
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement 1
	setwildbattle SPECIES_RATTATA, 5
	turnobject 1, DIR_NORTH
	message J_CatchingTutorialDebriefText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_J_SCENE_ROUTE_29, 0
	setflag FLAG_J_LEARNED_TO_CATCH_POKEMON
	return
J_Route29Tutorial2::
	turnobject 1, DIR_NORTH
	applymovement 1, J_Movement_Exclamation
	waitmovement 0
	applymovement 1, J_DudeMovementData2a
	waitmovement 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	setflag FLAG_J_DUDE_TALKED_TO_YOU
	message J_CatchingTutorialIntroText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_Script_RefusedTutorial2
	closemessage
	applymovement 1, J_DudeMovementData2b
	applymovement OBJ_EVENT_ID_PLAYER, J_DudeMovementData2b
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement 1
	setwildbattle SPECIES_RATTATA, 5
	turnobject 1, DIR_NORTH
	message J_CatchingTutorialDebriefText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_J_SCENE_ROUTE_29, 0
	setflag FLAG_J_LEARNED_TO_CATCH_POKEMON
	return
J_Script_RefusedTutorial1::
	message J_CatchingTutorialDeclinedText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_DudeMovementData1b
	waitmovement 1
	setvar VAR_J_SCENE_ROUTE_29, 0
	return
J_Script_RefusedTutorial2::
	message J_CatchingTutorialDeclinedText
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 1, J_DudeMovementData2b
	waitmovement 1
	setvar VAR_J_SCENE_ROUTE_29, 0
	return
J_CatchingTutorialDudeScript::
	faceplayer
	setvar VAR_0x8004, 16
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J_CatchingTutorialDudeScript_BoxFull
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_LEARNED_TO_CATCH_POKEMON, J_L614
	setvar VAR_RESULT, 1
J_L614:
	goto_if_ne VAR_RESULT, 0, J_CatchingTutorialDudeScript_BoxFull
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_MYSTERY_EGG_TO_ELM, J_L615
	setvar VAR_RESULT, 1
J_L615:
	goto_if_eq VAR_RESULT, 0, J_CatchingTutorialDudeScript_BoxFull
	message J_CatchingTutorialRepeatText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_CatchingTutorialDudeScript_Declined
	closemessage
	setwildbattle SPECIES_RATTATA, 5
	message J_CatchingTutorialDebriefText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_LEARNED_TO_CATCH_POKEMON
	return
J_CatchingTutorialDudeScript_BoxFull:
	message J_CatchingTutorialBoxFullText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CatchingTutorialDudeScript_Declined:
	message J_CatchingTutorialDeclinedText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route29YoungsterScript::
	faceplayer
	message J_Route29YoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route29TeacherScript::
	faceplayer
	message J_Route29TeacherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route29FisherScript::
	faceplayer
	message J_Route29FisherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route29CooltrainerMScript::
	faceplayer
	setvar VAR_RESULT, 1
	goto_if_ne VAR_RESULT, 0, J_Route29CooltrainerMScript_day_morn
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_Route29CooltrainerMScript_nite
J_Route29CooltrainerMScript_day_morn:
	message J_Route29CooltrainerMText_WaitingForNight
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route29CooltrainerMScript_nite:
	message J_Route29CooltrainerMText_WaitingForMorning
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TuscanyScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_PINK_BOW_FROM_TUSCANY, J_L616
	setvar VAR_RESULT, 1
J_L616:
	goto_if_ne VAR_RESULT, 0, J_TuscanyTuesdayScript
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_ne VAR_RESULT, 2, J_TuscanyNotTuesdayScript
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_MET_TUSCANY_OF_TUESDAY, J_L617
	setvar VAR_RESULT, 1
J_L617:
	goto_if_ne VAR_RESULT, 0, J_TuscanyScript_MetTuscany
	message J_MeetTuscanyText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_MET_TUSCANY_OF_TUESDAY
J_TuscanyScript_MetTuscany:
	message J_TuscanyGivesGiftText
	waitmessage
	waitbuttonpress
	giveitem ITEM_SILK_SCARF, 1
	goto_if_eq VAR_RESULT, 0, J_TuscanyDoneScript
	setflag FLAG_J_GOT_PINK_BOW_FROM_TUSCANY
	message J_TuscanyGaveGiftText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TuscanyTuesdayScript::
	message J_TuscanyTuesdayText
	waitmessage
	waitbuttonpress
J_TuscanyDoneScript::
	closemessage
	return
J_TuscanyNotTuesdayScript::
	message J_TuscanyNotTuesdayText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route29Sign1::
	message J_Route29Sign1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route29Sign2::
	message J_Route29Sign2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route29FruitTree::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_Route29Potion::
	finditem ITEM_POTION, 1
	return
J_DudeMovementData1a::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end
J_DudeMovementData2a::
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end
J_DudeMovementData1b::
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
J_DudeMovementData2b::
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	step_end
J_CatchingTutorialBoxFullText::
	.string "POKéMON hide in\nthe grass. Who\pknows when they'll\npop out…$"
J_CatchingTutorialIntroText::
	.string "I've seen you a\ncouple times. How\pmany POKéMON have\nyou caught?\pWould you like me\nto show you how to\lcatch POKéMON?$"
J_CatchingTutorialDebriefText::
	.string "That's how you do\nit.\pIf you weaken them\nfirst, POKéMON are\leasier to catch.$"
J_CatchingTutorialDeclinedText::
	.string "Oh. Fine, then.\pAnyway, if you\nwant to catch\pPOKéMON, you have\nto walk a lot.$"
J_CatchingTutorialRepeatText::
	.string "Huh? You want me\nto show you how to\lcatch POKéMON?$"
J_Route29YoungsterText::
	.string "Yo. How are your\nPOKéMON?\pIf they're weak\nand not ready for\pbattle, keep out\nof the grass.$"
J_Route29TeacherText::
	.string "See those ledges?\nIt's scary to jump\loff them.\pBut you can go to\nNEW BARK without\pwalking through\nthe grass.$"
J_Route29FisherText::
	.string "I wanted to take a\nbreak, so I saved\pto record my\nprogress.$"
J_Route29CooltrainerMText_WaitingForDay::
	.string "I'm waiting for\nPOKéMON that\pappear only in the\ndaytime.$"
J_Route29CooltrainerMText_WaitingForNight::
	.string "I'm waiting for\nPOKéMON that\pappear only at\nnight.$"
J_Route29CooltrainerMText_WaitingForMorning::
	.string "I'm waiting for\nPOKéMON that\pappear only in the\nmorning.$"
J_MeetTuscanyText::
	.string "TUSCANY: I do be-\nlieve that this is\pthe first time\nwe've met?\pPlease allow me to\nintroduce myself.\pI am TUSCANY of\nTuesday.$"
J_TuscanyGivesGiftText::
	.string "By way of intro-\nduction, please\paccept this gift,\na PINK BOW.$"
J_TuscanyGaveGiftText::
	.string "TUSCANY: Wouldn't\nyou agree that it\lis most adorable?\pIt strengthens\nnormal-type moves.\pI am certain it\nwill be of use.$"
J_TuscanyTuesdayText::
	.string "TUSCANY: Have you\nmet MONICA, my\lolder sister?\pOr my younger\nbrother, WESLEY?\pI am the second of\nseven children.$"
J_TuscanyNotTuesdayText::
	.string "TUSCANY: Today is\nnot Tuesday. That\lis unfortunate…$"
J_Route29Sign1Text::
	.string "ROUTE 29\pCHERRYGROVE CITY -\nNEW BARK TOWN$"
J_Route29Sign2Text::
	.string "ROUTE 29\pCHERRYGROVE CITY -\nNEW BARK TOWN$"
J_Route29_MapEvents::
