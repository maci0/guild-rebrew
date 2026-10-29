extern int g_7e46ac;
extern int g_772514;
extern unsigned short g_774970;
extern char *g_1015ea0;
extern int g_1015f4c[];
extern int g_7f4c00;
extern int g_14ad084;
extern int g_14ce8e0;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;
extern char g_7f4ca0[];

struct d2_daterec {
	char day;
	char month;
	short year;
	int time;
	short rest;
};

int __cdecl fcn_00470820(int, int, char *);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472640(int, int);
int __cdecl fcn_004b3c80(int);
void __cdecl fcn_004b54e0(int);
void __cdecl fcn_004c50e0(int, int);
char *__cdecl fcn_00508e40(int);
float __cdecl fcn_00505e30(unsigned short);
void __cdecl fcn_00509050(char *, char *);
int __cdecl fcn_00509120(char *, char *);
int __cdecl gm_AccumulateTyped2(char *);
int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl fcn_00519190();
void __cdecl fcn_0051af00();
int __cdecl fcn_00526120(char *, int);
void __cdecl fcn_00533a60(int, int, int *, int, char *, char *);
void __cdecl fcn_00534210(int, int, char *, int, int);
int __cdecl fcn_005373e0(int, int);
char *__cdecl fcn_005463a0(int, int, int);
char *__cdecl he_fn_Handlung(void);
int __cdecl fcn_005d2470(void *, void *);
int __cdecl fcn_005db8e0(void *, void *);
int __cdecl fcn_005dbb60(void *, void *);
int __cdecl _ftol(void);
int __cdecl d2_ShowTxt(int, int, char *, int);

