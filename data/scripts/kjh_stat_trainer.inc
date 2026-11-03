@ KJH: the stat trainer, in a Pokemon Center (ENG-7, src/kjh_stat_trainer.c). Sets a party Pokemon's IVs, EVs or
@ nature exactly, or switches its ability (Hidden Ability included, data/scripts/kjh_hidden_ability.inc), for free.
@ LV-8, in the levels-free game: EVs are Training points, which he puts back in the bank (a free full reset); IVs
@ only from Bond 20; the Hidden Ability only from Bond 12 (peak Bonds).
KJH_EventScript_StatTrainer::
	lock
	faceplayer
	goto_if_set FLAG_KJH_LEVELLESS, KJH_EventScript_StatTrainerIntroLevelsFree
	msgbox KJH_Text_StatTrainerIntro
	goto KJH_EventScript_StatTrainerChooseMon

KJH_EventScript_StatTrainerIntroLevelsFree::
	msgbox KJH_Text_StatTrainerIntroLevelsFree
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
	call_if_unset FLAG_KJH_LEVELLESS, KJH_EventScript_StatTrainerPushEvs
	call_if_set FLAG_KJH_LEVELLESS, KJH_EventScript_StatTrainerPushPoints
	dynmultipush KJH_Text_StatTrainerNature, KJH_STAT_TRAINER_NATURE
	dynmultipush KJH_Text_StatTrainerAbility, KJH_STAT_TRAINER_ABILITY
	dynmultipush KJH_Text_StatTrainerCancel, KJH_STAT_TRAINER_CANCEL
	dynmultistack 0, 0, FALSE, 5, FALSE, 0, NULL
	goto_if_ge VAR_RESULT, KJH_STAT_TRAINER_CANCEL, KJH_EventScript_StatTrainerBye
	goto_if_eq VAR_RESULT, KJH_STAT_TRAINER_ABILITY, KJH_EventScript_StatTrainerAbility
	copyvar VAR_0x8005, VAR_RESULT
	goto_if_unset FLAG_KJH_LEVELLESS, KJH_EventScript_StatTrainerEdit
	goto_if_eq VAR_0x8005, KJH_STAT_TRAINER_EVS, KJH_EventScript_StatTrainerResetPoints
	goto_if_ne VAR_0x8005, KJH_STAT_TRAINER_IVS, KJH_EventScript_StatTrainerEdit
	callnative KJH_ScriptCanTrainIvs, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_StatTrainerIvsNeedBond
KJH_EventScript_StatTrainerEdit::
	call_if_ne VAR_0x8005, KJH_STAT_TRAINER_NATURE, KJH_EventScript_StatTrainerHelpStats
	call_if_eq VAR_0x8005, KJH_STAT_TRAINER_NATURE, KJH_EventScript_StatTrainerHelpNature
	callnative KJH_ScriptStatTrainerEdit, requests_effects=1, waitstate=1
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_StatTrainerChooseWhat
	goto_if_eq VAR_0x8005, KJH_STAT_TRAINER_NATURE, KJH_EventScript_StatTrainerNatureDone
	msgbox KJH_Text_StatTrainerDone
	goto KJH_EventScript_StatTrainerChooseWhat

KJH_EventScript_StatTrainerPushEvs::
	dynmultipush KJH_Text_StatTrainerEvs, KJH_STAT_TRAINER_EVS
	return

KJH_EventScript_StatTrainerPushPoints::
	dynmultipush KJH_Text_StatTrainerPoints, KJH_STAT_TRAINER_EVS
	return

KJH_EventScript_StatTrainerIvsNeedBond::
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	msgbox KJH_Text_StatTrainerIvsNeedBond
	goto KJH_EventScript_StatTrainerChooseWhat

KJH_EventScript_StatTrainerResetPoints::
	callnative KJH_ScriptBufferPlacedPoints, requests_effects=1
	goto_if_eq VAR_RESULT, 0, KJH_EventScript_StatTrainerNoPoints
	msgbox KJH_Text_StatTrainerResetPoints, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, KJH_EventScript_StatTrainerChooseWhat
	callnative KJH_ScriptResetTrainingPoints, requests_effects=1
	msgbox KJH_Text_StatTrainerPointsReset
	goto KJH_EventScript_StatTrainerChooseWhat

KJH_EventScript_StatTrainerNoPoints::
	msgbox KJH_Text_StatTrainerNoPoints
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

KJH_Text_StatTrainerIntroLevelsFree::
	.string "I'm a STAT TRAINER!\p"
	.string "I can take back the TRAINING POINTS\n"
	.string "a POKéMON placed, to try a new build.\p"
	.string "I can change its nature, and switch\n"
	.string "its ability.\p"
	.string "With a BOND of 12, even to its HIDDEN\n"
	.string "ABILITY. With a BOND of 20, I can\l"
	.string "shape its IVs too.\p"
	.string "And it's all free!$"

KJH_Text_StatTrainerPoints::
	.string "POINTS$"

KJH_Text_StatTrainerIvsNeedBond::
	.string "{STR_VAR_1} and you aren't close\n"
	.string "enough yet.\p"
	.string "I shape IVs from a BOND of 20.$"

KJH_Text_StatTrainerResetPoints::
	.string "{STR_VAR_1} placed {STR_VAR_2} TRAINING\n"
	.string "POINTS. Take them all back?$"

KJH_Text_StatTrainerPointsReset::
	.string "Done! {STR_VAR_1}'s points are back.\n"
	.string "Place them again from its SUMMARY.$"

KJH_Text_StatTrainerNoPoints::
	.string "{STR_VAR_1} hasn't placed any\n"
	.string "TRAINING POINTS yet.$"

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
