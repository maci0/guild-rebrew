


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;
extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int d2_CurrentElementId;
#include "client_dialog_state.h"

int __cdecl fcn_004ee160(char*);
char* __cdecl ahm_GetWorkshopOwner(char*);
float __cdecl ahm_GetEssenceValue(char*, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText();
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl gm_AmountToUnits(int, unsigned char);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_GetControlValue(int);
int __cdecl fcn_0050b750(int, unsigned char);
int __cdecl gm_CheckEntityStock(ENTITY_RECORD*, int, unsigned char);
void __cdecl ahm_SendSetFloatValue(char*, float);
void __cdecl cm_RequestMoveCredits(int, int, unsigned char, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_RunDomizilSkillDialog(char* e, int* unused)
{
	int r;
	int ok;
	int c;
	int n;
	float f;
	int cancel;
	int tenth;
	char* p;
	int h;
	int line;
	int s;

	r = 0;
	n = fcn_004ee160(e);
	tenth = n / 10;
	p = ahm_GetWorkshopOwner(e);
	if (p == 0) {
		return 0;
	}
	f = ahm_GetEssenceValue(p, 3);
	h = d2_LoadForm(0, 0, "Locations\\Domizil\\skill");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	line = d2_GetWindowListItem(h, 1, io_AppendText(0x403a, 0x182, g_773d75));
	d2_SetElementValue(line, gm_AmountToUnits(tenth, g_773d75), gm_AmountToUnits(n, g_773d75), gm_AmountToUnits(tenth, g_773d75));
	d2_SetForm(h, 2);
	s = io_AppendText(0x403b);
	ok = d2_GetWindowListItem(h, 2, s);
	cancel = d2_GetWindowListItem(h, 2, s + 1);
	g_100f1dc = -1;
	do {
		p = ahm_GetWorkshopOwner(e);
		if (p == 0) {
			g_774654 = 1;
			main_RunFrameLoop(d2_RunDomizilSkillDialog, 0x20007);
			d2_DestroyForm(h);
			return 0;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == ok) {
				c = fcn_0050b750(d2_GetControlValue(line), g_773d75);
				if (gm_CheckEntityStock(((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970]), c, g_773d75) != 0) {
					ahm_SendSetFloatValue(p, (float) c / n * f * 0.75f);
					r = 1;
					g_774654 = 1;
					cm_RequestMoveCredits(*(int*) (p + 4), ((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970])->entity_id, g_773d75, c);
				}
			} else if (d2_CurrentElementId == cancel) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop(d2_RunDomizilSkillDialog, 0x677c7) != 0);
	d2_DestroyForm(h);
	return r;
}
