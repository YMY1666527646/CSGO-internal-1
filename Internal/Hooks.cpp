#include "Hooks.h"
#include "xor.h"
#include "Draw.h"
#include "Test.h"

#ifdef _WIN64
#define GWL_WNDPROC GWLP_WNDPROC
#endif

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EndScene oEndScene = NULL;
WNDPROC oWndProc;
static HWND window = NULL;

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);
}

bool init = false;
long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!init)
	{
		InitImGui(pDevice);
		init = true;
	}

	bool menu = true;
	if (GetAsyncKeyState(VK_INSERT) & 1) menu = !menu;

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::StyleColorsLight();
	
	ImGui::Begin(_("Internal"));
	ImGui::Checkbox(_("test"), &global.test);

	ImGui::Separator();

	//just matrix stuff
	ImGui::Text(std::to_string(global.VMatrix.matrix[0]).c_str());
	ImGui::Text(std::to_string(global.VMatrix.matrix[1]).c_str());
	ImGui::Text(std::to_string(global.VMatrix.matrix[2]).c_str());
	ImGui::Text(std::to_string(global.VMatrix.matrix[3]).c_str());
	ImGui::Text(std::to_string(global.VMatrix.matrix[4]).c_str());
	ImGui::Text(std::to_string(global.VMatrix.matrix[5]).c_str());
	ImGui::Text(std::to_string(global.VMatrix.matrix[6]).c_str());
	ImGui::Text(std::to_string(global.VMatrix.matrix[7]).c_str());
	ImGui::Text(std::to_string(global.VMatrix.matrix[8]).c_str());
	ImGui::Text(std::to_string(global.VMatrix.matrix[9]).c_str());
	ImGui::Text(std::to_string(global.VMatrix.matrix[10]).c_str());
	ImGui::Text(std::to_string(global.VMatrix.matrix[11]).c_str());
	ImGui::Text(std::to_string(global.VMatrix.matrix[12]).c_str());
	ImGui::Text(std::to_string(global.VMatrix.matrix[13]).c_str());
	ImGui::Text(std::to_string(global.VMatrix.matrix[14]).c_str());
	ImGui::Text(std::to_string(global.VMatrix.matrix[15]).c_str());
	
	ImGui::End();
	ImGui::EndFrame();

	//=======================ESP======================
	Draw::TestBox();
	Test::Test();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return oEndScene(pDevice);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE; // skip to next window

	window = handle;
	return FALSE; // window found abort search
}

HWND GetProcessWindow()
{
	window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return window;
}

void Hooks::initHook(LPVOID lpReserved)
{
	bool attached = false;
	do
	{
		if (flow::init(flow::RenderType::D3D9) == flow::Status::Success)
		{
			flow::bind(42, (void**)&oEndScene, hkEndScene);
			do
				window = GetProcessWindow();
			while (window == NULL);
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
			attached = true;
		}
	} while (!attached);
}
