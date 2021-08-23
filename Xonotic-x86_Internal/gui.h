#pragma once
#include <Windows.h>
#include <GL/glew.h>
#include "global.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_win32.h"
#include "helper.h"

typedef LRESULT(CALLBACK* tWndProc)(HWND, UINT, WPARAM, LPARAM);

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace GUI {
	void init();
	void frame();
	void shutdown();
};