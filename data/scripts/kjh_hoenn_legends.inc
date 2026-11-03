@ KJH: Hoenn's set-place legendaries on Emerald's native maps (ENG-10, CF-13; docs/LEGENDARIES.md in the KJH repo),
@ ported from pokefirered's data/scripts/kjh_legends.inc. No roamers in KJH (rule 1): Latias and Latios are static
@ outside Sky Pillar. Each fights as a legendary boss (CF-12's rule). Beaten or caught, it is gone; after running away
@ it stays. The Regis and Rayquaza keep Emerald's own scripts, with KJH's levels and gates (their maps' scripts.inc).

@ Cave of Origin B1F: Groudon and Kyogre wait there once the showdown at the entrance is won (agent hoenn-story's
@ FLAG_KJH_HOENN_SHOWDOWN_DONE); before that, nothing is there. Emerald's FLAG_DEFEATED_GROUDON / _KYOGRE say it is
@ gone (beaten or caught), as in Emerald's Terra and Marine Caves, which KJH never opens.
KJH_EventScript_CaveOfOriginB1F_OnTransition::
	setflag FLAG_KJH_HIDE_GROUDON
	setflag FLAG_KJH_HIDE_KYOGRE
	goto_if_unset FLAG_KJH_HOENN_SHOWDOWN_DONE, Common_EventScript_NopReturn
	call_if_unset FLAG_DEFEATED_GROUDON, KJH_EventScript_ShowGroudon
	call_if_unset FLAG_DEFEATED_KYOGRE, KJH_EventScript_ShowKyogre
	return

KJH_EventScript_ShowGroudon::
	clearflag FLAG_KJH_HIDE_GROUDON
	return

KJH_EventScript_ShowKyogre::
	clearflag FLAG_KJH_HIDE_KYOGRE
	return

KJH_EventScript_Legend_GROUDON::
	lock
	setvar VAR_0x8004, SPECIES_GROUDON
	setwildbattle SPECIES_GROUDON, 95
	call KJH_EventScript_HoennLegendBattle
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_HoennLegendStays
	setflag FLAG_DEFEATED_GROUDON
	goto KJH_EventScript_HoennLegendGone

KJH_EventScript_Legend_KYOGRE::
	lock
	setvar VAR_0x8004, SPECIES_KYOGRE
	setwildbattle SPECIES_KYOGRE, 95
	call KJH_EventScript_HoennLegendBattle
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_HoennLegendStays
	setflag FLAG_DEFEATED_KYOGRE
	goto KJH_EventScript_HoennLegendGone

@ Outside Sky Pillar: Latias and Latios, awake with the 8 Hoenn badges
KJH_EventScript_Legend_LATIAS::
	lock
	goto_if_unset FLAG_BADGE08_GET, KJH_EventScript_HoennLegendSleeps
	setvar VAR_0x8004, SPECIES_LATIAS
	setwildbattle SPECIES_LATIAS, 92
	goto KJH_EventScript_HoennLegendStatic

KJH_EventScript_Legend_LATIOS::
	lock
	goto_if_unset FLAG_BADGE08_GET, KJH_EventScript_HoennLegendSleeps
	setvar VAR_0x8004, SPECIES_LATIOS
	setwildbattle SPECIES_LATIOS, 92
	goto KJH_EventScript_HoennLegendStatic

KJH_EventScript_HoennLegendStatic::
	call KJH_EventScript_HoennLegendBattle
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_HoennLegendStays
	goto KJH_EventScript_HoennLegendGone

@ VAR_0x8004: its species; setwildbattle has made it. VAR_RESULT: TRUE when it was beaten or caught
KJH_EventScript_HoennLegendBattle::
	waitse
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	kjh_legendaryboss @ KJH (CF-13): the legendary boss rule
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, KJH_EventScript_HoennLegendBeaten
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, KJH_EventScript_HoennLegendBeaten
	setvar VAR_RESULT, FALSE
	return

KJH_EventScript_HoennLegendBeaten::
	setvar VAR_RESULT, TRUE
	return

KJH_EventScript_HoennLegendGone::
	removeobject VAR_LAST_TALKED
	release
	end

KJH_EventScript_HoennLegendStays::
	release
	end

KJH_EventScript_HoennLegendSleeps::
	msgbox KJH_Text_HoennLegendSleeps
	release
	end

@ Sky Pillar's top (Emerald's SkyPillar_Top_EventScript_Rayquaza, lockall): Rayquaza is the Hoenn finale
KJH_EventScript_RayquazaSleeps::
	msgbox KJH_Text_HoennLegendSleeps
	releaseall
	end

@ With the 8th Hoenn badge Rayquaza waits on the top, whether or not Emerald's Sootopolis story put it back there
@ (VAR_SKY_PILLAR_STATE 2); its awakening scene, which starts that story, can't play any more
KJH_EventScript_RayquazaOnTop::
	goto_if_ge VAR_SKY_PILLAR_STATE, 2, Common_EventScript_NopReturn
	setvar VAR_SKY_PILLAR_STATE, 2
	setvar VAR_SKY_PILLAR_RAYQUAZA_CRY_DONE, 1
	setflag FLAG_HIDE_SKY_PILLAR_TOP_RAYQUAZA @ the sleeping one, gone in its scene
	return

KJH_Text_HoennLegendSleeps::
	.string "It's fast asleep, deep in its\n"
	.string "ancient slumber…\p"
	.string "Only a TRAINER who holds all 8\n"
	.string "HOENN BADGES could wake it.$"
