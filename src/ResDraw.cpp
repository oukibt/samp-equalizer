#include <main.h>

SAMPFUNCS *SF = new SAMPFUNCS();

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	if (dwReasonForCall == DLL_PROCESS_ATTACH) SF->initPlugin(mainloop, hModule);
	return TRUE;
}

void ResDraw::Line(int ResX, int ResY, int X, int Y, int ToX, int ToY, int W, D3DCOLOR color)
{
	X = int((ResX / DEFAULT_X) * X);
	Y = int((ResY / DEFAULT_Y) * Y);

	ToX = int((ResX / DEFAULT_X) * ToX);
	ToY = int((ResY / DEFAULT_Y) * ToY);

	W = int((ResX / DEFAULT_X) * W);

	SF->getRender()->DrawLine(int(X), int(Y), int(ToX), int(ToY), int(W), color);
}