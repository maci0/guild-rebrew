extern int d2_SelectedEntityUiFlags;
extern int g_14ab314;
extern int g_14ad1f8;
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
void __cdecl d2_ShowHandelSearch(char*, int);
void __cdecl d2_OpenMeisterbriefDialog(char*);
extern int g_14ad1f0;

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_OpenContactEinkaufPanel(char*);
void __cdecl d2_RunProduktionDialog(char*);
void __cdecl d2_OpenTransportPanel(char*);
void __cdecl d2_ShowPersonalbuch(char*, char*);
void __cdecl d2_ShowLagerOptions(char*, int);
void __cdecl d2_ShowHandelSearch(char*, int);
void __cdecl d2_OpenMeisterbriefDialog(char*);

/* ADDRESS: GOLD 0x00595fb0 */
/* ADDRESS: GOLDTL 0x0059f190 */
void __cdecl d2_RunParfumerieProductionMenu(char* building, int searchArg)
{
	int prod;
	int sammeln;
	int lager;
	int transport;
	int meister;
	int personal;

	lager = 0;
	transport = 0;
	prod = 0;
	meister = 0;
	sammeln = 0;
	personal = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop((void*) d2_RunParfumerieProductionMenu, 0x67fff) != 0) {
		if (d2_SelectedEntityUiFlags & 0x200) {
			sammeln = RegisterStatusText("contact_SAMMELN", g_14ab314, 0x16);
			prod = RegisterStatusText("contact_PRODUKTION_PARFUMERIE", g_14ad1f8, 0x13);
		}
		if (d2_SelectedEntityUiFlags & 0x400) {
			lager = RegisterStatusText("contact_LAGER", g_14ad0f0, 0xe);
			transport = RegisterStatusText("contact_TRANSPORT", g_14ad100, 0x15);
			meister = RegisterStatusText("ob_MEISTERBRIEF", g_14a7d28, 0x16);
			personal = RegisterStatusText("ob_PERSONALBUCH", g_14a7b50, 0xc);
		}
		d2_OpenContactEinkaufPanel(building);
		if (sv_ClickedObjekt != 0) {
			if (sv_ClickedObjekt == prod) {
				d2_RunProduktionDialog(building);
			} else if (sv_ClickedObjekt == transport) {
				d2_OpenTransportPanel(building);
			} else if (sv_ClickedObjekt == personal) {
				d2_ShowPersonalbuch(building, "ob_PERSONALBUCH");
			} else if (sv_ClickedObjekt == lager) {
				d2_ShowLagerOptions(building, *(int*) (building + 0x5d));
			} else if (sv_ClickedObjekt == sammeln) {
				d2_ShowHandelSearch(building, searchArg);
			} else if (sv_ClickedObjekt == meister) {
				d2_OpenMeisterbriefDialog(building);
			}
		}
	}
}

/* ADDRESS: GOLD 0x00596200 */
/* ADDRESS: GOLDTL 0x0059f3e0 */
void __cdecl d2_RunMixingProductionMenu(char* e, int a2)
{
	int prod;
	int sammeln;
	int lager;
	int transport;
	int meister;
	int personal;

	meister = 0;
	lager = 0;
	transport = 0;
	prod = 0;
	sammeln = 0;
	personal = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop((void*) d2_RunMixingProductionMenu, 0x67fff) != 0) {
		if (d2_SelectedEntityUiFlags & 0x200) {
			sammeln = RegisterStatusText("contact_SAMMELN", g_14ab314, 0x16);
			prod = RegisterStatusText("contact_PRODUKTION_MISCHEN", g_14ad1f0, 0x13);
		}
		if (d2_SelectedEntityUiFlags & 0x400) {
			meister = RegisterStatusText("ob_MEISTERBRIEF", g_14a7d28, 0x16);
			personal = RegisterStatusText("ob_PERSONALBUCH", g_14a7b50, 0xc);
			lager = RegisterStatusText("contact_LAGER", g_14ad0f0, 0xe);
			transport = RegisterStatusText("contact_TRANSPORT", g_14ad100, 0x15);
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
			} else if (sv_ClickedObjekt == sammeln) {
				d2_ShowHandelSearch(e, a2);
			} else if (sv_ClickedObjekt == meister) {
				d2_OpenMeisterbriefDialog(e);
			}
		}
	}
}
