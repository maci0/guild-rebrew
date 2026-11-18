


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_0056fc70(char* u)
{
	*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
	fcn_00500bb0((pos14_7f4c00*) (u + 0x52), 0, 0x14, 0);
}
