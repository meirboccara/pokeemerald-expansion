@ KJH: translated from pokecrystal maps/OlivinePunishmentSpeechHouse.asm by kjh_tools/johto

JohtoOlivinePunishmentSpeechHouse_MapScripts::
	.byte 0

J_W_OlivinePunishmentSpeechHouseDad::
	lock
	call J_OlivinePunishmentSpeechHouseDad
	release
	end

J_W_OlivinePunishmentSpeechHouseDaughter::
	lock
	call J_OlivinePunishmentSpeechHouseDaughter
	release
	end

J_S_OlivinePunishmentSpeechHouseBookshelf1::
	lockall
	call J_OlivinePunishmentSpeechHouseBookshelf1
	releaseall
	end

J_S_OlivinePunishmentSpeechHouseBookshelf2::
	lockall
	call J_OlivinePunishmentSpeechHouseBookshelf2
	releaseall
	end

J_OlivinePunishmentSpeechHouse_MapScripts::
J_OlivinePunishmentSpeechHouseDad::
	faceplayer
	message J_OlivinePunishmentSpeechHouseDadText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivinePunishmentSpeechHouseDaughter::
	faceplayer
	message J_OlivinePunishmentSpeechHouseDaughterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivinePunishmentSpeechHouseBookshelf2::
	goto J_PictureBookshelfScript
J_OlivinePunishmentSpeechHouseBookshelf1::
	goto J_MagazineBookshelfScript
J_OlivinePunishmentSpeechHouseDadText::
	.string "Along the way to\nCIANWOOD, there\pare four deserted\nislands.\pBad kids are taken\nto the islands as\lpunishment!$"
J_OlivinePunishmentSpeechHouseDaughterText::
	.string "Whenever I get in\ntrouble, Daddy\lalways scares me.$"
J_OlivinePunishmentSpeechHouse_MapEvents::
