@ KJH: translated from pokecrystal maps/CherrygroveEvolutionSpeechHouse.asm by kjh_tools/johto

JohtoCherrygroveEvolutionSpeechHouse_MapScripts::
	.byte 0

J_W_CherrygroveEvolutionSpeechHouseLassScript::
	lock
	call J_CherrygroveEvolutionSpeechHouseLassScript
	release
	end

J_W_CherrygroveEvolutionSpeechHouseYoungsterScript::
	lock
	call J_CherrygroveEvolutionSpeechHouseYoungsterScript
	release
	end

J_S_CherrygroveEvolutionSpeechHouseBookshelf::
	lockall
	call J_CherrygroveEvolutionSpeechHouseBookshelf
	releaseall
	end

J_CherrygroveEvolutionSpeechHouse_MapScripts::
J_CherrygroveEvolutionSpeechHouseYoungsterScript::
	message J_CherrygroveEvolutionSpeechHouseYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CherrygroveEvolutionSpeechHouseLassScript::
	message J_CherrygroveEvolutionSpeechHouseLassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CherrygroveEvolutionSpeechHouseBookshelf::
	goto J_MagazineBookshelfScript
J_CherrygroveEvolutionSpeechHouseYoungsterText::
	.string "POKéMON gain expe-\nrience in battle\pand change their\nform.$"
J_CherrygroveEvolutionSpeechHouseLassText::
	.string "POKéMON change?\pI would be shocked\nif one did that!$"
J_CherrygroveEvolutionSpeechHouse_MapEvents::
