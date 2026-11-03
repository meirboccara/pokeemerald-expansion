@ KJH (ENG-10): Indigo Plateau's seasons (docs/STORY.md). The Kanto League first; then, once the player holds the 8
@ Johto BADGES, the Johto League, where the Elite Four and the Champion use their rematch teams. Between the two the
@ door guard stays in front of the door. Becoming Champion in the Johto season makes the player Johto Champion.

@ Out: VAR_RESULT TRUE while the League is between seasons. Opens the Johto season (FLAG_KJH_JOHTO_LEAGUE_OPEN) once
@ the 8 Johto BADGES are in.
KJH_EventScript_IndigoLeagueSeason::
	goto_if_unset FLAG_SYS_GAME_CLEAR, KJH_EventScript_IndigoInSeason
	goto_if_set FLAG_KJH_JOHTO_LEAGUE_OPEN, KJH_EventScript_IndigoInSeason
	goto_if_unset FLAG_JOHTO_BADGE01_GET, KJH_EventScript_IndigoBetweenSeasons
	goto_if_unset FLAG_JOHTO_BADGE02_GET, KJH_EventScript_IndigoBetweenSeasons
	goto_if_unset FLAG_JOHTO_BADGE03_GET, KJH_EventScript_IndigoBetweenSeasons
	goto_if_unset FLAG_JOHTO_BADGE04_GET, KJH_EventScript_IndigoBetweenSeasons
	goto_if_unset FLAG_JOHTO_BADGE05_GET, KJH_EventScript_IndigoBetweenSeasons
	goto_if_unset FLAG_JOHTO_BADGE06_GET, KJH_EventScript_IndigoBetweenSeasons
	goto_if_unset FLAG_JOHTO_BADGE07_GET, KJH_EventScript_IndigoBetweenSeasons
	goto_if_unset FLAG_JOHTO_BADGE08_GET, KJH_EventScript_IndigoBetweenSeasons
	setflag FLAG_KJH_JOHTO_LEAGUE_OPEN
KJH_EventScript_IndigoInSeason::
	setvar VAR_RESULT, FALSE
	return

KJH_EventScript_IndigoBetweenSeasons::
	setvar VAR_RESULT, TRUE
	return

@ The Hall of Fame (before EnterHallOfFame): in the Johto season, the player becomes Johto Champion
KJH_EventScript_IndigoHallOfFame::
	call_if_set FLAG_KJH_JOHTO_LEAGUE_OPEN, KJH_EventScript_BecomeJohtoChampion
	return

KJH_EventScript_BecomeJohtoChampion::
	setflag FLAG_KJH_JOHTO_CHAMPION
	return

KJH_Text_IndigoBetweenSeasons::
	.string "Congratulations, CHAMPION!\p"
	.string "The ELITE FOUR are training for\n"
	.string "the JOHTO LEAGUE season.\p"
	.string "Come back when you hold all 8\n"
	.string "JOHTO BADGES. They'll be ready.$"
