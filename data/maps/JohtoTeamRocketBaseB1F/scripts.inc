@ KJH: translated from pokecrystal maps/TeamRocketBaseB1F.asm by kjh_tools/johto

JohtoTeamRocketBaseB1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, JohtoTeamRocketBaseB1F_OnTransition
	.byte 0

JohtoTeamRocketBaseB1F_OnTransition:
	call J_TeamRocketBaseB1FHideSecurityGruntCallback
	end

J_T_TrainerGruntM16::
	trainerbattle_single TRAINER_J_GRUNTM_GRUNTM_16, J_GruntM16SeenText, J_GruntM16BeatenText
	call J_TrainerGruntM16_Script
	release
	end

J_T_TrainerScientistJed::
	trainerbattle_single TRAINER_J_SCIENTIST_JED, J_ScientistJedSeenText, J_ScientistJedBeatenText
	call J_TrainerScientistJed_Script
	release
	end

J_C_SecurityCamera1a::
	lockall
	call J_SecurityCamera1a
	releaseall
	end

J_C_SecurityCamera1b::
	lockall
	call J_SecurityCamera1b
	releaseall
	end

J_C_SecurityCamera2a::
	lockall
	call J_SecurityCamera2a
	releaseall
	end

J_C_SecurityCamera2b::
	lockall
	call J_SecurityCamera2b
	releaseall
	end

J_C_SecurityCamera3a::
	lockall
	call J_SecurityCamera3a
	releaseall
	end

J_C_SecurityCamera3b::
	lockall
	call J_SecurityCamera3b
	releaseall
	end

J_C_SecurityCamera4::
	lockall
	call J_SecurityCamera4
	releaseall
	end

J_C_SecurityCamera5::
	lockall
	call J_SecurityCamera5
	releaseall
	end

J_C_ExplodingTrap1::
	lockall
	call J_ExplodingTrap1
	releaseall
	end

J_C_ExplodingTrap2::
	lockall
	call J_ExplodingTrap2
	releaseall
	end

J_C_ExplodingTrap3::
	lockall
	call J_ExplodingTrap3
	releaseall
	end

J_C_ExplodingTrap4::
	lockall
	call J_ExplodingTrap4
	releaseall
	end

J_C_ExplodingTrap5::
	lockall
	call J_ExplodingTrap5
	releaseall
	end

J_C_ExplodingTrap6::
	lockall
	call J_ExplodingTrap6
	releaseall
	end

J_C_ExplodingTrap7::
	lockall
	call J_ExplodingTrap7
	releaseall
	end

J_C_ExplodingTrap8::
	lockall
	call J_ExplodingTrap8
	releaseall
	end

J_C_ExplodingTrap9::
	lockall
	call J_ExplodingTrap9
	releaseall
	end

J_C_ExplodingTrap10::
	lockall
	call J_ExplodingTrap10
	releaseall
	end

J_C_ExplodingTrap11::
	lockall
	call J_ExplodingTrap11
	releaseall
	end

J_C_ExplodingTrap12::
	lockall
	call J_ExplodingTrap12
	releaseall
	end

J_C_ExplodingTrap13::
	lockall
	call J_ExplodingTrap13
	releaseall
	end

J_C_ExplodingTrap14::
	lockall
	call J_ExplodingTrap14
	releaseall
	end

J_C_ExplodingTrap15::
	lockall
	call J_ExplodingTrap15
	releaseall
	end

J_C_ExplodingTrap16::
	lockall
	call J_ExplodingTrap16
	releaseall
	end

J_C_ExplodingTrap17::
	lockall
	call J_ExplodingTrap17
	releaseall
	end

J_C_ExplodingTrap18::
	lockall
	call J_ExplodingTrap18
	releaseall
	end

J_C_ExplodingTrap19::
	lockall
	call J_ExplodingTrap19
	releaseall
	end

J_C_ExplodingTrap20::
	lockall
	call J_ExplodingTrap20
	releaseall
	end

