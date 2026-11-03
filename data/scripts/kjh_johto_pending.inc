@ KJH (ENG-9): stand-ins for the KJH scripts that Johto's maps call and that come with later tickets: the story and
@ the legendaries (ENG-10), the Mega Stone shops (LV-21). The ferry is in kjh_ferry.inc (ENG-10). pokefirered's versions are in its
@ data/scripts/kjh_hoenn.inc, kjh_story.inc, kjh_legends.inc and kjh_features.inc.

KJH_EventScript_Story_OlivineAdmins::
	msgbox KJH_Text_JohtoOlivineAdminsNotYet, MSGBOX_NPC
	end

KJH_EventScript_MegaStoneDealerJohto::
	msgbox KJH_Text_JohtoMegaStoneDealerNotYet, MSGBOX_NPC
	end

KJH_EventScript_Legend_RAIKOU::
KJH_EventScript_Legend_ENTEI::
	msgbox KJH_Text_JohtoLegendNotYet, MSGBOX_SIGN
	end

KJH_Text_JohtoOlivineAdminsNotYet:
	.string "…$"

KJH_Text_JohtoMegaStoneDealerNotYet:
	.string "Come back later!$"

KJH_Text_JohtoLegendNotYet:
	.string "It's watching you closely.$"
