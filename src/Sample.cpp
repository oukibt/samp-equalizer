#include <Sample.h>

PlayParams::PlayParams(const char *Name, int Value)
{
	sprintf_s(name, "%s", Name);
	value = Value;
}

VOID Init()
{
	BASS_Init(-1, 44100, 0, 0, NULL);
}

inline VOID gotoxy(int xpos, int ypos)
{
	static COORD scrn;
	static HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = xpos;
	scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

VOID Volume(float percent)
{
	BASS_SetVolume(percent / 100.0f);
}

VOID ChannelVolume(DWORD Channel, float percent)
{
	BASS_ChannelSetAttribute(Channel, BASS_ATTRIB_VOL, (percent / 1000.0f));
}

DWORD WINAPI Play(LPVOID param)
{
	PlayParams* params = (PlayParams*)param;

	static char path[256];

	GetCurrentDirectoryA(sizeof path, path);
	strcat_s(path, "\\music\\");
	strcat_s(path, params->name);
	strcat_s(path, ".mp3");

	BASS_ChannelStop(Channel);

	HSAMPLE Sample = BASS_SampleLoad(false, path, 0, 0, 1, BASS_SAMPLE_FX);
    Channel = BASS_SampleGetChannel(Sample, FALSE);
    BASS_ChannelPlay(Channel, FALSE); 

	ChannelVolume(Channel, 100.0f);

	return 1;
}