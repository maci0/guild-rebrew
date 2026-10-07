#include "client_types.h"
extern Obj_1038140 g_1038140[];

void __cdecl fcn_0046f540(int id);

// FUNCTION: GOLDTL 0x4707d0
void __cdecl fcn_004707d0(int k)
{
	int j;

	for (j = 0; j < *(int*) (((char*)g_1038140) + k * 0x2bc + 0x184); j++) {
		fcn_0046f540(((int*) (((char*)g_1038140) + k * 0x2bc + 4))[j]);
	}
}
