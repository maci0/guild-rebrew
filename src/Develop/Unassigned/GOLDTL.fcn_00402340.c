#include "g_1552000.h"
extern int g_675170;
extern struct sin_402220 g_1552000;



extern int (__stdcall *g_662350)(int, int, int, int, int, int);

void __cdecl fcn_00402340(int a1, int a2)
{
	int h;

	h = g_675170;
	if (h != -1) {
		g_662350(h, a1, a2, 0, (int) &g_1552000, 0x10);
	}
}
