@ KJH: translated from pokecrystal maps/ElmsHouse.asm by kjh_tools/johto

JohtoElmsHouse_MapScripts::
	.byte 0

J_W_ElmsWife::
	lock
	call J_ElmsWife
	release
	end

J_W_ElmsSon::
	lock
	call J_ElmsSon
	release
	end

J_S_ElmsHousePC::
	lockall
	call J_ElmsHousePC
	releaseall
	end

J_S_ElmsHouseBookshelf::
	lockall
	call J_ElmsHouseBookshelf
	releaseall
	end

J_ElmsHouse_MapScripts::
J_ElmsWife::
	faceplayer
	message J_ElmsWifeText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmsSon::
	faceplayer
	message J_ElmsSonText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmsHousePC::
	message J_ElmsHousePCText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ElmsHouseBookshelf::
	goto J_DifficultBookshelfScript
J_ElmsWifeText::
	.string "Hi, {PLAYER}! My\nhusband's always\pso busy--I hope\nhe's OK.\pWhen he's caught\nup in his POKéMON\presearch, he even\nforgets to eat.$"
J_ElmsSonText::
	.string "When I grow up,\nI'm going to help\lmy dad!\pI'm going to be a\ngreat POKéMON\lprofessor!$"
J_ElmsHouseLabFoodText::
	.string "There's some food\nhere. It must be\lfor the LAB.$"
J_ElmsHousePokemonFoodText::
	.string "There's some food\nhere. This must be\lfor POKéMON.$"
J_ElmsHousePCText::
	.string "POKéMON. Where do\nthey come from? \pWhere are they\ngoing?\pWhy has no one\never witnessed a\lPOKéMON's birth?\pI want to know! I\nwill dedicate my\plife to the study\nof POKéMON!\p…\pIt's a part of\nPROF.ELM's re-\lsearch papers.$"
J_ElmsHouse_MapEvents::
