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
	setvar VAR_0x8004, KJH_MEGA_STARTER_KANTO
	call KJH_EventScript_MegaStarterScene
	goto KJH_EventScript_MegaResearcherExplain

KJH_EventScript_MegaResearcherBagFull::
	msgbox KJH_Text_MegaResearcherBagFull
	release
	end

@ With the bracelet: the starter's first Mega Evolution, if it is still owed and the starter is ready now
KJH_EventScript_MegaResearcherAgain::
	goto_if_set FLAG_KJH_MEGA_FIRST_SCENE, KJH_EventScript_MegaResearcherExplain
	setvar VAR_0x8004, KJH_MEGA_STARTER_KANTO
	call KJH_EventScript_MegaStarterScene
	goto KJH_EventScript_MegaResearcherExplain

@ The starter of the region VAR_0x8004 (KJH_MEGA_STARTER_*) steps forward: its picture, then its Mega form's;
@ otherwise what it still needs. Typhlosion has no Mega: its player picks a free stone (LV-23), as in Hoenn a player
@ without Prof. Birch's starter.
KJH_EventScript_MegaStarterScene::
	callnative KJH_ScriptMegaStarterReady, requests_effects=1
	goto_if_ne VAR_RESULT, KJH_MEGA_STARTER_NO_MEGA, KJH_EventScript_MegaStarterSceneHasMega
	goto_if_eq VAR_0x8004, KJH_MEGA_STARTER_HOENN, KJH_EventScript_MegaHoennPick
	goto KJH_EventScript_MegaTyphlosionPick
KJH_EventScript_MegaStarterSceneHasMega::
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
KJH_EventScript_MegaSceneDone::
	goto_if_eq VAR_0x8004, KJH_MEGA_STARTER_JOHTO, KJH_EventScript_MegaJohtoSceneDone
	goto_if_eq VAR_0x8004, KJH_MEGA_STARTER_HOENN, KJH_EventScript_MegaHoennSceneDone
	setflag FLAG_KJH_MEGA_FIRST_SCENE
	return

KJH_EventScript_MegaJohtoSceneDone::
	setflag FLAG_KJH_JOHTO_MEGA_SCENE
	return

KJH_EventScript_MegaHoennSceneDone::
	setflag FLAG_KJH_HOENN_MEGA_SCENE
	return

@ Typhlosion's player picks one stone of Johto's list, for free
KJH_EventScript_MegaTyphlosionPick::
	msgbox KJH_Text_MegaTyphlosionPick
	dynmultipush KJH_Text_Ampharosite, 0
	dynmultipush KJH_Text_Houndoominite, 1
	dynmultipush KJH_Text_Heracronite, 2
	dynmultipush KJH_Text_Scizorite, 3
	dynmultipush KJH_Text_Steelixite, 4
	dynmultipush KJH_Text_Skarmorite, 5
	dynmultipush KJH_Text_Meganiumite, 6
	dynmultipush KJH_Text_Feraligite, 7
	dynmultistack 0, 0, TRUE, 6, FALSE, 0, NULL @ B does nothing: the player must pick
	copyvar VAR_0x8005, VAR_RESULT @ giveitem sets VAR_RESULT
	call_if_eq VAR_0x8005, 0, KJH_EventScript_MegaGiveAmpharosite
	call_if_eq VAR_0x8005, 1, KJH_EventScript_MegaGiveHoundoominite
	call_if_eq VAR_0x8005, 2, KJH_EventScript_MegaGiveHeracronite
	call_if_eq VAR_0x8005, 3, KJH_EventScript_MegaGiveScizorite
	call_if_eq VAR_0x8005, 4, KJH_EventScript_MegaGiveSteelixite
	call_if_eq VAR_0x8005, 5, KJH_EventScript_MegaGiveSkarmorite
	call_if_eq VAR_0x8005, 6, KJH_EventScript_MegaGiveMeganiumiteFree
	call_if_eq VAR_0x8005, 7, KJH_EventScript_MegaGiveFeraligiteFree
	goto KJH_EventScript_MegaSceneDone

KJH_EventScript_MegaGiveMeganiumiteFree::
	giveitem ITEM_MEGANIUMITE
	return

KJH_EventScript_MegaGiveFeraligiteFree::
	giveitem ITEM_FERALIGITE
	return

KJH_EventScript_MegaGiveAmpharosite::
	giveitem ITEM_AMPHAROSITE
	return

