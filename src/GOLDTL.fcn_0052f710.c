extern int g_6a25b8;
extern int g_6a25bc;
extern int g_6a25c0;
extern int g_6a25c4[4];
extern int g_6a25d4;
extern int g_6a25d8;
extern int g_6a25dc;
extern int g_6a25e0;
extern int g_6a25e4;
extern int g_6a25e8;
extern int g_6a25ec;
extern int g_6a25f0;



void __cdecl fcn_0046b2b0(int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_0052f710(void)
{
	int i;

	if (g_6a25b8 != -1) {
		for (i = 0; i < 4; i++) {
			if (g_6a25c4[i] != -1) {
				fcn_0046b2b0(g_6a25c4[i]);
				g_6a25c4[i] = -1;
			}
		}
		fcn_00471e30(g_6a25b8);
		g_6a25b8 = -1;
		g_6a25bc = -1;
		g_6a25c0 = -1;
		g_6a25f0 = -1;
		g_6a25ec = -1;
		g_6a25e4 = -1;
		g_6a25e8 = -1;
		g_6a25dc = -1;
		g_6a25e0 = -1;
		g_6a25d8 = -1;
		g_6a25d4 = -1;
	}
}
