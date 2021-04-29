#include <cstdio>
#include <Windows.h>
#include <conio.h>
#include <cmath>
#include <string>
#include <vector>

#include <bass.h>
#pragma comment (lib, "bass.lib")

extern std::vector<std::vector<char>> MusicFiles;
extern HCHANNEL Channel;

bool CALLBACK Virtualize();
VOID CALLBACK equa(std::string str);
VOID Init();
VOID Volume(float percent);
VOID ChannelVolume(DWORD Channel, float percent);
DWORD WINAPI Play(void* param);
VOID MusicList();

struct PlayParams
{
	PlayParams(const char *Name, int Value);
	char name[64];
	int value;
};