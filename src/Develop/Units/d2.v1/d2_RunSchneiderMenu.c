


extern int d2_SelectedEntityUiFlags;
extern int sv_ClickedObjekt;
extern int g_14b5be4;
extern int g_14ab314;
extern int g_14b5bb8;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char s_6ad414[];
extern char s_6ad3f0[];
extern char s_6ad3e0[];
extern char s_6a9580[];
extern char s_6a956c[];
extern char s_6aa34c[];
extern char s_6a9924[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_ShowLagerOptions(char*, int);
void __cdecl d2_RunProduktionDialog(char*);
void __cdecl d2_OpenTransportPanel(char*);
void __cdecl d2_ShowPersonalbuch(char*, char*);
void __cdecl d2_OpenMeisterbriefDialog(char*);
void __cdecl d2_ShowHandelSearch(char*, int);
void __cdecl d2_SelectPlauschTarget(char*, int);
void __cdecl d2_OpenContactEinkaufPanel(char*);

/* ADDRESS: GOLDDE 0x005c64b0 */
void __cdecl d2_RunSchneiderMenu(char* obj, int arg)
{
	int info;
	int trade;
	int build;
	int stats;
	int family;
	int title;
	int diary;

	info = 0;
	stats = 0;
	family = 0;
	title = 0;
	diary = 0;
	trade = 0;
	build = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(d2_RunSchneiderMenu, 0x67fff)) {
		if (d2_SelectedEntityUiFlags & 0x200) {
			info = RegisterStatusText(s_6ad414, g_14b5be4, 0x13);
			trade = RegisterStatusText(s_6ad3f0, g_14ab314, 0x16);
			build = RegisterStatusText(s_6ad3e0, g_14b5bb8, 0xc);
		}
		if (d2_SelectedEntityUiFlags & 0x400) {
			stats = RegisterStatusText(s_6a9580, g_14ad0f0, 0xe);
			family = RegisterStatusText(s_6a956c, g_14ad100, 0x15);
			title = RegisterStatusText(s_6aa34c, g_14a7b50, 0xc);
			diary = RegisterStatusText(s_6a9924, g_14a7d28, 0x16);
		}
		if (sv_ClickedObjekt) {
			if (sv_ClickedObjekt == stats) {
				d2_ShowLagerOptions(obj, *(int*) (obj + 0x5d));
			} else if (sv_ClickedObjekt == info) {
				d2_RunProduktionDialog(obj);
			} else if (sv_ClickedObjekt == family) {
				d2_OpenTransportPanel(obj);
			} else if (sv_ClickedObjekt == title) {
				d2_ShowPersonalbuch(obj, s_6aa34c);
			} else if (sv_ClickedObjekt == diary) {
				d2_OpenMeisterbriefDialog(obj);
			} else if (sv_ClickedObjekt == trade) {
				d2_ShowHandelSearch(obj, arg);
			} else if (sv_ClickedObjekt == build) {
				d2_SelectPlauschTarget(obj, arg);
			}
		}
		d2_OpenContactEinkaufPanel(obj);
	}
	d2_ClearStatusTextSlots();
}
