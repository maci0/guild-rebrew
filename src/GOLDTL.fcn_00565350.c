#include <stdio.h>

extern unsigned short g_774970;
extern unsigned char g_774964;
extern unsigned char g_773d75;
extern int g_100f1dc;

int __cdecl fcn_00500cb0(void*, void*);
int __cdecl fcn_00508e40(int);
int __cdecl fcn_00507b00(int);
int __cdecl fcn_00507d10(int);
void __cdecl fcn_00545670(char*, int, int, char*, int);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00519190(int, ...);
void __cdecl fcn_004c6470(int, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
int __cdecl fcn_00422700(char*);
void __cdecl fcn_004c30a0(int, int, char*, int, int);
void __cdecl fcn_00545780(int);

/* ADDRESS: GOLDTL 0x00565350 */
void __cdecl fcn_00565350(int a0)
{
	unsigned char* ent;
	char* p;
	int* slot;
	char buf[1024];
	char name[64];
	char* s;
	int x;
	int y;
	int z;
	int kind;
	int v;
	int v6;
	int v7;
	int v8;
	int v9;
	int i;

	if (g_774970 != *(short*) (a0 + 8))
		return;
	if (!g_774964)
		return;
	if (0 < fcn_00500cb0((void*) (a0 + 0x44), (void*) 0x7f4c00))
		return;
	if (!*(char*) (a0 + 0xb1)) {
		v = fcn_00508e40(*(unsigned int*) (a0 + 0xac));
		if (v) {
			*(char*) (a0 + 0xb0) = *(char*) (v + 0x164);
			*(char*) (a0 + 0xb1) = *(char*) (v + 0x164) - 1;
		}
	}
	switch (*(int*) (a0 + 0x70)) {
	case 0:
		fcn_00545670((char*) a0, 0, 0, "Berufe\\Meisterpruefung_BESTANDEN", 0x5ec);
		if (!*(int*) (a0 + 0x74)) {
			fcn_00546190((char*) a0);
			return;
		}
		fcn_004727a0(*(int*) (*(int*) (a0 + 0x74) + 8), 0);
		fcn_00471b60(*(int*) (*(int*) (a0 + 0x74) + 8));
		ent = (unsigned char*) fcn_00508e40(*(unsigned int*) (a0 + 0xac));
		y = (-(*(char*) (ent + 9) != 0) & 0x5f) + 0x130;
		x = fcn_00507b00(*(char*) (a0 + 0xb0));
		z = fcn_00507d10(*(char*) (a0 + 0xb0));
		fcn_004727a0(*(int*) (*(int*) (a0 + 0x74) + 8), 1);
		v7 = (int) ((float) z * 0.5 + (float) (3 * x + 0x155a));
		fcn_00519190(0x15c3, g_773d75 * 0x2f4 + (int) 0x868080, (int) 0x7f4c00,
			*(unsigned char*) (a0 + 0xb1) + y, v7);
		fcn_004c6470(*(int*) (ent + 4), *(char*) (a0 + 0xb1));
		kind = *(char*) (ent + 2);
		if (kind == 6 || kind == 7 || kind == 5) {
			fcn_0051af00(buf, 0x1c1f, *(unsigned short*) ent,
				*(unsigned char*) (a0 + 0xb0) + y, *(unsigned char*) (a0 + 0xb1) + y);
			for (p = (char*) 0x7f4ca4; (int) p < 0x85a0a4; p += 0x21c) {
				kind = *(char*) (p - 2);
				if ((kind == 6 || kind == 7) && *(int*) p != *(int*) (ent + 4))
					fcn_00545d40(*(int*) p, -1, buf, 0, 0x5fe, 0);
			}
			*(unsigned int*) (ent + 0x1c8) &= 0x7fffffff;
		}
		*(int*) (a0 + 0x70) = *(int*) (a0 + 0x70) + 1;
		return;
	case 1:
		ent = (unsigned char*) fcn_00508e40(*(unsigned int*) (a0 + 0xac));
		x = fcn_00507b00(*(char*) (a0 + 0xb0));
		v6 = fcn_00507d10(*(char*) (a0 + 0xb0));
		sprintf(name, "brk_%02i", x);
		v7 = fcn_00422700("BERUF_BESTANDEN");
		if (0xd <= x) {
			if (*(char*) (ent + 9))
				s = "ADDON_BERUF_LISTE_WEIBLICH";
			else
				s = "ADDON_BERUF_LISTE_MAENNLICH";
			v = fcn_00422700(s);
			v8 = fcn_00422700("ADDON_GEBAEUDE_LISTE");
			v9 = fcn_00422700("ADDON_BERUFE_VEREINIGUNG_UNTERSCHRIFT");
		} else {
			if (*(char*) (ent + 9))
				s = "BERUF_LISTE_WEIBLICH";
			else
				s = "BERUF_LISTE_MAENNLICH";
			v = fcn_00422700(s);
			v8 = fcn_00422700("GEBAEUDE_LISTE");
			v9 = fcn_00422700("BERUFE_VEREINIGUNG_UNTERSCHRIFT");
		}
		i = fcn_00422700(s);
		if (v6 + 1 >= 3) {
			if (v6 + 1 >= 5)
				s = "FanfarePositivLang";
			else
				s = "FanfarePositivMittel";
		} else {
			s = "FanfarePositivKurz";
		}
		fcn_004c30a0(-7, 0, s, -1, 0);
		fcn_004c30a0(-6, v7, "SELBST", 1, 0);
		fcn_004c30a0(-8, v, name, v6 - 1, 0);
		fcn_004c30a0(-6, v7, "SELBST", 0, 0);
		fcn_004c30a0(-8, v8, name, (int) (3.0 - (double) v6 * 0.5), 0);
		fcn_004c30a0(-6, v7, "GEZEICHNET", -1, 0);
		if (0xd <= x)
			x -= 0xd;
		else
			x -= 1;
		fcn_004c30a0(-8, v9, "_BERUFE_VEREINIGUNG_UNTERSCHRIFT", x, 0);
		fcn_004c30a0(-7, 0, "MausclickLinks_s_01", -1, 0);
		*(int*) (a0 + 0x70) = *(int*) (a0 + 0x70) + 1;
		return;
	case 2:
		break;
	case 0xfffffffe:
	case 0xffffffff:
		fcn_00545780(a0);
		fcn_00546190((char*) a0);
		return;
	default:
		return;
	}
	slot = (int*) *(int*) (a0 + 0x74);
	if (!slot) {
		*(unsigned int*) (a0 + 0x70) = 0;
		return;
	}
	if (*(int*) 0x100f884 != slot[2]) {
		if (!*(char*) 0x7749e8)
			return;
		if (*(int*) 0x7749e4 != (int) slot)
			return;
	}
	if (*(int*) 0x100f1dc != -1) {
		if (*(int*) 0x100f1dc == 2) {
			fcn_00545780(a0);
			fcn_00546190((char*) a0);
			return;
		}
		if (*(int*) 0x100f1dc == 1) {
			fcn_00545780(a0);
			fcn_00546190((char*) a0);
			*(char*) 0x7749e8 = 0;
			return;
		}
	} else {
		if (!*(char*) 0x7749e8)
			return;
		if (*(int*) 0x7749e4 != (int) slot)
			return;
	}
	if (!*(char*) 0x7749e8)
		return;
	fcn_00545780(a0);
	fcn_00546190((char*) a0);
	*(char*) 0x7749e8 = 0;
}
