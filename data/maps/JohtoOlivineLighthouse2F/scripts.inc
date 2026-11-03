@ KJH: translated from pokecrystal maps/OlivineLighthouse2F.asm by kjh_tools/johto

JohtoOlivineLighthouse2F_MapScripts::
	.byte 0

J_T_TrainerSailorHuey::
	trainerbattle_single TRAINER_J_SAILOR_HUEY1, J_SailorHueySeenText, J_SailorHueyBeatenText
	call J_TrainerSailorHuey_Script
	release
	end

J_T_TrainerGentlemanAlfred::
	trainerbattle_single TRAINER_J_GENTLEMAN_ALFRED, J_GentlemanAlfredSeenText, J_GentlemanAlfredBeatenText
	call J_TrainerGentlemanAlfred_Script
	release
	end

J_OlivineLighthouse2F_MapScripts::
J_TrainerGentlemanAlfred::
J_TrainerGentlemanAlfred_Script:
	message J_GentlemanAlfredAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSailorHuey::
J_TrainerSailorHuey_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_HUEY_READY_FOR_REMATCH, J_L140
	setvar VAR_RESULT, 1
J_L140:
	goto_if_ne VAR_RESULT, 0, J_TrainerSailorHuey_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_TrainerSailorHuey_NumberAccepted
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HUEY_ASKED_FOR_PHONE_NUMBER, J_L141
	setvar VAR_RESULT, 1
J_L141:
	goto_if_ne VAR_RESULT, 0, J_TrainerSailorHuey_AskedBefore
	setflag FLAG_J_HUEY_ASKED_FOR_PHONE_NUMBER
	call J_TrainerSailorHuey_AskNumber1
	goto J_TrainerSailorHuey_AskForNumber
J_TrainerSailorHuey_AskedBefore:
	call J_TrainerSailorHuey_AskNumber2
J_TrainerSailorHuey_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_TrainerSailorHuey_PhoneFull
	goto_if_eq VAR_RESULT, 2, J_TrainerSailorHuey_NumberDeclined
	bufferstring STR_VAR_1, J_TrainerName_SAILOR_HUEY1
	call J_TrainerSailorHuey_RegisteredNumber
	goto J_TrainerSailorHuey_NumberAccepted
J_TrainerSailorHuey_WantsBattle:
	call J_TrainerSailorHuey_Rematch
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 3, J_TrainerSailorHuey_Fight3
	goto_if_eq VAR_RESULT, 2, J_TrainerSailorHuey_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerSailorHuey_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerSailorHuey_LoadFight0
J_TrainerSailorHuey_Fight3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L142
	setvar VAR_RESULT, 1
J_L142:
	goto_if_ne VAR_RESULT, 0, J_TrainerSailorHuey_LoadFight3
J_TrainerSailorHuey_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L143
	setvar VAR_RESULT, 1
J_L143:
	goto_if_ne VAR_RESULT, 0, J_TrainerSailorHuey_LoadFight2
J_TrainerSailorHuey_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_CLEARED_RADIO_TOWER, J_L144
	setvar VAR_RESULT, 1
J_L144:
	goto_if_ne VAR_RESULT, 0, J_TrainerSailorHuey_LoadFight1
J_TrainerSailorHuey_LoadFight0:
	trainerbattle_no_intro TRAINER_J_SAILOR_HUEY1, J_SailorHueyBeatenText
	clearflag FLAG_J_ENGINE_HUEY_READY_FOR_REMATCH
	return
J_TrainerSailorHuey_LoadFight1:
	trainerbattle_no_intro TRAINER_J_SAILOR_HUEY2, J_Text_Empty
	clearflag FLAG_J_ENGINE_HUEY_READY_FOR_REMATCH
	return
J_TrainerSailorHuey_LoadFight2:
	trainerbattle_no_intro TRAINER_J_SAILOR_HUEY3, J_Text_Empty
	clearflag FLAG_J_ENGINE_HUEY_READY_FOR_REMATCH
	return
J_TrainerSailorHuey_LoadFight3:
	trainerbattle_no_intro TRAINER_J_SAILOR_HUEY4, J_Text_Empty
	clearflag FLAG_J_ENGINE_HUEY_READY_FOR_REMATCH
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_HUEY_PROTEIN, J_L145
	setvar VAR_RESULT, 1
J_L145:
	goto_if_ne VAR_RESULT, 0, J_TrainerSailorHuey_HasProtein
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_PROTEIN_FROM_HUEY, J_L146
	setvar VAR_RESULT, 1
J_L146:
	goto_if_ne VAR_RESULT, 0, J_TrainerSailorHuey_SkipGift
	call J_TrainerSailorHuey_RematchGift
	giveitem ITEM_PROTEIN, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerSailorHuey_PackFull
	setflag FLAG_J_GOT_PROTEIN_FROM_HUEY
	goto J_TrainerSailorHuey_NumberAccepted
J_TrainerSailorHuey_SkipGift:
	return
J_TrainerSailorHuey_HasProtein:
	message J_SailorHueyGiveProteinText
	waitmessage
	waitbuttonpress
	giveitem ITEM_PROTEIN, 1
	goto_if_eq VAR_RESULT, 0, J_TrainerSailorHuey_PackFull
	clearflag FLAG_J_HUEY_PROTEIN
	setflag FLAG_J_GOT_PROTEIN_FROM_HUEY
	goto J_TrainerSailorHuey_NumberAccepted
J_TrainerSailorHuey_AskNumber1:
	goto J_Std_Nop
	return
J_TrainerSailorHuey_AskNumber2:
	goto J_Std_Nop
	return
J_TrainerSailorHuey_RegisteredNumber:
	goto J_Std_Nop
	return
J_TrainerSailorHuey_NumberAccepted:
	goto J_Std_Nop
	return
J_TrainerSailorHuey_NumberDeclined:
	goto J_Std_Nop
	return
J_TrainerSailorHuey_PhoneFull:
	goto J_Std_Nop
	return
J_TrainerSailorHuey_Rematch:
	goto J_Std_Nop
	return
J_TrainerSailorHuey_PackFull:
	setflag FLAG_J_HUEY_PROTEIN
	goto J_Std_Nop
	return
J_TrainerSailorHuey_RematchGift:
	goto J_Std_Nop
	return
J_SailorHueySeenText::
	.string "Men of the sea are\nalways spoiling\lfor a good fight!$"
J_SailorHueyBeatenText::
	.string "Urf!\nI lose!$"
J_SailorHueyUnusedText::
	.string "What power!\nHow would you like\pto sail the seas\nwith me?$"
J_GentlemanAlfredSeenText::
	.string "Hm? This is no\nplace for playing.$"
J_GentlemanAlfredBeatenText::
	.string "Ah! I can see that\nyou're serious.$"
J_GentlemanAlfredAfterBattleText::
	.string "Up top is a POKé-\nMON that keeps the\lLIGHTHOUSE lit.\pBut I hear that\nit's sick now and\pcan't be cured by\nordinary medicine.$"
J_SailorHueyGiveProteinText::
	.string "Man! You're as\ntough as ever!\pAnyway, here's\nthat medicine from\lbefore.$"
J_OlivineLighthouse2F_MapEvents::
