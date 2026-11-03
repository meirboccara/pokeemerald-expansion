@ KJH: translated from pokecrystal maps/Route41.asm by kjh_tools/johto

JohtoRoute41_MapScripts::
	.byte 0

J_T_TrainerSwimmermCharlie::
	trainerbattle_single TRAINER_J_SWIMMERM_CHARLIE, J_SwimmermCharlieSeenText, J_SwimmermCharlieBeatenText
	call J_TrainerSwimmermCharlie_Script
	release
	end

J_T_TrainerSwimmermGeorge::
	trainerbattle_single TRAINER_J_SWIMMERM_GEORGE, J_SwimmermGeorgeSeenText, J_SwimmermGeorgeBeatenText
	call J_TrainerSwimmermGeorge_Script
	release
	end

J_T_TrainerSwimmermBerke::
	trainerbattle_single TRAINER_J_SWIMMERM_BERKE, J_SwimmermBerkeSeenText, J_SwimmermBerkeBeatenText
	call J_TrainerSwimmermBerke_Script
	release
	end

J_T_TrainerSwimmermKirk::
	trainerbattle_single TRAINER_J_SWIMMERM_KIRK, J_SwimmermKirkSeenText, J_SwimmermKirkBeatenText
	call J_TrainerSwimmermKirk_Script
	release
	end

J_T_TrainerSwimmermMathew::
	trainerbattle_single TRAINER_J_SWIMMERM_MATHEW, J_SwimmermMathewSeenText, J_SwimmermMathewBeatenText
	call J_TrainerSwimmermMathew_Script
	release
	end

J_T_TrainerSwimmerfKaylee::
	trainerbattle_single TRAINER_J_SWIMMERF_KAYLEE, J_SwimmerfKayleeSeenText, J_SwimmerfKayleeBeatenText
	call J_TrainerSwimmerfKaylee_Script
	release
	end

J_T_TrainerSwimmerfSusie::
	trainerbattle_single TRAINER_J_SWIMMERF_SUSIE, J_SwimmerfSusieSeenText, J_SwimmerfSusieBeatenText
	call J_TrainerSwimmerfSusie_Script
	release
	end

J_T_TrainerSwimmerfDenise::
	trainerbattle_single TRAINER_J_SWIMMERF_DENISE, J_SwimmerfDeniseSeenText, J_SwimmerfDeniseBeatenText
	call J_TrainerSwimmerfDenise_Script
	release
	end

J_T_TrainerSwimmerfKara::
	trainerbattle_single TRAINER_J_SWIMMERF_KARA, J_SwimmerfKaraSeenText, J_SwimmerfKaraBeatenText
	call J_TrainerSwimmerfKara_Script
	release
	end

J_T_TrainerSwimmerfWendy::
	trainerbattle_single TRAINER_J_SWIMMERF_WENDY, J_SwimmerfWendySeenText, J_SwimmerfWendyBeatenText
	call J_TrainerSwimmerfWendy_Script
	release
	end

J_Route41_MapScripts::
J_TrainerSwimmerfKaylee::
J_TrainerSwimmerfKaylee_Script:
	message J_SwimmerfKayleeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSwimmerfSusie::
J_TrainerSwimmerfSusie_Script:
	message J_SwimmerfSusieAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSwimmerfDenise::
J_TrainerSwimmerfDenise_Script:
	message J_SwimmerfDeniseAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSwimmerfKara::
J_TrainerSwimmerfKara_Script:
	message J_SwimmerfKaraAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSwimmerfWendy::
J_TrainerSwimmerfWendy_Script:
	message J_SwimmerfWendyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSwimmermCharlie::
J_TrainerSwimmermCharlie_Script:
	message J_SwimmermCharlieAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSwimmermGeorge::
J_TrainerSwimmermGeorge_Script:
	message J_SwimmermGeorgeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSwimmermBerke::
J_TrainerSwimmermBerke_Script:
	message J_SwimmermBerkeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSwimmermKirk::
J_TrainerSwimmermKirk_Script:
	message J_SwimmermKirkAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSwimmermMathew::
