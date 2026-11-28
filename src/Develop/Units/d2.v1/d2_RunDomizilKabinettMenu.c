


extern int d2_SelectedEntityUiFlags;
extern int g_14b5308;
extern int g_14b538c;
extern int g_14b53c8;
extern int g_14b534c;
extern char g_6a9640[];
extern char g_6a9624[];
extern char g_6a9604[];
extern char g_6a95e8[];
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int sv_ClickedObjekt;

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void (__cdecl*)(int, char*), int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_RunDomizilKabinettDialog(int, char*);
void __cdecl d2_RunSpyCabinetDialog(int);
void __cdecl d2_ShowCabinetSpyDialog(int);
void __cdecl d2_RunSchleichendeLaehmungDialog(int);
void __cdecl d2_RunBeweiseFaelschenDialog(int);

void __cdecl d2_RunDomizilKabinettMenu(int entityId, char* msg)
{
	int k1;
	int k2;
	int k3;
	int k4;

	k1 = 0;
	k2 = 0;
	k3 = 0;
	k4 = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunDomizilKabinettMenu, 0x67fff) != 0) {
		if (d2_SelectedEntityUiFlags & 0x400) {
			k1 = RegisterStatusText(g_6a9640, g_14b5308, 0x16);
			k2 = RegisterStatusText(g_6a9624, g_14b538c, 0x16);
			k3 = RegisterStatusText(g_6a9604, g_14b53c8, 0x16);
			k4 = RegisterStatusText(g_6a95e8, g_14b534c, 0x16);
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (sv_ClickedObjekt != 0) {
			if (*(int*) (msg + 0x1c) != 0) {
				d2_RunDomizilKabinettDialog(entityId, msg);
			} else if (sv_ClickedObjekt == k1) {
				d2_RunSpyCabinetDialog(entityId);
			} else if (sv_ClickedObjekt == k2) {
				d2_ShowCabinetSpyDialog(entityId);
			} else if (sv_ClickedObjekt == k3) {
				d2_RunSchleichendeLaehmungDialog(entityId);
			} else if (sv_ClickedObjekt == k4) {
				d2_RunBeweiseFaelschenDialog(entityId);
			}
		}
	}
}
