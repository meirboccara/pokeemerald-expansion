@ KJH: translated from pokecrystal maps/IcePathB3F.asm by kjh_tools/johto

JohtoIcePathB3F_MapScripts::
	.byte 0

J_W_IcePathB3FRock::
	lock
	call J_IcePathB3FRock
	release
	end

J_IcePathB3F_MapScripts::
J_IcePathB3FNevermeltice::
	finditem ITEM_NEVER_MELT_ICE, 1
	return
J_IcePathB3FRock::
	goto EventScript_RockSmash
J_IcePathB3F_MapEvents::
