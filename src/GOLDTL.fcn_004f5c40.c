

#include "client_types.h"
#pragma pack(push, 1)
typedef Rec2d_9a3800 Rec2d;
// SIZE 0x2d
#pragma pack(pop)

extern Rec2d_9a3800 g_9a3800[512];

int __cdecl fcn_004f5bf0(unsigned int, int);

int __cdecl fcn_004f5c40(unsigned int key, int start, int* out)
{
	int i;

	i = fcn_004f5bf0(key, start);
	if (i >= 0) {
		*out = g_9a3800[i].id;
	}
	return i;
}
