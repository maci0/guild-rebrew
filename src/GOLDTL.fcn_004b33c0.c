extern int g_67fca8;
extern int g_67fca4;
extern unsigned char g_7728d4;
extern int g_7f4c00;

int __cdecl fcn_004b3010(int pos, int n, int* out, int a1);
void __cdecl fcn_004b2e20(char* out, int pos);

/* ADDRESS: GOLDTL 0x004b33c0 */
int __cdecl fcn_004b33c0(int a0, char* a1)
{
	int v5;
	int v4[4];
	int diff;

	do {
		if (g_7728d4 == 0)
			return 3;
		if (fcn_004b3010(g_67fca8, 3, v4, a0) == 0) {
			g_7728d4 = 0;
			return 4;
		}
		diff = g_7f4c00 - v4[0];
		if (diff == 1) {
			v5 = 1;
			fcn_004b2e20(a1, g_67fca8 + 1);
			if (*a1 == 0)
				v5 = 6;
		} else if (diff > 1) {
			v5 = 0;
		} else {
			return 2;
		}
		g_67fca8 += 3;
		if (g_67fca4 < g_67fca8)
			g_7728d4 = 0;
	} while (v5 == 0 || v5 == 6);
	return v5;
}
