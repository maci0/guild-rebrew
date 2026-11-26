





// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(char*, int, int, int);
int __cdecl fcn_004c5620(int, char*);

void __cdecl he_StartAction0x67(char* e)
{
	if ((e[0x78] & 4) == 0) {
		*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
		gm_AddTime(e + 0x52, 0x18, 0, 0);
		*(short*) (e + 0x56) = 9;
		*(int*) (e + 0x58) = 0;
		*(int*) (e + 0x84) = fcn_004c5620(0, e);
	}
}
