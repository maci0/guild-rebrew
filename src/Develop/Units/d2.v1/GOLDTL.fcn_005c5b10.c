

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
	char pad5c[0x9c];
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
	char pad0[0x3a8];
	int x3a8;
	int x3ac;
	int x3b0;
	int x3b4;
	char pad3b8[0x14];
} Win;
// SIZE 0x3cc

extern char g_7f4ca0[];
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern pos14_7f4c00 g_7f4c00;
extern int g_772514;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern char s_6ac738[];
extern char s_6ac730[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl gm_AccumulateTyped2(Player*);
int __cdecl fcn_0050b710(int, char);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl fcn_00471f80(int);
int __cdecl fcn_0050b750(int, char);
void __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c5150(int, int, char, int);
int __cdecl fcn_004c5530(Packet*);
void __cdecl fcn_004c4ef0(char*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005c5b10(char* a)
{
	int btn2;
	Packet pkt;
	int dlg;
	int s;
	int sl;
	int v;

	dlg = fcn_00470820(0, 0, s_6ac738);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	((Win*)g_1015f40)[g_772514].x3a8 = 0xe;
	((Win*)g_1015f40)[g_772514].x3ac = 0xe;
	((Win*)g_1015f40)[g_772514].x3b0 = 0xe;
	((Win*)g_1015f40)[g_772514].x3b4 = 0xe;
	d2_SetForm(dlg, 1);
	io_AppendText(0x19a9);
	d2_SetForm(dlg, 2);
	s = io_AppendText(0x19aa, g_773d75);
	sl = fcn_00472250(dlg, 2, s);
	btn2 = fcn_00472250(dlg, 2, s + 1);
	v = fcn_0050b710(gm_AccumulateTyped2(&((Player*)g_7f4ca0)[g_774970]), g_773d75) > 1000 ? 1000 : fcn_0050b710(gm_AccumulateTyped2(&((Player*)g_7f4ca0)[g_774970]), g_773d75);
	d2_SetElementValue(sl, 0x64, v, 0x64);
	if (fcn_005373e0((void*) fcn_005c5b10, 0x677c7) != 0) {
		do {
			if (g_100f1dc == 2) {
				if (btn2 != -1 && g_67d370 == btn2) {
					v = fcn_0050b750(fcn_00471f80(sl), g_773d75);
					memset(&pkt, 0, sizeof(pkt));
					pkt.type = 0x38;
					pkt.x8 = ((Player*)g_7f4ca0)[g_774970].x4;
					pkt.xc = *(int*) (a + 1);
					pkt.name = (*(Name14*)&g_7f4c00);
					pkt.x36 = 1;
					pkt.x58 = v;
					fcn_004c4eb0(s_6ac730);
					fcn_004c5150(-1, ((Player*)g_7f4ca0)[g_774970].x4, g_773d75, v);
					fcn_004c5530(&pkt);
					fcn_004c4ef0(s_6ac730);
					g_774654 = 1;
				}
			}
			else if (g_100f1dc == 1) {
				g_774654 = 1;
			}
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
		} while (fcn_005373e0((void*) fcn_005c5b10, 0x677c7) != 0);
	}
	fcn_00532ef0();
	fcn_00471e30(dlg);
}
