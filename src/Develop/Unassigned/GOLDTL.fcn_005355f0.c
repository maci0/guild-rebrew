extern int g_6a2bf8;
int g_6a2bfc = 0xffffffff;
int g_6a2c00 = 0xffffffff;



void __cdecl fcn_00471e30(int);

void __cdecl fcn_005355f0(void)
{
	if (g_6a2bf8 != -1) {
		fcn_00471e30(g_6a2bf8);
		g_6a2bf8 = -1;
		g_6a2bfc = -1;
		g_6a2c00 = -1;
	}
}
