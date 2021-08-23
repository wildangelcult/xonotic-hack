#pragma once
#include <cmath>
#include "vector.h"
#include "sdk.h"
#include "global.h"

#define call_traceline(ret, start, end, skip) G::CL_TraceLine((ret), (start), (end), MOVE_NORMAL, (skip), SUPERCONTENTS_SOLID | SUPERCONTENTS_BODY | SUPERCONTENTS_PLAYERCLIP, 0, /*0,*/ G::collision_extendmovelength->value, qtrue, qtrue, NULL, qtrue, qfalse)

bool world2screen(Vector3 pos, Vector2& screen);

float calc3DDistance(Vector3 src, Vector3 dst);