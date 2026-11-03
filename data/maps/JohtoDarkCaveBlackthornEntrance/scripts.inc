@ KJH: translated from pokecrystal maps/DarkCaveBlackthornEntrance.asm by kjh_tools/johto

JohtoDarkCaveBlackthornEntrance_MapScripts::
	.byte 0

J_W_DarkCaveBlackthornEntrancePharmacistScript::
	lock
	call J_DarkCaveBlackthornEntrancePharmacistScript
	release
	end

J_DarkCaveBlackthornEntrance_MapScripts::
J_DarkCaveBlackthornEntrancePharmacistScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_BLACKGLASSES_IN_DARK_CAVE, J_L243
	setvar VAR_RESULT, 1
J_L243:
	goto_if_ne VAR_RESULT, 0, J_DarkCaveBlackthornEntrancePharmacistScript_GotBlackglasses
	message J_DarkCaveBlackthornEntrancePharmacistText1
	waitmessage
	waitbuttonpress
	giveitem ITEM_BLACK_GLASSES, 1
	goto_if_eq VAR_RESULT, 0, J_DarkCaveBlackthornEntrancePharmacistScript_PackFull
	setflag FLAG_J_GOT_BLACKGLASSES_IN_DARK_CAVE
J_DarkCaveBlackthornEntrancePharmacistScript_GotBlackglasses:
	message J_DarkCaveBlackthornEntrancePharmacistText2
	waitmessage
	waitbuttonpress
J_DarkCaveBlackthornEntrancePharmacistScript_PackFull:
	closemessage
	return
J_DarkCaveBlackthornEntranceRevive::
	finditem ITEM_REVIVE, 1
	return
J_DarkCaveBlackthornEntranceTMSnore::
	finditem ITEM_RARE_CANDY, 1
	return
J_DarkCaveBlackthornEntrancePharmacistText1::
	.string "Whoa! You startled\nme there!\pI had my BLACK-\nGLASSES on, so I\pdidn't notice you\nat all.\pWhat am I doing\nhere?\pHey, don't you\nworry about it.\pI'll give you a\npair of BLACK-\lGLASSES, so forget\lyou saw me, OK?$"
J_DarkCaveBlackthornEntrancePharmacistText2::
	.string "BLACKGLASSES ups\nthe power of dark-\ltype moves.$"
J_DarkCaveBlackthornEntrance_MapEvents::
