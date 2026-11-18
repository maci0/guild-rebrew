


#include "client_types.h"
#include "client_straftat.h"
#pragma pack(push, 1)

// SIZE 0x2d
#pragma pack(pop)


int __cdecl fcn_004f57e0(void)
{
	int r;
	int i;

	r = -1;
	for (i = 0; i < 512; i++) {
		if (g_9a3800[i].state == 0) {
			r = i;
			i = 512;
		}
	}
	return r;
}
