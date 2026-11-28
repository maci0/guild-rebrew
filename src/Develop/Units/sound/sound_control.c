extern int g_772d30;
extern char* gm_MarketEntity;
extern char g_68a9a8[];

int __cdecl sb_PrepareVoice(int, char*);
int __cdecl d3snd_AttachSoundSource(int, int, int, float);
void __cdecl SetSoundControlValue(int stream, unsigned int value);
void __cdecl d3snd_PlaySource(int, int, int, int);

void __cdecl SetSoundControlValue(int stream, unsigned int value);
void __cdecl d3snd_StopObjectVoice(int, int);
void __cdecl d3snd_StopSourceVoice(int);

/* ADDRESS: GOLDTL 0x004c39b0 */
void __cdecl snd_PlayMarketAmbient(void)
{
	int h;
	int t;

	if (g_772d30 == 0) {
		h = *(int*) (gm_MarketEntity + 0x61);
		if (h != 0) {
			t = sb_PrepareVoice(0, g_68a9a8);
			g_772d30 = d3snd_AttachSoundSource(t, h, 0x7f, 2200.0f);
			if (g_772d30 != 0) {
				SetSoundControlValue(g_772d30, 1);
				d3snd_PlaySource(g_772d30, 0, 0, 0);
			}
		}
	}
}

/* ADDRESS: GOLDTL 0x004c3a10 */
void __cdecl snd_StopMarketAmbient(void)
{
	if (g_772d30 != 0) {
		SetSoundControlValue(g_772d30, 0);
		d3snd_StopObjectVoice(g_772d30, 1);
		d3snd_StopSourceVoice(g_772d30);
		g_772d30 = 0;
	}
}
