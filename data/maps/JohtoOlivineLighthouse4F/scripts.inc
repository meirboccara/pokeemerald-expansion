@ KJH: translated from pokecrystal maps/OlivineLighthouse4F.asm by kjh_tools/johto

JohtoOlivineLighthouse4F_MapScripts::
	.byte 0

J_T_TrainerSailorKent::
	trainerbattle_single TRAINER_J_SAILOR_KENT, J_SailorKentSeenText, J_SailorKentBeatenText
	call J_TrainerSailorKent_Script
	release
	end

J_T_TrainerLassConnie::
	trainerbattle_single TRAINER_J_LASS_CONNIE1, J_LassConnie1SeenText, J_LassConnie1BeatenText
	call J_TrainerLassConnie_Script
	release
	end

J_OlivineLighthouse4F_MapScripts::
J_TrainerLassConnie::
J_TrainerLassConnie_Script:
	message J_LassConnie1AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSailorKent::
J_TrainerSailorKent_Script:
	message J_SailorKentAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SailorKentSeenText::
	.string "JASMINE must be\nworried sick about\lthe POKéMON here.\pShe won't even\nsmile these days.$"
J_SailorKentBeatenText::
	.string "I can't manage a\nsmile either…$"
J_SailorKentAfterBattleText::
	.string "Speaking of sick,\nI've heard there's\pa good PHARMACY in\nCIANWOOD.$"
J_LassConnie1SeenText::
	.string "JASMINE is this\ncity's GYM LEADER.\pI mean to bring\nher back with me.\pNobody had better\nget in my way!$"
J_LassConnie1BeatenText::
	.string "Aaack! My POKéMON!$"
J_LassConnie1AfterBattleText::
	.string "Right. Anybody\nwould be worried\lif his or her own\lPOKéMON were hurt.\pI'll pray for the\nPOKéMON here, so\pJASMINE can come\nback to the GYM.$"
J_OlivineLighthouse4F_MapEvents::
