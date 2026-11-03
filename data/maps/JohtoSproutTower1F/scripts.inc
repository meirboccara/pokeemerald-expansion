@ KJH: translated from pokecrystal maps/SproutTower1F.asm by kjh_tools/johto

JohtoSproutTower1F_MapScripts::
	.byte 0

J_W_SproutTower1FSage1Script::
	lock
	call J_SproutTower1FSage1Script
	release
	end

J_W_SproutTower1FSage2Script::
	lock
	call J_SproutTower1FSage2Script
	release
	end

J_W_SproutTower1FGrannyScript::
	lock
	call J_SproutTower1FGrannyScript
	release
	end

J_W_SproutTower1FTeacherScript::
	lock
	call J_SproutTower1FTeacherScript
	release
	end

J_T_TrainerSageChow::
	trainerbattle_single TRAINER_J_SAGE_CHOW, J_SageChowSeenText, J_SageChowBeatenText
	call J_TrainerSageChow_Script
	release
	end

J_S_SproutTower1FStatue::
	lockall
	call J_SproutTower1FStatue
	releaseall
	end

J_SproutTower1F_MapScripts::
J_SproutTower1FSage1Script::
	faceplayer
	message J_SproutTower1FSage1Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SproutTower1FSage2Script::
	faceplayer
	message J_SproutTower1FSage2Text
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SproutTower1FGrannyScript::
	faceplayer
	message J_SproutTower1FGrannyText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SproutTower1FTeacherScript::
	faceplayer
	message J_SproutTower1FTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerSageChow::
J_TrainerSageChow_Script:
	message J_SageChowAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SproutTower1FParlyzHeal::
	finditem ITEM_PARALYZE_HEAL, 1
	return
J_SproutTower1FStatue::
	message J_SproutTower1FStatueText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_SageChowSeenText::
	.string "We stand guard in\nthis tower.\pHere, we express\nour gratitude to\lhonor all POKéMON.$"
J_SageChowBeatenText::
	.string "Th-Thank you!$"
J_SageChowAfterBattleText::
	.string "All living beings\ncoexist through\lcooperation.\pWe must always be\nthankful for this.$"
J_SproutTower1FSage1Text::
	.string "Only if you reach\nthe top will you\lobtain an HM.$"
J_SproutTower1FSage2Text::
	.string "SPROUT TOWER was\nbuilt long ago\pas a place for\nPOKéMON training.$"
J_SproutTower1FGrannyText::
	.string "A BELLSPROUT over\n100 feet tall…\pPeople say that it\nbecame the center\lpillar here.$"
J_SproutTower1FTeacherText::
	.string "See the pillar\nshaking?\pPeople are train-\ning upstairs.$"
J_SproutTower1FStatueText::
	.string "A POKéMON statue…\pIt looks very\ndistinguished.$"
J_SproutTower1F_MapEvents::
