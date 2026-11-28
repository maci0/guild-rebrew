


extern int sv_ClickedObjekt;
extern int g_14ab8c8;
extern int g_14ab89c;
extern char g_6ab12c[];
extern char g_6ab11c[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_ShowKircheTop5(void);
void __cdecl d2_RunAblassDialog(int, int);

/* ADDRESS: GOLDDE 0x00591930 */
void __cdecl d2_RunKircheAltarMenu(int building, int msg)
{
	int x;
	int y;

	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunKircheAltarMenu, 0x67fff) != 0) {
		x = RegisterStatusText(g_6ab12c, g_14ab8c8, 0x16);
		y = RegisterStatusText(g_6ab11c, g_14ab89c, 0x16);
		if (sv_ClickedObjekt != 0) {
			if (sv_ClickedObjekt == x) {
				d2_ShowKircheTop5();
			}
			else if (sv_ClickedObjekt == y) {
				d2_RunAblassDialog(building, msg);
			}
		}
	}
}
