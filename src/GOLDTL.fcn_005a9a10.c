// FUNCTION: GOLD 0x005a06e0
// SIZE: 566
// FUNCTION: GOLDTL 0x005a9a10
// SIZE: 566

typedef struct
{
	int x0;
	int x4;
	int x8;
} Ent;
// SIZE 0xc

typedef struct
{
	int x0;
	int x4;
	char pad8[5];
	unsigned char xd;
	char pade[0x15a];
	unsigned char x168;
	char pad169[0xb3];
} Player;
// SIZE 0x21c

extern Player g_7f4ca0[];
extern unsigned short g_774970;
extern int g_14abb2c;
extern int g_14abb28;
extern int g_14abb38;
extern int g_14abb54;
extern int g_772514;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern char s_6aaebc[];

int __cdecl fcn_00526120(int, int);
int __cdecl fcn_005a96a0(Player*, int);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_004e8ee0(Player*, int, Ent*, int*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_004e8d10(Player*, int, Ent*);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_0046f2c0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005a9a10(void)
{
	int flag;
	int cnt;
	Player* p;
	int prev;
	int btns[6];
	Ent list[6];
	int n;
	int dlg;
	int i;
	int sel;

	prev = -1;
	cnt = 0;
	flag = 1;
	p = &g_7f4ca0[g_774970];
	if (p->xd < 2) {
		fcn_00526120(g_14abb2c, 0);
		return;
	}
	if (p->x168 != 0) {
		fcn_005a96a0(p, p->x168);
		fcn_00532ef0();
		return;
	}
	if (fcn_004e8ee0(p, 6, list, &cnt) == 0) {
		if (cnt == 0) {
			fcn_00526120(g_14abb28, 0);
		}
		else {
			fcn_00526120(g_14abb38, 0);
		}
		return;
	}
	dlg = fcn_00470820(0, 0, s_6aaebc);
	fcn_00471b60(dlg);
	fcn_00473a90(0, 0);
	g_100f1dc = prev;
	do {
		n = fcn_004e8d10(p, 6, list);
		if (n != prev) {
			flag = 1;
		}
		prev = n;
		if (flag != 0) {
			fcn_004727a0(dlg, 1);
			fcn_0046f2c0(g_772514, 1);
			fcn_00519190(0x1a01);
			for (i = 0; i < n; i++) {
				btns[i] = fcn_00472250(dlg, 1, fcn_00519190(0x1a04, list[i].x0 + 0x253));
			}
			for (i = n; i < 6; i++) {
				btns[i] = -1;
			}
			flag = 0;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			sel = -1;
			for (i = 0; i < n; i++) {
				if (btns[i] == g_67d370) {
					sel = i;
					break;
				}
			}
			if (sel > -1 && sel < n) {
				if (fcn_005a96a0(p, list[sel].x0) == 1) {
					fcn_00526120(g_14abb54, 0);
					g_774654 = 1;
				}
			}
		}
	} while (fcn_005373e0((void*) fcn_005a9a10, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
