extern int g_772d14;
extern int g_772d10;
extern int g_772d28;
extern int g_774930;
extern int g_772d1c;
extern int g_772d24;

void __cdecl fcn_004c2d90(float, int);

// FUNCTION: GOLDTL 0x4c2d50

void __cdecl fcn_004c2d50(void)
{
	g_772d28 = 0;
	(*(char*)&g_772d10) = (*(char*)&g_772d14);
	if (g_774930 != 0 && g_772d1c != g_772d24)
		fcn_004c2d90(1.0f, 3000);
}
