@ KJH (CF-8): a headbutt tree, marked by a sign bg_event on the tree. From the Cascade Badge, a party Pokemon that
@ could learn Headbutt can shake it (no teaching); a Pokemon of the map's headbutt_mons table may fall out.
@ "Could learn": its level-up moves or its teachable moves. This line makes tools/learnset_helpers/make_tutors.py
@ count Headbutt as a tutor move, so every species that learns it in some game (all_learnables.json) has it:
@ move_tutor MOVE_HEADBUTT
EventScript_HeadbuttTree::
	lockall
	specialvar VAR_RESULT, KJH_GetHeadbuttPartySlot
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_HeadbuttTreeCantUse
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	msgbox Text_HeadbuttTreeAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_HeadbuttTreeEnd
	msgbox Text_HeadbuttTreeUsed, MSGBOX_DEFAULT
	closemessage
	playse SE_M_HEADBUTT
	waitse
	special KJH_HeadbuttWildEncounter
	goto_if_eq VAR_RESULT, FALSE, EventScript_HeadbuttTreeNothing
	waitstate
	releaseall
	end

EventScript_HeadbuttTreeNothing::
	msgbox Text_HeadbuttTreeNothing, MSGBOX_DEFAULT
EventScript_HeadbuttTreeEnd::
	releaseall
	end

EventScript_HeadbuttTreeCantUse::
	msgbox Text_HeadbuttTreeCouldShake, MSGBOX_DEFAULT
	releaseall
	end

Text_HeadbuttTreeCouldShake::
	.string "A POKéMON could be in this tree.\n"
	.string "It looks like it could be shaken.$"

Text_HeadbuttTreeAsk::
	.string "A POKéMON could be in this tree.\n"
	.string "Want {STR_VAR_1} to use HEADBUTT?$"

Text_HeadbuttTreeUsed::
	.string "{STR_VAR_1} used HEADBUTT!$"

Text_HeadbuttTreeNothing::
	.string "Nope. Nothing…$"
