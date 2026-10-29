#include <string.h>
#include "client_types.h"

/* SIZE 0x21c */
typedef struct {
	unsigned short f0;
	int f2;
	int f4;
	char pad8[0x18c];
	int f194;
} House;

extern char* lpObjektePROT;
extern char* g_7746c4;
extern int g_7746c8;
extern int g_7746f8;
extern int g_774654;
extern int g_7747b4;
extern int g_85ab60;
extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_67d370;
extern char* g_773da8;
extern unsigned char g_773d75;
extern unsigned short g_774970;
extern char g_7f4ca0[];
extern char g_7f3f24[];
extern char* g_14a5398;
extern char s_6aa330[];
extern char s_6aa328[];
extern char s_68b7ac[];
extern pos14_7f4c00 g_7f4c00;

int __cdecl fcn_0057ec20(int);
void __cdecl fcn_0057e880(int, int, int, int);
void* __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_0050f780(char*, char*, void*);
int __cdecl fcn_00526120(char*, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00519190(int);
void __cdecl fcn_00527f10(char*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_005c3820(char*);
int __cdecl fcn_0057eba0(int, int, int, int);
void __cdecl fcn_0050f900(void);
void __cdecl fcn_0050ee80(char*, char*);
float __cdecl eval_ObjektPreis2Credits(int, int);
int __cdecl fcn_00526010(char*, int, int);
int __cdecl fcn_00526070(char*, int, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00526920(char*, int, char*);
char* __cdecl fcn_00507a10(char*);
void __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c4ef0(char*);
void __cdecl fcn_004c5150(int, int, char, int);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_004c6ae0(int, int);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c4450(int);
char* __cdecl gm_GetEntityTableEntry(char*);
char* __cdecl fcn_0066080a(char*);
int __cdecl fcn_0064d41a(char*, char*, ...);

/* ADDRESS: GOLDTL 0x0059aa10 */
void __cdecl fcn_0059aa10(char* a0, int a1)
{
	char msg[0xf8];
	char buf[0x100];
	char name[0x80];
	char text[0x70];
	char* house;
	void* q;
	int h;
	char* node;
	int i;
	int sel;
	int ok;
	int v7;
	float f;
	int n;
	int amount;
	int req;
	char* p;
	int s;

	if (a0 == g_7746c4) {
		if (!fcn_0057ec20(0x200))
			return;
		fcn_0057e880(0x11, (int) a0, 0, a1);
	}
	house = &g_7f4ca0[(unsigned int) g_774970 * 0x21c];
	q = fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 0, a1);
	if (!q) {
		q = fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 4, 2);
		if (!q)
			return;
	}
	h = fcn_0050f780(s_6aa330, a0, q);
	if (h <= -1) {
		fcn_00526120(g_14a5398, 0);
		return;
	}
	fcn_00471b60(h);
	d2_SetForm(h, 4);
	h = fcn_00472250(h, 4, fcn_00519190(0x17e2));
	fcn_00527f10(a0);
	while (fcn_005373e0((void*) 0x59aa10, 0x657c7)) {
		if (g_14ce8e0)
			g_774654 = 1;
		if (g_100f1dc != -1 && g_67d370 == h)
			fcn_005c3820(a0);
		if (g_100f1dc >= 0xdf && g_100f1dc <= 0x3bb && g_85ab60 > 0) {
			for (i = 0; i < g_85ab60; i++) {
				p = &g_7f3f24[i * 0x34];
				if (*(int*) p != -1 && *(int*) p == g_67d370)
					break;
			}
			if (i < g_85ab60) {
				sel = g_100f1dc - 0xdf;
				memset(msg, 0, sizeof msg);
				if (fcn_0057eba0(0x2b, (int) a0, 0, sel)) {
					node = lpObjektePROT + sel * 0x41;
					if (house)
						v7 = (int) fcn_00502cd0(*(int*) (house + 0x14), 1, 0, sel);
					else
						v7 = (int) fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 6, 0, sel);
					if (v7) {
						if (house && (((*(unsigned short*) house == 0) == 0xfd) || g_7746c8)) {
							p = node + 1;
							{
								char* d = name;
								while ((*d++ = *p++) != 0)
									;
							}
							fcn_0066080a(name);
							fcn_0064d41a(text, s_68b7ac, name);
							fcn_00526920(a0, *(int*) (house + 2), text);
						}
					} else {
						*(unsigned char*) (msg + 0x36) = 1;
						if (*(unsigned char*) node != 6) {
							*(int*) (msg + 0x0c) = *(int*) (a0 + 1);
							*(int*) (msg + 0x30) = g_7f4c00.c;
							*(unsigned char*) (msg + 4) = 2;
							*(int*) (msg + 8) = *(int*) (g_7f4ca0 + (unsigned int) *(unsigned short*) (a0 + 0x25) * 0x21c + 4);
							*(int*) (msg + 0x28) = g_7f4c00.a;
							*(int*) (msg + 0x2c) = g_7f4c00.b;
							*(short*) (msg + 0x34) = g_7f4c00.d;
							*(short*) (msg + 0x58) = (short) sel;
							*(int*) (msg + 0x5c) = *(int*) (house + 2);
						} else {
							*(int*) (msg + 0x0c) = *(int*) (a0 + 1);
							*(unsigned char*) (msg + 4) = 0x0c;
							*(int*) (msg + 0x58) = *(int*) (a0 + 1);
							*(int*) (msg + 0x60) = sel;
							*(int*) (msg + 8) = *(int*) (g_7f4ca0 + (unsigned int) *(unsigned short*) (a0 + 0x25) * 0x21c + 4);
							*(int*) (msg + 0x28) = g_7f4c00.a;
							*(int*) (msg + 0x2c) = g_7f4c00.b;
							*(int*) (msg + 0x30) = g_7f4c00.c;
							*(short*) (msg + 0x34) = g_7f4c00.d;
							*(int*) (msg + 0x5c) = *(int*) (msg + 8);
						}
						req = *(unsigned char*) (node + 0x40);
						if (req == 0) {
							f = (float) (g_7747b4 * 0.25 + 0.5);
							n = (int) eval_ObjektPreis2Credits(sel, 100);
							amount = (int) (n * f);
							ok = 0;
							if (*(unsigned short*) (a0 + 0x27) != *(unsigned short*) g_773da8) {
								v7 = fcn_00526010(house, amount, g_773d75);
								req = 0x1a;
							} else {
								p = fcn_00507a10(a0);
								v7 = fcn_00526070(p, *(int*) (p + 0x14), amount, g_773d75);
								req = 0x1c;
							}
							if (v7)
								ok = 1;
							fcn_0051af00(buf, req, amount, a0, sel * 2 + 0x9a8);
							if (ok && fcn_00526120(buf, 1)) {
								fcn_0057e880(0x2b, (int) a0, 0, sel);
								fcn_004c4eb0(s_6aa328);
								if (*(unsigned short*) (a0 + 0x27) != *(unsigned short*) g_773da8) {
									fcn_004c5150(-1, *(int*) (g_7f4ca0 + (unsigned int) *(unsigned short*) (a0 + 0x27) * 0x21c + 4), (char) g_773d75, amount);
									p = gm_GetEntityTableEntry(house);
									if (p)
										*(int*) (p + 0x40) += amount;
								} else {
									p = fcn_00507a10(a0);
									if (p)
										fcn_004c51a0(-1, *(int*) (p + 2), (char) g_773d75, amount);
								}
								s = fcn_004c5530(msg);
								fcn_004c4ef0(s_6aa328);
								goto wait;
							}
						} else {
							fcn_0051af00(buf, 0x1b, req, a0, sel * 2 + 0x9a8);
							if (fcn_00526120(buf, 1)) {
								if (req > *(int*) (house + 0x194)) {
									fcn_0051af00(buf, 0x74, req);
									fcn_00526120(buf, 0);
								} else {
									fcn_004c4eb0(s_6aa328);
									fcn_004c6ae0(*(int*) (house + 4), -req);
									s = fcn_004c5530(msg);
									fcn_004c4ef0(s_6aa328);
									goto wait;
								}
							}
						}
					}
				}
			}
		}
		goto tail;
wait:
		if (s != -1) {
			while (fcn_004c4450(s) == 0)
				fcn_005373e0(0, 0x657c7);
		}
tail:
		fcn_0050ee80(a0, house);
	}
	fcn_0050f900();
	g_7746f8 = 0;
	if (a0 == g_7746c4)
		fcn_0057e880(0x11, (int) a0, 1, a1);
}
