@ KJH (ENG-10): the story's scenes (docs/STORY.md), from the pokefirered tree's data/scripts/kjh_story.inc.

@ Kanto, Vermilion City's harbor: scouts from Hoenn, spying on Team Rocket
KJH_EventScript_Story_VermilionAquaGrunt::
	trainerbattle_single TRAINER_KJH_VERMILION_AQUA_GRUNT, KJH_Text_VermilionAquaIntro, KJH_Text_VermilionAquaDefeat
	msgbox KJH_Text_VermilionAquaPostBattle, MSGBOX_AUTOCLOSE
	end

KJH_EventScript_Story_VermilionMagmaGrunt::
	trainerbattle_single TRAINER_KJH_VERMILION_MAGMA_GRUNT, KJH_Text_VermilionMagmaIntro, KJH_Text_VermilionMagmaDefeat
	msgbox KJH_Text_VermilionMagmaPostBattle, MSGBOX_AUTOCLOSE
	end

KJH_Text_VermilionAquaIntro::
	.string "TEAM ROCKET thinks it owns every\n"
	.string "POKéMON in KANTO.\p"
	.string "We of TEAM AQUA came all the way\n"
	.string "from HOENN to learn their tricks…\p"
	.string "…and to steal the best POKéMON\n"
	.string "before they do!$"

KJH_Text_VermilionAquaDefeat::
	.string "Gah! BOSS ARCHIE won't like this!$"

KJH_Text_VermilionAquaPostBattle::
	.string "The sea is the mother of all life.\n"
	.string "Every POKéMON that swims in it\l"
	.string "belongs to TEAM AQUA!$"

KJH_Text_VermilionMagmaIntro::
	.string "Don't listen to that AQUA fool!\p"
	.string "TEAM MAGMA is here to see how\n"
	.string "GIOVANNI runs his empire.\p"
	.string "LEADER MAXIE will build a bigger\n"
	.string "one. On solid ground!$"

KJH_Text_VermilionMagmaDefeat::
	.string "Ugh… I'll report this to MAXIE.$"

KJH_Text_VermilionMagmaPostBattle::
	.string "ROCKET steals POKéMON for money.\n"
	.string "We're after something far older.\p"
	.string "Something sleeping deep in HOENN…$"

@ Johto, Olivine Port: after the Radio Tower (JohtoRadioTower5F clears FLAG_KJH_HIDE_OLIVINE_ADMINS), Aqua's and
@ Magma's admins ship out Pokemon stolen while Team Rocket held Goldenrod. Talking to either: Matt, then Courtney,
@ then they tell the plan and leave.
KJH_EventScript_Story_OlivineAdmins::
	lock
	faceplayer
	goto_if_defeated TRAINER_KJH_AQUA_ADMIN_MATT, KJH_EventScript_Story_OlivineCourtney
	msgbox KJH_Text_OlivineMattIntro
	trainerbattle_no_intro TRAINER_KJH_AQUA_ADMIN_MATT, KJH_Text_OlivineMattDefeat
KJH_EventScript_Story_OlivineCourtney::
	goto_if_defeated TRAINER_KJH_MAGMA_ADMIN_COURTNEY, KJH_EventScript_Story_OlivineAdminsLeave
	msgbox KJH_Text_OlivineCourtneyIntro
	trainerbattle_no_intro TRAINER_KJH_MAGMA_ADMIN_COURTNEY, KJH_Text_OlivineCourtneyDefeat
KJH_EventScript_Story_OlivineAdminsLeave::
	msgbox KJH_Text_OlivineAdminsReveal
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_KJH_OLIVINE_MATT
	removeobject LOCALID_KJH_OLIVINE_COURTNEY
	setflag FLAG_KJH_HIDE_OLIVINE_ADMINS
	fadescreen FADE_FROM_BLACK
	release
	end

KJH_Text_OlivineMattIntro::
	.string "MATT: Hehehe! While TEAM ROCKET\n"
	.string "kept GOLDENROD busy, we filled our\l"
	.string "ship with JOHTO's POKéMON.\p"
	.string "You want them back?\n"
	.string "Go through TEAM AQUA first!$"

KJH_Text_OlivineMattDefeat::
	.string "MATT: Hah! You're a tough one!$"

KJH_Text_OlivineCourtneyIntro::
	.string "COURTNEY: …ROCKET… so loud…\n"
	.string "TEAM MAGMA… works quietly…\p"
	.string "You… won't touch our cargo.$"

KJH_Text_OlivineCourtneyDefeat::
	.string "COURTNEY: …Calculation error.$"