J_C_ExplodingTrap21::
	lockall
	call J_ExplodingTrap21
	releaseall
	end

J_C_ExplodingTrap22::
	lockall
	call J_ExplodingTrap22
	releaseall
	end

J_S_TeamRocketBaseB1FSecretSwitch::
	lockall
	call J_TeamRocketBaseB1FSecretSwitch
	releaseall
	end

J_S_TeamRocketBaseB1FSecurityCamera::
	lockall
	call J_TeamRocketBaseB1FSecurityCamera
	releaseall
	end

J_S_TeamRocketBaseB1FBookshelf::
	lockall
	call J_TeamRocketBaseB1FBookshelf
	releaseall
	end

J_TeamRocketBaseB1F_MapScripts::
J_TeamRocketBaseB1FNoopScene::
	return
J_TeamRocketBaseB1FHideSecurityGruntCallback::
	setflag FLAG_J_TEAM_ROCKET_BASE_SECURITY_GRUNTS
	return
J_SecurityCamera1a::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SECURITY_CAMERA_1, J_L153
	setvar VAR_RESULT, 1
J_L153:
	goto_if_ne VAR_RESULT, 0, J_NoSecurityCamera
	call J_PlaySecurityCameraSounds
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_POPULATION, J_L154
	setvar VAR_RESULT, 1
J_L154:
	goto_if_ne VAR_RESULT, 0, J_NoSecurityCamera
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	setobjectxyperm 1, 19, 2
	addobject 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement 1, J_SecurityCameraMovement1
	waitmovement 1
	call J_TrainerCameraGrunt1
	goto_if_eq VAR_RESULT, 1, J_NoSecurityCamera
	call J_PlaySecurityCameraSounds
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	setobjectxyperm 1, 19, 2
	addobject 1
	applymovement 1, J_SecurityCameraMovement1
	waitmovement 1
	call J_TrainerCameraGrunt2
	goto_if_eq VAR_RESULT, 1, J_NoSecurityCamera
	setflag FLAG_J_SECURITY_CAMERA_1
	return
J_SecurityCamera1b::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SECURITY_CAMERA_1, J_L155
	setvar VAR_RESULT, 1
J_L155:
	goto_if_ne VAR_RESULT, 0, J_NoSecurityCamera
	call J_PlaySecurityCameraSounds
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_POPULATION, J_L156
	setvar VAR_RESULT, 1
J_L156:
	goto_if_ne VAR_RESULT, 0, J_NoSecurityCamera
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	setobjectxyperm 1, 19, 3
	addobject 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement 1, J_SecurityCameraMovement1
	waitmovement 1
	call J_TrainerCameraGrunt1
	goto_if_eq VAR_RESULT, 1, J_NoSecurityCamera
	call J_PlaySecurityCameraSounds
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	setobjectxyperm 1, 19, 3
	addobject 1
	applymovement 1, J_SecurityCameraMovement1
	waitmovement 1
	call J_TrainerCameraGrunt2
	goto_if_eq VAR_RESULT, 1, J_NoSecurityCamera
	setflag FLAG_J_SECURITY_CAMERA_1
	return
J_SecurityCamera2a::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SECURITY_CAMERA_2, J_L157
	setvar VAR_RESULT, 1
J_L157:
	goto_if_ne VAR_RESULT, 0, J_NoSecurityCamera
	call J_PlaySecurityCameraSounds
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_POPULATION, J_L158
	setvar VAR_RESULT, 1
J_L158:
	goto_if_ne VAR_RESULT, 0, J_NoSecurityCamera
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	setobjectxyperm 1, 4, 7
	addobject 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement 1, J_SecurityCameraMovement2
	waitmovement 1
	call J_TrainerCameraGrunt1
	goto_if_eq VAR_RESULT, 1, J_NoSecurityCamera
	call J_PlaySecurityCameraSounds
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	setobjectxyperm 1, 12, 5
	addobject 1
	applymovement 1, J_SecurityCameraMovement3
	waitmovement 1
	call J_TrainerCameraGrunt2
	goto_if_eq VAR_RESULT, 1, J_NoSecurityCamera
	setflag FLAG_J_SECURITY_CAMERA_2
	return
