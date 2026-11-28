extern char* sb_Voices;
extern int sb_WaveDriver;



void __cdecl snd_ReleaseAllSampleBanks(void);
void __cdecl m_FreeTracked(int);
int __cdecl msx_ReleaseWaveDriver(int);

/* ADDRESS: GOLDDE 0x0041efd0 */
void __cdecl d3snd_Shutdown(void)
{
	snd_ReleaseAllSampleBanks();
	if ((*(int*)&sb_Voices) != 0) {
		m_FreeTracked((*(int*)&sb_Voices));
		(*(int*)&sb_Voices) = 0;
	}
	if (sb_WaveDriver != 0) {
		msx_ReleaseWaveDriver(sb_WaveDriver);
		sb_WaveDriver = 0;
	}
}
