// FUNCTION: GOLD 0x00577710
// FUNCTION: GOLDTL 0x57fce0

extern int* g_665f08;

int __cdecl fcn_0057fce0(int* msg)
{
	int* g;
	int r;

	g = g_665f08;
	if (g[14] >= 0 && *msg == 0x26 && msg[3] == 0x1d0) {
		r = 1;
		g[14] = r;
	} else if (*msg == 0x1a || *msg == 0x1c) {
		r = 1;
	} else {
		r = 0;
	}
	return r;
}
