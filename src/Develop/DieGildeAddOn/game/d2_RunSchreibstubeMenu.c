


extern int d2_SelectedEntityUiFlags;
extern int g_14ad1d8;
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

/* ADDRESS: GOLDDE 0x00591640 */
void __cdecl d2_RunSchreibstubeMenu(char* e)
{
	int meister;
	int lager;
	int prod;
	int personal;
	int transport;

	meister = 0;
	lager = 0;
	prod = 0;
	personal = 0;
	transport = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop((void*) d2_RunSchreibstubeMenu, 0x67fff) != 0) {
		d2_OpenContactEinkaufPanel(e);
		if (d2_SelectedEntityUiFlags & 0x200) {
			prod = RegisterStatusText("contact_PRODUKTION_SCHREIBEN", g_14ad1d8, 0x13);
			lager = RegisterStatusText("contact_LAGER", g_14ad0f0, 0xe);
			transport = RegisterStatusText("contact_TRANSPORT", g_14ad100, 0x15);
			personal = RegisterStatusText("ob_PERSONALBUCH", g_14a7b50, 0xc);
			meister = RegisterStatusText("ob_MEISTERBRIEF", g_14a7d28, 0xc);
		}
		if (sv_ClickedObjekt != 0 && (d2_SelectedEntityUiFlags & 0x200)) {
			if (sv_ClickedObjekt == personal) {
				d2_ShowPersonalbuch(e, "ob_PERSONALBUCH");
			} else if (sv_ClickedObjekt == lager) {
				d2_ShowLagerOptions(e, *(int*) (e + 0x5d));
			} else if (sv_ClickedObjekt == prod) {
				d2_RunProduktionDialog(e);
			} else if (sv_ClickedObjekt == transport) {
				d2_OpenTransportPanel(e);
			} else if (sv_ClickedObjekt == meister) {
				d2_OpenMeisterbriefDialog(e);
			}
		}
	}
}
