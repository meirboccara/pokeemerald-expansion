@ KJH: translated from pokecrystal maps/OlivineCafe.asm by kjh_tools/johto

JohtoOlivineCafe_MapScripts::
	.byte 0

J_W_OlivineCafeStrengthSailorScript::
	lock
	call J_OlivineCafeStrengthSailorScript
	release
	end

J_W_OlivineCafeFishingGuruScript::
	lock
	call J_OlivineCafeFishingGuruScript
	release
	end

J_W_OlivineCafeSailorScript::
	lock
	call J_OlivineCafeSailorScript
	release
	end

J_OlivineCafe_MapScripts::
J_OlivineCafeStrengthSailorScript::
	faceplayer
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_GOT_HM04_STRENGTH, J_L7
	setvar VAR_RESULT, 1
J_L7:
	goto_if_ne VAR_RESULT, 0, J_OlivineCafeStrengthSailorScript_GotStrength
	message J_OlivineCafeStrengthSailorText
	waitmessage
	waitbuttonpress
	giveitem ITEM_HM04, 1
	setflag FLAG_J_GOT_HM04_STRENGTH
J_OlivineCafeStrengthSailorScript_GotStrength:
	message J_OlivineCafeStrengthSailorText_GotStrength
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineCafeFishingGuruScript::
	faceplayer
	message J_OlivineCafeFishingGuruText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineCafeSailorScript::
	faceplayer
	message J_OlivineCafeSailorText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_OlivineCafeStrengthSailorText::
	.string "Hah! Your POKéMON\nsure look like\llightweights!\pThey don't have\nthe power to move\lboulders aside.\pHere, use this\nand teach them\lSTRENGTH!$"
J_OlivineCafeStrengthSailorText_GotStrength::
	.string "On the sea, the\nonly thing you can\pcount on is your\nown good self!\pI'm so proud of my\nbuff bod!$"
J_OlivineCafeFishingGuruText::
	.string "OLIVINE CAFE's\nmenu is chock full\pof hearty fare for\nbeefy SAILORS!$"
J_OlivineCafeSailorText::
	.string "Whenever I roll\ninto this town, I\palways visit the\nOLIVINE CAFE.\pEverything on the\nmenu makes me feel\pstronger. I can't\nstop eating!$"
J_OlivineCafe_MapEvents::
