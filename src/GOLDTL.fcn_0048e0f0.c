
#include <string.h>

extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_773d75;

char* __cdecl fcn_00508e40(int id);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_005100f0(int, int);
void __cdecl fcn_004c5530(char* msg);
typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 8

int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);

// FUNCTION: GOLDTL 0x48e0f0
// SIZE: 317
int __cdecl fcn_0048e0f0(char* a1, char* a2, char* a3)
{
	int found;
	char msg[0xf8];
	char* p;
	F8 f;

	p = fcn_00508e40(*(int*) (a2 + 0xc));
	if (p == 0) {
		return 0;
	}
	fcn_004c51a0(-1, *(int*) (a1 + 4), g_773d75, *(int*) (a3 + 8));
	fcn_005100f0(*(int*) (a1 + 4), -16);
	memset(msg, 0, sizeof(msg));
	msg[4] = (char) 0x99;
	*(int*) (msg + 8) = *(int*) (a1 + 4);
	*(int*) (msg + 0xc) = *(int*) (a2 + 0xc);
	*(int*) (msg + 0x28) = g_7f4c00;
	*(int*) (msg + 0x2c) = g_7f4c04;
	*(int*) (msg + 0x30) = g_7f4c08;
	*(short*) (msg + 0x34) = g_7f4c0c;
	msg[0x36] = 2;
	*(int*) (msg + 0x60) = *(int*) (p + 4);
	*(int*) (msg + 0x64) = -1;
	*(int*) (msg + 0x5c) = *(int*) (a2 + 0xc);
	*(int*) (msg + 0x68) = 4;
	*(int*) (msg + 0x6c) = 0;
	if (*(char**) (p + 0x170) != 0) {
		*(int*) (msg + 0x58) = *(int*) (*(char**) (p + 0x170) + 1);
	} else if (*(char**) (p + 0x16c) != 0) {
		*(int*) (msg + 0x58) = *(int*) (*(char**) (p + 0x16c) + 1);
	} else {
		found = -1;
		f.mask = 0x7b4c4a0;
		f.b = 0;
		fcn_004a5e60(p, 0, f, 0, 100.0f, &found);
		*(int*) (msg + 0x58) = found;
	}
	fcn_004c5530(msg);
	return 1;
}
