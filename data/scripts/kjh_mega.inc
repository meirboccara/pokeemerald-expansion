@ KJH: Mega Evolution's story in Kanto (LV-19, LV-20, src/kjh_mega.c, STORY.md in the KJH repo).
@ With 6 Kanto badges the MEGA RESEARCHER in Saffron City's Pokemon Center sends the player to Mt. Moon, where a
@ meteorite fell long ago. A guardian Alpha CLEFABLE stands by it (Mt. Moon B2F, by the fossils); once it is beaten
@ or caught the meteorite splits into a KEY STONE and a stone that glows next to the player's starter. Back in
@ Saffron the researcher sets the Key Stone in the MEGA BRACELET (expansion's MEGA RING) and gives the starter's
@ stone (Charizard: X or Y); at Bond 18 the starter answers at once, otherwise when its bond is complete.
@ The stone dealers come with LV-21.
KJH_EventScript_MegaResearcher::
	lock
	faceplayer
	checkitem ITEM_MEGA_RING
	goto_if_eq VAR_RESULT, TRUE, KJH_EventScript_MegaResearcherAgain
	goto_if_set FLAG_KJH_MEGA_GUARDIAN_DONE, KJH_EventScript_MegaResearcherKeyStone
	goto_if_set FLAG_KJH_MEGA_QUEST_STARTED, KJH_EventScript_MegaResearcherGoToMtMoon
	callnative KJH_ScriptCountKantoBadges, requests_effects=1
	goto_if_lt VAR_RESULT, 6, KJH_EventScript_MegaResearcherNotYet
	msgbox KJH_Text_MegaResearcherQuest
	setflag FLAG_KJH_MEGA_QUEST_STARTED
	release
	end

KJH_EventScript_MegaResearcherGoToMtMoon::
	msgbox KJH_Text_MegaResearcherGoToMtMoon
	release
	end

@ The Mega Stones share the Items pocket: room for one, or nothing is given yet
KJH_EventScript_MegaResearcherKeyStone::
	checkitemspace ITEM_VENUSAURITE
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_MegaResearcherBagFull
	msgbox KJH_Text_MegaResearcherKeyStone
	giveitem ITEM_MEGA_RING
	msgbox KJH_Text_MegaResearcherStarterStone
	call_if_eq VAR_STARTER_MON, 0, KJH_EventScript_MegaGiveVenusaurite
	call_if_eq VAR_STARTER_MON, 1, KJH_EventScript_MegaGiveBlastoisinite
	call_if_eq VAR_STARTER_MON, 2, KJH_EventScript_MegaGiveCharizardite
	call KJH_EventScript_MegaStarterScene
	goto KJH_EventScript_MegaResearcherExplain

KJH_EventScript_MegaResearcherBagFull::
	msgbox KJH_Text_MegaResearcherBagFull
	release
	end

@ With the bracelet: the starter's first Mega Evolution, if it is still owed and the starter is ready now
KJH_EventScript_MegaResearcherAgain::
	goto_if_set FLAG_KJH_MEGA_FIRST_SCENE, KJH_EventScript_MegaResearcherExplain
	call KJH_EventScript_MegaStarterScene
	goto KJH_EventScript_MegaResearcherExplain

@ The starter steps forward: its picture, then its Mega form's; otherwise what it still needs
KJH_EventScript_MegaStarterScene::
	callnative KJH_ScriptMegaStarterReady, requests_effects=1
	goto_if_eq VAR_RESULT, KJH_MEGA_STARTER_MISSING, KJH_EventScript_MegaStarterMissing
	goto_if_eq VAR_RESULT, KJH_MEGA_STARTER_EVOLVE, KJH_EventScript_MegaStarterEvolve
	goto_if_eq VAR_RESULT, KJH_MEGA_STARTER_BOND, KJH_EventScript_MegaStoneWaiting
	msgbox KJH_Text_MegaStarterStepsForward
	showmonpic VAR_0x8005, 10, 3
	playmoncry VAR_0x8005, CRY_MODE_NORMAL
	waitmoncry
	msgbox KJH_Text_MegaStonesReact
	hidemonpic
	showmonpic VAR_0x8006, 10, 3
	playfanfare MUS_EVOLVED
	waitfanfare
	msgbox KJH_Text_MegaBondComplete
	hidemonpic
	setflag FLAG_KJH_MEGA_FIRST_SCENE
	return

KJH_EventScript_MegaStarterMissing::
	msgbox KJH_Text_MegaStarterMissing
	return

KJH_EventScript_MegaStarterEvolve::
	msgbox KJH_Text_MegaStarterEvolve
	return

KJH_EventScript_MegaStoneWaiting::
	msgbox KJH_Text_MegaStoneWaiting
	return

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
	giveitem ITEM_VENUSAURITE
	return

KJH_EventScript_MegaGiveBlastoisinite::
	giveitem ITEM_BLASTOISINITE
	return

@ The other one is sold later (LV-21)
KJH_EventScript_MegaGiveCharizardite::
	message KJH_Text_MegaCharizarditeWhich
	waitmessage
	dynmultipush KJH_Text_CharizarditeX, 0
	dynmultipush KJH_Text_CharizarditeY, 1
	dynmultistack 0, 0, TRUE, 2, FALSE, 0, NULL @ B does nothing: the player must pick
	goto_if_eq VAR_RESULT, 1, KJH_EventScript_MegaGiveCharizarditeY
	giveitem ITEM_CHARIZARDITE_X
	return

KJH_EventScript_MegaGiveCharizarditeY::
	giveitem ITEM_CHARIZARDITE_Y
	return

@ Mt. Moon B2F: the guardian, hidden by FLAG_KJH_MEGA_GUARDIAN_DONE once fought
KJH_EventScript_MegaGuardian::
	lock
	goto_if_unset FLAG_KJH_MEGA_QUEST_STARTED, KJH_EventScript_MegaGuardianAsleep
	msgbox KJH_Text_MegaGuardianWakes
	playmoncry SPECIES_CLEFABLE, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_CLEFABLE, 45 @ KJH_MEGA_GUARDIAN_LEVEL; KJH_ScriptSetupMegaGuardian sets the level
	callnative KJH_ScriptSetupMegaGuardian, requests_effects=1
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, KJH_EventScript_MegaGuardianDone
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, KJH_EventScript_MegaGuardianDone
	release
	end

KJH_EventScript_MegaGuardianDone::
	setflag FLAG_KJH_MEGA_GUARDIAN_DONE
	removeobject VAR_LAST_TALKED
	msgbox KJH_Text_MegaMeteoriteSplits
	release
	end

KJH_EventScript_MegaGuardianAsleep::
	msgbox KJH_Text_MegaGuardianAsleep
	release
	end

KJH_Text_MegaResearcherNotYet::
	.string "I study MEGA EVOLUTION, a power\n"
	.string "that sleeps in some POKéMON.\p"
	.string "It answers only a strong bond.\n"
	.string "Come back with six KANTO BADGES!$"

KJH_Text_MegaResearcherQuest::
	.string "Six BADGES! Then listen.\p"
	.string "MEGA EVOLUTION needs a KEY STONE,\n"
	.string "a shard of a fallen star.\p"
	.string "Long ago a meteorite fell on\n"
	.string "MT. MOON. It lies deep inside.\p"
	.string "But they say a CLEFABLE guards it,\n"
	.string "stronger than any other.\p"
	.string "Bring me what you find there!$"

KJH_Text_MegaResearcherGoToMtMoon::
	.string "The meteorite lies deep in\n"
	.string "MT. MOON, by the old fossils.\p"
	.string "Mind its CLEFABLE guardian!$"

KJH_Text_MegaResearcherKeyStone::
	.string "A KEY STONE! You did it!\p"
	.string "Let me set it in this BRACELET…\n"
	.string "There! Take the MEGA BRACELET!$"

KJH_Text_MegaResearcherStarterStone::
	.string "And that other stone glows next to\n"
	.string "the first partner you chose in\l"
	.string "PALLET TOWN. It's a MEGA STONE!$"

KJH_Text_MegaCharizarditeWhich::
	.string "It shines two ways… Which do\n"
	.string "you want it to become?$"

KJH_Text_CharizarditeX::
	.string "CHARIZARDITE X$"

KJH_Text_CharizarditeY::
	.string "CHARIZARDITE Y$"

KJH_Text_MegaStarterStepsForward::
	.string "{STR_VAR_1} steps forward…$"

KJH_Text_MegaStonesReact::
	.string "The stones are reacting!$"

KJH_Text_MegaBondComplete::
	.string "{STR_VAR_1} MEGA EVOLVED!\p"
	.string "Your bond with {STR_VAR_1}\n"
	.string "is complete!$"

KJH_Text_MegaStoneWaiting::
	.string "The stone is waiting…\p"
	.string "It will answer when your bond with\n"
	.string "{STR_VAR_1} is complete.\p"
	.string "Come back and show me then!$"

KJH_Text_MegaStarterEvolve::
	.string "The stone glows for {STR_VAR_1},\n"
	.string "but only a {STR_VAR_2} can hold\l"
	.string "its power. Come back then!$"

KJH_Text_MegaStarterMissing::
	.string "The stone glows for your first\n"
	.string "partner… Bring {STR_VAR_1} here\l"
	.string "one day, and show me!$"

KJH_Text_MegaResearcherBagFull::
	.string "A KEY STONE! But your BAG has no\n"
	.string "room for what I have to give you.\p"
	.string "Make some room and come back!$"

KJH_Text_MegaGuardianAsleep::
	.string "A CLEFABLE sleeps against a strange\n"
	.string "old rock. It won't let you near.$"

KJH_Text_MegaGuardianWakes::
	.string "The CLEFABLE wakes and glows with\n"
	.string "the light of the old rock!$"

KJH_Text_MegaMeteoriteSplits::
	.string "The old meteorite splits open!\p"
	.string "Inside: a KEY STONE, and a stone\n"
	.string "that glows warmly…\p"
	.string "The researcher in SAFFRON will\n"
	.string "know what to do with them.$"

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

@ LV-21: the Mega Stone dealer in Celadon City's Pokemon Center (Goldenrod's and Slateport's come with their
@ regions). He sells once the player has the MEGA BRACELET, which comes with the starter's stone (LV-20).
KJH_EventScript_MegaStoneDealerKanto::
	lock
	faceplayer
	checkitem ITEM_MEGA_RING
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_MegaStoneDealerNotYet
	message KJH_Text_MegaStoneDealer
	waitmessage
	pokemart KJH_Mart_MegaStonesKanto
	msgbox KJH_Text_MegaStoneDealerBye
	release
	end

