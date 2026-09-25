#include <string.h>

struct fcn_004752e0_entry {
	int a;
	int b;
	int c;
	int d;
	int e;
	int used;
};
// SIZE 0x18

extern int g_100f804;
extern struct fcn_004752e0_entry g_100f200[];
// FUNCTION: GOLDTL 0x4752e0
// SIZE: 50

void __cdecl fcn_004752e0(int i)
{
	if (g_100f804 >= 1 && i >= 0) {
		memset(&g_100f200[i], 0, sizeof(g_100f200[i]));
		g_100f804--;
	}
}
