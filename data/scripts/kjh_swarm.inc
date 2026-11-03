@ KJH (CF-5): the swarm reporter, one in each Kanto Pokemon Center. Names today's swarm (src/kjh_swarms.c).
EventScript_KjhSwarmReporter::
	lock
	faceplayer
	dotimebasedevents @ a day that just turned over gets its swarm first (the periodic check runs about once a minute)
	specialvar VAR_RESULT, KJH_BufferTodaysSwarm
	goto_if_eq VAR_RESULT, FALSE, EventScript_KjhSwarmReporterNone
	msgbox Text_KjhSwarmToday
	release
	end

EventScript_KjhSwarmReporterNone::
	msgbox Text_KjhNoSwarmToday
	release
	end

Text_KjhSwarmToday::
	.string "I heard there's a swarm of\n"
	.string "{STR_VAR_1} on {STR_VAR_2} today!$"

Text_KjhNoSwarmToday::
	.string "No word of a swarm anywhere\n"
	.string "today. Maybe tomorrow!$"
