


extern int* g_665f08;

int __cdecl fcn_0057fb20(int* msg)
{
	int* g;
	int r;

	g = g_665f08;
	if (g[14] > 0) {
		if (*msg == 0x29 && msg[3] == 0x155) {
			r = 1;
			g[14] = r;
		} else {
			r = 0;
		}
		return r;
	}
	return 1;
}
