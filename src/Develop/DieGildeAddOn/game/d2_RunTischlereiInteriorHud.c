


extern int d2_SelectedEntityUiFlags;
extern int g_14ad278;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int sv_ClickedObjekt;

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_OpenContactEinkaufPanel(char*);
void __cdecl d2_RunProduktionDialog(char*);
void __cdecl d2_OpenTransportPanel(char*);
void __cdecl d2_ShowPersonalbuch(char*, char*);
void __cdecl d2_ShowLagerOptions(char*, int);
void __cdecl d2_OpenMeisterbriefDialog(char*);

/* ADDRESS: GOLDDE 0x00583470 */
void __cdecl d2_RunTischlereiInteriorHud(char* e)
{
	int prod;
	int lager;
	int transport;
	int meister;
	int personal;

	meister = 0;
	lager = 0;
	prod = 0;
	transport = 0;
	personal = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop((void*) d2_RunTischlereiInteriorHud, 0x67fff) != 0) {
		if (d2_SelectedEntityUiFlags & 0x200) {
			prod = RegisterStatusText("contact_PRODUKTION_TISCHLER", g_14ad278, 0x13);
		}
		if (d2_SelectedEntityUiFlags & 0x400) {
			lager = RegisterStatusText("contact_LAGER", g_14ad0f0, 0xe);
			transport = RegisterStatusText("contact_TRANSPORT", g_14ad100, 0x15);
			meister = RegisterStatusText("ob_MEISTERBRIEF", g_14a7d28, 0xc);
			personal = RegisterStatusText("ob_PERSONALBUCH", g_14a7b50, 0xc);
		}
		d2_OpenContactEinkaufPanel(e);
		if (sv_ClickedObjekt != 0) {
			if (sv_ClickedObjekt == prod) {
				d2_RunProduktionDialog(e);
			} else if (sv_ClickedObjekt == transport) {
				d2_OpenTransportPanel(e);
			} else if (sv_ClickedObjekt == personal) {
				d2_ShowPersonalbuch(e, "ob_PERSONALBUCH");
			} else if (sv_ClickedObjekt == lager) {
				d2_ShowLagerOptions(e, *(int*) (e + 0x5d));
			} else if (sv_ClickedObjekt == meister) {
				d2_OpenMeisterbriefDialog(e);
			}
		}
	}
}
