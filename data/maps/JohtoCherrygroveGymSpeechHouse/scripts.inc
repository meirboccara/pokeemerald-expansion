@ KJH: translated from pokecrystal maps/CherrygroveGymSpeechHouse.asm by kjh_tools/johto

JohtoCherrygroveGymSpeechHouse_MapScripts::
	.byte 0

J_W_CherrygroveGymSpeechHousePokefanMScript::
	lock
	call J_CherrygroveGymSpeechHousePokefanMScript
	release
	end

J_W_CherrygroveGymSpeechHouseBugCatcherScript::
	lock
	call J_CherrygroveGymSpeechHouseBugCatcherScript
	release
	end

J_S_CherrygroveGymSpeechHouseBookshelf::
	lockall
	call J_CherrygroveGymSpeechHouseBookshelf
	releaseall
	end

J_CherrygroveGymSpeechHouse_MapScripts::
J_CherrygroveGymSpeechHousePokefanMScript::
	faceplayer
	message J_CherrygroveGymSpeechHousePokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CherrygroveGymSpeechHouseBugCatcherScript::
	faceplayer
	message J_CherrygroveGymSpeechHouseBugCatcherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CherrygroveGymSpeechHouseBookshelf::
	goto J_PictureBookshelfScript
J_CherrygroveGymSpeechHousePokefanMText::
	.string "You're trying to\nsee how good you\pare as a POKéMON\ntrainer?\pYou better visit\nthe POKéMON GYMS\pall over JOHTO and\ncollect BADGES.$"
J_CherrygroveGymSpeechHouseBugCatcherText::
	.string "When I get older,\nI'm going to be a\lGYM LEADER!\pI make my POKéMON\nbattle with my\pfriend's to make\nthem tougher!$"
J_CherrygroveGymSpeechHouse_MapEvents::
