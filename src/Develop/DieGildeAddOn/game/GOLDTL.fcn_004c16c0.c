extern float fcn_00413d10(float *pos);
extern int fcn_00500e20(int *p);
extern int *fcn_004234e0(char *bank, char *name, int loop, int pan, int vol,
    int a, int b);
extern void fcn_00423890(int *voice, int vol);
extern void fcn_004237f0(int *voice, int a2);
extern void fcn_0064d41a();
extern int fcn_0064d3f8(void);
extern int fcn_00402ba0(int a, int b);
extern int fcn_00402c00(int a, int b, char *buf, int d);
extern void fcn_00455350(int a, int b, char *buf);
extern void fcn_004193c0(int a, int b);
extern int fcn_0041fc10(int handle, int value);
extern int fcn_00420780(char *name, int value);
extern void fcn_00420840(int handle);

extern char *g_6b8300;
extern unsigned char g_772d10;
extern int g_6b7fac;
extern int g_6b8010;
extern char *g_6b8014;
extern int g_772d4c;
extern int *g_772d48;
extern int *g_772d44;
extern int g_772d50;
extern int g_772d30;
extern unsigned char *g_7746c4;
extern short *g_7746cc;
extern int *g_773d78;
extern int *g_7e4538;
extern unsigned char *lpGebaeudePROT;
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

#define flt_64 (*(float *) 0x662928)
#define flt_time_scale (*(float *) 0x662a80)