J_SecurityCamera2b::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SECURITY_CAMERA_2, J_L159
	setvar VAR_RESULT, 1
J_L159:
	goto_if_ne VAR_RESULT, 0, J_NoSecurityCamera
	call J_PlaySecurityCameraSounds
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_POPULATION, J_L160
	setvar VAR_RESULT, 1
J_L160:
	goto_if_ne VAR_RESULT, 0, J_NoSecurityCamera
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	setobjectxyperm 1, 4, 8
	addobject 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement 1, J_SecurityCameraMovement4
	waitmovement 1
	call J_TrainerCameraGrunt1
	goto_if_eq VAR_RESULT, 1, J_NoSecurityCamera
	call J_PlaySecurityCameraSounds
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	setobjectxyperm 1, 12, 5
	addobject 1
	applymovement 1, J_SecurityCameraMovement5
	waitmovement 1
	call J_TrainerCameraGrunt2
	goto_if_eq VAR_RESULT, 1, J_NoSecurityCamera
	setflag FLAG_J_SECURITY_CAMERA_2
	return
J_SecurityCamera3a::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SECURITY_CAMERA_3, J_L161
	setvar VAR_RESULT, 1
J_L161:
	goto_if_ne VAR_RESULT, 0, J_NoSecurityCamera
	call J_PlaySecurityCameraSounds
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_POPULATION, J_L162
	setvar VAR_RESULT, 1
J_L162:
	goto_if_ne VAR_RESULT, 0, J_NoSecurityCamera
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	setobjectxyperm 1, 19, 6
	addobject 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement 1, J_SecurityCameraMovement1
	waitmovement 1
	call J_TrainerCameraGrunt1
	goto_if_eq VAR_RESULT, 1, J_NoSecurityCamera
	call J_PlaySecurityCameraSounds
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	setobjectxyperm 1, 25, 11
	addobject 1
	applymovement 1, J_SecurityCameraMovement6
	waitmovement 1
	call J_TrainerCameraGrunt2
	goto_if_eq VAR_RESULT, 1, J_NoSecurityCamera
	setflag FLAG_J_SECURITY_CAMERA_3
	return
J_SecurityCamera3b::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SECURITY_CAMERA_3, J_L163
	setvar VAR_RESULT, 1
J_L163:
	goto_if_ne VAR_RESULT, 0, J_NoSecurityCamera
	call J_PlaySecurityCameraSounds
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_POPULATION, J_L164
	setvar VAR_RESULT, 1
J_L164:
	goto_if_ne VAR_RESULT, 0, J_NoSecurityCamera
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	setobjectxyperm 1, 19, 7
	addobject 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement 1, J_SecurityCameraMovement1
	waitmovement 1
	call J_TrainerCameraGrunt1
	goto_if_eq VAR_RESULT, 1, J_NoSecurityCamera
	call J_PlaySecurityCameraSounds
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	setobjectxyperm 1, 25, 12
	addobject 1
	applymovement 1, J_SecurityCameraMovement7
	waitmovement 1
	call J_TrainerCameraGrunt2
	goto_if_eq VAR_RESULT, 1, J_NoSecurityCamera
	setflag FLAG_J_SECURITY_CAMERA_3
	return
J_SecurityCamera4::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SECURITY_CAMERA_4, J_L165
	setvar VAR_RESULT, 1
J_L165:
	goto_if_ne VAR_RESULT, 0, J_NoSecurityCamera
	call J_PlaySecurityCameraSounds
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_POPULATION, J_L166
	setvar VAR_RESULT, 1
