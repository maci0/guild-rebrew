// FUNCTION: GOLDTL 0x005b58a0

typedef struct
{
	char pad0[0x18];
	int x18;
	char pad1c[0x40];
	int x5c;
	char pad60[0xc];
	int x6c;
	char pad70[0x2f4 - 0x70];
} Ctl;
// SIZE 0x2f4

typedef struct
{
	int x;
	int y;
	int x8;
	int icon;
	int x10;
	int label;
	int value;
	int x1c;
	int x20;
	int x24;
	int a[6];
	int b[6];
	int x58;
} Gauge;
// SIZE 0x5c

extern int g_772514;
extern int g_772534;
extern char* g_1015ea0;
extern char* g_14abc28;

int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0046fac0(int, int, int, int);

void __cdecl fcn_005b58a0(int x, int y, Gauge* s)
{
	int i;

	s->icon = fcn_0046f740(x, y, 0x5db, g_772514);
	((Ctl*)g_1015ea0)[s->icon].x5c = 1;
	s->label = fcn_0046fac0(x - 0x36, y - 0x11, (*(int*)&g_14abc28), g_772514);
	((Ctl*)g_1015ea0)[s->label].x18 = 0xa0;
	((Ctl*)g_1015ea0)[s->label].x6c = 1;
	s->value = fcn_0046fac0(x - 0x36, y + 0x44, (int) "", g_772514);
	((Ctl*)g_1015ea0)[s->value].x18 = 0xa0;
	((Ctl*)g_1015ea0)[s->value].x6c = 1;
	s->x1c = -1;
	s->x10 = -1;
	s->x8 = 0;
	s->x24 = 0;
	s->x58 = g_772534;
	s->y = y;
	s->x = x;
	for (i = 0; i < 6; i++) {
		s->a[i] = -1;
		s->b[i] = -1;
	}
}
