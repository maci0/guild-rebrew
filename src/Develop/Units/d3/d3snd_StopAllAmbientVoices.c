extern int g_773de4;
extern int g_7f3e20[];



void __cdecl sb_StopVoice(int, int);

void __cdecl d3snd_StopAllAmbientVoices(void)
{
	int i;

	for (i = 0; i < g_773de4; i++) {
		sb_StopVoice(g_7f3e20[i], 1);
		g_7f3e20[i] = 0;
	}
	g_773de4 = 0;
}
