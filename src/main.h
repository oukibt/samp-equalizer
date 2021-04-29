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
	float Scale(int X);
	void Line(int ResX, int ResY, float X, float Y, float ToX, float ToY, float W, D3DCOLOR color);
	// void Box(int ResX, int ResY, float X, float Y, float ToX, float ToY, D3DCOLOR color);
};