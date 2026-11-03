@ KJH (LV-2): the team's level went up, on the first step in a further zone or after a badge (src/kjh_team_level.c).
EventScript_KjhTeamFeelsStronger::
	lockall
	msgbox Text_KjhTeamFeelsStronger
	call EventScript_KjhLibraryNewMoves @ LV-10: "CHARMELEON can now use SLASH, FLAMETHROWER..."
	call EventScript_KjhOfferEvolutions @ LV-9: "CHARMANDER is ready to evolve. Evolve now?"
	releaseall
	end

Text_KjhTeamFeelsStronger::
	.string "Your team feels stronger!$"

@ KJH (LV-10): after a level rise (VAR_0x8005 the old team level, VAR_0x8006 the new one), each party Pokemon with
@ new level-up moves in its library lists them (src/kjh_move_library.c, KJH_BufferNextNewLibraryMoves)
EventScript_KjhLibraryNewMoves::
	setvar VAR_0x8004, 0
EventScript_KjhLibraryNewMovesLoop:
	specialvar VAR_RESULT, KJH_BufferNextNewLibraryMoves
	goto_if_eq VAR_RESULT, FALSE, EventScript_KjhLibraryNewMovesEnd
	msgbox gStringVar4
	goto EventScript_KjhLibraryNewMovesLoop
EventScript_KjhLibraryNewMovesEnd:
	return

@ KJH (LV-9): after a level rise (VAR_0x8005 the old team level), each party Pokemon the rise made ready to evolve is
@ offered the evolution (src/kjh_evolution.c); NO leaves it for the party menu's EVOLVE. After a badge the team's level
@ rises on the next step, so this is the post-Gym scene.
EventScript_KjhOfferEvolutions::
	setvar VAR_0x8004, 0
EventScript_KjhOfferEvolutionsLoop:
	specialvar VAR_RESULT, KJH_BufferNextRiseEvolution
	goto_if_eq VAR_RESULT, FALSE, EventScript_KjhOfferEvolutionsEnd
	msgbox Text_KjhReadyToEvolve, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_KjhOfferEvolutionsNext
	closemessage
	specialvar VAR_RESULT, KJH_EvolveFromScript
	goto_if_eq VAR_RESULT, FALSE, EventScript_KjhOfferEvolutionsNext
	waitstate
EventScript_KjhOfferEvolutionsNext:
	addvar VAR_0x8004, 1
	goto EventScript_KjhOfferEvolutionsLoop
EventScript_KjhOfferEvolutionsEnd:
	return

Text_KjhReadyToEvolve::
	.string "{STR_VAR_1} is ready to evolve.\nEvolve now?$"
