typedef struct Tag {
	int id;
	int val;
	int pad;
} Tag;
// SIZE 0xc

#include "client_types.h"
extern Pair0c_1011980 g_1011980[6];

// FUNCTION: GOLD 0x00476bf0
// FUNCTION: GOLDTL 0x473750
void __cdecl fcn_00473750(int id, int val)
{
	int i;

	for (i = 0; i < 6; i++) {
		if (((Tag*)g_1011980)[i].id == id) {
			break;
		}
	}
	if (i == 6) {
		for (i = 0; i < 6; i++) {
			if (((Tag*)g_1011980)[i].id == -1) {
				break;
			}
		}
		if (i == 6) {
			return;
		}
	}
	((Tag*)g_1011980)[i].id = id;
	((Tag*)g_1011980)[i].val = val;
	if (!val) {
		((Tag*)g_1011980)[i].val = 0;
		((Tag*)g_1011980)[i].id = -1;
	}
}
