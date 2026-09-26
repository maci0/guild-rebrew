#include "g_6b71b0.h"

extern Chan g_6b71b0[10];
extern char g_6b72b4[];
extern char g_6b7e44[];

// FUNCTION: GOLD 0x004242c0
// SIZE: 49
// FUNCTION: GOLDTL 0x420650
// SIZE: 49

char* __cdecl fcn_00420650(void)
{
	int i;
	int a;

	i = 0;
	a = (int) g_6b72b4;
	do {
		if (*(char*) (a + 2) == 0 && *(char*) a != 0) {
			return (char*) g_6b71b0 + i * 296;
		}
		a += 0x128;
		i++;
	} while (a < (int) g_6b7e44);
	return 0;
}
