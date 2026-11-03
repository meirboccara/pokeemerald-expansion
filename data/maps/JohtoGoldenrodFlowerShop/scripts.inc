@ KJH: translated from pokecrystal maps/GoldenrodFlowerShop.asm by kjh_tools/johto

JohtoGoldenrodFlowerShop_MapScripts::
	.byte 0

J_W_FlowerShopTeacherScript::
	lock
	call J_FlowerShopTeacherScript
	release
	end

J_W_FlowerShopFloriaScript::
	lock
	call J_FlowerShopFloriaScript
	release
	end

J_GoldenrodFlowerShop_MapScripts::
J_FlowerShopTeacherScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOUGHT_SUDOWOODO, J_L529
	setvar VAR_RESULT, 1
J_L529:
	goto_if_ne VAR_RESULT, 0, J_FlowerShopTeacherScript_Lalala
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_SQUIRTBOTTLE, J_L530
	setvar VAR_RESULT, 1
J_L530:
	goto_if_ne VAR_RESULT, 0, J_FlowerShopTeacherScript_GotSquirtbottle
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_MET_FLORIA, J_L531
	setvar VAR_RESULT, 1
J_L531:
	goto_if_eq VAR_RESULT, 0, J_FlowerShopTeacherScript_HaventMetFloria
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TALKED_TO_FLORIA_AT_FLOWER_SHOP, J_L532
	setvar VAR_RESULT, 1
J_L532:
	goto_if_eq VAR_RESULT, 0, J_FlowerShopTeacherScript_Lalala
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE03_GET, J_L533
	setvar VAR_RESULT, 1
J_L533:
	goto_if_eq VAR_RESULT, 0, J_FlowerShopTeacherScript_NoPlainBadge
	faceplayer
	message J_GoldenrodFlowerShopTeacherHeresTheSquirtbottleText
	waitmessage
	waitbuttonpress
	bufferstring STR_VAR_2, J_ItemName_SQUIRTBOTTLE
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
	message J_Text_ReceivedKeyItem
	waitmessage
	waitfanfare
	setflag FLAG_J_HAS_SQUIRTBOTTLE
	setvar VAR_RESULT, 1
	setflag FLAG_J_GOT_SQUIRTBOTTLE
	closemessage
	setflag FLAG_J_FLORIA_AT_SUDOWOODO
	clearflag FLAG_J_FLORIA_AT_FLOWER_SHOP
	return
J_FlowerShopTeacherScript_Lalala:
	turnobject 1, DIR_WEST
	message J_GoldenrodFlowerShopTeacherLalalaHavePlentyOfWaterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_FlowerShopTeacherScript_GotSquirtbottle:
	faceplayer
	message J_GoldenrodFlowerShopTeacherDontDoAnythingDangerousText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_FlowerShopTeacherScript_NoPlainBadge:
	faceplayer
	message J_GoldenrodFlowerShopTeacherAskWantToBorrowWaterBottleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_FlowerShopTeacherScript_HaventMetFloria:
	faceplayer
	message J_GoldenrodFlowerShopTeacherMySisterWentToSeeWigglyTreeRoute36Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_FlowerShopFloriaScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOUGHT_SUDOWOODO, J_L534
	setvar VAR_RESULT, 1
J_L534:
	goto_if_ne VAR_RESULT, 0, J_FlowerShopFloriaScript_FoughtSudowoodo
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_SQUIRTBOTTLE, J_L535
	setvar VAR_RESULT, 1
J_L535:
	goto_if_ne VAR_RESULT, 0, J_FlowerShopFloriaScript_GotSquirtbottle
	message J_GoldenrodFlowerShopFloriaWonderIfSisWillLendWaterBottleText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_TALKED_TO_FLORIA_AT_FLOWER_SHOP
	setflag FLAG_J_FLORIA_AT_FLOWER_SHOP
	clearflag FLAG_J_FLORIA_AT_SUDOWOODO
	return
J_FlowerShopFloriaScript_GotSquirtbottle:
	message J_GoldenrodFlowerShopFloriaYouBeatWhitneyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_FlowerShopFloriaScript_FoughtSudowoodo:
	message J_GoldenrodFlowerShopFloriaItReallyWasAMonText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_FlowerShopShelf1::
	goto J_PictureBookshelfScript
J_FlowerShopShelf2::
	goto J_MagazineBookshelfScript
J_FlowerShopRadio::
	goto J_Radio2Script
J_GoldenrodFlowerShopTeacherMySisterWentToSeeWigglyTreeRoute36Text::
	.string "Have you seen that\nwiggly tree that's\pgrowing on ROUTE\n36?\pMy little sister\ngot all excited\pand went to see\nit…\pI'm worried… Isn't\nit dangerous?$"
J_GoldenrodFlowerShopTeacherAskWantToBorrowWaterBottleText::
	.string "Do you want to\nborrow the water\pbottle too?\nI don't want you\pdoing anything\ndangerous with it.$"
J_GoldenrodFlowerShopTeacherHeresTheSquirtbottleText::
	.string "Oh, you're better\nthan WHITNEY…\pYou'll be OK,\nthen. Here's the\lSQUIRTBOTTLE!$"
J_GoldenrodFlowerShopTeacherDontDoAnythingDangerousText::
	.string "Don't do anything\ntoo dangerous!$"
J_GoldenrodFlowerShopTeacherLalalaHavePlentyOfWaterText::
	.string "Lalala lalalala.\nHave plenty of\lwater, my lovely!$"
J_GoldenrodFlowerShopFloriaWonderIfSisWillLendWaterBottleText::
	.string "When I told my sis\nabout the jiggly\ptree, she told me\nit's dangerous.\pIf I beat WHITNEY,\nI wonder if she'll\plend me her water\nbottle…$"
J_GoldenrodFlowerShopFloriaYouBeatWhitneyText::
	.string "Wow, you beat\nWHITNEY? Cool!$"
J_GoldenrodFlowerShopFloriaItReallyWasAMonText::
	.string "So it really was a\nPOKéMON!$"
J_GoldenrodFlowerShop_MapEvents::
