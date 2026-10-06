extern char* g_1006920[];
extern int g_7728f4;

void __cdecl fcn_0044c440(char*);

// FUNCTION: GOLDTL 0x4bcae0

void __cdecl fcn_004bcae0(void)
{
	int i;

	for (i = 0; i < g_7728f4; i++) {
		if (g_1006920[i] != 0)
			fcn_0044c440(g_1006920[i]);
		g_1006920[i] = 0;
	}
}
