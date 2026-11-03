@ KJH: translated from pokecrystal maps/CharcoalKiln.asm by kjh_tools/johto

JohtoCharcoalKiln_MapScripts::
	.byte 0

J_W_CharcoalKilnBoss::
	lock
	call J_CharcoalKilnBoss
	release
	end

J_W_CharcoalKilnApprentice::
	lock
	call J_CharcoalKilnApprentice
	release
	end

J_W_CharcoalKilnFarfetchd::
	lock
	call J_CharcoalKilnFarfetchd
	release
	end

J_S_CharcoalKilnBookshelf::
	lockall
	call J_CharcoalKilnBookshelf
	releaseall
	end

J_S_CharcoalKilnRadio::
	lockall
	call J_CharcoalKilnRadio
	releaseall
	end

J_CharcoalKiln_MapScripts::
J_CharcoalKilnBoss::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_HM01_CUT, J_L319
	setvar VAR_RESULT, 1
J_L319:
	goto_if_ne VAR_RESULT, 0, J_CharcoalKilnBoss_GotCut
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_SLOWPOKE_WELL, J_L320
	setvar VAR_RESULT, 1
J_L320:
	goto_if_ne VAR_RESULT, 0, J_CharcoalKilnBoss_SavedSlowpoke
	message J_CharcoalKilnBossText1
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CharcoalKilnBoss_SavedSlowpoke:
	message J_CharcoalKilnBossText2
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CharcoalKilnBoss_GotCut:
	message J_CharcoalKilnBossText3
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CharcoalKilnApprentice::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_CHARCOAL_IN_CHARCOAL_KILN, J_L321
	setvar VAR_RESULT, 1
J_L321:
	goto_if_ne VAR_RESULT, 0, J_CharcoalKilnApprentice_YoureTheCoolest
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_HM01_CUT, J_L322
	setvar VAR_RESULT, 1
J_L322:
	goto_if_ne VAR_RESULT, 0, J_CharcoalKilnApprentice_Thanks
	message J_CharcoalKilnApprenticeText1
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CharcoalKilnApprentice_Thanks:
	message J_CharcoalKilnApprenticeText2
	waitmessage
	waitbuttonpress
	giveitem ITEM_CHARCOAL, 1
	goto_if_eq VAR_RESULT, 0, J_CharcoalKilnApprentice_Done
	setflag FLAG_J_GOT_CHARCOAL_IN_CHARCOAL_KILN
	closemessage
	return
J_CharcoalKilnApprentice_YoureTheCoolest:
	message J_CharcoalKilnApprenticeText3
	waitmessage
	waitbuttonpress
J_CharcoalKilnApprentice_Done:
	closemessage
	return
J_CharcoalKilnFarfetchd::
	faceplayer
	message J_FarfetchdText
	waitmessage
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_CharcoalKilnBookshelf::
	goto J_MagazineBookshelfScript
J_CharcoalKilnRadio::
	goto J_Radio2Script
J_CharcoalKilnBossText1::
	.string "All the SLOWPOKE\nhave disappeared\lfrom the town.\pThe forest's pro-\ntector may be\langry with us…\pIt may be a bad\nomen. We should\lstay in.$"
J_CharcoalKilnBossText2::
	.string "The SLOWPOKE have\nreturned…\pBut my APPRENTICE\nhasn't come back\lfrom ILEX FOREST.\pWhere in the world\nis that lazy guy?$"
J_CharcoalKilnBossText3::
	.string "You chased off\nTEAM ROCKET and\pwent to ILEX\nFOREST alone?\pThat takes guts!\nI like that. Come\ltrain with us.$"
J_CharcoalKilnApprenticeText1::
	.string "Where have all the\nSLOWPOKE gone?\pAre they out play-\ning somewhere?$"
J_CharcoalKilnApprenticeText2::
	.string "I'm sorry--I for-\ngot to thank you.\pThis is CHARCOAL\nthat I made.\pFire-type POKéMON\nwould be happy to\lhold that.$"
J_CharcoalKilnApprenticeText3::
	.string "The SLOWPOKE came\nback, and you even\lfound FARFETCH'D.\pYou're the cool-\nest, man!$"
J_FarfetchdText::
	.string "FARFETCH'D: Kwaa!$"
J_CharcoalKiln_MapEvents::
