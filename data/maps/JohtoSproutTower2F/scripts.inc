@ KJH: translated from pokecrystal maps/SproutTower2F.asm by kjh_tools/johto

JohtoSproutTower2F_MapScripts::
	.byte 0

J_T_TrainerSageNico::
	trainerbattle_single TRAINER_J_SAGE_NICO, J_SageNicoSeenText, J_SageNicoBeatenText
	call J_TrainerSageNico_Script
	release
	end

J_T_TrainerSageEdmond::
	trainerbattle_single TRAINER_J_SAGE_EDMOND, J_SageEdmondSeenText, J_SageEdmondBeatenText
	call J_TrainerSageEdmond_Script
	release
	end

J_S_SproutTower2FStatue::
	lockall
	call J_SproutTower2FStatue
	releaseall
	end

J_SproutTower2F_MapScripts::
J_TrainerSageNico::
J_TrainerSageNico_Script:
	message J_SageNicoAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSageEdmond::
J_TrainerSageEdmond_Script:
	message J_SageEdmondAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SproutTower2FStatue::
	message J_SproutTower2FStatueText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SproutTower2FXAccuracy::
	finditem ITEM_X_ACCURACY, 1
	return
J_SageNicoSeenText::
	.string "However hard we\nbattle, the TOWER\lwill stand strong.$"
J_SageNicoBeatenText::
	.string "I fought hard but\nI'm too weak.$"
J_SageNicoAfterBattleText::
	.string "The flexible pil-\nlar protects the\pTOWER, even from\nearthquakes.$"
J_SageEdmondSeenText::
	.string "…Sway like leaves\nin the wind…$"
J_SageEdmondBeatenText::
	.string "Oh, I'm weak!$"
J_SageEdmondAfterBattleText::
	.string "I tried to copy\nBELLSPROUT's\pgentle movements\nfor battle…\pBut I didn't train\nwell enough.$"
J_SproutTower2FStatueText::
	.string "A POKéMON statue…\pIt looks very\ndistinguished.$"
J_SproutTower2F_MapEvents::
