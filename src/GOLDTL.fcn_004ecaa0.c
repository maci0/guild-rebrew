


__declspec(dllimport) unsigned long __stdcall timeGetTime(void);

extern int g_772f78;
extern int g_772f7c;
extern int g_772f80;
extern int g_772f84;
extern int g_772f88;
extern int g_772f8c;
extern int g_68dec0[];

void __cdecl srand(unsigned int seed);
unsigned short __cdecl gm_RandomMod(unsigned short n);
void __cdecl fcn_004ecb40(void);

void __cdecl fcn_004ecaa0(int reseed)
{
	if (reseed) {
		*(unsigned short*) &g_772f8c = (unsigned short) (timeGetTime() % 0x7fff + 1);
	}
	srand((unsigned short) g_772f8c);
	fcn_004ecb40();
	if (reseed) {
		g_772f78 = gm_RandomMod(0x19);
		g_772f7c = g_68dec0[gm_RandomMod(8)];
		g_772f80 = gm_RandomMod(0x19);
		g_772f84 = g_68dec0[gm_RandomMod(8)];
		g_772f88 = 0;
	}
}