KJH_EventScript_MegaGiveHoundoominite::
	giveitem ITEM_HOUNDOOMINITE
	return

KJH_EventScript_MegaGiveHeracronite::
	giveitem ITEM_HERACRONITE
	return

KJH_EventScript_MegaGiveScizorite::
	giveitem ITEM_SCIZORITE
	return

KJH_EventScript_MegaGiveSteelixite::
	giveitem ITEM_STEELIXITE
	return

KJH_EventScript_MegaGiveSkarmorite::
	giveitem ITEM_SKARMORITE
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

@ LV-23: Johto. The bracelet is silent here until the Ruins of Alph quest: after 4 Johto badges a researcher in the
@ Ruins of Alph Research Center sends the player to the Inner Chamber, where the Unown walls show an ancient Mega
@ symbol and an ANCIENT KEYSTONE lies (FLAG_KJH_JOHTO_BRACELET hides it once taken). Then the Johto starter's scene,
@ and Goldenrod's dealer opens.
KJH_EventScript_JohtoMegaResearcher::
	lock
	faceplayer
	goto_if_set FLAG_KJH_JOHTO_BRACELET, KJH_EventScript_JohtoMegaResearcherAfter
	goto_if_set FLAG_KJH_JOHTO_MEGA_QUEST, KJH_EventScript_JohtoMegaResearcherGo
	checkitem ITEM_MEGA_RING
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_JohtoMegaResearcherNoBracelet
	callnative KJH_ScriptCountJohtoBadges, requests_effects=1
	goto_if_lt VAR_RESULT, 4, KJH_EventScript_JohtoMegaResearcherNotYet
	msgbox KJH_Text_JohtoMegaResearcherQuest
	setflag FLAG_KJH_JOHTO_MEGA_QUEST
	release
	end

KJH_EventScript_JohtoMegaResearcherGo::
	msgbox KJH_Text_JohtoMegaResearcherGo
	release
	end

KJH_EventScript_JohtoMegaResearcherNoBracelet::
	msgbox KJH_Text_JohtoMegaResearcherNoBracelet
	release
	end

KJH_EventScript_JohtoMegaResearcherNotYet::
	msgbox KJH_Text_JohtoMegaResearcherNotYet
	release
	end

@ The bracelet works in Johto: the starter's scene, if it is still owed
KJH_EventScript_JohtoMegaResearcherAfter::
	goto_if_set FLAG_KJH_JOHTO_MEGA_SCENE, KJH_EventScript_JohtoMegaResearcherDone
	setvar VAR_0x8004, KJH_MEGA_STARTER_JOHTO
	call KJH_EventScript_MegaStarterScene
KJH_EventScript_JohtoMegaResearcherDone::
	msgbox KJH_Text_JohtoMegaResearcherDone
	release
	end

KJH_EventScript_JohtoAncientKeystone::
	lock
	goto_if_unset FLAG_KJH_JOHTO_MEGA_QUEST, KJH_EventScript_JohtoAncientKeystoneAsleep
	checkitemspace ITEM_AMPHAROSITE
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_JohtoAncientKeystoneBagFull
	msgbox KJH_Text_JohtoAncientKeystone
	setflag FLAG_KJH_JOHTO_BRACELET
	removeobject VAR_LAST_TALKED
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	waitfanfare
	msgbox KJH_Text_JohtoBraceletWorks
	call_if_set FLAG_J_GOT_CHIKORITA_FROM_ELM, KJH_EventScript_MegaGiveMeganiumite
	call_if_set FLAG_J_GOT_TOTODILE_FROM_ELM, KJH_EventScript_MegaGiveFeraligite
	setvar VAR_0x8004, KJH_MEGA_STARTER_JOHTO
	call KJH_EventScript_MegaStarterScene
	release
	end

