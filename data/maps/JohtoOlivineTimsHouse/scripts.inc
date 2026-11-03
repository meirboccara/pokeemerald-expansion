@ KJH: translated from pokecrystal maps/OlivineTimsHouse.asm by kjh_tools/johto

JohtoOlivineTimsHouse_MapScripts::
	.byte 0

J_W_Tim::
	lock
	call J_Tim
	release
	end

J_S_TimsHouseBookshelf::
	lockall
	call J_TimsHouseBookshelf
	releaseall
	end

J_OlivineTimsHouse_MapScripts::
J_Tim::
	faceplayer
	waitbuttonpress
	closemessage
	return
J_TimsHouseBookshelf::
	goto J_MagazineBookshelfScript
J_OlivineTimsHouse_MapEvents::
