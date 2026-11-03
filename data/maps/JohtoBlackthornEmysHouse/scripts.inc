@ KJH: translated from pokecrystal maps/BlackthornEmysHouse.asm by kjh_tools/johto

JohtoBlackthornEmysHouse_MapScripts::
	.byte 0

J_W_Emy::
	lock
	call J_Emy
	release
	end

J_S_EmysHouseBookshelf::
	lockall
	call J_EmysHouseBookshelf
	releaseall
	end

J_BlackthornEmysHouse_MapScripts::
J_Emy::
	faceplayer
	waitbuttonpress
	closemessage
	return
J_EmysHouseBookshelf::
	goto J_MagazineBookshelfScript
J_BlackthornEmysHouse_MapEvents::
