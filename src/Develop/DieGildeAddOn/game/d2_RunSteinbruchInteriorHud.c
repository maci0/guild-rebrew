


extern int d2_SelectedEntityUiFlags;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_14ad208;
extern int g_14ad238;
extern int g_14ad0f8;
extern int g_14ad0e8;
extern int sv_ClickedObjekt;

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
int __cdecl gm_QueryEntities(int, int, int, int, int);
void __cdecl d3_UpdateBuildingInteriorState(void);
void __cdecl d2_ShowLagerOptions(char*, int);
void __cdecl d2_RunGelageDialog(char*);
void __cdecl d2_RunProductionTradeDialog(char*);
void __cdecl d2_ShowProductionDialog(char*);
void __cdecl d2_OpenTransportPanel(char*);
void __cdecl d2_RunMetalProduktionDialog(char*);
void __cdecl d2_RunWorkerTrainingDialog(char*);

/* ADDRESS: GOLDDE 0x00581de0 */
void __cdecl d2_RunSteinbruchInteriorHud(char* e)
{
	int gelage;
	int transport;
	int prod;
	int zs;
	int sp;
	int lager;
	int abbau;
	int suchen;

	lager = 0;
	prod = 0;
	suchen = 0;
	transport = 0;
	abbau = 0;
	gelage = 0;
	sp = 0;
	zs = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop((void*) d2_RunSteinbruchInteriorHud, 0x67fff) != 0) {
		if (d2_SelectedEntityUiFlags & 0x200) {
			lager = RegisterStatusText("contact_LAGER", g_14ad0f0, 0xe);
			abbau = RegisterStatusText("contact_ABBAU", g_14ad208, 0xa);
			suchen = RegisterStatusText("contact_SUCHEN_STEIN", g_14ad238, 0x16);
			prod = RegisterStatusText("contact_PRODUKTION", g_14ad0f8, 0x13);
			transport = RegisterStatusText("contact_TRANSPORT", g_14ad100, 0x15);
			gelage = RegisterStatusText("contact_GELAGE", g_14ad0e8, 0x16);
			if (gm_QueryEntities(*(int*) (e + 0x5d), 2, 6, 0, 0x35) != 0) {
				sp = RegisterStatusText("ob_STROHPUPPE", g_14abc30, 0x17);
			}
			if (gm_QueryEntities(*(int*) (e + 0x5d), 2, 6, 0, 0x34) != 0) {
				zs = RegisterStatusText("ob_ZIELSCHEIBE", g_14abc2c, 0x17);
			}
		}
		d3_UpdateBuildingInteriorState();
		if (sv_ClickedObjekt != 0) {
			if (sv_ClickedObjekt == lager) {
				d2_ShowLagerOptions(e, *(int*) (e + 0x5d));
			} else if (sv_ClickedObjekt == gelage) {
				d2_RunGelageDialog(e);
			} else if (sv_ClickedObjekt == abbau) {
				d2_RunProductionTradeDialog(e);
			} else if (sv_ClickedObjekt == suchen) {
				d2_ShowProductionDialog(e);
			} else if (sv_ClickedObjekt == transport) {
				d2_OpenTransportPanel(e);
			} else if (sv_ClickedObjekt == prod) {
				d2_RunMetalProduktionDialog(e);
			} else if (sv_ClickedObjekt == zs || sv_ClickedObjekt == sp) {
				d2_RunWorkerTrainingDialog(e);
			}
		}
	}
}
