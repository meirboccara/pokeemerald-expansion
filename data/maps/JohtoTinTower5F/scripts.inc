@ KJH: translated from pokecrystal maps/TinTower5F.asm by kjh_tools/johto

JohtoTinTower5F_MapScripts::
	.byte 0

J_TinTower5F_MapScripts::
J_TinTower5FRareCandy::
	finditem ITEM_RARE_CANDY, 1
	return
J_TinTower5FHiddenFullRestore::
	finditem ITEM_FULL_RESTORE
	return
J_TinTower5FHiddenCarbos::
	finditem ITEM_CARBOS
	return
J_TinTower5F_MapEvents::
