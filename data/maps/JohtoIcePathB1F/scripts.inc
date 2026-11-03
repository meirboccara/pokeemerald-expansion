@ KJH: translated from pokecrystal maps/IcePathB1F.asm by kjh_tools/johto

JohtoIcePathB1F_MapScripts::
	.byte 0

J_W_IcePathB1FBoulder::
	lock
	call J_IcePathB1FBoulder
	release
	end

J_IcePathB1F_MapScripts::
J_IcePathB1FSetUpStoneTableCallback::
	return
J_IcePathB1FSetUpStoneTableCallback_CommandQueue:
J_IcePathB1FSetUpStoneTableCallback_StoneTable:
J_IcePathB1FSetUpStoneTableCallback_Boulder1:
	setflag FLAG_J_BOULDER_IN_ICE_PATH_1
	clearflag FLAG_J_BOULDER_IN_ICE_PATH_1A
	goto J_IcePathB1FSetUpStoneTableCallback_FinishBoulder
J_IcePathB1FSetUpStoneTableCallback_Boulder2:
	setflag FLAG_J_BOULDER_IN_ICE_PATH_2
	clearflag FLAG_J_BOULDER_IN_ICE_PATH_2A
	goto J_IcePathB1FSetUpStoneTableCallback_FinishBoulder
J_IcePathB1FSetUpStoneTableCallback_Boulder3:
	setflag FLAG_J_BOULDER_IN_ICE_PATH_3
	clearflag FLAG_J_BOULDER_IN_ICE_PATH_3A
	goto J_IcePathB1FSetUpStoneTableCallback_FinishBoulder
J_IcePathB1FSetUpStoneTableCallback_Boulder4:
	setflag FLAG_J_BOULDER_IN_ICE_PATH_4
	clearflag FLAG_J_BOULDER_IN_ICE_PATH_4A
	goto J_IcePathB1FSetUpStoneTableCallback_FinishBoulder
J_IcePathB1FSetUpStoneTableCallback_FinishBoulder:
	delay 30
	call J_IcePathB1FSetUpStoneTableCallback_BoulderFallsThrough
	message J_IcePathBoulderFellThroughText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_IcePathB1FSetUpStoneTableCallback_BoulderFallsThrough:
	playse SE_M_STRENGTH
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 4
	special ShakeScreen
	delay 40
	return
J_IcePathB1FBoulder::
	goto EventScript_StrengthBoulder
J_IcePathB1FIron::
	finditem ITEM_IRON, 1
	return
J_IcePathB1FHiddenMaxPotion::
	finditem ITEM_MAX_POTION
	return
J_IcePathBoulderFellThroughText::
	.string "The boulder fell\nthrough.$"
J_IcePathB1F_MapEvents::