J_L166:
	goto_if_ne VAR_RESULT, 0, J_NoSecurityCamera
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	setobjectxyperm 1, 17, 16
	addobject 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement 1, J_SecurityCameraMovement1
	waitmovement 1
	call J_TrainerCameraGrunt1
	goto_if_eq VAR_RESULT, 1, J_NoSecurityCamera
	call J_PlaySecurityCameraSounds
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	setobjectxyperm 1, 25, 11
	addobject 1
	applymovement 1, J_SecurityCameraMovement8
	waitmovement 1
	call J_TrainerCameraGrunt2
	goto_if_eq VAR_RESULT, 1, J_NoSecurityCamera
	setflag FLAG_J_SECURITY_CAMERA_4
	return
J_SecurityCamera5::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_SECURITY_CAMERA_5, J_L167
	setvar VAR_RESULT, 1
J_L167:
	goto_if_ne VAR_RESULT, 0, J_NoSecurityCamera
	call J_PlaySecurityCameraSounds
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TEAM_ROCKET_BASE_POPULATION, J_L168
	setvar VAR_RESULT, 1
J_L168:
	goto_if_ne VAR_RESULT, 0, J_NoSecurityCamera
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	setobjectxyperm 1, 3, 16
	addobject 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	applymovement 1, J_SecurityCameraMovement1
	waitmovement 1
	call J_TrainerCameraGrunt1
	goto_if_eq VAR_RESULT, 1, J_NoSecurityCamera
	call J_PlaySecurityCameraSounds
	applymovement OBJ_EVENT_ID_PLAYER, J_Movement_Exclamation
	waitmovement 0
	playbgm MUS_RG_ENCOUNTER_ROCKET, FALSE
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	setobjectxyperm 1, 14, 16
	addobject 1
	applymovement 1, J_SecurityCameraMovement9
	waitmovement 1
	call J_TrainerCameraGrunt2
	goto_if_eq VAR_RESULT, 1, J_NoSecurityCamera
	setflag FLAG_J_SECURITY_CAMERA_5
	return
J_NoSecurityCamera::
	return
J_TrainerCameraGrunt1::
	message J_CameraGrunt1SeenText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_LAST_TALKED, 1
	trainerbattle_no_intro TRAINER_J_GRUNTM_GRUNTM_20, J_CameraGrunt1BeatenText
	removeobject 1
	return
J_TrainerCameraGrunt2::
	message J_CameraGrunt2SeenText
	waitmessage
	waitbuttonpress
	closemessage
	setvar VAR_LAST_TALKED, 1
	trainerbattle_no_intro TRAINER_J_GRUNTM_GRUNTM_21, J_CameraGrunt2BeatenText
	removeobject 1
	return
J_PlaySecurityCameraSounds::
	playse SE_M_LICK
	delay 10
	playse SE_M_LICK
	delay 10
	playse SE_M_LICK
	delay 10
	playse SE_M_LICK
	delay 10
	playse SE_M_LICK
	delay 10
	playse SE_M_LICK
	return
J_ExplodingTrap1::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_1, J_L169
	setvar VAR_RESULT, 1
J_L169:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_KoffingExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_1
	return
J_ExplodingTrap2::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_2, J_L170
	setvar VAR_RESULT, 1
J_L170:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_VoltorbExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_2
	return
J_ExplodingTrap3::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_3, J_L171
	setvar VAR_RESULT, 1
J_L171:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_GeodudeExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_3
	return
J_ExplodingTrap4::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_4, J_L172
	setvar VAR_RESULT, 1
J_L172:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_VoltorbExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_4
	return
J_ExplodingTrap5::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_5, J_L173
	setvar VAR_RESULT, 1
J_L173:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_GeodudeExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_5
	return
J_ExplodingTrap6::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_6, J_L174
	setvar VAR_RESULT, 1
J_L174:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_KoffingExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_6
	return
J_ExplodingTrap7::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_7, J_L175
	setvar VAR_RESULT, 1
