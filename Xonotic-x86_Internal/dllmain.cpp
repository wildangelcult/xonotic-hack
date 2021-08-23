#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "sdk.h"
#include "global.h"
#include "hooks.h"
#include "glDraw.h"
#include "helper.h"
#include "gui.h"
#include "trigger.h"

DWORD WINAPI mainThread(HMODULE hModule) {
    HOOKS::hook();

    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    unsigned int i;
    prvm_edict_t* ent;
    char* buf;
    while (!GetAsyncKeyState(VK_END)) {
        if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
            getLocalPlayer();
            getLocalPlayerModel();
            std::vector<cl_entvars_t*> list;
            for (i = 0, ent = G::prog->edicts; i < G::prog->num_edicts; ++i, ++ent) {
                buf = (char*)G::PRVM_GetString(G::prog, ent->fields->classname);
                std::string findStr(buf);
                if (findStr.find("entcs_receiver") != std::string::npos) {
                    if (G::localplayer == ent) {
                        std::cout << G::PRVM_GetString(G::prog, ent->fields->netname) << " " << i << " (local)" << std::endl;
                    }
                    else {
                        std::cout << G::PRVM_GetString(G::prog, ent->fields->netname) << " " << i << " " << ent << " - "<< (canSee(ent->fields->origin) ? " shoot him !!" : "") << std::endl;
                    }
                    list.push_back(ent->fields);
                }
            }
            std::cout << "-----------------------------" << std::endl;
        }

        if (GetAsyncKeyState(VK_INSERT) & 1) {
            G::menuVisible = !G::menuVisible;
        }
    }

    GUI::shutdown();
    HOOKS::unhook();
    
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)mainThread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

