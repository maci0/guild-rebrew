extern int g_77250c;
extern int g_6a2598;


void __cdecl d2_ClearSurface(int);
void __cdecl d2_RefreshTownView(int, int);
void __cdecl d2_UpdateViewportCenter(int);
void __cdecl d2_PositionWindow(int, int);

void __cdecl d2_RestoreHudPanels(void)
{
	d2_ClearSurface(g_77250c);
	d2_RefreshTownView(1, 0);
	d2_UpdateViewportCenter(0x140);
	d2_PositionWindow(g_6a2598, 1);
}
