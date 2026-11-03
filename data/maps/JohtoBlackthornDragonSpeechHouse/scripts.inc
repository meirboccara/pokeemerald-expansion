@ KJH: translated from pokecrystal maps/BlackthornDragonSpeechHouse.asm by kjh_tools/johto

JohtoBlackthornDragonSpeechHouse_MapScripts::
	.byte 0

J_W_BlackthornDragonSpeechHouseGrannyScript::
	lock
	call J_BlackthornDragonSpeechHouseGrannyScript
	release
	end

J_W_BlackthornDragonSpeechHouseDratiniScript::
	lock
	call J_BlackthornDragonSpeechHouseDratiniScript
	release
	end

J_BlackthornDragonSpeechHouse_MapScripts::
J_BlackthornDragonSpeechHouseGrannyScript::
	faceplayer
	message J_BlackthornDragonSpeechHouseGrannyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornDragonSpeechHouseDratiniScript::
	message J_BlackthornDragonSpeechHouseDratiniText
	waitmessage
	playmoncry SPECIES_DRATINI, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_BlackthornDragonSpeechHousePictureBookshelf::
	goto J_PictureBookshelfScript
J_BlackthornDragonSpeechHouseMagazineBookshelf::
	goto J_MagazineBookshelfScript
J_BlackthornDragonSpeechHouseGrannyText::
	.string "A clan of trainers\nwho can freely\pcommand dragons\nlive right here in\lBLACKTHORN.\pAs a result, there\nare many legends\pabout dragons in\nthis town.$"
J_BlackthornDragonSpeechHouseDratiniText::
	.string "DRATINI: Draa!$"
J_BlackthornDragonSpeechHouse_MapEvents::
