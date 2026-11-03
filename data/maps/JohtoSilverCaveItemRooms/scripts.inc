@ KJH: translated from pokecrystal maps/SilverCaveItemRooms.asm by kjh_tools/johto

JohtoSilverCaveItemRooms_MapScripts::
	.byte 0

J_SilverCaveItemRooms_MapScripts::
J_SilverCaveItemRoomsMaxRevive::
	finditem ITEM_MAX_REVIVE, 1
	return
J_SilverCaveItemRoomsFullRestore::
	finditem ITEM_FULL_RESTORE, 1
	return
J_SilverCaveItemRooms_MapEvents::
