// FUNCTION: GOLDTL 0x57fd20
// FUNCTION: GOLD 0x00577750

extern int* g_665f08;

void __cdecl fcn_00535550(int);
void __cdecl fcn_00535560(int);

int __cdecl fcn_0057fd20(void)
{
	int* g;

	g = g_665f08;
	if (g[16] == 2 && g[20] != 0) {
		fcn_00535550(g[20]);
		return 0;
	}
	if (g[16] == 3 && g[20] != 0) {
		fcn_00535560(g[20]);
	}
	return 0;
}
