// FUNCTION: GOLDTL 0x4eeb50
// SIZE: 85

#include <string.h>

int __cdecl ahm_CheckFlag(void*);
int __cdecl fcn_004c6d30(int*);

int __cdecl fcn_004eeb50(char* a1, int a2)
{
	int buf[6];

	if (ahm_CheckFlag(a1) == 0) {
		return -1;
	}
	memset(buf, 0, sizeof(buf));
	buf[0] = 0x61536d53;
	buf[1] = *(int*) (a1 + 4);
	buf[4] = a2;
	return fcn_004c6d30(buf);
}
