@ KJH (LV-2): the team's level went up, on the first step in a further zone or after a badge (src/kjh_team_level.c).
EventScript_KjhTeamFeelsStronger::
	lockall
	msgbox Text_KjhTeamFeelsStronger
	releaseall
	end

Text_KjhTeamFeelsStronger::
	.string "Your team feels stronger!$"
