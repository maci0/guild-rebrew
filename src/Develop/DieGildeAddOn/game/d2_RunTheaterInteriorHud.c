


extern int d2_SelectedEntityUiFlags;
extern int sv_ClickedObjekt;
extern int g_14b5aec;
extern int g_14b5bfc;
extern char g_6ad4ec[];
extern char g_6ad4d8[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_ShowBlutracheDialog(int);
int __cdecl d2_RunCardGameDialog(void);

/* ADDRESS: GOLDDE 0x005c7c10 */
void __cdecl d2_RunTheaterInteriorHud(int a)
{
	int x;
	int y;

	x = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunTheaterInteriorHud, 0x67fff) != 0) {
		if (d2_SelectedEntityUiFlags & 0x200) {
			x = RegisterStatusText(g_6ad4ec, g_14b5aec, 0x16);
		}
		y = RegisterStatusText(g_6ad4d8, g_14b5bfc, 0x16);
		if (sv_ClickedObjekt != 0) {
			if (sv_ClickedObjekt == x) {
				d2_ShowBlutracheDialog(a);
			}
			else if (sv_ClickedObjekt == y) {
				d2_RunCardGameDialog();
			}
		}
	}
}
