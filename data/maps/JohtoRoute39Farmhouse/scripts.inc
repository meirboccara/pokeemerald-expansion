@ KJH: translated from pokecrystal maps/Route39Farmhouse.asm by kjh_tools/johto

JohtoRoute39Farmhouse_MapScripts::
	.byte 0

J_W_PokefanM_DairyFarmer::
	lock
	call J_PokefanM_DairyFarmer
	release
	end

J_W_PokefanF_SnoreFarmer::
	lock
	call J_PokefanF_SnoreFarmer
	release
	end

J_S_FarmhouseBookshelf::
	lockall
	call J_FarmhouseBookshelf
	releaseall
	end

J_Route39Farmhouse_MapScripts::
J_PokefanM_DairyFarmer::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HEALED_MOOMOO, J_L12
	setvar VAR_RESULT, 1
J_L12:
	goto_if_ne VAR_RESULT, 0, J_FarmerMScript_SellMilk
	message J_FarmerMText_SickCow
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_TALKED_TO_FARMER_ABOUT_MOOMOO
	return
J_FarmerMScript_SellMilk::
	checkitem ITEM_MOOMOO_MILK, 1
	goto_if_ne VAR_RESULT, 0, J_FarmerMScript_Milking
	message J_FarmerMText_BuyMilk
	waitmessage
	showmoneybox 0, 0
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_FarmerMScript_NoSale
	checkmoney 0
	goto_if_eq VAR_RESULT, TRUE, J_L13
	setvar VAR_RESULT, 2
	goto J_L14
J_L13:
	setvar VAR_RESULT, 0
J_L14:
	goto_if_eq VAR_RESULT, 2, J_FarmerMScript_NoMoney
	additem ITEM_MOOMOO_MILK, 1
	goto_if_eq VAR_RESULT, 0, J_FarmerMScript_NoRoom
	removemoney 0
	showmoneybox 0, 0
	waitse
	playse SE_SHOP
	message J_FarmerMText_GotMilk
	waitmessage
	waitbuttonpress
	closemessage
	return
J_FarmerMScript_NoMoney::
	message J_FarmerMText_NoMoney
	waitmessage
	waitbuttonpress
	closemessage
	return
J_FarmerMScript_NoRoom::
	message J_FarmerMText_NoRoom
	waitmessage
	waitbuttonpress
	closemessage
	return
J_FarmerMScript_NoSale::
	message J_FarmerMText_NoSale
	waitmessage
	waitbuttonpress
	closemessage
	return
J_FarmerMScript_Milking::
	message J_FarmerMText_Milking
	waitmessage
	waitbuttonpress
	closemessage
	return
J_PokefanF_SnoreFarmer::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM13_SNORE_FROM_MOOMOO_FARM, J_L15
	setvar VAR_RESULT, 1
J_L15:
	goto_if_ne VAR_RESULT, 0, J_FarmerFScript_GotSnore
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HEALED_MOOMOO, J_L16
	setvar VAR_RESULT, 1
J_L16:
	goto_if_ne VAR_RESULT, 0, J_FarmerFScript_GiveSnore
	message J_FarmerFText_InTrouble
	waitmessage
	waitbuttonpress
	closemessage
	return
J_FarmerFScript_GiveSnore::
	message J_FarmerFText_HealedMiltank
	waitmessage
	waitbuttonpress
	giveitem ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, 0, J_FarmerFScript_NoRoomForSnore
	setflag FLAG_J_GOT_TM13_SNORE_FROM_MOOMOO_FARM
J_FarmerFScript_GotSnore::
	message J_FarmerFText_SnoreSpeech
	waitmessage
	waitbuttonpress
J_FarmerFScript_NoRoomForSnore::
	closemessage
	return
J_FarmhouseBookshelf::
	goto J_PictureBookshelfScript
J_FarmerMText_SickCow::
	.string "My MILTANK ain't\ngivin' me milk\ln'more.\pThis here FARM's\ngot famous milk.\pMost everyone\nwants a drink.\pIt'll give me lots\no' milk if'n I\pfeed it lots o'\nBERRIES, I reckon.$"
J_FarmerMText_BuyMilk::
	.string "How'd you like my\nMOOMOO MILK?\pIt's my pride and\njoy, there.\pGive it to POKéMON\nto restore HP!\pI'll give it to ya\nfer just ¥0.$"
J_FarmerMText_GotMilk::
	.string "Here ya go!\nDrink up'n enjoy!$"
J_FarmerMText_NoMoney::
	.string "Sorry, there.\nNo cash, no sale!$"
J_FarmerMText_NoRoom::
	.string "I reckon yer\nPACK's full.$"
J_FarmerMText_NoSale::
	.string "You don't want it?\nCome again, hear?$"
J_FarmerMText_Milking::
	.string "I best go do my\nmilkin'.$"
J_FarmerFText_InTrouble::
	.string "Our milk even goes\nout to KANTO.\pSo if our own\nMILTANK won't give\pus any milk, we're\nin trouble.$"
J_FarmerFText_HealedMiltank::
	.string "You fixed our\nMILTANK, hon. Now\pit gives MOOMOO\nMILK again.\pHere's somethin'\nfer your trouble.$"
J_Text_ReceivedTM13::
	.string "{PLAYER} received\nTM13.$"
J_FarmerFText_SnoreSpeech::
	.string "That there's\nSNORE.\pIt's a rare move\nthat only works\pwhile the POKéMON\nis asleep.\pYou best think how\nyou ought to use\lit, hon.$"
J_Route39Farmhouse_MapEvents::
