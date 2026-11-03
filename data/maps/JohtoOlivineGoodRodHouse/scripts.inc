@ KJH: translated from pokecrystal maps/OlivineGoodRodHouse.asm by kjh_tools/johto

JohtoOlivineGoodRodHouse_MapScripts::
	.byte 0

J_W_GoodRodGuru::
	lock
	call J_GoodRodGuru
	release
	end

J_OlivineGoodRodHouse_MapScripts::
J_GoodRodGuru::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_GOOD_ROD, J_L6
	setvar VAR_RESULT, 1
J_L6:
	goto_if_ne VAR_RESULT, 0, J_GoodRodGuru_AlreadyGotItem
	message J_OfferGoodRodText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_GoodRodGuru_DontWantIt
	message J_GiveGoodRodText
	waitmessage
	waitbuttonpress
	giveitem ITEM_GOOD_ROD, 1
	message J_GaveGoodRodText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_GOT_GOOD_ROD
	return
J_GoodRodGuru_DontWantIt:
	message J_DontWantGoodRodText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoodRodGuru_AlreadyGotItem:
	message J_HaveGoodRodText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoodRodHouseBookshelf::
	goto J_PictureBookshelfScript
J_OfferGoodRodText::
	.string "OLIVINE is on the\nsea!\pAnd if it's on the\nsea, there are\lbound to be fish!\pI've fished here\nfor 30 years.\pWould you like to\nface the sea and\lfish?$"
J_GiveGoodRodText::
	.string "Ah, hahah!\nWe have ourselves\la new angler!$"
J_GaveGoodRodText::
	.string "Fish aren't found\nin the sea alone.\pThey go wherever\nthere is water.$"
J_DontWantGoodRodText::
	.string "Whaaat? You don't\nlike to fish!?\lIncomprehensible!$"
J_HaveGoodRodText::
	.string "How are things?\nLand the big one?$"
J_OlivineGoodRodHouse_MapEvents::
