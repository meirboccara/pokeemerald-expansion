@ KJH: translated from pokecrystal maps/EcruteakItemfinderHouse.asm by kjh_tools/johto

JohtoEcruteakItemfinderHouse_MapScripts::
	.byte 0

J_W_EcruteakItemfinderGuy::
	lock
	call J_EcruteakItemfinderGuy
	release
	end

J_W_EcruteakHistoryBook::
	lock
	call J_EcruteakHistoryBook
	release
	end

J_S_ItemFinderHouseRadio::
	lockall
	call J_ItemFinderHouseRadio
	releaseall
	end

J_EcruteakItemfinderHouse_MapScripts::
J_EcruteakItemfinderGuy::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_ITEMFINDER, J_L288
	setvar VAR_RESULT, 1
J_L288:
	goto_if_ne VAR_RESULT, 0, J_EcruteakItemfinderGuy_itemfinder
	message J_EcruteakItemfinderAdventureText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_EcruteakItemfinderGuy_no
	message J_EcruteakItemfinderTrueSpiritText
	waitmessage
	waitbuttonpress
	giveitem ITEM_ITEMFINDER, 1
	setflag FLAG_J_GOT_ITEMFINDER
J_EcruteakItemfinderGuy_itemfinder:
	message J_ItemfinderExplanationText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakItemfinderGuy_no:
	message J_EcruteakItemfinderToEachHisOwnText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_EcruteakHistoryBook::
	message J_EcruteakHistoryBookText
	waitmessage
	yesnobox 20, 8
	goto_if_ne VAR_RESULT, 0, J_EcruteakHistoryBook_ReadBook
	closemessage
	return
J_EcruteakHistoryBook_ReadBook:
	message J_EcruteakTwoTowersText
	waitmessage
	yesnobox 20, 8
	goto_if_ne VAR_RESULT, 0, J_EcruteakHistoryBook_KeepReading
	closemessage
	return
J_EcruteakHistoryBook_KeepReading:
	message J_EcruteakThreeMonText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ItemFinderHouseRadio::
	goto J_Radio2Script
J_EcruteakItemfinderAdventureText::
	.string "Ah. You're on an\nadventure with\lyour POKéMON?\pWell, what's an\nadventure without\ltreasure hunting?\pAm I right, or am\nI right?$"
J_EcruteakItemfinderTrueSpiritText::
	.string "Good! You under-\nstand the true\pspirit of adven-\nture.\pI like that! Take\nthis with you.$"
J_ItemfinderExplanationText::
	.string "There are many\nitems lying about\pthat aren't ob-\nvious.\pUse ITEMFINDER to\ncheck if there is\pan item on the\nground near you.\pIt doesn't show\nthe exact spot,\pso you'll have to\nlook yourself.\pOh yeah--I heard\nthere are items\pin ECRUTEAK's\nBURNED TOWER.$"
J_EcruteakItemfinderToEachHisOwnText::
	.string "Oh… To each his\nown, I suppose…$"
J_EcruteakHistoryBookText::
	.string "HISTORY OF\nECRUTEAK\pWant to read it?$"
J_EcruteakTwoTowersText::
	.string "In ECRUTEAK, there\nwere two towers.\pEach tower was the\nroost of powerful\lflying POKéMON.\pBut one of the\ntowers burned to\lthe ground.\pThe two POKéMON\nhaven't been seen\lsince…\pKeep reading?$"
J_EcruteakThreeMonText::
	.string "ECRUTEAK was also\nhome to three\pPOKéMON that raced\naround the town.\pThey were said to\nhave been born of\pwater, lightning\nand fire.\pBut they could not\ncontain their\lexcessive power.\pSo they say the\nthree ran like the\pwind off into the\ngrassland.$"
J_EcruteakItemfinderHouse_MapEvents::
