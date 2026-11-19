





// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

short __cdecl fcn_004ac260(void);
int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_00555cd0(char* e)
{
	if ((e[0x78] & 4) == 0) {
		*(short*) (e + 0xac) = fcn_004ac260();
		*(int*) (e + 0xb4) = -1;
		*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
		*(int*) (e + 0x84) = fcn_004c5620(0, e);
	}
}
