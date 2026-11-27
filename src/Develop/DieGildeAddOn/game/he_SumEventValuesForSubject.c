


#include "he_tables.h"

extern HE_AP_EVENT g_7dcae0[256];

int __cdecl he_SumEventValuesForSubject(int k)
{
	int sum;
	int i;

	sum = 0;
	for (i = 0; i < 0x100; i++) {
		if (g_7dcae0[i].value_08 != 0 && g_7dcae0[i].subject_id == k) {
			sum += g_7dcae0[i].value_08;
		}
	}
	return sum;
}
