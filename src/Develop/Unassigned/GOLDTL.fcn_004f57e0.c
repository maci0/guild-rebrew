


#include "client_types.h"
#pragma pack(push, 1)
typedef Rec2d_9a3800 Rec2d;
// SIZE 0x2d
#pragma pack(pop)

extern Rec2d_9a3800 g_9a3800[512];

int __cdecl fcn_004f57e0(void)
{
	int r;
	int i;

	r = -1;
	for (i = 0; i < 512; i++) {
		if (g_9a3800[i].x25 == 0) {
			r = i;
			i = 512;
		}
	}
	return r;
}
