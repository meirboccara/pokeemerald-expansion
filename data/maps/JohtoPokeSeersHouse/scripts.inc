@ KJH: translated from pokecrystal maps/PokeSeersHouse.asm by kjh_tools/johto

JohtoPokeSeersHouse_MapScripts::
	.byte 0

J_W_SeerScript::
	lock
	call J_SeerScript
	release
	end

J_PokeSeersHouse_MapScripts::
J_SeerScript::
	faceplayer
	setvar VAR_RESULT, 0
	waitbuttonpress
	closemessage
	return
J_PokeSeersHouse_MapEvents::
