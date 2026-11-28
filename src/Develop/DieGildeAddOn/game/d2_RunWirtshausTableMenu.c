#include <string.h>
extern char g_6a956c[], g_6a9580[], g_6a9924[];

char* __cdecl d3_FindSceneObject(char*, int, char*, char*);
void __cdecl d3_SetSubtreeVisible(void*, int);
int __cdecl main_GetLanguage(void);
void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(int, int);
char* __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_OpenContactEinkaufPanel(char*);
void __cdecl d2_OpenTransportPanel(char*);
void __cdecl d2_ShowLagerOptions(char*, int);
void __cdecl d2_OpenMeisterbriefDialog(char*);
void __cdecl d3_SelectTavernCardTableCity(void);

extern int d2_SelectedEntityUiFlags;
extern char* sv_ClickedObjekt;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_14abb60;

/* Object server loop: probes the two card-table object names, picks the
 * localized name, then pumps the frame delay and dispatches the active dialog. */

/* ADDRESS: GOLDTL 0x005a3820 */
void __cdecl d2_RunWirtshausTableMenu(char* app)
{
	char name[0x100];
	char* obj;
	char* active;
	char* first;
	char* second;
	char* third;
	char* fourth;


	fourth = 0; second = 0; first = 0; third = 0;
	obj = d3_FindSceneObject(0, 0xc0, 0, (char*) 0x6aaa48);
	if (obj != 0) {
		d3_SetSubtreeVisible(obj, 0);
	}
	obj = d3_FindSceneObject(0, 0xc0, 0, (char*) 0x6aaa38);
	if (obj != 0) {
		d3_SetSubtreeVisible(obj, 0);
	}

	if (main_GetLanguage() == 0) {
		strcpy(name, "ob_KARTENTISCH_germ");
		obj = d3_FindSceneObject(0, 0xc0, 0, (char*) 0x6aaa48);
		if (obj == 0) {
			obj = d3_FindSceneObject(0, 0xc0, 0, (char*) 0x6aaa38);
			if (obj == 0) {
				goto ready;
			}
		}
		d3_SetSubtreeVisible(obj, 1);
	} else {
		strcpy(name, "ob_KARTENTISCH");




		obj = d3_FindSceneObject(0, 0xc0, 0, (char*) 0x6aaa38);
		if (obj != 0) {
			d3_SetSubtreeVisible(obj, 1);
		}
	}

ready:
	d2_ClearStatusTextSlots();
	if (main_RunFrameLoop(0x5a3820, 0x67fff) == 0) {
		return;
	}




	for (;;) {
		d2_OpenContactEinkaufPanel(app);
		if ((d2_SelectedEntityUiFlags & 0x200) != 0) {
			first = RegisterStatusText(g_6a956c, g_14ad100, 0x15);
			second = RegisterStatusText(g_6a9580, g_14ad0f0, 0xe);
			third = RegisterStatusText(g_6a9924, g_14a7d28, 0x16);
			fourth = RegisterStatusText(name, g_14abb60, 0x16);
		}
		active = sv_ClickedObjekt;
		if (active != 0) {
			if (active == first) {
				d2_OpenTransportPanel(app);
				active = sv_ClickedObjekt;
			}
			if (active == second) {
				d2_ShowLagerOptions(app, *(int*) (app + 0x5d));
			} else if (active == third) {
				d2_OpenMeisterbriefDialog(app);
			} else if (active == fourth) {
				*(int*) (fourth + 0x224) = 0;
				d3_SelectTavernCardTableCity();
				*(int*) (fourth + 0x224) = 1;
			}
		}
		if (main_RunFrameLoop(0x5a3820, 0x67fff) == 0) {
			break;
		}
	}
}
