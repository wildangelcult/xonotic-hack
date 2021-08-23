#pragma once
#include <Windows.h>
#include "sdk.h"
#include "vector.h"

struct tConfig {
	struct {
		bool enabled = false;
		float fov = 180.f;
		bool smooth = false;
		float smoothSpeed = 10.f;
	} aimbot;

	struct {
		bool triggerbot = false;
		bool teamplay = false;
	} misc;
};

namespace G {
	extern uintptr_t moduleBase;
	extern tCL_TraceLine CL_TraceLine;
	extern tPRVM_GetString PRVM_GetString;
	extern tMatrix4x4_Invert_Full Matrix4x4_Invert_Full;
	extern tMatrix4x4_Transform Matrix4x4_Transform;
	extern cvar_t* collision_extendmovelength;
	extern cvar_t* v_flipped;
	extern cvar_t* vid_conwidth;
	extern cvar_t* vid_conheight;
	extern cvar_t* teamplay;
	extern prvm_prog_t* prog;
	extern int* scoreboardlines;
	extern r_refdef_t* r_refdef;
	extern client_state_t* cl;
	extern client_static_t* cls;
	extern prvm_edict_t* localplayer;
	extern prvm_edict_t* localplayermodel;
	extern unsigned int* attackstate;

	extern bool guiInitialized;
	extern bool menuVisible;
	extern tConfig config;
};