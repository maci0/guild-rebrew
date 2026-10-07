// FUNCTION: GOLDTL 0x005c6ea0

void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

typedef struct
{
	char b[14];
} Name14;
// SIZE 0xe

typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	int xc;
	char pad10[0x18];
	Name14 name;
	unsigned char x36;
	char pad37[0x21];
	char x58;
	char pad59[3];
	int x5c;
	int x60;
	char pad64[0x94];
} Packet;
// SIZE 0xf8

typedef struct
{
	int x0;
	int x4;
	char pad8[0x180];
	unsigned char x188;
	char pad189[0x93];
} Player;
// SIZE 0x21c

typedef struct
{
	unsigned char x0;
	char pad1[0x24c];
} Shop;
// SIZE 0x24d

extern char g_7f4ca0[];
extern unsigned char* g_868050;
extern unsigned short g_774970;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern int g_14abc44;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern char s_6ac79c[];

char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl fcn_005462a0(void);
void __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_00526120(char*, int);
void __cdecl fcn_0052a0c0(unsigned char*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_004c5530(Packet*);
void __cdecl cm_ExProdObjekt(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_005305a0(void);

void __cdecl fcn_005c6ea0(unsigned char* obj, char* a1, int a2)
{
	int btn2;
	int btn1;
	int dlg;
	Packet pkt;
	char buf[0x800];
	int kind;
	Shop* t;
	int cnt;
	char* p;
	int s;
	int n;
	int i;

	cnt = 0;
	t = &((Shop*)g_868050)[obj[0]];
	if (t->x0 == 4) {
		kind = 1;
	}
	else {
		kind = t->x0 == 0x10 ? 0xf : 0x13;
	}
	for (p = fcn_005463a0(2, 0, 0x16, 3, *(int*) (obj + 1)); p != 0; p = fcn_005462a0()) {
		cnt++;
	}
	if (cnt >= 3) {
		fcn_0051af00(buf, 0x1a4a, cnt);
		fcn_00526120(buf, 0);
		return;
	}
	fcn_0052a0c0(obj, 1);
	dlg = fcn_00470820(0, 0, s_6ac79c);
	fcn_00471b60(dlg);
	fcn_00473a90(0, 0);
	fcn_004727a0(dlg, 1);
	s = fcn_00519190(0x1a45, kind + 0x20d, kind + 0x20e, a2 + 0x16b7);
	btn1 = fcn_00472250(dlg, 1, s);
	btn2 = fcn_00472250(dlg, 1, s + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == btn1) {
				n = 0;
				for (i = 0; i < 768; i++) {
					if (n >= 3) {
						break;
					}
					if (((Player*)g_7f4ca0)[i].x188 != 0) {
						memset(&pkt, 0, sizeof(pkt));
						pkt.type = 0x16;
						pkt.x8 = ((Player*)g_7f4ca0)[g_774970].x4;
						pkt.xc = *(int*) (obj + 1);
						pkt.name = (*(Name14*)&g_7f4c00);
						pkt.x36 = 1;
						if (a1 != 0) {
							pkt.x60 = *(int*) (a1 + 2);
						}
						else {
							pkt.x60 = -1;
						}
						pkt.x5c = ((Player*)g_7f4ca0)[i].x4;
						pkt.x58 = (char) a2;
						fcn_004c5530(&pkt);
						n++;
					}
				}
				if (n == 0) {
					fcn_00526120((char*) g_14abc44, 0);
				}
				else {
					cm_ExProdObjekt();
					if (n > 3) {
						fcn_0051af00(buf, 0x1a4a, 3);
						fcn_00526120(buf, 0);
					}
					g_774654 = 1;
				}
			}
			else if (g_67d370 == btn2) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005c6ea0, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_0052a2d0();
	fcn_00532ef0();
	fcn_005305a0();
}
