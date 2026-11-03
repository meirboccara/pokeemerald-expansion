@ KJH (LV-13): Kanto's training masters (src/kjh_masters.c). Each can be fought twice per in-game day; a win
@ gives +20 move points to every move of its type used in the battle.

KJH_EventScript_MasterWater::
	setvar VAR_0x8004, TRAINER_KJH_MASTER_WATER
	call KJH_EventScript_MasterAsk
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_MasterEnd
	cleartrainerflag TRAINER_KJH_MASTER_WATER
	trainerbattle_no_intro TRAINER_KJH_MASTER_WATER, KJH_Text_MasterDefeat
	setvar VAR_0x8004, TRAINER_KJH_MASTER_WATER
	goto KJH_EventScript_MasterAfter

KJH_EventScript_MasterFire::
	setvar VAR_0x8004, TRAINER_KJH_MASTER_FIRE
	call KJH_EventScript_MasterAsk
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_MasterEnd
	cleartrainerflag TRAINER_KJH_MASTER_FIRE
	trainerbattle_no_intro TRAINER_KJH_MASTER_FIRE, KJH_Text_MasterDefeat
	setvar VAR_0x8004, TRAINER_KJH_MASTER_FIRE
	goto KJH_EventScript_MasterAfter

KJH_EventScript_MasterElectric::
	setvar VAR_0x8004, TRAINER_KJH_MASTER_ELECTRIC
	call KJH_EventScript_MasterAsk
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_MasterEnd
	cleartrainerflag TRAINER_KJH_MASTER_ELECTRIC
	trainerbattle_no_intro TRAINER_KJH_MASTER_ELECTRIC, KJH_Text_MasterDefeat
	setvar VAR_0x8004, TRAINER_KJH_MASTER_ELECTRIC
	goto KJH_EventScript_MasterAfter

KJH_EventScript_MasterGhost::
	setvar VAR_0x8004, TRAINER_KJH_MASTER_GHOST
	call KJH_EventScript_MasterAsk
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_MasterEnd
	cleartrainerflag TRAINER_KJH_MASTER_GHOST
	trainerbattle_no_intro TRAINER_KJH_MASTER_GHOST, KJH_Text_MasterDefeat
	setvar VAR_0x8004, TRAINER_KJH_MASTER_GHOST
	goto KJH_EventScript_MasterAfter

KJH_EventScript_MasterIce::
	setvar VAR_0x8004, TRAINER_KJH_MASTER_ICE
	call KJH_EventScript_MasterAsk
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_MasterEnd
	cleartrainerflag TRAINER_KJH_MASTER_ICE
	trainerbattle_no_intro TRAINER_KJH_MASTER_ICE, KJH_Text_MasterDefeat
	setvar VAR_0x8004, TRAINER_KJH_MASTER_ICE
	goto KJH_EventScript_MasterAfter

KJH_EventScript_MasterBug::
	setvar VAR_0x8004, TRAINER_KJH_MASTER_BUG
	call KJH_EventScript_MasterAsk
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_MasterEnd
	cleartrainerflag TRAINER_KJH_MASTER_BUG
	trainerbattle_no_intro TRAINER_KJH_MASTER_BUG, KJH_Text_MasterDefeat
	setvar VAR_0x8004, TRAINER_KJH_MASTER_BUG
	goto KJH_EventScript_MasterAfter

KJH_EventScript_MasterRock::
	setvar VAR_0x8004, TRAINER_KJH_MASTER_ROCK
	call KJH_EventScript_MasterAsk
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_MasterEnd
	cleartrainerflag TRAINER_KJH_MASTER_ROCK
	trainerbattle_no_intro TRAINER_KJH_MASTER_ROCK, KJH_Text_MasterDefeat
	setvar VAR_0x8004, TRAINER_KJH_MASTER_ROCK
	goto KJH_EventScript_MasterAfter

KJH_EventScript_MasterFighting::
	setvar VAR_0x8004, TRAINER_KJH_MASTER_FIGHTING
	call KJH_EventScript_MasterAsk
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_MasterEnd
	cleartrainerflag TRAINER_KJH_MASTER_FIGHTING
	trainerbattle_no_intro TRAINER_KJH_MASTER_FIGHTING, KJH_Text_MasterDefeat
	setvar VAR_0x8004, TRAINER_KJH_MASTER_FIGHTING
	goto KJH_EventScript_MasterAfter

KJH_EventScript_MasterPoison::
	setvar VAR_0x8004, TRAINER_KJH_MASTER_POISON
	call KJH_EventScript_MasterAsk
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_MasterEnd
	cleartrainerflag TRAINER_KJH_MASTER_POISON
	trainerbattle_no_intro TRAINER_KJH_MASTER_POISON, KJH_Text_MasterDefeat
	setvar VAR_0x8004, TRAINER_KJH_MASTER_POISON
	goto KJH_EventScript_MasterAfter

KJH_EventScript_MasterGround::
	setvar VAR_0x8004, TRAINER_KJH_MASTER_GROUND
	call KJH_EventScript_MasterAsk
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_MasterEnd
	cleartrainerflag TRAINER_KJH_MASTER_GROUND
	trainerbattle_no_intro TRAINER_KJH_MASTER_GROUND, KJH_Text_MasterDefeat
	setvar VAR_0x8004, TRAINER_KJH_MASTER_GROUND
	goto KJH_EventScript_MasterAfter

KJH_EventScript_MasterNormal::
	setvar VAR_0x8004, TRAINER_KJH_MASTER_NORMAL
	call KJH_EventScript_MasterAsk
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_MasterEnd
	cleartrainerflag TRAINER_KJH_MASTER_NORMAL
	trainerbattle_no_intro TRAINER_KJH_MASTER_NORMAL, KJH_Text_MasterDefeat
	setvar VAR_0x8004, TRAINER_KJH_MASTER_NORMAL
	goto KJH_EventScript_MasterAfter

KJH_EventScript_MasterAsk::
	lock
	faceplayer
	special KJH_SpecialMasterFightsLeft
	goto_if_eq VAR_RESULT, 0, KJH_EventScript_MasterTired
	msgbox KJH_Text_MasterIntro, MSGBOX_YESNO
	return

KJH_EventScript_MasterTired::
	msgbox KJH_Text_MasterTired
	setvar VAR_RESULT, FALSE
	return

KJH_EventScript_MasterAfter::
	special KJH_SpecialMasterFought
	msgbox KJH_Text_MasterAfter
KJH_EventScript_MasterEnd::
	release
	end

KJH_Text_MasterIntro:
	.string "I'm a training master.\pA battle with me trains your moves\n"
	.string "of my type far more than any other.\pShall we train?$"

KJH_Text_MasterTired:
	.string "That's enough training for today.\n"
	.string "Come back tomorrow!$"

KJH_Text_MasterDefeat:
	.string "Well fought!\n"
	.string "Your moves of my type learned a lot.$"

KJH_Text_MasterAfter:
	.string "Train with me again sometime.\n"
	.string "Twice a day is plenty.$"
