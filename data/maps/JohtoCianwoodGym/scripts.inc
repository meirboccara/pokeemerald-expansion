@ KJH: translated from pokecrystal maps/CianwoodGym.asm by kjh_tools/johto

JohtoCianwoodGym_MapScripts::
	.byte 0

J_W_CianwoodGymChuckScript::
	lock
	call J_CianwoodGymChuckScript
	release
	end

J_T_TrainerBlackbeltYoshi::
	trainerbattle_single TRAINER_J_BLACKBELT_T_YOSHI, J_BlackbeltYoshiSeenText, J_BlackbeltYoshiBeatenText
	call J_TrainerBlackbeltYoshi_Script
	release
	end

J_T_TrainerBlackbeltLao::
	trainerbattle_single TRAINER_J_BLACKBELT_T_LAO, J_BlackbeltLaoSeenText, J_BlackbeltLaoBeatenText
	call J_TrainerBlackbeltLao_Script
	release
	end

J_T_TrainerBlackbeltNob::
	trainerbattle_single TRAINER_J_BLACKBELT_T_NOB, J_BlackbeltNobSeenText, J_BlackbeltNobBeatenText
	call J_TrainerBlackbeltNob_Script
	release
	end

J_T_TrainerBlackbeltLung::
	trainerbattle_single TRAINER_J_BLACKBELT_T_LUNG, J_BlackbeltLungSeenText, J_BlackbeltLungBeatenText
	call J_TrainerBlackbeltLung_Script
	release
	end

J_W_CianwoodGymBoulder::
	lock
	call J_CianwoodGymBoulder
	release
	end

J_S_CianwoodGymStatue::
	lockall
	call J_CianwoodGymStatue
	releaseall
	end

J_CianwoodGym_MapScripts::
J_CianwoodGymChuckScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_CHUCK, J_L590
	setvar VAR_RESULT, 1
J_L590:
	goto_if_ne VAR_RESULT, 0, J_CianwoodGymChuckScript_FightDone
	message J_ChuckIntroText1
	waitmessage
	waitbuttonpress
	closemessage
	turnobject 1, DIR_EAST
	message J_ChuckIntroText2
	waitmessage
	waitbuttonpress
	closemessage
	applymovement 6, J_CianwoodGymMovement_ChuckChucksBoulder
	waitmovement 6
	playse SE_M_STRENGTH
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 4
	special ShakeScreen
	delay 40
	removeobject 6
	delay 30
	faceplayer
	message J_ChuckIntroText3
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_J_CHUCK_CHUCK1, J_ChuckLossText
	setflag FLAG_J_BEAT_CHUCK
	message J_GetStormBadgeText
	waitmessage
	playse SE_SUCCESS
	waitse
	setflag FLAG_JOHTO_BADGE05_GET
	setvar VAR_0x8004, 7
	special KJH_CrystalReadVar
	call J_CianwoodGymActivateRockets
J_CianwoodGymChuckScript_FightDone:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TM01_DYNAMICPUNCH, J_L591
	setvar VAR_RESULT, 1
J_L591:
	goto_if_ne VAR_RESULT, 0, J_CianwoodGymChuckScript_AlreadyGotTM
	setflag (TRAINER_FLAGS_START + TRAINER_J_BLACKBELT_T_YOSHI)
	setflag (TRAINER_FLAGS_START + TRAINER_J_BLACKBELT_T_LAO)
	setflag (TRAINER_FLAGS_START + TRAINER_J_BLACKBELT_T_NOB)
	setflag (TRAINER_FLAGS_START + TRAINER_J_BLACKBELT_T_LUNG)
	message J_ChuckExplainBadgeText
	waitmessage
	waitbuttonpress
	giveitem ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, 0, J_CianwoodGymChuckScript_BagFull
	setflag FLAG_J_GOT_TM01_DYNAMICPUNCH
	message J_ChuckExplainTMText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodGymChuckScript_AlreadyGotTM:
	message J_ChuckAfterText
	waitmessage
	waitbuttonpress
J_CianwoodGymChuckScript_BagFull:
	closemessage
	return
