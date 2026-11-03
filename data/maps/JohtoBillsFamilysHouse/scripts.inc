@ KJH: translated from pokecrystal maps/BillsFamilysHouse.asm by kjh_tools/johto

JohtoBillsFamilysHouse_MapScripts::
	.byte 0

J_W_BillScript::
	lock
	call J_BillScript
	release
	end

J_W_BillsMomScript::
	lock
	call J_BillsMomScript
	release
	end

J_W_BillsYoungerSisterScript::
	lock
	call J_BillsYoungerSisterScript
	release
	end

J_S_BillsHouseBookshelf2::
	lockall
	call J_BillsHouseBookshelf2
	releaseall
	end

J_S_BillsHouseBookshelf1::
	lockall
	call J_BillsHouseBookshelf1
	releaseall
	end

J_S_BillsHouseRadio::
	lockall
	call J_BillsHouseRadio
	releaseall
	end

J_BillsFamilysHouse_MapScripts::
J_BillScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_EEVEE, J_L525
	setvar VAR_RESULT, 1
J_L525:
	goto_if_ne VAR_RESULT, 0, J_BillScript_GotEevee
	message J_BillTakeThisEeveeText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_BillScript_Refused
	message J_BillImCountingOnYouText
	waitmessage
	waitbuttonpress
	waitse
	setvar VAR_0x8004, 1
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 6, J_BillScript_NoRoom
	message J_ReceivedEeveeText
	waitmessage
	playse SE_SUCCESS
	waitse
	givemon SPECIES_EEVEE, 20, ITEM_NONE
	setflag FLAG_SYS_POKEMON_GET
	bufferspeciesname STR_VAR_1, SPECIES_EEVEE
	playfanfare MUS_LEVEL_UP
	message J_Text_ReceivedMon
	waitmessage
	waitfanfare
	setvar VAR_RESULT, 1
	setflag FLAG_J_GOT_EEVEE
	message J_BillEeveeMayEvolveText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BillScript_NoRoom:
	message J_BillPartyFullText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BillScript_Refused:
	message J_BillNoEeveeText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BillScript_GotEevee:
	message J_BillPopWontWorkText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BillsMomScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_MET_BILL, J_L526
	setvar VAR_RESULT, 1
J_L526:
	goto_if_eq VAR_RESULT, 0, J_BillsMomScript_HaventMetBill
	message J_BillsMomText_BeforeEcruteak
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BillsMomScript_HaventMetBill:
	message J_BillsMomText_AfterEcruteak
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BillsYoungerSisterScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_BillsYoungerSisterScript_GotBillsNumber
	message J_BillsYoungerSisterUsefulNumberText
	waitmessage
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_BillsYoungerSisterScript_NoRoom
	goto_if_eq VAR_RESULT, 2, J_BillsYoungerSisterScript_Refused
	waitse
	message J_RecordedBillsNumberText
	waitmessage
	playse SE_SUCCESS
	waitse
	waitbuttonpress
J_BillsYoungerSisterScript_GotBillsNumber:
	message J_BillsYoungerSisterStorageSystemText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BillsYoungerSisterScript_Refused:
	message J_BillsYoungerSisterRefusedNumberText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BillsYoungerSisterScript_NoRoom:
	message J_BillsYoungerSisterPhoneFullText
	waitmessage
	waitbuttonpress
	goto J_BillsYoungerSisterScript_Refused
J_BillsHouseBookshelf1::
	goto J_PictureBookshelfScript
J_BillsHouseBookshelf2::
	goto J_MagazineBookshelfScript
J_BillsHouseRadio::
	goto J_Radio2Script
J_BillTakeThisEeveeText::
	.string "BILL: Hi, {PLAYER}!\nDo us a favor and\ltake this EEVEE.\pIt came over when\nI was adjusting\lthe TIME CAPSULE.\pSomeone has to\ntake care of it,\pbut I don't like\nbeing outside.\pCan I count on you\nto play with it,\l{PLAYER}?$"
J_BillImCountingOnYouText::
	.string "BILL: I knew you'd\ncome through!\pWay to go! You're\nthe real deal!\pOK, I'm counting\non you.\pTake good care of\nit!$"
J_ReceivedEeveeText::
	.string "{PLAYER} received\nEEVEE!$"
J_BillEeveeMayEvolveText::
	.string "BILL: PROF.ELM\nclaims EEVEE may\pevolve in new and\nunknown ways.$"
J_BillPartyFullText::
	.string "Whoa, wait. You\ncan't carry any\lmore POKéMON.$"
J_BillNoEeveeText::
	.string "Oh… Now what to\ndo?$"
J_BillPopWontWorkText::
	.string "BILL: My pop, he\nwon't work. All he\pdoes is goof off\nall day long.\pHe's getting to be\na real headache…$"
J_BillsMomText_BeforeEcruteak::
	.string "Oh, you collect\nPOKéMON? My son\lBILL is an expert.\pHe just got called\nto the POKéMON\pCENTER in ECRUTEAK\nCITY.\pMy husband went\noff to the GAME\pCORNER without\nbeing called…$"
J_BillsMomText_AfterEcruteak::
	.string "My husband was\nonce known as a\pPOKéMANIAC.\nBILL must have\ptaken after his\nfather.$"
J_BillsYoungerSisterUsefulNumberText::
	.string "Are you a trainer?\pI've got a useful\nphone number for\lyou.$"
J_RecordedBillsNumberText::
	.string "{PLAYER} recorded\nBILL's number.$"
J_BillsYoungerSisterRefusedNumberText::
	.string "My brother made\nthe PC POKéMON\lstorage system.\pI was going to\ngive you BILL's\lnumber…$"
J_BillsYoungerSisterPhoneFullText::
	.string "You can't record\nany more numbers.$"
J_BillsYoungerSisterStorageSystemText::
	.string "My big brother\nBILL made the PC\pPOKéMON storage\nsystem.$"
J_BillsFamilysHouse_MapEvents::
