#include <main.h>
#include <Sample.h>

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

HCHANNEL Channel;

VOID CALLBACK equa(std::string str)
{
	if (str.empty())
	{
		BASS_ChannelStop(Channel);
		return;
	}

	PlayParams *params = new PlayParams(str.c_str(), 0);

	CreateThread(NULL, NULL, Play, params, NULL, NULL);
}

bool CALLBACK Virtualize()
{
	if (!SUCCEEDED(SF->getRender()->BeginRender())) return true;

	static float freq[512];
	static char equalizer[60][30];
	static int i, ptr, X, Y;

	SF->getGame()->getScreenResolution(&X, &Y);

	if (!BASS_ChannelIsActive(Channel)) return true;
	else BASS_ChannelGetData(Channel, freq, BASS_DATA_FFT1024);

	for (i = 0; i < (sizeof equalizer) / (sizeof equalizer[0]); i++)
	{
		for (ptr = 0; ptr < sizeof equalizer[0]; ptr++)
		{
			if (freq[(i*(500 / 61))] > (float)ptr / 1000) continue;
			else break;
		}

		SF->getRender()->DrawLine((int)((i+1.0f)*((X / DEFAULT_X) * 7.0f)), (int)(Y * (3.6f/5.0f)), (int)((i+1.0f)*((X / DEFAULT_X) * 7.0f)), (int)(Y * (3.6f/5.0f)) - (int)(ptr*((X / DEFAULT_X)*10.0f)), (int)((X / DEFAULT_X) * 5.0f), D3DCOLOR_XRGB(0xFF, 0xFF, 0x20));
	}

	SF->getRender()->EndRender();

	return true;
}

VOID WINAPI mainloop()
{
	static bool initialized = false;
	if (!initialized)
	{
		if (GAME && GAME->GetSystemState() == eSystemState::GS_PLAYING_GAME && SF->getSAMP()->IsInitialized())
		{
			SF->getSAMP()->getChat()->clDebugColor = D3DCOLOR_XRGB(0x54, 0xb8, 0xd6);
			SF->getSAMP()->getMisc()->ulFpsLimit = 228;
			*reinterpret_cast<BYTE*>(0x58932A) = 3;

			Init();

			SF->getRender()->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_PRESENT, Virtualize);
			SF->getSAMP()->registerChatCommand("equa", equa);
			initialized = true;
		}
	}
}