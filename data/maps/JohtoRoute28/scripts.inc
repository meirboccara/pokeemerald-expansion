@ KJH: translated from pokecrystal maps/Route28.asm by kjh_tools/johto

JohtoRoute28_MapScripts::
	.byte 0

J_S_Route28Sign::
	lockall
	call J_Route28Sign
	releaseall
	end

J_Route28_MapScripts::
J_Route28Sign::
	message J_Route28SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route28HiddenRareCandy::
	finditem ITEM_RARE_CANDY
	return
J_Route28SignText::
	.string "ROUTE 28$"
J_Route28_MapEvents::
