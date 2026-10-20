#include <string.h>

/* ADDRESS: GOLDTL 0x00473360 */
char __cdecl fcn_00473360(char* p)
{
	char shape[9];
	int a;

	if (p == 0)
		return 0;
	memset(shape, 0, 9);
	*(int*) shape = *(int*) p;
	*(int*) (shape + 4) = *(int*) (p + 4);
	if (!memcmp(shape, (char*) 0x67d8bc, 9)) {
		a = *(int*) p;
		if (a == 0 && *(unsigned short*) (p + 4) > 1)
			return 5;
		if (a == 1)
			return 4;
		if (a == 2)
			return 7;
		return a == 3 ? 8 : 1;
	}
	return *(char*) (p + 2) == 2 ? 17 : 0;
}