/* ADDRESS: GOLDTL 0x005d1790 */
void __cdecl fcn_005d1790(unsigned short *a0, int a1)
{
	char bufB[512];
	char bufA[512];
	int msg;
	char buf12[64];
	int r5;
	int r4;
	int r3;
	struct d2_daterec dt;
	int v23;
	int v15;
	int r2;
	int r1;
	int h;
	int ok;
	int t;
	int inx;
	int i;
	int idx;
	int stamp;
	char *p;
	char *q;
	char *r;

	ok = 0;
	r5 = -1;
	r3 = -1;
	r1 = -1;
	r4 = -1;
	r2 = -1;
	msg = g_7e46ac;
	h = fcn_00470820(0, 0, "panel\\info_spieler");
	fcn_00473a90(0, 0);
	fcn_00471b60(h);
	d2_SetForm(h, 1);
	fcn_00519190(0x1f53, *a0);
	d2_SetForm(h, 2);
	fcn_00509050((char *)a0, (char *)&dt);
	fcn_0051af00(buf12, "*%i.%i.%i", dt.day, dt.month, dt.year);
	fcn_00519190("$3>$L%s$A$0>", buf12);
	if (fcn_00509120((char *)a0, (char *)&dt) != 0) {
		fcn_0051af00(buf12, "+%i.%i.%i", dt.day, dt.month, dt.year);
		fcn_00519190("$3>$L%s$A$0>", buf12);
		ok = 1;
	} else {
		fcn_00505e30(*a0);
		fcn_00519190("$5<$R%s$0<$3>$L%i$A$0>", 0x1f54, _ftol());
	}
	if (*((char *)a0 + 0x164) != 0) {
		fcn_00519190("$5<$R%s$0<$3>$L%s$A$0>", 0x1f55,
		    (*((char *)a0 + 9) != 0 ? 0x18f : 0x130) + *((unsigned char *)a0 + 0x164));
	} else if (*((char *)a0 + 0x165) != 0) {
		fcn_00519190("$5<$R%s$0<$3>$L%s$A$0>", 0x1f56,
		    (*((char *)a0 + 9) != 0 ? 0x230 : 0x20d) + *((unsigned char *)a0 + 0x165));
	}
	t = *((char *)a0 + 9) != 0 ? 0x27b : 0x253;
	if (*((char *)a0 + 0x166) == 0 && *((char *)a0 + 0x169) == 0) {
		fcn_0051af00(buf12, "%s", "-");
		fcn_00519190("$5<$R%s$0<$3>$L%s$A$0>", 0x1f57, buf12);
	}
	if (*((char *)a0 + 0x166) != 0) {
		if (*((char *)a0 + 0x169) != 0) {
			fcn_00519190("$5<$R%s$0<$3>$L%s$A%s$A$0>", 0x1f57,
			    *((unsigned char *)a0 + 0x166) + t,
			    *((unsigned char *)a0 + 0x169) + t);
		} else {
			fcn_00519190("$5<$R%s$0<$3>$L%s$A$0>", 0x1f57,
			    *((unsigned char *)a0 + 0x166) + t);
		}
	} else if (*((char *)a0 + 0x169) != 0) {
		fcn_00519190("$5<$R%s$0<$3>$L%s$A$0>", 0x1f57,
		    *((unsigned char *)a0 + 0x169) + t);
	}
	if (ok != 0) {
		fcn_00519190("$5<$R%s$0<$3>$L%s$A$0>", 0x1f58, gm_WalkEntityChain(*a0));
	} else {
		fcn_00519190("$5<$R%s$0<$3>$L%T$A$0>", 0x1f58, gm_WalkEntityChain(*a0));
	}
	p = fcn_00508e40(*(int *)((char *)a0 + 0x5c));
	if (ok != 0) {
		*(unsigned short *)buf12 = *(unsigned short *)"-";
		fcn_00519190("$5<$R%s$0<$3>$L%s$A$0>", g_14ad084, buf12);
	} else if (p != 0 && *((unsigned char *)p + 8) > 0) {
		fcn_0051af00(buf12, 0x1f5f, *(unsigned short *)p);
		fcn_00519190("$5<$R%s$0<$3>$L%s$A$0>", 0x1f59, buf12);
	} else {
		q = fcn_005463a0(1, 0, 0x41);
		while (q != 0) {
			if (*(int *)(q + 0xac) == *(int *)((char *)a0 + 4)) {
				r = fcn_00508e40(*(int *)(q + 0xb0));
				if (r != 0) {
					fcn_0051af00(buf12, 0x1f5e, *(unsigned short *)r);
					fcn_00519190("$5<$R%s$0<$3>$L%s$A$0>", 0x1f59, buf12);
					goto printed;
				}
				break;
			}
			q = he_fn_Handlung();
		}
		if (p == 0) {
			fcn_00519190("$5<$R%s$0<$3>$L%s$A$0>", 0x1f59, 0x1f5d);
		} else {
			fcn_0051af00(buf12, 0x1f60, *(unsigned short *)p);
			fcn_00519190("$5<$R%s$0<$3>$L%s$A$0>", 0x1f59, buf12);
		}
	printed:
		;
	}
	fcn_00519190("$5<$R%s $0<$3>$L%s$A$0>", 0x488,
	    (g_7f4c00 >= 0x75 ? 0x483 : 0x486) + *((unsigned char *)a0 + 0xc));
	fcn_00519190("$5<$R%s$0<", 0x1f5a);
	ok = 0;
	p = (char *)a0 + 0x68;
	i = 5;
	do {
		q = fcn_00508e40(*(int *)p);
		if (q != 0) {
			ok = 1;
			fcn_00519190("$3>$L%1N1$A$0>", *(unsigned short *)q);
		}
		p += 4;
		i--;
	} while (i != 0);
	if (ok == 0) {
		fcn_00519190("$3>$L-$A$0>");
	}
	d2_SetForm(h, 3);
	stamp = g_1015f4c[(int)g_772514 * 243];
	fcn_0051af00(buf12, 0x1f61);
	idx = d2_ShowTxt(0, 1, buf12, g_772514);
	*(int *)(g_1015ea0 + idx * 0x2f4 + 0x6c) = 1;
	*(int *)(g_1015ea0 + idx * 0x2f4 + 0x18) = stamp;
	inx = 2;
	i = 0;
	do {
		fcn_0051af00(buf12, i + 0x16b7);
		inx += 0x18;
		d2_ShowTxt(10, inx - 1, buf12, g_772514);
		fcn_00534210(0xaf, inx, (char *)a0, i, 0x4e5);
		i++;
	} while (i < 5);
	fcn_0051af00(buf12, 0x1f63);
	idx = d2_ShowTxt(0, 0x9a, buf12, g_772514);
	inx = 7;
	*(int *)(g_1015ea0 + idx * 0x2f4 + 0x6c) = 1;
	*(int *)(g_1015ea0 + idx * 0x2f4 + 0x18) = stamp;
	if (*(int *)((char *)a0 + 0x2c) != 0) {
		if (*(int *)((char *)a0 + 0x2c) & 0xf) {
			fcn_0051af00(buf12, 0x161e);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, g_772514);
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x6c) = 1;
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x18) = stamp;
			inx++;
		}
		if (*(int *)((char *)a0 + 0x2c) & 0xf0) {
			fcn_0051af00(buf12, 0x161f);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, g_772514);
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x6c) = 1;
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x18) = stamp;
			inx++;
		}
		if (*(int *)((char *)a0 + 0x2c) & 0xf00) {
			fcn_0051af00(buf12, 0x1620);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, g_772514);
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x6c) = 1;
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x18) = stamp;
			inx++;
		}
		if (*(int *)((char *)a0 + 0x2c) & 0x3000) {
			fcn_0051af00(buf12, 0x1621);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, g_772514);
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x6c) = 1;
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x18) = stamp;
			inx++;
		}
		if (*(int *)((char *)a0 + 0x2c) & 0x1c000) {
			fcn_0051af00(buf12, 0x1622);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, g_772514);
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x6c) = 1;
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x18) = stamp;
			inx++;
		}
		if (*(int *)((char *)a0 + 0x2c) & 0xe0000) {
			fcn_0051af00(buf12, 0x1623);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, g_772514);
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x6c) = 1;
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x18) = stamp;
			inx++;
		}
		if (*(int *)((char *)a0 + 0x2c) & 0x700000) {
			fcn_0051af00(buf12, 0x1624);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, g_772514);
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x6c) = 1;
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x18) = stamp;
			inx++;
		}
		if (*(int *)((char *)a0 + 0x2c) & 0x1800000) {
			fcn_0051af00(buf12, 0x1625);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, g_772514);
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x6c) = 1;
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x18) = stamp;
			inx++;
		}
		if (*(int *)((char *)a0 + 0x2c) & 0x1e000000) {
			fcn_0051af00(buf12, 0x1626);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, g_772514);
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x6c) = 1;
			*(int *)(g_1015ea0 + idx * 0x2f4 + 0x18) = stamp;
		}
	}
	if (a1 != 0) {
		d2_SetForm(h, 4);
		r5 = fcn_00472250(h, 4, fcn_00519190(0x1f50, *a0));
	} else {
		if ((*((char *)g_7f4ca0 + 540 * g_774970 + 9) == 0 &&
		     *(int *)(g_7f4ca0 + 540 * g_774970 + 4) == *(int *)((char *)a0 + 0x60)) ||
		    (*((char *)g_7f4ca0 + 540 * g_774970 + 9) == 1 &&
		     *(int *)(g_7f4ca0 + 540 * g_774970 + 4) == *(int *)((char *)a0 + 0x64))) {
			if (*((char *)a0 + 0x164) != 0) {
				if ((*(int *)((char *)a0 + 0x1c8) & 0x10000) == 0) {
					if ((*((unsigned char *)g_7f4ca0 + 540 * g_774970 + 0x1c8) & 0x20) == 0) {
						fcn_0051af00(bufA, 0x1f4b, *a0);
						fcn_0051af00(bufB, 0x1a96);
						d2_SetForm(h, 4);
						fcn_00533a60(g_772514, 0, &v15, 2, bufA, bufB);
						r1 = v15;
						r4 = v23;
					}
				} else if ((*((unsigned char *)g_7f4ca0 + 540 * g_774970 + 0x1c8) & 0x20) == 0) {
					fcn_0051af00(bufA, 0x1f4b, *a0);
					d2_SetForm(h, 4);
					r1 = fcn_00472250(h, 4,
					    fcn_00519190("%ia[%s]", bufA));
				}
			} else {
				if (fcn_005463a0(2, 2, *a0, 0, 0x5e) == 0) {
					v15 = a0[5] + 4;
					if (v15 >= *(float *)((char *)a0 + 0x20)) {
						if ((*((unsigned char *)g_7f4ca0 + 540 * g_774970 + 0x1c8) & 0x20) == 0) {
							fcn_0051af00(bufA, 0x1f4b, *a0);
							fcn_0051af00(bufB, 0x1a96);
							d2_SetForm(h, 4);
							fcn_00533a60(g_772514, 0, &v15, 2, bufA, bufB);
							r1 = v15;
							r2 = v23;
						}
						goto label_2281;
					}
				}
				if ((*((unsigned char *)g_7f4ca0 + 540 * g_774970 + 0x1c8) & 0x20) == 0) {
					fcn_0051af00(bufA, 0x1f4b, *a0);
					d2_SetForm(h, 4);
					r1 = fcn_00472250(h, 4,
					    fcn_00519190("%ia[%s]", bufA));
				}
			}
		} else if (*(int *)(g_7f4ca0 + 540 * g_774970 + 4) == *(int *)((char *)a0 + 4) &&
		    fcn_004b3c80(*(int *)((char *)a0 + 4)) != 0) {
			d2_SetForm(h, 4);
			r3 = fcn_00472250(h, 4, fcn_00519190(0x1f49));
		}
	}
