// FUNCTION: GOLD 0x004c5bc0
// FUNCTION: GOLDTL 0x4c6680

#include <string.h>

int __cdecl fcn_004c4330(char*);

int __cdecl fcn_004c6680(char* s1, int a, int b, char* s2)
{
	char buf[0x9c];

	buf[0] = 0x4e;
	strcpy(buf + 0x10, s1);
	*(int*) (buf + 0x28) = a;
	*(int*) (buf + 0x2c) = b;
	if (s2 != 0)
		strcpy(buf + 0x30, s2);
	else
		buf[0x30] = 0;
	return fcn_004c4330(buf);
}
