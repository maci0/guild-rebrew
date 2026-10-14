#include "client_types.h"
extern unsigned short g_7e1f74;
extern unsigned short g_7f4c04;
extern unsigned char g_7747b0;
extern int g_7766a8;
extern int g_6a3774;
extern pos14_7f4c00 g_7e1f70;




void __cdecl fcn_00500bb0(char*, int, int, int);

void __cdecl fcn_00538060(void)
{
	int t;
	int h;
	int m;

	if ((g_7e1f74 < 0x17 && g_7f4c04 < 0x17) || (g_7747b0 & 0x80) != 0) {
		t = (int) ((g_7766a8 * 0.00625f + 0.5) * g_6a3774);
		h = t / 3600;
		m = (t - h * 3600) / 60;
		fcn_00500bb0((char*)&g_7e1f70, h, m, t - (h * 60 + m) * 60);
	}
}
