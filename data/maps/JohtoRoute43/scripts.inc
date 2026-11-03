@ KJH: translated from pokecrystal maps/Route43.asm by kjh_tools/johto

JohtoRoute43_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoRoute43_OnTransition
	.byte 0

JohtoRoute43_OnTransition:
	call J_Route43CheckIfRocketsScene
	end

J_T_TrainerPokemaniacBen::
	trainerbattle_single TRAINER_J_POKEMANIAC_BEN, J_PokemaniacBenSeenText, J_PokemaniacBenBeatenText
	call J_TrainerPokemaniacBen_Script
	release
	end

J_T_TrainerPokemaniacBrent::
	trainerbattle_single TRAINER_J_POKEMANIAC_BRENT1, J_PokemaniacBrentSeenText, J_PokemaniacBrentBeatenText
	call J_TrainerPokemaniacBrent_Script
	release
	end

J_T_TrainerPokemaniacRon::
	trainerbattle_single TRAINER_J_POKEMANIAC_RON, J_PokemaniacRonSeenText, J_PokemaniacRonBeatenText
	call J_TrainerPokemaniacRon_Script
	release
	end

J_T_TrainerFisherMarvin::
	trainerbattle_single TRAINER_J_FISHER_MARVIN, J_FisherMarvinSeenText, J_FisherMarvinBeatenText
	call J_TrainerFisherMarvin_Script
	release
	end

J_T_TrainerPicnickerTiffany::
	trainerbattle_single TRAINER_J_PICNICKER_TIFFANY3, J_PicnickerTiffanySeenText, J_PicnickerTiffanyBeatenText
	call J_TrainerPicnickerTiffany_Script
	release
	end

J_T_TrainerCamperSpencer::
	trainerbattle_single TRAINER_J_CAMPER_SPENCER, J_CamperSpencerSeenText, J_CamperSpencerBeatenText
	call J_TrainerCamperSpencer_Script
	release
	end

J_W_Route43FruitTree::
	lock
	call J_Route43FruitTree
	release
	end

J_S_Route43Sign1::
	lockall
	call J_Route43Sign1
	releaseall
	end

J_S_Route43Sign2::
	lockall
	call J_Route43Sign2
	releaseall
	end

J_S_Route43TrainerTips::
	lockall
	call J_Route43TrainerTips
	releaseall
	end

J_Route43_MapScripts::
J_Route43CheckIfRocketsScene::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_ROCKET_HIDEOUT, J_L386
	setvar VAR_RESULT, 1
J_L386:
	goto_if_ne VAR_RESULT, 0, J_Route43CheckIfRocketsScene_NoRockets
	setvar VAR_J_SCENE_ROUTE_43_GATE, 0
	return
J_Route43CheckIfRocketsScene_NoRockets:
	setvar VAR_J_SCENE_ROUTE_43_GATE, 1
	return
J_TrainerCamperSpencer::
J_TrainerCamperSpencer_Script:
	message J_CamperSpencerAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPokemaniacBen::
J_TrainerPokemaniacBen_Script:
	message J_PokemaniacBenAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPokemaniacBrent::
J_TrainerPokemaniacBrent_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_BRENT_READY_FOR_REMATCH, J_L387
	setvar VAR_RESULT, 1
J_L387:
	goto_if_ne VAR_RESULT, 0, J_TrainerPokemaniacBrent_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerPokemaniacBrent_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BRENT_ASKED_FOR_PHONE_NUMBER, J_L388
	setvar VAR_RESULT, 1
J_L388:
	goto_if_ne VAR_RESULT, 0, J_TrainerPokemaniacBrent_AskedAlready
	message J_PokemaniacBrentAfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_BRENT_ASKED_FOR_PHONE_NUMBER
	call J_TrainerPokemaniacBrent_AskNumber1
	goto J_TrainerPokemaniacBrent_AskForNumber
J_TrainerPokemaniacBrent_AskedAlready:
	call J_TrainerPokemaniacBrent_AskNumber2
J_TrainerPokemaniacBrent_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerPokemaniacBrent_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerPokemaniacBrent_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_POKEMANIAC_BRENT1
	call J_TrainerPokemaniacBrent_RegisteredNumber
	goto J_TrainerPokemaniacBrent_NumberAccepted
J_TrainerPokemaniacBrent_WantsBattle:
	call J_TrainerPokemaniacBrent_Rematch
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 3, J_TrainerPokemaniacBrent_Fight3
	goto_if_eq VAR_RESULT, 2, J_TrainerPokemaniacBrent_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerPokemaniacBrent_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerPokemaniacBrent_LoadFight0
J_TrainerPokemaniacBrent_Fight3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L389
	setvar VAR_RESULT, 1
J_L389:
	goto_if_ne VAR_RESULT, 0, J_TrainerPokemaniacBrent_LoadFight3
J_TrainerPokemaniacBrent_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L390
	setvar VAR_RESULT, 1
