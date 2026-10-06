// FUNCTION: GOLD 0x004afe80
// FUNCTION: GOLDTL 0x4affc0

#include <string.h>

typedef struct {
	short v[7];
} stamp14;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca4[];

void __cdecl fcn_004c5530(void*);

int __cdecl fcn_004affc0(void)
{
	char m[0xf8];
	char* p;

	memset(m, 0, sizeof(m));
	m[4] = 0x7f;
	*(stamp14*) (m + 0x28) = (*(stamp14*)&g_7f4c00);
	*(int*) (m + 0xc) = -1;
	*(short*) (m + 0x2c) = 8;
	*(int*) (m + 0x2e) = 0;
	m[0x36] = 1;
	for (p = g_7f4ca4; (int) p < (int) (g_7f4ca4 + 0x65400); p += 0x21c) {
		if (p[-2] == 6 || p[-2] == 7) {
			*(int*) (m + 8) = *(int*) p;
			*(int*) (m + 0x58) = *(int*) p;
			fcn_004c5530(m);
		}
	}
	return 1;
}
