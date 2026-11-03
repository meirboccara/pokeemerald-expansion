@ KJH: translated from pokecrystal maps/GoldenrodDeptStore5F.asm by kjh_tools/johto

JohtoGoldenrodDeptStore5F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoGoldenrodDeptStore5F_OnTransition
	.byte 0

JohtoGoldenrodDeptStore5F_OnTransition:
	call J_GoldenrodDeptStore5FCheckIfSundayCallback
	end

J_W_GoldenrodDeptStore5FClerkScript::
	lock
	call J_GoldenrodDeptStore5FClerkScript
	release
	end

J_W_GoldenrodDeptStore5FLassScript::
	lock
	call J_GoldenrodDeptStore5FLassScript
	release
	end

J_W_Mike::
	lock
	call J_Mike
	release
	end

J_W_GoldenrodDeptStore5FPokefanMScript::
	lock
	call J_GoldenrodDeptStore5FPokefanMScript
	release
	end

J_W_Carrie::
	lock
	call J_Carrie
	release
	end

J_W_GoldenrodDeptStore5FReceptionistScript::
	lock
	call J_GoldenrodDeptStore5FReceptionistScript
	release
	end

J_S_GoldenrodDeptStore5FDirectory::
	lockall
	call J_GoldenrodDeptStore5FDirectory
	releaseall
	end

J_S_GoldenrodDeptStore5FElevatorButton::
	lockall
	call J_GoldenrodDeptStore5FElevatorButton
	releaseall
	end

J_GoldenrodDeptStore5F_MapScripts::
J_GoldenrodDeptStore5FCheckIfSundayCallback::
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 0, J_GoldenrodDeptStore5FCheckIfSundayCallback_yes
	setflag FLAG_J_GOLDENROD_DEPT_STORE_5F_HAPPINESS_EVENT_LADY
	return
J_GoldenrodDeptStore5FCheckIfSundayCallback_yes:
	clearflag FLAG_J_GOLDENROD_DEPT_STORE_5F_HAPPINESS_EVENT_LADY
	return
J_GoldenrodDeptStore5FClerkScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM02_HEADBUTT, J_L536
	setvar VAR_RESULT, 1
J_L536:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodDeptStore5FClerkScript_headbutt
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM08_ROCK_SMASH, J_L537
	setvar VAR_RESULT, 1
J_L537:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodDeptStore5FClerkScript_onlyrocksmash
	goto J_GoldenrodDeptStore5FClerkScript_neither
J_GoldenrodDeptStore5FClerkScript_headbutt:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM08_ROCK_SMASH, J_L538
	setvar VAR_RESULT, 1
J_L538:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodDeptStore5FClerkScript_both
	goto J_GoldenrodDeptStore5FClerkScript_onlyheadbutt
J_GoldenrodDeptStore5FClerkScript_neither:
	pokemart J_Mart_MART_GOLDENROD_5F_1
	closemessage
	return
J_GoldenrodDeptStore5FClerkScript_onlyheadbutt:
	pokemart J_Mart_MART_GOLDENROD_5F_2
	closemessage
	return
J_GoldenrodDeptStore5FClerkScript_onlyrocksmash:
	pokemart J_Mart_MART_GOLDENROD_5F_3
	closemessage
	return
J_GoldenrodDeptStore5FClerkScript_both:
	pokemart J_Mart_MART_GOLDENROD_5F_4
	closemessage
	return
J_GoldenrodDeptStore5FReceptionistScript::
	faceplayer
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_ne VAR_RESULT, 0, J_GoldenrodDeptStore5FReceptionistScript_EventIsOver
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_GOLDENROD_DEPT_STORE_TM27_RETURN, J_L539
	setvar VAR_RESULT, 1
J_L539:
	goto_if_ne VAR_RESULT, 0, J_GoldenrodDeptStore5FReceptionistScript_EventIsOver
	special KJH_GetLeadFriendship
	message J_GoldenrodDeptStore5FReceptionistOhYourMonDotDotDotText
	waitmessage
	waitbuttonpress
	goto_if_gt VAR_RESULT, 149, J_GoldenrodDeptStore5FReceptionistScript_VeryHappy
	goto_if_gt VAR_RESULT, 49, J_GoldenrodDeptStore5FReceptionistScript_SomewhatHappy
	goto J_GoldenrodDeptStore5FReceptionistScript_NotVeryHappy
