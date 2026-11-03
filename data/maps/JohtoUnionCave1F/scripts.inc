@ KJH: translated from pokecrystal maps/UnionCave1F.asm by kjh_tools/johto

JohtoUnionCave1F_MapScripts::
	.byte 0

J_T_TrainerHikerDaniel::
	trainerbattle_single TRAINER_J_HIKER_DANIEL, J_HikerDanielSeenText, J_HikerDanielBeatenText
	call J_TrainerHikerDaniel_Script
	release
	end

J_T_TrainerPokemaniacLarry::
	trainerbattle_single TRAINER_J_POKEMANIAC_LARRY, J_PokemaniacLarrySeenText, J_PokemaniacLarryBeatenText
	call J_TrainerPokemaniacLarry_Script
	release
	end

J_T_TrainerHikerRussell::
	trainerbattle_single TRAINER_J_HIKER_RUSSELL, J_HikerRussellSeenText, J_HikerRussellBeatenText
	call J_TrainerHikerRussell_Script
	release
	end

J_T_TrainerFirebreatherRay::
	trainerbattle_single TRAINER_J_FIREBREATHER_RAY, J_FirebreatherRaySeenText, J_FirebreatherRayBeatenText
	call J_TrainerFirebreatherRay_Script
	release
	end

J_T_TrainerFirebreatherBill::
	trainerbattle_single TRAINER_J_FIREBREATHER_BILL, J_FirebreatherBillSeenText, J_FirebreatherBillBeatenText
	call J_TrainerFirebreatherBill_Script
	release
	end

J_UnionCave1F_MapScripts::
J_TrainerPokemaniacLarry::
J_TrainerPokemaniacLarry_Script:
	message J_PokemaniacLarryAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerHikerRussell::
J_TrainerHikerRussell_Script:
	message J_HikerRussellAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerHikerDaniel::
J_TrainerHikerDaniel_Script:
	message J_HikerDanielAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerFirebreatherBill::
J_TrainerFirebreatherBill_Script:
	message J_FirebreatherBillAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerFirebreatherRay::
J_TrainerFirebreatherRay_Script:
	message J_FirebreatherRayAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_UnionCave1FGreatBall::
	finditem ITEM_GREAT_BALL, 1
	return
J_UnionCave1FXAttack::
	finditem ITEM_X_ATTACK, 1
	return
J_UnionCave1FPotion::
	finditem ITEM_POTION, 1
	return
J_UnionCave1FAwakening::
	finditem ITEM_AWAKENING, 1
	return
J_UnionCave1FUnusedSign::
	message J_UnionCave1FUnusedSignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_HikerRussellSeenText::
	.string "You're headed to\nAZALEA, are you?\pLet my POKéMON see\nif you are good\lenough to battle.$"
J_HikerRussellBeatenText::
	.string "Oh, oh, oh!$"
J_HikerRussellAfterBattleText::
	.string "All right, then!\nI've decided.\pI'm not leaving\nuntil my POKéMON\lget tougher!$"
J_PokemaniacLarrySeenText::
	.string "I roam far and\nwide in search of\lPOKéMON.\pAre you looking\nfor POKéMON too?\pThen you're my\ncollecting rival!$"
J_PokemaniacLarryBeatenText::
	.string "Ugh. My poor POKé-\nMON…$"
J_PokemaniacLarryAfterBattleText::
	.string "Every Friday, you\ncan hear POKéMON\proars from deep\ninside the cave.$"
J_HikerDanielSeenText::
	.string "Whoa! What a\nsurprise!\pI didn't expect to\nsee anyone here!$"
J_HikerDanielBeatenText::
	.string "Whoa! I'm beaten\nbig time!$"
J_HikerDanielAfterBattleText::
	.string "I was conned into\nbuying a SLOWPOKE-\lTAIL.\pI feel sorry for\nthe poor POKéMON.$"
J_FirebreatherBillSeenText::
	.string "ZUBAT's SUPERSONIC\nkeeps confusing\lmy POKéMON.\pI'm seriously\nupset about that!$"
J_FirebreatherBillBeatenText::
	.string "I flamed out!$"
J_FirebreatherBillAfterBattleText::
	.string "On weekends, you\ncan hear strange\proars from deep in\nthe cave.$"
J_FirebreatherRaySeenText::
	.string "If it's light, a\ncave isn't scary.\pIf you're strong,\nPOKéMON aren't\lscary.$"
J_FirebreatherRayBeatenText::
	.string "FLASH!$"
J_FirebreatherRayAfterBattleText::
	.string "It's my POKéMON's\nfire that lights\lup this cave.$"
J_UnionCave1FUnusedSignText::
	.string "UNION CAVE$"
J_UnionCave1F_MapEvents::
