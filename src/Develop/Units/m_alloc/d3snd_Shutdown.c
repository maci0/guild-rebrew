extern char* g_6b7e88;
extern int g_6b7d7c;



void __cdecl snd_ReleaseAllSampleBanks(void);
void __cdecl m_FreeTracked(int);
int __cdecl msx_ReleaseWaveDriver(int);

void __cdecl d3snd_Shutdown(void)
{
	snd_ReleaseAllSampleBanks();
	if ((*(int*)&g_6b7e88) != 0) {
		m_FreeTracked((*(int*)&g_6b7e88));
		(*(int*)&g_6b7e88) = 0;
	}
	if (g_6b7d7c != 0) {
		msx_ReleaseWaveDriver(g_6b7d7c);
		g_6b7d7c = 0;
	}
}
