#include <string.h>

int __cdecl fcn_004fa5b0(int a1, char* a2, int a3);

// FUNCTION: GOLD 0x499570
// FUNCTION: GOLDTL 0x498fb0

int __cdecl fcn_00498fb0(char* name)
{
	int buf[0x88];

	memset(buf, 0, sizeof(buf));
	buf[0] = 1;
	return fcn_004fa5b0(2, name, (int) buf) == 2 ? 0x16 : 0;
}
