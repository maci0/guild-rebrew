// FUNCTION: GOLD 0x004c90d0
// FUNCTION: GOLDTL 0x4c9c70

typedef struct
{
	int a;
	int b;
} Pair;
// SIZE 0x8

#include "client_types.h"
extern Pair_99f800 g_99f800[0x800];

int __cdecl fcn_004f58b0(int, int);

int __cdecl fcn_004c9c70(char* a1, char* a2)
{
	int i;

	i = fcn_004f58b0(*(int*) (a1 + 0x14), *(int*) (a1 + 0x10));
	if (i > -1) {
		((Pair*)g_99f800)[i].a = *(int*) (a1 + 0x14);
		((Pair*)g_99f800)[i].b = *(int*) (a1 + 0x10);
	}
	if (a2 != 0) {
		*a2 = 1;
	}
	return 0;
}
