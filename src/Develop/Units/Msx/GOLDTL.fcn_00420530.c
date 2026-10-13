// FUNCTION: GOLDTL 0x00420530

#include <windows.h>

extern int g_6b71a4;
extern float g_678150;
extern float g_678154;
extern float g_678158;
extern unsigned int g_67815c;
extern int g_678160;
extern int g_6b7190;
extern int g_6b7fac;
extern CRITICAL_SECTION g_14cc5a0;
void __cdecl fcn_0041fc80(int vol);

void __cdecl fcn_00420530(float fade, int time)
{
	if (g_6b71a4 == 0 || fade < 0.0f || fade > 1.0f) {
		return;
	}
	EnterCriticalSection(&g_14cc5a0);
	if (time == 0) {
		g_678150 = fade;
		fcn_0041fc80(g_678160);
		LeaveCriticalSection(&g_14cc5a0);
		return;
	}
	g_67815c = time;
	g_678158 = fade;
	g_678154 = g_678150;
	g_6b7190 = (*(volatile int*)&g_6b7fac) * 8 + (*(volatile int*)&g_6b7fac) * 4 + (*(volatile int*)&g_6b7fac);
	LeaveCriticalSection(&g_14cc5a0);
}
