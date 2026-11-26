#include <string.h>

#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;

int __cdecl gm_AddTime(void* p, int size, int a, int b);

/* ADDRESS: GOLDTL 0x0057b000 */
void __cdecl fcn_0057b000(char* obj)
{
	*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
	if (*(unsigned short*) (obj + 0x56) >= 0x17) {
		gm_AddTime(obj + 0x52, 0x18, 0, 0);
		*(unsigned short*) (obj + 0x56) = 0xc;
		*(int*) (obj + 0x70) = 0;
	} else {
		gm_AddTime(obj + 0x52, 6, 0, 0);
		*(int*) (obj + 0x70) = 0;
	}
}
