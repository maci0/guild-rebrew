#include "Develop/client_types.h"

extern int gm_GameTime;

void __cdecl gm_AddTime(char*, int, int, int);

/* ADDRESS: GOLDTL 0x00550480 */
void __cdecl fcn_00550480(char* p)
{
	char* q;

	q = p + 0x52;
	*(pos14_7f4c00*) q = *(pos14_7f4c00*) &gm_GameTime;
	gm_AddTime(q, 0x18, 0, 0);
}
