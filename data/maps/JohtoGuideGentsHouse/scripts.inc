@ KJH: translated from pokecrystal maps/GuideGentsHouse.asm by kjh_tools/johto

JohtoGuideGentsHouse_MapScripts::
	.byte 0

J_W_GuideGentsHouseGuideGent::
	lock
	call J_GuideGentsHouseGuideGent
	release
	end

J_S_GuideGentsHouseBookshelf::
	lockall
	call J_GuideGentsHouseBookshelf
	releaseall
	end

J_GuideGentsHouse_MapScripts::
J_GuideGentsHouseGuideGent::
	faceplayer
	message J_GuideGentsHouseGuideGentText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_GuideGentsHouseBookshelf::
	goto J_MagazineBookshelfScript
J_GuideGentsHouseGuideGentText::
	.string "When I was a wee\nlad, I was a hot-\lshot trainer!\pHere's a word of\nadvice: Catch lots\lof POKéMON!\pTreat them all\nwith kindness!$"
J_GuideGentsHouse_MapEvents::