@ The starter's stone is the region's first (Typhlosion's player picks one in the scene)
KJH_EventScript_MegaGiveMeganiumite::
	msgbox KJH_Text_JohtoStarterStone
	giveitem ITEM_MEGANIUMITE
	return

KJH_EventScript_MegaGiveFeraligite::
	msgbox KJH_Text_JohtoStarterStone
	giveitem ITEM_FERALIGITE
	return

KJH_EventScript_JohtoAncientKeystoneAsleep::
	msgbox KJH_Text_JohtoAncientKeystoneAsleep
	release
	end

KJH_EventScript_JohtoAncientKeystoneBagFull::
	msgbox KJH_Text_MegaResearcherBagFull
	release
	end

@ Goldenrod City's Pokemon Center (the converted map's dealer, next to the stat trainer)
KJH_EventScript_MegaStoneDealerJohto::
	lock
	faceplayer
	goto_if_set FLAG_KJH_JOHTO_BRACELET, KJH_EventScript_MegaStoneDealerJohtoOpen
	goto_if_set FLAG_KJH_LEVELLESS, KJH_EventScript_MegaStoneDealerJohtoNotYet
	checkitem ITEM_MEGA_RING @ the classic game: the bracelet works everywhere
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_MegaStoneDealerNotYet
KJH_EventScript_MegaStoneDealerJohtoOpen::
	message KJH_Text_MegaStoneDealerJohto
	waitmessage
	pokemart KJH_Mart_MegaStonesJohto
	msgbox KJH_Text_MegaStoneDealerBye
	release
	end

KJH_EventScript_MegaStoneDealerJohtoNotYet::
	msgbox KJH_Text_MegaStoneDealerJohtoNotYet
	release
	end

@ Never sold (src/kjh_mega.c, sNeverSoldStones): Dragon's Den B1F, Mt. Silver beside Red's room
KJH_EventScript_ItemDragoninite::
	finditem ITEM_DRAGONINITE
	end

KJH_EventScript_ItemTyranitarite::
	finditem ITEM_TYRANITARITE
	end

@ Johto's ordinary stones; never Dragoninite or Tyranitarite
	.align 2
KJH_Mart_MegaStonesJohto::
	.2byte ITEM_MEGANIUMITE
	.2byte ITEM_FERALIGITE
	.2byte ITEM_AMPHAROSITE
	.2byte ITEM_STEELIXITE
	.2byte ITEM_SCIZORITE
	.2byte ITEM_HERACRONITE
	.2byte ITEM_SKARMORITE
	.2byte ITEM_HOUNDOOMINITE
	.2byte ITEM_NONE
	release
	end

KJH_Text_MegaTyphlosionPick::
	.string "This stone glows, but TYPHLOSION's\n"
	.string "power can't take a MEGA form…\p"
	.string "Then let it become another MEGA\n"
	.string "STONE. Which one would you like?$"

KJH_Text_Ampharosite::
	.string "AMPHAROSITE$"

KJH_Text_Houndoominite::
	.string "HOUNDOOMINITE$"

KJH_Text_Heracronite::
	.string "HERACRONITE$"

KJH_Text_Scizorite::
	.string "SCIZORITE$"

KJH_Text_Steelixite::
	.string "STEELIXITE$"

KJH_Text_Skarmorite::
	.string "SKARMORITE$"

KJH_Text_Meganiumite::
	.string "MEGANIUMITE$"

KJH_Text_Feraligite::
	.string "FERALIGITE$"

KJH_Text_JohtoStarterStone::
	.string "Another stone glows next to the\n"
	.string "partner PROF. ELM gave you!$"

KJH_Text_JohtoMegaResearcherNoBracelet::
	.string "The UNOWN walls show a strange\n"
	.string "symbol… MEGA EVOLUTION, perhaps?\p"
	.string "Without a MEGA BRACELET, though,\n"
	.string "it means nothing.$"

KJH_Text_JohtoMegaResearcherNotYet::
	.string "Your BRACELET is silent in JOHTO?\n"
	.string "The old power here is different.\p"
	.string "Come back with four JOHTO BADGES,\n"
	.string "and I'll tell you what I found.$"

KJH_Text_JohtoMegaResearcherQuest::
	.string "Four BADGES! Listen.\p"
	.string "In the INNER CHAMBER the UNOWN\n"
	.string "walls show an ancient MEGA symbol.\p"
	.string "Below it lies a KEYSTONE, older\n"
	.string "than any in KANTO. Go and see!$"

KJH_Text_JohtoMegaResearcherGo::
	.string "The ancient KEYSTONE lies in the\n"
	.string "INNER CHAMBER, under the symbol.$"

KJH_Text_JohtoMegaResearcherDone::
	.string "Your BRACELET speaks JOHTO's old\n"
	.string "language now. Remarkable!$"

KJH_Text_JohtoAncientKeystoneAsleep::
	.string "An old stone sits under a strange\n"
	.string "symbol on the wall.$"

