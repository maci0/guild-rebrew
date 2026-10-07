// FUNCTION: GOLD 0x00572260
// FUNCTION: GOLDTL 0x57a700

#include <string.h>

// SIZE 0xf8
#include "client_types.h"
struct msg {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x18];
	pos14_7f4c00 when;
	unsigned char code;
	char pad37[0x21];
	int who;
	int other;
	int value;
	char pad64[0x94];
};

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};

extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];

char* __cdecl fcn_005463a0(int, ...);
char* __cdecl fcn_005462a0(void);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_004c5530(struct msg*);
void __cdecl fcn_005100f0(int, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_0057a700(char* u)
{
	struct msg m;
	char* o;

	*(int*) (u + 0x70) = 0;
	if (u[0x78] & 4) {
		return;
	}
	*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
	for (o = fcn_005463a0(2, 0, 0x90, 3, *(int*) (u + 0x10)); o != 0; o = fcn_005462a0()) {
		if (o != u) {
			*(int*) (u + 0x84) = fcn_004c5620(-1, u);
			return;
		}
	}
	memset(&m, 0, sizeof(m));
	m.owner = *(int*) (u + 0xc);
	m.target = *(int*) (u + 0xac);
	m.when = g_7f4c00;
	m.kind = 0x91;
	m.code = 0xa;
	m.who = *(int*) (u + 4);
	m.other = -1;
	m.value = *(int*) (u + 0xb0);
	fcn_004c5530(&m);
	*(int*) (u + 0xb8) = 0;
	if (*(int*) (u + 0xb4) > 2) {
		*(int*) (u + 0xb4) = 2;
	}
	if (*(int*) (u + 0xb0) > 2) {
		*(int*) (u + 0xb0) = 2;
	}
	fcn_005100f0(((struct house*)g_7f4ca0)[*(unsigned short*) (u + 8)].owner, -((*(int*) (u + 0xb4) + 2) * (*(int*) (u + 0xb0) + 2)));
	fcn_00500bb0((pos14_7f4c00*) (u + 0x52), 0, 5, 0);
	fcn_004c5620(0, u);
}
