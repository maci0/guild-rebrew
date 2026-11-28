


extern int sv_ClickedObjekt;
extern int g_14ab0b8;
extern int g_14aadd8;
extern int g_14ab098;
extern char g_6aa78c[];
extern char g_6aa77c[];
extern char g_6aa764[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_ShowFestInvitation(int, int);
void __cdecl d2_RunTalenteDialog(int, int, int);
void __cdecl d2_ShowAnschwaerzenDialog(int);
void __cdecl d3_EndCameraAndUiMode(void);

void __cdecl d2_RunSocialActionsHud(int entity, int mode)
{
	int x;
	int y;
	int z;

	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunSocialActionsHud, 0x67fff) != 0) {
		x = RegisterStatusText(g_6aa78c, g_14ab0b8, 0x16);
		y = RegisterStatusText(g_6aa77c, g_14aadd8, 0xc);
		z = RegisterStatusText(g_6aa764, g_14ab098, 0xc);
		if (sv_ClickedObjekt != 0) {
			if (sv_ClickedObjekt == x) {
				d2_ShowFestInvitation(entity, mode);
			}
			else if (sv_ClickedObjekt == y) {
				d2_RunTalenteDialog(entity, mode, 3);
			}
			else if (sv_ClickedObjekt == z) {
				d2_ShowAnschwaerzenDialog(entity);
				d3_EndCameraAndUiMode();
			}
		}
	}
}
