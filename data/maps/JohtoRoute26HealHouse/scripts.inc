@ KJH: translated from pokecrystal maps/Route26HealHouse.asm by kjh_tools/johto

JohtoRoute26HealHouse_MapScripts::
	.byte 0

J_W_Route26HealHouseTeacherScript::
	lock
	call J_Route26HealHouseTeacherScript
	release
	end

J_S_Route26HealHouseBookshelf::
	lockall
	call J_Route26HealHouseBookshelf
	releaseall
	end

J_Route26HealHouse_MapScripts::
J_Route26HealHouseTeacherScript::
	faceplayer
	message J_Route26HealHouseRestAWhileText
	waitmessage
	waitbuttonpress
	closemessage
	fadescreen FADE_TO_BLACK
	playbgm MUS_RG_HEAL, FALSE
	special HealPlayerParty
	delay 60
	fadescreen FADE_FROM_BLACK
	fadedefaultbgm
	message J_Route26HealHouseKeepAtItText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route26HealHouseBookshelf::
	goto J_PictureBookshelfScript
J_Route26HealHouseRestAWhileText::
	.string "Your POKéMON look\na little tired.\pYou should rest\nthem a while.$"
J_Route26HealHouseKeepAtItText::
	.string "There!\pYour POKéMON are\nlooking good!\pKeep at it!$"
J_Route26HealHouse_MapEvents::
