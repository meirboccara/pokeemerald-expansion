@ KJH: translated from pokecrystal maps/Route40.asm by kjh_tools/johto

JohtoRoute40_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoRoute40_OnTransition
	.byte 0

JohtoRoute40_OnTransition:
	call J_Route40MonicaCallback
	end

J_T_TrainerSwimmermSimon::
	trainerbattle_single TRAINER_J_SWIMMERM_SIMON, J_SwimmermSimonSeenText, J_SwimmermSimonBeatenText
	call J_TrainerSwimmermSimon_Script
	release
	end

J_T_TrainerSwimmermRandall::
	trainerbattle_single TRAINER_J_SWIMMERM_RANDALL, J_SwimmermRandallSeenText, J_SwimmermRandallBeatenText
	call J_TrainerSwimmermRandall_Script
	release
	end

J_T_TrainerSwimmerfElaine::
	trainerbattle_single TRAINER_J_SWIMMERF_ELAINE, J_SwimmerfElaineSeenText, J_SwimmerfElaineBeatenText
	call J_TrainerSwimmerfElaine_Script
	release
	end

J_T_TrainerSwimmerfPaula::
	trainerbattle_single TRAINER_J_SWIMMERF_PAULA, J_SwimmerfPaulaSeenText, J_SwimmerfPaulaBeatenText
	call J_TrainerSwimmerfPaula_Script
	release
	end

J_W_Route40Rock::
	lock
	call J_Route40Rock
	release
	end

J_W_Route40Lass1Script::
	lock
	call J_Route40Lass1Script
	release
	end

J_W_MonicaScript::
	lock
	call J_MonicaScript
	release
	end

J_W_Route40PokefanMScript::
	lock
	call J_Route40PokefanMScript
	release
	end

J_W_Route40Lass2Script::
	lock
	call J_Route40Lass2Script
	release
	end

J_W_Route40StandingYoungsterScript::
	lock
	call J_Route40StandingYoungsterScript
	release
	end

J_S_Route40Sign::
	lockall
	call J_Route40Sign
	releaseall
	end

J_Route40_MapScripts::
J_Route40MonicaCallback::
	clearflag FLAG_J_BATTLE_TOWER_OPEN_CIVILIANS
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 1, J_Route40MonicaCallback_MonicaAppears
	setflag FLAG_J_ROUTE_40_MONICA_OF_MONDAY
	return
J_Route40MonicaCallback_MonicaAppears:
	clearflag FLAG_J_ROUTE_40_MONICA_OF_MONDAY
	return
J_TrainerSwimmerfElaine::
J_TrainerSwimmerfElaine_Script:
	message J_SwimmerfElaineAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSwimmerfPaula::
J_TrainerSwimmerfPaula_Script:
	message J_SwimmerfPaulaAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSwimmermSimon::
J_TrainerSwimmermSimon_Script:
	message J_SwimmermSimonAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSwimmermRandall::
J_TrainerSwimmermRandall_Script:
	message J_SwimmermRandallAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route40Lass1Script::
	faceplayer
	message J_Route40Lass1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route40PokefanMScript::
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_Route40PokefanMScript_mobile
	faceplayer
	message J_Route40PokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route40PokefanMScript_mobile:
	faceplayer
	message J_Route40PokefanMText_Mobile
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route40Lass2Script::
	faceplayer
	message J_Route40Lass2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route40StandingYoungsterScript::
	faceplayer
	message J_Route40StandingYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MonicaScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_SHARP_BEAK_FROM_MONICA, J_L581
	setvar VAR_RESULT, 1
J_L581:
	goto_if_ne VAR_RESULT, 0, J_MonicaScript_Monday
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_ne VAR_RESULT, 1, J_MonicaScript_NotMonday
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_MET_MONICA_OF_MONDAY, J_L582
	setvar VAR_RESULT, 1
J_L582:
	goto_if_ne VAR_RESULT, 0, J_MonicaScript_MetMonica
	message J_MeetMonicaText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_MET_MONICA_OF_MONDAY
