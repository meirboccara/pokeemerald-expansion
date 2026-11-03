@ KJH: translated from pokecrystal maps/RuinsOfAlphOmanyteItemRoom.asm by kjh_tools/johto

JohtoRuinsOfAlphOmanyteItemRoom_MapScripts::
	.byte 0

J_S_RuinsOfAlphOmanyteItemRoomAncientReplica::
	lockall
	call J_RuinsOfAlphOmanyteItemRoomAncientReplica
	releaseall
	end

J_RuinsOfAlphOmanyteItemRoom_MapScripts::
J_RuinsOfAlphOmanyteItemRoomMysteryberry::
	finditem ITEM_LEPPA_BERRY, 1
	return
J_RuinsOfAlphOmanyteItemRoomMysticWater::
	finditem ITEM_MYSTIC_WATER, 1
	return
J_RuinsOfAlphOmanyteItemRoomStardust::
	finditem ITEM_STARDUST, 1
	return
J_RuinsOfAlphOmanyteItemRoomStarPiece::
	finditem ITEM_STAR_PIECE, 1
	return
J_RuinsOfAlphOmanyteItemRoomAncientReplica::
	message J_RuinsOfAlphOmanyteItemRoomAncientReplicaText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphOmanyteItemRoomAncientReplicaText::
	.string "It's a replica of\nan ancient POKé-\lMON.$"
J_RuinsOfAlphOmanyteItemRoom_MapEvents::
