#pragma once

#include <Windows.h>
#include <fstream>
#include <string>
#include "SAMPFUNCS_API.h"
#include "game_api.h"

#define DEFAULT_X 1920.0f
#define DEFAULT_Y 1080.0f

extern SAMPFUNCS *SF;

#define EQUALIZER_DIALOG 24891

VOID WINAPI mainloop();
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved);

namespace ResDraw
{
	void Line(int ResX, int ResY, int X, int Y, int ToX, int ToY, int W, D3DCOLOR color);
};