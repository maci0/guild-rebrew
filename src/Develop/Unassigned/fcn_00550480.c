#include "client_types.h"

extern int g_7f4c00;

void __cdecl fcn_00500bb0(char*, int, int, int);

/* ADDRESS: GOLDTL 0x00550480 */
void __cdecl fcn_00550480(char* p)
{
	char* q;

	q = p + 0x52;
	*(pos14_7f4c00*) q = *(pos14_7f4c00*) &g_7f4c00;
	fcn_00500bb0(q, 0x18, 0, 0);
}
