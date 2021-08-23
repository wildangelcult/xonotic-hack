#pragma once
#include <cmath>
#include "global.h"
#include "vector.h"
#include "helper.h"
#include "geom.h"
#include "helper.h"

namespace AIMBOT {
	float getFov(Vector3 viewangles, Vector3 aimangles);
	Vector3 calcAngle(Vector3 pos);
	prvm_edict_t* getEnemy();
	void aim();
};