label_2281:
	g_100f1dc = -1;
	g_67d370 = -1;
	do {
		if (r1 != -1) {
			fcn_00472640(r1, gm_AccumulateTyped2(g_7f4ca0 + 540 * g_774970) > 0);
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			fcn_00471af0(h, 0);
			if (g_67d370 != r5) {
				if (g_67d370 != r1) {
					if (g_67d370 != r2) {
						if (g_67d370 != r4) {
							if (g_67d370 == r3) {
								fcn_004b54e0(*(int *)((char *)a0 + 4));
							}
						} else if (fcn_005dbb60(g_7f4ca0 + 540 * g_774970, a0) != 0) {
							fcn_00472640(r4, 0);
						}
					} else if (fcn_005db8e0(g_7f4ca0 + 540 * g_774970, a0) != 0) {
						fcn_00472640(r2, 0);
					}
				} else if (fcn_005d2470(g_7f4ca0 + 540 * g_774970, a0) != 0) {
					fcn_00472640(r1, 0);
				}
			} else {
				fcn_0051af00(bufB, 0x1f51, *a0, *a0);
				if (fcn_00526120(bufB, 1) != 0) {
					fcn_004c50e0(*(int *)(g_7f4ca0 + 540 * g_774970 + 4),
					    *(int *)((char *)a0 + 4));
					g_774654 = 2;
				}
			}
			fcn_00471af0(h, 1);
		}
	} while (fcn_005373e0((int)fcn_005d1790, msg) != 0);
	fcn_00471e30(h);
}
