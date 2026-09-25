// FUNCTION: GOLDTL 0x4b0100
// SIZE: 138

#include <string.h>

typedef struct {
	short v[7];
} stamp14;
// SIZE 0xe

extern stamp14 g_7f4c00;
extern char* g_773da8;

void __cdecl fcn_004c5530(void*);

int __cdecl fcn_004b0100(void)
{
	char m[0xf8];

	memset(m, 0, sizeof(m));
	m[4] = 0x4e;
	*(int*) (m + 8) = *(int*) (g_773da8 + 4);
	*(int*) (m + 0xc) = -1;
	*(int*) (m + 0x58) = -1;
	m[0x36] = 1;
	*(int*) (m + 0x9c) = 1000;
	*(stamp14*) (m + 0x28) = g_7f4c00;
	*(short*) (m + 0x2c) = 7;
	fcn_004c5530(m);
	return 1;
}