J_TrainerSwimmermMathew_Script:
	message J_SwimmermMathewAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route41Rock::
	goto EventScript_RockSmash
J_Route41HiddenMaxEther::
	finditem ITEM_MAX_ETHER
	return
J_SwimmermCharlieSeenText::
	.string "The water's warm\nhere. I'm loose\land limber.\pSure, I'll take\nyou on!$"
J_SwimmermCharlieBeatenText::
	.string "Yikes! I've got\nprune skin!$"
J_SwimmermCharlieAfterBattleText::
	.string "Isn't it relaxing\njust floating like\lthis?$"
J_SwimmermGeorgeSeenText::
	.string "I'm a bit tired.\nIf I win, lend me\lyour POKéMON.$"
J_SwimmermGeorgeBeatenText::
	.string "Pant, pant…$"
J_SwimmermGeorgeAfterBattleText::
	.string "It's so far to\nCIANWOOD.\pBut it's no easy\nreturn trip to\lOLIVINE either.\pWhat should I do?$"
J_SwimmermBerkeSeenText::
	.string "See those islands\nthat are blocked\lby whirlpools?\pThere just has to\nbe a secret!$"
J_SwimmermBerkeBeatenText::
	.string "What's the secret\nto your strength?$"
J_SwimmermBerkeAfterBattleText::
	.string "It was a dark and\nstormy night…\pI saw this giant\nPOKéMON flying\lfrom the islands.\pIt was scattering\nfeathers from its\lsilver wings.$"
J_SwimmermKirkSeenText::
	.string "The waves are wild\nhere.\pThey tire you out\nwhile you swim.$"
J_SwimmermKirkBeatenText::
	.string "I'm beat!$"
J_SwimmermKirkAfterBattleText::
	.string "The currents keep\nme from reaching\lthat island.$"
J_SwimmermMathewSeenText::
	.string "Are you seeking\nthe secrets of\lWHIRL ISLANDS?$"
J_SwimmermMathewBeatenText::
	.string "Ooh, you've got\ngreat endurance!$"
J_SwimmermMathewAfterBattleText::
	.string "A secret about\nWHIRL ISLANDS…\pIt's pitch-black\ninside!$"
J_SwimmerfKayleeSeenText::
	.string "I'm on my way to\nWHIRL ISLANDS.\pI'm going explor-\ning with friends.$"
J_SwimmerfKayleeBeatenText::
	.string "Is that how you do\nit?$"
J_SwimmerfKayleeAfterBattleText::
	.string "There's supposed\nto be a big POKé-\lMON deep beneath\lWHIRL ISLANDS.\pI wonder what it\ncould be?$"
J_SwimmerfSusieSeenText::
	.string "You look so ele-\ngant, riding your\lPOKéMON.$"
J_SwimmerfSusieBeatenText::
	.string "I'm crushed…$"
J_SwimmerfSusieAfterBattleText::
	.string "Wasn't there a hit\nsong about a boy\lriding a LAPRAS?$"
J_SwimmerfDeniseSeenText::
	.string "The weather is so\nbeautiful, I'm in\la daze!$"
J_SwimmerfDeniseBeatenText::
	.string "Ohhh!$"
J_SwimmerfDeniseAfterBattleText::
	.string "A sunburn is the\nworst for skin.\pBut I don't use a\nsunblock.\pI won't pollute\nthe water.$"
J_SwimmerfKaraSeenText::
	.string "If you need to\nrest, just tread\lwater.\pYou'll get your\nwind back, so you\pcan keep on going\nstrong.$"
J_SwimmerfKaraBeatenText::
	.string "Oh! You have more\nenergy than I do.$"
J_SwimmerfKaraAfterBattleText::
	.string "I heard roars from\ndeep inside the\lISLANDS.$"
J_SwimmerfWendySeenText::
	.string "At night, STARYU\ngather near the\lwater's surface.$"
J_SwimmerfWendyBeatenText::
	.string "Oh, dear…$"
J_SwimmerfWendyAfterBattleText::
	.string "The clusters of\nSTARYU light up\lat the same time.\pIt's so beautiful,\nit's scary.$"
J_Route41_MapEvents::
