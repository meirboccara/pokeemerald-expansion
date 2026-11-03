@ KJH: translated from pokecrystal maps/GoldenrodBikeShop.asm by kjh_tools/johto

JohtoGoldenrodBikeShop_MapScripts::
	.byte 0

J_W_GoldenrodBikeShopClerkScript::
	lock
	call J_GoldenrodBikeShopClerkScript
	release
	end

J_S_GoldenrodBikeShopBicycle::
	lockall
	call J_GoldenrodBikeShopBicycle
	releaseall
	end

J_GoldenrodBikeShop_MapScripts::
J_GoldenrodBikeShopNoopScene::
	return
J_GoldenrodBikeShopClerkScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_BICYCLE, J_L524
	setvar VAR_RESULT, 1
J_L524:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodBikeShopClerkScript_GotBicycle
	message J_GoldenrodBikeShopClerkIntroText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_GoldenrodBikeShopClerkScript_Refused
	message J_GoldenrodBikeShopClerkAgreedText
	waitmessage
	waitbuttonpress
	waitse
	additem ITEM_BICYCLE, 1
	message J_BorrowedABicycleText
	waitmessage
	playse SE_SUCCESS
	waitse
	setflag FLAG_J_ENGINE_BIKE_SHOP_CALL_ENABLED
	setflag FLAG_J_GOT_BICYCLE
J_GoldenrodBikeShopClerkScript_GotBicycle:
	message J_GoldenrodBikeShopClerkFirstRateBikesText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodBikeShopClerkScript_Refused:
	message J_GoldenrodBikeShopClerkRefusedText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodBikeShopJustReleasedCompactBike::
	message J_GoldenrodBikeShopJustReleasedCompactBikeText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodBikeShopBicycle::
	message J_GoldenrodBikeShopBicycleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodBikeShopClerkIntroText::
	.string "…sigh… I moved\nhere, but I can't\psell my BICYCLES.\nWhy is that?\pCould you ride a\nBICYCLE and adver-\ltise for me?$"
J_GoldenrodBikeShopClerkAgreedText::
	.string "Really? Great!\pGive me your name\nand phone number,\pand I'll loan you\na BICYCLE.$"
J_BorrowedABicycleText::
	.string "{PLAYER} borrowed a\nBICYCLE.$"
J_GoldenrodBikeShopClerkFirstRateBikesText::
	.string "My BICYCLES are\nfirst-rate! You\pcan ride them\nanywhere.$"
J_GoldenrodBikeShopClerkRefusedText::
	.string "…sigh… Oh, for\nthe kindness of\lpeople…$"
J_GoldenrodBikeShopJustReleasedCompactBikeText::
	.string "Just released!\pFirst-rate compact\nBICYCLES!$"
J_GoldenrodBikeShopBicycleText::
	.string "It's a shiny new\nBICYCLE!$"
J_GoldenrodBikeShop_MapEvents::
