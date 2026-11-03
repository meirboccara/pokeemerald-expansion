@ KJH: translated from pokecrystal maps/ManiasHouse.asm by kjh_tools/johto

JohtoManiasHouse_MapScripts::
	.byte 0

J_W_ManiaScript::
	lock
	call J_ManiaScript
	release
	end

J_ManiasHouse_MapScripts::
J_ManiaScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_MANIA_TOOK_SHUCKIE_OR_LET_YOU_KEEP_HIM, J_L587
	setvar VAR_RESULT, 1
J_L587:
	goto_if_ne VAR_RESULT, 0, J_ManiaScript_default_postevent
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_SHUCKIE, J_L588
	setvar VAR_RESULT, 1
J_L588:
	goto_if_ne VAR_RESULT, 0, J_ManiaScript_alreadyhaveshuckie
	message J_ManiaText_AskLookAfterShuckle
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_ManiaScript_refusetotakeshuckie
	givemon SPECIES_SHUCKLE, 15, ITEM_ORAN_BERRY
	setvar VAR_RESULT, 1
	goto_if_eq VAR_RESULT, 0, J_ManiaScript_partyfull
	message J_ManiaText_TakeCareOfShuckle
	waitmessage
	waitbuttonpress
	waitse
	message J_ManiaText_GotShuckle
	waitmessage
	playse SE_SUCCESS
	waitse
	closemessage
	setflag FLAG_J_GOT_SHUCKIE
	return
J_ManiaScript_alreadyhaveshuckie:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_GOT_SHUCKIE_TODAY, J_L589
	setvar VAR_RESULT, 1
J_L589:
	goto_if_eq VAR_RESULT, 0, J_ManiaScript_returnshuckie
	message J_ManiaText_TakeCareOfShuckle
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ManiaScript_partyfull:
	message J_ManiaText_PartyFull
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ManiaScript_refusetotakeshuckie:
	message J_ManiaText_IfHeComesBack
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ManiaScript_returnshuckie:
	message J_ManiaText_CanIHaveMyMonBack
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_ManiaScript_refused
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_ManiaScript_wrong
	goto_if_eq VAR_RESULT, 1, J_ManiaScript_refused
	goto_if_eq VAR_RESULT, 3, J_ManiaScript_superhappy
	goto_if_eq VAR_RESULT, 4, J_ManiaScript_default_postevent
	message J_ManiaText_ThankYou
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_MANIA_TOOK_SHUCKIE_OR_LET_YOU_KEEP_HIM
	return
J_ManiaScript_wrong:
	message J_ManiaText_ShuckleNotThere
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ManiaScript_superhappy:
	message J_ManiaText_ShuckleLikesYou
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_MANIA_TOOK_SHUCKIE_OR_LET_YOU_KEEP_HIM
	return
J_ManiaScript_refused:
	message J_ManiaText_SameAsBeingRobbed
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ManiaScript_nothingleft:
	message J_ManiaText_ShuckleIsYourLastMon
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ManiaScript_default_postevent:
	message J_ManiaText_HappinessSpeech
	waitmessage
	waitbuttonpress
	closemessage
	return
J_ManiasHouseUnusedBookshelf::
	goto J_PictureBookshelfScript
J_ManiaText_AskLookAfterShuckle::
	.string "I, I'm in shock!\pA guy about your\nage with piercing\peyes and long hair\ncame in.\pHe scared me into\ngiving him my\lprized POKéMON!\pI still have one\nleft, but what if\lhe comes back?\pYou look strong.\nCould you look\pafter my POKéMON\nfor a while?$"
J_ManiaText_TakeCareOfShuckle::
	.string "Oh, thank you!\pTake good care of\nit, please!$"
J_ManiaText_GotShuckle::
	.string "{PLAYER} received a\nPOKéMON.$"
J_ManiaText_PartyFull::
	.string "Your POKéMON party\nis full.$"
J_ManiaText_IfHeComesBack::
	.string "Oh, no… What'll\nI do if he comes\lback?$"
J_ManiaText_CanIHaveMyMonBack::
	.string "Hi! How's my POKé-\nMON?\pI think I'm safe\nnow, so may I have\lit back?$"
J_ManiaText_ThankYou::
	.string "Thank you!$"
J_ManiaText_ShuckleNotThere::
	.string "Hey, you don't\nhave my POKéMON\lwith you.$"
J_ManiaText_ShuckleLikesYou::
	.string "My POKéMON has\ncome to like you.\pAll right, you\nshould keep it.\pBut promise to\nbe good to it!$"
J_ManiaText_SameAsBeingRobbed::
	.string "Oh, no, no… That's\nthe same as being\lrobbed.$"
J_ManiaText_HappinessSpeech::
	.string "For POKéMON, hap-\npiness is being\pwith a person who\ntreats them well.$"
J_ManiaText_ShuckleIsYourLastMon::
	.string "If I take my POKé-\nMON back, what are\pyou going to use\nin battle?$"
J_ManiasHouse_MapEvents::