KJH_Text_JohtoAncientKeystone::
	.string "The UNOWN symbol glows!\p"
	.string "The old stone answers your\n"
	.string "BRACELET: an ANCIENT KEYSTONE!$"

KJH_Text_JohtoBraceletWorks::
	.string "The MEGA BRACELET works in JOHTO\n"
	.string "now!$"

KJH_Text_MegaStoneDealerJohto::
	.string "MEGA STONES! I have the ones of\n"
	.string "JOHTO's POKéMON.$"

KJH_Text_MegaStoneDealerJohtoNotYet::
	.string "I sell MEGA STONES, but your\n"
	.string "BRACELET is silent in JOHTO.\p"
	.string "The researchers at the RUINS OF\n"
	.string "ALPH might know why.$"

@ LV-23: Hoenn. The bracelet is silent here until the Meteor Falls quest: after 4 Hoenn badges the MEGA RESEARCHER
@ visiting PROF. COZMO in Fallarbor Town sends the player to Meteor Falls, where a fragment of the meteorite TEAM
@ MAGMA took still glows (Meteor Falls 1F, past Cozmo's spot; FLAG_KJH_HOENN_BRACELET hides it once taken). Then
@ Hoenn's starter scene (Prof. Birch's: Sceptilite, Blazikenite or Swampertite), and Slateport's dealer opens.
KJH_EventScript_HoennMegaResearcher::
	lock
	faceplayer
	goto_if_set FLAG_KJH_HOENN_BRACELET, KJH_EventScript_HoennMegaResearcherAfter
	goto_if_set FLAG_KJH_HOENN_MEGA_QUEST, KJH_EventScript_HoennMegaResearcherGo
	checkitem ITEM_MEGA_RING
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_HoennMegaResearcherNoBracelet
	callnative KJH_ScriptCountHoennBadges, requests_effects=1
	goto_if_lt VAR_RESULT, 4, KJH_EventScript_HoennMegaResearcherNotYet
	msgbox KJH_Text_HoennMegaResearcherQuest
	setflag FLAG_KJH_HOENN_MEGA_QUEST
	release
	end

KJH_EventScript_HoennMegaResearcherGo::
	msgbox KJH_Text_HoennMegaResearcherGo
	release
	end

KJH_EventScript_HoennMegaResearcherNoBracelet::
	msgbox KJH_Text_HoennMegaResearcherNoBracelet
	release
	end

KJH_EventScript_HoennMegaResearcherNotYet::
	msgbox KJH_Text_HoennMegaResearcherNotYet
	release
	end

@ The bracelet works in Hoenn: the starter's scene, if it is still owed
KJH_EventScript_HoennMegaResearcherAfter::
	goto_if_set FLAG_KJH_HOENN_MEGA_SCENE, KJH_EventScript_HoennMegaResearcherDone
	setvar VAR_0x8004, KJH_MEGA_STARTER_HOENN
	call KJH_EventScript_MegaStarterScene
KJH_EventScript_HoennMegaResearcherDone::
	msgbox KJH_Text_HoennMegaResearcherDone
	release
	end

@ Meteor Falls 1F: the meteorite fragment
KJH_EventScript_HoennMeteoriteFragment::
	lock
	goto_if_unset FLAG_KJH_HOENN_MEGA_QUEST, KJH_EventScript_HoennMeteoriteFragmentAsleep
	checkitemspace ITEM_SCEPTILITE
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_HoennMeteoriteFragmentBagFull
	msgbox KJH_Text_HoennMeteoriteFragment
	setflag FLAG_KJH_HOENN_BRACELET
	removeobject VAR_LAST_TALKED
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	waitfanfare
	msgbox KJH_Text_HoennBraceletWorks
	callnative KJH_ScriptHoennStarterStone, requests_effects=1
	goto_if_eq VAR_RESULT, ITEM_NONE, KJH_EventScript_HoennMeteoriteFragmentScene
	copyvar VAR_0x8009, VAR_RESULT
	msgbox KJH_Text_HoennStarterStone
	giveitem VAR_0x8009
KJH_EventScript_HoennMeteoriteFragmentScene::
	setvar VAR_0x8004, KJH_MEGA_STARTER_HOENN
	call KJH_EventScript_MegaStarterScene
	release
	end

KJH_EventScript_HoennMeteoriteFragmentAsleep::
	msgbox KJH_Text_HoennMeteoriteFragmentAsleep
	release
	end

