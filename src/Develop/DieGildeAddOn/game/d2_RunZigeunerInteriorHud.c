


extern int d2_SelectedEntityUiFlags;
extern int sv_ClickedObjekt;
extern int g_14b5b94;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_14ad0f8;
extern int g_14b5ab4;

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_RunRohstoffsuchenDialog(int);
void __cdecl d2_OpenTransportPanel(int);
void __cdecl d2_RunProduktionDialog(int);
void __cdecl d2_ShowLagerOptions(int, int);
void __cdecl d2_OpenMeisterbriefDialog(int);
void __cdecl d2_OpenBlutracheDialog(int);
void __cdecl d2_ShowPersonalbuch(int, char*);
void __cdecl d3_UpdateBuildingInteriorState(void);

/* ADDRESS: GOLDDE 0x005c7cb0 */
void __cdecl d2_RunZigeunerInteriorHud(int a)
{
	int zig;
	int trans;
	int prod;
	int lager;
	int meister;
	int betteln;
	int personal;

	zig = 0;
	trans = 0;
	prod = 0;
	lager = 0;
	personal = 0;
	meister = 0;
	betteln = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunZigeunerInteriorHud, 0x67fff) != 0) {
		if (d2_SelectedEntityUiFlags & 0x200) {
			zig = RegisterStatusText("contact_ZUTATEN_SUCHEN_ZIGEUNER", g_14b5b94, 0x16);
			trans = RegisterStatusText("contact_TRANSPORT", g_14ad100, 0x15);
			prod = RegisterStatusText("contact_PRODUKTION_ZIGEUNER", g_14ad0f8, 0x13);
			lager = RegisterStatusText("contact_LAGER", g_14ad0f0, 0xe);
			betteln = RegisterStatusText("contact_BETTELN", g_14b5ab4, 0x2c);
		}
		if (d2_SelectedEntityUiFlags & 0x400) {
			personal = RegisterStatusText("contact_PERSONALBUCH", g_14a7b50, 0xc);
			meister = RegisterStatusText("contact_MEISTERBRIEF", g_14a7d28, 0xc);
		}
		if (sv_ClickedObjekt != 0) {
			if (d2_SelectedEntityUiFlags & 0x200) {
				if (sv_ClickedObjekt == zig) {
					d2_RunRohstoffsuchenDialog(a);
				} else if (sv_ClickedObjekt == trans) {
					d2_OpenTransportPanel(a);
				} else if (sv_ClickedObjekt == prod) {
					d2_RunProduktionDialog(a);
				} else if (sv_ClickedObjekt == lager) {
					d2_ShowLagerOptions(a, 0);
				} else if (sv_ClickedObjekt == meister) {
					d2_OpenMeisterbriefDialog(a);
				} else if (sv_ClickedObjekt == betteln) {
					d2_OpenBlutracheDialog(a);
				}
			}
			if (sv_ClickedObjekt == personal) {
				d2_ShowPersonalbuch(a, "ob_PERSONALBUCH");
			}
		}
		d3_UpdateBuildingInteriorState();
	}
}
