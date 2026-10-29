/* Reconstruction of the two native functions in inventory extent
 * 0x005a59d0..0x005a66a7: the dialog pump body and its message handler. */

typedef struct {
	int sel;
	int pad4[2];
	int val;
	int pad10[1];
	int x14;
	int x18;
} Lrow;

extern int g_772514;
extern char* g_77255c;
extern char* g_1015ea0;
extern char g_1015f40[];
extern char g_6b5c60[];
extern char g_6aac84[];
extern char g_6aac7c[];
extern char g_6aacac[];
extern int g_14ab710;
extern int g_14ab718;
extern int g_14ab6fc;
extern int g_14ce8e0;
extern int g_100f8c0;
extern int g_100f1dc;
extern int g_774654;
extern int g_774970;
extern unsigned char g_773d75;
extern int g_67d370;
extern double g_6640e8;

void __cdecl ResetDisplayCounters(void);
int __cdecl CountDisplayCounters(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_00533dc0(int, int, int);
int __cdecl d2_ShowTxt(int, int, char*, int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00475220(char*);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_00533a40(char*);
int __cdecl fcn_005a5440(int, void*, int, int, int);
int __cdecl fcn_005a5980(void*);
int __cdecl fcn_0059c830(void*);
int __cdecl fcn_0046f940(int, char*);
void __cdecl fcn_0046ed00(int, int, int);
int __cdecl fcn_00472170(int, int);
void __cdecl d2_SetElementImage(int, int);
void __cdecl d2_SetElementValue(int, int, int, int);
void __cdecl fcn_00473fe0(void);
int __cdecl fcn_00508620(int, int);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_004c4eb0(char*);
int __cdecl fcn_004c4ef0(char*);
int __cdecl fcn_004c51f0(int, int, int, int, int, int);
void __cdecl fcn_004c4510(int, int);
void __cdecl fcn_004c4570(int, int, int, int);
int __cdecl fcn_004c5360(int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_00532ef0(void);
char* __cdecl itoa(int, char*, int);

/* ADDRESS: GOLDTL 0x005a59d0 */
int __cdecl fcn_005a59d0(char* a0)
{
	int v1, v2, v3, v4, v5, v6, v7, v8;
	int v17, v18, v19;
	int e0, e1, e2, e3, e4;
	int h1, h2;
	int v15, v16, v28, v29, v30, v31;
	Lrow ownRows[16];
	Lrow globRows[16];
	char buf[256];

	v7 = 0;
	v31 = 0;
	do {
		*(int*)((char*)ownRows + v7) = -1;
		*(int*)((char*)ownRows + v7 + 0xc) = 0;
		*(int*)((char*)globRows + v7) = -1;
		*(int*)((char*)globRows + v7 + 0xc) = 0;
		v7 += 0x1c;
	} while (v7 < 0x1c0);
	v8 = fcn_00470820(0, 0, g_6aac84);
	fcn_00471b60(v8);
	e2 = fcn_00472250(v8, 0, 2);
	e3 = fcn_00472250(v8, 0, 3);
	e1 = fcn_00472250(v8, 0, 1);
	e0 = fcn_00472250(v8, 0, 0);
	e4 = fcn_00472250(v8, 0, 4);
	d2_SetForm(v8, 0);
	fcn_00533dc0(g_772514, 0x73b, 0x73f);
	d2_SetForm(v8, 0);
	h1 = d2_ShowTxt((*(int*)(g_1015ea0 + e1 * 0x2f4 + 0x10) - *(int*)(g_77255c + 4)) + 2,
		(*(int*)(g_1015ea0 + e1 * 0x2f4 + 0x1c) - *(int*)(g_77255c + 8)) + 2
			+ *(int*)(g_1015ea0 + e1 * 0x2f4 + 0x14),
		g_6b5c60, g_772514);
	h2 = d2_ShowTxt((*(int*)(g_1015ea0 + e2 * 0x2f4 + 0x10) - *(int*)(g_77255c + 4)) + 2,
		(*(int*)(g_1015ea0 + e2 * 0x2f4 + 0x1c) - *(int*)(g_77255c + 8)) + 2
			+ *(int*)(g_1015ea0 + e2 * 0x2f4 + 0x14),
		g_6b5c60, g_772514);
	*(int*)(g_1015ea0 + 0x84 + h1 * 0x2f4) = 0x54;
	*(int*)(g_1015ea0 + 0x84 + h2 * 0x2f4) = 0x54;
	*(int*)(g_1015ea0 + 0x54 + e4 * 0x2f4) = 1;
	d2_SetForm(v8, 0);
	*(int*)(g_1015f40 + g_772514 * 0x3cc + 0x3a8) = 0xe;
	*(int*)(g_1015f40 + g_772514 * 0x3cc + 0x3ac) = 0x18;
	*(int*)(g_1015f40 + g_772514 * 0x3cc + 0x3b0) = 0xe;
	*(int*)(g_1015f40 + g_772514 * 0x3cc + 0x3b4) = 0xe;
	d2_SetForm(v8, 1);
	fcn_00519190(0x18f5);
	d2_SetForm(v8, 2);
	fcn_00519190(0x18f6, *(int*)(a0 + 0x69),
		*(unsigned short*)(g_773d75 * 0x2f4 + 0x8680b4) * 2 + 0x9a8, *(int*)(a0 + 0x6d));
	fcn_00475220(g_14ab6fc);
	fcn_00473a90(0, 0);
	v29 = -1;
	do {
		if (g_14ce8e0) {
			if (CountDisplayCounters()) {
				fcn_00473fe0();
				for (v15 = 0; v15 < 0x1c0; v15 += 0x1c) {
					if (*(int*)((char*)ownRows + v15) != -1)
						d2_SetElementValue(*(int*)((char*)ownRows + v15), 0, 0, 0);
					if (*(int*)((char*)globRows + v15) != -1)
						d2_SetElementValue(*(int*)((char*)globRows + v15), 0, 0, 0);
				}
			} else {
				g_774654 = 1;
			}
		}
		ResetDisplayCounters();
		if (v31 != 2) {
			v29 = fcn_005a5440(*(int*)(a0 + 0x5d), ownRows, v8, 5, 1);
			if (v29 != -1) {
				if (!g_100f8c0 || !v31) {
					fcn_0051af00(buf, 0x18fa, ownRows[v29].x14, ownRows[v29].val * 2 + 0x9a8);
					fcn_00475220(buf);
				}
				v31 = 1;
				v30 = v29;
				d2_SetElementImage(e4, 0x4f8);
				goto label_image_done;
			}
		}
		v29 = fcn_005a5440(*(int*)(g_774970 * 0x21c + 0x7f4e18), globRows, v8, 4, 1);
		if (v29 != -1) {
			if (!g_100f8c0 || !v31) {
				fcn_0051af00(buf, 0x18f8, globRows[v29].x14, globRows[v29].val * 2 + 0x9a8);
				fcn_00475220(buf);
			}
			v31 = 2;
			v30 = v29;
			d2_SetElementImage(e4, 0x4f9);
		} else {
			v31 = 0;
			v30 = -1;
			fcn_00475220(g_14ab6fc);
			d2_SetElementImage(e4, 0x4f7);
		}
	label_image_done:
		v15 = fcn_0059c830(ownRows);
		v16 = fcn_0059c830(globRows);
		if (v15 > 4) {
			fcn_00472170(e1, 1);
			fcn_00472170(e0, 1);
			fcn_00472170(e3, 1);
			itoa(v15, buf, 10);
			fcn_0046f940(e3, buf);
		} else {
			fcn_00472170(e1, 0);
			fcn_00472170(e0, 0);
			fcn_00472170(e3, 0);
		}
		if (v16 > 4) {
			fcn_00472170(e2, 1);
			fcn_00472170(e2, 1);
			fcn_00472170(e4, 1);
			itoa(v16, buf, 10);
			fcn_0046f940(e2, buf);
		} else {
			fcn_00472170(e2, 0);
			fcn_00472170(e2, 0);
			fcn_00472170(e4, 0);
		}
		if (g_100f1dc == 3 || g_100f1dc == 4) {
			if (g_67d370 == e0) {
				d2_SetForm(v8, 4);
				fcn_0046ed00(0, -0x4c, g_772514);
			} else if (g_67d370 == e1) {
				d2_SetForm(v8, 4);
				fcn_0046ed00(0, 0x4c, g_772514);
			} else if (g_67d370 == e2) {
				d2_SetForm(v8, 5);
				fcn_0046ed00(0, -0x4c, g_772514);
			} else if (g_67d370 == e3) {
				d2_SetForm(v8, 5);
				fcn_0046ed00(0, 0x4c, g_772514);
			}
		}
		if (v31 == 1) {
			v16 = fcn_005a5980(globRows);
			if (v16 != -1) {
				v2 = globRows[v16].val;
				v3 = ownRows[v29].val;
				if (v2 != v3) {
					v30 = globRows[v16].x18;
					if (ownRows[v29].x14 <= globRows[v16].x18)
						v30 = ownRows[v29].x14;
					if ((g_774970 != *(unsigned short*)(a0 + 0x27))
						&& (*(int*)(a0 + 0x6d) * 0.1 * (float)fcn_00508620(v30, v2)
							<= (float)fcn_00508620(1, v3)))
						fcn_00508620(1, v3);
					v4 = ownRows[v29].x14;
					if ((float)fcn_00508620(v30, v2) <= (float)fcn_00508620(v4, v3)) {
						fcn_004c4eb0(g_6aac7c);
						v28 = fcn_00508620(0, v3);
						fcn_004c51f0(-1,
							*(int*)(g_774970 * 0x21c + 0x7f4ca4), v3, v28,
							g_773d75,
							0);
						v17 = fcn_00508620(0, v3);
						fcn_004c51f0(*(int*)(g_774970 * 0x21c + 0x7f4ca4), -1,
							v2, v17,
							g_773d75,
							0);
						v18 = fcn_00508620(0, v3);
						fcn_004c51f0(-1, *(int*)(a0 + 1), v2, v18,
							g_773d75,
							0);
						v19 = fcn_00508620(0, v3);
						fcn_004c51f0(*(int*)(a0 + 1), -1, v3, v19,
							g_773d75,
							0);
						v5 = fcn_004c4ef0(g_6aac7c);
						while (!fcn_004c4450(v5))
							fcn_005373e0(0, 0x677c7);
						fcn_005a5440(*(int*)(g_774970 * 0x21c + 0x7f4e18), globRows, v8, 4, 1);
						fcn_005a5440(*(int*)(a0 + 0x5d), ownRows, v8, 5, 1);
						fcn_00533a40(g_14ab718);
						fcn_00473fe0();
						for (v15 = 0; v15 < 0x1c0; v15 += 0x1c) {
							if (*(int*)((char*)ownRows + v15) != -1)
								d2_SetElementValue(*(int*)((char*)ownRows + v15), 0, 0, 0);
							if (*(int*)((char*)globRows + v15) != -1)
								d2_SetElementValue(*(int*)((char*)globRows + v15), 0, 0, 0);
						}
					} else {
						fcn_0051af00(buf, 0x18fd, v2 * 2 + 0x9a8);
						fcn_00475220(buf);
					}
				} else {
					fcn_00475220(g_14ab710);
				}
			}
		} else if (v31 == 2) {
			v16 = fcn_005a5980(ownRows);
			if (v16 != -1) {
				v2 = ownRows[v16].val;
				v3 = globRows[v29].val;
				if (v2 != v3) {
					v4 = globRows[v29].x14;
					if ((g_774970 != *(unsigned short*)(a0 + 0x27))
						&& (*(int*)(a0 + 0x6d) * 0.1 * (float)fcn_00508620(v4, v3)
							<= (float)fcn_00508620(1, v3)))
						fcn_00508620(1, v3);
					v30 = ownRows[v16].x18;
					if ((float)fcn_00508620(v4, v3) <= (float)fcn_00508620(v30, v2)) {
						fcn_004c4eb0(g_6aac7c);
						fcn_004c51f0(-1,
							*(int*)(g_774970 * 0x21c + 0x7f4ca4), v2,
							fcn_00508620(0, v2),
							g_773d75,
							0);
						fcn_004c51f0(*(int*)(g_774970 * 0x21c + 0x7f4ca4), -1,
							v2, fcn_00508620(0, v2),
							g_773d75,
							0);
						fcn_004c51f0(-1, *(int*)(a0 + 1), v3, fcn_00508620(v4, v3),
							g_773d75,
							0);
						fcn_004c51f0(*(int*)(a0 + 1), -1, v2, fcn_00508620(0, v2),
							g_773d75,
							0);
						v5 = fcn_004c4ef0(g_6aac7c);
						while (!fcn_004c4450(v5))
							fcn_005373e0(0, 0x677c7);
						fcn_005a5440(*(int*)(g_774970 * 0x21c + 0x7f4e18), globRows, v8, 4, 1);
						fcn_005a5440(*(int*)(a0 + 0x5d), ownRows, v8, 5, 1);
						fcn_00533a40(g_14ab718);
						fcn_00473fe0();
						for (v15 = 0; v15 < 0x1c0; v15 += 0x1c) {
							if (*(int*)((char*)ownRows + v15) != -1)
								d2_SetElementValue(*(int*)((char*)ownRows + v15), 0, 0, 0);
							if (*(int*)((char*)globRows + v15) != -1)
								d2_SetElementValue(*(int*)((char*)globRows + v15), 0, 0, 0);
						}
					} else {
						fcn_0051af00(buf, 0x18fd, v2 * 2 + 0x9a8);
						fcn_00533a40(buf);
					}
				} else {
					fcn_00533a40(g_14ab710);
				}
			}
		}
	} while (fcn_005373e0(fcn_005a59d0, 0x677c7));
	ResetDisplayCounters();
	fcn_00471e30(v8);
	return fcn_00532ef0();
}

/* Second native function inside the same inventory extent (0x005a6570).
 * Not an inventory entry on its own: the 3287-byte row also spans the
 * 15-byte nop gap at 0x005a6562..0x005a6570. */
int __cdecl fcn_005a6570(char* a0)
{
	int v1, v2;
	int e1, e2;
	int v8;

	v8 = fcn_00470820(0, 0, g_6aacac);
	fcn_00471b60(v8);
	d2_SetForm(v8, 2);
	fcn_00519190(0x1908);
	d2_SetForm(v8, 1);
	v1 = fcn_00519190(0x1907);
	e1 = fcn_00472250(v8, 1, v1);
	e2 = fcn_00472250(v8, 1, v1 + 1);
	d2_SetElementValue(e2, 3, 0xf, *(int*)(a0 + 0x69));
	d2_SetElementValue(e1, 3, 0xf, *(int*)(a0 + 0x6d));
	do {
		if (g_14ce8e0 || g_100f1dc == 1)
			g_774654 = 1;
		if (g_100f1dc == 2) {
			v2 = fcn_00471f80(e2);
			fcn_004c4510(*(int*)(a0 + 1), v2);
			fcn_004c4570(4, 1, 0x69, &v2);
			fcn_004c4570(4, 1, 0x6d, &v2);
			fcn_004c5360(0);
			g_774654 = 1;
		} else if (g_100f1dc == 1) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_005a6570, 0x677c7));
	fcn_00471e30(v8);
	return 0;
}
