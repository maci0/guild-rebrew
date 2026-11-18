#include "client_types.h"
#include "client_actions.h"

extern pos14_7f4c00 g_7f4c00;

extern void __cdecl fcn_00508cf0(int a, void* p);


/* ADDRESS: GOLDTL 0x0055a040 */
void __cdecl fcn_0055a040(char* action)
{
	int* p;
	int n;

	fcn_00508cf0(6, action + 0xb0);
	p = (int*)(action + 0xb0);
	n = 6;
	do {
		*p = *p + 1;
		p++;
	} while (--n != 0);
	*(pos14_7f4c00*)(action + 0x52) = g_7f4c00;
	*(int*)(action + 0x70) = 0xc;
	*(short*)(action + 0x56) = 9;
	*(int*)(action + 0x58) = 0;
}
