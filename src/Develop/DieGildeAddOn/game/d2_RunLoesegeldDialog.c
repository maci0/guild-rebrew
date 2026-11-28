/* Menu action: the recruitable thief (diebesgilde) offer.  Looks the selected
   record up, finds the matching action record of type 0x3e (loesegeld) or
   0x3d, fills the payment packet and runs the modal button loop until the
   player answers. */

extern char* cm_PacketDeltaBase;
extern int g_14aba40;
extern int g_14aba48;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
extern double dbl_0_75;
extern double g_665fc0;
extern char g_6ab2e0[];

int __cdecl d2_CheckOwnerBlocked(char*);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl d2_ShowModalMessageBox(char*, int);
char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl gm_CalcPersonWealth(unsigned short);
double __cdecl gm_RandomFloat01(void);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl cm_SendCopyEntityData(char*);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_SendBlockCharacter(int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d3_EndCameraAndUiMode(void);
int __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005aeab0 */
/* ADDRESS: GOLDDE 0x005934b0 */
void __cdecl d2_RunLoesegeldDialog(char* rec)
{
	char text[0x400];
	char line[0x200];
	char note[0x200];
	char pkt[0xf8];
	char* ent;
	char* act;
	char* ctx;
	unsigned char cls;
	int v;
	int cnt;
	int b1;
	int b2;
	int b3;
	int flags;
	float weight;
	double prob;

	weight = 0.0f;
	if (d2_CheckOwnerBlocked(rec) != 0) {
		return;
	}
	ent = gm_LookupEntityRecordById(*(int*) (rec + 0x65));
	if (ent == 0) {
		d2_ShowModalMessageBox((char*) g_14aba40, 0);
		return;
	}
	act = he_StartHandlungSearch(1, 0, 0x3e);
	while (act != 0) {
		if (*(int*) (act + 0xac) == *(int*) (ent + 4)) {
			io_FormatTextBuffer(text, 0x19c9, *(unsigned short*) ent);
			d2_ShowModalMessageBox(text, 0);
			return;
		}
		act = he_fn_Handlung();
	}
	act = he_StartHandlungSearch(1, 0, 0x3d);
	while (act != 0) {
		if (*(int*) (act + 0xac) == *(int*) (ent + 4)) {
			break;
		}
		act = he_fn_Handlung();
	}
	if (act == 0) {
		d2_ShowModalMessageBox((char*) g_14aba48, 0);
		return;
	}
	cls = *(unsigned char*) (ent + 0x1b1);
	if (cls >= 4) {
		weight = 0.1f;
	} else if (cls == 3) {
		weight = 0.06f;
	} else if (cls == 2) {
		weight = 0.04f;
	} else if (cls == 1) {
		weight = 0.02f;
	}
	v = gm_CalcPersonWealth(*(unsigned short*) ent);
	prob = (double) v;
	if (((double) gm_RandomFloat01() * 0.5 + dbl_0_75) * g_665fc0
	    < prob) {
		prob = ((double) gm_RandomFloat01() * 0.5 + dbl_0_75) * g_665fc0;
	}
	cnt = (int) prob;
	cnt = (int) ((double) cnt * (double) weight);
	ctx = (char*) d2_LoadForm(0, 0, g_6ab2e0);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows((int) ctx);
	d2_SetForm((int) ctx, 1);

	v = io_AppendText(0x19c4, *(unsigned short*) ent, (int) (act + 0xb4),
	    2, cnt, *(unsigned short*) ent, *(unsigned short*) ent);
	b1 = d2_GetWindowListItem((int) ctx, 1, v);
	b2 = d2_GetWindowListItem((int) ctx, 1, v + 1);
	b3 = d2_GetWindowListItem((int) ctx, 1, v + 2);
	d2_DialogButtonAction = -1;
	for (;;) {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == b1) {
				int entityId = *(int*) (ent + 4);
				*(unsigned char*) (pkt + 4) = 0x3e;
				*(int*) (pkt + 8) = entityId;
				*(int*) (pkt + 0xc) = *(int*) (rec + 1);
				*(unsigned char*) (pkt + 0x36) = 9;
				*(int*) (pkt + 0x58) = entityId;
				*(int*) (pkt + 0x60) = *(int*) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c);
				*(int*) (pkt + 0x64) = cnt;
				cm_SendCopyEntityData(pkt);
				io_FormatTextBuffer(note, 0x19c5, cnt, *(unsigned short*) ent);
				d2_ShowModalMessageBox(note, 0);
				d2_DialogCloseRequested = 1;
			} else if (d2_CurrentElementId == b2) {
				flags = -1;
				cm_BeginPacketFieldDelta(rec, *(int*) (rec + 1));
				cm_AppendPacketFieldDelta(4, 1, (int) (rec - cm_PacketDeltaBase) + 0x65,
				    &flags);
				cm_RequestChangeAttribute();
				cm_SendBlockCharacter(*(int*) (ent + 4),
				    -(int) *(unsigned char*) (ent + 0x1b1), 0);
				io_FormatTextBuffer(line, 0x19c6, *(unsigned short*) ent);
				d2_ShowModalMessageBox(line, 0);
				d2_DialogCloseRequested = 1;
			} else if (d2_CurrentElementId == b3) {
				io_FormatTextBuffer(text, 0x19c7, *(unsigned short*) ent);
				d2_ShowModalMessageBox(text, 0);
				d2_DialogCloseRequested = 1;
			}
		}
		if (main_RunFrameLoop((void*) d2_RunLoesegeldDialog, 0x677c7) == 0) {
			d3_EndCameraAndUiMode();
			d2_DestroyForm((int) ctx);
			return;
		}
	}
}
