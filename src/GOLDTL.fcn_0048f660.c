#include <string.h>

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

void __cdecl fcn_004c5530(char* msg);

/* ADDRESS: GOLD 0x004900b0 */
/* ADDRESS: GOLDTL 0x0048f660 */
int __cdecl fcn_0048f660(char* a1, char* a2, int a3, char* p)
{
	char msg[0xf8];

	memset(msg, 0, sizeof(msg));
	msg[4] = (char) 0x88;
	msg[0x36] = 2;
	*(int*) (msg + 8) = *(int*) (a1 + 4);
	*(int*) (msg + 0xc) = *(int*) (a2 + 1);
	*(int*) (msg + 0x28) = (*(int*)&g_7f4c00);
	*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x30) = g_7f4c08;
	*(short*) (msg + 0x34) = g_7f4c0c;
	*(int*) (msg + 0x5c) = *(int*) (p + 0xc);
	*(int*) (msg + 0x60) = *(int*) (p + 4);
	*(int*) (msg + 0x64) = *(int*) (p + 0x10);
	*(int*) (msg + 0x58) = *(int*) (p + 8);
	*(int*) (msg + 0x38) = *(int*) (p + 4);
	fcn_004c5530(msg);
	return 0x3d;
}
