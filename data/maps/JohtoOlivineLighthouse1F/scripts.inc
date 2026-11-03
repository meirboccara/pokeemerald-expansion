@ KJH: translated from pokecrystal maps/OlivineLighthouse1F.asm by kjh_tools/johto

JohtoOlivineLighthouse1F_MapScripts::
	.byte 0

J_W_OlivineLighthouse1FSailorScript::
	lock
	call J_OlivineLighthouse1FSailorScript
	release
	end

J_W_OlivineLighthouse1FPokefanFScript::
	lock
	call J_OlivineLighthouse1FPokefanFScript
	release
	end

J_OlivineLighthouse1F_MapScripts::
J_OlivineLighthouse1FSailorScript::
	faceplayer
	message J_OlivineLighthouse1FSailorText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineLighthouse1FPokefanFScript::
	faceplayer
	message J_OlivineLighthouse1FPokefanFText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineLighthouse1FSailorText::
	.string "People train at\nthis LIGHTHOUSE.\pIt's not easy to\nclimb because of\lall the trainers.$"
J_OlivineLighthouse1FPokefanFText::
	.string "In the past, POKé-\nMON used to light\pthe sea around\nOLIVINE at night.\pThe LIGHTHOUSE was\nmade in honor of\lthose POKéMON.$"
J_OlivineLighthouse1F_MapEvents::
