// FUNCTION: GOLD 0x0055cd50
// SIZE: 262
// FUNCTION: GOLDTL 0x564fc0
// SIZE: 262

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
	char pad5c[0x9c];
};

extern pos14_7f4c00 g_7f4c00;

char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c5530(struct msg*);
void __cdecl fcn_004c6470(int, int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00564fc0(char* u)
{
	struct msg m;
	char* h;

	switch (*(int*) (u + 0x70)) {
	case -2:
	case -1:
		fcn_00546190(u);
		break;
	case 0:
		(*(int*) (u + 0xb8))--;
		h = fcn_00508e40(*(int*) (u + 0xac));
		if (*(int*) (u + 0xb8) < 0 && h != 0) {
			if (h[2] == 6 || h[2] == 7) {
				memset(&m, 0, sizeof(m));
				m.kind = 0x26;
				m.target = -1;
				m.code = 9;
				m.owner = *(int*) (u + 0xac);
				m.when = g_7f4c00;
				m.who = *(int*) (u + 0xac);
				fcn_004c5530(&m);
			}
			fcn_004c6470(*(int*) (h + 4), *(unsigned char*) (h + 0x164) - 1);
			fcn_00546190(u);
		}
		break;
	}
}
