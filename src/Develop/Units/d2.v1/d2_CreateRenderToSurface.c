extern char g_7725ec[];
extern char g_6b5de0[];
extern char g_14ce86c[];


void __stdcall fcn_005ef8cf(int, int, int, int, int, int, int);

/* ADDRESS: GOLDDE 0x00469210 */
int __cdecl d2_CreateRenderToSurface(void)
{
	fcn_005ef8cf(*(int*) &g_6b5de0, 0x100, 0x100, *(int*) &g_14ce86c, 0, 0, (int) &g_7725ec);
	return 1;
}
