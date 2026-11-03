@ KJH: translated from pokecrystal maps/DayOfWeekSiblingsHouse.asm by kjh_tools/johto

JohtoDayOfWeekSiblingsHouse_MapScripts::
	.byte 0

J_W_DayOfWeekSiblingsHousePokedexScript::
	lock
	call J_DayOfWeekSiblingsHousePokedexScript
	release
	end

J_DayOfWeekSiblingsHouse_MapScripts::
J_DayOfWeekSiblingsHousePokedexScript::
	message J_DayOfWeekSiblingsHousePokedexText1
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_DayOfWeekSiblingsHousePokedexScript_End
	message J_DayOfWeekSiblingsHousePokedexText2
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_DayOfWeekSiblingsHousePokedexScript_End
	message J_DayOfWeekSiblingsHousePokedexText3
	waitmessage
	waitbuttonpress
J_DayOfWeekSiblingsHousePokedexScript_End:
	closemessage
	return
J_DayOfWeekSiblingsHousePokedexText1::
	.string "There's something\nwritten here.\pRead it?$"
J_DayOfWeekSiblingsHousePokedexText2::
	.string "To my brothers and\nsisters:\pWe take pride in\nserving POKéMON\ltrainers.\pWhen trainers talk\nto you, give them\lsomething useful.\pLove,\nMONICA\pKeep reading?$"
J_DayOfWeekSiblingsHousePokedexText3::
	.string "Monday, MONICA\nROUTE 40\pTuesday, TUSCANY\nROUTE 29\pWednesday, WESLEY\nLAKE OF RAGE\pThursday, ARTHUR\nROUTE 36\pFriday, FRIEDA\nROUTE 32\pSaturday, SANTOS\nBLACKTHORN CITY\pSunday, SUNNY\nROUTE 37$"
J_DayOfWeekSiblingsHouse_MapEvents::
