@ KJH: translated from pokecrystal maps/OlivineLighthouse3F.asm by kjh_tools/johto

JohtoOlivineLighthouse3F_MapScripts::
	.byte 0

J_T_TrainerSailorTerrell::
	trainerbattle_single TRAINER_J_SAILOR_TERRELL, J_SailorTerrellSeenText, J_SailorTerrellBeatenText
	call J_TrainerSailorTerrell_Script
	release
	end

J_T_TrainerGentlemanPreston::
	trainerbattle_single TRAINER_J_GENTLEMAN_PRESTON, J_GentlemanPrestonSeenText, J_GentlemanPrestonBeatenText
	call J_TrainerGentlemanPreston_Script
	release
	end

J_T_TrainerBirdKeeperTheo::
	trainerbattle_single TRAINER_J_BIRD_KEEPER_THEO, J_BirdKeeperTheoSeenText, J_BirdKeeperTheoBeatenText
	call J_TrainerBirdKeeperTheo_Script
	release
	end

J_OlivineLighthouse3F_MapScripts::
J_TrainerBirdKeeperTheo::
J_TrainerBirdKeeperTheo_Script:
	message J_BirdKeeperTheoAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGentlemanPreston::
J_TrainerGentlemanPreston_Script:
	message J_GentlemanPrestonAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSailorTerrell::
J_TrainerSailorTerrell_Script:
	message J_SailorTerrellAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineLighthouse3FEther::
	finditem ITEM_ETHER, 1
	return
J_BirdKeeperTheoSeenText::
	.string "Why are you here?\nAre you just going\pto gawk? I suggest\nthat you leave!$"
J_BirdKeeperTheoBeatenText::
	.string "You really are\nconcerned…$"
J_BirdKeeperTheoAfterBattleText::
	.string "How the heck do\nyou go up?\pI want to visit\nthe sick POKéMON,\pbut I can't get up\nthere…$"
J_SailorTerrellSeenText::
	.string "Sailors are both\nkind and strong.\lHow about you?$"
J_SailorTerrellBeatenText::
	.string "You are both kind\nand strong…$"
J_SailorTerrellAfterBattleText::
	.string "Every time I come\nback to OLIVINE, I\lvisit the GYM.\pThe GYM LEADER's\nPOKéMON type has\pchanged without me\nnoticing.$"
J_GentlemanPrestonSeenText::
	.string "I travel the world\nto train my POKé-\lMON. I wish to\lbattle with you.$"
J_GentlemanPrestonBeatenText::
	.string "…sigh… I must\ntrain some more…$"
J_GentlemanPrestonAfterBattleText::
	.string "JASMINE used to\nuse rock POKéMON\llike ONIX.$"
J_OlivineLighthouse3F_MapEvents::
