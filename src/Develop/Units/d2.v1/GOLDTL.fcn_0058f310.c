#include "client_types.h"

extern int g_772514;
extern unsigned short g_774970;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern int g_7e46ac;
extern int g_14b556c;
extern int g_14b5574;
extern int g_14b5588;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_7f4ca0[];
extern char g_7f4ca4[];

void* __cdecl fcn_005cd440(void*, char*, int, int);
int __cdecl fcn_00532ef0(void);
void __cdecl fcn_0052a0c0(char*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_00525f60(char*, int);
void __cdecl fcn_00526120(int, int);
int __cdecl fcn_004a5e60(unsigned short*, int, int, int, float, float, int*);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_0052ae70(void);

/* ADDRESS: GOLDTL 0x0058f310 */
int __cdecl fcn_0058f310(char* a0)
{
	int q[20];
	char req[0xf8];
	int flag;
	int b1;
	int b2;
	int b3;
	int n;
	int sel;
	int i;
	int idx;
	int id;
	int h;
	char* v;
	char* hh;

	for (i = 0; i < 20; i++) {
		q[i] = 0;
	}
	for (i = 7; i < 15; i++) {
		q[i] = -1;
	}
	q[0] = 1;
	q[1] = 0x400;
	q[4] = 6;
	v = (char*) fcn_005cd440(q, (char*) g_14b5574, 0, 0);
	if (v == 0) {
		return fcn_00532ef0();
	}
	fcn_0052a0c0(a0, 0);
	h = fcn_00470820(0, 0, (char*) 0x6a96d8);
	fcn_00473a90(0, 0);
	fcn_00471b60(h);
	d2_SetForm(h, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(h, 1);
	n = fcn_00519190(0x4098, 0x4097, *(unsigned short*) v, *(unsigned short*) v);
	b1 = fcn_00472250(h, 1, n);
	d2_SetForm(h, 2);
	n = fcn_00519190(0x4099);
	b2 = fcn_00472250(h, 2, n);
	b3 = fcn_00472250(h, 2, n + 1);
	fcn_00472380(b1, 4, 0xc, 4);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == b2) {
				flag = 0;
				n = fcn_00471f80(b1);
				idx = g_774970;
				if (fcn_00525f60(g_7f4ca0 + idx * 0x21c, n) == 0) {
					flag = 1;
				}
				hh = 0;
				for (i = 0; i < 768; i++) {
					if (*(unsigned char*) (g_7f4ca0 + i * 0x21c + 0x188) != 0) {
						hh = g_7f4ca0 + i * 0x21c;
						break;
					}
				}
				if (hh == 0) {
					fcn_00526120(g_14b556c, 0);
				} else if (flag == 0) {
					for (i = 0; i < 0x3e; i++) {
						*(int*) (req + i * 4) = 0;
					}
					req[4] = (char) 0x88;
					req[0x36] = 2;
					*(int*) (req + 0x64) = n;
					*(int*) (req + 0xc) = *(int*) (a0 + 1);
					*(int*) (req + 0x2c) = g_7f4c04;
					*(short*) (req + 0x34) = g_7f4c0c;
					*(int*) (req + 8) = *(int*) (g_7f4ca4 + *(unsigned short*) (a0 + 0x27) * 0x21c);
					*(int*) (req + 0x28) = g_7f4c00;
					*(int*) (req + 0x30) = g_7f4c08;
					*(int*) (req + 0x5c) = *(int*) (v + 4);
					*(int*) (req + 0x60) = *(int*) (hh + 4);
					*(int*) (req + 0x38) = *(int*) (hh + 4);
					if (*(int*) (v + 0x170) != 0) {
						sel = *(int*) (*(int*) (v + 0x170) + 1);
					} else if (*(int*) (v + 0x16c) != 0) {
						sel = *(int*) (*(int*) (v + 0x16c) + 1);
					} else {
						sel = -1;
						fcn_004a5e60((unsigned short*) (g_7f4ca0 + idx * 0x21c), 0, 0x7b4c4a0, 0, 0.0f,
						    100.0f, &sel);
					}
					*(int*) (req + 0x58) = sel;
					id = fcn_004c5530(req);
					if (id != -1) {
						while (fcn_004c4450(id) == 0) {
							fcn_005373e0(0, 0x20007);
						}
					}
					g_7e46ac = 0x677c7;
					g_774654 = 1;
					fcn_00526120(g_14b5588, 0);
				}
			} else if (g_67d370 == b3) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_0058f310, 0x677c7) != 0);
	fcn_00471e30(h);
	fcn_0052a2d0();
	fcn_0052ae70();
	return fcn_00532ef0();
}
