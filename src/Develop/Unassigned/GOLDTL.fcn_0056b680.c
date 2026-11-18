#include "client_types.h"
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

extern pos14_7f4c00 gm_GameTime;


/* ADDRESS: GOLDTL 0x0056b680 */
void __cdecl fcn_0056b680(char* o)
{
	pos14_7f4c00* p;

	p = (pos14_7f4c00*) (o + 0x52);
	*p = gm_GameTime;
	*(pos14_7f4c00*) (o + 0xcc) = gm_GameTime;
	fcn_00500bb0((pos14_7f4c00*) (o + 0xcc), 0x30, 0, 0);
	fcn_00500bb0(p, 0, 0, 1);
}
