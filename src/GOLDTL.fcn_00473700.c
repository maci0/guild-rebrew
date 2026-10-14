struct fcn_00473700_slot {
	int key;
	int count;
	int extra;
};
// SIZE 0xc

#include "client_types.h"

// FUNCTION: GOLDTL 0x473700

void __cdecl fcn_00473700(int key, int n)
{
	int i;

	for (i = 0; i < 6; i++) {
		if (((struct fcn_00473700_slot*)DisplayCounters)[i].key == key)
			break;
	}
	if (i != 6) {
		((struct fcn_00473700_slot*)DisplayCounters)[i].count -= n;
		if (((struct fcn_00473700_slot*)DisplayCounters)[i].count == 0) {
			((struct fcn_00473700_slot*)DisplayCounters)[i].count = 0;
			((struct fcn_00473700_slot*)DisplayCounters)[i].key = -1;
		}
	}
}
