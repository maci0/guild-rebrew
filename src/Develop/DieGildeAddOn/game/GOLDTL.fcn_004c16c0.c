extern void fcn_004cd500();
extern void fcn_004ce090();
extern void fcn_004ce1a0();
extern void fcn_004ce1c0();
extern void fcn_004ce1d0();
extern void fcn_004ce2a0();
extern void fcn_004ce320();
extern void fcn_004c4450();
extern int fcn_00500e20();
extern void fcn_004237f0();
extern void fcn_00413d10();
extern int fcn_004234e0();
extern void fcn_00423890();
extern int fcn_0041fc10();
extern int fcn_00420840();
extern int fcn_00420780();
extern void fcn_00402ba0();
extern void fcn_00455350();
extern int fcn_00402c00();
extern void fcn_004193c0();
extern void fcn_00535960();
extern void fcn_0064d41a();
extern int fcn_0064d3f8();
extern int _ftol();

extern char *g_6b8300;
extern unsigned char g_772d10;
extern int g_6b7fac;
extern int g_772d4c;
extern char *g_772d48;
extern char *g_772d44;
extern char *g_6b8014;
extern char *g_7e4538;
extern char *g_773d78;
extern int g_772d30;
extern char *g_7746c4;
extern char *g_7746cc;
extern char *g_772d50;
extern char *lpGebaeudePROT;
extern char g_772b10;
extern float g_6628a0;
extern float g_662a18;
extern float g_664ea0;
extern float g_664e80;
extern char s_689e18[];
extern char s_689e68[];
extern char s_689dfc[];
extern char s_689ddc[];
extern char s_689dc0[];
extern char s_689f48[];
extern char s_689ee8[];
extern char s_689fac[];
extern char s_68a0d0[];
extern char s_68a0c4[];
extern char s_68a09c[];
extern char s_689ff0[];
extern char s_68a03c[];
extern char s_68a070[];
extern char s_689ee0[];
extern char s_689ed4[];
extern char s_689ec8[];
extern char s_689ebc[];
extern char s_68a124[];