J_L390:
	goto_if_ne VAR_RESULT, 0, J_TrainerPokemaniacBrent_LoadFight2
J_TrainerPokemaniacBrent_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_ROCKET_HIDEOUT, J_L391
	setvar VAR_RESULT, 1
J_L391:
	goto_if_ne VAR_RESULT, 0, J_TrainerPokemaniacBrent_LoadFight1
J_TrainerPokemaniacBrent_LoadFight0:
	trainerbattle_no_intro TRAINER_J_POKEMANIAC_BRENT1, J_PokemaniacBrentBeatenText
	clearflag FLAG_J_ENGINE_BRENT_READY_FOR_REMATCH
	return
J_TrainerPokemaniacBrent_LoadFight1:
	trainerbattle_no_intro TRAINER_J_POKEMANIAC_BRENT2, J_Text_Empty
	clearflag FLAG_J_ENGINE_BRENT_READY_FOR_REMATCH
	return
J_TrainerPokemaniacBrent_LoadFight2:
	trainerbattle_no_intro TRAINER_J_POKEMANIAC_BRENT3, J_Text_Empty
	clearflag FLAG_J_ENGINE_BRENT_READY_FOR_REMATCH
	return
J_TrainerPokemaniacBrent_LoadFight3:
	trainerbattle_no_intro TRAINER_J_POKEMANIAC_BRENT4, J_Text_Empty
	clearflag FLAG_J_ENGINE_BRENT_READY_FOR_REMATCH
	return
J_TrainerPokemaniacBrent_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerPokemaniacBrent_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerPokemaniacBrent_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerPokemaniacBrent_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerPokemaniacBrent_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerPokemaniacBrent_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerPokemaniacBrent_Rematch:
	goto J_Std_Nop
	return
J_TrainerPokemaniacRon::
J_TrainerPokemaniacRon_Script:
	message J_PokemaniacRonAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerFisherMarvin::
J_TrainerFisherMarvin_Script:
	message J_FisherMarvinAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPicnickerTiffany::
J_TrainerPicnickerTiffany_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_TIFFANY_READY_FOR_REMATCH, J_L392
	setvar VAR_RESULT, 1
J_L392:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerTiffany_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_TIFFANY_HAS_PINK_BOW, J_L393
	setvar VAR_RESULT, 1
J_L393:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerTiffany_HasPinkBow
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerTiffany_NumberAccepted
	setvar VAR_0x8004, SPECIES_CLEFAIRY
	special KJH_CheckPartySpecies
	goto_if_eq VAR_RESULT, 0, J_TrainerPicnickerTiffany_NoClefairy
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TIFFANY_ASKED_FOR_PHONE_NUMBER, J_L394
	setvar VAR_RESULT, 1
J_L394:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerTiffany_AskedAlready
	message J_PicnickerTiffanyWantsPicnicText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_TIFFANY_ASKED_FOR_PHONE_NUMBER
	call J_TrainerPicnickerTiffany_AskNumber1
	goto J_TrainerPicnickerTiffany_AskForNumber
J_TrainerPicnickerTiffany_AskedAlready:
	call J_TrainerPicnickerTiffany_AskNumber2
J_TrainerPicnickerTiffany_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerPicnickerTiffany_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerPicnickerTiffany_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_PICNICKER_TIFFANY3
	call J_TrainerPicnickerTiffany_RegisteredNumber
	goto J_TrainerPicnickerTiffany_NumberAccepted
J_TrainerPicnickerTiffany_WantsBattle:
	call J_TrainerPicnickerTiffany_Rematch
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 3, J_TrainerPicnickerTiffany_Fight3
	goto_if_eq VAR_RESULT, 2, J_TrainerPicnickerTiffany_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerPicnickerTiffany_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerPicnickerTiffany_LoadFight0
J_TrainerPicnickerTiffany_Fight3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L395
	setvar VAR_RESULT, 1
J_L395:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerTiffany_LoadFight3
J_TrainerPicnickerTiffany_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L396
	setvar VAR_RESULT, 1
J_L396:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerTiffany_LoadFight2
J_TrainerPicnickerTiffany_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L397
	setvar VAR_RESULT, 1
J_L397:
	goto_if_ne VAR_RESULT, 0, J_TrainerPicnickerTiffany_LoadFight1
J_TrainerPicnickerTiffany_LoadFight0:
	trainerbattle_no_intro TRAINER_J_PICNICKER_TIFFANY3, J_PicnickerTiffanyBeatenText
	clearflag FLAG_J_ENGINE_TIFFANY_READY_FOR_REMATCH
	return
J_TrainerPicnickerTiffany_LoadFight1:
	trainerbattle_no_intro TRAINER_J_PICNICKER_TIFFANY1, J_Text_Empty
	clearflag FLAG_J_ENGINE_TIFFANY_READY_FOR_REMATCH
	return
J_TrainerPicnickerTiffany_LoadFight2:
	trainerbattle_no_intro TRAINER_J_PICNICKER_TIFFANY2, J_Text_Empty
	clearflag FLAG_J_ENGINE_TIFFANY_READY_FOR_REMATCH
	return
