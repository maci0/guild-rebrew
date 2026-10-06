struct fcn_00473700_slot {
	int key;
	int count;
	int extra;
};
// SIZE 0xc

#include "client_types.h"
extern Pair0c_1011980 g_1011980[6];
// FUNCTION: GOLDTL 0x473700

void __cdecl fcn_00473700(int key, int n)
{
	int i;

	for (i = 0; i < 6; i++) {
		if (((struct fcn_00473700_slot*)g_1011980)[i].key == key)
			break;
	}
	if (i != 6) {
		((struct fcn_00473700_slot*)g_1011980)[i].count -= n;
		if (((struct fcn_00473700_slot*)g_1011980)[i].count == 0) {
			((struct fcn_00473700_slot*)g_1011980)[i].count = 0;
			((struct fcn_00473700_slot*)g_1011980)[i].key = -1;
		}
	}
}