J_MonicaScript_MetMonica:
	message J_MonicaGivesGiftText
	waitmessage
	waitbuttonpress
	giveitem ITEM_SHARP_BEAK, 1
	goto_if_eq VAR_RESULT, 0, J_MonicaScript_done
	setflag FLAG_J_GOT_SHARP_BEAK_FROM_MONICA
	message J_MonicaGaveGiftText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MonicaScript_Monday:
	message J_MonicaMondayText
	waitmessage
	waitbuttonpress
J_MonicaScript_done:
	closemessage
	return
J_MonicaScript_NotMonday:
	message J_MonicaNotMondayText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route40Sign::
	message J_Route40SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route40Rock::
	goto EventScript_RockSmash
J_Route40HiddenHyperPotion::
	finditem ITEM_HYPER_POTION
	return
J_Route40_StepRightUp6Movement::
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
J_Route40_StepUp5Movement::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
J_Route40_StepUp4Movement::
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
J_SwimmermSimonSeenText::
	.string "You have to warm\nup before going\linto the water.\pThat's basic.$"
J_SwimmermSimonBeatenText::
	.string "OK! Uncle! I give!$"
J_SwimmermSimonAfterBattleText::
	.string "CIANWOOD CITY is\na good distance\laway from here.$"
J_SwimmermRandallSeenText::
	.string "Hey, you're young\nand fit!\pDon't ride your\nPOKéMON! Swim!$"
J_SwimmermRandallBeatenText::
	.string "Uh-oh. I lost…$"
J_SwimmermRandallAfterBattleText::
	.string "Swimming exercises\nyour entire body.\lIt's healthy.$"
J_SwimmerfElaineSeenText::
	.string "Are you going to\nCIANWOOD?\pHow about a quick\nbattle first?$"
J_SwimmerfElaineBeatenText::
	.string "I lost that one!$"
J_SwimmerfElaineAfterBattleText::
	.string "I'd say I'm a bet-\nter swimmer than\lyou. Yeah!$"
J_SwimmerfPaulaSeenText::
	.string "No inner tube for\nme.\pI'm hanging on to\na sea POKéMON!$"
J_SwimmerfPaulaBeatenText::
	.string "Ooh, I'm feeling\ndizzy!$"
J_SwimmerfPaulaAfterBattleText::
	.string "While I float like\nthis, the waves\lcarry me along.$"
J_Route40Lass1Text::
	.string "Although you can't\nsee it from here,\pCIANWOOD is across\nthe sea.$"
J_Route40PokefanMText::
	.string "Hm! There's a big\nbuilding up ahead!\pWhat is it?$"
J_Route40PokefanMText_Mobile::
	.string "Hm! Look at all\nthose serious-\llooking trainers\lstreaming in.\pWhat? What?$"
J_Route40Lass2Text::
	.string "I came to OLIVINE\nby ship to see the\psights and soak up\nthe atmosphere.\pBeing a port, it\nfeels so different\lfrom a big city.$"
J_Route40StandingYoungsterText::
	.string "Have you gone to\nthe BATTLE TOWER?\pI think a lot of\ntough trainers\phave gathered\nthere already.\pBut since you have\nso many BADGES,\pyou shouldn't do\nbadly at all.$"
J_MeetMonicaText::
	.string "MONICA: Glad to\nmeet you. I'm\pMONICA of Monday.$"
J_MonicaGivesGiftText::
	.string "As a token of our\nfriendship, I have\la gift for you!$"
J_MonicaGaveGiftText::
	.string "MONICA: It's an\nitem that raises\pthe power of fly-\ning-type moves.\pYou should equip a\nbird POKéMON with\lthat item.$"
J_MonicaMondayText::
	.string "MONICA: My broth-\ners and sisters\pare all over the\nplace.\pSee if you could\nfind them all!$"
J_MonicaNotMondayText::
	.string "MONICA: I don't\nthink today is\lMonday. How sad…$"
J_Route40SignText::
	.string "ROUTE 40\pCIANWOOD CITY -\nOLIVINE CITY$"
J_Route40_MapEvents::
