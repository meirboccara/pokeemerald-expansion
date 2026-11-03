@ KJH: translated from pokecrystal maps/Route29Route46Gate.asm by kjh_tools/johto

JohtoRoute29Route46Gate_MapScripts::
	.byte 0

J_W_Route29Route46GateOfficerScript::
	lock
	call J_Route29Route46GateOfficerScript
	release
	end

J_W_Route29Route46GateYoungsterScript::
	lock
	call J_Route29Route46GateYoungsterScript
	release
	end

J_Route29Route46Gate_MapScripts::
J_Route29Route46GateOfficerScript::
	faceplayer
	message J_Route29Route46GateOfficerText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route29Route46GateYoungsterScript::
	faceplayer
	message J_Route29Route46GateYoungsterText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_Route29Route46GateOfficerText::
	.string "You can't climb\nledges.\pBut you can jump\ndown from them to\ltake a shortcut.$"
J_Route29Route46GateYoungsterText::
	.string "Different kinds of\nPOKéMON appear\lpast here.\pIf you want to\ncatch them all,\pyou have to look\neverywhere.$"
J_Route29Route46Gate_MapEvents::
