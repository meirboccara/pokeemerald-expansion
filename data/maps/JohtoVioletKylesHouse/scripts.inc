@ KJH: translated from pokecrystal maps/VioletKylesHouse.asm by kjh_tools/johto

JohtoVioletKylesHouse_MapScripts::
	.byte 0

J_W_VioletKylesHousePokefanMScript::
	lock
	call J_VioletKylesHousePokefanMScript
	release
	end

J_W_Kyle::
	lock
	call J_Kyle
	release
	end

J_VioletKylesHouse_MapScripts::
J_VioletKylesHousePokefanMScript::
	faceplayer
	message J_VioletKylesHousePokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Kyle::
	faceplayer
	waitbuttonpress
	closemessage
	return
J_VioletKylesHousePokefanMText::
	.string "A POKéMON you get\nin a trade grows\lquickly.\pBut if you don't\nhave the right GYM\pBADGE, they may\ndisobey you.$"
J_VioletKylesHouse_MapEvents::
