// FUNCTION: GOLD 0x4eded0
// FUNCTION: GOLDTL 0x4efd30

#include "client_types.h"
extern Slot170_7731b8 g_7731b8[8];
extern int g_773d38;

int __cdecl fcn_004efd30(int a1)
{
	int i;
	int a;

	if (a1 == -1) {
		return 0;
	}
	i = 0;
	a = (int) g_7731b8;
	do {
		if (*(int*) a == a1) {
			return (int) (((char*)g_7731b8) + i * 368);
		}
		a += 0x170;
		i++;
	} while (a < (int) &g_773d38);
	return 0;
}
