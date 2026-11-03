@ KJH: translated from pokecrystal maps/Route35.asm by kjh_tools/johto

JohtoRoute35_MapScripts::
	.byte 0

J_T_TrainerCamperIvan::
	trainerbattle_single TRAINER_J_CAMPER_IVAN, J_CamperIvanSeenText, J_CamperIvanBeatenText
	call J_TrainerCamperIvan_Script
	release
	end

J_T_TrainerCamperElliot::
	trainerbattle_single TRAINER_J_CAMPER_ELLIOT, J_CamperElliotSeenText, J_CamperElliotBeatenText
	call J_TrainerCamperElliot_Script
	release
	end

J_T_TrainerPicnickerBrooke::
	trainerbattle_single TRAINER_J_PICNICKER_BROOKE, J_PicnickerBrookeSeenText, J_PicnickerBrookeBeatenText
	call J_TrainerPicnickerBrooke_Script
	release
	end

J_T_TrainerPicnickerKim::
	trainerbattle_single TRAINER_J_PICNICKER_KIM, J_PicnickerKimSeenText, J_PicnickerKimBeatenText
	call J_TrainerPicnickerKim_Script
	release
	end

J_T_TrainerBirdKeeperBryan::
	trainerbattle_single TRAINER_J_BIRD_KEEPER_BRYAN, J_BirdKeeperBryanSeenText, J_BirdKeeperBryanBeatenText
	call J_TrainerBirdKeeperBryan_Script
	release
	end

J_T_TrainerFirebreatherWalt::
	trainerbattle_single TRAINER_J_FIREBREATHER_WALT, J_FirebreatherWaltSeenText, J_FirebreatherWaltBeatenText
	call J_TrainerFirebreatherWalt_Script
	release
	end

J_T_TrainerBugCatcherArnie::
	trainerbattle_single TRAINER_J_BUG_CATCHER_ARNIE1, J_BugCatcherArnieSeenText, J_BugCatcherArnieBeatenText
	call J_TrainerBugCatcherArnie_Script
	release
	end

J_T_TrainerJugglerIrwin::
	trainerbattle_single TRAINER_J_JUGGLER_IRWIN1, J_JugglerIrwin1SeenText, J_JugglerIrwin1BeatenText
	call J_TrainerJugglerIrwin_Script
	release
	end

J_W_TrainerOfficerDirk::
	lock
	call J_TrainerOfficerDirk
	release
	end

J_W_Route35FruitTree::
	lock
	call J_Route35FruitTree
	release
	end

J_S_Route35Sign::
	lockall
	call J_Route35Sign
	releaseall
	end

J_Route35_MapScripts::
J_TrainerBirdKeeperBryan::
J_TrainerBirdKeeperBryan_Script:
	message J_BirdKeeperBryanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerJugglerIrwin::
J_TrainerJugglerIrwin_Script:
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_Route35NumberAcceptedM
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_IRWIN_ASKED_FOR_PHONE_NUMBER, J_L422
	setvar VAR_RESULT, 1
J_L422:
	goto_if_ne VAR_RESULT, 0, J_TrainerJugglerIrwin_AskedAlready
	message J_JugglerIrwinAfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_IRWIN_ASKED_FOR_PHONE_NUMBER
	call J_Route35AskNumber1M
	goto J_TrainerJugglerIrwin_AskForNumber
J_TrainerJugglerIrwin_AskedAlready:
	call J_Route35AskNumber2M
J_TrainerJugglerIrwin_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_Route35PhoneFullM
	goto_if_eq VAR_RESULT, 2, J_Route35NumberDeclinedM
	bufferstring STR_VAR_1, J_TrainerName_JUGGLER_IRWIN1
	call J_Route35RegisteredNumberM
	goto J_Route35NumberAcceptedM
J_Route35AskNumber1M::
	goto J_Std_Nop
	return
J_Route35AskNumber2M::
	goto J_Std_Nop
	return
J_Route35RegisteredNumberM::
	goto J_Std_Nop
	return
J_Route35NumberAcceptedM::
	goto J_Std_Nop
	return
J_Route35NumberDeclinedM::
	goto J_Std_Nop
	return
J_Route35PhoneFullM::
	goto J_Std_Nop
	return
J_Route35RematchM::
	goto J_Std_Nop
	return
J_TrainerCamperIvan::
J_TrainerCamperIvan_Script:
	message J_CamperIvanAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerCamperElliot::
J_TrainerCamperElliot_Script:
	message J_CamperElliotAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPicnickerBrooke::
J_TrainerPicnickerBrooke_Script:
	message J_PicnickerBrookeAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerPicnickerKim::
