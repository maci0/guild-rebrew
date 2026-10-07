#include "client_types.h"
extern Obj_1038140 g_1038140[];

// FUNCTION: GOLDTL 0x472830
int __cdecl fcn_00472830(int k, int j)
{
	if (j > *(int*) (((char*)g_1038140) + k * 0x2bc + 0x184) || j < 0) {
		return -1;
	}
	return ((int*) (((char*)g_1038140) + k * 0x2bc + 4))[j];
}
