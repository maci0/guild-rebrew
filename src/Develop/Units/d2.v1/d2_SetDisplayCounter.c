typedef struct Tag {
	int id;
	int val;
	int pad;
} Tag;
// SIZE 0xc

#include "Develop/client_types.h"


/* ADDRESS: GOLDTL 0x00473750 */
void __cdecl d2_SetDisplayCounter(int id, int val)
{
	int i;

	for (i = 0; i < 6; i++) {
		if (((Tag*)d2_DisplayCounters)[i].id == id) {
			break;
		}
	}
	if (i == 6) {
		for (i = 0; i < 6; i++) {
			if (((Tag*)d2_DisplayCounters)[i].id == -1) {
				break;
			}
		}
		if (i == 6) {
			return;
		}
	}
	((Tag*)d2_DisplayCounters)[i].id = id;
	((Tag*)d2_DisplayCounters)[i].val = val;
	if (!val) {
		((Tag*)d2_DisplayCounters)[i].val = 0;
		((Tag*)d2_DisplayCounters)[i].id = -1;
	}
}
