@ KJH: translated from pokecrystal maps/CianwoodPharmacy.asm by kjh_tools/johto

JohtoCianwoodPharmacy_MapScripts::
	.byte 0

J_W_CianwoodPharmacist::
	lock
	call J_CianwoodPharmacist
	release
	end

J_S_CianwoodPharmacyBookshelf::
	lockall
	call J_CianwoodPharmacyBookshelf
	releaseall
	end

J_CianwoodPharmacy_MapScripts::
J_CianwoodPharmacyNoopScene::
	return
J_CianwoodPharmacist::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_SECRETPOTION_FROM_PHARMACY, J_L594
	setvar VAR_RESULT, 1
J_L594:
	goto_if_ne VAR_RESULT, 0, J_CianwoodPharmacist_Mart
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_JASMINE_EXPLAINED_AMPHYS_SICKNESS, J_L595
	setvar VAR_RESULT, 1
J_L595:
	goto_if_eq VAR_RESULT, 0, J_CianwoodPharmacist_Mart
	message J_PharmacistGiveSecretpotionText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_HAS_SECRETPOTION
	setvar VAR_RESULT, 1
	message J_ReceivedSecretpotionText
	waitmessage
	playse SE_SUCCESS
	waitse
	setflag FLAG_J_GOT_SECRETPOTION_FROM_PHARMACY
	message J_PharmacistDescribeSecretpotionText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodPharmacist_Mart:
	pokemart J_Mart_MART_CIANWOOD
	closemessage
	return
J_CianwoodPharmacyBookshelf::
	goto J_DifficultBookshelfScript
J_PharmacistGiveSecretpotionText::
	.string "Your POKéMON ap-\npear to be fine.\pIs something wor- \nrying you?\p…\pThe LIGHTHOUSE\nPOKéMON is in\ltrouble?\pI got it!\pThis ought to do\nthe trick.$"
J_ReceivedSecretpotionText::
	.string "{PLAYER} received\nSECRETPOTION.$"
J_PharmacistDescribeSecretpotionText::
	.string "My SECRETPOTION is\na tad too strong.\pI only offer it in\nan emergency.$"
J_CianwoodPharmacy_MapEvents::
