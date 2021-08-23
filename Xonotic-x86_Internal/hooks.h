#pragma once
#include <Windows.h>
#include <cstring>
#include "mem.h"
#include "glDraw.h"
#include "sdk.h"
#include "global.h"
#include "geom.h"
#include "gui.h"
#include "trigger.h"
#include "aimbot.h"

typedef void(__stdcall* tSwapBuffers)(HDC hdc);

namespace HOOKS {
	void hook();
	void __stdcall hSwapBuffers(HDC hdc);
	void unhook();
};