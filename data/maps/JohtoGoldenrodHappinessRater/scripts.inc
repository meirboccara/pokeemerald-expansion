@ KJH: translated from pokecrystal maps/GoldenrodHappinessRater.asm by kjh_tools/johto

JohtoGoldenrodHappinessRater_MapScripts::
	.byte 0

J_W_GoldenrodHappinessRaterTeacherScript::
	lock
	call J_GoldenrodHappinessRaterTeacherScript
	release
	end

J_W_GoldenrodHappinessRaterPokefanMScript::
	lock
	call J_GoldenrodHappinessRaterPokefanMScript
	release
	end

J_W_GoldenrodHappinessRaterTwinScript::
	lock
	call J_GoldenrodHappinessRaterTwinScript
	release
	end

J_S_HappinessRatersHouseBookshelf::
	lockall
	call J_HappinessRatersHouseBookshelf
	releaseall
	end

J_S_HappinessRatersHouseRadio::
	lockall
	call J_HappinessRatersHouseRadio
	releaseall
	end

J_GoldenrodHappinessRater_MapScripts::
J_GoldenrodHappinessRaterTeacherScript::
	faceplayer
	special KJH_GetLeadFriendship
	message J_GoldenrodHappinessRaterTeacherText
	waitmessage
	waitbuttonpress
	goto_if_gt VAR_RESULT, 249, J_GoldenrodHappinessRaterTeacherScript_LovesYouALot
	goto_if_gt VAR_RESULT, 199, J_GoldenrodHappinessRaterTeacherScript_ReallyTrustsYou
	goto_if_gt VAR_RESULT, 149, J_GoldenrodHappinessRaterTeacherScript_SortOfHappy
	goto_if_gt VAR_RESULT, 99, J_GoldenrodHappinessRaterTeacherScript_QuiteCute
	goto_if_gt VAR_RESULT, 49, J_GoldenrodHappinessRaterTeacherScript_NotUsedToYou
	goto J_GoldenrodHappinessRaterTeacherScript_LooksMean
J_GoldenrodHappinessRaterTeacherScript_LovesYouALot:
	message J_GoldenrodHappinessRatingText_LovesYouALot
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodHappinessRaterTeacherScript_ReallyTrustsYou:
	message J_GoldenrodHappinessRatingText_ReallyTrustsYou
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodHappinessRaterTeacherScript_SortOfHappy:
	message J_GoldenrodHappinessRatingText_SortOfHappy
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodHappinessRaterTeacherScript_QuiteCute:
	message J_GoldenrodHappinessRatingText_QuiteCute
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodHappinessRaterTeacherScript_NotUsedToYou:
	message J_GoldenrodHappinessRatingText_NotUsedToYou
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodHappinessRaterTeacherScript_LooksMean:
	message J_GoldenrodHappinessRatingText_LooksMean
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodHappinessRaterPokefanMScript::
	faceplayer
	message J_GoldenrodHappinessRaterPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodHappinessRaterTwinScript::
	faceplayer
	message J_GoldenrodHappinessRaterTwinText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_HappinessRatersHouseBookshelf::
	goto J_DifficultBookshelfScript
J_HappinessRatersHouseRadio::
	goto J_Radio2Script
J_GoldenrodHappinessRaterTeacherText::
	.string "If you treat your\nPOKéMON nicely,\pthey will love you\nin return.\pOh? Let me see\nyour {STR_VAR_1}…$"
J_GoldenrodHappinessRatingText_LovesYouALot::
	.string "It looks really\nhappy! It must\llove you a lot.$"
J_GoldenrodHappinessRatingText_ReallyTrustsYou::
	.string "I get the feeling\nthat it really\ltrusts you.$"
J_GoldenrodHappinessRatingText_SortOfHappy::
	.string "It's friendly to-\nward you. It looks\lsort of happy.$"
J_GoldenrodHappinessRatingText_QuiteCute::
	.string "It's quite cute.$"
J_GoldenrodHappinessRatingText_NotUsedToYou::
	.string "You should treat\nit better. It's\lnot used to you.$"
J_GoldenrodHappinessRatingText_LooksMean::
	.string "It doesn't seem to\nlike you at all.\lIt looks mean.$"
J_GoldenrodHappinessRaterPokefanMText::
	.string "I keep losing in\nbattles, and my\pPOKéMON end up\nfainting…\pMaybe that's why\nmy POKéMON don't\llike me much…$"
J_GoldenrodHappinessRaterTwinText::
	.string "When I use an item\non my POKéMON, it\lacts really glad!$"
J_GoldenrodHappinessRater_MapEvents::
