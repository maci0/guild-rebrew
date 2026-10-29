


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
extern char g_77670b;
extern char g_77e020[];
extern char* g_14ad590[];
extern unsigned short g_774970;
extern char g_7f4ca0[];

int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00570250(char* u)
{
	switch (*(int*) (u + 0x70)) {
	case -2:
	case -1:
		fcn_00546190(u);
		break;
	case 0:
		if (g_77670b != 0) {
			fcn_00545d40(((struct house*)g_7f4ca0)[g_774970].owner, -1, g_14ad590[((int*)g_77e020)[*(int*) (u + 0xac)]], 0, 0x5f9, 0);
			(*(int*) (u + 0xac))++;
			if (*(int*) (u + 0xac) > 0x1a) {
				*(int*) (u + 0x70) = 1;
			}
			*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (u + 0x52), gm_RandomMod(4) + 8, 0, 0);
		} else {
			*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (u + 0x52), 1, 0, 0);
		}
		break;
	}
}
