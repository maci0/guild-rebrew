

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
	char pad37[0x21];
	int x58;
	int x5c;
	char pad60[0x98];
} Packet;
// SIZE 0xf8

extern unsigned short g_774970;
extern char g_7f4ca0[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_005d2a40(int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_004c5530(Packet*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00412830(int);

int __cdecl fcn_005d2d30(unsigned short* a1)
{
	Packet pkt;
	int cost;
	int dlg;
	int r;
	int h;

	cost = fcn_005d2a40(*(int*) (g_7f4ca0 + g_774970 * 540 + 4), *(int*) (a1 + 2));
	dlg = fcn_00470820(0, 0, "privillegien\\werbung2");
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	fcn_00519190(0x1ce5, *a1, cost);
	g_100f1dc = -1;
	r = 0;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2) {
				memset(&pkt, 0, sizeof(pkt));
				pkt.type = 0x41;
				pkt.x8 = *(int*) (g_7f4ca0 + g_774970 * 540 + 4);
				pkt.xc = pkt.x8;
				pkt.name = (*(Name14*)&g_7f4c00);
				pkt.x36 = 2;
				pkt.x5c = *(int*) (a1 + 2);
				pkt.x58 = pkt.x8;
				h = fcn_004c5530(&pkt);
				while (fcn_004c4450(h) == 0) {
					fcn_00535960();
				}
				r = 1;
				g_774654 = 1;
			} else if (g_100f1dc == 1) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005d2d30, 0x657c7) != 0);
	fcn_00471e30(dlg);
	g_100f1dc = -1;
	fcn_00412830(0x11);
	return r;
}
