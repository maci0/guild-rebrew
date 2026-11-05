#include <string.h>

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern short g_7f4c0c;

int __cdecl fcn_004ae210(int);
void __cdecl fcn_004c5530(void*);

/* ADDRESS: GOLDTL 0x004b1a90 */
int __cdecl fcn_004b1a90(void)
{
	char msg[0xf8];
	int mode;
	char* rec;
	int n;
	int sent;

	mode = 0xa;
	n = 0;
	sent = 0;
	rec = (char*) 0x7f4ca4;
	while (sent < 8 && (int) rec < 0x85a0a4) {
		if (fcn_004ae210(n) != 0) {
			memset(msg, 0, sizeof(msg));
			msg[4] = 0x55;
			*(int*) (msg + 8) = *(int*) rec;
			*(int*) (msg + 0xc) = *(int*) rec;
			*(int*) (msg + 0x28) = *(int*) &g_7f4c00;
			*(int*) (msg + 0x2c) = mode;
			*(int*) (msg + 0x30) = 0;
			*(short*) (msg + 0x34) = g_7f4c0c;
			msg[0x36] = 9;
			fcn_004c5530(msg);
			sent++;
		}
		n++;
		rec += 0x21c;
	}
	return 1;
}
