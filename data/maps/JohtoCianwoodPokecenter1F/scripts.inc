@ KJH: translated from pokecrystal maps/CianwoodPokecenter1F.asm by kjh_tools/johto

JohtoCianwoodPokecenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoCianwoodPokecenter1F_OnTransition
	.byte 0

JohtoCianwoodPokecenter1F_OnTransition:
	setrespawn HEAL_LOCATION_J_CIANWOOD
	end

J_W_CianwoodPokecenter1FNurseScript::
	lock
	call J_CianwoodPokecenter1FNurseScript
	release
	end

J_W_CianwoodPokecenter1FLassScript::
	lock
	call J_CianwoodPokecenter1FLassScript
	release
	end

J_W_CianwoodGymGuideScript::
	lock
	call J_CianwoodGymGuideScript
	release
	end

J_W_CianwoodPokecenter1FSuperNerdScript::
	lock
	call J_CianwoodPokecenter1FSuperNerdScript
	release
	end

J_CianwoodPokecenter1F_MapScripts::
J_CianwoodPokecenter1FNurseScript::
	goto J_Std_Nurse
J_CianwoodPokecenter1FLassScript::
	faceplayer
	message J_CianwoodPokecenter1FLassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodGymGuideScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_CHUCK, J_L593
	setvar VAR_RESULT, 1
J_L593:
	goto_if_ne VAR_RESULT, 0, J_CianwoodGymGuideScript_CianwoodGymGuideWinScript
	message J_CianwoodGymGuideText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodGymGuideScript_CianwoodGymGuideWinScript:
	message J_CianwoodGymGuideWinText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodPokecenter1FSuperNerdScript::
	faceplayer
	message J_CianwoodPokecenter1FSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodPokecenter1FLassText::
	.string "Did you meet the\nPOKéMANIAC?\pHe's always brag-\nging about his\lrare POKéMON.$"
J_CianwoodGymGuideText::
	.string "The POKéMON GYM\ntrainers here are\lmacho bullies.\pIf I stick around,\nthey might come\lafter me.\pHere's some ad-\nvice: the GYM\pLEADER uses the\nfighting-type.\pSo you should\nconfound him with\lpsychic POKéMON.\pWipe out his POKé-\nMON before they\pcan use their\nphysical strength.\pAnd those boulders\nin the middle of\lthe GYM?\pIf you don't move\nthem correctly,\pyou won't reach\nthe GYM LEADER.\pIf you get stuck,\ngo outside.$"
J_CianwoodGymGuideWinText::
	.string "{PLAYER}! You won!\nI could tell by\llooking at you!$"
J_CianwoodPokecenter1FUnusedText1::
	.string "Don't you get the\nurge to show off\pyour POKéMON to\nfriends?\pI wish I could\nshow the POKéMON I\praised to my pal\nin VIOLET.$"
J_CianwoodPokecenter1FUnusedText2::
	.string "I've been battling\nmy pal in VIOLET\pusing a MOBILE\nADAPTER link.\pI'm down 5-7\nagainst him. I've\lgotta crank it up!$"
J_CianwoodPokecenter1FSuperNerdText::
	.string "I love showing off\nthe POKéMON that\pI've raised.\nDon't you?\pI'm going to get\ninto a bunch of\pbattles, and show\noff my POKéMON!$"
J_CianwoodPokecenter1F_MapEvents::
