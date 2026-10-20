#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

void __cdecl fcn_00500bb0(void* clock, int arg2, int arg3, int arg4);
int __cdecl gm_RandomMod(int range);
int __cdecl fcn_004c5620(char a1, unsigned char* e);

/* ADDRESS: GOLDTL 0x00549b90 */
void __cdecl fcn_00549b90(char* p)
{
	if (*(unsigned char*) (p + 0x78) & 4) {
		return;
	}
	*(pos14_7f4c00*) (p + 0x52) = g_7f4c00;
	fcn_00500bb0(p + 0x52, 1, 0, 0);
	*(pos14_7f4c00*) (p + 0xb0) = g_7f4c00;
	fcn_00500bb0(p + 0xb0, 0x18, 0, 0);
	*(int*) (p + 0xb6) = 0;
	*(short*) (p + 0xb4) = (short) (gm_RandomMod(4) + 0x13);
	*(int*) (p + 0xc0) = 1;
	*(int*) (p + 0x84) = fcn_004c5620(0, (unsigned char*) p);
}
