extern int g_772d30;
extern char* g_773d78;
extern char g_68a9a8[];

int __cdecl fcn_00422460(int, char*);
int __cdecl d3snd_AttachSoundSource(int, int, int, float);
void __cdecl SetSoundControlValue(int stream, unsigned int value);
void __cdecl d3snd_PlaySource(int, int, int, int);

void __cdecl SetSoundControlValue(int stream, unsigned int value);
void __cdecl d3snd_StopObjectVoice(int, int);
void __cdecl fcn_00418d70(int);

/* ADDRESS: GOLDTL 0x004c39b0 */
void __cdecl fcn_004c39b0(void)
{
	int h;
	int t;

	if (g_772d30 == 0) {
		h = *(int*) (g_773d78 + 0x61);
		if (h != 0) {
			t = fcn_00422460(0, g_68a9a8);
			g_772d30 = d3snd_AttachSoundSource(t, h, 0x7f, 2200.0f);
			if (g_772d30 != 0) {
				SetSoundControlValue(g_772d30, 1);
				d3snd_PlaySource(g_772d30, 0, 0, 0);
			}
		}
	}
}

/* ADDRESS: GOLDTL 0x004c3a10 */
void __cdecl fcn_004c3a10(void)
{
	if (g_772d30 != 0) {
		SetSoundControlValue(g_772d30, 0);
		d3snd_StopObjectVoice(g_772d30, 1);
		fcn_00418d70(g_772d30);
		g_772d30 = 0;
	}
}
