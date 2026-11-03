@ KJH: translated from pokecrystal maps/CianwoodLugiaSpeechHouse.asm by kjh_tools/johto

JohtoCianwoodLugiaSpeechHouse_MapScripts::
	.byte 0

J_W_CianwoodLugiaSpeechHouseTeacherScript::
	lock
	call J_CianwoodLugiaSpeechHouseTeacherScript
	release
	end

J_W_CianwoodLugiaSpeechHouseLassScript::
	lock
	call J_CianwoodLugiaSpeechHouseLassScript
	release
	end

J_W_CianwoodLugiaSpeechHouseTwinScript::
	lock
	call J_CianwoodLugiaSpeechHouseTwinScript
	release
	end

J_S_CianwoodLugiaSpeechHouseBookshelf::
	lockall
	call J_CianwoodLugiaSpeechHouseBookshelf
	releaseall
	end

J_CianwoodLugiaSpeechHouse_MapScripts::
J_CianwoodLugiaSpeechHouseTeacherScript::
	faceplayer
	message J_CianwoodLugiaSpeechHouseTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodLugiaSpeechHouseLassScript::
	faceplayer
	message J_CianwoodLugiaSpeechHouseLassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodLugiaSpeechHouseTwinScript::
	faceplayer
	message J_CianwoodLugiaSpeechHouseTwinText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodLugiaSpeechHouseBookshelf::
	goto J_PictureBookshelfScript
J_CianwoodLugiaSpeechHouseTeacherText::
	.string "You came from\nOLIVINE?\pDo you remember\nthe four islands\lalong the way?\pI heard that a \nmythical sea crea-\lture is hiding in\lthem.$"
J_CianwoodLugiaSpeechHouseLassText::
	.string "I heard that you\ncan only see it if\pyou have a SILVER\nWING.\pIt must have the\nsame scent as the\lcreature.$"
J_CianwoodLugiaSpeechHouseTwinText::
	.string "I've heard that\nthe whirlpools\paround the islands\nare caused by the\lsea creature.\pYou might need a\nspecial move to\lget past them.$"
J_CianwoodLugiaSpeechHouse_MapEvents::
