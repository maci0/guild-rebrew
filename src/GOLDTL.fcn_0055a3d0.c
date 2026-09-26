// FUNCTION: GOLDTL 0x55a3d0
// SIZE: 358

// SIZE 0x2f4

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern trade_868080 g_868080[];
extern unsigned char g_773d75;
extern int g_100f884;
extern int g_100f1dc;
extern char g_6a5a10[];
extern char g_6811b0[];

int __cdecl fcn_00500cb0(pos14_7f4c00*, char*);
void __cdecl fcn_00545780(char*);
void __cdecl fcn_00546190(char*);
char* __cdecl fcn_005463a0(int, ...);
int __cdecl fcn_00545670(char*, int, int, char*, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);

void __cdecl fcn_0055a3d0(char* u)
{
	char* o;

	if (*(int*) (u + 0x70) != -1 && *(int*) (u + 0x70) != -2) {
		switch (*(int*) (u + 0x70)) {
		case 0:
			if (*(char**) (u + 0x74) == 0) {
				fcn_00545670(u, 0, 0, g_6a5a10, 0x5ec);
			}
			if (*(char**) (u + 0x74) == 0) {
				fcn_00546190(u);
				return;
			}
			fcn_00471b60(*(int*) (*(char**) (u + 0x74) + 8));
			fcn_004727a0(*(int*) (*(char**) (u + 0x74) + 8), 0);
			fcn_00519190((int) g_6811b0);
			fcn_00519190(0x10b9, &g_868080[g_773d75], *(unsigned short*) (u + 8));
			*(int*) (u + 0x70) = 1;
			break;
		case 1:
			if (fcn_00500cb0(&g_7f4c00, u + 0x52) > 0) {
				fcn_00545780(u);
				fcn_00546190(u);
				return;
			}
			if (*(char**) (u + 0x74) == 0) {
				*(int*) (u + 0x70) = 0;
				return;
			}
			if (g_100f884 != *(int*) (*(char**) (u + 0x74) + 8) || g_100f1dc == -1) {
				return;
			}
			if (g_100f1dc == 2) {
				o = fcn_005463a0(2, 2, *(unsigned short*) (u + 8), 1, *(int*) (u + 0xb0));
				*(int*) (o + 0xb0) = 1;
				fcn_00545780(u);
				fcn_00546190(u);
				return;
			}
			if (g_100f1dc == 1) {
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
