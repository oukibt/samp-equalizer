#pragma once

#include <Windows.h>
#include <fstream>
#include <string>
#include "SAMPFUNCS_API.h"
#include "game_api.h"

#define DEFAULT_X 1920.0f
#define DEFAULT_Y 1080.0f

extern SAMPFUNCS *SF = new SAMPFUNCS();

VOID WINAPI mainloop();
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	if (dwReasonForCall == DLL_PROCESS_ATTACH) SF->initPlugin(mainloop, hModule);
	return TRUE;
}