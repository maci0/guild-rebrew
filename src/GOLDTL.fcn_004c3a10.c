extern int g_772d30;

void __cdecl SetSoundControlValue(int stream, unsigned int value);
void __cdecl fcn_00419370(int, int);
void __cdecl fcn_00418d70(int);

// FUNCTION: GOLDTL 0x4c3a10

void __cdecl fcn_004c3a10(void)
{
	if (g_772d30 != 0) {
		SetSoundControlValue(g_772d30, 0);
		fcn_00419370(g_772d30, 1);
		fcn_00418d70(g_772d30);
		g_772d30 = 0;
	}
}
