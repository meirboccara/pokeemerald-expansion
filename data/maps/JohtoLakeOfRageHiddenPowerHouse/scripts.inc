@ KJH: translated from pokecrystal maps/LakeOfRageHiddenPowerHouse.asm by kjh_tools/johto

JohtoLakeOfRageHiddenPowerHouse_MapScripts::
	.byte 0

J_W_HiddenPowerGuy::
	lock
	call J_HiddenPowerGuy
	release
	end

J_S_HiddenPowerHouseBookshelf::
	lockall
	call J_HiddenPowerHouseBookshelf
	releaseall
	end

J_LakeOfRageHiddenPowerHouse_MapScripts::
J_HiddenPowerGuy::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM10_HIDDEN_POWER, J_L374
	setvar VAR_RESULT, 1
J_L374:
	goto_if_ne VAR_RESULT, 0, J_HiddenPowerGuy_AlreadyGotItem
	message J_HiddenPowerGuyText1
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM10, 1
	goto_if_eq VAR_RESULT, 0, J_HiddenPowerGuy_Done
	setflag FLAG_J_GOT_TM10_HIDDEN_POWER
	message J_HiddenPowerGuyText2
	waitmessage
	waitbuttonpress
	closemessage
	return
J_HiddenPowerGuy_AlreadyGotItem:
	message J_HiddenPowerGuyText3
	waitmessage
	waitbuttonpress
J_HiddenPowerGuy_Done:
	closemessage
	return
J_HiddenPowerHouseBookshelf::
	goto J_DifficultBookshelfScript
J_HiddenPowerGuyText1::
	.string "…You have strayed\nfar…\pHere I have medi-\ntated. Inside me,\pa new power has\nbeen awakened.\pLet me share my\npower with your\pPOKéMON.\nTake this, child.$"
J_HiddenPowerGuyText2::
	.string "Do you see it? It\nis HIDDEN POWER!\pIt draws out the\npower of POKéMON\lfor attacking.\pRemember this: its\ntype and power de-\lpend on the POKé-\lMON using it.$"
J_HiddenPowerGuyText3::
	.string "I am meditating…$"
J_LakeOfRageHiddenPowerHouse_MapEvents::
