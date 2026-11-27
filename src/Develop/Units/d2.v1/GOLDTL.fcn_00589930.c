#include <string.h>
#include "client_types.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};
#include "Develop/Units/d2.v1/d2_gui.h"
struct msg {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x18];
	pos14_7f4c00 when;
	unsigned char code;
	char pad37[0x21];
	int f58;
	int f5c;
	int f60;
	int f64;
	int f68;
	int f6c;
	char pad70[0x88];
};

struct act {
	int count;
	int item;
	int yes;
	int no;
	int amt[3];
};

extern pos14_7f4c00 gm_GameTime;


extern int d2_CurrentElementId;
#include "client_data.h"
int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl fcn_0046fac0(int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
void __cdecl fcn_00472380(int, int, int, int, int);
void __cdecl d2_SetValueGaugeStepLabels(int, int, int, int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_GetControlValue(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
int __cdecl gm_CheckEntityStock(char*, int, char);
int __cdecl fcn_005898f0(void*);
char* __cdecl gm_GetEntityTableEntry(char*);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
int __cdecl ai_FindEntityInFavorRange(unsigned short*, int, int, int, float, float,
                        int*);
int __cdecl cm_SendCopyEntityData(struct msg*);
int __cdecl cm_GetCommandStatus(int);
void __cdecl d3snd_PlaySoundEffect(int, int, char*, int);
void __cdecl d3_EndCameraAndUiMode(void);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x00589930 */
void __cdecl d2_ShowCabinetSpyDialog(char* building)
{
	struct act act;
	struct msg m;
	char* p;
	int dlg;
	int lst;
	int btn;
	int i;
	int amt;
	int j;
	int target;
	float f;

	act.count = gm_WalkEntityChain(*(unsigned short*) &g_774970);
	f = (float) act.count;
	act.amt[0] = (int) (f * 0.01f);
	act.amt[1] = (int) (f * 0.015f);
	act.amt[2] = (int) (f * 0.0199999996f);
	dlg = d2_LoadForm(0, 0, (char*) 0x6a9514);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(*(int*) &d2_CurrentWindowId);
	d2_SetForm(dlg, 2);
	i = fcn_0046fac0(0, 3, *(int*) 0x14b53a0, *(int*) &d2_CurrentWindowId);
	((D2_CONTROL_TL*)g_1015ea0)[i].value_06c = 1;
	((D2_CONTROL_TL*)g_1015ea0)[i].width =
	    *(int*) (*(int*) &d2_CurrentWindowId * 0x3cc + (unsigned long)&g_1015f4c);
	d2_SetElementFont(i, 0x54);
	lst = d2_AddWindowValueGauge(0x57, 0x14, 200, 0, 100, 0x7b, 2,
	                   *(int*) &d2_CurrentWindowId);
	act.item = lst;
	fcn_00472380(lst, 0, 2, 0, 1);
	d2_SetValueGaugeStepLabels(lst, 3, *(int*) 0x14b53a4, *(int*) 0x14b53a8,
	             *(int*) 0x14b53ac);
	d2_SetForm(dlg, 3);
	btn = io_AppendText(0x4024);
	act.no = d2_GetWindowListItem(dlg, 3, btn);
	act.yes = d2_GetWindowListItem(dlg, 3, btn + 1);
	*(int*) &g_100f1dc = -1;
	do {
		j = d2_GetControlValue(lst);
		d2_SetForm(dlg, 1);
		io_AppendText(0x6811b0);
		io_AppendText(0x401e, 0x401c);
		amt = act.amt[j];
		io_AppendText(0x401f, amt);
		if (*(int*) 0x14ce8e0) {
			*(int*) 0x774654 = 1;
		} else if (*(int*) &g_100f1dc != -1) {
			if (d2_CurrentElementId == act.no) {
				if (gm_CheckEntityStock(
				        (char*) (unsigned long)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*)&g_774970]

,
				        amt, *(char*) &g_773d75) &&
				    fcn_005898f0(building)) {
					p = gm_GetEntityTableEntry(
					    (char*) (unsigned long)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*)&g_774970]


);
					if (p)
						*(int*) (p + 0x28) += amt;
					cm_RequestTransferCurrencyNoKill(
					    -1,
					    ((ENTITY_RECORD*)((char*)&g_7f4ca4 - 4))[*(unsigned short*)&g_774970].entity_id


,
					    *(char*) &g_773d75, amt);
					memset(&m, 0, sizeof(m));
					m.kind = 0x99;
					m.code = 2;
					m.f60 = -1;
					m.f64 = -1;
					m.f68 = 3;
					m.f6c = j;
					act.count = -1;
					m.owner = ((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (building + 0x27)].entity_id;
					target = *(int*) (building + 1);
					m.when = gm_GameTime;
					m.target = target;
					m.f5c = target;
					ai_FindEntityInFavorRange(
					    (unsigned short*) (unsigned long)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*)&g_774970]


,
					    0, 0x7b4c4a0, 0, 0.0f, 100.0f, &act.count);
					m.f58 = act.count;
					i = cm_SendCopyEntityData(&m);
					while (i != -1 && !cm_GetCommandStatus(i)) {
						main_RunFrameLoop(0, 0x20007);
					}
					d3snd_PlaySoundEffect(-7, 0, (char*) 0x6a9508, 0);
					lst = act.item;
					*(int*) 0x774654 = 1;
				}
			} else if (d2_CurrentElementId == act.yes) {
				*(int*) 0x774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) 0x589930, 0x677c7));
	d2_DestroyForm(dlg);
	d3_EndCameraAndUiMode();
}
