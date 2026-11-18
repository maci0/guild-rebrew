


typedef struct
{
	int a;
	int b;
} Pair;
// SIZE 0x8

#include "client_types.h"
extern Pair_99f800 g_99f800[0x800];

int __cdecl fcn_004f58b0(int, int);

int __cdecl fcn_004c9c70(char* a1, char* response)
{
	int index;

	index = fcn_004f58b0(*(int*) (a1 + 0x14), *(int*) (a1 + 0x10));
	if (index > -1) {
		((Pair*)g_99f800)[index].a = *(int*) (a1 + 0x14);
		((Pair*)g_99f800)[index].b = *(int*) (a1 + 0x10);
	}
	if (response != 0) {
		*response = 1;
	}
	return 0;
}
