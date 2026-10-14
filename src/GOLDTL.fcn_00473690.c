#include "client_types.h"
typedef DISPLAY_COUNTER Pair0c;
// SIZE 0xc






/* ADDRESS: GOLD 0x00476b80 */
/* ADDRESS: GOLDTL 0x00473690 */
void __cdecl fcn_00473690(int key, int amt)
{
	int i;
	int a;

	if (amt == 0) {
		return;
	}
	for (i = 0, a = (int) DisplayCounters; a < (int) (DisplayCounters + 6); a += 0xc, i++) {
		if (*(int*) a == key) {
			break;
		}
	}
	if (i == 6) {
		for (i = 0, a = (int) DisplayCounters; a < (int) (DisplayCounters + 6); a += 0xc, i++) {
			if (*(int*) a == -1) {
				break;
			}
		}
		if (i == 6) {
			return;
		}
	}
	DisplayCounters[i].key = key;
	DisplayCounters[i].val += amt;
}
