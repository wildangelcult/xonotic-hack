#include "aimbot.h"
const double PI = 3.14159265358979323846;

void sinCos(float angle, float* sine, float* cosine) {
	*sine = sin(angle);
	*cosine = cos(angle);
}

Vector3 angleVectors(Vector3 angles) {
	float sp, sy, cp, cy;
	sinCos(angles.x * (PI / 180), &sp, &cp);
	sinCos(angles.y * (PI / 180), &sy, &cy);
	return {cp * cy, cp * sy, -sp};
}

float AIMBOT::getFov(Vector3 viewangles, Vector3 aimangles) {
	Vector3 view = angleVectors(viewangles);
	Vector3 aim = angleVectors(aimangles);
	return acos(view.dot(aim) / view.lengthSqr()) * (180 / PI);
}

Vector3 AIMBOT::calcAngle(Vector3 pos) {
	Vector3 delta = pos - G::r_refdef->origin;

	return {-(float)(asin(delta.z / delta.length()) * (180 / PI)), (float)(atan2(delta.y, delta.x) * (180 / PI)), 0.0f};
}

prvm_edict_t* AIMBOT::getEnemy() {
	getLocalPlayer();
	getLocalPlayerModel();
	float lowestFov = G::config.aimbot.fov;
	float currFov = 0.f;
	prvm_edict_t* result = nullptr;

	unsigned int i;
	prvm_edict_t* ent;
	for (i = 0, ent = G::prog->edicts; i < G::prog->num_edicts; ++i, ++ent) {
		if (strcmp(G::PRVM_GetString(G::prog, ent->fields->classname), "entcs_receiver"))
			continue;
		if (G::localplayer == ent)
			continue;
		if (G::config.misc.teamplay && ((int)G::localplayer->fields->colormap & 0xF) == ((int)ent->fields->colormap & 0xF))
			continue;
		if (!canSee(ent->fields->origin))
			continue;

		currFov = getFov(G::cl->viewangles, calcAngle(ent->fields->origin));
		if (currFov <= lowestFov) {
			lowestFov = currFov;
			result = ent;
		}
	}

	return result;
}

void AIMBOT::aim() {
	prvm_edict_t* enemy = getEnemy();
	if (enemy) {
		Vector3 aimangle = calcAngle(enemy->fields->origin);
		if (G::config.aimbot.smooth) {
			Vector3 delta = aimangle - G::cl->viewangles;
			delta.correctAngles();
			aimangle = G::cl->viewangles + (delta * (G::config.aimbot.smoothSpeed / 100));
			aimangle.correctAngles();
			G::cl->viewangles = aimangle;
		}
		else {
			G::cl->viewangles = aimangle;
		}
	}
}