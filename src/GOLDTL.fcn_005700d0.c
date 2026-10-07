// FUNCTION: GOLD 0x00567d20
// FUNCTION: GOLDTL 0x5700d0

// SIZE 0x10
struct step {
	int when;
	short dur;
	short pad;
	int arg;
	int msg;
};

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_77e0a0[];
extern char g_776709;
extern unsigned short g_774970;
extern char g_7f4ca0[];
extern char* g_14a5320[];

int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_005700d0(char* u)
{
	int t;

	switch (*(int*) (u + 0x70)) {
	case -2:
	case -1:
		fcn_00546190(u);
		break;
	case 0:
		t = ((struct step*)g_77e0a0)[*(int*) (u + 0xac)].msg;
		if (t != 0 && t != -1 && g_776709 != 0) {
			fcn_00545d40(((struct house*)g_7f4ca0)[g_774970].owner, -1, g_14a5320[t], 0x40, 0x5f9, 0);
		}
		(*(int*) (u + 0xac))++;
		if (((struct step*)g_77e0a0)[*(int*) (u + 0xac)].msg == 0) {
			*(int*) (u + 0x70) = 1;
			return;
		}
		*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
		*(int*) (u + 0x52) = ((struct step*)g_77e0a0)[*(int*) (u + 0xac)].when;
		*(short*) (u + 0x56) = ((struct step*)g_77e0a0)[*(int*) (u + 0xac)].dur;
		*(int*) (u + 0x58) = ((struct step*)g_77e0a0)[*(int*) (u + 0xac)].arg;
		break;
	}
}
