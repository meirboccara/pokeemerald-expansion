@ KJH (ENG-10): the S.S. AQUA between Kanto and Johto (docs/STORY.md). Regions open in order: Johto once the player is
@ Kanto Champion. The first trip lands in NEW BARK TOWN, where PROF. ELM's story begins, with Crystal's world set up as
@ its bedroom does for a new game; later trips land at OLIVINE PORT. Olivine sails back to Vermilion. Hoenn comes with
@ ENG-9's second step. The pokefirered tree's "journey partner" choice is not ported: with levels that follow the zones
@ it isn't needed for balance (docs/LEVELLESS_DESIGN.md §10).
KJH_EventScript_VermilionFerry::
	lock
	faceplayer
	textcolor NPC_TEXT_COLOR_MALE
	goto_if_unset FLAG_SYS_GAME_CLEAR, KJH_EventScript_FerryNeedKantoLeague
	msgbox KJH_Text_FerryToJohto, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, KJH_EventScript_FerryDecline
	goto_if_set FLAG_KJH_JOHTO_ARRIVED, KJH_EventScript_SailToOlivine
	msgbox KJH_Text_FirstJohtoTrip
	call_if_unset FLAG_J_INITIALIZED_EVENTS, J_InitializeEventsScript
	setflag FLAG_KJH_HIDE_OLIVINE_ADMINS
	setflag FLAG_KJH_JOHTO_ARRIVED
	call KJH_EventScript_SetSail
	warp MAP_JOHTO_NEW_BARK_TOWN, 13, 6
	waitstate
	release
	end

KJH_EventScript_SailToOlivine::
	msgbox KJH_Text_AllAboard
	call KJH_EventScript_SetSail
	warp MAP_JOHTO_OLIVINE_PORT, 8, 15
	waitstate
	release
	end

KJH_EventScript_OlivineFerry::
	lock
	faceplayer
	textcolor NPC_TEXT_COLOR_MALE
	msgbox KJH_Text_FerryToKanto, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, KJH_EventScript_FerryDecline
	msgbox KJH_Text_AllAboard
	call KJH_EventScript_SetSail
	warp MAP_VERMILION_CITY, 23, 32
	waitstate
	release
	end

@ The ship's horn, then the screen fades out before the warp
KJH_EventScript_SetSail::
	closemessage
	playse SE_RG_SS_ANNE_HORN
	fadescreen FADE_TO_BLACK
	return

KJH_EventScript_FerryNeedKantoLeague::
	msgbox KJH_Text_FerryNeedKantoLeague
	release
	end

KJH_EventScript_FerryDecline::
	msgbox KJH_Text_FerryDecline
	release
	end

KJH_Text_FerryToJohto::
	.string "Ahoy! The S.S. AQUA sails to\n"
	.string "JOHTO. Coming aboard?$"

KJH_Text_FerryToKanto::
	.string "Ahoy! The S.S. AQUA sails back to\n"
	.string "VERMILION CITY in KANTO.\p"
	.string "Coming aboard?$"

KJH_Text_FerryNeedKantoLeague::
	.string "Sorry, the ship to JOHTO only takes\n"
	.string "the CHAMPION of the KANTO LEAGUE.\p"
	.string "Win at the INDIGO PLATEAU first,\n"
	.string "then come back!$"

KJH_Text_FirstJohtoTrip::
	.string "The KANTO CHAMPION! Then you're\n"
	.string "ready for JOHTO.\p"
	.string "They say TEAM ROCKET's leftovers\n"
	.string "are gathering over there…\p"
	.string "We'll drop you off at NEW BARK\n"
	.string "TOWN. PROF. ELM lives there.\p"
	.string "Win JOHTO's 8 BADGES and the\n"
	.string "JOHTO LEAGUE will be waiting!$"

KJH_Text_AllAboard::
	.string "All aboard! Bon voyage!$"

KJH_Text_FerryDecline::
	.string "Come back whenever you're ready\n"
	.string "to travel.$"
