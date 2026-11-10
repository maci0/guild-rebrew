#include <string.h>

#include "client_types.h"

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

extern pos14_7f4c00 g_7f4c00;
extern short g_7f4c0c;

int __cdecl fcn_004ae210(int);
void __cdecl fcn_004c5530(void*);

/* ADDRESS: GOLDTL 0x004b1a90 */
int __cdecl fcn_004b1a90(void)
{
	char msg[0xf8];
	stamp14 stamp;
	char* rec;
	int n;
	int sent;
	int id;

	stamp = *(stamp14*) &g_7f4c00;
	stamp.b = 0xa;
	stamp.c = 0;
	sent = 0;
	n = 0;
	rec = (char*) 0x7f4ca4;
	do {
		if (sent >= 8) {
			break;
		}
		if (fcn_004ae210(n) != 0) {
			memset(msg, 0, sizeof(msg));
			id = *(int*) rec;
			*(int*) (msg + 8) = id;
			*(int*) (msg + 0xc) = id;
			msg[4] = 0x55;
			msg[0x36] = 9;
			*(stamp14*) (msg + 0x28) = stamp;
			fcn_004c5530(msg);
			sent++;
		}
		n++;
		rec += 0x21c;
	} while ((int) rec < 0x85a0a4);
	return 1;
}
