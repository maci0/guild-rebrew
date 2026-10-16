extern char g_10069a0[];
extern int g_10069a4;
extern int g_10069a8;
extern char g_10069c0;

void __cdecl fcn_004fe1e0(void*, int, int, int);

/* ADDRESS: GOLD 0x004b3bd0 */

void __cdecl fcn_004b3bd0(int a1, int a2)
{
	(*(int*) g_10069a0) = a2;
	g_10069a4 = a1;
	g_10069a8 = 0;
	fcn_004fe1e0(&g_10069a8, 0, 0, 0);
	g_10069c0 = 0;
}
