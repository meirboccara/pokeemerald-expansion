@ KJH: translated from pokecrystal maps/MountMortar1FOutside.asm by kjh_tools/johto

JohtoMountMortar1FOutside_MapScripts::
	.byte 0

J_MountMortar1FOutside_MapScripts::
J_MountMortar1FOutsideEther::
	finditem ITEM_ETHER, 1
	return
J_MountMortar1FOutsideRevive::
	finditem ITEM_REVIVE, 1
	return
J_MountMortar1FOutsideHiddenHyperPotion::
	finditem ITEM_HYPER_POTION
	return
J_MountMortar1FOutside_MapEvents::
