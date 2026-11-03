@ KJH: translated from pokecrystal maps/Route35GoldenrodGate.asm by kjh_tools/johto

JohtoRoute35GoldenrodGate_MapScripts::
	.byte 0

J_W_RandyScript::
	lock
	call J_RandyScript
	release
	end

J_W_Route35GoldenrodGatePokefanFScript::
	lock
	call J_Route35GoldenrodGatePokefanFScript
	release
	end

J_W_Route35GoldenrodGateFisherScript::
	lock
	call J_Route35GoldenrodGateFisherScript
	release
	end

J_Route35GoldenrodGate_MapScripts::
J_RandyScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_HP_UP_FROM_RANDY, J_L454
	setvar VAR_RESULT, 1
J_L454:
	goto_if_ne VAR_RESULT, 0, J_RandyScript_gothpup
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GAVE_KENYA, J_L455
	setvar VAR_RESULT, 1
J_L455:
	goto_if_ne VAR_RESULT, 0, J_RandyScript_questcomplete
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_KENYA, J_L456
	setvar VAR_RESULT, 1
J_L456:
	goto_if_ne VAR_RESULT, 0, J_RandyScript_alreadyhavekenya
	message J_Route35GoldenrodGateRandyAskTakeThisMonToMyFriendText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_RandyScript_refused
	message J_Route35GoldenrodGateRandyThanksText
	waitmessage
	waitbuttonpress
	waitse
	setvar VAR_0x8004, 1
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 6, J_RandyScript_partyfull
	message J_Route35GoldenrodGatePlayerReceivedAMonWithMailText
	waitmessage
	playse SE_SUCCESS
	waitse
	givemon SPECIES_SPEAROW, 10, ITEM_NONE
	setflag FLAG_SYS_POKEMON_GET
	bufferspeciesname STR_VAR_1, SPECIES_SPEAROW
	playfanfare MUS_LEVEL_UP
	message J_Text_ReceivedMon
	waitmessage
	waitfanfare
	setvar VAR_RESULT, 1
	setflag FLAG_J_GOT_KENYA
J_RandyScript_alreadyhavekenya:
	message J_Route35GoldenrodGateRandyWeirdTreeBlockingRoadText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RandyScript_partyfull:
	message J_Route35GoldenrodGateRandyCantCarryAnotherMonText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RandyScript_refused:
	message J_Route35GoldenrodGateRandyOhNeverMindThenText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RandyScript_questcomplete:
	message J_Route35GoldenrodGateRandySomethingForYourTroubleText
	waitmessage
	waitbuttonpress
	giveitem ITEM_HP_UP, 1
	goto_if_eq VAR_RESULT, 0, J_RandyScript_bagfull
	setflag FLAG_J_GOT_HP_UP_FROM_RANDY
J_RandyScript_gothpup:
	message J_Route35GoldenrodGateRandyMyPalWasSnoozingRightText
	waitmessage
	waitbuttonpress
J_RandyScript_bagfull:
	closemessage
	return
J_GiftSpearowMail::
	.string "DARK CAVE leads$"
	.string "\nto another road$"
J_GiftSpearowName::
	.string "KENYA$"
J_GiftSpearowOTName::
	.string "RANDY$"
J_Route35GoldenrodGatePokefanFScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_FOUGHT_SUDOWOODO, J_L457
	setvar VAR_RESULT, 1
J_L457:
	goto_if_ne VAR_RESULT, 0, J_Route35GoldenrodGatePokefanFScript_FoughtSudowoodo
	message J_Route35GoldenrodGatePokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route35GoldenrodGatePokefanFScript_FoughtSudowoodo:
	message J_Route35GoldenrodGatePokefanFText_FoughtSudowoodo
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route35GoldenrodGateFisherScript::
	faceplayer
	message J_Route35GoldenrodGateFisherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route35GoldenrodGateRandyAskTakeThisMonToMyFriendText::
	.string "Excuse me, kid!\nCan you do a guy\la favor?\pCan you take this\nPOKéMON with MAIL\lto my friend?\pHe's on ROUTE 31.$"
J_Route35GoldenrodGateRandyThanksText::
	.string "You will? Perfect!\nThanks, kid!\pMy pal's a chubby\nguy who snoozes\lall the time.\pYou'll recognize\nhim right away!$"
J_Route35GoldenrodGatePlayerReceivedAMonWithMailText::
	.string "{PLAYER} received a\nPOKéMON with MAIL.$"
J_Route35GoldenrodGateRandyWeirdTreeBlockingRoadText::
	.string "You can read it,\nbut don't lose it!\lROUTE 31!\pOh, yeah. There\nwas a weird tree\lblocking the road.\pI wonder if it's\nbeen cleared?$"
J_Route35GoldenrodGateRandyCantCarryAnotherMonText::
	.string "You can't carry\nanother POKéMON…$"
J_Route35GoldenrodGateRandyOhNeverMindThenText::
	.string "Oh… Never mind,\nthen…$"
J_Route35GoldenrodGateRandySomethingForYourTroubleText::
	.string "Thanks, kid! You\nmade the delivery\lfor me!\pHere's something\nfor your trouble!$"
J_Route35GoldenrodGateRandyMyPalWasSnoozingRightText::
	.string "My pal was snooz-\ning, right? Heh,\lwhat'd I say?$"
J_Route35GoldenrodGatePokefanFText::
	.string "A strange tree is\nblocking the road.\pIt wriggles around\nif you talk to it.\pI heard it became\nwild when someone\pwatered it with a\nSQUIRTBOTTLE.$"
J_Route35GoldenrodGatePokefanFText_FoughtSudowoodo::
	.string "I like the POKéMON\nLullaby they play\lon the radio.$"
J_Route35GoldenrodGateFisherText::
	.string "I wonder how many\nkinds of POKéMON\pthere are in the\nworld.\pThree years ago,\nPROF.OAK said that\pthere were 150\ndifferent kinds.$"
J_Route35GoldenrodGate_MapEvents::