J_L175:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_VoltorbExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_7
	return
J_ExplodingTrap8::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_8, J_L176
	setvar VAR_RESULT, 1
J_L176:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_KoffingExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_8
	return
J_ExplodingTrap9::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_9, J_L177
	setvar VAR_RESULT, 1
J_L177:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_KoffingExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_9
	return
J_ExplodingTrap10::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_10, J_L178
	setvar VAR_RESULT, 1
J_L178:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_VoltorbExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_10
	return
J_ExplodingTrap11::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_11, J_L179
	setvar VAR_RESULT, 1
J_L179:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_GeodudeExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_11
	return
J_ExplodingTrap12::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_12, J_L180
	setvar VAR_RESULT, 1
J_L180:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_GeodudeExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_12
	return
J_ExplodingTrap13::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_13, J_L181
	setvar VAR_RESULT, 1
J_L181:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_GeodudeExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_13
	return
J_ExplodingTrap14::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_14, J_L182
	setvar VAR_RESULT, 1
J_L182:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_KoffingExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_14
	return
J_ExplodingTrap15::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_15, J_L183
	setvar VAR_RESULT, 1
J_L183:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_VoltorbExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_15
	return
J_ExplodingTrap16::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_16, J_L184
	setvar VAR_RESULT, 1
J_L184:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_KoffingExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_16
	return
J_ExplodingTrap17::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_17, J_L185
	setvar VAR_RESULT, 1
J_L185:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_VoltorbExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_17
	return
J_ExplodingTrap18::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_18, J_L186
	setvar VAR_RESULT, 1
J_L186:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_GeodudeExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_18
	return
J_ExplodingTrap19::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_19, J_L187
	setvar VAR_RESULT, 1
J_L187:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_GeodudeExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_19
	return
J_ExplodingTrap20::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_20, J_L188
	setvar VAR_RESULT, 1
J_L188:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_VoltorbExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_20
	return
J_ExplodingTrap21::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_21, J_L189
	setvar VAR_RESULT, 1
J_L189:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_KoffingExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_21
	return
J_ExplodingTrap22::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_EXPLODING_TRAP_22, J_L190
	setvar VAR_RESULT, 1
J_L190:
	goto_if_ne VAR_RESULT, 0, J_NoExplodingTrap
	call J_VoltorbExplodingTrap
	setflag FLAG_J_EXPLODING_TRAP_22
	return
J_VoltorbExplodingTrap::
	fadescreen FADE_TO_WHITE
	playmoncry SPECIES_VOLTORB, CRY_MODE_NORMAL
	waitmoncry
	fadescreen FADE_FROM_WHITE
	setvar VAR_LAST_TALKED, -1
	setwildbattle SPECIES_VOLTORB, 23
	dowildbattle
	return
J_GeodudeExplodingTrap::
	fadescreen FADE_TO_WHITE
	playmoncry SPECIES_GEODUDE, CRY_MODE_NORMAL
	waitmoncry
	fadescreen FADE_FROM_WHITE
	setvar VAR_LAST_TALKED, -1
	setwildbattle SPECIES_GEODUDE, 21
	dowildbattle
	return
J_KoffingExplodingTrap::
	fadescreen FADE_TO_WHITE
	playmoncry SPECIES_KOFFING, CRY_MODE_NORMAL
	waitmoncry
	fadescreen FADE_FROM_WHITE
	setvar VAR_LAST_TALKED, -1
	setwildbattle SPECIES_KOFFING, 21
	dowildbattle
	return
J_NoExplodingTrap::
	return
J_TrainerScientistJed::
J_TrainerScientistJed_Script:
	message J_ScientistJedAfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TrainerGruntM16::
J_TrainerGruntM16_Script:
	message J_GruntM16AfterBattleText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TeamRocketBaseB1FSecurityCamera::
	message J_TeamRocketBaseB1FSecurityCameraText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TeamRocketBaseB1FBookshelf::
	goto J_TeamRocketOathScript
