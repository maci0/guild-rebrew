#include <string.h>
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int d2_CurrentWindowId, g_100f1dc, g_14ce8e0, g_774654, d2_CurrentElementId; extern char* g_1015ea0; extern unsigned short g_774970; extern unsigned char g_773d75;
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
typedef struct { int mask; int b; } FAVOR_MASK_FILTER;
typedef struct { int f0; int f4; int pad8[2]; int f10; int pad14[2]; int f1c[8]; int pad3c[5]; } ENTITY_QUERY_PARAMS;
typedef struct {
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
} FORGE_EVIDENCE_REQ;

int __cdecl gm_WalkEntityChain(unsigned short);
void* __cdecl fcn_005cd440(void*, int, int, int);
int __cdecl amt_GetRoleLevel(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_0046fac0(int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00472380(int, int, int, int, int);
void __cdecl fcn_00468bb0(int, int, int, int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_GetControlValue(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
int __cdecl gm_CheckEntityStock(char*, int, char);
int __cdecl d2_CheckActionBlocker(char*, int);
int __cdecl fcn_005898f0(void*);
char* __cdecl gm_GetEntityTableEntry(char*);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
void __cdecl gm_ModifyHealth(int, int);
int __cdecl ai_FindEntityInFavorRange(unsigned short*, int, FAVOR_MASK_FILTER, int, float, int*);
int __cdecl cm_SendCopyEntityData(FORGE_EVIDENCE_REQ*);
int __cdecl cm_GetCommandStatus(int);
void __cdecl d3snd_PlaySoundEffect(int, int, char*, int);
void __cdecl d3_EndCameraAndUiMode(void);

/* ADDRESS: GOLDTL 0x00589d00 */
void __cdecl d2_RunBeweiseFaelschenDialog(int building)
{
	char* selectedEntity;
	FORGE_EVIDENCE_REQ req;
	ENTITY_QUERY_PARAMS q;
	int amt[3];
	int dlg;
	int no;
	int yes;
	int ids[3];
	int total;
	int n;
	int elem;
	int btn;
	int sel;
	int pick;
	int id;
	FAVOR_MASK_FILTER f;

	total = gm_WalkEntityChain(g_774970);
	memset(&q, 0, sizeof(q));
	memset(q.f1c, -1, sizeof(q.f1c));
	q.f0 = 1;
	q.f4 = 0x400;
	q.f10 = 6;
	selectedEntity = (char*) fcn_005cd440(&q, *(int*) 0x14b5354, 0, 0);
	if (selectedEntity == 0)
		return;
	total += gm_WalkEntityChain(*(unsigned short*) selectedEntity);
	n = amt_GetRoleLevel(*(unsigned char*) (selectedEntity + 0x166)) / 3 + 2;
	amt[0] = (int) (float) n;
	amt[1] = (int) (1.5f * (float) n);
	amt[2] = (int) ((float) n + (float) n);
	ids[0] = (int) (0.01f * (float) total);
	ids[1] = (int) (0.015f * (float) total);
	ids[2] = (int) ((float) total * 0.02f);
	dlg = fcn_00470820(0, 0, (char*) 0x6a9514);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(dlg, 2);
	elem = fcn_0046fac0(0, 3, *(int*) 0x14b5360, d2_CurrentWindowId);
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[elem].value_06c)) = 1;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[elem].width)) =
	    *(int*) (d2_CurrentWindowId * 0x3cc + 0x1015f4c);
	d2_SetElementFont(elem, 0x54);
	elem = fcn_004677e0(0x57, 0x14, 0xc8, 0, 0x64, 0x7b, 2, d2_CurrentWindowId);
	fcn_00472380(elem, 0, 2, 0, 1);
	fcn_00468bb0(elem, 3, *(int*) 0x14b5364, *(int*) 0x14b5368,
	             *(int*) 0x14b536c);
	d2_SetForm(dlg, 3);
	btn = io_AppendText(0x4014);
	no = d2_GetWindowListItem(dlg, 3, btn);
	yes = d2_GetWindowListItem(dlg, 3, btn + 1);
	g_100f1dc = -1;
	do {
		sel = d2_GetControlValue(elem);
		d2_SetForm(dlg, 1);
		io_AppendText(0x6811b0);
		io_AppendText(0x400e, 0x400c, *(unsigned short*) selectedEntity);
		io_AppendText(0x400f, amt[sel], ids[sel]);
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			pick = d2_CurrentElementId;
			if (pick == no) {
				char* p;

				if (gm_CheckEntityStock(
				        (char*) (0x7f4ca0 +
				                 (unsigned int) g_774970 *
				                     0x21c),
				        ids[sel], g_773d75) != 0 &&
				    d2_CheckActionBlocker(
				        (char*) (0x7f4ca0 +
				                 (unsigned int) g_774970 *
				                     0x21c),
				        amt[sel]) == 1 &&
				    fcn_005898f0((void*) building) != 0) {
					p = gm_GetEntityTableEntry(
					    (char*) (0x7f4ca0 +
					             (unsigned int) g_774970 *
					                 0x21c));
					if (p != 0)
						*(int*) (p + 0x28) += ids[sel];
					cm_RequestTransferCurrencyNoKill(
					    -1,
					    *(int*) (0x7f4ca4 +
					             (unsigned int) g_774970 *
					                 0x21c),
					    g_773d75, ids[sel]);
					gm_ModifyHealth(
					    *(int*) (0x7f4ca4 +
					             (unsigned int) g_774970 *
					                 0x21c),
					    -amt[sel]);
					memset(&req, 0, sizeof(req));
					req.kind = 0x99;
					req.code = 2;
					req.f64 = -1;
					req.f68 = 2;
					req.f6c = sel;
					req.owner =
					    *(int*) (0x7f4ca4 +
					             (unsigned int) *(unsigned short*) (building + 0x27) *
					                 0x21c);
					id = *(int*) (building + 1);
					req.when = gm_GameTime;
					req.target = id;
					req.f5c = id;
					req.f60 = *(int*) (selectedEntity + 4);
					if (*(int*) (selectedEntity + 0x170) != 0) {
						req.f58 = *(int*) (*(int*) (selectedEntity + 0x170) + 1);
					} else if (*(int*) (selectedEntity + 0x16c) != 0) {
						req.f58 = *(int*) (*(int*) (selectedEntity + 0x16c) + 1);
					} else {
						n = -1;
						f.mask = 0x7b4c4a0;
						f.b = 0;
						ai_FindEntityInFavorRange(
						    (unsigned short*) (0x7f4ca0 +
						                       (unsigned int) g_774970 *
						                           0x21c),
						    0, f, 0, 100.0f, &n);
						req.f58 = n;
					}
					id = cm_SendCopyEntityData(&req);
					if (id != -1) {
						do {
							if (cm_GetCommandStatus(id) != 0)
								break;
							main_RunFrameLoop(0, 0x20007);
						} while (1);
					}
					d3snd_PlaySoundEffect(-7, 0, (char*) 0x6a9508, 0);
					g_774654 = 1;
				}
			} else if (pick == yes) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) 0x589d00, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	d3_EndCameraAndUiMode();
}
