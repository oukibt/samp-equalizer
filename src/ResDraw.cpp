#include <main.h>

SAMPFUNCS *SF = new SAMPFUNCS();

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	if (dwReasonForCall == DLL_PROCESS_ATTACH) SF->initPlugin(mainloop, hModule);
	return TRUE;
}

float ResDraw::Scale(int X)
{ 
	return (X / DEFAULT_X);
}

void ResDraw::Line(int ResX, int ResY, float X, float Y, float ToX, float ToY, float W, D3DCOLOR color)
{
	SF->getRender()->DrawLine((int)(X * (ResX / DEFAULT_X)), (int)(Y * (ResX / DEFAULT_X)), (int)(ToX * (ResX / DEFAULT_X)), (int)(ToY * (ResX / DEFAULT_X)), (int)((ResX / DEFAULT_X) * W), color);
}