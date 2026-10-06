#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad[3];
	int f8;
	int fc;
	char pad2[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad3[0x21];
	char b58;
	char pad4[3];
	char b5c;
	char pad5[0x9b];
};

// FUNCTION: GOLD 0x005473c0
// FUNCTION: GOLDTL 0x54f340

void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_0054f340(char* o)
{
	*(pos14_7f4c00*) (o + 0x44) = g_7f4c00;
	*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 2, 0, 0);
}
