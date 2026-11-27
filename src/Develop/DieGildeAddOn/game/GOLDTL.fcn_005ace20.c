


extern int g_7746a0;
extern int g_14ab8c8;
extern int g_14ab89c;
extern char g_6ab12c[];
extern char g_6ab11c[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_ShowKircheTop5(void);
void __cdecl d2_RunAblassDialog(int, int);

void __cdecl d2_RunKircheAltarMenu(int building, int msg)
{
	int x;
	int y;

	fcn_005338a0();
	while (main_RunFrameLoop(d2_RunKircheAltarMenu, 0x67fff) != 0) {
		x = RegisterStatusText(g_6ab12c, g_14ab8c8, 0x16);
		y = RegisterStatusText(g_6ab11c, g_14ab89c, 0x16);
		if (g_7746a0 != 0) {
			if (g_7746a0 == x) {
				d2_ShowKircheTop5();
			}
			else if (g_7746a0 == y) {
				d2_RunAblassDialog(building, msg);
			}
		}
	}
}
