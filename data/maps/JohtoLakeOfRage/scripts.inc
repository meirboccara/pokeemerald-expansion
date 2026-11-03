@ KJH: translated from pokecrystal maps/LakeOfRage.asm by kjh_tools/johto

JohtoLakeOfRage_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoLakeOfRage_OnTransition
	.byte 0

JohtoLakeOfRage_OnTransition:
	call J_LakeOfRageFlypointCallback
	call J_LakeOfRageWesleyCallback
	end

J_W_LakeOfRageLanceScript::
	lock
	call J_LakeOfRageLanceScript
	release
	end

J_W_LakeOfRageGrampsScript::
	lock
	call J_LakeOfRageGrampsScript
	release
	end

J_W_LakeOfRageSuperNerdScript::
	lock
	call J_LakeOfRageSuperNerdScript
	release
	end

J_W_LakeOfRageCooltrainerFScript::
	lock
	call J_LakeOfRageCooltrainerFScript
	release
	end

J_T_TrainerFisherAndre::
	trainerbattle_single TRAINER_J_FISHER_ANDRE, J_FisherAndreSeenText, J_FisherAndreBeatenText
	call J_TrainerFisherAndre_Script
	release
	end

J_T_TrainerFisherRaymond::
	trainerbattle_single TRAINER_J_FISHER_RAYMOND, J_FisherRaymondSeenText, J_FisherRaymondBeatenText
	call J_TrainerFisherRaymond_Script
	release
	end

J_T_TrainerCooltrainermAaron::
	trainerbattle_single TRAINER_J_COOLTRAINERM_AARON, J_CooltrainermAaronSeenText, J_CooltrainermAaronBeatenText
	call J_TrainerCooltrainermAaron_Script
	release
	end

J_T_TrainerCooltrainerfLois::
	trainerbattle_single TRAINER_J_COOLTRAINERF_LOIS, J_CooltrainerfLoisSeenText, J_CooltrainerfLoisBeatenText
	call J_TrainerCooltrainerfLois_Script
	release
	end

J_W_RedGyarados::
	lock
	call J_RedGyarados
	release
	end

J_W_WesleyScript::
	lock
	call J_WesleyScript
	release
	end

J_S_LakeOfRageSign::
	lockall
	call J_LakeOfRageSign
	releaseall
	end

J_S_MagikarpHouseSignScript::
	lockall
	call J_MagikarpHouseSignScript
	releaseall
	end

J_LakeOfRage_MapScripts::
J_LakeOfRageNoop1Scene::
	return
J_LakeOfRageNoop2Scene::
	return
J_LakeOfRageFlypointCallback::
	setflag FLAG_J_ENGINE_FLYPOINT_LAKE_OF_RAGE
	return
J_LakeOfRageWesleyCallback::
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 3, J_LakeOfRageWesleyCallback_WesleyAppears
	setflag FLAG_J_LAKE_OF_RAGE_WESLEY_OF_WEDNESDAY
	return
J_LakeOfRageWesleyCallback_WesleyAppears:
	clearflag FLAG_J_LAKE_OF_RAGE_WESLEY_OF_WEDNESDAY
	return
J_LakeOfRageLanceScript::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_REFUSED_TO_HELP_LANCE_AT_LAKE_OF_RAGE, J_L398
	setvar VAR_RESULT, 1
J_L398:
	goto_if_ne VAR_RESULT, 0, J_LakeOfRageLanceScript_AskAgainForHelp
	message J_LakeOfRageLanceForcedToEvolveText
	waitmessage
	waitbuttonpress
	faceplayer
	message J_LakeOfRageLanceIntroText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_LakeOfRageLanceScript_RefusedToHelp
J_LakeOfRageLanceScript_AgreedToHelp:
	message J_LakeOfRageLanceRadioSignalText
	waitmessage
	waitbuttonpress
	closemessage
	playse SE_WARP_IN
	applymovement 1, J_LakeOfRageLanceTeleportIntoSkyMovement
	waitmovement 1
	removeobject 1
	clearflag FLAG_J_MAHOGANY_MART_LANCE_AND_DRAGONITE
	setflag FLAG_J_DECIDED_TO_HELP_LANCE
	setvar VAR_J_SCENE_MAHOGANY_MART_1F, 1
	return
J_LakeOfRageLanceScript_RefusedToHelp:
	message J_LakeOfRageLanceRefusedText
	waitmessage
	waitbuttonpress
	closemessage
	setflag FLAG_J_REFUSED_TO_HELP_LANCE_AT_LAKE_OF_RAGE
	return
