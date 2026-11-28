struct D2_DISPLAY_COUNTER_SLOT {
	int key;
	int count;
	int extra;
};
// SIZE 0xc

#include "Develop/client_types.h"


/* ADDRESS: GOLDTL 0x00473700 */
void __cdecl d2_SubDisplayCounter(int key, int n)
{
	int i;

	for (i = 0; i < 6; i++) {
		if (((struct D2_DISPLAY_COUNTER_SLOT*)d2_DisplayCounters)[i].key == key)
			break;
	}
	if (i != 6) {
		((struct D2_DISPLAY_COUNTER_SLOT*)d2_DisplayCounters)[i].count -= n;
		if (((struct D2_DISPLAY_COUNTER_SLOT*)d2_DisplayCounters)[i].count == 0) {
			((struct D2_DISPLAY_COUNTER_SLOT*)d2_DisplayCounters)[i].count = 0;
			((struct D2_DISPLAY_COUNTER_SLOT*)d2_DisplayCounters)[i].key = -1;
		}
	}
}
