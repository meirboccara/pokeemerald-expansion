@ KJH: translated from pokecrystal maps/NationalParkBugContest.asm by kjh_tools/johto

JohtoNationalParkBugContest_MapScripts::
	.byte 0

J_W_BugCatchingContestant1AScript::
	lock
	call J_BugCatchingContestant1AScript
	release
	end

J_W_BugCatchingContestant2AScript::
	lock
	call J_BugCatchingContestant2AScript
	release
	end

J_W_BugCatchingContestant3AScript::
	lock
	call J_BugCatchingContestant3AScript
	release
	end

J_W_BugCatchingContestant4AScript::
	lock
	call J_BugCatchingContestant4AScript
	release
	end

J_W_BugCatchingContestant5AScript::
	lock
	call J_BugCatchingContestant5AScript
	release
	end

J_W_BugCatchingContestant6AScript::
	lock
	call J_BugCatchingContestant6AScript
	release
	end

J_W_BugCatchingContestant7AScript::
	lock
	call J_BugCatchingContestant7AScript
	release
	end

J_W_BugCatchingContestant8AScript::
	lock
	call J_BugCatchingContestant8AScript
	release
	end

J_W_BugCatchingContestant9AScript::
	lock
	call J_BugCatchingContestant9AScript
	release
	end

J_W_BugCatchingContestant10AScript::
	lock
	call J_BugCatchingContestant10AScript
	release
	end

J_S_NationalParkBugContestRelaxationSquareSign::
	lockall
	call J_NationalParkBugContestRelaxationSquareSign
	releaseall
	end

J_S_NationalParkBugContestBattleNoticeSign::
	lockall
	call J_NationalParkBugContestBattleNoticeSign
	releaseall
	end

J_S_NationalParkBugContestTrainerTipsSign::
	lockall
	call J_NationalParkBugContestTrainerTipsSign
	releaseall
	end

J_NationalParkBugContest_MapScripts::
J_BugCatchingContestant1AScript::
	faceplayer
	message J_BugCatchingContestant1AText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant2AScript::
	faceplayer
	message J_BugCatchingContestant2AText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant3AScript::
	faceplayer
	message J_BugCatchingContestant3AText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant4AScript::
	faceplayer
	message J_BugCatchingContestant4AText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant5AScript::
	faceplayer
	message J_BugCatchingContestant5AText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant6AScript::
	faceplayer
	message J_BugCatchingContestant6AText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant7AScript::
	faceplayer
	message J_BugCatchingContestant7AText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant8AScript::
	faceplayer
	message J_BugCatchingContestant8AText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant9AScript::
	faceplayer
	message J_BugCatchingContestant9AText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_BugCatchingContestant10AScript::
	faceplayer
	message J_BugCatchingContestant10AText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NationalParkBugContestRelaxationSquareSign::
	message J_NationalParkBugContestRelaxationSquareText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NationalParkBugContestBattleNoticeSign::
	message J_NationalParkBugContestBattleNoticeText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NationalParkBugContestTrainerTipsSign::
	message J_NationalParkBugContestTrainerTipsText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_NationalParkBugContestParlyzHeal::
	finditem ITEM_PARALYZE_HEAL, 1
	return
J_NationalParkBugContestTMDig::
	finditem ITEM_TM28, 1
	return
J_NationalParkBugContestHiddenFullHeal::
	finditem ITEM_FULL_HEAL
	return
J_BugCatchingContestant1AText::
	.string "DON: I'm going to\nwin! Don't bother\lme.$"
J_BugCatchingContestant2AText::
	.string "ED: My PARASECT\nputs POKéMON to\lsleep with SPORE.$"
J_BugCatchingContestant3AText::
	.string "NICK: I'm raising\nfast POKéMON for\lbattles.$"
J_BugCatchingContestant4AText::
	.string "WILLIAM: I'm not\nconcerned about\lwinning.\pI'm just looking\nfor rare POKéMON.$"
J_BugCatchingContestant5AText::
	.string "BENNY: Ssh! You'll\nscare off SCYTHER.\pI'll talk to you\nlater.$"
J_BugCatchingContestant6AText::
	.string "BARRY: You should\nweaken bug POKéMON\pfirst, then throw\na BALL.$"
J_BugCatchingContestant7AText::
	.string "CINDY: I love bug\nPOKéMON.\pI guess you must\nlike them too.$"
J_BugCatchingContestant8AText::
	.string "JOSH: I've been\ncollecting bug\pPOKéMON since I\nwas just a baby.\pThere's no way I'm\ngoing to lose!$"
J_BugCatchingContestant9AText::
	.string "SAMUEL: If you've\ngot the time to\pchat, go find some\nbug POKéMON.$"
J_BugCatchingContestant10AText::
	.string "KIPP: I've studied\nabout bug POKéMON\la lot.\pI'm going to win\nfor sure.$"
J_NationalParkBugContestRelaxationSquareText::
	.string "RELAXATION SQUARE\nNATIONAL PARK$"
J_NationalParkBugContestBattleNoticeText::
	.string "What is this\nnotice?\pPlease battle only\nin the grass.\pNATIONAL PARK\nWARDEN'S OFFICE$"
J_NationalParkBugContestTrainerTipsText::
	.string "TRAINER TIPS\pPrint out MAIL by\nopening it then\lpressing START.$"
J_NationalParkBugContest_MapEvents::