KJH_EventScript_MegaStoneDealerNotYet::
	msgbox KJH_Text_MegaStoneDealerNotYet
	release
	end

@ Cerulean Cave B1F, in the alcoves on each side of Mewtwo
KJH_EventScript_ItemMewtwoniteX::
	finditem ITEM_MEWTWONITE_X
	end

KJH_EventScript_ItemMewtwoniteY::
	finditem ITEM_MEWTWONITE_Y
	end

@ Kanto's ordinary stones, at KJH_MEGA_STONE_PRICE (include/kjh_mega.h); never the ones of sNeverSoldStones
@ (Dragoninite, Mewtwonite X and Y). The starters' stones are here too: the player's other Charizardite.
	.align 2
KJH_Mart_MegaStonesKanto::
	.2byte ITEM_VENUSAURITE
	.2byte ITEM_CHARIZARDITE_X
	.2byte ITEM_CHARIZARDITE_Y
	.2byte ITEM_BLASTOISINITE
	.2byte ITEM_BEEDRILLITE
	.2byte ITEM_PIDGEOTITE
	.2byte ITEM_RAICHUNITE_X
	.2byte ITEM_RAICHUNITE_Y
	.2byte ITEM_CLEFABLITE
	.2byte ITEM_ALAKAZITE
	.2byte ITEM_VICTREEBELITE
	.2byte ITEM_SLOWBRONITE
	.2byte ITEM_GENGARITE
	.2byte ITEM_KANGASKHANITE
	.2byte ITEM_STARMINITE
	.2byte ITEM_PINSIRITE
	.2byte ITEM_GYARADOSITE
	.2byte ITEM_AERODACTYLITE
	.2byte ITEM_NONE
	release
	end

KJH_Text_MegaStoneDealer::
	.string "MEGA STONES! I have the ones of\n"
	.string "KANTO's POKéMON.$"

KJH_Text_MegaStoneDealerBye::
	.string "Come back any time!$"

KJH_Text_MegaStoneDealerNotYet::
	.string "I sell MEGA STONES, but they're of\n"
	.string "no use without a MEGA BRACELET.\p"
	.string "The researcher in SAFFRON's\n"
	.string "POKéMON CENTER knows more.$"