/* ADDRESS: GOLDTL 0x004c16c0 */
int __cdecl fcn_004c16c0(void)
{
	char buf[16];
	int v2;
	int v5;
	int v6;
	int i;
	float f;
	float fv;
	unsigned char c;
	unsigned char *p;

	if (g_6b8300 != 0 && g_772d10 != 0) {
		v5 = 0;
		v2 = (*(volatile int *) &g_6b7fac + *(volatile int *) &g_6b7fac * 2) * 4
		    + *(volatile int *) &g_6b7fac;
		if (g_772d4c != fcn_00500e20((int *) 0x7f4c00)) {
			g_772d4c = fcn_00500e20((int *) 0x7f4c00);
			if (g_772d48 != 0) {
				fcn_004237f0(g_772d48, 0);
				*(int *) ((char *) g_772d48 + 0x18) = 0;
				g_772d48 = 0;
			}
			if (g_772d44 != 0) {
				fcn_004237f0(g_772d44, 0);
				*(int *) ((char *) g_772d44 + 0x18) = 0;
				g_772d44 = 0;
			}
		}
		f = (g_664ea0 - *(float *) (g_6b8014 + 0x50)
		    - fcn_00413d10((float *) (g_6b8014 + 0x4c))) * flt_time_scale;
		if (g_7e4538 != 0) {
			v5 = *g_7e4538;
		}
		v6 = g_772d4c * 100;
		if ((unsigned) (v2 - *(int *) (v6 + 0x681830)) >
		    (unsigned) (fcn_0064d3f8() % 2000 + *(int *) (v6 + 0x68182c))) {
			if (v5 < 0x15e) {
				*(int *) (v6 + 0x681830) = v2;
				v6 = g_772d4c * 100;
				if (g_6628a0 < (float) fcn_0064d3f8() * g_662a18
				    + *(float *) (v6 + 0x681820)) {
					fcn_004234e0(0, s_68a124,
					    fcn_0064d3f8() % *(int *) (g_772d4c * 100 + 0x681828) + 1,
					    0x3f,
					    (int) ((float) (*(float *) (v6 + 0x681824)) * g_664e80),
					    0, 0);
				}
				if (fcn_0064d3f8() % 10 > 6) {
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
			if (v5 > 0x64 || g_772d4c == 3) {
				if (g_772d44 != 0) {
					fcn_0064d41a(&g_772b10, s_689f48, g_772d44);
					fcn_004237f0(g_772d44, 0);
					*(int *) ((char *) g_772d44 + 0x18) = 0;
					g_772d44 = 0;
				}
				if (g_772d48 != 0) {
					fcn_0064d41a(&g_772b10, s_689ee8, g_772d48);
					fcn_004237f0(g_772d48, 0);
					*(int *) ((char *) g_772d48 + 0x18) = 0;
					g_772d48 = 0;
				}
			}
			else {
				fcn_0064d41a(&g_772b10, s_689fac, g_772d48, g_772d44);
				if (g_772d44 != 0) {
					fcn_00423890(g_772d44,
					    (int) (f * *(float *) (g_772d4c * 100 + 0x681838)
						* g_664e80) >> 1);
				}
				if (g_772d48 != 0) {
					fcn_00423890(g_772d48,
					    (int) (f * *(float *) (g_772d4c * 100 + 0x681838)
						* g_664e80) >> 1);
				}
			}
		}
		else {
			*(int *) (v6 + 0x681844) = v2;
			if (g_6628a0 < (float) fcn_0064d3f8() * g_662a18
			    + *(float *) (g_772d4c * 100 + 0x681834)) {
				if (g_772d48 != 0) {
					i = *(int *) ((char *) g_772d48 + 0xc);
					if (i > 2) {
						goto join;
					}
				}
				else {
					i = 0;
				}
				fcn_0064d41a(&g_772b10, s_68a0d0, g_772d48, i);
				g_772d48 = fcn_004234e0(0, s_68a0c4,
				    fcn_0064d3f8() % *(int *) (g_772d4c * 100 + 0x68183c) + 2,
				    0x3f,
				    (int) (f * *(float *) (g_772d4c * 100 + 0x681838)
					* g_664e80),
				    0, 0);
				fcn_0064d41a(&g_772b10, s_68a09c, g_772d48);
			}
join:
			if (g_772d4c == 1) {
				if (g_772d44 == 0) {
					g_772d44 = fcn_004234e0(0, s_68a0c4, 0, 0x3f,
					    (int) (*(float *) (g_772d4c * 100 + 0x681838) * f
						* g_664e80) >> 1, 0, 0);
					fcn_0064d41a(&g_772b10, s_68a070, g_772d44);
				}
				else {
					fcn_00423890(g_772d44,
					    (int) (*(float *) (g_772d4c * 100 + 0x681838) * f
						* g_664e80) >> 1);
					fcn_0064d41a(&g_772b10, s_68a03c, g_772d44);
				}
			}
			else if (g_772d44 != 0) {
				fcn_0064d41a(&g_772b10, s_689ff0, g_772d44);
				fcn_004237f0(g_772d44, 0);
				*(int *) ((char *) g_772d44 + 0x18) = 0;
				g_772d44 = 0;
			}
		}
		v6 = g_772d4c * 100;
		if ((unsigned) (fcn_0064d3f8() % 2000 + *(int *) (v6 + 0x68187c)) <
		    (unsigned) (v2 - *(int *) (v6 + 0x681880))) {
			*(int *) (v6 + 0x681880) = v2;
			v6 = g_772d4c * 100;
			if (g_6628a0 < (float) fcn_0064d3f8() * g_662a18
			    + *(float *) (v6 + 0x681820)) {
				fcn_004234e0(0, s_689ee0, 1, 0x3f,
				    (int) (f * *(float *) (v6 + 0x681874) * g_664e80),
				    0, 0);
			}
		}
		v6 = g_772d4c * 100;
		if ((unsigned) (fcn_0064d3f8() % 2000 + *(int *) (v6 + 0x681868)) <
		    (unsigned) (v2 - *(int *) (v6 + 0x68186c))) {
			*(int *) (v6 + 0x68186c) = v2;
			if (g_6628a0 < (float) fcn_0064d3f8() * g_662a18
			    + *(float *) (g_772d4c * 100 + 0x68185c)) {
				p = s_689ed4;
				if (fcn_0064d3f8() % 10 >= 5) {
					p = s_689ec8;
				}
				fcn_004234e0(0, p, 1, 0x3f,
				    (int) (f * *(float *) (g_772d4c * 100 + 0x681860)
					* g_664e80), 0, 0);
			}
		}
		v6 = g_772d4c * 100;
		if ((unsigned) (fcn_0064d3f8() % 2000 + *(int *) (v6 + 0x681854)) <
		    (unsigned) (v2 - *(int *) (v6 + 0x681858))) {
			*(int *) (v6 + 0x681858) = v2;
			v6 = g_772d4c * 100;
			if (g_6628a0 < (float) fcn_0064d3f8() * g_662a18
			    + *(float *) (v6 + 0x681848)) {
				fcn_004234e0(0, s_689ebc,
				    fcn_0064d3f8() % *(int *) (g_772d4c * 100 + 0x681850) + 1,
				    0x3f,
				    (int) (f * *(float *) (v6 + 0x68184c)
					* g_664e80), 0, 0);
			}
		}
		if (g_772d30 != 0 && g_773d78 != 0) {
			i = *(int *) ((char *) g_773d78 + 0x61);
			fcn_00455350(i, i + 0x4c, buf);
			i = fcn_00402c00(0, 0, buf, 0x44610000) * 0x14;
			if (i >= 0x7f) {
				i = 0x7f;
			}
			fcn_004193c0(g_772d30, i);
		}
	}
	else {
		v5 = (*(volatile int *) &g_6b7fac + *(volatile int *) &g_6b7fac * 2) * 4
		    + *(volatile int *) &g_6b7fac;
		if (g_772d4c != fcn_00500e20((int *) 0x7f4c00)) {
			g_772d4c = fcn_00500e20((int *) 0x7f4c00);
		}
		if (g_772d44 != 0) {
			fcn_0064d41a(&g_772b10, s_689e68, g_772d44);
			fcn_004237f0(g_772d44, 0);
			*(int *) ((char *) g_772d44 + 0x18) = 0;
			g_772d44 = 0;
		}
		if (g_772d48 != 0) {
			fcn_0064d41a(&g_772b10, s_689e18, g_772d48);
			fcn_004237f0(g_772d48, 0);
			*(int *) ((char *) g_772d48 + 0x18) = 0;
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
		c = *(unsigned char *) (lpGebaeudePROT + (unsigned) *g_7746c4 * 0x24d);
		if (c == 0x16 && g_7746cc != 0 && *g_7746cc == 0x120) {
			if (g_772d50 == 0) {
				i = fcn_00420780(s_689dfc, 5);
				g_772d50 = i;
				return i;
			}
			i = fcn_00402ba0(g_6b8010, 0) * 9;
			fv = flt_64 < (float) i ? flt_64 : (float) i;
			return fcn_0041fc10(g_772d50, (int) fv);
		}
		if (c != 0x12 && c != 0x14 && c != 8 && c != 0x15 && c != 0x0e) {
			if (c != 7 || g_7746cc == 0 || *g_7746cc != 0xf7) {
				goto label;
			}
			i = fcn_00402ba0(g_6b8010, 0) * 6;
			fv = flt_64 < (float) i ? flt_64 : (float) i;
			if (g_772d50 == 0) {
				i = fcn_00420780(s_689ddc, 5);
				g_772d50 = i;
				return i;
			}
			return fcn_0041fc10(g_772d50, (int) fv);
		}
		i = fcn_00402ba0(g_6b8010, 0) * 6;
		fv = flt_64 < (float) i ? flt_64 : (float) i;
		if (g_772d50 == 0) {
			if (*(int *) ((char *) g_7746c4 + 0x95) == -1) {
				return 0;
			}
			i = fcn_00420780(s_689dc0, (int) fv);
			g_772d50 = i;
			return i;
		}
		if (*(int *) ((char *) g_7746c4 + 0x95) == -1) {
			fcn_00420840(g_772d50);
			g_772d50 = 0;
			return 0;
		}
		return fcn_0041fc10(g_772d50, (int) fv);
	}
label:
	if (g_772d50 == 0) {
		return 0;
	}
	fcn_00420840(g_772d50);
	g_772d50 = 0;
	return 0;
}
