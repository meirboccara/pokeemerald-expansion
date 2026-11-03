@ KJH: translated from pokecrystal maps/Route28SteelWingHouse.asm by kjh_tools/johto

JohtoRoute28SteelWingHouse_MapScripts::
	.byte 0

J_W_Celebrity::
	lock
	call J_Celebrity
	release
	end

J_W_CelebritysFearow::
	lock
	call J_CelebritysFearow
	release
	end

J_S_CelebrityHouseBookshelf::
	lockall
	call J_CelebrityHouseBookshelf
	releaseall
	end

J_Route28SteelWingHouse_MapScripts::
J_Route28SteelWingHouseNoopScene::
	return
J_Celebrity::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM47_STEEL_WING, J_L580
	setvar VAR_RESULT, 1
J_L580:
	goto_if_ne VAR_RESULT, 0, J_Celebrity_AlreadyGotItem
	message J_CelebrityText1
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM47, 1
	goto_if_eq VAR_RESULT, 0, J_Celebrity_Done
	setflag FLAG_J_GOT_TM47_STEEL_WING
J_Celebrity_Done:
	closemessage
	return
J_Celebrity_AlreadyGotItem:
	message J_CelebrityText2
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CelebritysFearow::
	message J_CelebritysFearowText
	waitmessage
	playmoncry SPECIES_FEAROW, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_CelebrityHouseBookshelf::
	goto J_MagazineBookshelfScript
J_CelebrityText1::
	.string "Oh, dear.\nYou've found me.\pPlease don't tell\nanyone about me.\pI'll give you this\nfor keeping my\lsecret. Please?$"
J_CelebrityText2::
	.string "It's tough being a\ntop celebrity.\pEverywhere I go,\npeople chase me.\pI just want to be\nleft alone…$"
J_CelebritysFearowText::
	.string "FEAROW: Feero!$"
J_Route28SteelWingHouse_MapEvents::
