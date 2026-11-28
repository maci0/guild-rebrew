


extern int sv_ClickedObjekt;
extern int gm_AllEntitiesControllable;
extern char io_LastKeyScancode;
extern int g_14ab07c;
extern int g_14ab750;
extern int g_14aadd8;
extern char g_6aa750[];
extern char g_6aa73c[];
extern char g_6aa728[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_OpenDuelTargetPicker(int);
void __cdecl d2_OpenStraftatAccusePicker(int);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_RunTalenteDialog(int, int, int);

void __cdecl d2_RunRhetoricActionsHud(int entity, int mode)
{
	int x;
	int y;
	int z;

	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunRhetoricActionsHud, 0x67fff) != 0) {
		x = RegisterStatusText(g_6aa750, g_14ab07c, 0xc);
		y = RegisterStatusText(g_6aa73c, g_14ab750, 0xc);
		z = RegisterStatusText(g_6aa728, g_14aadd8, 0xc);
		if (gm_AllEntitiesControllable != 0) {
			if (io_LastKeyScancode == 0x19) {
				d2_OpenDuelTargetPicker(entity);
			}
			if (io_LastKeyScancode == 0x20) {
				d2_OpenStraftatAccusePicker(entity);
			}
		}
		if (sv_ClickedObjekt != 0) {
			if (sv_ClickedObjekt == x) {
				d2_OpenStraftatAccusePicker(entity);
				d3_EndCameraAndUiMode();
			}
			else if (sv_ClickedObjekt == y) {
				d2_OpenDuelTargetPicker(entity);
			}
			else if (sv_ClickedObjekt == z) {
				d2_RunTalenteDialog(entity, mode, 4);
			}
		}
	}
}
