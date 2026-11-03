@ KJH: translated from pokecrystal maps/GoldenrodNameRater.asm by kjh_tools/johto

JohtoGoldenrodNameRater_MapScripts::
	.byte 0

J_W_GoldenrodNameRater::
	lock
	call J_GoldenrodNameRater
	release
	end

J_S_GoldenrodNameRaterBookshelf::
	lockall
	call J_GoldenrodNameRaterBookshelf
	releaseall
	end

J_S_GoldenrodNameRaterRadio::
	lockall
	call J_GoldenrodNameRaterRadio
	releaseall
	end

J_GoldenrodNameRater_MapScripts::
J_GoldenrodNameRater::
	faceplayer
	setvar VAR_RESULT, 0
	waitbuttonpress
	closemessage
	return
J_GoldenrodNameRaterBookshelf::
	goto J_DifficultBookshelfScript
J_GoldenrodNameRaterRadio::
	goto J_Radio2Script
J_GoldenrodNameRater_MapEvents::
