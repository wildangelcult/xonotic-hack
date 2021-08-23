#include "trigger.h"

void TRIGGER::trigger() {
	getLocalPlayer();
	getLocalPlayerModel();

	float start[3];
	ASSIGN_VECTOR3_TO_FARR(start, G::r_refdef->origin);
	Vector3 calc = G::r_refdef->origin + (G::r_refdef->forward * 1000000.f);
	float end[3];
	ASSIGN_VECTOR3_TO_FARR(end, calc);

	trace_t trace = { 0 };
	call_traceline(&trace, start, end, G::localplayermodel);

	if (trace.ent && !strcmp(G::PRVM_GetString(G::prog, ((prvm_edict_t*)trace.ent)->fields->classname), "csqcmodel") && (int)((prvm_edict_t*)trace.ent)->fields->entnum <= *G::scoreboardlines && (!G::config.misc.teamplay || (G::cl->scores[(int)((prvm_edict_t*)trace.ent)->fields->entnum - 1].colors & 0xF) != ((int)G::localplayer->fields->colormap & 0xF)))
		*G::attackstate |= 2;
}