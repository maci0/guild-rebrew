#include <string.h>

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_773d75;

void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_004c5530(char* msg);

/* ADDRESS: GOLDTL 0x004abb10 */
int __cdecl fcn_004abb10(char* a0, char* a1)
{
	char msg[0xf8];

	fcn_004c5420(*(int*) (a0 + 4), 0x1cc, 4, 0x10, 0);
	fcn_004c51a0(-1, *(int*) (a0 + 4), (*(char*)&g_773d75), -*(int*) (a1 + 0x10));
	memset(msg, 0, sizeof(msg));
	msg[4] = (char) 0x9d;
	*(int*) (msg + 8) = *(int*) (a0 + 4);
	*(int*) (msg + 0xc) = -1;
	*(int*) (msg + 0x28) = (*(int*)&g_7f4c00);
	*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x30) = g_7f4c08;
	*(short*) (msg + 0x34) = g_7f4c0c;
	msg[0x36] = 2;
	*(int*) (msg + 0x58) = *(int*) (a1 + 0xc);
	*(int*) (msg + 0x5c) = *(int*) (a1 + 4);
	fcn_004c5530(msg);
	return 0x45;
}
