


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
	int x58;
	int x5c;
	int x60;
	int x64;
	char pad68[0x90];
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

extern char g_7f4ca0[];
extern char* g_7e4260[32];
extern unsigned short g_774970;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern int g_14abc98;
extern int g_14b5290;
extern int g_14abcf0;
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

int __cdecl fcn_005afa50(int unused, char* e)
{
	int btn1;
	Packet pkt;
	int i;
	int n;
	int dlg;
	int s;
	int btn2;

	if (e == 0) {
		return 0;
	}
	for (i = 0; i < 768; i++) {
		if (((Player*)g_7f4ca0)[i].x188 != 0) {
			break;
		}
	}
	if (i >= 768) {
		fcn_00526120(g_14abc98, 0);
		return 0;
	}
	if (e[0x5b] & 8) {
		fcn_00526120(g_14b5290, 0);
		return 0;
	}
	dlg = fcn_00470820(0, 0, s_6ab348);
	fcn_00471b60(dlg);
	fcn_00473a90(0, 0);
	fcn_004727a0(dlg, 1);
	s = fcn_00519190(0x1a73, e);
	btn1 = fcn_00472250(dlg, 1, s);
	btn2 = fcn_00472250(dlg, 1, s + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == btn1) {
				memset(&pkt, 0, sizeof(pkt));
				pkt.type = 0x64;
				pkt.x8 = ((Player*)g_7f4ca0)[g_774970].x4;
				pkt.xc = *(int*) (g_7746c4 + 1);
				pkt.name = (*(Name14*)&g_7f4c00);
				pkt.x36 = 1;
				pkt.x5c = *(int*) (e + 1);
				pkt.x60 = *(int*) (g_7746c4 + 1);
				pkt.x64 = *(int*) (g_7746cc + 2);
				for (i = 0; i < 32; i++) {
					if (((Player**)g_7e4260)[i] != 0 && ((Player**)g_7e4260)[i]->x188 != 0) {
						pkt.x58 = ((Player**)g_7e4260)[i]->x4;
						fcn_004c5530(&pkt);
						cm_ExProdObjekt();
						break;
					}
				}
				n = 0;
				for (i = 0; i < 32; i++) {
					if (((Player**)g_7e4260)[i] != 0 && ((Player**)g_7e4260)[i]->x188 != 0) {
						n++;
					}
				}
				if (n > 1) {
					fcn_00526120(g_14abcf0, 4);
				}
				g_774654 = 2;
			}
			else if (g_67d370 == btn2) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005afa50, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return 0;
}
