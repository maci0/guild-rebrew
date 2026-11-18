


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl fcn_005591c0(char* e)
{
	*(int*) (e + 0x70) = 0;
	*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
	*(short*) (e + 0x56) = 7;
	*(int*) (e + 0x58) = 0;
}