J_LakeOfRageLanceScript_AskAgainForHelp:
	faceplayer
	message J_LakeOfRageLanceAskHelpText
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_LakeOfRageLanceScript_RefusedToHelp
	goto J_LakeOfRageLanceScript_AgreedToHelp
J_RedGyarados::
	message J_LakeOfRageGyaradosCryText
	waitmessage
	delay 15
	playmoncry SPECIES_GYARADOS, CRY_MODE_NORMAL
	waitmoncry
	closemessage
	setwildbattle SPECIES_GYARADOS, 30
	dowildbattle
	goto_if_eq VAR_RESULT, 1, J_RedGyarados_NotBeaten
	removeobject 9
J_RedGyarados_NotBeaten:
	setflag FLAG_J_HAS_RED_SCALE
	setvar VAR_RESULT, 1
	waitse
	message J_LakeOfRageGotRedScaleText
	waitmessage
	playse SE_SUCCESS
	waitse
	closemessage
	setvar VAR_J_SCENE_LAKE_OF_RAGE, 0
	addobject 1
	return
J_LakeOfRageGrampsScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_ROCKET_HIDEOUT, J_L399
	setvar VAR_RESULT, 1
J_L399:
	goto_if_ne VAR_RESULT, 0, J_LakeOfRageGrampsScript_ClearedRocketHideout
	message J_LakeOfRageGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_LakeOfRageGrampsScript_ClearedRocketHideout:
	message J_LakeOfRageGrampsText_ClearedRocketHideout
	waitmessage
	waitbuttonpress
	closemessage
	return
J_LakeOfRageSuperNerdScript::
	faceplayer
	message J_LakeOfRageSuperNerdText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_LakeOfRageCooltrainerFScript::
	faceplayer
	message J_LakeOfRageCooltrainerFText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_LakeOfRageSign::
	message J_LakeOfRageSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MagikarpHouseSignScript::
	message J_FishingGurusHouseSignText
	waitmessage
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_ROCKET_HIDEOUT, J_L400
	setvar VAR_RESULT, 1
J_L400:
	goto_if_ne VAR_RESULT, 0, J_MagikarpHouseSignScript_MagikarpLengthRecord
	waitbuttonpress
	closemessage
	return
J_MagikarpHouseSignScript_MagikarpLengthRecord:
	waitbuttonpress
	setvar VAR_RESULT, 0
	closemessage
	return
J_TrainerFisherAndre::
J_TrainerFisherAndre_Script:
	message J_FisherAndreAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerFisherRaymond::
J_TrainerFisherRaymond_Script:
	message J_FisherRaymondAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainermAaron::
J_TrainerCooltrainermAaron_Script:
	message J_CooltrainermAaronAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainerfLois::
J_TrainerCooltrainerfLois_Script:
	message J_CooltrainerfLoisAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_WesleyScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_BLACKBELT_FROM_WESLEY, J_L401
	setvar VAR_RESULT, 1
J_L401:
	goto_if_ne VAR_RESULT, 0, J_WesleyWednesdayScript
	setvar VAR_0x8004, 11
	special KJH_CrystalReadVar
	goto_if_ne VAR_RESULT, 3, J_WesleyNotWednesdayScript
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_MET_WESLEY_OF_WEDNESDAY, J_L402
	setvar VAR_RESULT, 1
J_L402:
	goto_if_ne VAR_RESULT, 0, J_WesleyScript_MetWesley
	message J_MeetWesleyText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_MET_WESLEY_OF_WEDNESDAY
J_WesleyScript_MetWesley:
	message J_WesleyGivesGiftText
	waitmessage
	waitbuttonpress
	giveitem ITEM_POTION, 1
	goto_if_eq VAR_RESULT, 0, J_WesleyDoneScript
	setflag FLAG_J_GOT_BLACKBELT_FROM_WESLEY
	message J_WesleyGaveGiftText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_WesleyWednesdayScript::
	message J_WesleyWednesdayText
	waitmessage
	waitbuttonpress
J_WesleyDoneScript::
	closemessage
	return
J_WesleyNotWednesdayScript::
	message J_WesleyNotWednesdayText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_LakeOfRageElixer::
	finditem ITEM_ELIXIR, 1
	return
J_LakeOfRageTMDetect::
	finditem ITEM_RARE_CANDY, 1
	return
J_LakeOfRageHiddenFullRestore::
	finditem ITEM_FULL_RESTORE
	return
J_LakeOfRageHiddenRareCandy::
	finditem ITEM_RARE_CANDY
	return
J_LakeOfRageHiddenMaxPotion::
	finditem ITEM_MAX_POTION
	return
J_LakeOfRageLanceTeleportIntoSkyMovement::
	step_end
