@ KJH: translated from pokecrystal maps/DanceTheater.asm by kjh_tools/johto

JohtoDanceTheater_MapScripts::
	.byte 0

J_T_TrainerKimonoGirlNaoko::
	trainerbattle_single TRAINER_J_KIMONO_GIRL_NAOKO, J_KimonoGirlNaokoSeenText, J_KimonoGirlNaokoBeatenText
	call J_TrainerKimonoGirlNaoko_Script
	release
	end

J_T_TrainerKimonoGirlSayo::
	trainerbattle_single TRAINER_J_KIMONO_GIRL_SAYO, J_KimonoGirlSayoSeenText, J_KimonoGirlSayoBeatenText
	call J_TrainerKimonoGirlSayo_Script
	release
	end

J_T_TrainerKimonoGirlZuki::
	trainerbattle_single TRAINER_J_KIMONO_GIRL_ZUKI, J_KimonoGirlZukiSeenText, J_KimonoGirlZukiBeatenText
	call J_TrainerKimonoGirlZuki_Script
	release
	end

J_T_TrainerKimonoGirlKuni::
	trainerbattle_single TRAINER_J_KIMONO_GIRL_KUNI, J_KimonoGirlKuniSeenText, J_KimonoGirlKuniBeatenText
	call J_TrainerKimonoGirlKuni_Script
	release
	end

J_T_TrainerKimonoGirlMiki::
	trainerbattle_single TRAINER_J_KIMONO_GIRL_MIKI, J_KimonoGirlMikiSeenText, J_KimonoGirlMikiBeatenText
	call J_TrainerKimonoGirlMiki_Script
	release
	end

J_W_DanceTheaterSurfGuy::
	lock
	call J_DanceTheaterSurfGuy
	release
	end

J_W_DanceTheaterRhydon::
	lock
	call J_DanceTheaterRhydon
	release
	end

J_W_DanceTheaterCooltrainerMScript::
	lock
	call J_DanceTheaterCooltrainerMScript
	release
	end

J_W_DanceTheaterGrannyScript::
	lock
	call J_DanceTheaterGrannyScript
	release
	end

J_S_DanceTheaterFancyPanel::
	lockall
	call J_DanceTheaterFancyPanel
	releaseall
	end

J_DanceTheater_MapScripts::
J_TrainerKimonoGirlNaoko::
J_TrainerKimonoGirlNaoko_Script:
	message J_KimonoGirlNaokoAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerKimonoGirlSayo::
J_TrainerKimonoGirlSayo_Script:
	message J_KimonoGirlSayoAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerKimonoGirlZuki::
J_TrainerKimonoGirlZuki_Script:
	message J_KimonoGirlZukiAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerKimonoGirlKuni::
J_TrainerKimonoGirlKuni_Script:
	message J_KimonoGirlKuniAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerKimonoGirlMiki::
J_TrainerKimonoGirlMiki_Script:
	message J_KimonoGirlMikiAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DanceTheaterSurfGuy::
	faceplayer
	message J_SurfGuyNeverLeftAScratchText
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_HM03_SURF, J_L277
	setvar VAR_RESULT, 1
J_L277:
	goto_if_ne VAR_RESULT, 0, J_SurfGuyAlreadyGaveSurf
	setvar VAR_RESULT, 0
	goto_if_unset (TRAINER_FLAGS_START + TRAINER_J_KIMONO_GIRL_NAOKO), J_L278
	setvar VAR_RESULT, 1
J_L278:
	goto_if_eq VAR_RESULT, 0, J_DanceTheaterSurfGuy_KimonoGirlsUndefeated
	setvar VAR_RESULT, 0
	goto_if_unset (TRAINER_FLAGS_START + TRAINER_J_KIMONO_GIRL_SAYO), J_L279
	setvar VAR_RESULT, 1
J_L279:
	goto_if_eq VAR_RESULT, 0, J_DanceTheaterSurfGuy_KimonoGirlsUndefeated
	setvar VAR_RESULT, 0
	goto_if_unset (TRAINER_FLAGS_START + TRAINER_J_KIMONO_GIRL_ZUKI), J_L280
	setvar VAR_RESULT, 1
J_L280:
	goto_if_eq VAR_RESULT, 0, J_DanceTheaterSurfGuy_KimonoGirlsUndefeated
	setvar VAR_RESULT, 0
	goto_if_unset (TRAINER_FLAGS_START + TRAINER_J_KIMONO_GIRL_KUNI), J_L281
	setvar VAR_RESULT, 1
J_L281:
	goto_if_eq VAR_RESULT, 0, J_DanceTheaterSurfGuy_KimonoGirlsUndefeated
	setvar VAR_RESULT, 0
	goto_if_unset (TRAINER_FLAGS_START + TRAINER_J_KIMONO_GIRL_MIKI), J_L282
	setvar VAR_RESULT, 1
J_L282:
	goto_if_eq VAR_RESULT, 0, J_DanceTheaterSurfGuy_KimonoGirlsUndefeated
	goto J_DanceTheaterSurfGuy_GetSurf
