@ KJH: translated from pokecrystal maps/IcePathB2FMahoganySide.asm by kjh_tools/johto

JohtoIcePathB2FMahoganySide_MapScripts::
	.byte 0

J_W_IcePathB2FMahoganySideBoulder::
	lock
	call J_IcePathB2FMahoganySideBoulder
	release
	end

J_IcePathB2FMahoganySide_MapScripts::
J_IcePathB2FMahoganySideBoulder::
	message J_IcePathB2FMahoganySideBoulderText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_IcePathB2FMahoganySideFullHeal::
	finditem ITEM_FULL_HEAL, 1
	return
J_IcePathB2FMahoganySideMaxPotion::
	finditem ITEM_MAX_POTION, 1
	return
J_IcePathB2FMahoganySideHiddenCarbos::
	finditem ITEM_CARBOS
	return
J_IcePathB2FMahoganySideBoulderText::
	.string "It's immovably\nimbedded in ice.$"
J_IcePathB2FMahoganySide_MapEvents::
