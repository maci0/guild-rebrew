extern char g_10069a0[];
extern int g_10069a4;
extern int g_10069a8;
extern char g_10069c0;


void __cdecl sim_SetSyncParams(void*, int, int, int);

void __cdecl fcn_004b3d40(int a1, int a2)
{
	(*(int*)g_10069a0) = a2;
	g_10069a4 = a1;
	g_10069a8 = 0;
	sim_SetSyncParams(&g_10069a8, 0, 0, 0);
	g_10069c0 = 0;
}
