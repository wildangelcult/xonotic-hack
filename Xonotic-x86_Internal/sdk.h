#pragma once
#include <cstdint>
#include "vector.h"

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}
#define DEFINE_MEMBER_0(type, name, offset) type name

#define OFFSETS_PRVM_GetString 0x201E60
#define OFFSETS_CL_TraceLine 0x3A090
#define OFFSETS_Matrix4x4_Invert_Full 0x17CD70
#define OFFSETS_Matrix4x4_Transform 0x17F6B0
#define OFFSETS_collision_extendmovelength 0x396A80
#define OFFSETS_v_flipped 0x3993A0
#define OFFSETS_vid_conwidth 0x394500
#define OFFSETS_vid_conheight 0x394480
#define OFFSETS_CLVM 0x142e300
#define OFFSETS_scoreboardlines 0xA5E500
#define OFFSETS_r_refdef 0x137F8C0
#define OFFSETS_cl 0xC56D60
#define OFFSETS_attackstate 0xC564CC
#define OFFSETS_teamplay 0x3B14C0
#define OFFSETS_cls 0xE3F300

#define SUPERCONTENTS_SOLID			0x00000001
#define SUPERCONTENTS_WATER			0x00000002
#define SUPERCONTENTS_SLIME			0x00000004
#define SUPERCONTENTS_LAVA			0x00000008
#define SUPERCONTENTS_SKY			0x00000010
#define SUPERCONTENTS_BODY			0x00000020
#define SUPERCONTENTS_CORPSE		0x00000040
#define SUPERCONTENTS_NODROP		0x00000080
#define SUPERCONTENTS_PLAYERCLIP	0x00000100
#define SUPERCONTENTS_MONSTERCLIP	0x00000200
#define SUPERCONTENTS_DONOTENTER	0x00000400
#define SUPERCONTENTS_BOTCLIP		0x00000800
#define SUPERCONTENTS_OPAQUE		0x00001000

#define SUPERCONTENTS_LIQUIDSMASK	(SUPERCONTENTS_LAVA | SUPERCONTENTS_SLIME | SUPERCONTENTS_WATER)
#define SUPERCONTENTS_VISBLOCKERMASK	SUPERCONTENTS_OPAQUE

#define MOVE_NORMAL     0
#define MOVE_NOMONSTERS 1
#define MOVE_MISSILE    2
#define MOVE_WORLDONLY  3
#define MOVE_HITMODEL   4

typedef enum cactive_e
{
	ca_uninitialized,	// during early startup
	ca_dedicated, 		// a dedicated server with no ability to start a client
	ca_disconnected, 	// full screen console with no connection
	ca_connected		// valid netcon, talking to a server
}
cactive_t;

#pragma pack(1)
class client_static_t {
public:
	union {
		DEFINE_MEMBER_0(cactive_t, state, 0x0);
	};
};

#pragma pack(1)
class entity_t {
public:
	union {
		DEFINE_MEMBER_N(uint16_t, modelindex, 0x150 + 0x36);
		DEFINE_MEMBER_N(uint32_t, end, 0x4a0 - 0x4);
	};
};

#pragma pack(1)
class scoreboard_t {
public:
	union {
		DEFINE_MEMBER_0(char, name[128], 0x0);
		DEFINE_MEMBER_N(int, frags, 0x80);
		DEFINE_MEMBER_N(int, colors, 0x84);
		DEFINE_MEMBER_N(int, qw_userid, 0x88);
		DEFINE_MEMBER_N(char, qw_userinfo[1280], 0x8c);
		DEFINE_MEMBER_N(float, qw_entertime, 0x58c);
		DEFINE_MEMBER_N(int, qw_ping, 0x590);
		DEFINE_MEMBER_N(int, qw_packetloss, 0x594);
		DEFINE_MEMBER_N(int, qw_movementloss, 0x598);
		DEFINE_MEMBER_N(int, qw_spectator, 0x59c);
		DEFINE_MEMBER_N(char, qw_team[8], 0x5a0);
		DEFINE_MEMBER_N(char, qw_skin[128], 0x5a8);
	};
};

#pragma pack(1)
class client_state_t {
public:
	union {
		DEFINE_MEMBER_N(Vector3, viewangles, 0x5a30);
		DEFINE_MEMBER_N(int, realplayerentity, 0x199d98);
		DEFINE_MEMBER_N(int, playerentity, 0x199d9c);
		DEFINE_MEMBER_N(int, maxclients, 0x199da0);
		DEFINE_MEMBER_N(scoreboard_t*, scores, 0x19a288);
		DEFINE_MEMBER_N(entity_t*, entities, 0x1a240c);
		DEFINE_MEMBER_N(int, num_entities, 0x1a243c);
	};
};

#pragma pack(1)
class cl_entvars_t {
public:
	union {
		DEFINE_MEMBER_N(float, entnum, 0x1c);
		DEFINE_MEMBER_N(Vector3, origin, 0x30);
		DEFINE_MEMBER_N(int, classname, 0x6c);
		DEFINE_MEMBER_N(int, netname, 0xbc);
		DEFINE_MEMBER_N(float, colormap, 0xc8);
	};
};

