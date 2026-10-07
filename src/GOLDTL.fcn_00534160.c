extern char* g_772500;
extern int g_772514;

// FUNCTION: GOLDTL 0x534160

void __cdecl fcn_0046f740(int, int, int, int);

void __cdecl fcn_00534160(int x0, int y, int len, int t)
{
	int w;
	int n;
	int rem;
	int i;

	w = *(short*) (g_772500 + t * 0x54 + 0x50) + 2;
	n = (int) (len * 0.04761905f);
	rem = n % 2;
	n /= 2;
	for (i = 0; i < n; i++) {
		fcn_0046f740(x0 + i * w, y, t, g_772514);
	}
	if (rem != 0) {
		fcn_0046f740(x0 + i * w, y, t + 1, g_772514);
	}
}
