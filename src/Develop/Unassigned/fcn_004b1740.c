void *memset(void *, int, unsigned int);
int __cdecl fcn_004ae170(int);
int __cdecl fcn_004c5530(void *);

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

#pragma pack(2)
typedef struct
{
	int a;
	short b;
	int c;
	int d;
} stamp14;
#pragma pack()
// SIZE 0xe

/* ADDRESS: GOLDTL 0x004b1740 */
int __cdecl fcn_004b1740(void)
{
	char msg[0xf8];
	stamp14 stamp;
	char* rec;
	int i;
	int id;

	stamp = *(stamp14*) &g_7f4c00;
	memset(msg, 0, sizeof(msg));
	stamp.c = 0;
	i = 0;
	rec = (char*) 0x7f4ca4;
	do {
		if (fcn_004ae170(i) != 0) {
			memset(msg, 0, sizeof(msg));
			stamp.b = (short) (i % 4 + 0xa);
			id = *(int*) rec;
			*(int*) (msg + 8) = id;
			*(int*) (msg + 0xc) = id;
			msg[4] = 0x57;
			msg[0x36] = 1;
			*(stamp14*) (msg + 0x28) = stamp;
			fcn_004c5530(msg);
		}
		rec += 0x21c;
		i++;
	} while ((int) rec < 0x85a0a4);
	return 1;
}
