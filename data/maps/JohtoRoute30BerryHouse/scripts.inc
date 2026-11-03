@ KJH: translated from pokecrystal maps/Route30BerryHouse.asm by kjh_tools/johto

JohtoRoute30BerryHouse_MapScripts::
	.byte 0

J_W_Route30BerryHousePokefanMScript::
	lock
	call J_Route30BerryHousePokefanMScript
	release
	end

J_S_Route30BerryHouseBookshelf::
	lockall
	call J_Route30BerryHouseBookshelf
	releaseall
	end

J_Route30BerryHouse_MapScripts::
J_Route30BerryHousePokefanMScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_BERRY_FROM_ROUTE_30_HOUSE, J_L689
	setvar VAR_RESULT, 1
J_L689:
	goto_if_ne VAR_RESULT, 0, J_Route30BerryHousePokefanMScript_GotBerry
	message J_Route30BerrySpeechHouseMonEatBerriesText
	waitmessage
	waitbuttonpress
	giveitem ITEM_ORAN_BERRY, 1
	goto_if_eq VAR_RESULT, 0, J_Route30BerryHousePokefanMScript_NoRoom
	setflag FLAG_J_GOT_BERRY_FROM_ROUTE_30_HOUSE
J_Route30BerryHousePokefanMScript_GotBerry:
	message J_Route30BerrySpeechHouseCheckTreesText
	waitmessage
	waitbuttonpress
J_Route30BerryHousePokefanMScript_NoRoom:
	closemessage
	return
J_Route30BerryHouseBookshelf::
	goto J_MagazineBookshelfScript
J_Route30BerrySpeechHouseMonEatBerriesText::
	.string "You know, POKéMON\neat BERRIES.\pWell, my POKéMON\ngot healthier by\leating a BERRY.\pHere. I'll share\none with you!$"
J_Route30BerrySpeechHouseCheckTreesText::
	.string "Check trees for\nBERRIES. They just\ldrop right off.$"
J_Route30BerryHouse_MapEvents::