KJH_EventScript_HoennMeteoriteFragmentBagFull::
	msgbox KJH_Text_MegaResearcherBagFull
	release
	end

@ A player without Prof. Birch's starter picks one stone of Hoenn's list, for free (as Typhlosion's in Johto); the
@ options' ids are the stones
KJH_EventScript_MegaHoennPick::
	msgbox KJH_Text_MegaHoennPick
	dynmultipush KJH_Text_Sceptilite, ITEM_SCEPTILITE
	dynmultipush KJH_Text_Blazikenite, ITEM_BLAZIKENITE
	dynmultipush KJH_Text_Swampertite, ITEM_SWAMPERTITE
	dynmultipush KJH_Text_Gardevoirite, ITEM_GARDEVOIRITE
	dynmultipush KJH_Text_Sablenite, ITEM_SABLENITE
	dynmultipush KJH_Text_Mawilite, ITEM_MAWILITE
	dynmultipush KJH_Text_Aggronite, ITEM_AGGRONITE
	dynmultipush KJH_Text_Medichamite, ITEM_MEDICHAMITE
	dynmultipush KJH_Text_Manectite, ITEM_MANECTITE
	dynmultipush KJH_Text_Sharpedonite, ITEM_SHARPEDONITE
	dynmultipush KJH_Text_Cameruptite, ITEM_CAMERUPTITE
	dynmultipush KJH_Text_Altarianite, ITEM_ALTARIANITE
	dynmultipush KJH_Text_Banettite, ITEM_BANETTITE
	dynmultipush KJH_Text_Chimechite, ITEM_CHIMECHITE
	dynmultipush KJH_Text_Absolite, ITEM_ABSOLITE
	dynmultipush KJH_Text_AbsoliteZ, ITEM_ABSOLITE_Z
	dynmultipush KJH_Text_Glalitite, ITEM_GLALITITE
	dynmultistack 0, 0, TRUE, 6, FALSE, 0, NULL @ B does nothing: the player must pick
	copyvar VAR_0x8005, VAR_RESULT @ giveitem sets VAR_RESULT
	giveitem VAR_0x8005
	goto KJH_EventScript_MegaSceneDone

@ Slateport City's Pokemon Center
KJH_EventScript_MegaStoneDealerHoenn::
	lock
	faceplayer
	goto_if_set FLAG_KJH_HOENN_BRACELET, KJH_EventScript_MegaStoneDealerHoennOpen
	goto_if_set FLAG_KJH_LEVELLESS, KJH_EventScript_MegaStoneDealerHoennNotYet
	checkitem ITEM_MEGA_RING @ the classic game: the bracelet works everywhere
	goto_if_eq VAR_RESULT, FALSE, KJH_EventScript_MegaStoneDealerNotYet
KJH_EventScript_MegaStoneDealerHoennOpen::
	message KJH_Text_MegaStoneDealerHoenn
	waitmessage
	pokemart KJH_Mart_MegaStonesHoenn
	msgbox KJH_Text_MegaStoneDealerBye
	release
	end

KJH_EventScript_MegaStoneDealerHoennNotYet::
	msgbox KJH_Text_MegaStoneDealerHoennNotYet
	release
	end

@ Never sold (src/kjh_mega.c, sNeverSoldStones): Meteor Falls B1F's Bagon room, Mossdeep's Space Center 2F, Sky
@ Pillar's entrance cave
KJH_EventScript_ItemSalamencite::
	finditem ITEM_SALAMENCITE
	end

KJH_EventScript_ItemMetagrossite::
	finditem ITEM_METAGROSSITE
	end

KJH_EventScript_ItemLatiasite::
	finditem ITEM_LATIASITE
	end

KJH_EventScript_ItemLatiosite::
	finditem ITEM_LATIOSITE
	end

@ Hoenn's ordinary stones; never Salamencite, Metagrossite, Latiasite or Latiosite
	.align 2
KJH_Mart_MegaStonesHoenn::
	.2byte ITEM_SCEPTILITE
	.2byte ITEM_BLAZIKENITE
	.2byte ITEM_SWAMPERTITE
	.2byte ITEM_GARDEVOIRITE
	.2byte ITEM_SABLENITE
	.2byte ITEM_MAWILITE
	.2byte ITEM_AGGRONITE
	.2byte ITEM_MEDICHAMITE
	.2byte ITEM_MANECTITE
	.2byte ITEM_SHARPEDONITE
	.2byte ITEM_CAMERUPTITE
	.2byte ITEM_ALTARIANITE
	.2byte ITEM_BANETTITE
	.2byte ITEM_CHIMECHITE
	.2byte ITEM_ABSOLITE
	.2byte ITEM_ABSOLITE_Z
	.2byte ITEM_GLALITITE
	.2byte ITEM_NONE
	release
	end

KJH_Text_MegaHoennPick::
	.string "This stone glows, but no partner\n"
	.string "from PROF. BIRCH is here for it…\p"
	.string "Then let it become another MEGA\n"
	.string "STONE. Which one would you like?$"

KJH_Text_Sceptilite::
	.string "SCEPTILITE$"

KJH_Text_Blazikenite::
	.string "BLAZIKENITE$"

KJH_Text_Swampertite::
	.string "SWAMPERTITE$"

KJH_Text_Gardevoirite::
	.string "GARDEVOIRITE$"

KJH_Text_Sablenite::
	.string "SABLENITE$"

KJH_Text_Mawilite::
	.string "MAWILITE$"

KJH_Text_Aggronite::
	.string "AGGRONITE$"

KJH_Text_Medichamite::
	.string "MEDICHAMITE$"

KJH_Text_Manectite::
	.string "MANECTITE$"

KJH_Text_Sharpedonite::
	.string "SHARPEDONITE$"

KJH_Text_Cameruptite::
	.string "CAMERUPTITE$"

KJH_Text_Altarianite::
	.string "ALTARIANITE$"

KJH_Text_Banettite::
	.string "BANETTITE$"

KJH_Text_Chimechite::
	.string "CHIMECHITE$"

KJH_Text_Absolite::
	.string "ABSOLITE$"

KJH_Text_AbsoliteZ::
	.string "ABSOLITE Z$"

KJH_Text_Glalitite::
	.string "GLALITITE$"

KJH_Text_HoennStarterStone::
	.string "Another stone glows next to the\n"
	.string "partner PROF. BIRCH gave you!$"

KJH_Text_HoennMegaResearcherNoBracelet::
	.string "PROF. COZMO's meteorites hum with\n"
	.string "the power of MEGA EVOLUTION.\p"
	.string "Without a MEGA BRACELET, though,\n"
	.string "it means nothing.$"

KJH_Text_HoennMegaResearcherNotYet::
	.string "Your BRACELET is silent in HOENN?\n"
	.string "The stars here speak another way.\p"
	.string "Come back with four HOENN BADGES,\n"
	.string "and I'll tell you what I found.$"

KJH_Text_HoennMegaResearcherQuest::
	.string "Four BADGES! Listen.\p"
	.string "TEAM MAGMA took the meteorite from\n"
	.string "METEOR FALLS, but not all of it.\p"
	.string "A fragment broke off near where\n"
	.string "PROF. COZMO stood. It still glows.\p"
	.string "A star that fell on HOENN might\n"
	.string "wake your BRACELET. Go and see!$"

KJH_Text_HoennMegaResearcherGo::
	.string "The fragment lies in METEOR FALLS,\n"
	.string "past the spot where PROF. COZMO\l"
	.string "met TEAM MAGMA.$"

KJH_Text_HoennMegaResearcherDone::
	.string "Your BRACELET hums with HOENN's\n"
	.string "fallen star now. Wonderful!$"

KJH_Text_HoennMeteoriteFragmentAsleep::
	.string "A small dark rock, warm to the\n"
	.string "touch. Did it fall from the sky?$"

KJH_Text_HoennMeteoriteFragment::
	.string "The fragment glows with starlight!\p"
	.string "It answers your BRACELET: a piece\n"
	.string "of the METEORITE!$"

KJH_Text_HoennBraceletWorks::
	.string "The MEGA BRACELET works in HOENN\n"
	.string "now!$"

KJH_Text_MegaStoneDealerHoenn::
	.string "MEGA STONES! I have the ones of\n"
	.string "HOENN's POKéMON.$"

KJH_Text_MegaStoneDealerHoennNotYet::
	.string "I sell MEGA STONES, but your\n"
	.string "BRACELET is silent in HOENN.\p"
	.string "A researcher is visiting PROF.\n"
	.string "COZMO in FALLARBOR TOWN…$"
