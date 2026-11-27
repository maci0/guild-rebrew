extern int g_6a2bf8;
int g_6a2bfc = 0xffffffff;
int g_6a2c00 = 0xffffffff;



void __cdecl d2_DestroyForm(int);

void __cdecl d2_DestroyScrollPerga(void)
{
	if (g_6a2bf8 != -1) {
		d2_DestroyForm(g_6a2bf8);
		g_6a2bf8 = -1;
		g_6a2bfc = -1;
		g_6a2c00 = -1;
	}
}
