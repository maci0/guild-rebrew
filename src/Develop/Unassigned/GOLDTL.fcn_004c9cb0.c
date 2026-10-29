


typedef struct
{
	int a;
	int b;
} Pair;
// SIZE 0x8

#include "client_types.h"
extern Pair_99f800 g_99f800[0x800];

int __cdecl fcn_004c9cb0(char* a1, char* a2)
{
	int i;

	for (i = 0; i < 0x800; i++) {
		if (((Pair*)g_99f800)[i].a == *(int*) (a1 + 0x14) && ((Pair*)g_99f800)[i].b == *(int*) (a1 + 0x10)) {
			((Pair*)g_99f800)[i].a = -1;
			((Pair*)g_99f800)[i].b = -1;
			if (a2 != 0) {
				*a2 = 1;
			}
			return 0;
		}
	}
	return 1;
}
