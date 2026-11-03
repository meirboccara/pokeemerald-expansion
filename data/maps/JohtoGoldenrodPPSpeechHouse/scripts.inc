@ KJH: translated from pokecrystal maps/GoldenrodPPSpeechHouse.asm by kjh_tools/johto

JohtoGoldenrodPPSpeechHouse_MapScripts::
	.byte 0

J_W_GoldenrodPPSpeechHouseFisherScript::
	lock
	call J_GoldenrodPPSpeechHouseFisherScript
	release
	end

J_W_GoldenrodPPSpeechHouseLassScript::
	lock
	call J_GoldenrodPPSpeechHouseLassScript
	release
	end

J_S_GoldenrodPPSpeechHouseBookshelf1::
	lockall
	call J_GoldenrodPPSpeechHouseBookshelf1
	releaseall
	end

J_S_GoldenrodPPSpeechHouseBookshelf2::
	lockall
	call J_GoldenrodPPSpeechHouseBookshelf2
	releaseall
	end

J_S_GoldenrodPPSpeechHouseRadio::
	lockall
	call J_GoldenrodPPSpeechHouseRadio
	releaseall
	end

J_GoldenrodPPSpeechHouse_MapScripts::
J_GoldenrodPPSpeechHouseFisherScript::
	faceplayer
	message J_GoldenrodPPSpeechHouseFisherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodPPSpeechHouseLassScript::
	faceplayer
	message J_GoldenrodPPSpeechHouseLassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodPPSpeechHouseBookshelf2::
	goto J_DifficultBookshelfScript
J_GoldenrodPPSpeechHouseBookshelf1::
	goto J_MagazineBookshelfScript
J_GoldenrodPPSpeechHouseRadio::
	goto J_Radio2Script
J_GoldenrodPPSpeechHouseFisherText::
	.string "Once while I was\nbattling, my\pPOKéMON couldn't\nmake any moves.\pThe POWER POINTS,\nor PP, of its\pmoves were all\ngone.$"
J_GoldenrodPPSpeechHouseLassText::
	.string "Sometimes, a\nhealthy POKéMON\pmay be unable to\nuse its moves.\pIf that happens,\nheal it at a POKé-\lMON CENTER or use\lan item.$"
J_GoldenrodPPSpeechHouse_MapEvents::
