@ KJH: translated from pokecrystal maps/RuinsOfAlphKabutoItemRoom.asm by kjh_tools/johto

JohtoRuinsOfAlphKabutoItemRoom_MapScripts::
	.byte 0

J_S_RuinsOfAlphKabutoItemRoomAncientReplica::
	lockall
	call J_RuinsOfAlphKabutoItemRoomAncientReplica
	releaseall
	end

J_RuinsOfAlphKabutoItemRoom_MapScripts::
J_RuinsOfAlphKabutoItemRoomBerry::
	finditem ITEM_ORAN_BERRY, 1
	return
J_RuinsOfAlphKabutoItemRoomPsncureberry::
	finditem ITEM_PECHA_BERRY, 1
	return
J_RuinsOfAlphKabutoItemRoomHealPowder::
	finditem ITEM_HEAL_POWDER, 1
	return
J_RuinsOfAlphKabutoItemRoomEnergypowder::
	finditem ITEM_ENERGY_POWDER, 1
	return
J_RuinsOfAlphKabutoItemRoomAncientReplica::
	message J_RuinsOfAlphKabutoItemRoomAncientReplicaText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphKabutoItemRoomAncientReplicaText::
	.string "It's a replica of\nan ancient POKé-\lMON.$"
J_RuinsOfAlphKabutoItemRoom_MapEvents::