J_TrainerPicnickerTiffany_LoadFight3:
	trainerbattle_no_intro TRAINER_J_PICNICKER_TIFFANY4, J_Text_Empty
	clearflag FLAG_J_ENGINE_TIFFANY_READY_FOR_REMATCH
	return
J_TrainerPicnickerTiffany_HasPinkBow:
	call J_TrainerPicnickerTiffany_Gift
	giveitem ITEM_SILK_SCARF, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerPicnickerTiffany_NoRoom
	clearflag FLAG_J_ENGINE_TIFFANY_HAS_PINK_BOW
	setflag FLAG_J_TIFFANY_GAVE_PINK_BOW
	goto J_TrainerPicnickerTiffany_NumberAccepted
J_TrainerPicnickerTiffany_NoRoom:
	goto J_TrainerPicnickerTiffany_PackFull
J_TrainerPicnickerTiffany_NoClefairy:
	message J_PicnickerTiffanyClefairyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPicnickerTiffany_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerPicnickerTiffany_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerPicnickerTiffany_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerPicnickerTiffany_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerPicnickerTiffany_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerPicnickerTiffany_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerPicnickerTiffany_Rematch:
	goto J_Std_Nop
	return
J_TrainerPicnickerTiffany_Gift:
	goto J_Std_Nop
	return
J_TrainerPicnickerTiffany_PackFull:
	goto J_Std_Nop
	return
J_Route43Sign1::
	message J_Route43Sign1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route43Sign2::
	message J_Route43Sign2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route43TrainerTips::
	message J_Route43TrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route43FruitTree::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_Route43MaxEther::
	finditem ITEM_MAX_ETHER, 1
	return
J_PokemaniacBenSeenText::
	.string "I love POKéMON!\pThat's why I\nstarted--and why\pI'll keep on col-\nlecting POKéMON!$"
J_PokemaniacBenBeatenText::
	.string "How could you do\nthis to me?$"
J_PokemaniacBenAfterBattleText::
	.string "What else do I\nlike besides\lPOKéMON?\pMARY on the radio.\nI bet she's cute!$"
J_PokemaniacBrentSeenText::
	.string "Hey! Do you have\nany rare POKéMON?$"
J_PokemaniacBrentBeatenText::
	.string "Oh, my poor POKé-\nMON! Darlings!$"
J_PokemaniacBrentAfterBattleText::
	.string "I'd be happy just\nto own a single\lrare POKéMON.$"
J_PokemaniacRonSeenText::
	.string "Would you get\nthis?\pSome {RIVAL} guy\nmade fun of my\lPOKéMON!\pDarn it! My POKé-\nMON's great!$"
J_PokemaniacRonBeatenText::
	.string "My NIDOKING did\npretty right on!$"
J_PokemaniacRonAfterBattleText::
	.string "It's okay for\npeople to like\pdifferent types\nof POKéMON.\pPOKéMON isn't just\nabout having the\lmost powerful one.$"
J_FisherMarvinSeenText::
	.string "I'm in a slump.\pMaybe it's the\ngear I'm using.\pLet's battle for a\nchange of pace!$"
J_FisherMarvinBeatenText::
	.string "I lost, but I feel\nbetter anyway.$"
J_FisherMarvinAfterBattleText::
	.string "KURT's LURE BALL\nis the best for\pcatching hooked\nPOKéMON.\pIt's much more\neffective than a\lULTRA BALL.$"
J_CamperSpencerSeenText::
	.string "I can do so much\nwith my POKéMON--\lit's super-fun!$"
J_CamperSpencerBeatenText::
	.string "Losing isn't fun\nat all…$"
J_CamperSpencerAfterBattleText::
	.string "What is going on\nat LAKE OF RAGE?\pWe were planning\nto camp there.$"
J_PicnickerTiffanySeenText::
	.string "Are you going to\nLAKE OF RAGE too?\pLet's play for a \nlittle while!$"
J_PicnickerTiffanyBeatenText::
	.string "I played too much!$"
J_PicnickerTiffanyWantsPicnicText::
	.string "I'm having a pic-\nnic with POKéMON.\pWon't you join us?$"
J_PicnickerTiffanyClefairyText::
	.string "Isn't my CLEFAIRY\njust the most\ladorable thing?$"
J_Route43Sign1Text::
	.string "ROUTE 43\pLAKE OF RAGE -\nMAHOGANY TOWN$"
J_Route43Sign2Text::
	.string "ROUTE 43\pLAKE OF RAGE -\nMAHOGANY TOWN$"
J_Route43TrainerTipsText::
	.string "TRAINER TIPS\pAll POKéMON have\npros and cons\pdepending on their\ntypes.\pIf their types\ndiffer, a stronger\pPOKéMON may\nlose in battle.\pLearn which types\nare strong and\pweak against your\nPOKéMON's type.$"
J_Route43_MapEvents::
