/*
 * Open the trade-goods dialogue for the object a0 and run its modal loop.
 * Creates (or reuses) the dialog slot, fills the four product rows and the
 * container list, then dispatches clicks until the dialog closes.
 */

extern char* g_item_def_table; /* 0x0099ec10 */
extern int g_14aba94;          /* 0x014aba94 */
extern int g_14aba98;          /* 0x014aba98 */
extern int g_14aba9c;          /* 0x014aba9c */
extern int g_14abaa0;          /* 0x014abaa0 */
extern int g_14ce8cc;          /* 0x014ce8cc */
extern int g_14ce8e0;          /* 0x014ce8e0 */
extern int g_100f894;          /* 0x0100f894 */
extern int g_100f1dc;          /* 0x0100f1dc */
extern int g_1015ea0;          /* 0x01015ea0 */
extern int g_67d370;           /* 0x0067d370 */
extern int g_772514;           /* 0x00772514 */
extern unsigned char g_773d75; /* 0x00773d75 */
extern int g_774654;           /* 0x00774654 */
extern int g_775334;           /* 0x00775334 */
extern int g_7e46ac;           /* 0x007e46ac */
extern char s_6ac7b0[];        /* 0x006ac7b0 */

int __cdecl fcn_00525fb0(int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_00526120(int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_005c69d0(int);
int __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl fcn_00594340(void);
int __cdecl fcn_00533dc0(int, int, int);
int __cdecl fcn_00472830(int, int, int, int*, int*, int*);
int __cdecl fcn_00533f40(int, int, int, int);
int __cdecl fcn_00595e20(int, int);
int __cdecl fcn_005963f0(int, int, int, int);
int __cdecl fcn_005974e0(int, int);
int __cdecl fcn_00597940(int, int, int, int, int);
int __cdecl fcn_00471f80(int);
int* __cdecl fcn_004ce590(int);
int* __cdecl fcn_004ce610(int);
int __cdecl fcn_005c7270(int, int);
int __cdecl fcn_004c51f0(int, int, int, int, int, int);
int __cdecl fcn_00472380(int, int, int, int, int);
void __cdecl fcn_004c44a0(void);
void __cdecl fcn_004c44b0(void);
int __cdecl fcn_004c44c0(void);
void __cdecl fcn_00535960(void);
void __cdecl fcn_00473fe0(void);
int __cdecl fcn_004ce9e0(int);
int __cdecl fcn_005c6a10(int, int);
int __cdecl fcn_0046f940(int, char*);
int __cdecl fcn_00471e30(int);
int __cdecl fcn_005373e0(int, int);
int __cdecl fcn_00532ef0(int);
int __cdecl CountDisplayCounters(void);
void __cdecl ResetDisplayCounters(void);
int __cdecl __itoa(int, char*, int);

/* ADDRESS: GOLDTL 0x005c72f0 */
int __cdecl fcn_005c72f0(int a0)
{
	int v7;
	int v8;
	int v9buf[4];
	int v10[4];
	char v11[232];
	int v13;
	int v14;
	int v15;
	int v16;
	int v17;
	int v18;
	int v19;
	int v20;
	int v21;
	int v22;
	int v23;
	int v24;
	int v25;
	unsigned short* p;
	char* def;
	char* list;
	int* p4;
	int* rec;
	int win;

	v7 = a0;
	v15 = 0;
	v8 = -1;
	if (fcn_00525fb0(a0) != 0) {
		return 0;
	}
	if ((g_7e46ac & 0x10000) != 0) {
		v18 = 0x7d6c6;
	} else {
		v18 = 0x677c7;
	}
	p = (unsigned short*) fcn_00502cd0(*(int*) (v7 + 0x5d), 2, 0, 0x2a, 6);
	if (p == 0) {
		p = (unsigned short*) fcn_00502cd0(*(int*) (v7 + 0x5d), 2, 0, 0x116, 6);
	}
	if (p == 0) {
		fcn_00526120(g_14aba98, 0);
		return 0;
	}
	win = fcn_00470820(0, 0, s_6ac7b0);
	fcn_00471b60(win);
	d2_SetForm(win, 3);
	io_AppendText(0x19db);
	fcn_005c69d0(v7);
	d2_SetOverlayAnimation(0, 0);
	fcn_00594340();
	d2_SetForm(win, 0);
	fcn_00533dc0(g_772514, 0x72f, 0);
	fcn_00533f40(0x270, 0x15c, g_772514,
			fcn_00472830(win, 2, 0x78, v10, v9buf, &v8));
	*(int*) (g_1015ea0 + 0x84 + v8 * 0x2f4) = 0x54;
	def = g_item_def_table + (unsigned int) *p * 0x41;
	v16 = win * 0xaf;
label_5c7466:
	v7 = a0;
	if (*p != 0x116 && *def != 0x11) {
		if (*def == 0x05) {
			v15 = fcn_00595e20(a0, (int) p);
			fcn_005963f0(win, 1, 1, v7);
		}
	} else {
		v15 = fcn_005974e0(a0, (int) p);
		fcn_00597940(win, 1, 1, v7, (int) p);
	}
	if (g_100f1dc != -1 && v15 != 0) {
		v7 = 0;
		p4 = (int*) 0x7774a8;
		for (;;) {
			if (p4[-2] != 0 && *p4 == g_67d370) {
				v7 = *(int*) (v7 * 0x40 + 0x7774a0);
				if (v7 != 0) {
					fcn_004c44a0();
					fcn_00473fe0();
					rec = (int*) 0x778db0;
					goto label_5c752a;
				}
				break;
			}
			p4 += 0x10;
			v7 += 1;
			if ((int) p4 >= 0x777ca8) {
				break;
			}
		}
	}
	goto label_5c76eb;
label_5c752a:
	do {
		int v5;
		v5 = *rec;
		if (v5 != -1 && fcn_00471f80(v5) != 0) {
			v5 = rec[-4];
			if (fcn_004ce590(v5) != 0) {
				if (*(int*) fcn_004ce610(v7) != 0) {
					fcn_00526120(g_14aba9c, 4);
					goto label_5c7572;
				}
				v7 *= 0x38;
				v13 = *(int*) (v7 + 0x778da0);
				v5 = fcn_005c7270(v7, v13);
				if (v5 != 0) {
					fcn_004c51f0(*(int*) (v7 + 4), *(int*) &p[1], v13, 1,
							(v5 & 0xffffff00) | ((int) g_773d75 << 24), 0);
					v5 = fcn_00471f80(*(int*) (v7 + 0x778db0));
					fcn_00472380(*(int*) (v7 + 0x778db0), 0,
							*(int*) (v7 + 0x778dd0), v5 - 1, 0);
					break;
				}
				v14 = 4;
				v13 = g_14abaa0;
			} else {
				v14 = 0;
				v13 = g_14aba94;
			}
			fcn_00526120(v13, v14);
			break;
		}
label_5c7572:
		rec += 0xe;
		v7 += 1;
	} while ((int) rec < 0x779130);
	v7 = 0;
	rec = (int*) 0x7796f0;
	do {
		int v5;
		v5 = *rec;
		if (v5 != -1 && fcn_00471f80(v5) != 0) {
			v7 *= 0x38;
			v13 = *(int*) (v7 + 0x7796e0);
			if (fcn_004ce590(v13) != 0) {
				v13 = *(int*) (v7 + 0x7796e0);
				v5 = fcn_005c7270(v7, v13);
				if (v5 != 0) {
					fcn_004c51f0(*(int*) (v7 + 4), *(int*) &p[1], v13, 1,
							(v5 & 0xffffff00) | ((int) g_773d75 << 24), 0);
					v5 = fcn_00471f80(*(int*) (v7 + 0x7796f0));
					fcn_00472380(*(int*) (v7 + 0x7796f0), 0,
							*(int*) (v7 + 0x779710), v5 - 1, 0);
					break;
				}
				v13 = g_14abaa0;
			} else {
				v13 = g_14aba94;
			}
			fcn_00526120(v13, 0);
			break;
		}
		rec += 0xe;
		v7 += 1;
	} while ((int) rec < 0x7798b0);
	fcn_004c44b0();
	v7 = fcn_004c44c0();
	while (v7 == 0) {
		fcn_00535960();
		v7 = fcn_004c44c0();
	}
	fcn_004ce9e0(v7);
label_5c76eb:
	v7 = fcn_005c6a10(win, 2);
	if (g_100f894 == *(int*) (v16 * 4 + 0x1038148) && v7 != 0 && g_14ce8cc != 0) {
		fcn_004c44a0();
		p4 = (int*) 0x7774a0;
		do {
			if (*p4 != 0) {
				int* q;
				int n;
				q = &p4[4];
				n = 6;
				do {
					if (*q != -1 && fcn_00471f80(*q) != 0) {
						fcn_004c51f0(*(int*) &p[1], *(int*) (*p4 + 4),
								q[1], 1,
								(fcn_00471f80(*q) & 0xffffff00) | ((int) g_773d75 << 24),
								0);
					}
					q += 2;
					n -= 1;
				} while (n != 0);
			}
			p4 += 0x10;
		} while ((int) p4 < 0x777ca0);
		fcn_004c44b0();
		v7 = fcn_004c44c0();
		while (v7 == 0) {
			fcn_00535960();
			v7 = fcn_004c44c0();
		}
		p4 = (int*) 0x7774a0;
		do {
			if (*p4 != 0) {
				fcn_004ce9e0(*p4);
			}
			p4 += 0x10;
		} while ((int) p4 < 0x777ca0);
	}
	__itoa(g_775334, v11, 10);
	fcn_0046f940(v8, v11);
	if (g_14ce8e0 != 0) {
		if (CountDisplayCounters() == 0) {
			g_774654 = 1;
		} else {
			int* q;
			ResetDisplayCounters();
			q = (int*) 0x778db0;
			do {
				v7 = *q;
				if (v7 != -1 && fcn_00471f80(v7) != 0) {
					fcn_00472380(*q, 0, q[8], 0, 0);
				}
				q += 0xe;
			} while ((int) q < 0x779130);
			q = (int*) 0x7796f0;
			do {
				v7 = *q;
				if (v7 != -1 && fcn_00471f80(v7) != 0) {
					fcn_00472380(*q, 0, q[8], 0, 0);
				}
				q += 0xe;
			} while ((int) q < 0x7798b0);
			p4 = (int*) 0x7774b0;
			do {
				if (p4[-4] != 0) {
					int* q2;
					int n;
					v7 = 6;
					q2 = p4;
					do {
						if (*q2 != -1) {
							fcn_00472380(*q2, 0, 0, 0, 0);
						}
						q2 += 2;
						v7 -= 1;
					} while (v7 != 0);
				}
				p4 += 0x10;
			} while ((int) p4 < 0x777cb0);
		}
	}
	v7 = fcn_005373e0(0x5c72f0, v18);
	if (v7 != 0) {
		goto label_5c7466;
	}
	fcn_00471e30(win);
	return fcn_00532ef0(a0);
}
