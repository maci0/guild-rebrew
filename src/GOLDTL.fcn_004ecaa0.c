// FUNCTION: GOLD 0x004ead20
// SIZE: 160
// FUNCTION: GOLDTL 0x004ecaa0
// SIZE: 160

__declspec(dllimport) unsigned long __stdcall timeGetTime(void);

extern int g_772f78;
extern int g_772f7c;
extern int g_772f80;
extern int g_772f84;
extern int g_772f88;
extern int g_772f8c;
extern int g_68dec0[];

void __cdecl srand(unsigned int seed);
unsigned short __cdecl fcn_0042e410(unsigned short n);
void __cdecl fcn_004ecb40(void);

void __cdecl fcn_004ecaa0(int reseed)
{
	if (reseed) {
		*(unsigned short*) &g_772f8c = (unsigned short) (timeGetTime() % 0x7fff + 1);
	}
	srand((unsigned short) g_772f8c);
	fcn_004ecb40();
	if (reseed) {
		g_772f78 = fcn_0042e410(0x19);
		g_772f7c = g_68dec0[fcn_0042e410(8)];
		g_772f80 = fcn_0042e410(0x19);
		g_772f84 = g_68dec0[fcn_0042e410(8)];
		g_772f88 = 0;
	}
}
