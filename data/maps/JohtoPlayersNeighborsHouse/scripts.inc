@ KJH: translated from pokecrystal maps/PlayersNeighborsHouse.asm by kjh_tools/johto

JohtoPlayersNeighborsHouse_MapScripts::
	.byte 0

J_W_PlayersNeighborsDaughterScript::
	lock
	call J_PlayersNeighborsDaughterScript
	release
	end

J_W_PlayersNeighborScript::
	lock
	call J_PlayersNeighborScript
	release
	end

J_S_PlayersNeighborsHouseBookshelfScript::
	lockall
	call J_PlayersNeighborsHouseBookshelfScript
	releaseall
	end

J_S_PlayersNeighborsHouseRadioScript::
	lockall
	call J_PlayersNeighborsHouseRadioScript
	releaseall
	end

J_PlayersNeighborsHouse_MapScripts::
J_PlayersNeighborsDaughterScript::
	faceplayer
	message J_PlayersNeighborsDaughterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_PlayersNeighborScript::
	faceplayer
	message J_PlayersNeighborText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_PlayersNeighborsHouseBookshelfScript::
	goto J_MagazineBookshelfScript
J_PlayersNeighborsHouseRadioScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_KJH_GOT_JOHTO_STARTER, J_L655
	setvar VAR_RESULT, 1
J_L655:
	goto_if_ne VAR_RESULT, 0, J_PlayersNeighborsHouseRadioScript_NormalRadio
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_LISTENED_TO_INITIAL_RADIO, J_L656
	setvar VAR_RESULT, 1
J_L656:
	goto_if_ne VAR_RESULT, 0, J_PlayersNeighborsHouseRadioScript_AbbreviatedRadio
	playbgm MUS_SCHOOL, FALSE
	message J_PlayerNeighborRadioText1
	waitmessage
	delay 45
	message J_PlayerNeighborRadioText2
	waitmessage
	delay 45
	message J_PlayerNeighborRadioText3
	waitmessage
	delay 45
	fadenewbgm MUS_RG_PALLET
	message J_PlayerNeighborRadioText4
	waitmessage
	delay 45
	closemessage
	setflag FLAG_J_LISTENED_TO_INITIAL_RADIO
	return
J_PlayersNeighborsHouseRadioScript_NormalRadio:
	goto J_Radio1Script
J_PlayersNeighborsHouseRadioScript_AbbreviatedRadio:
	message J_PlayerNeighborRadioText4
	waitmessage
	delay 45
	closemessage
	return
J_PlayersNeighborsDaughterText::
	.string "PIKACHU is an\nevolved POKéMON.\pI was amazed by\nPROF.ELM's find-\lings.\pHe's so famous for\nhis research on\lPOKéMON evolution.\p…sigh…\pI wish I could be\na researcher like\lhim…$"
J_PlayersNeighborText::
	.string "My daughter is\nadamant about\pbecoming PROF.\nELM's assistant.\pShe really loves\nPOKéMON!\pBut then, so do I!$"
J_PlayerNeighborRadioText1::
	.string "PROF.OAK'S POKéMON\nTALK! Please tune\lin next time!$"
J_PlayerNeighborRadioText2::
	.string "POKéMON CHANNEL!$"
J_PlayerNeighborRadioText3::
	.string "This is DJ MARY,\nyour co-host!$"
J_PlayerNeighborRadioText4::
	.string "POKéMON!\nPOKéMON CHANNEL…$"
J_PlayersNeighborsHouse_MapEvents::
