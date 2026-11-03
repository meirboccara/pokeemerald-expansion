@ KJH: translated from pokecrystal maps/Route27SandstormHouse.asm by kjh_tools/johto

JohtoRoute27SandstormHouse_MapScripts::
	.byte 0

J_W_SandstormHouseWoman::
	lock
	call J_SandstormHouseWoman
	release
	end

J_S_SandstormHouseBookshelf::
	lockall
	call J_SandstormHouseBookshelf
	releaseall
	end

J_Route27SandstormHouse_MapScripts::
J_SandstormHouseWoman::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM37_SANDSTORM, J_L657
	setvar VAR_RESULT, 1
J_L657:
	goto_if_ne VAR_RESULT, 0, J_SandstormHouseWoman_AlreadyGotItem
	special KJH_GetLeadFriendship
	message J_SandstormHouseWomanText1
	waitmessage
	waitbuttonpress
	goto_if_gt VAR_RESULT, 149, J_SandstormHouseWoman_Loyal
	goto J_SandstormHouseWoman_Disloyal
J_SandstormHouseWoman_Loyal:
	message J_SandstormHouseWomanLoyalText
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM37, 1
	goto_if_eq VAR_RESULT, 0, J_SandstormHouseWoman_Done
	setflag FLAG_J_GOT_TM37_SANDSTORM
J_SandstormHouseWoman_AlreadyGotItem:
	message J_SandstormHouseSandstormDescription
	waitmessage
	waitbuttonpress
J_SandstormHouseWoman_Done:
	closemessage
	return
J_SandstormHouseWoman_Disloyal:
	message J_SandstormHouseWomanDisloyalText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SandstormHouseBookshelf::
	goto J_MagazineBookshelfScript
J_SandstormHouseWomanText1::
	.string "Where are you off\nto with POKéMON?\pPOKéMON LEAGUE?\pAre your POKéMON\nloyal enough for\lyou to win?\pLet me see…$"
J_SandstormHouseWomanLoyalText::
	.string "Ah! Your POKéMON\ntrusts you very\lmuch.\pIt's nice to see a\ngood trainer.\pHere. A gift for\nyour journey.$"
J_SandstormHouseSandstormDescription::
	.string "TM37 happens to be\nSANDSTORM.\pIt's a move that\ninflicts damage on\lboth battlers.\pIt's for advanced\ntrainers only.\pUse it if you\ndare. Good luck!$"
J_SandstormHouseWomanDisloyalText::
	.string "If it doesn't come\nto trust you some\pmore, it could be\ntough going.\pTrust is the tie\nthat binds POKéMON\land trainers.$"
J_Route27SandstormHouse_MapEvents::
