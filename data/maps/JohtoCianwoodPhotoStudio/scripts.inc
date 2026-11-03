@ KJH: translated from pokecrystal maps/CianwoodPhotoStudio.asm by kjh_tools/johto

JohtoCianwoodPhotoStudio_MapScripts::
	.byte 0

J_W_CianwoodPhotoStudioFishingGuruScript::
	lock
	call J_CianwoodPhotoStudioFishingGuruScript
	release
	end

J_CianwoodPhotoStudio_MapScripts::
J_CianwoodPhotoStudioFishingGuruScript::
	faceplayer
	message J_CianwoodPhotoStudioFishingGuruText_Question
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, 0, J_CianwoodPhotoStudioFishingGuruScript_Refused
	message J_CianwoodPhotoStudioFishingGuruText_Yes
	waitmessage
	waitbuttonpress
	setvar VAR_RESULT, 0
	waitbuttonpress
	closemessage
	return
J_CianwoodPhotoStudioFishingGuruScript_Refused:
	message J_CianwoodPhotoStudioFishingGuruText_No
	waitmessage
	waitbuttonpress
	closemessage
	return
J_CianwoodPhotoStudioFishingGuruText_Question::
	.string "You have magnifi-\ncent POKéMON with\lyou.\pHow about a photo\nfor a souvenir?$"
J_CianwoodPhotoStudioFishingGuruText_Yes::
	.string "OK! Big smile now!$"
J_CianwoodPhotoStudioFishingGuruText_No::
	.string "Oh, that's too\nbad. I thought it\pwould be a great\nmemento…$"
J_CianwoodPhotoStudio_MapEvents::
