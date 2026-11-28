


extern int d2_SelectedEntityUiFlags;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_14ad288;
extern int g_14ad0e8;
extern int sv_ClickedObjekt;
extern int g_6a25f0;

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d3_UpdateBuildingInteriorState(void);
void __cdecl d2_HandleErnten(char*, int);
void __cdecl d2_OpenTransportPanel(char*);
void __cdecl d2_ShowLagerOptions(char*, int);
void __cdecl d2_RunMetalProduktionDialog(char*);
void __cdecl d2_RunGelageDialog(char*);
void __cdecl d2_RunWorkerTrainingDialog(char*);
void __cdecl ob_HandleBepflanzung(char*);

/* ADDRESS: GOLDDE 0x00581c40 */
void __cdecl d2_RunHolzfaellerInteriorHud(char* e)
{
	int zs;
	int sp;
	int x;
	int lager;
	int holz;
	int gelage;
	int transport;

	lager = 0;
	transport = 0;
	holz = 0;
	gelage = 0;
	sp = 0;
	zs = 0;
	d2_ClearStatusTextSlots();
	x = *(int*) (e + 0x71);
	while (main_RunFrameLoop((void*) d2_RunHolzfaellerInteriorHud, 0x67fff) != 0) {
		if (d2_SelectedEntityUiFlags & 0x200) {
			lager = RegisterStatusText("contact_LAGER", g_14ad0f0, 0xe);
			holz = RegisterStatusText("contact_PRODUKTION_HOLZ", g_14ad288, 0x13);
			gelage = RegisterStatusText("contact_GELAGE", g_14ad0e8, 0x16);
			transport = RegisterStatusText("contact_TRANSPORT", g_14ad100, 0x15);
			zs = RegisterStatusText("ob_ZIELSCHEIBE", g_14abc2c, 0xc);
			sp = RegisterStatusText("ob_STROHPUPPE", g_14abc30, 0xc);
		}
		d3_UpdateBuildingInteriorState();
		d2_HandleErnten(e, x);
		if (sv_ClickedObjekt != 0) {
			if (sv_ClickedObjekt == transport) {
				d2_OpenTransportPanel(e);
			} else if (sv_ClickedObjekt == lager) {
				d2_ShowLagerOptions(e, *(int*) (e + 0x5d));
			} else if (sv_ClickedObjekt == holz) {
				d2_RunMetalProduktionDialog(e);
			} else if (sv_ClickedObjekt == gelage) {
				d2_RunGelageDialog(e);
			} else if (sv_ClickedObjekt == zs) {
				d2_RunWorkerTrainingDialog(e);
			} else if (sv_ClickedObjekt == sp) {
				d2_RunWorkerTrainingDialog(e);
			}
		}
		if (d2_DialogButtonAction != -1 && d2_CurrentElementId == g_6a25f0) {
			ob_HandleBepflanzung(e);
		}
	}
}
