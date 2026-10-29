#include <string.h>

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

int __cdecl fcn_00500bb0(void* p, int size, int a, int b);

/* ADDRESS: GOLDTL 0x0057b000 */
void __cdecl fcn_0057b000(char* obj)
{
	*(pos14_7f4c00*) (obj + 0x52) = g_7f4c00;
	if (*(unsigned short*) (obj + 0x56) >= 0x17) {
		fcn_00500bb0(obj + 0x52, 0x18, 0, 0);
		*(unsigned short*) (obj + 0x56) = 0xc;
		*(int*) (obj + 0x70) = 0;
	} else {
		fcn_00500bb0(obj + 0x52, 6, 0, 0);
		*(int*) (obj + 0x70) = 0;
	}
}
