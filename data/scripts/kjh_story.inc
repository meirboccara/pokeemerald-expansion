@ KJH (ENG-10): the story's scenes (docs/STORY.md), from the pokefirered tree's data/scripts/kjh_story.inc.

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
