#include <Sample.h>

std::vector<std::vector<char>> MusicFiles;

PlayParams::PlayParams(const char *Name, int Value)
{
	sprintf_s(name, "%s", Name);
	value = Value;
}

VOID MusicList()
{
	BASS_ChannelStop(Channel);

	static char path[256];
	static int len;
	static std::string str;
	static WIN32_FIND_DATA FindFileData;
	static HANDLE hFind;

	GetCurrentDirectoryA(MAX_PATH, path);
	strcat_s(path, "\\music\\*");

	hFind = FindFirstFile(path, &FindFileData);
	FindNextFile(hFind, &FindFileData);

	MusicFiles.resize(0);
	MusicFiles.erase(MusicFiles.begin(), MusicFiles.end());

	for (;FindNextFile(hFind, &FindFileData) != 0;)
	{
		if (strcmp(&FindFileData.cFileName[strlen(FindFileData.cFileName) - 4], ".mp3")) continue;

		str = FindFileData.cFileName;
		str.append("\n");
		len = MusicFiles.size();
		MusicFiles.resize(len+1);
		MusicFiles[len].assign(str.begin(), str.end());
		MusicFiles[len][strlen(FindFileData.cFileName) - 4] = NULL;
	}
}

VOID Init()
{
	BASS_Init(-1, 44100, NULL, NULL, NULL);
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

	BASS_ChannelStop(Channel);

	GetCurrentDirectoryA(MAX_PATH, path);
	strcat_s(path, "\\music\\");
	strcat_s(path, params->name);
	strcat_s(path, ".mp3");

	HSAMPLE Sample = BASS_SampleLoad(false, path, 0, 0, 1, BASS_SAMPLE_FX);
	Channel = BASS_SampleGetChannel(Sample, FALSE);

    BASS_ChannelPlay(Channel, FALSE); 

	ChannelVolume(Channel, 100.0f);

	delete params, param;

	return 1;
}