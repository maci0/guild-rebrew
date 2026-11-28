


extern int sv_ClickedObjekt;
extern int d2_SelectedEntityUiFlags;
extern int g_14ab918;
extern char g_6ab07c[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_OpenBeichteDialog(int);

void __cdecl d2_RunBeichtstuhlMenu(int building)
{
	int x;

	x = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunBeichtstuhlMenu, 0x67fff) != 0) {
		if (!(d2_SelectedEntityUiFlags & 0x200)) {
			x = RegisterStatusText(g_6ab07c, g_14ab918, 0x16);
		}
		if (sv_ClickedObjekt != 0 && !(d2_SelectedEntityUiFlags & 0x200) && sv_ClickedObjekt == x) {
			d2_OpenBeichteDialog(building);
		}
	}
}
