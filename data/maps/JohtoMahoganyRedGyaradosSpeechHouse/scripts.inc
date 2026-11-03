@ KJH: translated from pokecrystal maps/MahoganyRedGyaradosSpeechHouse.asm by kjh_tools/johto

JohtoMahoganyRedGyaradosSpeechHouse_MapScripts::
	.byte 0

J_W_MahoganyRedGyaradosSpeechHouseBlackBeltScript::
	lock
	call J_MahoganyRedGyaradosSpeechHouseBlackBeltScript
	release
	end

J_W_MahoganyRedGyaradosSpeechHouseTeacherScript::
	lock
	call J_MahoganyRedGyaradosSpeechHouseTeacherScript
	release
	end

J_MahoganyRedGyaradosSpeechHouse_MapScripts::
J_MahoganyRedGyaradosSpeechHouseBlackBeltScript::
	faceplayer
	message J_MahoganyRedGyaradosSpeechHouseBlackBeltText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyRedGyaradosSpeechHouseTeacherScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_ROCKETS_IN_RADIO_TOWER, J_L33
	setvar VAR_RESULT, 1
J_L33:
	goto_if_ne VAR_RESULT, 0, J_MahoganyRedGyaradosSpeechHouseTeacherScript_RocketsInRadioTower
	message J_MahoganyRedGyaradosSpeechHouseTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyRedGyaradosSpeechHouseTeacherScript_RocketsInRadioTower:
	message J_MahoganyRedGyaradosSpeechHouseTeacherText_RocketsInRadioTower
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MahoganyRedGyaradosSpeechHouseUnusedBookshelf1::
	goto J_PictureBookshelfScript
J_MahoganyRedGyaradosSpeechHouseUnusedBookshelf2::
	goto J_MagazineBookshelfScript
J_MahoganyRedGyaradosSpeechHouseBlackBeltText::
	.string "I heard that a red\nGYARADOS appeared\lat the LAKE.\pThat's odd, since\neven ordinary\pGYARADOS are rare\nin that lake…$"
J_MahoganyRedGyaradosSpeechHouseTeacherText::
	.string "My favorite radio\nprogram? I'd say\lPOKéMON MUSIC.$"
J_MahoganyRedGyaradosSpeechHouseTeacherText_RocketsInRadioTower::
	.string "I've been hearing\nlaughter on the\pradio…\nIt's creepy.$"
J_MahoganyRedGyaradosSpeechHouse_MapEvents::
