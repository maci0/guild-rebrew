

void __cdecl d3_ApplyGraphicsOptions(void);
void __cdecl msx_ApplyAudioSettings(void);
void __cdecl fcn_005e2510(void);

void __cdecl fcn_005e2650(void)
{
	d3_ApplyGraphicsOptions();
	msx_ApplyAudioSettings();
	fcn_005e2510();
}
