#include <cstdio>
#include <Windows.h>
#include <conio.h>
#include <cmath>
#include <string>

using namespace std;

#include <bass.h>
#pragma comment (lib, "bass.lib")

extern HCHANNEL Channel;

bool CALLBACK Virtualize();
VOID CALLBACK equa(std::string str);
void Init();
void Volume(float percent);
void ChannelVolume(DWORD Channel, float percent);
DWORD WINAPI Play(void* param);

struct PlayParams
{
	PlayParams(const char *Name, int Value);
	char name[64];
	int value;
};