// FUNCTION: GOLD 0x004ece10
// FUNCTION: GOLDTL 0x4eec10

#include <string.h>

int __cdecl ahm_CheckFlag(void*);
int __cdecl fcn_004c6d30(int*);

int __cdecl fcn_004eec10(char* a1)
{
	int buf[6];

	if (ahm_CheckFlag(a1) == 0) {
		return -1;
	}
	memset(buf, 0, sizeof(buf));
	buf[0] = 0x46697245;
	buf[1] = *(int*) (a1 + 4);
	return fcn_004c6d30(buf);
}
