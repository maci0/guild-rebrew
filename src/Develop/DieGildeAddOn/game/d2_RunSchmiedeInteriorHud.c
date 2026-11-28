


extern int d2_SelectedEntityUiFlags;
extern int g_14ad0f8;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_14ad0e8;
extern int sv_ClickedObjekt;

void __cdecl d2_DispatchTutorialInput(int, char*, int, int);
void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
int __cdecl gm_QueryEntities(int, int, int, int, int);
void __cdecl d3_UpdateBuildingInteriorState(void);
void __cdecl d2_OpenTransportPanel(char*);
void __cdecl d2_ShowLagerOptions(char*, int);
void __cdecl d2_RunMetalProduktionDialog(char*);
void __cdecl d2_RunGelageDialog(char*);
void __cdecl d2_RunWorkerTrainingDialog(char*);

void __cdecl d2_RunSchmiedeInteriorHud(char* e)
{
	int d;
	int g;
	int f;
	int a;
	int b;
	int c;

	a = 0;
	c = 0;
	b = 0;
	d = 0;
	f = 0;
	g = 0;
	d2_DispatchTutorialInput(0x1b, e, 0, 0);
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop((void*) d2_RunSchmiedeInteriorHud, 0x67fff) != 0) {
		if (d2_SelectedEntityUiFlags & 0x200) {
			a = RegisterStatusText("contact_PRODUKTION_METALL", g_14ad0f8, 0x13);
			b = RegisterStatusText("contact_TRANSPORT", g_14ad100, 0x15);
			c = RegisterStatusText("contact_LAGER", g_14ad0f0, 0xe);
			d = RegisterStatusText("contact_GELAGE", g_14ad0e8, 0x16);
			if (gm_QueryEntities(*(int*) (e + 0x5d), 2, 6, 0, 0x35) != 0) {
				f = RegisterStatusText("ob_STROHPUPPE", g_14abc30, 0x17);
			}
			if (gm_QueryEntities(*(int*) (e + 0x5d), 2, 6, 0, 0x34) != 0) {
				g = RegisterStatusText("ob_ZIELSCHEIBE", g_14abc2c, 0x17);
			}
		}
		d3_UpdateBuildingInteriorState();
		if (sv_ClickedObjekt != 0) {
			if (sv_ClickedObjekt == b) {
				d2_OpenTransportPanel(e);
			} else if (sv_ClickedObjekt == c) {
				d2_ShowLagerOptions(e, 0);
			} else if (sv_ClickedObjekt == a) {
				d2_RunMetalProduktionDialog(e);
			} else if (sv_ClickedObjekt == d) {
				d2_RunGelageDialog(e);
			} else if (sv_ClickedObjekt == g || sv_ClickedObjekt == f) {
				d2_RunWorkerTrainingDialog(e);
			}
		}
	}
	d2_DispatchTutorialInput(0x1c, e, 0, 0);
}
