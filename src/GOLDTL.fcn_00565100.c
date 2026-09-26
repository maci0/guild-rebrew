// FUNCTION: GOLDTL 0x565100
// SIZE: 492

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern int g_100f884;
extern int g_100f1dc;
extern char g_6a5a10[];
extern char g_6b5c60[];

int __cdecl fcn_00500cb0(pos14_7f4c00*, char*);
int __cdecl fcn_00545670(char*, int, int, char*, int);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_00545780(char*);
char* __cdecl fcn_00508e40(int);
int __cdecl fcn_00507d10(int);
int __cdecl fcn_00507b00(int);
int __cdecl fcn_00422700(char*);
void __cdecl fcn_004c30a0(int, int, char*, int, int);
int __cdecl fcn_00519190(int, ...);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_00526920(char*, int, char*);

void __cdecl fcn_00565100(char* u)
{
	char* h;
	int lvl;
	int n;
	int r;
	int text;
	char* q;

	if (fcn_00500cb0(&g_7f4c00, u + 0x52) < 0) {
		return;
	}
	switch (*(int*) (u + 0x70)) {
	case 0:
		fcn_00545670(u, 0, 0, g_6a5a10, 0x5fd);
		if (*(char**) (u + 0x74) == 0) {
			fcn_00546190(u);
			return;
		}
		h = fcn_00508e40(*(int*) (u + 0xac));
		if (h != 0) {
			lvl = fcn_00507d10(*(unsigned char*) (h + 0x164)) + 1;
			text = h[9] ? 0x15ab : 0x159b;
			n = fcn_00507b00(*(unsigned char*) (h + 0x164));
			if (h[9] == 0) {
				if (n <= 0xc) {
					r = fcn_00422700("BERUF_TRAINING_SPIELER_MAENNLICH");
					fcn_004c30a0(-8, r, "BERUF_TRAINING_SPIELER_MAENNLICH", n - 1, 0);
				} else {
					r = fcn_00422700("ADDON_BERUF_TRAINING_SPIELER_MAENNLICH");
					fcn_004c30a0(-8, r, "BERUF_TRAINING_SPIELER_MAENNLICH", n - 0xd, 0);
				}
			} else if (n <= 0xc) {
				r = fcn_00422700("BERUF_TRAINING_SPIELER_WEIBLICH");
				fcn_004c30a0(-8, r, "BERUF_TRAINING_SPIELER_WEIBLICH", n - 1, 0);
			} else {
				r = fcn_00422700("ADDON_BERUF_TRAINING_SPIELER_WEIBLICH");
				fcn_004c30a0(-8, r, "BERUF_TRAINING_SPIELER_WEIBLICH", n - 0xd, 0);
			}
			fcn_00519190(0x159a, *(unsigned short*) h, lvl + 0x1556, n + text, 4);
		}
		(*(int*) (u + 0x70))++;
		break;
	case 1:
		if (g_100f884 != *(int*) (*(char**) (u + 0x74) + 8) || g_100f1dc == -1) {
			break;
		}
		if (g_100f1dc == 2) {
			h = fcn_00508e40(*(int*) (u + 0xac));
			if (*(char**) (h + 0x170) != 0) {
				q = fcn_00502cd0(*(int*) (*(char**) (h + 0x170) + 0x5d), 2, 0, 0x13, 6);
				fcn_00526920(*(char**) (h + 0x170), *(int*) (q + 2), g_6b5c60);
			}
			fcn_00545780(u);
			fcn_00546190(u);
			return;
		} else if (g_100f1dc != 1) {
			break;
		}
	case -2:
	case -1:
		fcn_00545780(u);
		fcn_00546190(u);
		break;
	}
}
