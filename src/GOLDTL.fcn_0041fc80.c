// FUNCTION: GOLDTL 0x0041fc80
// SIZE: 168

#include <stdio.h>
#include <windows.h>

extern int g_6b71a4;
extern float g_678150;
extern int g_678160;
extern char g_6b7090[];
extern CRITICAL_SECTION g_14cc5a0;
void __cdecl fcn_0042a0e0(int h, int vol);

void __cdecl fcn_0041fc80(int vol)
{
	if (g_6b71a4 == 0) {
		return;
	}
	if (g_678150 < 0.0f) {
		g_678150 = 0.0f;
	} else if (g_678150 > 1.0f) {
		g_678150 = 1.0f;
	}
	EnterCriticalSection(&g_14cc5a0);
	fcn_0042a0e0(g_6b71a4, (int) (vol * g_678150));
	LeaveCriticalSection(&g_14cc5a0);
	g_678160 = vol;
	sprintf(g_6b7090, "Fademodifier is %f, Mastervolume is %d", g_678150, vol);
}
