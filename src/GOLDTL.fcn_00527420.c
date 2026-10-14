

extern int g_7ea380[15];
extern int g_774680;
extern int g_774684;
extern int g_774674;
extern int g_774678;
extern int g_77467c;
extern int g_6a25fc;
extern int g_6a25a8;
extern int g_6a25ac;
extern int g_6a2598;
extern int g_6a2524;

void __cdecl fcn_0046b2b0(int h);
void __cdecl fcn_00475f80(int h);
void __cdecl fcn_0047ac60(int h, int v);
void __cdecl fcn_004752e0(int h);
void __cdecl fcn_005272e0(void);
void __cdecl fcn_0046f280(int h);
void __cdecl fcn_0052f710(void);

void __cdecl fcn_00527420(void)
{
	int i;

	for (i = 0; i < 15; i++) {
		if (g_7ea380[i] != -1) {
			fcn_0046b2b0(g_7ea380[i]);
			g_7ea380[i] = -1;
		}
	}
	if (g_774680 != 0) {
		fcn_00475f80(g_774680);
		g_774680 = 0;
	}
	if (g_774684 != 0) {
		fcn_00475f80(g_774684);
		g_774684 = 0;
	}
	if (g_774674 != 0) {
		fcn_0047ac60(g_774674, 0);
		g_774674 = 0;
	}
	if (g_774678 != 0) {
		fcn_0047ac60(g_774678, 0);
		g_774678 = 0;
	}
	if (g_77467c != 0) {
		fcn_0047ac60(g_77467c, 0);
		g_77467c = 0;
	}
	if (g_6a25fc != -1) {
		fcn_0046b2b0(g_6a25fc);
		g_6a25fc = -1;
	}
	if (g_6a25a8 != -1) {
		fcn_004752e0(g_6a25a8);
	}
	fcn_005272e0();
	g_6a25ac = -1;
	if (g_6a2598 != -1) {
		fcn_0046f280(g_6a2598);
		g_6a2598 = -1;
	}
	fcn_0052f710();
	g_6a2524 = 1;
}
