#include "gui.h"

tWndProc oWndProc;
HWND hWindow = NULL;

LRESULT CALLBACK hWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (G::menuVisible) {
        ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);
        return 1;
    }
    return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}

BOOL CALLBACK enumWins(HWND hWin, LPARAM lp) {
    DWORD pid;
    GetWindowThreadProcessId(hWin, &pid);
    if (GetCurrentProcessId() != pid) return TRUE;

    hWindow = hWin;
    return FALSE;
}

void GUI::init() {
    glewInit();
    EnumWindows(enumWins, NULL);
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplWin32_Init(hWindow);
    ImGui_ImplOpenGL3_Init("#version 140");

    oWndProc = (WNDPROC)SetWindowLongPtr(hWindow, GWL_WNDPROC, (LONG_PTR)hWndProc);

    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 171, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_CheckMark, IM_COL32(0, 171, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, IM_COL32(0, 0, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(0, 0, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(30, 30, 30, 255));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(50, 50, 50, 255));
    ImGui::PushStyleColor(ImGuiCol_ResizeGrip, IM_COL32(0, 0, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered, IM_COL32(30, 30, 30, 255));
    ImGui::PushStyleColor(ImGuiCol_ResizeGripActive, IM_COL32(50, 50, 50, 255));
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 0, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(30, 30, 30, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(50, 50, 50, 255));
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, IM_COL32(0, 171, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, IM_COL32(30, 171, 30, 255));
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, IM_COL32(30, 30, 30, 255));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, IM_COL32(50, 50, 50, 255));
    ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(0, 0, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_TabHovered, IM_COL32(30, 30, 30, 255));
    ImGui::PushStyleColor(ImGuiCol_TabActive, IM_COL32(50, 50, 50, 255));
    ImGui::PushStyleColor(ImGuiCol_TabUnfocused, IM_COL32(50, 50, 50, 255));
    ImGui::PushStyleColor(ImGuiCol_TabUnfocusedActive, IM_COL32(50, 50, 50, 255));

    G::guiInitialized = true;
}

void GUI::frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Super hagz for 1337 hagerz - Royale with cheese edition");
    ImGui::BeginTabBar("##mainTabs", ImGuiTabBarFlags_Reorderable);

    if (ImGui::BeginTabItem("Aimbot")) {
        ImGui::Checkbox("Enabled", &G::config.aimbot.enabled);
        ImGui::SliderFloat("FOV", &G::config.aimbot.fov, 0.f, 180.f);
        ImGui::Checkbox("Smooth aim", &G::config.aimbot.smooth);
        ImGui::SliderFloat("Smooth aim speed", &G::config.aimbot.smoothSpeed, 0.f, 100.f, "%.3f%%");
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Misc")) {
        ImGui::Checkbox("Triggerbot", &G::config.misc.triggerbot);
        ImGui::Checkbox("Teamplay", &G::config.misc.teamplay);
        ImGui::SameLine();
        guiHelp("I couldn't find a way to detect this automatically, so you have to tell the cheat manually");
        ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::shutdown() {
    SetWindowLongPtr(hWindow, GWL_WNDPROC, (LONG_PTR)oWndProc);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}