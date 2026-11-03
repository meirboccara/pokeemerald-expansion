@ KJH: Tin Tower 1F's Raikou and Entei (ENG-10, docs/LEGENDARIES.md in the KJH repo): no roamers in KJH, so they are
@ static encounters beside Suicune, awake once the player has faced Suicune (FLAG_J_FOUGHT_SUICUNE), Lv 75, ported
@ from pokefirered's data/scripts/kjh_legends.inc. Each fights as a legendary boss (CF-12's rule, CF-13). Beaten or
@ caught, it is gone (its object's flag, FLAG_KJH_HIDE_RAIKOU / _ENTEI); after running away it stays.
KJH_EventScript_Legend_RAIKOU::
	lock
	setvar VAR_0x8004, SPECIES_RAIKOU
	setwildbattle SPECIES_RAIKOU, 75
	goto KJH_EventScript_JohtoBeast

KJH_EventScript_Legend_ENTEI::
	lock
	setvar VAR_0x8004, SPECIES_ENTEI
	setwildbattle SPECIES_ENTEI, 75
	goto KJH_EventScript_JohtoBeast

@ VAR_0x8004: its species; setwildbattle has made it
KJH_EventScript_JohtoBeast::
	goto_if_unset FLAG_J_FOUGHT_SUICUNE, KJH_EventScript_JohtoLegendSleeps
	waitse
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	kjh_legendaryboss @ KJH (CF-13): the legendary boss rule
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, KJH_EventScript_JohtoBeastGone
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, KJH_EventScript_JohtoBeastGone
	release
	end

KJH_EventScript_JohtoBeastGone::
	removeobject VAR_LAST_TALKED
	release
	end

KJH_EventScript_JohtoLegendSleeps::
	msgbox KJH_Text_JohtoLegendSleeps
	release
	end

KJH_Text_JohtoLegendSleeps::
	.string "It watches you calmly…\p"
	.string "It seems to be waiting for\n"
	.string "SUICUNE's chosen TRAINER.$"
