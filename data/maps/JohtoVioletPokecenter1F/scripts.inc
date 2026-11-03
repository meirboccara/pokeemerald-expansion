@ KJH: translated from pokecrystal maps/VioletPokecenter1F.asm by kjh_tools/johto

JohtoVioletPokecenter1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoVioletPokecenter1F_OnTransition
	.byte 0

JohtoVioletPokecenter1F_OnTransition:
	setrespawn HEAL_LOCATION_J_VIOLET
	end

J_W_VioletPokecenterNurse::
	lock
	call J_VioletPokecenterNurse
	release
	end

J_W_VioletPokecenter1FGameboyKidScript::
	lock
	call J_VioletPokecenter1FGameboyKidScript
	release
	end

J_W_VioletPokecenter1FGentlemanScript::
	lock
	call J_VioletPokecenter1FGentlemanScript
	release
	end

J_W_VioletPokecenter1FYoungsterScript::
	lock
	call J_VioletPokecenter1FYoungsterScript
	release
	end

J_W_VioletPokecenter1F_ElmsAideScript::
	lock
	call J_VioletPokecenter1F_ElmsAideScript
	release
	end

J_VioletPokecenter1F_MapScripts::
J_VioletPokecenterNurse::
	goto J_Std_Nurse
J_VioletPokecenter1F_ElmsAideScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_REFUSED_TO_TAKE_EGG_FROM_ELMS_AIDE, J_L452
	setvar VAR_RESULT, 1
J_L452:
	goto_if_ne VAR_RESULT, 0, J_VioletPokecenter1F_ElmsAideScript_SecondTimeAsking
	message J_VioletPokecenterElmsAideFavorText
	waitmessage
J_VioletPokecenter1F_ElmsAideScript_AskTakeEgg:
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_VioletPokecenter1F_ElmsAideScript_RefusedEgg
	setvar VAR_0x8004, 1
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 6, J_VioletPokecenter1F_ElmsAideScript_PartyFull
	giveegg SPECIES_TOGEPI
	setvar VAR_RESULT, 1
	bufferstring STR_VAR_2, J_VioletPokecenter1F_ElmsAideScript_eggname
	call J_VioletPokecenter1F_ElmsAideScript_AideGivesEgg
	setflag FLAG_J_GOT_TOGEPI_EGG_FROM_ELMS_AIDE
	clearflag FLAG_J_ELMS_AIDE_IN_LAB
	clearflag FLAG_J_TOGEPI_HATCHED
	setvar VAR_J_SCENE_ROUTE_32, 1
	message J_VioletPokecenterElmsAideGiveEggText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_0x8004, 9
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 1, J_VioletPokecenter1F_ElmsAideScript_AideWalksAroundPlayer
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement 5, J_MovementData_AideWalksStraightOutOfPokecenter
	waitmovement 5
	playse SE_EXIT
	removeobject 5
	waitse
	return
J_VioletPokecenter1F_ElmsAideScript_AideWalksAroundPlayer:
	applymovement 5, J_MovementData_AideWalksLeftToExitPokecenter
	waitmovement 5
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement 5, J_MovementData_AideFinishesLeavingPokecenter
	waitmovement 5
	playse SE_EXIT
	removeobject 5
	waitse
	return
J_VioletPokecenter1F_ElmsAideScript_eggname:
	.string "EGG$"
J_VioletPokecenter1F_ElmsAideScript_AideGivesEgg:
	goto J_ReceiveTogepiEggScript
	return
J_VioletPokecenter1F_ElmsAideScript_PartyFull:
	message J_VioletCityElmsAideFullPartyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletPokecenter1F_ElmsAideScript_RefusedEgg:
	message J_VioletPokecenterElmsAideRefuseText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_REFUSED_TO_TAKE_EGG_FROM_ELMS_AIDE
	return
J_VioletPokecenter1F_ElmsAideScript_SecondTimeAsking:
	message J_VioletPokecenterElmsAideAskEggText
	waitmessage
	goto J_VioletPokecenter1F_ElmsAideScript_AskTakeEgg
J_VioletPokecenter1FGameboyKidScript::
	faceplayer
	message J_VioletPokecenter1FGameboyKidText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletPokecenter1FGentlemanScript::
	faceplayer
	message J_VioletPokecenter1FGentlemanText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletPokecenter1FYoungsterScript::
	faceplayer
	message J_VioletPokecenter1FYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MovementData_AideWalksStraightOutOfPokecenter::
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
J_MovementData_AideWalksLeftToExitPokecenter::
	walk_left
	walk_down
	step_end
J_MovementData_AideFinishesLeavingPokecenter::
	walk_down
	walk_down
	walk_down
	step_end
J_VioletPokecenterElmsAideFavorText::
	.string "{PLAYER}, long\ntime, no see.\pPROF.ELM asked me\nto find you.\pHe has another\nfavor to ask.\pWould you take the\nPOKéMON EGG?$"
J_VioletPokecenterElmsAideGiveEggText::
	.string "We discovered that\na POKéMON will not\phatch until it\ngrows in the EGG.\pIt also has to be\nwith other active\lPOKéMON to hatch.\p{PLAYER}, you're\nthe only person\lwe can rely on.\pPlease call PROF.\nELM when that EGG\lhatches!$"
J_VioletCityElmsAideFullPartyText::
	.string "Oh, no. You can't\ncarry any more\lPOKéMON with you.\pI'll wait here\nwhile you make\lroom for the EGG.$"
J_VioletPokecenterElmsAideRefuseText::
	.string "B-but… PROF.ELM\nasked for you…$"
J_VioletPokecenterElmsAideAskEggText::
	.string "{PLAYER}, will you\ntake the EGG?$"
J_VioletPokecenterFarawayLinkText::
	.string "I've been thinking\nit'd be great to\pbe able to link up\nand battle with my\pfriends who live\nfar away.$"
J_VioletPokecenterMobileAdapterText::
	.string "I just battled a\nfriend in CIANWOOD\lover a link.\pIf you connect a\nMOBILE ADAPTER,\pyou can link with\na friend far away.$"
J_VioletPokecenter1FGameboyKidText::
	.string "A guy named BILL\nmade the POKéMON\lPC storage system.$"
J_VioletPokecenter1FGentlemanText::
	.string "It was around\nthree years ago.\pTEAM ROCKET was up\nto no good with\lPOKéMON.\pBut justice pre-\nvailed--a young\lkid broke 'em up.$"
J_VioletPokecenter1FYoungsterText::
	.string "POKéMON are smart.\nThey won't obey a\ptrainer they don't\nrespect.\pWithout the right\nGYM BADGES, they\pwill just do as\nthey please.$"
J_VioletPokecenter1F_MapEvents::
