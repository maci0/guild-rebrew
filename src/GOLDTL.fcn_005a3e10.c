

typedef struct
{
	int x0;
	int x4;
	char pad8[0x214];
} Player;
// SIZE 0x21c

extern char g_7f4ca0[];
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern char* g_7746cc;
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern char s_6aa830[];

int __cdecl fcn_00470820(int, int, char*);
int __cdecl gm_AccumulateTyped2(Player*);
int __cdecl fcn_0050d270(int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_0050b710(int, char);
void __cdecl fcn_00472380(int, int, int, int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_0050b750(int, char);
void __cdecl fcn_004c5150(int, int, char, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

void __cdecl fcn_005a3e10(void)
{
	int sl;
	int dlg;
	int have;
	int stock;
	int max;
	int v;

	dlg = fcn_00470820(0, 0, s_6aa830);
	have = gm_AccumulateTyped2(&((Player*)g_7f4ca0)[g_774970]);
	stock = fcn_0050d270(*(int*) (g_7746cc + 0x14));
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(dlg, 1);
	fcn_00519190(0x1a4c);
	fcn_004727a0(dlg, 2);
	sl = fcn_00472250(dlg, 2, fcn_00519190(0x1a4d, g_773d75));
	max = fcn_0050b710(stock, g_773d75) + fcn_0050b710(have, g_773d75) > fcn_0050b710(stock, g_773d75) ?
	      fcn_0050b710(stock, g_773d75) + fcn_0050b710(have, g_773d75) : fcn_0050b710(stock, g_773d75);
	fcn_00472380(sl, 0, max, fcn_0050b710(stock, g_773d75));
	fcn_00473a90(0, 0);
	if (fcn_005373e0((void*) fcn_005a3e10, 0x677c7) != 0) {
		do {
			if (g_14ce8e0 != 0 || g_100f1dc == 1) {
				g_774654 = 1;
			}
			if (g_100f1dc == 2) {
				v = fcn_0050b750(fcn_00471f80(sl), g_773d75);
				if (stock < v) {
					fcn_004c5150(*(int*) (g_7746cc + 2), ((Player*)g_7f4ca0)[g_774970].x4, g_773d75, v - stock);
				}
				else {
					fcn_004c5150(((Player*)g_7f4ca0)[g_774970].x4, *(int*) (g_7746cc + 2), g_773d75, stock - v);
				}
				g_774654 = 1;
			}
		} while (fcn_005373e0((void*) fcn_005a3e10, 0x677c7) != 0);
	}
	if (dlg != 0) {
		fcn_00471e30(dlg);
	}
	fcn_00532ef0();
}