J_DanceTheaterSurfGuy_KimonoGirlsUndefeated:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_PLAYER_IS_FEMALE, J_L283
	setvar VAR_RESULT, 1
J_L283:
	goto_if_ne VAR_RESULT, 0, J_DanceTheaterSurfGuy_PlayerIsFemale
	message J_SurfGuyLadGiftText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DanceTheaterSurfGuy_PlayerIsFemale:
	message J_SurfGuyLassieGiftText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DanceTheaterSurfGuy_GetSurf:
	message J_SurfGuyLikeADanceText
	waitmessage
	waitbuttonpress
	giveitem ITEM_HM03, 1
	setflag FLAG_J_GOT_HM03_SURF
	message J_SurfGuySurfExplanationText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SurfGuyAlreadyGaveSurf::
	message J_SurfGuyElegantKimonoGirlsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DanceTheaterRhydon::
	message J_RhydonText
	waitmessage
	playmoncry SPECIES_RHYDON, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_DanceTheaterCooltrainerMScript::
	faceplayer
	message J_DanceTheaterCooltrainerMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DanceTheaterGrannyScript::
	faceplayer
	message J_DanceTheaterGrannyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_DanceTheaterFancyPanel::
	message J_DanceTheaterFancyPanelText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_KimonoGirlNaokoSeenText::
	.string "You have lovely\nPOKéMON. May I see\lthem in battle?$"
J_KimonoGirlNaokoBeatenText::
	.string "Oh, you are very\nstrong.$"
J_KimonoGirlNaokoAfterBattleText::
	.string "I enjoyed that\nbout. I would like\lto see you again.$"
J_KimonoGirlSayoSeenText::
	.string "I always dance\nwith my POKéMON.\pOf course, I also\ntrain them.$"
J_KimonoGirlSayoBeatenText::
	.string "Oh, so close!\nI almost had you.$"
J_KimonoGirlSayoAfterBattleText::
	.string "Rhythm is impor-\ntant for both\pdancing and POKé-\nMON.$"
J_KimonoGirlZukiSeenText::
	.string "Isn't my barrette\npretty?\pOh. A POKéMON\nbattle?$"
J_KimonoGirlZukiBeatenText::
	.string "I don't have any\nPOKéMON left…$"
J_KimonoGirlZukiAfterBattleText::
	.string "I put a different\nflower in my bar-\lrette every month.$"
J_KimonoGirlKuniSeenText::
	.string "Oh, you're a cute\ntrainer. Would you\llike to battle?$"
J_KimonoGirlKuniBeatenText::
	.string "You're stronger\nthan you look.$"
J_KimonoGirlKuniAfterBattleText::
	.string "I trained a lot,\nso I thought I was\pa capable trainer.\nI guess I'm not.$"
J_KimonoGirlMikiSeenText::
	.string "Do you like my\ndancing? I'm good\lat POKéMON too.$"
J_KimonoGirlMikiBeatenText::
	.string "Ooh, you're good\nat POKéMON too.$"
J_KimonoGirlMikiAfterBattleText::
	.string "I can keep dancing\nbecause there are\ppeople who enjoy\nwhat I do.\pMy POKéMON keep my\nspirits up too.$"
J_SurfGuyNeverLeftAScratchText::
	.string "Not only are the\nKIMONO GIRLS great\pdancers, they're\nalso skilled at\lPOKéMON.\pI always challenge\nthem, but I've\pnever even left a\nscratch…$"
J_SurfGuyLadGiftText::
	.string "Lad! If you can\ndefeat all the\pKIMONO GIRLS, I'll\ngive you a gift.$"
J_SurfGuyLassieGiftText::
	.string "Lassie, if you can\ndefeat all the\pKIMONO GIRLS, I'll\ngive you a gift.$"
J_SurfGuyLikeADanceText::
	.string "The way you bat-\ntled, it was like\lwatching a dance.\pIt was a rare\ntreat to see!\pI want you to have\nthis. Don't worry\l--take it!$"
J_SurfGuySurfExplanationText::
	.string "That's SURF.\pIt's a move that\nlets POKéMON swim\lacross water.$"
J_SurfGuyElegantKimonoGirlsText::
	.string "I wish my POKéMON\nwere as elegant as\lthe KIMONO GIRLS…$"
J_RhydonText::
	.string "RHYDON: Gugooh\ngugogooh!$"
J_DanceTheaterCooltrainerMText::
	.string "That man's always\nwith his RHYDON.\pSays he wants a\nPOKéMON that can\lSURF and dance.\pIs he trying to\nmake a synchro-\lnized swimming\lPOKéMON?$"
J_DanceTheaterGrannyText::
	.string "The KIMONO GIRLS\nare so beautiful…\pBut they have to\ngo through rigor-\lous training.\pAnd they have to\nlearn to follow\pcustoms before ap-\npearing in public.\pBut if you love\nsomething, any-\lthing is possible.$"
J_DanceTheaterFancyPanelText::
	.string "It's a fancy panel\nthat's decorated\lwith flowers.$"
J_DanceTheater_MapEvents::
