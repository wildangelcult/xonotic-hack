#include "global.h"

uintptr_t G::moduleBase = (uintptr_t)GetModuleHandle("xonotic-x86.exe");
tCL_TraceLine G::CL_TraceLine = (tCL_TraceLine)(G::moduleBase + OFFSETS_CL_TraceLine);
tPRVM_GetString G::PRVM_GetString = (tPRVM_GetString)(G::moduleBase + OFFSETS_PRVM_GetString);
tMatrix4x4_Invert_Full G::Matrix4x4_Invert_Full = (tMatrix4x4_Invert_Full)(G::moduleBase + OFFSETS_Matrix4x4_Invert_Full);
tMatrix4x4_Transform G::Matrix4x4_Transform = (tMatrix4x4_Transform)(G::moduleBase + OFFSETS_Matrix4x4_Transform);
cvar_t* G::collision_extendmovelength = (cvar_t*)(G::moduleBase + OFFSETS_collision_extendmovelength);
cvar_t* G::v_flipped = (cvar_t*)(G::moduleBase + OFFSETS_v_flipped);
cvar_t* G::vid_conwidth = (cvar_t*)(G::moduleBase + OFFSETS_vid_conwidth);
cvar_t* G::vid_conheight = (cvar_t*)(G::moduleBase + OFFSETS_vid_conheight);
cvar_t* G::teamplay = (cvar_t*)(G::moduleBase + OFFSETS_teamplay);
prvm_prog_t* G::prog = (prvm_prog_t*)(G::moduleBase + OFFSETS_CLVM);
int* G::scoreboardlines = (int*)(G::moduleBase + OFFSETS_scoreboardlines);
r_refdef_t* G::r_refdef = (r_refdef_t*)(G::moduleBase + OFFSETS_r_refdef);
client_state_t* G::cl = (client_state_t*)(G::moduleBase + OFFSETS_cl);
client_static_t* G::cls = (client_static_t*)(G::moduleBase + OFFSETS_cls);
prvm_edict_t* G::localplayer = nullptr;
prvm_edict_t* G::localplayermodel = nullptr;
unsigned int* G::attackstate = (unsigned int*)(G::moduleBase + OFFSETS_attackstate);

bool G::guiInitialized = false;
bool G::menuVisible = true;
tConfig G::config;