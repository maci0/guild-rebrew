extern unsigned short g_774970;
extern int g_6b7fb8;
extern int g_6b8010;
extern int g_7e4538;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;
extern char g_7f4ca4[];
extern char g_6b5c60[];
extern char g_68149c[];
extern char g_6a2edc[];
extern char g_6a2f08[];
extern char g_6a6b50[];
extern char g_6a6ad0[];
extern char g_6a6ae0[];
extern char g_6a6af4[];
extern char g_6a6afc[];
extern char g_6a6b0c[];
extern char g_6a6b28[];
extern char g_6a6b38[];
extern char g_6a6b48[];

int __cdecl fcn_004c4450(int);
char *__cdecl gm_StartFilteredEntitySearch(int, ...);
int __cdecl fcn_0050cad0(int *, int *);
void __cdecl fcn_0050ff70(char *, int);
int __cdecl fcn_004c30a0(int, int, char *, int, int);
void __cdecl fcn_00500bb0(char *, int, int, int);
char *__cdecl fcn_00508e40(int);
char *__cdecl fcn_00445600(char *, int, int, char *);
void __cdecl fcn_00455350(char *, char *, float *);
int __cdecl fcn_00451840(float *, float *, float);
int __cdecl fcn_004c5da0(int, int, int, char *, int, char *);
int __cdecl fcn_004c5620(int, char *);
void __cdecl fcn_004c5c80(int);
int __cdecl sprintf(char *, char *, ...);
int __cdecl fcn_00426d00(char *);
int __cdecl fcn_00428720(char *);
void __cdecl fcn_00418f90(int);
void __cdecl fcn_00546190(char *);
void __cdecl fcn_004432d0(int, int);
char *__cdecl fcn_00422460(int, char *);
int __cdecl fcn_00418c80(int, int, int, float);
void __cdecl fcn_004192b0(int, int, int, int);
void __cdecl fcn_004193f0(int, int, int, float);
void __cdecl fcn_0051af00(char *, int, ...);
int __cdecl he_MessageBoxQuickjump(int, int, char *, unsigned char, int, int, int, char *, char *);
int __cdecl gm_RandomMod(unsigned short);
char *__cdecl fcn_00426fd0(char *);
int __cdecl fcn_00428340(int, int, int, int, int);
char *__cdecl fcn_00504c90(char *, int);
void __cdecl fcn_004c6430(int, int, int);
void __cdecl fcn_004c5ed0(int, char *, int);

