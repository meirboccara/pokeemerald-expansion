@ KJH: translated from pokecrystal maps/OlivineGym.asm by kjh_tools/johto

JohtoOlivineGym_MapScripts::
	.byte 0

J_W_OlivineGymJasmineScript::
	lock
	call J_OlivineGymJasmineScript
	release
	end

J_W_OlivineGymGuideScript::
	lock
	call J_OlivineGymGuideScript
	release
	end

J_S_OlivineGymStatue::
	lockall
	call J_OlivineGymStatue
	releaseall
	end

J_OlivineGym_MapScripts::
J_OlivineGymJasmineScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_JASMINE, J_L1
	setvar VAR_RESULT, 1
J_L1:
	goto_if_ne VAR_RESULT, 0, J_OlivineGymJasmineScript_FightDone
	message J_Jasmine_SteelTypeIntro
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_J_JASMINE_JASMINE1, J_Jasmine_BetterTrainer
	setflag FLAG_J_BEAT_JASMINE
	message J_Text_ReceivedMineralBadge
	waitmessage
	playse SE_SUCCESS
	waitse
	setflag FLAG_JOHTO_BADGE06_GET
	setvar VAR_0x8004, 7
	special KJH_CrystalReadVar
	call J_OlivineGymActivateRockets
J_OlivineGymJasmineScript_FightDone:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM23_IRON_TAIL, J_L2
	setvar VAR_RESULT, 1
J_L2:
	goto_if_ne VAR_RESULT, 0, J_OlivineGymJasmineScript_GotIronTail
	message J_Jasmine_BadgeSpeech
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM23, 1
	goto_if_eq VAR_RESULT, 0, J_OlivineGymJasmineScript_NoRoomForIronTail
	setflag FLAG_J_GOT_TM23_IRON_TAIL
	message J_Jasmine_IronTailSpeech
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineGymJasmineScript_GotIronTail:
	message J_Jasmine_GoodLuck
	waitmessage
	waitbuttonpress
J_OlivineGymJasmineScript_NoRoomForIronTail:
	closemessage
	return
J_OlivineGymActivateRockets::
	goto_if_eq VAR_RESULT, 7, J_OlivineGymActivateRockets_RadioTowerRockets
	goto_if_eq VAR_RESULT, 6, J_OlivineGymActivateRockets_GoldenrodRockets
	return
J_OlivineGymActivateRockets_GoldenrodRockets:
	goto J_GoldenrodRocketsScript
J_OlivineGymActivateRockets_RadioTowerRockets:
	goto J_RadioTowerRocketsScript
J_OlivineGymGuideScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_JASMINE, J_L3
	setvar VAR_RESULT, 1
J_L3:
	goto_if_ne VAR_RESULT, 0, J_OlivineGymGuideScript_OlivineGymGuideWinScript
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_JASMINE_RETURNED_TO_GYM, J_L4
	setvar VAR_RESULT, 1
J_L4:
	goto_if_eq VAR_RESULT, 0, J_OlivineGymGuideScript_OlivineGymGuidePreScript
	message J_OlivineGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineGymGuideScript_OlivineGymGuideWinScript:
	message J_OlivineGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineGymGuideScript_OlivineGymGuidePreScript:
	message J_OlivineGymGuidePreText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineGymStatue::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE06_GET, J_L5
	setvar VAR_RESULT, 1
J_L5:
	goto_if_ne VAR_RESULT, 0, J_OlivineGymStatue_Beaten
	goto J_GymStatue1Script
J_OlivineGymStatue_Beaten:
	bufferstring STR_VAR_2, J_TrainerName_JASMINE_JASMINE1
	goto J_GymStatue2Script
J_Jasmine_SteelTypeIntro::
	.string "…Thank you for\nyour help at the\lLIGHTHOUSE…\pBut this is dif-\nferent. Please\pallow me to intro-\nduce myself.\pI am JASMINE, a\nGYM LEADER. I use\lthe steel-type.\p…Do you know about\nthe steel-type?\pIt's a type that\nwas only recently\ldiscovered.\p…Um… May I begin?$"
J_Jasmine_BetterTrainer::
	.string "…You are a better\ntrainer than me,\pin both skill and\nkindness.\pIn accordance with\nLEAGUE rules, I\pconfer upon you\nthis BADGE.$"
J_Text_ReceivedMineralBadge::
	.string "{PLAYER} received\nMINERALBADGE.$"
J_Jasmine_BadgeSpeech::
	.string "MINERALBADGE\nraises POKéMON's\lDEFENSE.\p…Um… Please take\nthis too…$"
J_Text_ReceivedTM09::
	.string "{PLAYER} received\nTM09.$"
J_Jasmine_IronTailSpeech::
	.string "…You could use\nthat TM to teach\lIRON TAIL.$"
J_Jasmine_GoodLuck::
	.string "Um… I don't know\nhow to say this,\lbut good luck…$"
J_OlivineGymGuideText::
	.string "JASMINE uses the\nnewly discovered\lsteel-type.\pI don't know very\nmuch about it.$"
J_OlivineGymGuideWinText::
	.string "That was awesome.\pThe steel-type,\nhuh?\pThat was a close\nencounter of an\lunknown kind!$"
J_OlivineGymGuidePreText::
	.string "JASMINE, the GYM\nLEADER, is at the\lLIGHTHOUSE.\pShe's been tending\nto a sick POKéMON.\pA strong trainer\nhas to be compas-\lsionate.$"
J_OlivineGym_MapEvents::
