/* ADDRESS: GOLDTL 0x00aed2a0 */
extern char g_aed2a0[];
/* ADDRESS: GOLD 0x00a68ca0 */
extern char g_aed2a0[];



#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_004c47e0(int* p)
{
	int v;

	v = p[1];
	*(char*) (g_aed2a0 + 4) = 0;
	*(int*) g_aed2a0 = v;
	memset(g_aed2a0 + 5, 0, 119);
	*(int*) (g_aed2a0 + 0x80) = 0;
	*(int*) (g_aed2a0 + 0x94) = (int) p;
}
