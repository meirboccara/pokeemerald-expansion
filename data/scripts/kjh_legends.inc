@ KJH: Tin Tower 1F's Raikou and Entei (ENG-10, docs/LEGENDARIES.md in the KJH repo): no roamers in KJH, so they are
@ static encounters beside Suicune, awake once the player has faced Suicune (FLAG_J_FOUGHT_SUICUNE), Lv 75, ported
@ from pokefirered's data/scripts/kjh_legends.inc. Each fights as a legendary boss (CF-12's rule, CF-13). Beaten or
@ caught, it is gone (its object's flag, FLAG_KJH_HIDE_RAIKOU / _ENTEI); after running away it stays.
KJH_EventScript_Legend_RAIKOU::
	lock
	setvar VAR_0x8004, SPECIES_RAIKOU
	setwildbattle SPECIES_RAIKOU, 75
	goto KJH_EventScript_JohtoBeast

KJH_EventScript_Legend_ENTEI::
	lock
	setvar VAR_0x8004, SPECIES_ENTEI
	setwildbattle SPECIES_ENTEI, 75
	goto KJH_EventScript_JohtoBeast

@ VAR_0x8004: its species; setwildbattle has made it
KJH_EventScript_JohtoBeast::
	goto_if_unset FLAG_J_FOUGHT_SUICUNE, KJH_EventScript_JohtoLegendSleeps
	waitse
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	kjh_legendaryboss @ KJH (CF-13): the legendary boss rule
	special BattleSetup_StartLegendaryBattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, KJH_EventScript_JohtoBeastGone
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, KJH_EventScript_JohtoBeastGone
	release
	end

KJH_EventScript_JohtoBeastGone::
	removeobject VAR_LAST_TALKED
	release
	end

KJH_EventScript_JohtoLegendSleeps::
	msgbox KJH_Text_JohtoLegendSleeps
	release
	end

KJH_Text_JohtoLegendSleeps::
	.string "It watches you calmly…\p"
	.string "It seems to be waiting for\n"
	.string "SUICUNE's chosen TRAINER.$"

@ Pewter City's Legend Keeper (ENG-10, docs/LEGENDARIES.md; ported from pokefirered's kjh_legends.inc): once the player
@ is Champion of all three regions (the Hoenn League is the last one: FLAG_HOENN_GAME_CLEAR, Hoenn's Hall of Fame) he
@ hands out the last keys: the Silver Wing (Lugia, Whirl Islands), the GS Ball with the forest restless (Celebi, Ilex
@ Forest's shrine: both flags, or the shrine stays silent), the Mystic and Aurora Tickets for the Vermilion Seagallop
@ (Mew at Navel Rock, Deoxys at Birth Island), and Jirachi, Lv 90.
KJH_EventScript_LegendKeeper::
	lock
	faceplayer
	goto_if_set FLAG_KJH_GOT_TICKETS, KJH_EventScript_LegendKeeperWhere
	goto_if_unset FLAG_HOENN_GAME_CLEAR, KJH_EventScript_LegendKeeperBefore
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, KJH_EventScript_LegendKeeperPartyFull
	msgbox KJH_Text_LegendKeeperGift
	closemessage
	setflag FLAG_J_HAS_SILVER_WING
	bufferstring STR_VAR_2, KJH_ItemName_SilverWing
	call KJH_EventScript_LegendKeeperKeyItem
	setflag FLAG_J_HAS_GS_BALL
	setflag FLAG_J_FOREST_IS_RESTLESS
	bufferstring STR_VAR_2, J_ItemName_GS_BALL
	call KJH_EventScript_LegendKeeperKeyItem
	giveitem ITEM_MYSTIC_TICKET
	giveitem ITEM_AURORA_TICKET
	setflag FLAG_ENABLE_SHIP_NAVEL_ROCK
	setflag FLAG_ENABLE_SHIP_BIRTH_ISLAND
	msgbox KJH_Text_LegendKeeperWish
	givemon SPECIES_JIRACHI, 90
	bufferspeciesname STR_VAR_1, SPECIES_JIRACHI
	playfanfare MUS_LEVEL_UP
	message J_Text_ReceivedMon
	waitmessage
	waitfanfare
	waitbuttonpress
	setflag FLAG_KJH_GOT_TICKETS
	goto KJH_EventScript_LegendKeeperWhere

KJH_EventScript_LegendKeeperKeyItem::
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message J_Text_ReceivedKeyItem
	waitmessage
	waitfanfare
	waitbuttonpress
	return

KJH_EventScript_LegendKeeperBefore::
	msgbox KJH_Text_LegendKeeperBefore
	release
	end

KJH_EventScript_LegendKeeperPartyFull::
	msgbox KJH_Text_LegendKeeperPartyFull
	release
	end

KJH_EventScript_LegendKeeperWhere::
	msgbox KJH_Text_LegendKeeperWhere
	release
	end

KJH_ItemName_SilverWing::
	.string "SILVER WING$"

KJH_Text_LegendKeeperBefore::
	.string "I keep watch over the legends of\n"
	.string "three regions.\p"
	.string "Become CHAMPION of all three,\n"
	.string "from KANTO to HOENN, and I will\l"
	.string "trust you with what I guard.$"

KJH_Text_LegendKeeperPartyFull::
	.string "The CHAMPION of three regions!\p"
	.string "One of my gifts needs room in your\n"
	.string "party. Come back with a free place.$"

KJH_Text_LegendKeeperGift::
	.string "The CHAMPION of three regions!\n"
	.string "Then these are yours.$"

KJH_Text_LegendKeeperWish::
	.string "And one more… This POKéMON wakes\n"
	.string "once every thousand years to\l"
	.string "grant a wish. It chose you.$"

KJH_Text_LegendKeeperWhere::
	.string "The SILVER WING calls LUGIA in\n"
	.string "JOHTO's WHIRL ISLANDS.\p"
	.string "Bring the GS BALL to the shrine in\n"
	.string "ILEX FOREST.\p"
	.string "The tickets work on the VERMILION\n"
	.string "SEAGALLOP: NAVEL ROCK hides MEW,\l"
	.string "BIRTH ISLAND hides DEOXYS.$"
