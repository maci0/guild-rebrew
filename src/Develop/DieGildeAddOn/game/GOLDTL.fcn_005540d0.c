int __cdecl fcn_004c5620(int, char*);

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;




void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl fcn_005540d0(char* o)
{
	if ((o[0x78] & 4) == 0) {
		*(int*) (o + 0xd4) = -1;
		o[0xdc] = 0;
		*(pos14_7f4c00*) (o + 0x44) = gm_GameTime;
		*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (o + 0x52), 0, 1, 0);
		*(int*) (o + 0x84) = fcn_004c5620(0, o);
	}
}
