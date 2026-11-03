@ KJH: translated from pokecrystal maps/MoveDeletersHouse.asm by kjh_tools/johto

JohtoMoveDeletersHouse_MapScripts::
	.byte 0

J_W_MoveDeleter::
	lock
	call J_MoveDeleter
	release
	end

J_S_MoveDeletersHouseBookshelf::
	lockall
	call J_MoveDeletersHouseBookshelf
	releaseall
	end

J_MoveDeletersHouse_MapScripts::
J_MoveDeleter::
	faceplayer
	setvar VAR_RESULT, 0
	waitbuttonpress
	closemessage
	return
J_MoveDeletersHouseBookshelf::
	goto J_DifficultBookshelfScript
J_MoveDeletersHouse_MapEvents::
