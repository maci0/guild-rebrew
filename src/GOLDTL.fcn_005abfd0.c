// FUNCTION: GOLDTL 0x005abfd0
// SIZE: 625

typedef struct
{
	int x0;
	int x4;
	char pad8[0x214];
} Player;
// SIZE 0x21c

extern Player g_7f4ca0[];
extern unsigned short g_774970;
extern int g_772514;
extern int g_14ab930;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern char s_6ab060[];

int __cdecl fcn_004f5da0(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_00525f60(Player*, int);
void __cdecl fcn_005100f0(int, int);
void __cdecl fcn_005b21d0(Player*, Player*, unsigned char*);
void __cdecl fcn_004f5e20(int, int);
int __cdecl fcn_00526120(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005abfd0(unsigned char* e)
{
	int flag;
	int btnA;
	int btnB;
	int btnC;
	int dlg;
	int amt;
	int v;
	Player* me;

	flag = 0;
	btnA = -1;
	btnC = -1;
	btnB = -1;
	if (*(unsigned short*) (e + 0x27) == 0xffff) {
		return;
	}
	amt = fcn_004f5da0(g_7f4ca0[g_774970].x4);
	dlg = fcn_00470820(0, 0, s_6ab060);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 0);
	fcn_005340f0(g_772514);
	fcn_00473a90(0, 0);
	fcn_004727a0(dlg, 1);
	fcn_00519190(0x197f);
	if (amt != 0) {
		btnB = fcn_00472250(dlg, 1, fcn_00519190(0x1981, amt));
		fcn_00472380(btnB, 2, 6, 2);
		btnA = fcn_00472250(dlg, 1, fcn_00519190(0x1982));
		btnC = fcn_00472250(dlg, 1, fcn_00519190(0x1983));
		flag = 1;
	}
	else {
		fcn_00519190(0x1980);
	}
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1 && flag != 0) {
			if (g_67d370 == btnA) {
				me = &g_7f4ca0[g_774970];
				v = fcn_00471f80(btnB);
				if (fcn_00525f60(me, v) != 0) {
					fcn_005100f0(me->x4, -v);
					if (*(unsigned short*) (e + 0x27) != 0xffff && *(unsigned short*) (e + 0x27) != g_774970) {
						fcn_005100f0(g_7f4ca0[*(unsigned short*) (e + 0x27)].x4, 1);
						fcn_005b21d0(&g_7f4ca0[g_774970], &g_7f4ca0[*(unsigned short*) (e + 0x27)], e);
					}
					fcn_004f5e20(me->x4, v / 2);
					fcn_00526120(g_14ab930, 0);
					g_774654 = 1;
				}
			}
			else if (g_67d370 == btnC) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005abfd0, 0x677c7) != 0);
	fcn_00532ef0();
	fcn_00471e30(dlg);
}
