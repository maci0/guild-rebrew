#include "client_types.h"
void __cdecl sim_SetSyncParams(pos14_7f4c00*, int, int, int);

extern pos14_7f4c00 gm_GameTime;




void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_00567ff0(char* o)
{
	pos14_7f4c00* p;

	p = (pos14_7f4c00*) (o + 0x52);
	*p = gm_GameTime;
	sim_SetSyncParams(p, 5, 0, 0);
	*(pos14_7f4c00*) (o + 0x60) = *p;
	fcn_00500bb0(p, 1, 0, 0);
}
