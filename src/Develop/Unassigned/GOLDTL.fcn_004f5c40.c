

#include "client_types.h"
#include "client_straftat.h"
#pragma pack(push, 1)

// SIZE 0x2d
#pragma pack(pop)


int __cdecl gm_FindStraftatIndex(unsigned int, int);

int __cdecl fcn_004f5c40(unsigned int key, int start, int* out)
{
	int i;

	i = gm_FindStraftatIndex(key, start);
	if (i >= 0) {
		*out = g_9a3800[i].id;
	}
	return i;
}
