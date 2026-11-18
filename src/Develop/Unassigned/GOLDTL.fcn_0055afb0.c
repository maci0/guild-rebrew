void __cdecl fcn_0055afb0(char*);

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;


/* ADDRESS: GOLDTL 0x0055afb0 */
void __cdecl fcn_0055afb0(char* o)
{
	*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
	*(pos14_7f4c00*) (o + 0xac) = gm_GameTime;
	*(int*) (o + 0x70) = 0;
}
