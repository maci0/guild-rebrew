extern int g_774800;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;




unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_0057c920(char* o)
{
	if (o[0x78] & 4) {
		return;
	}
	*(pos14_7f4c00*) (o + 0x44) = g_7f4c00;
	*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
	if (g_774800 != 0) {
		fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 1, 0, 0);
	} else {
		fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 0x18, 0, 0);
		*(short*) (o + 0x56) = gm_RandomMod(2) + 0x13;
	}
	*(int*) (o + 0x58) = 0;
	*(int*) (o + 0x84) = fcn_004c5620(0, o);
}
