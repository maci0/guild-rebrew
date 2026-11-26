#include "Develop/DieGildeAddOn/game/building_prototype.h"


// SIZE 0x8
typedef struct {
	int key;
	unsigned char lo;
	unsigned char hi;
	short pad;
} Range;

extern Range g_6aa0b0[];
extern unsigned char* lpGebaeudePROT;
extern unsigned short g_7f4c04;

int __cdecl gm_IsGebaeudeOpen(unsigned char* p, int* lo, int* hi)
{
	BUILDING_PROTOTYPE *t;
	int i;

	t = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*p];
	for (i = 0; g_6aa0b0[i].key != 0; i++) {
		if (t->category == g_6aa0b0[i].key) {
			if (lo != 0) {
				*lo = g_6aa0b0[i].lo;
			}
			if (hi != 0) {
				*hi = g_6aa0b0[i].hi;
			}
			if (g_7f4c04 >= (unsigned short) g_6aa0b0[i].lo &&
			    g_7f4c04 < (unsigned short) g_6aa0b0[i].hi) {
				return 1;
			}
			return 0;
		}
	}
	return 1;
}