/* ADDRESS: GOLDTL 0x0056cfc0 */
void __cdecl fcn_0056cfc0(char *a0)
{
	char *e;
	char *r;
	char *m;
	char *h;
	int *p;
	int *q;
	int i;
	int n;
	int d;
	float f;

	if ((*(unsigned char *)(a0 + 0x78) & 2) &&
	    (n = *(int *)(a0 + 0x84)) != -1) {
		if (!fcn_004c4450(n))
			return;
		*(int *)(a0 + 0x84) = -1;
	}
	switch (*(int *)(a0 + 0x70)) {
	case 0:
		e = gm_StartFilteredEntitySearch(1, 1, *(int *)(a0 + 0xac));
		if (e != 0) {
			if (*(unsigned char *)(e + 0x5a) & 1) {
				*(int *)(a0 + 0x70) = -1;
				return;
			}
			if (*(unsigned char *)(a0 + 0xb4) < 3) {
				char names[3][64] = {"dummy_FAHNE", "dummy_RAUCH_0", "dummy_BRAND"};
				float pos[4] = {-243.0f, -90.0f, 190.0f};
				char text[0x400];
				int v10 = g_6b8010;

				if (*(int *)(e + 0x61) != 0) {
					fcn_004432d0(0, 1);
					if (*(char *)(a0 + 0xb4) == 1) {
						r = fcn_00422460(0, g_6a6b48);
						if (r != 0 &&
						    (r = (char *)fcn_00418c80((int)r, *(int *)(e + 0x61), 0x6b, 2200.0f)) != 0)
							fcn_004192b0((int)r, 0, 0, 0);
					} else if (*(char *)(a0 + 0xb4) == 0) {
						r = fcn_00422460(0, g_6a6b38);
						if (r != 0)
							fcn_004193f0((int)r, *(int *)(e + 0x61), 0x6b, 2200.0f);
						if (*(unsigned short *)(e + 0x27) == g_774970) {
							fcn_004c30a0(-8, 0, g_6a6b28, 0, 100);
							if (*(char *)(a0 + 0x104)) {
								fcn_0051af00(text, 0x42d6, e);
								he_MessageBoxQuickjump(
									*(int *)(g_7f4ca4 + (unsigned short)g_774970 * 0x21c),
									-1, text, 0, 0x5ed, *(int *)(e + 1), -1, 0,
									g_6b5c60);
							}
						}
					}
					r = fcn_00445600((char *)*(int *)(e + 0x61), 0x100, 0,
							 &names[(unsigned char)*(unsigned char *)(a0 + 0xb4)][0]);
					if (r == 0) {
						r = fcn_00445600((char *)*(int *)(e + 0x61), 0x100, 0,
								 g_6a2edc);
					} else {
						fcn_00455350(r, r + 0x4c, pos);
					}
					if (r != 0) {
						fcn_00455350(r, r + 0x4c, pos);
						pos[0] = (float)(gm_RandomMod(0x40) & 0xffff) + pos[0] - 32.0f;
						pos[2] = (float)(gm_RandomMod(0x40) & 0xffff) + pos[2] - 32.0f;
						pos[1] = pos[1] - 20.0;
						m = fcn_00426fd0(g_6a6b0c);
						if (m != 0) {
							sprintf(m, g_6a6afc, *(int *)(a0 + 4),
								*(unsigned char *)(a0 + 0xb4));
							fcn_00428340((int)m, 3, (int)pos[0], (int)pos[1],
								     (int)pos[2]);
							*(int *)(m + 0x104) = 0;
						}
					}
				} else if (*(unsigned char *)(a0 + 0x78) & 2) {
					*(int *)(a0 + 0x84) = fcn_004c5620(-1, (char *)a0);
					return;
				}
				*(int *)(a0 + 0x52) = g_7f4c00;
				*(int *)(a0 + 0x56) = g_7f4c04;
				*(int *)(a0 + 0x5a) = g_7f4c08;
				*(unsigned short *)(a0 + 0x5e) = g_7f4c0c;
				*(int *)(a0 + 0x60) = g_7f4c00;
				*(int *)(a0 + 0x64) = g_7f4c04;
				*(int *)(a0 + 0x68) = g_7f4c08;
				*(unsigned short *)(a0 + 0x6c) = g_7f4c0c;
				fcn_00500bb0(a0 + 0x52, 0, 4, 0);
				fcn_004432d0(v10, 1);
			} else {
				*(int *)(a0 + 0x70) = *(int *)(a0 + 0x70) + 1;
			}
		} else {
			*(int *)(a0 + 0x70) = *(int *)(a0 + 0x70) + 1;
		}
		if (e == 0) {
			*(int *)(a0 + 0x52) = g_7f4c00;
			*(int *)(a0 + 0x56) = g_7f4c04;
			*(int *)(a0 + 0x5a) = g_7f4c08;
			*(unsigned short *)(a0 + 0x5e) = g_7f4c0c;
		}
		if ((*(unsigned char *)(a0 + 0x78) & 2) &&
		    *(unsigned char *)(a0 + 0xb4) == 1) {
			i = 0;
			n = (int)fcn_00504c90(e, 3);
			if (n != 0) {
				h = g_7f4ca4 + 0x180;
				q = (int *)(a0 + 0xb8);
				do {
					if (*(char *)(h - 0x17c) != 0 &&
					    *(int *)h != 0 &&
					    *(int *)(*(int *)h + 0x2c) == *(int *)(e + 1) &&
					    (*(char *)(h - 4) == 0 || *(char *)(h - 4) == 4) &&
					    i < 0x10) {
						m = (char *)*(int *)(h - 0x180);
						*q = (int)m;
						fcn_004c6430((int)m, 0, 0);
						fcn_004c5c80(*q);
						fcn_004c5da0(*q, *(int *)(n + 1), -1, 0, 1, g_6a6af4);
						fcn_004c5ed0(*q, g_6a6ae0,
							     (gm_RandomMod(2) & 0xffff) + 1);
						i++;
						q++;
					}
					h += 0x21c;
				} while ((int)h < 0x85a224);
			}
		}
		if (*(unsigned char *)(a0 + 0xb4) >= 3)
			break;
		*(unsigned char *)(a0 + 0xb4) = *(unsigned char *)(a0 + 0xb4) + 1;
		return;
	case 1:
		if (!(*(unsigned char *)(a0 + 0x78) & 2))
			return;
		e = gm_StartFilteredEntitySearch(1, 1, *(int *)(a0 + 0xac));
		if (*(int *)(a0 + 0xb0) > 0) {
			if (e != 0) {
				float pos[4];

				f = 1.0f;
				p = (int *)(a0 + 0x60);
				n = (int)((float)fcn_0050cad0(p, (int *)0x7f4c00) *
					  (1.0f / 6.0f) * 2.0f);
				if (g_7e4538 != 0)
					f = 1.0 + *(int *)g_7e4538 * 0.002 * 0.7;
				*(int *)(a0 + 0xb0) =
					(int)((float)*(int *)(a0 + 0xb0) - n * f);
				fcn_0050ff70(e, -n);
				if (*(unsigned short *)(e + 0x27) == g_774970 &&
				    *(unsigned int *)(a0 + 0xfc) + 0x20d < (unsigned int)g_6b7fb8) {
					d = *(char *)(e + 0x5c) - n;
					if (d <= 0) {
						fcn_004c30a0(-8, 0, g_6a6ad0, 2, 100);
						*(int *)(a0 + 0xfc) = g_6b7fb8;
					} else if (d <= 0xa) {
						fcn_004c30a0(-8, 0, g_6a6ad0, 1, 100);
						*(int *)(a0 + 0xfc) = g_6b7fb8;
					} else if (d <= 0x19) {
						fcn_004c30a0(-8, 0, g_6a6ad0, 0, 100);
						*(int *)(a0 + 0xfc) = g_6b7fb8;
					}
				}
				*(int *)(a0 + 0x52) = g_7f4c00;
				*(int *)(a0 + 0x56) = g_7f4c04;
				*(int *)(a0 + 0x5a) = g_7f4c08;
				*(unsigned short *)(a0 + 0x5e) = g_7f4c0c;
				*(int *)(a0 + 0x60) = g_7f4c00;
				*(int *)(a0 + 0x64) = g_7f4c04;
				*(int *)(a0 + 0x68) = g_7f4c08;
				*(unsigned short *)(a0 + 0x6c) = g_7f4c0c;
				fcn_00500bb0(a0 + 0x52, 0, 4, 0);
				if (*(unsigned char *)(a0 + 0xb4) < 3)
					*(int *)(a0 + 0x70) = 0;
				i = 0;
				p = (int *)(a0 + 0xb8);
				n = 0x10;
				do {
					if (*p != -1) {
						if (i == 0) {
							e = gm_StartFilteredEntitySearch(1, 1,
										 *(int *)(a0 + 0xac));
							i = (int)fcn_00504c90(e, 3);
						}
						r = fcn_00508e40(*p);
						if (r != 0 &&
						    (m = *(char **)(r + 0x184)) != 0 &&
						    *(int *)(m + 0x2c) == -1 &&
						    *(int *)(m + 0x128) == 0 &&
						    (m = fcn_00445600((char *)*(int *)(e + 0x61), 0x100, 0,
								      g_68149c)) != 0) {
							fcn_00455350(m, m + 0x4c, pos);
							if (fcn_00451840(
								    (float *)(*(int *)(*(int *)(r + 0x184) + 0x34) + 0x4c),
								    pos, 750.0f) != 0) {
								if (i != 0)
									fcn_004c5da0(*p, *(int *)(i + 1), -1, 0, 1,
										     g_6a6af4);
							} else {
								fcn_004c5da0(*p, *(int *)(e + 1), -1, 0, 1,
									     g_6a6af4);
							}
						}
					}
					p++;
				} while (--n);
			}
			if (*(int *)(a0 + 0xb0) > 0 && e != 0)
				return;
		}
		*(int *)(a0 + 0x84) = fcn_004c5620(-1, (char *)a0);
		return;
	case 0xfffffffe:
	case 0xffffffff: {
		char buf[0x40];

		e = gm_StartFilteredEntitySearch(1, 1, *(int *)(a0 + 0xac));
		if ((*(unsigned char *)(a0 + 0x78) & 2) && e != 0) {
			p = (int *)(a0 + 0xb8);
			i = 0x10;
			do {
				if (*p != -1) {
					fcn_004c5c80(*p);
					fcn_004c5da0(*p, *(int *)(e + 1), -1, 0, 0, g_6a6af4);
				}
				p++;
			} while (--i);
			for (i = 0; i < 3; i++) {
				sprintf(buf, g_6a6afc, *(int *)(a0 + 4), i);
				n = fcn_00426d00(buf);
				if (n != 0)
					fcn_00428720((char *)n);
			}
		}
		if (e != 0 && *(int *)(e + 0x61) != 0 &&
		    (n = *(int *)(*(int *)(e + 0x61) + 0x210)) != 0)
			fcn_00418f90(n);
		fcn_00546190(a0);
		break;
	}
	default:
		break;
	}
}
