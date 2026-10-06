// FUNCTION: GOLD 0x00594020
// FUNCTION: GOLDTL 0x0059cde0

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
	int ids[8];
	char str[0x20];
	char pad78[0x80];
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
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern unsigned char* g_7746c8;
extern char s_6aa464[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
char* __cdecl fcn_005463a0(int, int, int, int, int, int, int);
char* __cdecl fcn_005462a0(void);
int __cdecl fcn_004c5530(Packet*);
void __cdecl cm_ExProdObjekt(void);
void __cdecl fcn_005305a0(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_0059cde0(char* name)
{
	int btn2;
	int dlg;
	int btn1;
	Packet pkt;
	int r;
	int s;
	char* p;
	int* q;
	int i;

	r = 0;
	if (name == 0) {
		return 0;
	}
	dlg = fcn_00470820(0, 0, s_6aa464);
	fcn_00471b60(dlg);
	fcn_00473a90(0, 0);
	fcn_004727a0(dlg, 1);
	s = fcn_00519190(0x1a95);
	btn1 = fcn_00472250(dlg, 1, s);
	btn2 = fcn_00472250(dlg, 1, s + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == btn1) {
				for (p = fcn_005463a0(3, 0, 0x48, 2, *(unsigned short*) (((char*)g_7746c8) + 0x27), 3, *(int*) (((char*)g_7746c8) + 1)); p != 0; p = fcn_005462a0()) {
					if (strcmp(p + 0xac, name) == 0) {
						break;
					}
				}
				if (p == 0) {
					pkt.type = 0x48;
					pkt.x8 = ((Player*)g_7f4ca0)[*(unsigned short*) (((char*)g_7746c8) + 0x27)].x4;
					pkt.xc = *(int*) (((char*)g_7746c8) + 1);
					pkt.name = (*(Name14*)&g_7f4c00);
					pkt.x36 = 2;
					strcpy(pkt.str, name);
					for (i = 0; i < 8; i++) {
						pkt.ids[i] = -1;
					}
					cm_ExProdObjekt();
					q = pkt.ids;
					for (i = 0; i < 32; i++) {
						if (((Player**)g_7e4260)[i] != 0 && ((Player**)g_7e4260)[i]->x188 != 0) {
							*q = ((Player**)g_7e4260)[i]->x4;
							q++;
						}
					}
					fcn_004c5530(&pkt);
				}
				fcn_005305a0();
				r = 1;
				g_774654 = 1;
			}
			else if (g_67d370 == btn2) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_0059cde0, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return r;
}
