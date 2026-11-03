@ KJH: switching a Pokemon's ability, its Hidden Ability included (ENG-7, src/kjh_hidden_ability.c,
@ docs/HIDDEN_ABILITIES.md in the KJH repo). The player picks it from the Pokemon's abilities: first, second and
@ Hidden. Prof. Oak does it once the player has 4 badges in one region; a woman in a Fuchsia City house does it from
@ the start. The stat trainer (KJH_EventScript_ChooseAbility) does it too.

@ Oak's talk scripts call this after his own lines, before their release
KJH_EventScript_ProfessorAbility::
	callnative KJH_ScriptIsAbilitySwitchUnlocked, requests_effects=1
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_AbilityReturn
	faceplayer
	msgbox KJH_Text_ProfessorAbility, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, KJH_EventScript_AbilityReturn
	call KJH_EventScript_ChooseMonAndSwitchAbility
	msgbox KJH_Text_ProfessorAbilityBye
	return

KJH_EventScript_AbilityNpc::
	lock
	faceplayer
	msgbox KJH_Text_AbilityNpc, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, KJH_EventScript_AbilityNpcBye
	call KJH_EventScript_ChooseMonAndSwitchAbility
KJH_EventScript_AbilityNpcBye::
	msgbox KJH_Text_AbilityNpcBye
	release
	end

KJH_EventScript_ChooseMonAndSwitchAbility::
	msgbox KJH_Text_AbilityWhichMon
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, KJH_EventScript_AbilityReturn
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, KJH_EventScript_AbilityEgg
	goto KJH_EventScript_ChooseAbility

KJH_EventScript_AbilityEgg::
	msgbox KJH_Text_AbilityEgg
KJH_EventScript_AbilityReturn::
	return

@ The player picks the ability of the party Pokemon VAR_0x8004 (first, second or Hidden); B keeps it
KJH_EventScript_ChooseAbility::
	callnative KJH_ScriptBufferAbilityChoices, requests_effects=1
	goto_if_eq VAR_RESULT, 1, KJH_EventScript_OnlyOneAbility
	message KJH_Text_WhichAbility
	waitmessage
	goto_if_eq VAR_RESULT, 2, KJH_EventScript_ChooseAbility2
	dynmultipush gStringVar1, 0
	dynmultipush gStringVar2, 1
	dynmultipush gStringVar3, 2
	dynmultistack 0, 0, FALSE, 3, FALSE, 0, NULL
	goto KJH_EventScript_AbilityChosen

KJH_EventScript_ChooseAbility2::
	dynmultipush gStringVar1, 0
	dynmultipush gStringVar2, 1
	dynmultistack 0, 0, FALSE, 2, FALSE, 0, NULL
KJH_EventScript_AbilityChosen::
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, KJH_EventScript_AbilityReturn
	copyvar VAR_0x8005, VAR_RESULT
	callnative KJH_ScriptSetChosenAbility, requests_effects=1
	goto_if_eq VAR_RESULT, KJH_ABILITY_SAME, KJH_EventScript_SameAbility
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	goto_if_eq VAR_RESULT, KJH_ABILITY_HIDDEN, KJH_EventScript_HiddenAbilityDone
	msgbox KJH_Text_AbilityDone
	return

KJH_EventScript_HiddenAbilityDone::
	msgbox KJH_Text_HiddenAbilityDone
	return

KJH_EventScript_SameAbility::
	msgbox KJH_Text_SameAbility
	return

KJH_EventScript_OnlyOneAbility::
	msgbox KJH_Text_OnlyOneAbility
	return

KJH_Text_ProfessorAbility::
	.string "Oh, and with your BADGES, you're\n"
	.string "ready for my latest research.\p"
	.string "I can give a POKéMON any of its\n"
	.string "abilities, even its rare\l"
	.string "HIDDEN ABILITY.\p"
	.string "Shall I change one?$"

KJH_Text_ProfessorAbilityBye::
	.string "Come back whenever you like!$"

KJH_Text_AbilityNpc::
	.string "Every POKéMON hides more than one\n"
	.string "talent. I can draw out any of its\l"
	.string "abilities, even a HIDDEN ABILITY.\p"
	.string "Shall I change one?$"

KJH_Text_AbilityNpcBye::
	.string "Come back any time.$"

KJH_Text_AbilityWhichMon::
	.string "Which POKéMON?$"

KJH_Text_AbilityEgg::
	.string "An EGG? Let it hatch first!$"

KJH_Text_WhichAbility::
	.string "Which ability should it have?$"

KJH_Text_AbilityDone::
	.string "There! {STR_VAR_1} has a new ability.$"

KJH_Text_HiddenAbilityDone::
	.string "There! {STR_VAR_1} has its\n"
	.string "HIDDEN ABILITY now!$"

KJH_Text_SameAbility::
	.string "It already has that ability.$"

KJH_Text_OnlyOneAbility::
	.string "This POKéMON has only one\n"
	.string "ability. I can't change it.$"
