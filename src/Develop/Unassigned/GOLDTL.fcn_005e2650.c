

void __cdecl d3_ApplyGraphicsOptions(void);
void __cdecl msx_ApplyAudioSettings(void);
void __cdecl gm_ApplyGameSettings(void);

void __cdecl fcn_005e2650(void)
{
	d3_ApplyGraphicsOptions();
	msx_ApplyAudioSettings();
	gm_ApplyGameSettings();
}
