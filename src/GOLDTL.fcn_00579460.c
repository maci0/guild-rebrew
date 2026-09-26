// FUNCTION: GOLDTL 0x579460
// SIZE: 468

// SIZE 0x21c
struct house {
	char pad0[0x1cc];
	unsigned char flags;
	char pad1cd[0x4f];
};

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];
extern unsigned short g_774970;
extern int g_100f884;
extern int g_100f1dc;
extern char g_6a5a10[];
extern char g_6811b0[];
extern char g_6a7f1c[];

char* __cdecl fcn_00508e40(int);
void __cdecl fcn_00545780(char*);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_00500cb0(pos14_7f4c00*, char*);
void __cdecl fcn_00579410(char*, struct house*);
void __cdecl fcn_00579390(char*, struct house*);
int __cdecl fcn_00545670(char*, int, int, char*, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_004c30a0(int, int, char*, int, int);

void __cdecl fcn_00579460(char* u)
{
	char* h;
	char* p;

	p = u + 0xac;
	h = fcn_00508e40(*(int*) (u + 0xac));
	if (h == 0 || (((struct house*)g_7f4ca0)[*(unsigned short*) (u + 8)].flags & 1) != 0) {
		*(int*) (u + 0x70) = -2;
	}
	if (*(int*) (u + 0x70) == -2) {
		if (*(char**) (u + 0x74) != 0) {
			fcn_00545780(u);
		}
		fcn_00546190(u);
		return;
	}
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
		fcn_00519190(0x40fd, *(unsigned short*) h, *(int*) (u + 0xb8));
		fcn_004c30a0(-7, 0, g_6a7f1c, -1, 0);
		*(int*) (u + 0x70) = 1;
		break;
	case 1:
		if (fcn_00500cb0(&g_7f4c00, u + 0x52) > 0) {
			fcn_00579410(p, &((struct house*)g_7f4ca0)[g_774970]);
			fcn_00545780(u);
			fcn_00546190(u);
			break;
		}
		if (*(char**) (u + 0x74) == 0) {
			*(int*) (u + 0x70) = 0;
			return;
		}
		if (g_100f884 != *(int*) (*(char**) (u + 0x74) + 8) || g_100f1dc == -1) {
			return;
		}
		if (g_100f1dc == 2) {
			fcn_00579390(p, &((struct house*)g_7f4ca0)[g_774970]);
			fcn_00545780(u);
			fcn_00546190(u);
			return;
		}
		if (g_100f1dc == 1) {
			fcn_00579410(p, &((struct house*)g_7f4ca0)[g_774970]);
			fcn_00545780(u);
			fcn_00546190(u);
		}
		break;
	}
}
