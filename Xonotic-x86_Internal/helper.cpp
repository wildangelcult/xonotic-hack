#include "helper.h"

void getLocalPlayer() {
	unsigned int i;
	prvm_edict_t* ent;
	float tmp = 0;
	for (i = 0, ent = G::prog->edicts; i < G::prog->num_edicts; ++i, ++ent) {
		if (!strcmp(G::PRVM_GetString(G::prog, ent->fields->classname), "entcs_receiver")) {
			tmp = G::r_refdef->origin.z - ent->fields->origin.z;
			if (ent->fields->origin.x == G::r_refdef->origin.x && ent->fields->origin.y == G::r_refdef->origin.y && tmp >= 20 && tmp <= 35) {
				G::localplayer = ent;
				break;
			}
		}
	}
}

void getLocalPlayerModel() {
	unsigned int i;
	prvm_edict_t* ent;
	float tmp = 0;
	for (i = 0, ent = G::prog->edicts; i < G::prog->num_edicts; ++i, ++ent) {
		if (!strcmp(G::PRVM_GetString(G::prog, ent->fields->classname), "csqcmodel")) {
			if ((int)ent->fields->entnum == G::cl->realplayerentity) {
				G::localplayermodel = ent;
			}
		}
	}
}

//u must call getLocalPlayerModel before this
bool canSee(Vector3 target) {
	float start[3];
	ASSIGN_VECTOR3_TO_FARR(start, G::r_refdef->origin);
	float end[3];
	ASSIGN_VECTOR3_TO_FARR(end, target);

	trace_t trace = { 0 };
	call_traceline(&trace, start, end, G::localplayermodel);

	if (trace.ent && !strcmp(G::PRVM_GetString(G::prog, ((prvm_edict_t*)trace.ent)->fields->classname), "csqcmodel") && (int)((prvm_edict_t*)trace.ent)->fields->entnum <= *G::scoreboardlines)
		return true;
	else
		return false;
}

void guiHelp(const char* desc) {
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}