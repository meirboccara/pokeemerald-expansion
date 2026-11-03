@ KJH (ENG-9): stand-ins for the KJH scripts that Johto's maps call and that come with later tickets: the
@ legendaries (ENG-10). Goldenrod's Mega Stone dealer is in kjh_mega.inc (LV-23), the ferry and the story in
@ kjh_ferry.inc and kjh_story.inc (ENG-10). pokefirered's versions are in its
@ data/scripts/kjh_hoenn.inc, kjh_story.inc, kjh_legends.inc and kjh_features.inc.

KJH_EventScript_Legend_RAIKOU::
KJH_EventScript_Legend_ENTEI::
	msgbox KJH_Text_JohtoLegendNotYet, MSGBOX_SIGN
	end

KJH_Text_JohtoLegendNotYet:
	.string "It's watching you closely.$"
