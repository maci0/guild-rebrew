// FUNCTION: GOLD 0x004aff30
// FUNCTION: GOLDTL 0x4b0070

#include <string.h>

typedef struct {
	short v[7];
} stamp14;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char* g_773da8;

void __cdecl fcn_004c5530(void*);

int __cdecl fcn_004b0070(void)
{
	char m[0xf8];

	memset(m, 0, sizeof(m));
	m[4] = 0x7d;
	*(int*) (m + 8) = *(int*) (g_773da8 + 4);
	*(int*) (m + 0xc) = -1;
	m[0x36] = 1;
	*(int*) (m + 0x58) = 1;
	*(stamp14*) (m + 0x28) = (*(stamp14*)&g_7f4c00);
	*(short*) (m + 0x2c) = 8;
	*(int*) (m + 0x2e) = 0;
	fcn_004c5530(m);
	return 1;
}
