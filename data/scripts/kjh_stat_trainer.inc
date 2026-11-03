@ KJH: the stat trainer, in a Pokemon Center (ENG-7, src/kjh_stat_trainer.c). Sets a party Pokemon's IVs, EVs or
@ nature exactly, or switches its ability (Hidden Ability included, data/scripts/kjh_hidden_ability.inc), for free.
KJH_EventScript_StatTrainer::
	lock
	faceplayer
	msgbox KJH_Text_StatTrainerIntro
KJH_EventScript_StatTrainerChooseMon::
	msgbox KJH_Text_StatTrainerWhichMon
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, KJH_EventScript_StatTrainerBye
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, KJH_EventScript_StatTrainerEgg
KJH_EventScript_StatTrainerChooseWhat::
	message KJH_Text_StatTrainerWhat
	waitmessage
	dynmultipush KJH_Text_StatTrainerIvs, KJH_STAT_TRAINER_IVS
	dynmultipush KJH_Text_StatTrainerEvs, KJH_STAT_TRAINER_EVS
	dynmultipush KJH_Text_StatTrainerNature, KJH_STAT_TRAINER_NATURE
	dynmultipush KJH_Text_StatTrainerAbility, KJH_STAT_TRAINER_ABILITY
	dynmultipush KJH_Text_StatTrainerCancel, KJH_STAT_TRAINER_CANCEL
	dynmultistack 0, 0, FALSE, 5, FALSE, 0, NULL
	goto_if_ge VAR_RESULT, KJH_STAT_TRAINER_CANCEL, KJH_EventScript_StatTrainerBye
	goto_if_eq VAR_RESULT, KJH_STAT_TRAINER_ABILITY, KJH_EventScript_StatTrainerAbility
	copyvar VAR_0x8005, VAR_RESULT
	call_if_ne VAR_0x8005, KJH_STAT_TRAINER_NATURE, KJH_EventScript_StatTrainerHelpStats
	call_if_eq VAR_0x8005, KJH_STAT_TRAINER_NATURE, KJH_EventScript_StatTrainerHelpNature
	callnative KJH_ScriptStatTrainerEdit, requests_effects=1, waitstate=1
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_StatTrainerChooseWhat
	goto_if_eq VAR_0x8005, KJH_STAT_TRAINER_NATURE, KJH_EventScript_StatTrainerNatureDone
	msgbox KJH_Text_StatTrainerDone
	goto KJH_EventScript_StatTrainerChooseWhat

KJH_EventScript_StatTrainerNatureDone::
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	msgbox KJH_Text_StatTrainerNatureDone
	goto KJH_EventScript_StatTrainerChooseWhat

KJH_EventScript_StatTrainerAbility::
	call KJH_EventScript_ChooseAbility
	goto KJH_EventScript_StatTrainerChooseWhat

KJH_EventScript_StatTrainerHelpStats::
	message KJH_Text_StatTrainerHelpStats
	waitmessage
	return

KJH_EventScript_StatTrainerHelpNature::
	message KJH_Text_StatTrainerHelpNature
	waitmessage
	return

KJH_EventScript_StatTrainerEgg::
	msgbox KJH_Text_AbilityEgg
	goto KJH_EventScript_StatTrainerChooseMon

KJH_EventScript_StatTrainerBye::
	msgbox KJH_Text_StatTrainerBye
	release
	end

KJH_Text_StatTrainerIntro::
	.string "I'm a STAT TRAINER!\p"
	.string "I can shape a POKéMON's IVs, EVs and\n"
	.string "nature exactly the way you want.\p"
	.string "I can also switch its ability, even\n"
	.string "to a rare HIDDEN ABILITY.\l"
	.string "And it's free!$"

KJH_Text_StatTrainerWhichMon::
	.string "Which POKéMON should I train?$"

KJH_Text_StatTrainerWhat::
	.string "What should I change?$"

KJH_Text_StatTrainerIvs::
	.string "IVs$"

KJH_Text_StatTrainerEvs::
	.string "EVs$"

KJH_Text_StatTrainerNature::
	.string "NATURE$"

KJH_Text_StatTrainerAbility::
	.string "ABILITY$"

KJH_Text_StatTrainerCancel::
	.string "CANCEL$"

KJH_Text_StatTrainerHelpStats::
	.string "{DPAD_LEFTRIGHT}-/+1  SELECT/START: -/+10\n"
	.string "{DPAD_UPDOWN}PICK  {A_BUTTON}SAVE  {B_BUTTON}CANCEL$"

KJH_Text_StatTrainerHelpNature::
	.string "{DPAD_LEFTRIGHT}NATURE\n"
	.string "{A_BUTTON}SAVE  {B_BUTTON}CANCEL$"

KJH_Text_StatTrainerDone::
	.string "Done! Its stats are set.$"

KJH_Text_StatTrainerNatureDone::
	.string "Done! {STR_VAR_1} has a new nature.$"

KJH_Text_StatTrainerBye::
	.string "Come back any time!$"
