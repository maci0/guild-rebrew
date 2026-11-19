#include "client_types.h"








extern pos14_7f4c00 gm_GameTime;
void __cdecl fcn_00500bb0(char*, int, int, int);

/* ADDRESS: GOLDTL 0x005530d0 */
void __cdecl fcn_005530d0(char* obj)
{
	pos14_7f4c00* p;

	p = (pos14_7f4c00*) (obj + 0x52);
	*p = gm_GameTime;
	fcn_00500bb0((char*) p, 0, 2, 0);
}
