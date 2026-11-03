@ KJH (LV-2): the team's level went up, on the first step in a further zone or after a badge (src/kjh_team_level.c).
EventScript_KjhTeamFeelsStronger::
	lockall
	msgbox Text_KjhTeamFeelsStronger
	call EventScript_KjhLibraryNewMoves @ LV-10: "CHARMELEON can now use SLASH, FLAMETHROWER..."
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
