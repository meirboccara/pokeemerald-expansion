@ KJH: translated from pokecrystal maps/OlivineLighthouse5F.asm by kjh_tools/johto

JohtoOlivineLighthouse5F_MapScripts::
	.byte 0

J_T_TrainerSailorErnest::
	trainerbattle_single TRAINER_J_SAILOR_ERNEST, J_SailorErnestSeenText, J_SailorErnestBeatenText
	call J_TrainerSailorErnest_Script
	release
	end

J_T_TrainerBirdKeeperDenis::
	trainerbattle_single TRAINER_J_BIRD_KEEPER_DENIS, J_BirdKeeperDenisSeenText, J_BirdKeeperDenisBeatenText
	call J_TrainerBirdKeeperDenis_Script
	release
	end

J_OlivineLighthouse5F_MapScripts::
J_TrainerBirdKeeperDenis::
J_TrainerBirdKeeperDenis_Script:
	message J_BirdKeeperDenisAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSailorErnest::
J_TrainerSailorErnest_Script:
	message J_SailorErnestAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineLighthouse5FRareCandy::
	finditem ITEM_RARE_CANDY, 1
	return
J_OlivineLighthouse5FSuperRepel::
	finditem ITEM_SUPER_REPEL, 1
	return
J_OlivineLighthouse5FTMSwagger::
	finditem ITEM_RARE_CANDY, 1
	return
J_OlivineLighthouse5FHiddenHyperPotion::
	finditem ITEM_HYPER_POTION
	return
J_SailorErnestSeenText::
	.string "I wanted to battle\nJASMINE, but she's\pnot up to it now.\nSo, how about you?$"
J_SailorErnestBeatenText::
	.string "Whoa, whoa. You're\noverwhelming!$"
J_SailorErnestAfterBattleText::
	.string "A GYM LEADER isn't\njust about being\pstrong. A LEADER\nalso needs to be\lcompassionate.$"
J_BirdKeeperDenisSeenText::
	.string "We're pretty high\nup here. My bird\pPOKéMON are in\nprime form.$"
J_BirdKeeperDenisBeatenText::
	.string "Oops…They crashed…$"
J_BirdKeeperDenisAfterBattleText::
	.string "My POKéMON learned\nhow to use FLY in\lCIANWOOD.\pWell, since I'm a\nloser, I'll FLY\lacross the sea…$"
J_OlivineLighthouse5F_MapEvents::
