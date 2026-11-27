

// SIZE 0x10
typedef struct {
	int a;
	int b;
	int c;
	int d;
} Slot10;

#include "client_types.h"
extern Card_1007ce0 g_1007ce0[24];

int __cdecl gm_FindCardThreeOfAKind(int* ids, int* out, int flag);
int __cdecl gm_FindCardRankGroup(int* ids, int zero, int kind, int* found);

int __cdecl gm_CheckCardFullHouse(int* ids, int* out, int kind)
{
	int i;
	int n;
	int v;

	if (kind != 0) {
		return 0;
	}
	if (ids[0] < 0 || ids[1] < 0 || ids[2] < 0 || ids[3] < 0 || ids[4] < 0) {
		return 0;
	}
	if (gm_FindCardThreeOfAKind(ids, out, 0) == 0) {
		return 0;
	}
	v = ((Slot10*)g_1007ce0)[out[0]].a;
	if (gm_FindCardRankGroup(ids, 0, v, &kind) != 2) {
		return 0;
	}
	n = 3;
	for (i = 0; i < 5; i++) {
		v = ids[i];
		if (((Slot10*)g_1007ce0)[v].a == kind) {
			out[n] = v;
			n++;
			if (n == 5) {
				return 1;
			}
		}
	}
	return 0;
}
