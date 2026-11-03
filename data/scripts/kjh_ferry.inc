@ KJH (ENG-10): the S.S. AQUA between Kanto, Johto and Hoenn (docs/STORY.md). Regions open in order: Johto once the
@ player is Kanto Champion, Hoenn (from Olivine) once Johto Champion. The first trip to Johto lands in NEW BARK TOWN,
@ where PROF. ELM's story begins, with Crystal's world set up as its bedroom does for a new game; later trips land at
@ OLIVINE PORT. The first trip to Hoenn lands in SLATEPORT, where the moving truck takes the player home to LITTLEROOT
@ and Emerald's own opening plays (kjh_hoenn_story.c); later trips land in Slateport's harbor. Once a region is
@ reached, every port sails to it. The pokefirered tree's "journey partner" choice is not ported: with levels that
@ follow the zones it isn't needed for balance (docs/LEVELLESS_DESIGN.md §10).
KJH_EventScript_VermilionFerry::
	lock
	faceplayer
	textcolor NPC_TEXT_COLOR_MALE
	goto_if_unset FLAG_SYS_GAME_CLEAR, KJH_EventScript_FerryNeedKantoLeague
	goto_if_set FLAG_KJH_HOENN_ARRIVED, KJH_EventScript_VermilionFerryChoice
	msgbox KJH_Text_FerryToJohto, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, KJH_EventScript_FerryDecline
KJH_EventScript_FerryToJohtoFromKanto::
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

@ Kanto's port, once Hoenn is reached: Johto or Hoenn
KJH_EventScript_VermilionFerryChoice::
	message KJH_Text_FerryWhere
	waitmessage
	dynmultichoice 19, 1, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, KJH_Text_FerryJohto, KJH_Text_FerryHoenn, KJH_Text_FerryCancel
	goto_if_eq VAR_RESULT, 0, KJH_EventScript_FerryToJohtoFromKanto
	goto_if_eq VAR_RESULT, 1, KJH_EventScript_SailToSlateport
	goto KJH_EventScript_FerryDecline

@ Johto's port: back to Kanto; Hoenn once the player is Johto Champion
KJH_EventScript_OlivineFerry::
	lock
	faceplayer
	textcolor NPC_TEXT_COLOR_MALE
	goto_if_set FLAG_KJH_JOHTO_CHAMPION, KJH_EventScript_OlivineFerryChoice
	goto_if_set FLAG_KJH_HOENN_ARRIVED, KJH_EventScript_OlivineFerryChoice
	msgbox KJH_Text_FerryToKanto, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, KJH_EventScript_FerryDecline
	goto KJH_EventScript_SailToVermilion

KJH_EventScript_OlivineFerryChoice::
	message KJH_Text_FerryWhere
	waitmessage
	dynmultichoice 19, 1, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, KJH_Text_FerryHoenn, KJH_Text_FerryKanto, KJH_Text_FerryCancel
	goto_if_eq VAR_RESULT, 0, KJH_EventScript_FerryToHoenn
	goto_if_eq VAR_RESULT, 1, KJH_EventScript_SailToVermilion
	goto KJH_EventScript_FerryDecline

@ The Johto Champion's first trip: Hoenn is reached, and Slateport's harbor sends the player home (SlateportCity_Harbor)
KJH_EventScript_FerryToHoenn::
	goto_if_set FLAG_KJH_HOENN_ARRIVED, KJH_EventScript_SailToSlateport
	msgbox KJH_Text_FirstHoennTrip
	setflag FLAG_KJH_HOENN_ARRIVED
	setvar VAR_KJH_HOENN_ARRIVAL_STATE, 1
	call KJH_EventScript_SetSail
	warp MAP_SLATEPORT_CITY_HARBOR, 13, 12
	waitstate
	release
	end

KJH_EventScript_SailToSlateport::
	msgbox KJH_Text_AllAboard
	call KJH_EventScript_SetSail
	warp MAP_SLATEPORT_CITY_HARBOR, 13, 12
	waitstate
	release
	end

KJH_EventScript_SailToVermilion::
	msgbox KJH_Text_AllAboard
	call KJH_EventScript_SetSail
	warp MAP_VERMILION_CITY, 23, 32
	waitstate
	release
	end

@ Hoenn's port, Slateport's harbor: back to Johto or Kanto
KJH_EventScript_SlateportFerry::
	lock
	faceplayer
	textcolor NPC_TEXT_COLOR_MALE
	message KJH_Text_FerryWhere
	waitmessage
	dynmultichoice 19, 1, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, KJH_Text_FerryJohto, KJH_Text_FerryKanto, KJH_Text_FerryCancel
	goto_if_eq VAR_RESULT, 0, KJH_EventScript_SailToOlivine
	goto_if_eq VAR_RESULT, 1, KJH_EventScript_SailToVermilion
	goto KJH_EventScript_FerryDecline

@ The first landing (SlateportCity_Harbor's frame script): a message from Mom, then the moving truck home to Littleroot,
@ where Emerald's opening plays as in a new game (kjh_hoenn_story.c)
KJH_EventScript_HoennArrival::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	msgbox KJH_Text_HoennArrival
	closemessage
	setvar VAR_KJH_HOENN_ARRIVAL_STATE, 2
	special KJH_RideMovingTruck
	waitstate
	releaseall
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

KJH_Text_FerryWhere::
	.string "Ahoy! Where would you like to\n"
	.string "sail on the S.S. AQUA?$"

KJH_Text_FerryJohto::
	.string "JOHTO$"

KJH_Text_FerryHoenn::
	.string "HOENN$"

KJH_Text_FerryKanto::
	.string "KANTO$"

KJH_Text_FerryCancel::
	.string "CANCEL$"

KJH_Text_FirstHoennTrip::
	.string "The JOHTO CHAMPION! Then you're\n"
	.string "ready for HOENN, the last region.\p"
	.string "Word is, TEAM ROCKET's BOSS was\n"
	.string "seen boarding a ship south…\p"
	.string "We land at SLATEPORT. PROF. BIRCH\n"
	.string "lives down the coast, in LITTLEROOT.\p"
	.string "Win HOENN's 8 BADGES and the\n"
	.string "HOENN LEAGUE will be waiting!$"

KJH_Text_HoennArrival::
	.string "SAILOR: Land ho! SLATEPORT CITY,\n"
	.string "HOENN!\p"
	.string "Oh, and a message came for you\n"
	.string "over the ship's radio. It's from\l"
	.string "your MOM!\p"
	.string "“Welcome to HOENN, honey!\n"
	.string "While you were in JOHTO, we moved\l"
	.string "to LITTLEROOT TOWN.\p"
	.string "Our moving truck is waiting at the\n"
	.string "harbor. Ride home with our things!”\p"
	.string "Well, off you go, CHAMPION!$"

KJH_Text_AllAboard::
	.string "All aboard! Bon voyage!$"

KJH_Text_FerryDecline::
	.string "Come back whenever you're ready\n"
	.string "to travel.$"
