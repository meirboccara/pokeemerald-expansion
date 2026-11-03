@ KJH: translated from pokecrystal maps/BlackthornGym2F.asm by kjh_tools/johto

JohtoBlackthornGym2F_MapScripts::
	.byte 0

J_T_TrainerCooltrainermCody::
	trainerbattle_single TRAINER_J_COOLTRAINERM_CODY, J_CooltrainermCodySeenText, J_CooltrainermCodyBeatenText
	call J_TrainerCooltrainermCody_Script
	release
	end

J_T_TrainerCooltrainerfFran::
	trainerbattle_single TRAINER_J_COOLTRAINERF_FRAN, J_CooltrainerfFranSeenText, J_CooltrainerfFranBeatenText
	call J_TrainerCooltrainerfFran_Script
	release
	end

J_W_BlackthornGymBoulder::
	lock
	call J_BlackthornGymBoulder
	release
	end

J_BlackthornGym2F_MapScripts::
J_BlackthornGym2FSetUpStoneTableCallback::
	return
J_BlackthornGym2FSetUpStoneTableCallback_CommandQueue:
J_BlackthornGym2FSetUpStoneTableCallback_StoneTable:
J_BlackthornGym2FSetUpStoneTableCallback_Boulder1:
	setflag FLAG_J_BOULDER_IN_BLACKTHORN_GYM_1
	goto J_BlackthornGym2FSetUpStoneTableCallback_Fall
J_BlackthornGym2FSetUpStoneTableCallback_Boulder2:
	setflag FLAG_J_BOULDER_IN_BLACKTHORN_GYM_2
	goto J_BlackthornGym2FSetUpStoneTableCallback_Fall
J_BlackthornGym2FSetUpStoneTableCallback_Boulder3:
	setflag FLAG_J_BOULDER_IN_BLACKTHORN_GYM_3
	goto J_BlackthornGym2FSetUpStoneTableCallback_Fall
J_BlackthornGym2FSetUpStoneTableCallback_Fall:
	delay 30
	call J_BlackthornGym2FSetUpStoneTableCallback_FX
	message J_BlackthornGym2FBoulderFellText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BlackthornGym2FSetUpStoneTableCallback_FX:
	playse SE_M_STRENGTH
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 4
	special ShakeScreen
	delay 40
	return
J_BlackthornGymBoulder::
	goto EventScript_StrengthBoulder
J_TrainerCooltrainermCody::
J_TrainerCooltrainermCody_Script:
	message J_CooltrainermCodyAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCooltrainerfFran::
J_TrainerCooltrainerfFran_Script:
	message J_CooltrainerfFranAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CooltrainermCodySeenText::
	.string "It's not as if we\nall use dragon-\ltype POKéMON.$"
J_CooltrainermCodyBeatenText::
	.string "Rats! If only I\nhad a dragon!$"
J_CooltrainermCodyAfterBattleText::
	.string "Members of our\ndragon-user clan\pcan use dragon\nPOKéMON only after\pour MASTER allows\nit.$"
J_CooltrainerfFranSeenText::
	.string "I can't allow a\nnameless trainer\lpast me!\pCLAIR would be\nlivid if I did!$"
J_CooltrainerfFranBeatenText::
	.string "Awww… I lost…$"
J_CooltrainerfFranAfterBattleText::
	.string "Uh-oh… CLAIR is\ngoing to be mad…$"
J_BlackthornGym2FBoulderFellText::
	.string "The boulder fell\nthrough!$"
J_BlackthornGym2F_MapEvents::
