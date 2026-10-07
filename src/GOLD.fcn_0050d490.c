extern int g_6f1c28;
extern signed char g_76faa0[];
extern signed char g_76fa60[];

// SIZE 0x3e0
struct s_fd7c50 {
	int p;
	char pad[0x3dc];
};

extern struct s_fd7c50 g_fd7c50[64];

// FUNCTION: GOLD 0x0050d490
/* Twin of GOLDTL 0x510930; the GOLD slot records are 0x3e0 bytes, not 0x3dc. */

void __cdecl fcn_004478e0(int, int);
void __cdecl fcn_00457c20(int);
void __cdecl fcn_004473f0(void);
void __cdecl fcn_0045ef50(int);

void __cdecl fcn_0050d490(void)
{
	int i;

	fcn_004478e0(0, 0);
	if (g_6f1c28 != 0) {
		fcn_00457c20(g_6f1c28);
		g_6f1c28 = 0;
	}
	fcn_004473f0();
	for (i = 0; i < 0x2dc; i++) {
		if (g_76faa0[i] > 0) {
			fcn_004478e0(g_76faa0[i], 0);
			fcn_004473f0();
			g_76faa0[i] = -1;
		}
	}
	for (i = 0; i < 0x22; i++) {
		if (g_76fa60[i] > 0) {
			fcn_004478e0(g_76fa60[i], 0);
			fcn_004473f0();
			g_76fa60[i] = -1;
		}
	}
	for (i = 0; i < 64; i++) {
		if (g_fd7c50[i].p != 0) {
			fcn_0045ef50(g_fd7c50[i].p);
			g_fd7c50[i].p = 0;
		}
	}
}
