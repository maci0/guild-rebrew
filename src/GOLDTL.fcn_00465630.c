#include <stdlib.h>

int __cdecl fcn_00461560(void* z);

// FUNCTION: GOLD 0x00468630
// FUNCTION: GOLDTL 0x465630
int __cdecl fcn_00465630(char* s)
{
	int err = 0;
	char* p;

	if (s == 0) {
		return -102;
	}
	p = *(char**) (s + 0x7c);
	if (p == 0) {
		return -102;
	}
	if (*(unsigned long*) (p + 0x5c) == 0) {
		if (*(unsigned long*) (p + 0x50) != *(unsigned long*) (p + 0x54)) {
			err = -105;
		}
	}
	if (*(void**) p) {
		free(*(void**) p);
	}
	*(void**) p = 0;
	if (*(int*) (p + 0x40)) {
		fcn_00461560(p + 4);
	}
	*(int*) (p + 0x40) = 0;
	if (p) {
		free(p);
	}
	*(char**) (s + 0x7c) = 0;
	return err;
}
