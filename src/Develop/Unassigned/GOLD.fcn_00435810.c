#include <string.h>

/* ADDRESS: GOLD 0x00435810 */
void __cdecl fcn_00435810(char* base, char* name)
{
	char* p;
	char* s;
	int k;

	if (base == 0) {
		return;
	}
	p = base + 0x90;
	for (k = 3; k != 0; k--, p += 0x7c) {
		s = *(char**) (p - 0xc);
		if (s != 0 && strcmp(name, s) == 0) {
			*p &= 0xfd;
		}
	}
}
