extern int g_772f3c;



void __cdecl d3snd_StopTrackedVoices(void);
void __cdecl msx_OverrideMusicTrack(void);

void __cdecl fcn_004e4e90(void)
{
	if (g_772f3c == 0) {
		d3snd_StopTrackedVoices();
		msx_OverrideMusicTrack();
	}
}