J_LakeOfRageLanceForcedToEvolveText::
	.string "This lake is full\nof GYARADOS but\lnothing else…\pSo the MAGIKARP\nare being forced\lto evolve…$"
J_LakeOfRageLanceIntroText::
	.string "Did you come here\nbecause of the\lrumors?\pYou're {PLAYER}?\nI'm LANCE, a\ltrainer like you.\pI heard some ru-\nmors, so I came to\linvestigate…\pI saw the way you\nbattled earlier,\l{PLAYER}.\pI can tell that\nyou're a trainer\pwith considerable\nskill.\pIf you don't mind,\ncould you help me\linvestigate?$"
J_LakeOfRageLanceRadioSignalText::
	.string "LANCE: Excellent!\pIt seems that the\nLAKE's MAGIKARP\pare being forced\nto evolve.\pA mysterious radio\nbroadcast coming\pfrom MAHOGANY is\nthe cause.\pI'll be waiting\nfor you, {PLAYER}.$"
J_LakeOfRageLanceRefusedText::
	.string "Oh… Well, if you\nchange your mind,\lplease help me.$"
J_LakeOfRageLanceAskHelpText::
	.string "LANCE: Hm? Are you\ngoing to help me?$"
J_LakeOfRageGyaradosCryText::
	.string "GYARADOS: Gyashaa!$"
J_LakeOfRageGotRedScaleText::
	.string "{PLAYER} obtained a\nRED SCALE.$"
J_LakeOfRageGrampsText::
	.string "The GYARADOS are\nangry!\pIt's a bad omen!$"
J_LakeOfRageGrampsText_ClearedRocketHideout::
	.string "Hahah! The MAGI-\nKARP are biting!$"
J_LakeOfRageSuperNerdText::
	.string "I heard this lake\nwas made by ram-\lpaging GYARADOS.\pI wonder if there\nis any connection\pto their mass out-\nbreak now?$"
J_LakeOfRageCooltrainerFText::
	.string "Did my eyes de-\nceive me? I saw a\pred GYARADOS in\nthe LAKE…\pBut I thought\nGYARADOS were\lusually blue?$"
J_FisherAndreSeenText::
	.string "Let me battle with\nthe POKéMON I just\lcaught!$"
J_FisherAndreBeatenText::
	.string "I might be an ex-\npert angler, but\pI stink as a POKé-\nMON trainer…$"
J_FisherAndreAfterBattleText::
	.string "I won't lose as an\nangler! I catch\lPOKéMON all day.$"
J_FisherRaymondSeenText::
	.string "No matter what I\ndo, all I catch\pare the same POKé-\nMON…$"
J_FisherRaymondBeatenText::
	.string "My line's all\ntangled up…$"
J_FisherRaymondAfterBattleText::
	.string "Why can't I catch\nany good POKéMON?$"
J_CooltrainermAaronSeenText::
	.string "If a trainer spots\nanother trainer,\phe has to make a\nchallenge.\pThat is our\ndestiny.$"
J_CooltrainermAaronBeatenText::
	.string "Whew…\nGood battle.$"
J_CooltrainermAaronAfterBattleText::
	.string "POKéMON and their\ntrainer become\ppowerful through\nconstant battling.$"
J_CooltrainerfLoisSeenText::
	.string "What happened to\nthe red GYARADOS?\pIt's gone?\pOh, darn. I came\nhere for nothing?\pI know--let's\nbattle!$"
J_CooltrainerfLoisBeatenText::
	.string "Good going!$"
J_CooltrainerfLoisAfterBattleText::
	.string "Come to think of\nit, I've seen a\lpink BUTTERFREE.$"
J_MeetWesleyText::
	.string "WESLEY: Well, how\ndo you do?\pSeeing as how it's\nWednesday today,\pI'm WESLEY of\nWednesday.$"
J_WesleyGivesGiftText::
	.string "Pleased to meet\nyou. Please take a\lsouvenir.$"
J_WesleyGaveGiftText::
	.string "WESLEY: BLACKBELT\nbeefs up the power\lof fighting moves.$"
J_WesleyWednesdayText::
	.string "WESLEY: Since you\nfound me, you must\phave met my broth-\ners and sisters.\pOr did you just\nget lucky?$"
J_WesleyNotWednesdayText::
	.string "WESLEY: Today's\nnot Wednesday.\lThat's too bad.$"
J_LakeOfRageSignText::
	.string "LAKE OF RAGE,\nalso known as\lGYARADOS LAKE.$"
J_FishingGurusHouseSignText::
	.string "FISHING GURU'S\nHOUSE$"
J_LakeOfRage_MapEvents::
