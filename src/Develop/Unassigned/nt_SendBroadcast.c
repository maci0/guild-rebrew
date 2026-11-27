#include "g_1552000.h"
extern int g_675170;
extern struct sin_402220 g_1552000;



extern int (__stdcall *g_662350)(int, int, int, int, int, int);

void __cdecl nt_SendBroadcast(int buf, int len)
{
	int h;

	h = g_675170;
	if (h != -1) {
		g_662350(h, buf, len, 0, (int) &g_1552000, 0x10);
	}
}