J_CianwoodGymActivateRockets::
	goto_if_eq VAR_RESULT, 7, J_CianwoodGymActivateRockets_RadioTowerRockets
	goto_if_eq VAR_RESULT, 6, J_CianwoodGymActivateRockets_GoldenrodRockets
	return
J_CianwoodGymActivateRockets_GoldenrodRockets:
	goto J_GoldenrodRocketsScript
J_CianwoodGymActivateRockets_RadioTowerRockets:
	goto J_RadioTowerRocketsScript
J_TrainerBlackbeltYoshi::
J_TrainerBlackbeltYoshi_Script:
	message J_BlackbeltYoshiAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBlackbeltLao::
J_TrainerBlackbeltLao_Script:
	message J_BlackbeltLaoAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBlackbeltNob::
J_TrainerBlackbeltNob_Script:
	message J_BlackbeltNobAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBlackbeltLung::
J_TrainerBlackbeltLung_Script:
	message J_BlackbeltLungAfterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodGymBoulder::
	goto EventScript_StrengthBoulder
J_CianwoodGymStatue::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE05_GET, J_L592
	setvar VAR_RESULT, 1
J_L592:
	goto_if_ne VAR_RESULT, 0, J_CianwoodGymStatue_Beaten
	goto J_GymStatue1Script
J_CianwoodGymStatue_Beaten:
	bufferstring STR_VAR_2, J_TrainerName_CHUCK_CHUCK1
	goto J_GymStatue2Script
J_CianwoodGymMovement_ChuckChucksBoulder::
	walk_fast_left
	walk_fast_up
	jump_right
	step_end
J_ChuckIntroText1::
	.string "WAHAHAH!\pSo you've come\nthis far!\pLet me tell you,\nI'm tough!\pMy POKéMON will\ncrush stones and\lshatter bones!\pWatch this!$"
J_ChuckIntroText2::
	.string "CHUCK: Urggh!\n…\pOooarrgh!$"
J_ChuckIntroText3::
	.string "There! Scared now,\nare you?\pWhat?\nIt has nothing to\pdo with POKéMON?\nThat's true!\pCome on. We shall\ndo battle!$"
J_ChuckLossText::
	.string "Wha? Huh?\nI lost?\pHow about that!\nYou're worthy of\lSTORMBADGE!$"
J_GetStormBadgeText::
	.string "{PLAYER} received\nSTORMBADGE.$"
J_ChuckExplainBadgeText::
	.string "STORMBADGE lets\nyour POKéMON use\pFLY when you're\nnot in a battle.\pHere, take this\ntoo!$"
J_ChuckExplainTMText::
	.string "That is DYNAMIC-\nPUNCH.\pIt doesn't always\nhit, but when it\pdoes, it causes\nconfusion!$"
J_ChuckAfterText::
	.string "WAHAHAH! I enjoyed\nbattling you!\pBut a loss is a\nloss!\pFrom now on, I'm\ngoing to train 24\lhours a day!$"
J_BlackbeltYoshiSeenText::
	.string "My POKéMON and I\nare bound togeth-\ler by friendship.\pOur bond will\nnever be broken!$"
J_BlackbeltYoshiBeatenText::
	.string "This isn't real!$"
J_BlackbeltYoshiAfterText::
	.string "You seem to have a\nstrong bond with\lyour POKéMON too!$"
J_BlackbeltLaoSeenText::
	.string "We martial artists\nfear nothing!$"
J_BlackbeltLaoBeatenText::
	.string "That's shocking!$"
J_BlackbeltLaoAfterText::
	.string "Fighting POKéMON\nare afraid of psy-\lchics…$"
J_BlackbeltNobSeenText::
	.string "Words are useless.\nLet your fists do\lthe talking!$"
J_BlackbeltNobBeatenText::
	.string "…$"
J_BlackbeltNobAfterText::
	.string "I lost! \nI'm speechless!$"
J_BlackbeltLungSeenText::
	.string "My raging fists\nwill shatter your\lPOKéMON!$"
J_BlackbeltLungBeatenText::
	.string "I got shattered!$"
J_BlackbeltLungAfterText::
	.string "My POKéMON lost…\nMy… my pride is\lshattered…$"
J_CianwoodGym_MapEvents::
