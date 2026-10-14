typedef struct Tag {
	int id;
	int val;
	int pad;
} Tag;
// SIZE 0xc

#include "client_types.h"


/* ADDRESS: GOLD 0x00476bf0 */
/* ADDRESS: GOLDTL 0x00473750 */
void __cdecl fcn_00473750(int id, int val)
{
	int i;

	for (i = 0; i < 6; i++) {
		if (((Tag*)DisplayCounters)[i].id == id) {
			break;
		}
	}
	if (i == 6) {
		for (i = 0; i < 6; i++) {
			if (((Tag*)DisplayCounters)[i].id == -1) {
				break;
			}
		}
		if (i == 6) {
			return;
		}
	}
	((Tag*)DisplayCounters)[i].id = id;
	((Tag*)DisplayCounters)[i].val = val;
	if (!val) {
		((Tag*)DisplayCounters)[i].val = 0;
		((Tag*)DisplayCounters)[i].id = -1;
	}
}
