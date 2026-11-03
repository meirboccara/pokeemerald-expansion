@ KJH: translated from pokecrystal maps/LakeOfRageMagikarpHouse.asm by kjh_tools/johto

JohtoLakeOfRageMagikarpHouse_MapScripts::
	.byte 0

J_W_MagikarpLengthRaterScript::
	lock
	call J_MagikarpLengthRaterScript
	release
	end

J_S_MagikarpHouseBookshelf::
	lockall
	call J_MagikarpHouseBookshelf
	releaseall
	end

J_LakeOfRageMagikarpHouse_MapScripts::
J_MagikarpLengthRaterScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_LAKE_OF_RAGE_ELIXIR_ON_STANDBY, J_L375
	setvar VAR_RESULT, 1
J_L375:
	goto_if_ne VAR_RESULT, 0, J_MagikarpLengthRaterScript_GetReward
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_LAKE_OF_RAGE_ASKED_FOR_MAGIKARP, J_L376
	setvar VAR_RESULT, 1
J_L376:
	goto_if_ne VAR_RESULT, 0, J_MagikarpLengthRaterScript_AskedForMagikarp
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_ROCKET_HIDEOUT, J_L377
	setvar VAR_RESULT, 1
J_L377:
	goto_if_ne VAR_RESULT, 0, J_MagikarpLengthRaterScript_ClearedRocketHideout
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_LAKE_OF_RAGE_EXPLAINED_WEIRD_MAGIKARP, J_L378
	setvar VAR_RESULT, 1
J_L378:
	goto_if_ne VAR_RESULT, 0, J_MagikarpLengthRaterScript_ExplainedHistory
	message J_MagikarpLengthRaterText_LakeOfRageHistory
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_LAKE_OF_RAGE_EXPLAINED_WEIRD_MAGIKARP
	return
J_MagikarpLengthRaterScript_ExplainedHistory:
	message J_MagikarpLengthRaterText_MenInBlack
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MagikarpLengthRaterScript_ClearedRocketHideout:
	message J_MagikarpLengthRaterText_WorldsLargestMagikarp
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_LAKE_OF_RAGE_ASKED_FOR_MAGIKARP
	return
J_MagikarpLengthRaterScript_AskedForMagikarp:
	setvar VAR_RESULT, 129
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_MagikarpLengthRaterScript_ClearedRocketHideout
	message J_MagikarpLengthRaterText_YouHaveAMagikarp
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_MagikarpLengthRaterScript_NotMagikarp
	goto_if_eq VAR_RESULT, 1, J_MagikarpLengthRaterScript_Refused
	goto_if_eq VAR_RESULT, 2, J_MagikarpLengthRaterScript_TooShort
	goto J_MagikarpLengthRaterScript_GetReward
J_MagikarpLengthRaterScript_GetReward:
	message J_MagikarpLengthRaterText_Memento
	waitmessage
	waitbuttonpress
	giveitem ITEM_ELIXIR, 1
	goto_if_eq VAR_RESULT, 0, J_MagikarpLengthRaterScript_NoRoom
	message J_MagikarpLengthRaterText_Bonus
	waitmessage
	waitbuttonpress
	closemessage
	clearflag FLAG_J_LAKE_OF_RAGE_ELIXIR_ON_STANDBY
	return
J_MagikarpLengthRaterScript_NoRoom:
	closemessage
	setflag FLAG_J_LAKE_OF_RAGE_ELIXIR_ON_STANDBY
	return
J_MagikarpLengthRaterScript_TooShort:
	message J_MagikarpLengthRaterText_TooShort
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MagikarpLengthRaterScript_NotMagikarp:
	message J_MagikarpLengthRaterText_NotMagikarp
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MagikarpLengthRaterScript_Refused:
	message J_MagikarpLengthRaterText_Refused
	waitmessage
	waitbuttonpress
	closemessage
	return
J_LakeOfRageMagikarpHouseUnusedRecordSign::
	message J_LakeOfRageMagikarpHouseUnusedRecordText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MagikarpHouseBookshelf::
	goto J_DifficultBookshelfScript
J_MagikarpLengthRaterText_LakeOfRageHistory::
	.string "LAKE OF RAGE is\nactually a crater\pmade by rampaging\nGYARADOS.\pThe crater filled\nup with rainwater\pand the LAKE was\nformed.\pThat's the story\npassed on from my\pGrandpa's great-\ngreat-grandpa.\pIt used to be that\nyou could catch\plively MAGIKARP\nthere, but…\pI don't understand\nwhat's happening.$"
J_MagikarpLengthRaterText_MenInBlack::
	.string "The LAKE hasn't\nbeen normal since\pthose men wearing\nblack arrived.$"
J_MagikarpLengthRaterText_WorldsLargestMagikarp::
	.string "LAKE OF RAGE is\nback to normal.\pThe MAGIKARP have\nreturned.\pI may yet realize\nmy dream of see-\ling the world's\llargest MAGIKARP.\pDo you have a ROD?\nPlease help me if\lyou do.$"
J_MagikarpLengthRaterText_YouHaveAMagikarp::
	.string "Ah, you have a\nMAGIKARP! Let's\psee how big that\nbaby is.$"
J_MagikarpLengthRaterText_Memento::
	.string "Wow! This one is\noutstanding!\pI tip my hat to\nyou!\pTake this as a\nmemento!$"
J_MagikarpLengthRaterText_Bonus::
	.string "The record is the\nimportant thing.\pThink of that as\na bonus!$"
J_MagikarpLengthRaterText_TooShort::
	.string "Wow! This one is\noutstanding!\p…I wish I could\nsay that, but I've\pseen a bigger one\nbefore.$"
J_MagikarpLengthRaterText_NotMagikarp::
	.string "What? That's not a\nMAGIKARP!$"
J_MagikarpLengthRaterText_Refused::
	.string "Oh… So you didn't\nget one good\penough to show me?\nMaybe next time.$"
J_LakeOfRageMagikarpHouseUnusedRecordText::
	.string "CURRENT RECORD\p{STR_VAR_1} caught by\n{STR_VAR_2}$"
J_LakeOfRageMagikarpHouseUnusedDummyText::
	.string "$"
J_LakeOfRageMagikarpHouse_MapEvents::
