#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char s_67fb50[];

void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c6ae0(int id, int k);
void __cdecl fcn_004c4ef0(char* s);

// FUNCTION: GOLD 0x4aaae0
// SIZE: 162
// FUNCTION: GOLDTL 0x4aac00
// SIZE: 162
int __cdecl fcn_004aac00(char* a1, int a2, char* x)
{
	char msg[0xf8];

	*(int*) (msg + 8) = *(int*) (x + 8);
	*(int*) (msg + 0x5c) = *(int*) (a1 + 4);
	*(int*) (msg + 0x58) = *(int*) (x + 4);
	*(int*) (msg + 0x60) = *(int*) (x + 8);
	*(int*) (msg + 0x28) = (*(int*)&g_7f4c00);
	msg[4] = 0x2f;
	*(int*) (msg + 0xc) = -1;
	msg[0x36] = 1;
	*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x30) = g_7f4c08;
	*(short*) (msg + 0x34) = g_7f4c0c;
	fcn_004c4eb0(s_67fb50);
	fcn_004c5530(msg);
	fcn_004c6ae0(*(int*) (a1 + 4), -3);
	fcn_004c4ef0(s_67fb50);
	return 1;
}
