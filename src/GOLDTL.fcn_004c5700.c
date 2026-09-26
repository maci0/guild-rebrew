#include "client_types.h"
// GLOBAL: GOLDTL 0x7f4c00
extern pos14_7f4c00 g_7f4c00;
// FUNCTION: GOLD 0x004c4d40
// SIZE: 112
// FUNCTION: GOLDTL 0x4c5700
// SIZE: 98

int __cdecl fcn_004c4330(void*);

typedef struct
{
	int a;
	int b;
	int c;
	short d;
} Quad4;
// SIZE 0x10

int __cdecl fcn_00500cb0(void*, char*);

int __cdecl fcn_004c5700(Quad4* a1)
{
	char buf[0x9c];

	if (fcn_00500cb0(a1, ((char*)&g_7f4c00)) == 0) {
		return -1;
	}
	buf[0] = 0x1e;
	*(int*) (buf + 0x10) = a1->a;
	*(int*) (buf + 0x14) = a1->b;
	*(int*) (buf + 0x18) = a1->c;
	*(short*) (buf + 0x1c) = a1->d;
	return fcn_004c4330(buf);
}
