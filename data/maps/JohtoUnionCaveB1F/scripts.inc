@ KJH: translated from pokecrystal maps/UnionCaveB1F.asm by kjh_tools/johto

JohtoUnionCaveB1F_MapScripts::
	.byte 0

J_T_TrainerHikerPhillip::
	trainerbattle_single TRAINER_J_HIKER_PHILLIP, J_HikerPhillipSeenText, J_HikerPhillipBeatenText
	call J_TrainerHikerPhillip_Script
	release
	end

J_T_TrainerHikerLeonard::
	trainerbattle_single TRAINER_J_HIKER_LEONARD, J_HikerLeonardSeenText, J_HikerLeonardBeatenText
	call J_TrainerHikerLeonard_Script
	release
	end

J_T_TrainerPokemaniacAndrew::
	trainerbattle_single TRAINER_J_POKEMANIAC_ANDREW, J_PokemaniacAndrewSeenText, J_PokemaniacAndrewBeatenText
	call J_TrainerPokemaniacAndrew_Script
	release
	end

J_T_TrainerPokemaniacCalvin::
	trainerbattle_single TRAINER_J_POKEMANIAC_CALVIN, J_PokemaniacCalvinSeenText, J_PokemaniacCalvinBeatenText
	call J_TrainerPokemaniacCalvin_Script
	release
	end

J_W_UnionCaveB1FBoulder::
	lock
	call J_UnionCaveB1FBoulder
	release
	end

J_UnionCaveB1F_MapScripts::
J_TrainerPokemaniacAndrew::
J_TrainerPokemaniacAndrew_Script:
	message J_PokemaniacAndrewAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPokemaniacCalvin::
J_TrainerPokemaniacCalvin_Script:
	message J_PokemaniacCalvinAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerHikerPhillip::
J_TrainerHikerPhillip_Script:
	message J_HikerPhillipAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerHikerLeonard::
J_TrainerHikerLeonard_Script:
	message J_HikerLeonardAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_UnionCaveB1FTMSwift::
	finditem ITEM_RARE_CANDY, 1
	return
J_UnionCaveB1FXDefend::
	finditem ITEM_X_DEFEND, 1
	return
J_UnionCaveB1FBoulder::
	goto EventScript_StrengthBoulder
J_HikerPhillipSeenText::
	.string "It's been a while\nsince I last saw\lanother person.\pDon't be shy.\nLet's battle!$"
J_HikerPhillipBeatenText::
	.string "Uurggh…$"
J_HikerPhillipAfterBattleText::
	.string "I've been lost for\na long time…\pI don't mind it\nhere, but I am\lsoooo hungry!$"
J_HikerLeonardSeenText::
	.string "What do you know!\nA visitor!$"
J_HikerLeonardBeatenText::
	.string "Wahahah! You're a\nfeisty one!$"
J_HikerLeonardAfterBattleText::
	.string "I live down here.\pYou can, too, if\nyou'd like.\pThere's plenty of\nroom, you see.$"
J_PokemaniacAndrewSeenText::
	.string "Who's there?\pLeave me and my\nPOKéMON alone!$"
J_PokemaniacAndrewBeatenText::
	.string "Go…\nGo away!$"
J_PokemaniacAndrewAfterBattleText::
	.string "Just me and my\nPOKéMON. I'm de-\llirious with joy.$"
J_PokemaniacCalvinSeenText::
	.string "I came all the way\nhere to conduct my\lPOKéMON research.\pLet me demonstrate\nmy findings in a\lreal battle!$"
J_PokemaniacCalvinBeatenText::
	.string "You demonstrated\non me!$"
J_PokemaniacCalvinAfterBattleText::
	.string "I should compile\nand announce my\lstudy findings.\pI might even be-\ncome famous like\lPROF.ELM.$"
J_UnionCaveB1F_MapEvents::