KJH_Text_OlivineAdminsReveal::
	.string "MATT: Fine, keep the POKéMON.\n"
	.string "We've got bigger fish to catch.\p"
	.string "That radio message reached\n"
	.string "GIOVANNI, you know. He answered…\l"
	.string "from HOENN.\p"
	.string "COURTNEY: He wants… what sleeps in\n"
	.string "the CAVE OF ORIGIN… GROUDON…\p"
	.string "MATT: …and KYOGRE!\n"
	.string "Over BOSS ARCHIE's dead body!\p"
	.string "See you in HOENN, kid!\n"
	.string "If you ever make it that far!$"

@ Hoenn (ENG-10): Emerald's own story on expansion's native maps, with KJH's thread on top. These scripts are outside
@ Hoenn's scope (constants/kjh_hoenn_scope_begin.h): they name Hoenn's badges FLAG_HOENN_BADGE0x_GET.

@ Slateport's harbor: a Rocket grunt who followed Giovanni south
KJH_EventScript_Story_SlateportRocketGrunt::
	trainerbattle_single TRAINER_KJH_ROCKET_GRUNT_SLATEPORT, KJH_Text_SlateportRocketIntro, KJH_Text_SlateportRocketDefeat
	msgbox KJH_Text_SlateportRocketPostBattle, MSGBOX_AUTOCLOSE
	end

KJH_Text_SlateportRocketIntro::
	.string "The BOSS is back!\n"
	.string "TEAM ROCKET lives again!\p"
	.string "And you're not stopping us this\n"
	.string "time, brat!$"

KJH_Text_SlateportRocketDefeat::
	.string "Not you again!$"

KJH_Text_SlateportRocketPostBattle::
	.string "HOENN's gangs found the legends,\n"
	.string "so the BOSS will just take them.\p"
	.string "Get all 8 HOENN BADGES and see\n"
	.string "for yourself… at the CAVE OF\l"
	.string "ORIGIN in SOOTOPOLIS!$"

@ Cave of Origin's entrance: the showdown with Maxie, Archie and Giovanni once the player holds Hoenn's 8th badge
@ (Juan's: Emerald's crisis in Sootopolis is over by then). Each win is kept, so after a loss the next talk resumes
@ with the next leader. Afterwards Groudon and Kyogre can be reached in B1F (data/scripts/kjh_legends.inc) and the
@ Hoenn League opens (EverGrandeCity_PokemonLeague_1F).
@ With the 8th badge Emerald's crisis is over: Wallace has left B1F for Sky Pillar (Emerald's removeobject sets his
@ flag; this keeps it so for a save that skipped it), and the three leaders wait here until the showdown is won.
KJH_EventScript_Story_ShowdownSetup::
	setflag FLAG_KJH_HIDE_SHOWDOWN
	goto_if_unset FLAG_HOENN_BADGE08_GET, KJH_EventScript_Story_ShowdownSetupEnd
	setflag FLAG_HIDE_CAVE_OF_ORIGIN_B1F_WALLACE
	goto_if_set FLAG_KJH_HOENN_SHOWDOWN_DONE, KJH_EventScript_Story_ShowdownSetupEnd
	clearflag FLAG_KJH_HIDE_SHOWDOWN
KJH_EventScript_Story_ShowdownSetupEnd::
	return

KJH_EventScript_Story_Showdown::
	lock
	faceplayer
	goto_if_defeated TRAINER_KJH_SHOWDOWN_MAXIE, KJH_EventScript_Story_ShowdownArchie
	msgbox KJH_Text_ShowdownOpening
	msgbox KJH_Text_ShowdownMaxieIntro
	trainerbattle_no_intro TRAINER_KJH_SHOWDOWN_MAXIE, KJH_Text_ShowdownMaxieDefeat
KJH_EventScript_Story_ShowdownArchie::
	goto_if_defeated TRAINER_KJH_SHOWDOWN_ARCHIE, KJH_EventScript_Story_ShowdownGiovanni
	msgbox KJH_Text_ShowdownArchieIntro
	trainerbattle_no_intro TRAINER_KJH_SHOWDOWN_ARCHIE, KJH_Text_ShowdownArchieDefeat
KJH_EventScript_Story_ShowdownGiovanni::
	goto_if_defeated TRAINER_KJH_SHOWDOWN_GIOVANNI, KJH_EventScript_Story_ShowdownEnd
	msgbox KJH_Text_ShowdownGiovanniIntro
	trainerbattle_no_intro TRAINER_KJH_SHOWDOWN_GIOVANNI, KJH_Text_ShowdownGiovanniDefeat
