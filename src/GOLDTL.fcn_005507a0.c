// FUNCTION: GOLDTL 0x5507a0

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
extern char g_7f4ca0[];
extern unsigned char g_773d75;
extern char* g_773da8;
extern int g_100f884;
extern int g_100f1dc;
extern float g_6652c8;
extern char g_6a5a10[];
extern char g_6811b0[];

int __cdecl fcn_00500cb0(pos14_7f4c00*, char*);
void __cdecl fcn_00545780(char*);
void __cdecl fcn_00546190(char*);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl fcn_004c5150(int, int, unsigned char, int);
void __cdecl fcn_0050fe40(unsigned short, int);
int __cdecl fcn_00545670(char*, int, int, char*, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);

void __cdecl fcn_005507a0(char* u)
{
	int v;

	if (*(int*) (u + 0x70) != -1 && *(int*) (u + 0x70) != -2) {
		if (fcn_00500cb0(&g_7f4c00, u + 0x44) == -1) {
			return;
		}
		switch (*(int*) (u + 0x70)) {
		case 0:
			v = (int) (gm_WalkEntityChain(*(unsigned short*) (u + 8)) * g_6652c8);
			if (*(char**) (u + 0x74) == 0) {
				fcn_00545670(u, 0, 0, g_6a5a10, 0x5ec);
			}
			fcn_004727a0(*(int*) (*(char**) (u + 0x74) + 8), 0);
			fcn_00519190((int) g_6811b0);
			fcn_00519190(0x10b1, *(unsigned short*) (u + 8), v);
			*(int*) (u + 0x70) = 1;
			break;
		case 1:
			if (*(char**) (u + 0x74) == 0) {
				*(int*) (u + 0x70) = 0;
				return;
			}
			if (g_100f884 != *(int*) (*(char**) (u + 0x74) + 8) || g_100f1dc == -1) {
				return;
			}
			if (g_100f1dc == 2) {
				fcn_004c5150(*(int*) (g_773da8 + 4), ((struct house*)g_7f4ca0)[*(unsigned short*) (u + 8)].owner, g_773d75,
				    (int) (gm_WalkEntityChain(*(unsigned short*) (u + 8)) * g_6652c8));
				fcn_0050fe40(*(unsigned short*) (u + 8), 8);
				fcn_00545780(u);
				fcn_00546190(u);
				return;
			}
			if (g_100f1dc == 1) {
				fcn_0050fe40(*(unsigned short*) (u + 8), -6);
				fcn_00545780(u);
				fcn_00546190(u);
			}
			break;
		}
	} else {
		if (*(char**) (u + 0x74) != 0) {
			fcn_00545780(u);
		}
		fcn_00546190(u);
	}
}