#pragma pack(1)
class prvm_edict_t {
public:
	union {
		DEFINE_MEMBER_0(uintptr_t, privPtr, 0x0);
		DEFINE_MEMBER_N(cl_entvars_t*, fields, 0x4);
	};
};

#pragma pack(1)
class prvm_prog_t {
public:
	union {
		DEFINE_MEMBER_N(int, num_edicts, 0x396ac);
		DEFINE_MEMBER_N(int, max_edicts, 0x396b0);
		DEFINE_MEMBER_N(int, limit_edicts, 0x396b4);
		DEFINE_MEMBER_N(int, reserved_edicts, 0x396b8);
		DEFINE_MEMBER_N(prvm_edict_t*, edicts, 0x396bc);
	};
};

#pragma pack(1)
class cvar_t {
public:
	union {
		DEFINE_MEMBER_N(const char*, name, 0x4);
		DEFINE_MEMBER_N(const char*, description, 0xc);
		DEFINE_MEMBER_N(int, integer, 0x10);
		DEFINE_MEMBER_N(float, value, 0x14);
		DEFINE_MEMBER_N(Vector3, vector, 0x18);
	};
};

#pragma pack(1)
class r_refdef_t {
public:
	union {
		DEFINE_MEMBER_N(float, matrix[16], 0x8 + 0x0);
		DEFINE_MEMBER_N(Vector3, origin, 0x8 + 0x80);
		DEFINE_MEMBER_N(Vector3, forward, 0x8 + 0x8c);
		DEFINE_MEMBER_N(Vector3, left, 0x8 + 0x98);
		DEFINE_MEMBER_N(Vector3, right, 0x8 + 0xa4);
		DEFINE_MEMBER_N(Vector3, up, 0x8 + 0xb0);
		DEFINE_MEMBER_N(float, frustum_x, 0x8 + 0x170);
		DEFINE_MEMBER_N(float, frustum_y, 0x8 + 0x174);
		DEFINE_MEMBER_N(int, width, 0x8 + 0x1c0);
		DEFINE_MEMBER_N(int, height, 0x8 + 0x1c4);
	};
};

typedef union plane_s
{
	struct
	{
		Vector3	normal;
		float	dist;
	};
	Vector4 normal_and_dist;
}
plane_t;

typedef struct trace_s
{
	// if true, the entire trace was in solid (see hitsupercontentsmask)
	int allsolid;
	// if true, the initial point was in solid (see hitsupercontentsmask)
	int startsolid;
	// this is set to true in world.c if startsolid was set in a trace against world
	int worldstartsolid;
	// this is set to true in world.c if startsolid was set in a trace against a SOLID_BSP entity, in other words this is true if the entity is stuck in a door or wall, but not if stuck in another normal entity
	int bmodelstartsolid;
	// if true, the trace passed through empty somewhere
	// (set only by Q1BSP tracing)
	int inopen;
	// if true, the trace passed through water/slime/lava somewhere
	// (set only by Q1BSP tracing)
	int inwater;
	// fraction of the total distance that was traveled before impact
	// in case of impact this is actually nudged a bit off the surface
	// (1.0 = did not hit anything)
	double fraction;
	// final position of the trace (simply a point between start and end)
	double endpos[3];
	// surface normal at impact (not really correct for edge collisions)
	plane_t plane;
	// entity the surface is on
	// (not set by trace functions, only by physics)
	void* ent;
	// which SUPERCONTENTS bits to collide with, I.E. to consider solid
	// (this also affects startsolid/allsolid)
	int hitsupercontentsmask;
	// deliberately skip surfaces matching this mask (e.g. SUPERCONTENTS_SKY allows you to bypass sky surfaces in q1bsp/q2bsp which are SUPERCONTENTS_SKY | SUPERCONTENTS_SOLID)
	int skipsupercontentsmask;
	// deliberately skip surfaces matching this mask on materialflags (e.g. MATERIALFLAGMASK_TRANSLUCENT)
	int skipmaterialflagsmask;
	// the supercontents mask at the start point
	int startsupercontents;
	// the supercontents of the impacted surface
	int hitsupercontents;
	// the q3 surfaceflags of the impacted surface
	int hitq3surfaceflags;
	// the texture of the impacted surface
	const void* hittexture;
	// initially false, set when the start leaf is found
	// (set only by Q1BSP tracing and entity box tracing)
	int startfound;
	// if startsolid, contains the minimum penetration depth found in the
	// trace, and the normal needed to push it out of that solid
	double startdepth;
	double startdepthnormal[3];
	const void* starttexture;
}
trace_t;

enum qbool {
	qfalse = 0,
	qtrue = 1
};

typedef const char*(__cdecl* tPRVM_GetString)(prvm_prog_t* prog, int num);
typedef void(__cdecl* tCL_TraceLine)(trace_t* ret, float* start, float* end, int type, prvm_edict_t* passedict, int hitsupercontentsmask, int skipsupercontentsmask, /*int skipmaterialflagsmask,*/ float extend, qbool hitnetworkbrushmodels, qbool hitnetworkplayers, int* hitnetworkentity, qbool hitcsqcentities, qbool hitsurfaces);
typedef int(__cdecl* tMatrix4x4_Invert_Full)(float* out, float* in);
typedef void(__cdecl* tMatrix4x4_Transform)(float *in, float *v, float *out);

#pragma pack()