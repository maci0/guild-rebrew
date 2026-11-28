

void __cdecl d3_ApplyGraphicsOptions(void);
void __cdecl msx_ApplyAudioSettings(void);
void __cdecl gm_ApplyGameSettings(void);

void __cdecl main_ApplyAllSettings(void)
{
	d3_ApplyGraphicsOptions();
	msx_ApplyAudioSettings();
	gm_ApplyGameSettings();
}
