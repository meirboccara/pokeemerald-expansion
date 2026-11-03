@ KJH: translated from pokecrystal maps/RuinsOfAlphInnerChamber.asm by kjh_tools/johto

JohtoRuinsOfAlphInnerChamber_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, JohtoRuinsOfAlphInnerChamber_OnFrame
	.byte 0

JohtoRuinsOfAlphInnerChamber_OnFrame:
	map_script_2 VAR_J_SCENE_RUINS_OF_ALPH_INNER_CHAMBER, 1, J_SC_RuinsOfAlphInnerChamberStrangePresenceScene
	.2byte 0

J_W_RuinsOfAlphInnerChamberFisherScript::
	lock
	call J_RuinsOfAlphInnerChamberFisherScript
	release
	end

J_W_RuinsOfAlphInnerChamberTeacherScript::
	lock
	call J_RuinsOfAlphInnerChamberTeacherScript
	release
	end

J_W_RuinsOfAlphInnerChamberGrampsScript::
	lock
	call J_RuinsOfAlphInnerChamberGrampsScript
	release
	end

J_S_RuinsOfAlphInnerChamberStatue::
	lockall
	call J_RuinsOfAlphInnerChamberStatue
	releaseall
	end

J_SC_RuinsOfAlphInnerChamberStrangePresenceScene::
	lockall
	call J_RuinsOfAlphInnerChamberStrangePresenceScene
	releaseall
	end

J_RuinsOfAlphInnerChamber_MapScripts::
J_RuinsOfAlphInnerChamberNoopScene::
	return
J_RuinsOfAlphInnerChamberStrangePresenceScene::
	call J_RuinsOfAlphInnerChamberStrangePresenceScript
	return
J_RuinsOfAlphInnerChamberStrangePresenceScript::
	message J_RuinsOfAlphStrangePresenceText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_J_SCENE_RUINS_OF_ALPH_INNER_CHAMBER, 0
	setflag FLAG_J_MADE_UNOWN_APPEAR_IN_RUINS
	clearflag FLAG_J_RUINS_OF_ALPH_OUTSIDE_TOURIST_FISHER
	return
J_RuinsOfAlphInnerChamberFisherScript::
	faceplayer
	message J_RuinsOfAlphInnerChamberFisherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphInnerChamberTeacherScript::
	faceplayer
	message J_RuinsOfAlphInnerChamberTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphInnerChamberGrampsScript::
	faceplayer
	message J_RuinsOfAlphInnerChamberGrampsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphInnerChamberStatue::
	message J_RuinsOfAlphInnerChamberStatueText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_RuinsOfAlphStrangePresenceText::
	.string "There is a strange\npresence here…$"
J_RuinsOfAlphInnerChamberFisherText::
	.string "This is a big\nroom, but there's\lnothing here.$"
J_RuinsOfAlphInnerChamberTeacherText::
	.string "This place has a\nmystical quality\lto it.\pIt feels sort of\nethereal even.$"
J_RuinsOfAlphInnerChamberGrampsText::
	.string "Ancient buildings\nare often tombs of\lkings.\pLike the pyramids,\nfor instance.$"
J_RuinsOfAlphInnerChamberStatueText::
	.string "It's a replica of\nan ancient POKé-\lMON.$"
J_RuinsOfAlphInnerChamber_MapEvents::
