@ KJH: the MEGA RESEARCHER in Saffron City's Pokemon Center (LV-19, ported from KJH's pokefirered tree,
@ src/kjh_mega.c). With 6 Kanto badges he gives the MEGA BRACELET (expansion's MEGA RING) and the Mega Stone of the
@ player's Kanto starter. LV-20 moves the starter's stone to the Mt. Moon quest; the stone dealers come with LV-21.
KJH_EventScript_MegaResearcher::
	lock
	faceplayer
	checkitem ITEM_MEGA_RING
	goto_if_eq VAR_RESULT, TRUE, KJH_EventScript_MegaResearcherExplain
	callnative KJH_ScriptCountKantoBadges, requests_effects=1
	goto_if_lt VAR_RESULT, 6, KJH_EventScript_MegaResearcherNotYet
	msgbox KJH_Text_MegaResearcherGive
	giveitem ITEM_MEGA_RING
	call_if_eq VAR_STARTER_MON, 0, KJH_EventScript_MegaGiveVenusaurite
	call_if_eq VAR_STARTER_MON, 1, KJH_EventScript_MegaGiveBlastoisinite
	call_if_eq VAR_STARTER_MON, 2, KJH_EventScript_MegaGiveCharizardite
KJH_EventScript_MegaResearcherExplain::
	goto_if_set FLAG_KJH_LEVELLESS, KJH_EventScript_MegaResearcherExplainBond
	msgbox KJH_Text_MegaResearcherExplain
	release
	end

KJH_EventScript_MegaResearcherExplainBond::
	msgbox KJH_Text_MegaResearcherExplainBond
	release
	end

KJH_EventScript_MegaResearcherNotYet::
	msgbox KJH_Text_MegaResearcherNotYet
	release
	end

KJH_EventScript_MegaGiveVenusaurite::
	msgbox KJH_Text_MegaResearcherStarterStone
	giveitem ITEM_VENUSAURITE
	return

KJH_EventScript_MegaGiveBlastoisinite::
	msgbox KJH_Text_MegaResearcherStarterStone
	giveitem ITEM_BLASTOISINITE
	return

KJH_EventScript_MegaGiveCharizardite::
	msgbox KJH_Text_MegaResearcherStarterStone
	giveitem ITEM_CHARIZARDITE_X
	return

KJH_Text_MegaResearcherNotYet::
	.string "I study MEGA EVOLUTION, a power\n"
	.string "that sleeps in some POKéMON.\p"
	.string "It answers only a strong bond.\n"
	.string "Come back with six KANTO BADGES!$"

KJH_Text_MegaResearcherGive::
	.string "Six BADGES! Your bond with your\n"
	.string "POKéMON is strong enough.\p"
	.string "Take this MEGA BRACELET!$"

KJH_Text_MegaResearcherStarterStone::
	.string "And the MEGA STONE of the first\n"
	.string "partner you chose in PALLET TOWN!$"

KJH_Text_MegaResearcherExplain::
	.string "A POKéMON with its MEGA STONE can\n"
	.string "MEGA EVOLVE, once per battle.\p"
	.string "On the move menu, press START,\n"
	.string "then pick a move.\p"
	.string "Be careful: GYM LEADERS, the\n"
	.string "LEAGUE, your rival and some bosses\l"
	.string "will MEGA EVOLVE too from now on!$"

KJH_Text_MegaResearcherExplainBond::
	.string "A POKéMON with its MEGA STONE, held\n"
	.string "or in your BAG, can MEGA EVOLVE once\l"
	.string "it reaches a BOND of 18.\p"
	.string "On the move menu, press START,\n"
	.string "then pick a move.\p"
	.string "Far from KANTO the BRACELET can go\n"
	.string "silent, and with few BADGES there,\l"
	.string "MEGA EVOLUTION is held back.\p"
	.string "Be careful: GYM LEADERS, the\n"
	.string "LEAGUE, your rival and some bosses\l"
	.string "will MEGA EVOLVE too from now on!$"
