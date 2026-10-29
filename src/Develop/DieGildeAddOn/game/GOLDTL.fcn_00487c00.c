#include <string.h>

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca4[];
extern unsigned char g_773d75;
extern char g_67e348[];

unsigned short __cdecl gm_RandomMod(int n);
struct unit;
struct unit* __cdecl fcn_005463a0(int n, ...);
void __cdecl fcn_004c4eb0(int a1);
void __cdecl fcn_004c5530(int a1);
void __cdecl fcn_004c5150(int a1, int a2, char a3, int a4);
void __cdecl fcn_004c4ef0(int a1);

/* ADDRESS: GOLDTL 0x00487c00 */
void __cdecl fcn_00487c00(char* a0, char* entity, int chance)
{
	unsigned char v[0xf8];

	if (a0 == 0) {
		return;
	}
	if ((*(unsigned int*) (entity + 0x1c8) & 8) != 0) {
		return;
	}
	if ((gm_RandomMod(100) & 0xffff) < chance) {
		return;
	}
	if (fcn_005463a0(2, 0, 0x13, 3, *(int*) (*(char**) (entity + 0x16c) + 1)) != 0) {
		return;
	}
	if (*(int*) (a0 + 0xe) >= 3) {
		return;
	}
	if (*(int*) (entity + 0x1b8) < 0x9600) {
		return;
	}
	memset(v, 0, 0xf8);
	v[4] = 0x13;
	*(int*) (v + 8) = *(int*) (g_7f4ca4 + *(unsigned short*) (*(char**) (entity + 0x16c) + 0x27) * 0x21c);
	*(int*) (v + 0xc) = *(int*) (*(char**) (entity + 0x16c) + 1);
	*(pos14_7f4c00*) (v + 0x28) = g_7f4c00;
	v[0x36] = 1;
	*(int*) (v + 0x58) = *(int*) (a0 + 2);
	*(int*) (v + 0x5c) = 1;
	*(int*) (v + 0x64) = 1;
	fcn_004c4eb0((int) g_67e348);
	fcn_004c5530((int) v);
	fcn_004c5150(-1, *(int*) (g_7f4ca4 + *(unsigned short*) (*(char**) (entity + 0x16c) + 0x27) * 0x21c), g_773d75, 0x3200);
	*(int*) (entity + 0x1b8) += -0x3200;
	fcn_004c4ef0((int) g_67e348);
	*(unsigned int*) (entity + 0x1c8) |= 8;
}
