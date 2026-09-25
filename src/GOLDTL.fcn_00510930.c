extern int g_773dd8;
extern signed char g_7f3b40[];
extern signed char g_7f3b00[];

// SIZE 0x3dc
struct s_1043370 {
	int p;
	char pad[0x3d8];
};

extern struct s_1043370 g_1043370[64];

// FUNCTION: GOLDTL 0x510930
// SIZE: 182

void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_00454560(int);
void __cdecl fcn_00442e30(void);
void __cdecl gv_Free3Fields(int);

void __cdecl fcn_00510930(void)
{
	int i;

	fcn_004432d0(0, 0);
	if (g_773dd8 != 0) {
		fcn_00454560(g_773dd8);
		g_773dd8 = 0;
	}
	fcn_00442e30();
	for (i = 0; i < 0x2dc; i++) {
		if (g_7f3b40[i] > 0) {
			fcn_004432d0(g_7f3b40[i], 0);
			fcn_00442e30();
			g_7f3b40[i] = -1;
		}
	}
	for (i = 0; i < 0x22; i++) {
		if (g_7f3b00[i] > 0) {
			fcn_004432d0(g_7f3b00[i], 0);
			fcn_00442e30();
			g_7f3b00[i] = -1;
		}
	}
	for (i = 0; i < 64; i++) {
		if (g_1043370[i].p != 0) {
			gv_Free3Fields(g_1043370[i].p);
			g_1043370[i].p = 0;
		}
	}
}
