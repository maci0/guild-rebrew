extern int g_77250c;
extern int g_6a2598;


void __cdecl d2_ClearSurface(int);
void __cdecl fcn_00527f60(int, int);
void __cdecl d2_UpdateViewportCenter(int);
void __cdecl d2_PositionWindow(int, int);

void __cdecl fcn_00528fd0(void)
{
	d2_ClearSurface(g_77250c);
	fcn_00527f60(1, 0);
	d2_UpdateViewportCenter(0x140);
	d2_PositionWindow(g_6a2598, 1);
}
