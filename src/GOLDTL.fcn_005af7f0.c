// FUNCTION: GOLD 0x005a63c0
// SIZE: 519
// FUNCTION: GOLDTL 0x005af7f0
// SIZE: 519

#include <string.h>

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
	char pad37;
	int ids[6];
	char pad50[8];
	char str[0x20];
	int x78;
	int x7c;
	char pad80[0x78];
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

extern Player g_7f4ca0[];
extern Player* g_7e4260[32];
extern unsigned short g_774970;
extern Name14 g_7f4c00;
extern int g_14abc98;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern char* g_7746c4;
extern char* g_7746cc;
extern char s_6ab348[];

int __cdecl fcn_00526120(int, int);
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

int __cdecl fcn_005af7f0(int unused, char* str)
{
	int btn2;
	int btn1;
	Packet pkt;
	int i;
	int n;
	int dlg;
	int s;

	if (str == 0) {
		return 0;
	}
	for (i = 0; i < 768; i++) {
		if (g_7f4ca0[i].x188 != 0) {
			break;
		}
	}
	if (i >= 768) {
		fcn_00526120(g_14abc98, 0);
		return 0;
	}
	dlg = fcn_00470820(0, 0, s_6ab348);
	fcn_00471b60(dlg);
	fcn_00473a90(0, 0);
	fcn_004727a0(dlg, 1);
	s = fcn_00519190(0x1a70);
	btn1 = fcn_00472250(dlg, 1, s);
	btn2 = fcn_00472250(dlg, 1, s + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == btn1) {
				pkt.type = 0x65;
				pkt.x8 = g_7f4ca0[g_774970].x4;
				pkt.xc = *(int*) (g_7746c4 + 1);
				pkt.name = g_7f4c00;
				pkt.x36 = 2;
				strcpy(pkt.str, str);
				for (i = 0; i < 6; i++) {
					pkt.ids[i] = -1;
				}
				n = 0;
				pkt.x78 = *(int*) (g_7746c4 + 1);
				pkt.x7c = *(int*) (g_7746cc + 2);
				for (i = 0; i < 32; i++) {
					if (n >= 6) {
						break;
					}
					if (g_7e4260[i] != 0 && g_7e4260[i]->x188 != 0) {
						pkt.ids[n] = g_7e4260[i]->x4;
						n++;
					}
				}
				if (n != 0) {
					fcn_004c5530(&pkt);
					cm_ExProdObjekt();
				}
				g_774654 = 2;
			}
			else if (g_67d370 == btn2) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005af7f0, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return 0;
}
