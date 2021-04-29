#include <main.h>
#include <Sample.h>

HCHANNEL Channel;

VOID CALLBACK OnDialogResponse(int dialogid, int response, int listitem, const char *input)
{
	if (dialogid != EQUALIZER_DIALOG) return;
	if (!response) return;

	PlayParams *params = new PlayParams(MusicFiles[listitem].data(), 0);
	CreateThread(NULL, NULL, Play, params, NULL, NULL);
}

VOID CALLBACK equa(std::string str)
{
	if (str.empty())
	{
		if (!BASS_ChannelIsActive(Channel))
		{
			MusicList();

			static char string[1024];
			static int len, i;
			
			len = MusicFiles.size();

			memset(string, 0, sizeof string);

			for (i = 0; i < len; i++)
			{
				strcat_s(string, MusicFiles[i].data());
				strcat_s(string, "\n");
			}

			SF->getSAMP()->getDialog()->ShowDialog(EQUALIZER_DIALOG, DIALOG_STYLE_LIST, "Music", string, "Play", "Exit");
			return;
		}
		BASS_ChannelStop(Channel);
		BASS_SampleFree(Channel);
		return;
	}

	SF->getSAMP()->getChat()->AddChatMessage(0xFFFFFFFF, str.c_str());

	PlayParams *params = new PlayParams(str.c_str(), 0);
	CreateThread(NULL, NULL, Play, params, NULL, NULL);
}

bool CALLBACK Virtualize()
{
	if (!SUCCEEDED(SF->getRender()->BeginRender())) return true;

	static float freq[512];
	static char equalizer[70][80];
	static int i, ptr, X, Y;

	if (!BASS_ChannelIsActive(Channel)) return true;
	else BASS_ChannelGetData(Channel, freq, BASS_DATA_FFT1024);

	SF->getGame()->getScreenResolution(&X, &Y);

	for (i = 0; i < (sizeof equalizer) / (sizeof equalizer[0]); i++)
	{
		for (ptr = 0; ptr < sizeof equalizer[0]; ptr++)
		{
			if (freq[(i*(500 / 71))] > ((ptr / 1000.0f) * (ptr / 30.0f))) continue;
			else break;
		}

		ResDraw::Line(X, Y, (i+1.0f) * 7.0f, (Y * (3.6f/5.0f)) / ResDraw::Scale(X), (i+1.0f) * 7.0f, (Y * (3.6f/5.0f) - (ptr * (ResDraw::Scale(X) * 4.0f))) / ResDraw::Scale(X), 5.0f, D3DCOLOR_XRGB(0xFF, 0xFF, 0x20));
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
			Init();

			SF->getRender()->registerD3DCallback(eDirect3DDeviceMethods::D3DMETHOD_PRESENT, Virtualize);
			SF->getSAMP()->registerDialogCallback(OnDialogResponse);
			SF->getSAMP()->registerChatCommand("equa", equa);

			initialized = true;
		}
	}
}