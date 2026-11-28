


extern int g_772e6c;
extern int g_772e70;
extern int g_772e74;
extern int g_772e7c;

void __cdecl sb_ReleaseSampleBank(int);

/* ADDRESS: GOLDDE 0x004b0f80 */
void __cdecl d3snd_FreeObjectSoundBanks(void)
{
	if (g_772e6c != 0) {
		sb_ReleaseSampleBank(g_772e6c);
		g_772e6c = 0;
	}
	if (g_772e70 != 0) {
		sb_ReleaseSampleBank(g_772e70);
		g_772e70 = 0;
	}
	if (g_772e74 != 0) {
		sb_ReleaseSampleBank(g_772e74);
		g_772e74 = 0;
	}
	if (g_772e7c != 0) {
		sb_ReleaseSampleBank(g_772e7c);
		g_772e7c = 0;
	}
}
