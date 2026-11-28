#ifdef REBREW_GOLD
#define fcn_004c3140 fcn_00423a50
#endif
#define RED(c) ((unsigned char) (c))
#define GREEN(c) ((unsigned char) (((unsigned short) (c)) >> 8))
#define BLUE(c) ((unsigned char) ((c) >> 16))
#define ALPHA(c) ((unsigned char) ((c) >> 24))

extern unsigned char msx_AudioVolumeSettings[4];
extern unsigned char g_7766a4[4];
extern float g_681750;
extern float g_6819b0;

void __cdecl sb_SetMasterVolume(int);
void __cdecl SetMasterVolume(int);
void __cdecl fcn_004c3140(int);

/* ADDRESS: GOLDDE 0x005c3af0 */
void __cdecl msx_ApplyAudioSettings(void)
{
	float s;

	s = RED((*(unsigned long*)msx_AudioVolumeSettings)) * (1.0f / 127.0f);
	sb_SetMasterVolume((int) (GREEN((*(unsigned long*)msx_AudioVolumeSettings)) * s));
	SetMasterVolume((int) (BLUE((*(unsigned long*)msx_AudioVolumeSettings)) * s));
	fcn_004c3140((int) (GREEN((*(unsigned long*)msx_AudioVolumeSettings)) * s));
	g_681750 = ALPHA((*(unsigned long*)msx_AudioVolumeSettings)) * (1.0f / 127.0f);
	g_6819b0 = RED((*(unsigned long*)g_7766a4)) * 0.25f;
}
