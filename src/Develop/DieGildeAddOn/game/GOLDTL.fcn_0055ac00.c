#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5620(int, char*);

/* ADDRESS: GOLDTL 0x0055ac00 */
void __cdecl fcn_0055ac00(char* e)
{
	if ((e[0x78] & 4) != 0) {
		return;
	}
	*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
	if (*(unsigned short*) (e + 0x56) >= 0x11) {
		gm_AddTime((pos14_7f4c00*) (e + 0x52), 0x18, 0, 0);
	}
	*(unsigned short*) (e + 0x56) = 0x11;
	*(int*) (e + 0x58) = 0;
	*(int*) (e + 0xac) = 0;
	*(int*) (e + 0xb0) = 0x1b;
	*(int*) (e + 0xb4) = -1;
	*(int*) (e + 0xb8) = -1;
	*(int*) (e + 0x84) = fcn_004c5620(0, e);
}
