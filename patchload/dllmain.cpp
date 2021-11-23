#include "pch.h"
HMODULE PMODULE = NULL;
char szPluginPath[MAX_PATH] = "\0";

extern "C" __declspec(dllexport)void* __stdcall Init(LPSTR IniName);
extern "C" __declspec(dllexport)bool __stdcall Release();

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
        
    case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
    	PMODULE = hModule;
    	DisableThreadLibraryCalls(PMODULE);
        GetModuleFileName(PMODULE, szPluginPath, MAX_PATH);
        Init(NULL);
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
        Release();
        break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport) void* __stdcall Init(LPSTR IniName)
{
    static BOOL bInstalled = FALSE;
    if (bInstalled == FALSE)
    {
        bInstalled = TRUE;
        D2String::LogMsg("--------------------------------");
        D2String::LogMsg("--------------------------------");
        D2String::LogMsg("*** ENTERING DIABLO II ***");
        InstallAndUnInstall::Install();
    }

	return NULL;
}

extern "C" __declspec(dllexport) bool __stdcall Release()
{
    static BOOL bUnInstalled = FALSE;
    if (bUnInstalled == FALSE)
    {
        bUnInstalled = TRUE;
        InstallAndUnInstall::UnInstall();
        D2String::LogMsg("***** ENDING DIABLO II *****");
        D2String::LogMsg("--------------------------------");
        D2String::LogMsg("--------------------------------");
    }

	return true;
}

extern "C" PVOID __declspec(dllexport) __stdcall Test() //NOTE :- needs to be exported
{
    char filename[MAX_PATH];
    GetModuleFileName(PMODULE, filename, MAX_PATH);
    LoadLibrary(filename);
    return NULL;
}

