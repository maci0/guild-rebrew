typedef struct
{
	char pad0[0x50];
	short w;
	short h;
} fcn_005caaa0_Def;
// SIZE 0x54

// SIZE 0x21c
typedef struct
{
	char pad0[4];
	int id;
	char pad8[0x21c - 8];
} fcn_005caaa0_Ent;

// SIZE 0x2f4
typedef struct
{
	char pad0[0x5c];
	int f5c;
	char pad60[0x1d0 - 0x60];
	int f1d0;
	char pad1d4[0x2f0 - 0x1d4];
	char* owner;
} fcn_005caaa0_Tile;

typedef struct
{
	char* e;
	int tile;
	int bar;
	char padc[0xc];
	int icon;
	int f1c;
	int f20;
	int f24;
	int f28;
	char pad2c[4];
	int f30;
} fcn_005caaa0_Sel;

extern char* g_772500;
extern int g_772514;
extern char* g_1015ea0;
extern char g_7f4ca0[];
extern unsigned short g_774970;

int __cdecl fcn_0046f740(int x, int y, int a3, int win);
int __cdecl fcn_004677e0(int x, int y, int a3, int a4, int a5, int a6, int a7, int win);
void __cdecl fcn_00472380(int, int, int, ...);
void __cdecl fcn_00472640(int i, int flag);
float __cdecl fcn_0050f980(int a, int b, int c);

/* ADDRESS: GOLDTL 0x005caaa0 */
int __cdecl fcn_005caaa0(int x, int y, int win, fcn_005caaa0_Sel* s)
{
	int cx;
	int b;

	cx = x + ((fcn_005caaa0_Def*)g_772500)[1498].w / 2;
	s->tile = fcn_0046f740(x, y, 0x5da, g_772514);
	s->bar = -1;
	if (s->e != 0) {
		s->icon = fcn_0046f740(cx - ((fcn_005caaa0_Def*)g_772500)[*(int*) (s->e + 0x18c)].w / 2 - 3, y + 1, *(int*) (s->e + 0x18c), g_772514);
		fcn_0046f740(x + 3, y + 3, s->f1c, g_772514);
		if (s->f20 != 0)
			fcn_0046f740(x + 3, ((fcn_005caaa0_Def*)g_772500)[1498].h + y - 0x13, s->f20, g_772514);
		if (s->f24 != 0)
			fcn_0046f740(((fcn_005caaa0_Def*)g_772500)[1498].w + x - 0x10, y + 3, s->f24, g_772514);
		fcn_0046f740(((fcn_005caaa0_Def*)g_772500)[1498].w + x - 0x10, ((fcn_005caaa0_Def*)g_772500)[1498].h + y - 0x13, s->f28, g_772514);
		if (s->e[2] != 6) {
			b = fcn_004677e0(cx - 0x23, ((fcn_005caaa0_Def*)g_772500)[1498].h + y + 2, 0x40, 0, 0x64, 0x75, 0x442, g_772514);
			s->bar = b;
			if (s->e[2] == 7)
				fcn_00472380(b, 0, 0x64, 0, 1);
			else
				fcn_00472380(s->bar, 0, 0x64, (int) fcn_0050f980(g_774970, *(unsigned short*) s->e, 1));
			fcn_00472640(s->bar, 0);
		}
		if (*(int*) (s->e + 0x210) == ((fcn_005caaa0_Ent*)g_7f4ca0)[g_774970].id)
			fcn_0046f740(((fcn_005caaa0_Def*)g_772500)[1498].w + x, y, 0x6d3, g_772514);
		if (s->f30 != 0) {
			((fcn_005caaa0_Tile*)g_1015ea0)[s->tile].f5c = 1;
			((fcn_005caaa0_Tile*)g_1015ea0)[s->tile].f1d0 = 3;
			((fcn_005caaa0_Tile*)g_1015ea0)[s->tile].owner = s->e;
		}
		if (s->e[2] == 5 || s->e[2] == 6 || s->e[2] == 7)
			fcn_0046f740(x - 0x20, y, *(int*) (s->e + 0x54), g_772514);
	} else {
		fcn_0046f740(cx - ((fcn_005caaa0_Def*)g_772500)[1275].w / 2 - 3, y + 1, 0x4fb, g_772514);
	}
	return 0;
}
