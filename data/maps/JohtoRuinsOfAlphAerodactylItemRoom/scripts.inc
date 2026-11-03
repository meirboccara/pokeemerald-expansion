@ KJH: translated from pokecrystal maps/RuinsOfAlphAerodactylItemRoom.asm by kjh_tools/johto

JohtoRuinsOfAlphAerodactylItemRoom_MapScripts::
	.byte 0

J_S_RuinsOfAlphAerodactylItemRoomAncientReplica::
	lockall
	call J_RuinsOfAlphAerodactylItemRoomAncientReplica
	releaseall
	end

J_RuinsOfAlphAerodactylItemRoom_MapScripts::
J_RuinsOfAlphAerodactylItemRoomGoldBerry::
	finditem ITEM_SITRUS_BERRY, 1
	return
J_RuinsOfAlphAerodactylItemRoomMoonStone::
	finditem ITEM_MOON_STONE, 1
	return
J_RuinsOfAlphAerodactylItemRoomHealPowder::
	finditem ITEM_HEAL_POWDER, 1
	return
J_RuinsOfAlphAerodactylItemRoomEnergyRoot::
	finditem ITEM_ENERGY_ROOT, 1
	return
J_RuinsOfAlphAerodactylItemRoomAncientReplica::
	message J_RuinsOfAlphAerodactylItemRoomAncientReplicaText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphAerodactylItemRoomAncientReplicaText::
	.string "It's a replica of\nan ancient POKé-\lMON.$"
J_RuinsOfAlphAerodactylItemRoom_MapEvents::