J_TrainerPicnickerKim_Script:
	message J_PicnickerKimAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerBugCatcherArnie::
J_TrainerBugCatcherArnie_Script:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_ARNIE_READY_FOR_REMATCH, J_L423
	setvar VAR_RESULT, 1
J_L423:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherArnie_WantsBattle
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_YANMA_SWARM, J_L424
	setvar VAR_RESULT, 1
J_L424:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherArnie_YanmaSwarming
	setvar VAR_RESULT, 0
	goto_if_ne VAR_RESULT, 0, J_Route35NumberAcceptedM
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ARNIE_ASKED_FOR_PHONE_NUMBER, J_L425
	setvar VAR_RESULT, 1
J_L425:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherArnie_AskedAlready
	message J_BugCatcherArnieAfterBattleText
	waitmessage
	waitbuttonpress
	setflag FLAG_J_ARNIE_ASKED_FOR_PHONE_NUMBER
	call J_Route35AskNumber1M
	goto J_TrainerBugCatcherArnie_AskForNumber
J_TrainerBugCatcherArnie_AskedAlready:
	call J_Route35AskNumber2M
J_TrainerBugCatcherArnie_AskForNumber:
	setvar VAR_RESULT, 2
	goto_if_eq VAR_RESULT, 1, J_Route35PhoneFullM
	goto_if_eq VAR_RESULT, 2, J_Route35NumberDeclinedM
	bufferstring STR_VAR_1, J_TrainerName_BUG_CATCHER_ARNIE1
	call J_Route35RegisteredNumberM
	goto J_Route35NumberAcceptedM
J_TrainerBugCatcherArnie_WantsBattle:
	call J_Route35RematchM
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 4, J_TrainerBugCatcherArnie_Fight4
	goto_if_eq VAR_RESULT, 3, J_TrainerBugCatcherArnie_Fight3
	goto_if_eq VAR_RESULT, 2, J_TrainerBugCatcherArnie_Fight2
	goto_if_eq VAR_RESULT, 1, J_TrainerBugCatcherArnie_Fight1
	goto_if_eq VAR_RESULT, 0, J_TrainerBugCatcherArnie_LoadFight0
J_TrainerBugCatcherArnie_Fight4:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_RESTORED_POWER_TO_KANTO, J_L426
	setvar VAR_RESULT, 1
J_L426:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherArnie_LoadFight4
J_TrainerBugCatcherArnie_Fight3:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_JOHTO_BADGE08_GET, J_L427
	setvar VAR_RESULT, 1
J_L427:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherArnie_LoadFight3
J_TrainerBugCatcherArnie_Fight2:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_BLACKTHORN, J_L428
	setvar VAR_RESULT, 1
J_L428:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherArnie_LoadFight2
J_TrainerBugCatcherArnie_Fight1:
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_ENGINE_FLYPOINT_LAKE_OF_RAGE, J_L429
	setvar VAR_RESULT, 1
J_L429:
	goto_if_ne VAR_RESULT, 0, J_TrainerBugCatcherArnie_LoadFight1
J_TrainerBugCatcherArnie_LoadFight0:
	trainerbattle_no_intro TRAINER_J_BUG_CATCHER_ARNIE1, J_BugCatcherArnieBeatenText
	clearflag FLAG_J_ENGINE_ARNIE_READY_FOR_REMATCH
	return
J_TrainerBugCatcherArnie_LoadFight1:
	trainerbattle_no_intro TRAINER_J_BUG_CATCHER_ARNIE2, J_Text_Empty
	clearflag FLAG_J_ENGINE_ARNIE_READY_FOR_REMATCH
	return
J_TrainerBugCatcherArnie_LoadFight2:
	trainerbattle_no_intro TRAINER_J_BUG_CATCHER_ARNIE3, J_Text_Empty
	clearflag FLAG_J_ENGINE_ARNIE_READY_FOR_REMATCH
	return
J_TrainerBugCatcherArnie_LoadFight3:
	trainerbattle_no_intro TRAINER_J_BUG_CATCHER_ARNIE4, J_Text_Empty
	clearflag FLAG_J_ENGINE_ARNIE_READY_FOR_REMATCH
	return
J_TrainerBugCatcherArnie_LoadFight4:
	trainerbattle_no_intro TRAINER_J_BUG_CATCHER_ARNIE5, J_Text_Empty
	clearflag FLAG_J_ENGINE_ARNIE_READY_FOR_REMATCH
	return
J_TrainerBugCatcherArnie_YanmaSwarming:
	message J_BugCatcherArnieYanmaText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerFirebreatherWalt::