KJH_EventScript_Story_ShowdownEnd::
	msgbox KJH_Text_ShowdownFarewell
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_KJH_SHOWDOWN_MAXIE
	removeobject LOCALID_KJH_SHOWDOWN_GIOVANNI
	removeobject LOCALID_KJH_SHOWDOWN_ARCHIE
	setflag FLAG_KJH_HIDE_SHOWDOWN
	setflag FLAG_KJH_HOENN_SHOWDOWN_DONE
	fadescreen FADE_FROM_BLACK
	msgbox KJH_Text_ShowdownAfter
	release
	end

KJH_Text_ShowdownOpening::
	.string "GIOVANNI: So the child who broke\n"
	.string "TEAM ROCKET twice comes for a\l"
	.string "third time.\p"
	.string "MAXIE: GROUDON will expand the\n"
	.string "land. Not serve your gang.\p"
	.string "ARCHIE: KYOGRE belongs to the sea.\n"
	.string "And the sea belongs to AQUA!\p"
	.string "GIOVANNI: Squabble all you like.\n"
	.string "The strongest takes the prize.\p"
	.string "…Very well. The child first.$"

KJH_Text_ShowdownMaxieIntro::
	.string "MAXIE: Fufufu… I will show you\n"
	.string "the power of the land!$"

KJH_Text_ShowdownMaxieDefeat::
	.string "MAXIE: Impossible… my calculations…$"

KJH_Text_ShowdownArchieIntro::
	.string "ARCHIE: Bwahaha! Out of the way,\n"
	.string "landlubber!\p"
	.string "No kid is sinking TEAM AQUA!$"

KJH_Text_ShowdownArchieDefeat::
	.string "ARCHIE: Blast it! Swamped by a kid!$"

KJH_Text_ShowdownGiovanniIntro::
	.string "GIOVANNI: Fwahahaha!\p"
	.string "KANTO and JOHTO were only\n"
	.string "practice.\p"
	.string "With the legends of HOENN, TEAM\n"
	.string "ROCKET will rule every region!\p"
	.string "Face GIOVANNI, the greatest\n"
	.string "TRAINER, one last time!$"

KJH_Text_ShowdownGiovanniDefeat::
	.string "GIOVANNI: …Three regions.\n"
	.string "And the same child every time.$"

KJH_Text_ShowdownFarewell::
	.string "GIOVANNI: I know when I am beaten.\p"
	.string "TEAM ROCKET is finished. For real,\n"
	.string "this time.\p"
	.string "MAXIE, ARCHIE… leave those POKéMON\n"
	.string "in peace. This child has earned\l"
	.string "the right to meet them.\p"
	.string "Then go to EVER GRANDE CITY.\n"
	.string "Show HOENN's LEAGUE what\l"
	.string "beat me.$"

KJH_Text_ShowdownAfter::
	.string "The three leaders are gone.\p"
	.string "Deep below, something ancient\n"
	.string "is stirring…$"

@ Sootopolis: once Juan's badge is won Emerald's Expert blocks the Cave of Origin ("the cave, too, shall sleep"); in
@ KJH he stands aside (SootopolisCity_EventScript_SetExpertBlockCaveEntrance) and points to the showdown
KJH_EventScript_Story_SootopolisExpert::
	goto_if_set FLAG_KJH_HOENN_SHOWDOWN_DONE, KJH_EventScript_Story_SootopolisExpertAfter
	msgbox KJH_Text_SootopolisExpert
	release
	end

KJH_EventScript_Story_SootopolisExpertAfter::
	msgbox KJH_Text_SootopolisExpertAfter
	release
	end

KJH_Text_SootopolisExpert::
	.string "Three strangers went into the CAVE\n"
	.string "OF ORIGIN. One in red, one in blue,\l"
	.string "one in black…\p"
	.string "You hold all 8 HOENN BADGES.\n"
	.string "Please, stop them!$"

KJH_Text_SootopolisExpertAfter::
	.string "The strangers are gone, thanks to\n"
	.string "you.\p"
	.string "Deep in the CAVE OF ORIGIN, the\n"
	.string "ancient POKéMON sleep on…$"

@ Ever Grande's Pokemon League: the door guards wait for the showdown (EverGrandeCity_PokemonLeague_1F)
KJH_EventScript_Story_HoennLeagueClosed::
	msgbox KJH_Text_HoennLeagueClosed
	releaseall
	end

KJH_Text_HoennLeagueClosed::
	.string "The LEAGUE is closed while three\n"
	.string "gangs threaten the CAVE OF ORIGIN.\p"
	.string "If you hold all 8 HOENN BADGES,\n"
	.string "could you stop them in SOOTOPOLIS?$"
