


#include "he_tables.h"

extern HE_AP_EVENT he_ApEvents[256];

/* ADDRESS: GOLDDE 0x0052d5d0 */
int __cdecl he_SumEventCostsForSubject(int k)
{
	int sum;
	int i;

	sum = 0;
	for (i = 0; i < 0x100; i++) {
		if (he_ApEvents[i].value_0c != 0 && he_ApEvents[i].subject_id == k) {
			sum += he_ApEvents[i].value_0c;
		}
	}
	return sum;
}
