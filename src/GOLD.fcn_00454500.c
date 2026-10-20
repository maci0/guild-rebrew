#include <string.h>

/* ADDRESS: GOLD 0x00454500 */
int __cdecl fcn_00454500(int a)
{
	int n;
	char* p;

	n = 0x40;
	p = (char*) a;
	memset(p, 0, n);
	*(int*) (a + 0x3c) = 0x3f800000;
	*(int*) (a + 0x28) = 0x3f800000;
	*(int*) (a + 0x14) = 0x3f800000;
	*(int*) a = 0x3f800000;
	return a;
}
