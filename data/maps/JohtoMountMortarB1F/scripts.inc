@ KJH: translated from pokecrystal maps/MountMortarB1F.asm by kjh_tools/johto

JohtoMountMortarB1F_MapScripts::
	.byte 0

J_W_MountMortarB1FBoulder::
	lock
	call J_MountMortarB1FBoulder
	release
	end

J_W_MountMortarB1FKiyoScript::
	lock
	call J_MountMortarB1FKiyoScript
	release
	end

J_MountMortarB1F_MapScripts::
J_MountMortarB1FKiyoScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_TYROGUE_FROM_KIYO, J_L239
	setvar VAR_RESULT, 1
J_L239:
	goto_if_ne VAR_RESULT, 0, J_MountMortarB1FKiyoScript_GotTyrogue
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_BLACKBELT_KIYO, J_L240
	setvar VAR_RESULT, 1
J_L240:
	goto_if_ne VAR_RESULT, 0, J_MountMortarB1FKiyoScript_BeatKiyo
	message J_MountMortarB1FKiyoIntroText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_J_BLACKBELT_T_KIYO, J_MountMortarB1FKiyoWinText
	setflag FLAG_J_BEAT_BLACKBELT_KIYO
J_MountMortarB1FKiyoScript_BeatKiyo:
	message J_MountMortarB1FTyrogueRewardText
	waitmessage
	waitbuttonpress
	waitse
	setvar VAR_0x8004, 1
	special KJH_CrystalReadVar
	goto_if_eq VAR_RESULT, 6, J_MountMortarB1FKiyoScript_NoRoom
	message J_MountMortarB1FReceiveMonText
	waitmessage
	playse SE_SUCCESS
	waitse
	givemon SPECIES_TYROGUE, 10, ITEM_NONE
	setflag FLAG_SYS_POKEMON_GET
	bufferspeciesname STR_VAR_1, SPECIES_TYROGUE
	playfanfare MUS_LEVEL_UP
	message J_Text_ReceivedMon
	waitmessage
	waitfanfare
	setvar VAR_RESULT, 1
	setflag FLAG_J_GOT_TYROGUE_FROM_KIYO
J_MountMortarB1FKiyoScript_GotTyrogue:
	message J_MountMortarB1FKiyoGotTyrogueText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MountMortarB1FKiyoScript_NoRoom:
	message J_MountMortarB1FKiyoFullPartyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_MountMortarB1FBoulder::
	goto EventScript_StrengthBoulder
J_MountMortarB1FHyperPotion::
	finditem ITEM_HYPER_POTION, 1
	return
J_MountMortarB1FCarbos::
	finditem ITEM_CARBOS, 1
	return
J_MountMortarB1FFullRestore::
	finditem ITEM_FULL_RESTORE, 1
	return
J_MountMortarB1FMaxEther::
	finditem ITEM_MAX_ETHER, 1
	return
J_MountMortarB1FPPUp::
	finditem ITEM_PP_UP, 1
	return
J_MountMortarB1FHiddenMaxRevive::
	finditem ITEM_MAX_REVIVE
	return
J_MountMortarB1FKiyoIntroText::
	.string "Hey!\pI am the KARATE\nKING!\pI train alone here\nin the dark!\pYou!\nBattle with me!\pHwaaarggh!$"
J_MountMortarB1FKiyoWinText::
	.string "Waaaarggh!\nI'm beaten!$"
J_MountMortarB1FTyrogueRewardText::
	.string "I… I'm crushed…\pMy training is\nstill not enough…\pBut a loss is a\nloss. I admit it.\pAs proof that you\ndefeated me, I'll\pgive you a rare\nfighting POKéMON.$"
J_MountMortarB1FReceiveMonText::
	.string "{PLAYER} received\nTYROGUE.$"
J_MountMortarB1FKiyoGotTyrogueText::
	.string "TYROGUE is a\nfighting-type.\pIt evolves into a\ntougher POKéMON.\pKeep up the hard\nwork. I'll keep\ltraining too.\pFarewell!$"
J_MountMortarB1FKiyoFullPartyText::
	.string "You have no room\nin your party!$"
J_MountMortarB1F_MapEvents::
