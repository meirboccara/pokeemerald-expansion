@ KJH (LV-17): fair fights. Called by each Gym Leader's script right before trainerbattle, with VAR_0x8004 = the
@ Leader (src/kjh_fair_fight.c). With more healthy Pokemon than the Leader has, the player picks that many; the rest
@ wait and come back once the battle is over. Cancelling the choice cancels the battle.
EventScript_KjhFairFight::
	specialvar VAR_0x8005, KJH_FairFightCount
	goto_if_eq VAR_0x8005, 0, EventScript_KjhFairFightEnd
	lock
	faceplayer
	msgbox Text_KjhFairFightChoose
	closemessage
	special KJH_ChooseFairFightParty
	waitstate
	goto_if_eq VAR_RESULT, FALSE, EventScript_KjhFairFightCancelled
	special KJH_ApplyFairFightParty
EventScript_KjhFairFightEnd::
	return

EventScript_KjhFairFightCancelled::
	release
	end

Text_KjhFairFightChoose::
	.string "{STR_VAR_1} uses {STR_VAR_2} POKéMON.\n"
	.string "Choose {STR_VAR_2}.$"