J_TrainerFirebreatherWalt_Script:
	message J_FirebreatherWaltAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerOfficerDirk::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_eq VAR_RESULT, 0, J_TrainerOfficerDirk_NotNight
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_BEAT_OFFICER_DIRK, J_L430
	setvar VAR_RESULT, 1
J_L430:
	goto_if_ne VAR_RESULT, 0, J_TrainerOfficerDirk_AfterBattle
	playbgm MUS_RG_ENCOUNTER_BOY, FALSE
	message J_OfficerDirkSeenText
	waitmessage
	waitbuttonpress
	closemessage
	trainerbattle_no_intro TRAINER_J_OFFICER_DIRK, J_OfficerDirkBeatenText
	setflag FLAG_J_BEAT_OFFICER_DIRK
	closemessage
	return
J_TrainerOfficerDirk_AfterBattle:
	message J_OfficerDirkAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerOfficerDirk_NotNight:
	message J_OfficerDirkPrettyToughText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route35Sign::
	message J_Route35SignText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route35TMRollout::
	finditem ITEM_RARE_CANDY, 1
	return
J_Route35FruitTree::
	msgbox J_Text_FruitTree, MSGBOX_SIGN
	return
J_CamperIvanSeenText::
	.string "I've been getting\nPOKéMON data off\pmy radio. I think\nI'm good.$"
J_CamperIvanBeatenText::
	.string "I give!$"
J_CamperIvanAfterBattleText::
	.string "Music on the radio\nchanges the moods\lof wild POKéMON.$"
J_CamperElliotSeenText::
	.string "I'm gonna show my\ngirlfriend I'm hot\lstuff!$"
J_CamperElliotBeatenText::
	.string "I wish you would\nhave lost for me…$"
J_CamperElliotAfterBattleText::
	.string "I was humiliated\nin front of my\lgirlfriend…$"
J_PicnickerBrookeSeenText::
	.string "My boyfriend's\nweak, so I can't\lrely on him.$"
J_PicnickerBrookeBeatenText::
	.string "Oh, my! You're so\nstrong!$"
J_PicnickerBrookeAfterBattleText::
	.string "I can count on my\nPOKéMON more than\lmy boyfriend.$"
J_PicnickerKimSeenText::
	.string "Are you going to\nthe GYM? Me too!$"
J_PicnickerKimBeatenText::
	.string "Oh. I couldn't\nwin…$"
J_PicnickerKimAfterBattleText::
	.string "The GYM BADGES are\npretty. I collect\lthem.$"
J_BirdKeeperBryanSeenText::
	.string "What kinds of\nBALLS do you use?$"
J_BirdKeeperBryanBeatenText::
	.string "Yikes! Not fast\nenough!$"
J_BirdKeeperBryanAfterBattleText::
	.string "Some POKéMON flee\nright away.\pTry catching them\nwith KURT's FAST\lBALL.\pWhenever I find a\nWHT APRICORN, I\ltake it to KURT.\pHe turns it into a\ncustom BALL.$"
J_JugglerIrwin1SeenText::
	.string "Behold my graceful\nBALL dexterity!$"
J_JugglerIrwin1BeatenText::
	.string "Whew! That was a\njolt!$"
J_JugglerIrwinAfterBattleText::
	.string "I was going to\ndazzle you with my\lprize POKéMON.\pBut your prowess\nelectrified me!$"
J_BugCatcherArnieSeenText::
	.string "I'll go anywhere\nif bug POKéMON\lappear there.$"
J_BugCatcherArnieBeatenText::
	.string "Huh? I shouldn't\nhave lost that…$"
J_BugCatcherArnieAfterBattleText::
	.string "My VENONAT won me\nthe Bug-Catching\pContest at the\nNATIONAL PARK.$"
J_BugCatcherArnieYanmaText::
	.string "Wow… Look at all\nthose YANMA!\pI'm so blown away,\nI can't move.$"
J_FirebreatherWaltSeenText::
	.string "I'm practicing my\nfire breathing.$"
J_FirebreatherWaltBeatenText::
	.string "Ow! I scorched the\ntip of my nose!$"
J_FirebreatherWaltAfterBattleText::
	.string "The POKéMON March\non the radio lures\lwild POKéMON.$"
J_OfficerDirkSeenText::
	.string "Danger lurks in\nthe night!$"
J_OfficerDirkBeatenText::
	.string "Whoops!$"
J_OfficerDirkAfterBattleText::
	.string "You know, night-\ntime is fun in its\lown ways.\pBut don't overdo\nit, OK?$"
J_OfficerDirkPrettyToughText::
	.string "Your POKéMON look\npretty tough.\pYou could go any-\nwhere safely.$"
J_Route35SignText::
	.string "ROUTE 35$"
J_Route35_MapEvents::
