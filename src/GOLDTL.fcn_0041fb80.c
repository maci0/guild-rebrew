

extern int g_6b71a0;
extern int g_6b71a4;
extern int g_6b71a8;
void __cdecl fcn_0042ad00(void);
int __cdecl fcn_0042a2d0(int);

void __cdecl fcn_0041fb80(void)
{
	g_6b71a0 = 1;
	if (g_6b71a4 != 0) {
		fcn_0042ad00();
		fcn_0042a2d0(g_6b71a4);
		g_6b71a4 = 0;
	}
	if (g_6b71a8 != 0) {
		fcn_0042a2d0(g_6b71a8);
		g_6b71a8 = 0;
	}
}
