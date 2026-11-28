


extern int d2_SelectedEntityUiFlags;
extern int sv_ClickedObjekt;
extern int g_14a5548;
extern int g_14ad118;
extern char g_6aa370[];
extern char g_6aa35c[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_RunSoeldnerbuchDialog(int, char*);
void __cdecl d2_RunEquipmentDialog(int);

/* ADDRESS: GOLDDE 0x00580460 */
void __cdecl d2_RunWacheInteriorHud(int a)
{
	int x;
	int y;

	x = 0;
	y = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunWacheInteriorHud, 0x67fff) != 0) {
		if (d2_SelectedEntityUiFlags & 0x200) {
			x = RegisterStatusText(g_6aa370, g_14a5548, 0xc);
			y = RegisterStatusText(g_6aa35c, g_14ad118, 0xd);
		}
		if (sv_ClickedObjekt != 0) {
			if (sv_ClickedObjekt == x) {
				d2_RunSoeldnerbuchDialog(a, g_6aa370);
			}
			else if (sv_ClickedObjekt == y) {
				d2_RunEquipmentDialog(a);
			}
		}
	}
}
