#include <string.h>

#include "client_types.h"

char* __cdecl fcn_005463a0(int n, ...);
char* __cdecl he_fn_Handlung(void);
char* __cdecl fcn_00508e40(int a1);
char* __cdecl fcn_0051af00(char* buf, int id, ...);
char* __cdecl fcn_00519190(int fmt, ...);
int __cdecl fcn_00470820(int a, int b, char* name);
int __cdecl fcn_00471b60(int);
int __cdecl fcn_00473a90(int, int);
int __cdecl d2_SetForm(int, int);
int __cdecl fcn_00472250(char*, int, char*);
int __cdecl fcn_00471e30(int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl gm_RandomMod(unsigned short n);
void __cdecl fcn_004c5530(char* a);
void __cdecl fcn_004c5150(int a1, int a2, char a3, int a4);
int __cdecl fcn_004c5620(char a1, unsigned char* e);
void __cdecl fcn_00500bb0(char*, int, int, int);
int __cdecl fcn_00526010(char*, int, char);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_005d2ec0(char*, int*);

extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];

/* ADDRESS: GOLDTL 0x005d3120 */
int __cdecl fcn_005d3120(int a0, int* a1)
{
	int mode;
	int id;
	int h;
	int base;
	int q;
	int d;
	int lv[6];
	int ids[9];
	char buf[0xf8];
	char buf2[0x200];
	char buf3[0x200];
	char n;
	char* e;
	char* p;
	char* s;
	int i;
	int v;

	mode = 1;
	base = 0;
	id = -1;
	e = fcn_005463a0(1, 0, 0x41);
	while (e != 0) {
		if (*(int*) (e + 0xac) == *(int*) (a0 + 4)) {
			mode = 2;
			id = *(int*) (e + 0xb0);
			if (*(char*) (e + 0xbb) == 1) {
				mode = 3;
			}
			if (*(char*) (e + 0xba) == 1) {
				mode = 4;
			}
			break;
		}
		e = he_fn_Handlung();
	}
	if (*(char*) (a0 + 2) != 6) {
		if (e != 0) {
			return 0x20;
		}
		p = fcn_00508e40(*(int*) ((char*) a1 + 0x214));
		if (p == 0) {
			return 0x20;
		}
		if (*(char*) (p + 8) == 0) {
			return 0x20;
		}
		memset(buf, 0, 0xf8);
		*(pos14_7f4c00*) (buf + 0x28) = g_7f4c00;
		*(int*) (buf + 0x08) = *(int*) (a0 + 4);
		*(int*) (buf + 0x0c) = *(int*) (a0 + 4);
		*(int*) (buf + 0x58) = *(int*) (a0 + 4);
		buf[0x04] = 0x41;
		buf[0x36] = 2;
		*(int*) (buf + 0x5c) = *(int*) (p + 4);
		fcn_004c5530(buf);
		return 0x10;
	}
	if (mode == 1) {
		return fcn_005d2ec0((char*) a0, a1);
	}
	h = fcn_00470820(0, 0, (char*) 0x6acbbc);
	fcn_00471b60(h);
	fcn_00473a90(0, 0);
	d2_SetForm(h, 1);
	fcn_00519190(0x1cf3);
	if (mode == 2) {
		p = fcn_00508e40(id);
		d = (char) *(e + 0xb9);
		d -= (char) *(e + 0xb8);
		d = d < 0 ? 0 : d;
		fcn_00519190(0x1ce7, *(unsigned short*) a0, *(unsigned short*) p, d, 0x5d);
	} else if (mode == 3) {
		p = fcn_00508e40(id);
		fcn_00519190(0x1ce3);
		fcn_00519190(0x1d31, *(unsigned short*) p);
	} else if (mode == 4) {
		p = fcn_00508e40(id);
		lv[0] = *(int*) (e + 0xc0);
		lv[1] = *(int*) (e + 0xc4);
		lv[2] = *(int*) (e + 0xc8);
		base = *(unsigned char*) (p + 0xd);
		s = e + 0xbc;
		for (i = 4; i < 0xc; i += 4) {
			*(int*) ((char*) &lv[2] + i) = *(unsigned char*) s;
			s++;
		}
		d = (char) *(e + 0xb9);
		d -= (char) *(e + 0xb8);
		fcn_00519190(0x1cf4, *(unsigned short*) p, 0x5d, d, 0x5d);
		ids[0] = fcn_00472250((char*) h, 1,
		                      (char*) fcn_00519190(0x1cf5, lv[3] + 0x1d11, lv[0]));
		ids[1] = fcn_00472250((char*) h, 1,
		                      (char*) fcn_00519190(0x1cf6, lv[4] + 0x1d11, lv[1]));
		ids[2] = fcn_00472250((char*) h, 1,
		                      (char*) fcn_00519190(0x1cf7, lv[5] + 0x1d11, lv[2]));
		ids[3] = fcn_00472250((char*) h, 1, (char*) fcn_00519190(0x1cf8));
	}
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1 && mode == 4) {
			for (i = 0; i < 4; i++) {
				if (g_67d370 == ids[i]) {
					break;
				}
			}
			if (i < 3) {
				if (fcn_00526010(g_7f4ca0 + g_774970 * 540, lv[i], g_773d75) != 0) {
					n = 0;
					p = fcn_00508e40(id);
					q = lv[i];
					d = lv[3 + i] - base;
					{
						float f;

						f = (float) d * *(float*) 0x665bc0;
						if (f <= *(float*) 0x6628a8) {
							f = *(float*) 0x6628a8;
						}
						v = (int) (f * *(float*) 0x6628b0 + *(float*) 0x6628cc);
					}
					if (v > 0) {
						if (v >= 3) {
							n = 3;
						} else {
							n = (char) v;
						}
						if (v == 1) {
							v = 0x1d02 + (gm_RandomMod(5) & 0xffff) + 5;
						} else if (v == 2) {
							v = 0x1d02 + (gm_RandomMod(4) & 0xffff) + 9;
						} else {
							v = 0x1d02 + (gm_RandomMod(3) & 0xffff) + 0xc;
						}
					} else {
						v = 0x1d02 + (gm_RandomMod(5) & 0xffff);
					}
					fcn_0051af00(buf2, 0x1cf9, *(unsigned short*) p, v);
					*(char*) (e + 0xb8) += n;
					if (*(char*) (e + 0xb8) >= *(char*) (e + 0xb9)) {
						*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
						fcn_00500bb0(e + 0x52, 0, 1, 0);
					}
					*(int*) (e + 0x84) = fcn_004c5620(0, (unsigned char*) e);
					fcn_004c5150(-1, *(int*) (a0 + 4), g_773d75, q);
					fcn_00526120(buf2, 0);
					mode = mode;
					g_774654 = 1;
				}
			} else if (i == 3) {
				p = fcn_00508e40(id);
				fcn_0051af00(buf3, 0x1cfa, *(unsigned short*) p);
				*(char*) (e + 0xba) = 0;
				*(int*) (e + 0x84) = fcn_004c5620(0, (unsigned char*) e);
				fcn_00526120(buf3, 0);
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005d3120, 0x657c7) != 0);
	fcn_00471e30(h);
	return 2;
}
