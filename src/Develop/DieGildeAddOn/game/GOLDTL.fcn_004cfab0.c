extern int g_9ba2e0[0x20];
extern int g_772514;
extern double g_662c38;

char __cdecl fcn_00443e10(int, int*);
void __cdecl fcn_004ceac0(int, int);
int __cdecl fcn_0046e940(int, int, int, int, int);
void __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_00507e30(int, int, int);
void __cdecl fcn_00534160(int, int, int);
float __cdecl fcn_004ff040(int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00472380(int, int, int, int);

/* ADDRESS: GOLDTL 0x004cfab0 */
void __cdecl fcn_004cfab0(int a0, int a1)
{
	int rect[4];
	int w;
	int h;
	int x0;
	int y0;
	int slot;

	if (!fcn_00443e10(*(int*) (*(int*) (a1 + 0x184) + 0x34), rect)) {
		return;
	}
	w = rect[2] - rect[0] + 0x20;
	x0 = rect[0] - 0x10;
	y0 = rect[1] - 0x10;
	if (w <= 0x6e) {
		w = 0x6e;
	}
	h = rect[3] - rect[1] + 0x20;
	for (slot = 0; slot < 0x20; slot++) {
		if (g_9ba2e0[slot] == -1) {
			fcn_004ceac0(a0, a1);
			g_9ba2e0[slot] = fcn_0046e940(x0, y0, w, h, 0x10);
			fcn_0046f740(0, 0, 0x7b0, g_772514);
			fcn_0046f740(w - 0x18, 0, 0x7b1, g_772514);
			*(int*) (0x10161cc + g_772514 * 0x3cc) = 0x54;
			fcn_00534160(4, 4, fcn_00507e30(a1, 3, 0x4df));
			fcn_00472380(fcn_004677e0(0, 0xe, 0x40, 0, 0x64, 0x75, 0x442, g_772514), 0, 0x64,
			    (int) (fcn_004ff040(a1) * g_662c38));
			return;
		}
	}
}
