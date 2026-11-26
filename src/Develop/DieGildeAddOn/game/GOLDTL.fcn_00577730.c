#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5620(int, char*);

/* ADDRESS: GOLDTL 0x00577730 */
void __cdecl fcn_00577730(char* e)
{
	if ((e[0x78] & 4) == 0) {
		*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (e + 0x52), 0x30, 0, 0);
		*(int*) (e + 0x84) = fcn_004c5620(0, e);
	}
}
