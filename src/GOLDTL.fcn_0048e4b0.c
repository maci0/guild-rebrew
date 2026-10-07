#include <string.h>

typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_773d75;

void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_004c5530(char* msg);
int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);

// FUNCTION: GOLD 0x48ef00
// FUNCTION: GOLDTL 0x0048e4b0
int __cdecl fcn_0048e4b0(char* a1, char* a2, char* a3)
{
	int found;
	char msg[0xf8];
	F8 f;

	fcn_004c51a0(-1, *(int*) (a1 + 4), (*(char*)&g_773d75), *(int*) (a3 + 8));
	memset(msg, 0, sizeof(msg));
	msg[4] = (char) 0x99;
	*(int*) (msg + 8) = *(int*) (a1 + 4);
	*(int*) (msg + 0xc) = *(int*) (a2 + 0xc);
	*(int*) (msg + 0x28) = (*(int*)&g_7f4c00);
	*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x30) = g_7f4c08;
	*(short*) (msg + 0x34) = g_7f4c0c;
	msg[0x36] = 2;
	*(int*) (msg + 0x5c) = *(int*) (a2 + 0xc);
	*(int*) (msg + 0x60) = -1;
	*(int*) (msg + 0x64) = -1;
	*(int*) (msg + 0x68) = 3;
	*(int*) (msg + 0x6c) = *(int*) (a3 + 0x10);
	found = -1;
	f.mask = 0x7b4c4a0;
	f.b = 0;
	fcn_004a5e60(a1, 0, f, 0, 100.0f, &found);
	*(int*) (msg + 0x58) = found;
	fcn_004c5530(msg);
	return 1;
}
