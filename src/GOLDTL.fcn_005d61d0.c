// FUNCTION: GOLDTL 0x005d61d0

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

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00525f60(char*, int);
void __cdecl fcn_004c6ae0(int, int);
int __cdecl fcn_004c5530(Packet*);
void __cdecl fcn_00500bb0(Name14*, int, int, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005d61d0(unsigned short* a1)
{
	int dlg;
	Name14 nm;
	Packet pkt;
	char buf[0x100];
	int r;

	r = 0;
	dlg = fcn_00470820(0, 0, "privillegien\\furcht_einfloessen");
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 1);
	fcn_00519190(0x1d62, *a1, *a1, 2, *a1);
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2) {
				if (fcn_00525f60(g_7f4ca0 + g_774970 * 540, 2) != 0) {
					fcn_004c6ae0(*(int*) (g_7f4ca0 + g_774970 * 540 + 4), -2);
					memset(&pkt, 0, sizeof(pkt));
					pkt.type = 0x4b;
					pkt.x8 = *(int*) (g_7f4ca0 + g_774970 * 540 + 4);
					pkt.xc = pkt.x8;
					pkt.name = (*(Name14*)&g_7f4c00);
					pkt.x36 = 2;
					pkt.x5c = *(int*) (a1 + 2);
					pkt.x58 = pkt.x8;
					fcn_004c5530(&pkt);
					nm = (*(Name14*)&g_7f4c00);
					fcn_00500bb0(&nm, 0x18, 0, 0);
					fcn_0051af00(buf, 0x1d63, &nm, *a1);
					fcn_00526120(buf, 0);
					g_774654 = 4;
					r = 1;
				}
			} else if (g_100f1dc == 1) {
				g_774654 = 2;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005d61d0, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return r;
}
