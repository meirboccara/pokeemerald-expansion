@ KJH: translated from pokecrystal maps/SilverCaveRoom3.asm by kjh_tools/johto

JohtoSilverCaveRoom3_MapScripts::
	.byte 0

J_W_Red::
	lock
	call J_Red
	release
	end

J_SilverCaveRoom3_MapScripts::
J_Red::
	fadeoutbgm 0
	faceplayer
	message J_RedSeenText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_J_RED_RED1, J_RedWinLossText
	fadeoutbgm 0
	message J_RedLeavesText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject 1
	delay 15
	fadescreen FADE_FROM_BLACK
	delay 30
	special HealPlayerParty
	special DrawWholeMapView
	return
J_RedSeenText::
	.string "……\n……$"
J_RedWinLossText::
	.string "…$"
J_RedLeavesText::
	.string "……\n……$"
J_SilverCaveRoom3_MapEvents::
