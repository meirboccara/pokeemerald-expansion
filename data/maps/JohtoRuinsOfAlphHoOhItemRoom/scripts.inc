@ KJH: translated from pokecrystal maps/RuinsOfAlphHoOhItemRoom.asm by kjh_tools/johto

JohtoRuinsOfAlphHoOhItemRoom_MapScripts::
	.byte 0

J_S_RuinsOfAlphHoOhItemRoomAncientReplica::
	lockall
	call J_RuinsOfAlphHoOhItemRoomAncientReplica
	releaseall
	end

J_RuinsOfAlphHoOhItemRoom_MapScripts::
J_RuinsOfAlphHoOhItemRoomGoldBerry::
	finditem ITEM_SITRUS_BERRY, 1
	return
J_RuinsOfAlphHoOhItemRoomMysteryberry::
	finditem ITEM_LEPPA_BERRY, 1
	return
J_RuinsOfAlphHoOhItemRoomRevivalHerb::
	finditem ITEM_REVIVAL_HERB, 1
	return
J_RuinsOfAlphHoOhItemRoomCharcoal::
	finditem ITEM_CHARCOAL, 1
	return
J_RuinsOfAlphHoOhItemRoomAncientReplica::
	message J_RuinsOfAlphHoOhItemRoomAncientReplicaText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphHoOhItemRoomAncientReplicaText::
	.string "It's a replica of\nan ancient POKé-\lMON.$"
J_RuinsOfAlphHoOhItemRoom_MapEvents::
