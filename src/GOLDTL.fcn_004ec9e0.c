// FUNCTION: GOLD 0x004eac60
// SIZE: 181
// FUNCTION: GOLDTL 0x004ec9e0
// SIZE: 181

typedef struct
{
	int a;
	int b;
	int c;
} V12;
// SIZE 0xc

typedef struct
{
	int active;
	V12 v;
	int y;
	int x;
} Slot18;
// SIZE 0x18

extern int g_772f78;
extern int g_772f7c;
extern int g_772f80;
extern int g_772f84;
extern int g_772f88;
extern Slot18 g_772f90[3];
extern int g_772fd8;
extern V12* g_772fdc;

void __cdecl fcn_004ecaa0(int a);

void __cdecl fcn_004ec9e0(void)
{
	int i;

	if (g_772fd8 == 0) {
		return;
	}
	for (i = 0; i < 3; i++) {
		g_772f90[i].v = g_772fdc[g_772f88 % g_772fd8];
		g_772f88++;
		g_772f90[i].active = 1;
		g_772f90[i].x = g_772f80;
		g_772f90[i].y = g_772f78;
		g_772f80 = (g_772f84 + g_772f80) % 25;
		g_772f78 = (g_772f7c + g_772f78) % 25;
	}
	if (g_772f88 >= g_772fd8) {
		fcn_004ecaa0(1);
	}
}
