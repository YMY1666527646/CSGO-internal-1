#pragma once
#include "include.h"
#include "mhook/flow.h"
#include "mhook/MinHook.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

namespace Hooks
{
	void initHook(LPVOID lpReserved);
}