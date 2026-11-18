


#include "he_tables.h"

extern HE_AP_EVENT g_7dcae0[256];

int __cdecl fcn_00546fe0(int k)
{
	int sum;
	int i;

	sum = 0;
	for (i = 0; i < 0x100; i++) {
		if (g_7dcae0[i].value_0c != 0 && g_7dcae0[i].subject_id == k) {
			sum += g_7dcae0[i].value_0c;
		}
	}
	return sum;
}
