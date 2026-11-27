extern float g_699b0c;
extern int g_773de4;
extern int g_7f3e20[];



int __cdecl sb_PlayVoice(int, int, int, int, int, int, int);

void __cdecl d3snd_PlayAmbientVoice(int soundName, int volume, int pitch)
{
	int h;

	h = sb_PlayVoice(0, soundName, 0, 0x3f, (int) (volume * g_699b0c), 1, pitch);
	if (g_773de4 < 0x10) {
		g_7f3e20[g_773de4] = h;
		g_773de4++;
	}
}