J_TeamRocketBaseB1FSecretSwitch::
	setvar VAR_RESULT, 0
	goto_if_unset FLAG_J_TURNED_OFF_SECURITY_CAMERAS, J_L191
	setvar VAR_RESULT, 1
J_L191:
	goto_if_ne VAR_RESULT, 0, J_TeamRocketBaseB1FSecretSwitch_SecretSwitchOff
	message J_TeamRocketBaseB1FSecretSwitchText
	waitmessage
	playse SE_SELECT
	waitbuttonpress
	closemessage
	setflag FLAG_J_TURNED_OFF_SECURITY_CAMERAS
	setflag FLAG_J_SECURITY_CAMERA_1
	setflag FLAG_J_SECURITY_CAMERA_2
	setflag FLAG_J_SECURITY_CAMERA_3
	setflag FLAG_J_SECURITY_CAMERA_4
	setflag FLAG_J_SECURITY_CAMERA_5
	return
J_TeamRocketBaseB1FSecretSwitch_SecretSwitchOff:
	message J_TeamRocketBaseB1FSwitchOffText
	waitmessage
	waitbuttonpress
	closemessage
	return
J_TeamRocketBaseB1FHyperPotion::
	finditem ITEM_HYPER_POTION, 1
	return
J_TeamRocketBaseB1FNugget::
	finditem ITEM_NUGGET, 1
	return
J_TeamRocketBaseB1FGuardSpec::
	finditem ITEM_GUARD_SPEC, 1
	return
J_TeamRocketBaseB1FHiddenRevive::
	finditem ITEM_REVIVE
	return
J_SecurityCameraMovement1::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end
J_SecurityCameraMovement2::
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	face_right
	step_end
J_SecurityCameraMovement3::
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	step_end
J_SecurityCameraMovement4::
	jump_2_up
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	face_right
	step_end
J_SecurityCameraMovement5::
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	step_end
J_SecurityCameraMovement6::
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	step_end
J_SecurityCameraMovement7::
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_left
	step_end
J_SecurityCameraMovement8::
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end
J_SecurityCameraMovement9::
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end
J_CameraGrunt1SeenText::
	.string "Hey!\nIntruder alert!$"
J_CameraGrunt1BeatenText::
	.string "Dang… I failed…$"
J_CameraGrunt2SeenText::
	.string "It's my turn!\nThere's no escape!$"
J_CameraGrunt2BeatenText::
	.string "Surveillance cams\nare in the POKéMON\lstatues.\pWe'll keep appear-\ning until you trip\la secret switch.$"
J_ScientistJedSeenText::
	.string "This was once a\nninja hideout.\pThere are traps to\nconfound intruders\llike you.$"
J_ScientistJedBeatenText::
	.string "I get it…$"
J_ScientistJedAfterBattleText::
	.string "All right. I'll\ndivulge a secret\labout our hideout.\pThat thing on the\nfloor up ahead is\la warp panel.\pIf you step on it,\nyou'll be warped\pback to the en-\ntrance.$"
J_GruntM16SeenText::
	.string "Heheh. Feeling\nlucky, punk?\pGo ahead, take\nanother step.\pWe've got traps\nset in the floor!$"
J_GruntM16BeatenText::
	.string "Kaboom!$"
J_GruntM16AfterBattleText::
	.string "I don't even know\nwhere the traps\lare planted.\pYou'll just have\nto collect your\lcourage and walk.$"
J_TeamRocketBaseB1FSecurityCameraText::
	.string "It's a PERSIAN\nstatue…\pIts eyes are oddly\nshiny.$"
J_TeamRocketBaseB1FSecretSwitchText::
	.string "A secret switch!\nBetter press it.$"
J_TeamRocketBaseB1FSwitchOffText::
	.string "The switch is\nturned off.$"
J_TeamRocketBaseB1F_MapEvents::
