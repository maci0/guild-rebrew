// FUNCTION: GOLDTL 0x005c5b10
// SIZE: 654

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

extern Player g_7f4ca0[];
extern Win g_1015f40[];
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern Name14 g_7f4c00;
extern int g_772514;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern char s_6ac738[];
extern char s_6ac730[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl gm_AccumulateTyped2(Player*);
int __cdecl fcn_0050b710(int, char);
void __cdecl fcn_00472380(int, int, int, int);
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
	fcn_004727a0(dlg, 0);
	g_1015f40[g_772514].x3a8 = 0xe;
	g_1015f40[g_772514].x3ac = 0xe;
	g_1015f40[g_772514].x3b0 = 0xe;
	g_1015f40[g_772514].x3b4 = 0xe;
	fcn_004727a0(dlg, 1);
	fcn_00519190(0x19a9);
	fcn_004727a0(dlg, 2);
	s = fcn_00519190(0x19aa, g_773d75);
	sl = fcn_00472250(dlg, 2, s);
	btn2 = fcn_00472250(dlg, 2, s + 1);
	v = fcn_0050b710(gm_AccumulateTyped2(&g_7f4ca0[g_774970]), g_773d75) > 1000 ? 1000 : fcn_0050b710(gm_AccumulateTyped2(&g_7f4ca0[g_774970]), g_773d75);
	fcn_00472380(sl, 0x64, v, 0x64);
	if (fcn_005373e0((void*) fcn_005c5b10, 0x677c7) != 0) {
		do {
			if (g_100f1dc == 2) {
				if (btn2 != -1 && g_67d370 == btn2) {
					v = fcn_0050b750(fcn_00471f80(sl), g_773d75);
					memset(&pkt, 0, sizeof(pkt));
					pkt.type = 0x38;
					pkt.x8 = g_7f4ca0[g_774970].x4;
					pkt.xc = *(int*) (a + 1);
					pkt.name = g_7f4c00;
					pkt.x36 = 1;
					pkt.x58 = v;
					fcn_004c4eb0(s_6ac730);
					fcn_004c5150(-1, g_7f4ca0[g_774970].x4, g_773d75, v);
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
