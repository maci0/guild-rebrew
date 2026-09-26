#include "client_types.h"
typedef Pair0c_1011980 Pair0c;
// SIZE 0xc

// GLOBAL: GOLDTL 0x1011980
extern Pair0c_1011980 g_1011980[6];
// GLOBAL: GOLD 0xf8ab80
extern Pair0c_1011980 g_1011980[6];

// FUNCTION: GOLD 0x00476b80
// SIZE: 98
// FUNCTION: GOLDTL 0x473690
// SIZE: 98
void __cdecl fcn_00473690(int key, int amt)
{
	int i;
	int a;

	if (amt == 0) {
		return;
	}
	for (i = 0, a = (int) g_1011980; a < (int) (g_1011980 + 6); a += 0xc, i++) {
		if (*(int*) a == key) {
			break;
		}
	}
	if (i == 6) {
		for (i = 0, a = (int) g_1011980; a < (int) (g_1011980 + 6); a += 0xc, i++) {
			if (*(int*) a == -1) {
				break;
			}
		}
		if (i == 6) {
			return;
		}
	}
	g_1011980[i].key = key;
	g_1011980[i].val += amt;
}
