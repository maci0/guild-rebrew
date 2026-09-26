// FUNCTION: GOLD 0x005426d0
// SIZE: 246
// FUNCTION: GOLDTL 0x54a5a0
// SIZE: 246

#pragma pack(1)
// SIZE 0x7
struct target7 {
	char a;
	char b;
	int id;
	char c;
};
#pragma pack()

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_005015e0(char**, int, int, int);
void __cdecl fcn_004c5620(int, char*);
int __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_004c5b00(int, struct target7);

void __cdecl fcn_0054a5a0(char* u)
{
	char* found;
	struct target7 t;

	found = 0;
	if (u[0x78] & 4) {
		return;
	}
	*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (u + 0x52), 0x18, 0, 0);
	*(short*) (u + 0x56) = 7;
	*(int*) (u + 0x58) = 0;
	fcn_005015e0(&found, 0, 0, *(int*) (u + 0x10));
	if (found == 0) {
		fcn_004c5620(-1, u);
		return;
	}
	if (fcn_00502cd0(*(int*) (found + 0x5d), 1, 0, 0x1b5) == 0) {
		t.a = -1;
		t.b = -1;
		t.id = -1;
		fcn_004c5b00(*(int*) (found + 1), t);
	}
	*(int*) (u + 0x84) = -1;
	fcn_004c5620(0, u);
}
