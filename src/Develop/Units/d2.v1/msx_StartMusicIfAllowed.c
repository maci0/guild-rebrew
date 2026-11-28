extern int cut_SkipMode;



void __cdecl d3snd_StopTrackedVoices(void);
void __cdecl msx_OverrideMusicTrack(void);

void __cdecl msx_StartMusicIfAllowed(void)
{
	if (cut_SkipMode == 0) {
		d3snd_StopTrackedVoices();
		msx_OverrideMusicTrack();
	}
}