/* ADDRESS: GOLDTL 0x004c16c0 */
int __cdecl fcn_004c16c0(void)
{
	char buf[16];
	int v2;
	int v5;
	int v6;
	int i;
	float f;
	char *p;

	if (g_6b8300 != 0 && g_772d10 != 0) {
		v5 = 0;
		v2 = g_6b7fac * 0xd;
		if (g_772d4c != fcn_00500e20(0x7f4c00)) {
			g_772d4c = fcn_00500e20(0x7f4c00);
			if (g_772d48 != 0) {
				fcn_004237f0(g_772d48, 0);
				*(int *) (g_772d48 + 0x18) = 0;
				g_772d48 = 0;
			}
			if (g_772d44 != 0) {
				fcn_004237f0(g_772d44, 0);
				*(int *) (g_772d44 + 0x18) = 0;
				g_772d44 = 0;
			}
		}
		fcn_00413d10(g_6b8014 + 0x4c);
		if (g_7e4538 != 0) {
			v5 = *(int *) g_7e4538;
		}
		v6 = g_772d4c * 100;
		if ((unsigned) (v2 - *(int *) (v6 + 0x681830)) >
		    (unsigned) (fcn_0064d3f8() % 2000 + *(int *) (v6 + 0x68182c))) {
			if (v5 <= 0x15e) {
				*(int *) (v6 + 0x681830) = v2;
				v6 = g_772d4c * 100;
				if (g_6628a0 < (float) fcn_0064d3f8() * g_662a18 +
				    *(float *) (v6 + 0x681820)) {
					fcn_004234e0(0, s_68a124,
					    fcn_0064d3f8() % *(int *) (g_772d4c * 100 + 0x681828) + 1,
					    0x3f,
					    (int) (*(float *) (v6 + 0x681824) * g_664e80),
					    0, 0);
				}
				if (7 <= fcn_0064d3f8() % 10) {
					fcn_004234e0(0, s_68a124,
					    fcn_0064d3f8() % *(int *) (g_772d4c * 100 + 0x681828) + 1,
					    0x3f,
					    (int) (*(float *) (g_772d4c * 100 + 0x681824) * g_664e80),
					    0, 0);
				}
			}
		}
		v6 = g_772d4c * 100;
		if ((unsigned) (v2 - *(int *) (v6 + 0x681844)) <=
		    (unsigned) (fcn_0064d3f8() % 2000 + *(int *) (v6 + 0x681840)) || v5 >= 100) {
			if (v5 >= 0x65 || g_772d4c == 3) {
				if (g_772d44 != 0) {
					fcn_0064d41a(&g_772b10, s_689f48, g_772d44);
					fcn_004237f0(g_772d44, 0);
					*(int *) (g_772d44 + 0x18) = 0;
					g_772d44 = 0;
				}
				if (g_772d48 != 0) {
					fcn_0064d41a(&g_772b10, s_689ee8, g_772d48);
					fcn_004237f0(g_772d48, 0);
					*(int *) (g_772d48 + 0x18) = 0;
					g_772d48 = 0;
				}
			}
			else {
				fcn_0064d41a(&g_772b10, s_689fac, g_772d48, g_772d44);
				if (g_772d44 != 0) {
					fcn_00423890(g_772d44, (int) (float) fcn_0064d3f8() / 2);
				}
				if (g_772d48 != 0) {
					fcn_00423890(g_772d48, (int) (float) fcn_0064d3f8() / 2);
				}
			}
		}
		else {
			*(int *) (v6 + 0x681844) = v2;
			if (g_6628a0 < (float) fcn_0064d3f8() * g_662a18 +
			    *(float *) (g_772d4c * 100 + 0x681834)) {
				if (g_772d48 != 0) {
					i = *(int *) (g_772d48 + 0xc);
					if (i > 2) {
						goto join;
					}
				}
				else {
					i = 0;
				}
				fcn_0064d41a(&g_772b10, s_68a0d0, g_772d48, i);
				g_772d48 = fcn_004234e0(0, s_68a0c4,
				    fcn_0064d3f8() % *(int *) (g_772d4c * 100 + 0x68183c) + 2, 0x3f,
				    (int) (float) (fcn_0064d3f8() / 2), 0, 0);
				fcn_0064d41a(&g_772b10, s_68a09c, g_772d48);
			}
join:
			if (g_772d4c != 1) {
				if (g_772d44 != 0) {
					fcn_0064d41a(&g_772b10, s_689ff0, g_772d44);
					fcn_004237f0(g_772d44, 0);
					g_772d44 = 0;
				}
			}
			else if (g_772d44 != 0) {
				fcn_00423890(g_772d44, (int) (float) fcn_0064d3f8() / 2);
				fcn_0064d41a(&g_772b10, s_68a03c, g_772d44);
			}
			else {
				g_772d44 = fcn_004234e0(0, s_68a0c4, 0, 0x3f,
				    (int) (float) fcn_0064d3f8() / 2, 0, 0);
				fcn_0064d41a(&g_772b10, s_68a070, g_772d44);
			}
		}
		v6 = g_772d4c * 100;
		if ((unsigned) (fcn_0064d3f8() % 2000 + *(int *) (v6 + 0x68187c)) <
		    (unsigned) (v2 - *(int *) (v6 + 0x681880))) {
			*(int *) (v6 + 0x681880) = v2;
			v6 = g_772d4c * 100;
			if (g_6628a0 < (float) fcn_0064d3f8() * g_662a18 +
			    *(float *) (v6 + 0x681820)) {
				fcn_004234e0(0, s_689ee0, 1, 0x3f,
				    (int) (float) fcn_0064d3f8() / 2, 0, 0);
			}
		}
		v6 = g_772d4c * 100;
		if ((unsigned) (fcn_0064d3f8() % 2000 + *(int *) (v6 + 0x681868)) <
		    (unsigned) (v2 - *(int *) (v6 + 0x68186c))) {
			*(int *) (v6 + 0x68186c) = v2;
			if (g_6628a0 < (float) fcn_0064d3f8() * g_662a18 +
			    *(float *) (g_772d4c * 100 + 0x68185c)) {
				p = s_689ed4;
				if (5 <= fcn_0064d3f8() % 10) {
					p = s_689ec8;
				}
				fcn_004234e0(0, p, 1, 0x3f, (int) (float) fcn_0064d3f8() / 2, 0, 0);
			}
		}
		v6 = g_772d4c * 100;
		if ((unsigned) (fcn_0064d3f8() % 2000 + *(int *) (v6 + 0x681854)) <
		    (unsigned) (v2 - *(int *) (v6 + 0x681858))) {
			*(int *) (v6 + 0x681858) = v2;
			v6 = g_772d4c * 100;
			if (g_6628a0 < (float) fcn_0064d3f8() * g_662a18 +
			    *(float *) (v6 + 0x681848)) {
				fcn_004234e0(0, s_689ebc,
				    fcn_0064d3f8() % *(int *) (g_772d4c * 100 + 0x681850) + 1,
				    0x3f,
				    (int) (*(float *) (g_772d4c * 100 + 0x681834) * g_664e80), 0, 0);
			}
		}
		if (g_772d30 != 0 && g_773d78 != 0) {
			fcn_00455350(*(int *) (g_773d78 + 0x61),
			    *(int *) (g_773d78 + 0x61) + 0x4c, buf);
			i = fcn_00402c00(0, 0, buf, 0x44610000) * 0x14;
			if (i >= 0x7f) {
				i = 0x7f;
			}
			fcn_004193c0(g_772d30, i);
		}
	}
	else {
		v5 = g_6b7fac * 0xd;
		if (g_772d4c != fcn_00500e20(0x7f4c00)) {
			g_772d4c = fcn_00500e20(0x7f4c00);
		}
		if (g_772d44 != 0) {
			fcn_0064d41a(&g_772b10, s_689e68, g_772d44);
			fcn_004237f0(g_772d44, 0);
			*(int *) (g_772d44 + 0x18) = 0;
			g_772d44 = 0;
		}
		if (g_772d48 != 0) {
			fcn_0064d41a(&g_772b10, s_689e18, g_772d48);
			fcn_004237f0(g_772d48, 0);
			*(int *) (g_772d48 + 0x18) = 0;
			g_772d48 = 0;
		}
		v2 = g_772d4c * 100;
		*(int *) (v2 + 0x681830) = v5;
		*(int *) (v2 + 0x681844) = v5;
		*(int *) (v2 + 0x68186c) = v5;
		*(int *) (v2 + 0x681858) = v5;
		*(int *) (v2 + 0x681880) = v5;
	}
	if (g_7746c4 != 0 && g_772d10 != 0) {
		i = *(unsigned char *) (lpGebaeudePROT + (unsigned) *g_7746c4 * 0x24d);
		if (i == 0x16 && (g_7746cc != 0 && *g_7746cc == 0x120)) {
			if (g_772d50 != 0) {
				fcn_00402ba0(g_6b8014, 0);
				return fcn_0041fc10(g_772d50, 0);
			}
			g_772d50 = fcn_00420780(s_689dfc, 5);
			return 0;
		}
		if (i != 0x12 && i != 0x14 && i != 8 && i != 0x15 && i != 0x0e) {
			if (i != 7 || g_7746cc == 0 || *g_7746cc != 0xf7) {
				goto label;
			}
			fcn_00402ba0(g_6b8014, 0);
			if (g_772d50 == 0) {
				g_772d50 = fcn_00420780(s_689ddc, 5);
				return 0;
			}
			return fcn_0041fc10(g_772d50, 0);
		}
		fcn_00402ba0(g_6b8014, 0);
		if (g_772d50 == 0) {
			if (*(int *) (g_7746c4 + 0x95) == -1) {
				return 0;
			}
			g_772d50 = fcn_00420780(s_689dc0, 0);
			return 0;
		}
		if (*(int *) (g_7746c4 + 0x95) == -1) {
			fcn_00420840(g_772d50);
			g_772d50 = 0;
			return 0;
		}
		return fcn_0041fc10(g_772d50, 0);
	}
label:
	if (g_772d50 == 0) {
		return 0;
	}
	fcn_00420840(g_772d50);
	g_772d50 = 0;
	return 0;
}
