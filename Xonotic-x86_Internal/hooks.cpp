#include "hooks.h"

tSwapBuffers oSwapBuffers;

unsigned int i;
prvm_edict_t* ent;
void __stdcall HOOKS::hSwapBuffers(HDC hdc) {
	if (!G::guiInitialized) GUI::init();
	GL::setupOrtho();

	if (G::menuVisible) GUI::frame();
	
    for (i = 0, ent = G::prog->edicts; i < G::prog->num_edicts; ++i, ++ent) {
        if (!strcmp(G::PRVM_GetString(G::prog, ent->fields->classname), "entcs_receiver")) {
			Vector2 screen;
			if (world2screen(ent->fields->origin, screen)) {
				GL::drawFilledRect(screen.x - 2, screen.y - 2, 4, 4, colors::red);
			}
        }
    }
	if (G::cls->state == ca_connected) {
		if (G::config.misc.triggerbot) {
				TRIGGER::trigger();
		}

		if (G::config.aimbot.enabled && GetAsyncKeyState(VK_XBUTTON2)) {
			AIMBOT::aim();
		}
	}

	GL::restoreGL();
	oSwapBuffers(hdc);
}

void HOOKS::hook() {
	oSwapBuffers = (tSwapBuffers)mem::TrampHook32((BYTE*)GetProcAddress(GetModuleHandle("GDI32.dll"), "SwapBuffers"), (BYTE*)hSwapBuffers, 6);
}

void HOOKS::unhook() {
	mem::Patch((BYTE*)GetProcAddress(GetModuleHandle("GDI32.dll"), "SwapBuffers"), (BYTE*)oSwapBuffers, 6);
}