J_GoldenrodDeptStore5FReceptionistScript_VeryHappy:
	message J_GoldenrodDeptStore5FReceptionistThisMoveShouldBePerfectText
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM27, 1
	goto_if_eq VAR_RESULT, 0, J_GoldenrodDeptStore5FReceptionistScript_Done
	setflag FLAG_J_ENGINE_GOLDENROD_DEPT_STORE_TM27_RETURN
	closemessage
	return
J_GoldenrodDeptStore5FReceptionistScript_SomewhatHappy:
	message J_GoldenrodDeptStore5FReceptionistItsAdorableText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore5FReceptionistScript_NotVeryHappy:
	message J_GoldenrodDeptStore5FReceptionistItLooksEvilHowAboutThisTMText
	waitmessage
	waitbuttonpress
	giveitem ITEM_TM21, 1
	goto_if_eq VAR_RESULT, 0, J_GoldenrodDeptStore5FReceptionistScript_Done
	setflag FLAG_J_ENGINE_GOLDENROD_DEPT_STORE_TM27_RETURN
	closemessage
	return
J_GoldenrodDeptStore5FReceptionistScript_EventIsOver:
	message J_GoldenrodDeptStore5FReceptionistThereAreTMsPerfectForMonText
	waitmessage
	waitbuttonpress
J_GoldenrodDeptStore5FReceptionistScript_Done:
	closemessage
	return
J_Carrie::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 2, J_Carrie_NotGBC
	message J_GoldenrodDeptStore5FCarrieMysteryGiftExplanationText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_RESULT, 0
	return
J_Carrie_NotGBC:
	message J_GoldenrodDeptStore5FCarrieMysteryGiftRequiresGBCText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore5FLassScript::
	faceplayer
	message J_GoldenrodDeptStore5FLassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Mike::
	faceplayer
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore5FPokefanMScript::
	faceplayer
	message J_GoldenrodDeptStore5FPokefanMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore5FDirectory::
	message J_GoldenrodDeptStore5FDirectoryText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GoldenrodDeptStore5FElevatorButton::
	goto J_Std_Nop
J_GoldenrodDeptStore5FReceptionistOhYourMonDotDotDotText::
	.string "Hello. Oh, your\nPOKéMON…$"
J_GoldenrodDeptStore5FReceptionistThisMoveShouldBePerfectText::
	.string "It's very attached\nto you.\pThis move should\nbe perfect for a\lpair like you.$"
J_GoldenrodDeptStore5FReceptionistItsAdorableText::
	.string "It's adorable!\pYou should teach\nit good TM moves.$"
J_GoldenrodDeptStore5FReceptionistItLooksEvilHowAboutThisTMText::
	.string "It looks evil. How\nabout this TM for\lit?$"
J_GoldenrodDeptStore5FReceptionistThereAreTMsPerfectForMonText::
	.string "There are sure to\nbe TMs that are\pjust perfect for\nyour POKéMON.$"
J_GoldenrodDeptStore5FCarrieMysteryGiftExplanationText::
	.string "MYSTERY GIFT.\pWith just a\nlittle beep, you\lget a gift.$"
J_GoldenrodDeptStore5FCarrieMysteryGiftRequiresGBCText::
	.string "The MYSTERY GIFT\noption requires a\lGame Boy Color.$"
J_GoldenrodDeptStore5FLassText::
	.string "On Sundays, a lady\ncomes to check out\lPOKéMON.\pShe even gives\naway TMs!$"
J_GoldenrodDeptStore5FPokefanMText::
	.string "You can't rename a\nPOKéMON you get in\la trade.\pThe name is a re-\nflection of the\poriginal trainer's\nfeelings for it.$"
J_GoldenrodDeptStore5FDirectoryText::
	.string "Customize Your\nPOKéMON\p5F TM CORNER$"
J_GoldenrodDeptStore5F_MapEvents::
