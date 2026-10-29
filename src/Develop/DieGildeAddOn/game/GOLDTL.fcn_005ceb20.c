


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
	unsigned char x58;
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
	char pad8[0x214];
} Player;
// SIZE 0x21c

typedef struct
{
	char pad0[0x223];
	unsigned char x223;
	char pad224[0x29];
} Shop;
// SIZE 0x24d

extern char g_7f4ca0[];
extern unsigned short g_774970;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned char* lpGebaeudePROT;
extern int g_772514;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern char* g_7746cc;
extern char s_6aca6c[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl gm_CheckEntityType(unsigned char*);
int __cdecl fcn_004c5530(Packet*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00476b60(void);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005ceb20(unsigned char* obj, int mode)
{
	int btn2;
	int btn1;
	Packet pkt;
	char buf[0x200];
	int dlg;
	int s;
	char* p;

	btn2 = -1;
	dlg = fcn_00470820(0, 0, s_6aca6c);
	d2_SetForm(dlg, 0);
	fcn_005340f0(g_772514);
	fcn_00471b60(dlg);
	fcn_00473a90(0, 0);
	d2_SetForm(dlg, 1);
	switch (mode) {
	case 0x20:
		s = fcn_00519190(0x1938);
		btn1 = fcn_00472250(dlg, 1, s);
		btn2 = fcn_00472250(dlg, 1, s + 1);
		break;
	case 0x10:
		fcn_00519190(0x1949);
		fcn_00519190(0x194b);
		btn1 = fcn_00472250(dlg, 1, fcn_00519190(0x194d));
		break;
	default:
		fcn_00471e30(dlg);
		return;
	}
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		else if (g_100f1dc != -1) {
			if (g_67d370 == btn1) {
				for (p = fcn_005463a0(2, 0, 7, 3, *(int*) (obj + 1)); p != 0; p = he_fn_Handlung()) {
					if (p[0xac] == 0) {
						break;
					}
				}
				if (p == 0) {
					memset(&pkt, 0, sizeof(pkt));
					pkt.type = 7;
					pkt.x8 = ((Player*)g_7f4ca0)[g_774970].x4;
					pkt.xc = *(int*) (obj + 1);
					pkt.x36 = 1;
					pkt.name = (*(Name14*)&g_7f4c00);
					pkt.x5c = 1;
					if (gm_CheckEntityType(obj) != 0) {
						pkt.x60 = -1;
					}
					else {
						pkt.x60 = *(int*) (g_7746cc + 2);
					}
					pkt.x58 = 0;
					fcn_004c5530(&pkt);
					fcn_0051af00(buf, 0x1939, ((Shop*)lpGebaeudePROT)[obj[0]].x223 + 0x130);
					fcn_00476b60();
					fcn_00526120(buf, 0);
				}
				g_774654 = 1;
			}
			else if (g_67d370 == btn2) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005ceb20, 0x677c7) != 0);
	fcn_00471e30(dlg);
}
