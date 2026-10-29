


#include <string.h>

typedef struct {
	short v[7];
} stamp14;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca4[];

int __cdecl fcn_004ae170(int);
void __cdecl fcn_004c5530(void*);

int __cdecl fcn_004b1820(void)
{
	stamp14 st;
	char m[0xf8];
	int i;

	st = (*(stamp14*)&g_7f4c00);
	memset(m, 0, sizeof(m));
	*(int*) ((char*) &st + 6) = 0;
	for (i = 0; i < 0x300; i++) {
		if (fcn_004ae170(i) != 0) {
			memset(m, 0, sizeof(m));
			st.v[2] = i % 4 + 0xd;
			m[4] = 0x58;
			*(int*) (m + 8) = *(int*) (g_7f4ca4 + i * 0x21c);
			*(int*) (m + 0xc) = *(int*) (g_7f4ca4 + i * 0x21c);
			m[0x36] = 1;
			*(stamp14*) (m + 0x28) = st;
			fcn_004c5530(m);
		}
	}
	return 1;
}
