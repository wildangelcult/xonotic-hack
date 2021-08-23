#pragma once
#include "sdk.h"
#include "global.h"
#include "geom.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_win32.h"

void getLocalPlayer();

void getLocalPlayerModel();

bool canSee(Vector3 target);

void guiHelp(const char* desc);