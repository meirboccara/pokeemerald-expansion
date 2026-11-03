@ KJH: translated from pokecrystal maps/OlivineHouseBeta.asm by kjh_tools/johto

JohtoOlivineHouseBeta_MapScripts::
	.byte 0

J_W_OlivineHouseBetaTeacherScript::
	lock
	call J_OlivineHouseBetaTeacherScript
	release
	end

J_W_OlivineHouseBetaRhydonScript::
	lock
	call J_OlivineHouseBetaRhydonScript
	release
	end

J_S_OlivineHouseBetaBookshelf1::
	lockall
	call J_OlivineHouseBetaBookshelf1
	releaseall
	end

J_S_OlivineHouseBetaBookshelf2::
	lockall
	call J_OlivineHouseBetaBookshelf2
	releaseall
	end

J_OlivineHouseBeta_MapScripts::
J_OlivineHouseBetaTeacherScript::
	faceplayer
	message J_OlivineHouseBetaTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineHouseBetaRhydonScript::
	message J_OlivineHouseBetaRhydonText
	waitmessage
	playmoncry SPECIES_RHYDON, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_OlivineHouseBetaBookshelf1::
	goto J_PictureBookshelfScript
J_OlivineHouseBetaBookshelf2::
	goto J_MagazineBookshelfScript
J_OlivineHouseBetaTeacherText::
	.string "When my POKéMON\ngot sick, the\pPHARMACIST in\nECRUTEAK made some\lmedicine for me.$"
J_OlivineHouseBetaRhydonText::
	.string "RHYDON: Gugooh!$"
J_OlivineHouseBeta_MapEvents::
