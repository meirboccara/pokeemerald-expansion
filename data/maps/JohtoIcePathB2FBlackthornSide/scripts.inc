@ KJH: translated from pokecrystal maps/IcePathB2FBlackthornSide.asm by kjh_tools/johto

JohtoIcePathB2FBlackthornSide_MapScripts::
	.byte 0

J_IcePathB2FBlackthornSide_MapScripts::
J_IcePathB2FBlackthornSideTMRest::
	finditem ITEM_TM44, 1
	return
J_IcePathB2FBlackthornSideHiddenIceHeal::
	finditem ITEM_ICE_HEAL
	return
J_IcePathB2FBlackthornSide_MapEvents::
