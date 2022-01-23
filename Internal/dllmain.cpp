#include "include.h"
#include "Hooks.h"
#include "xor.h"

void init(LPVOID Module)
{
    Hooks::initHook(Module);
    Util::console(_("internal"));
    global.modbase = (uintptr_t)GetModuleHandle("client.dll");
    while (true)
    {
        memcpy(&global.VMatrix.matrix, (PBYTE*)(global.modbase + 0x4DC3734), sizeof(global.VMatrix.matrix)); //dwViewMatrix
        global.LPlayer = *(DWORD*)(global.modbase + 0xDB65EC); //dwLocalPlayer
    }
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if(ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        init(hModule);
    }
    return TRUE;
}

