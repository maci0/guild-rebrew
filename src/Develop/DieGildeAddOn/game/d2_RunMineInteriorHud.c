


extern int d2_SelectedEntityUiFlags;
extern int sv_ClickedObjekt;
extern int g_14ad230;
extern int g_14ad208;
extern char g_6aa39c[];
extern char g_6aa38c[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_ShowProductionDialog(int);
void __cdecl d2_RunProductionTradeDialog(int);

void __cdecl d2_RunMineInteriorHud(int a)
{
	int x;
	int y;

	x = 0;
	y = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunMineInteriorHud, 0x67fff) != 0) {
		if (d2_SelectedEntityUiFlags & 0x200) {
			x = RegisterStatusText(g_6aa39c, g_14ad230, 0x16);
			y = RegisterStatusText(g_6aa38c, g_14ad208, 0xa);
		}
		if (sv_ClickedObjekt != 0) {
			if (sv_ClickedObjekt == x) {
				d2_ShowProductionDialog(a);
			}
			else if (sv_ClickedObjekt == y) {
				d2_RunProductionTradeDialog(a);
			}
		}
	}
}
