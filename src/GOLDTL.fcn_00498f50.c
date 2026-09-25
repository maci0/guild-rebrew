#include <string.h>

int __cdecl fcn_004fa5b0(int a1, char* a2, int a3);

// FUNCTION: GOLDTL 0x498f50
// SIZE: 88

int __cdecl fcn_00498f50(int busy, char* name)
{
	int buf[0x88];

	if (busy != 0)
		return 0;
	memset(buf, 0, sizeof(buf));
	buf[0] = 1;
	return fcn_004fa5b0(2, name, (int) buf) == 2 ? 0x16 : 0;
}
