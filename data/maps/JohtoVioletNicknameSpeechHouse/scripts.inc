@ KJH: translated from pokecrystal maps/VioletNicknameSpeechHouse.asm by kjh_tools/johto

JohtoVioletNicknameSpeechHouse_MapScripts::
	.byte 0

J_W_VioletNicknameSpeechHouseTeacherScript::
	lock
	call J_VioletNicknameSpeechHouseTeacherScript
	release
	end

J_W_VioletNicknameSpeechHouseLassScript::
	lock
	call J_VioletNicknameSpeechHouseLassScript
	release
	end

J_W_VioletNicknameSpeechHouseBirdScript::
	lock
	call J_VioletNicknameSpeechHouseBirdScript
	release
	end

J_VioletNicknameSpeechHouse_MapScripts::
J_VioletNicknameSpeechHouseTeacherScript::
	faceplayer
	message J_VioletNicknameSpeechHouseTeacherText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletNicknameSpeechHouseLassScript::
	faceplayer
	message J_VioletNicknameSpeechHouseLassText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_VioletNicknameSpeechHouseBirdScript::
	faceplayer
	message J_VioletNicknameSpeechHouseBirdText
	waitmessage
	playmoncry SPECIES_PIDGEY, CRY_MODE_NORMAL
	waitmoncry
	waitbuttonpress
	closemessage
	return
J_VioletNicknameSpeechHouseTeacherText::
	.string "She uses the names\nof her favorite\lthings to eat.\pFor the nicknames\nshe gives to her\lPOKéMON, I mean.$"
J_VioletNicknameSpeechHouseLassText::
	.string "I call my PIDGEY\nSTRAWBERRY!$"
J_VioletNicknameSpeechHouseBirdText::
	.string "STRAWBERRY: Pijji!$"
J_VioletNicknameSpeechHouse_MapEvents::
