@ KJH: translated from pokecrystal maps/SlowpokeWellB2F.asm by kjh_tools/johto

JohtoSlowpokeWellB2F_MapScripts::
	.byte 0

J_W_SlowpokeWellB2FGymGuideScript::
	lock
	call J_SlowpokeWellB2FGymGuideScript
	release
	end

J_SlowpokeWellB2F_MapScripts::
J_SlowpokeWellB2FGymGuideScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_KINGS_ROCK_IN_SLOWPOKE_WELL, J_L139
	setvar VAR_RESULT, 1
J_L139:
	goto_if_ne VAR_RESULT, 0, J_SlowpokeWellB2FGymGuideScript_GotKingsRock
	message J_SlowpokeWellB2FGymGuideText
	waitmessage
	waitbuttonpress
	giveitem ITEM_KINGS_ROCK, 1
	goto_if_eq VAR_RESULT, 0, J_SlowpokeWellB2FGymGuideScript_NoRoom
	setflag FLAG_J_GOT_KINGS_ROCK_IN_SLOWPOKE_WELL
J_SlowpokeWellB2FGymGuideScript_NoRoom:
	closemessage
	return
J_SlowpokeWellB2FGymGuideScript_GotKingsRock:
	message J_SlowpokeWellB2FGymGuideText_GotKingsRock
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SlowpokeWellB2FTMRainDance::
	finditem ITEM_TM18, 1
	return
J_SlowpokeWellB2FGymGuideText::
	.string "I'm waiting to see\nSLOWPOKE's moment\lof evolution.\pThrough observa-\ntion, I made a new\ldiscovery.\pA SLOWPOKE with a\nKING'S ROCK often\pgets bitten by a\nSHELLDER.\pHere, I'll share a\nKING'S ROCK with\lyou.$"
J_SlowpokeWellB2FGymGuideText_GotKingsRock::
	.string "I'm going to be\nlike SLOWPOKE.\pI'll wait patient-\nly, so I can see\lone evolve.$"
J_SlowpokeWellB2F_MapEvents::
