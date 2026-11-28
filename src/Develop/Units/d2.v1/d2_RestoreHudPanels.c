extern int d2_ScreenSurface;
extern int d2_HudTopBarWindowId;


void __cdecl d2_ClearSurface(int);
void __cdecl d2_RefreshTownView(int, int);
void __cdecl d2_UpdateViewportCenter(int);
void __cdecl d2_PositionWindow(int, int);

void __cdecl d2_RestoreHudPanels(void)
{
	d2_ClearSurface(d2_ScreenSurface);
	d2_RefreshTownView(1, 0);
	d2_UpdateViewportCenter(0x140);
	d2_PositionWindow(d2_HudTopBarWindowId, 1);
}
