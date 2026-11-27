#include "client_dialog_state.h"
extern int g_14abaac;
/* Kidnapping message handler: validates the request against the current
 * location slot, builds and posts the stealing-guild packet, and pumps the
 * message queue until the dialog reports no further action. */
#include "Develop/DieGildeAddOn/game/entity_record.h"
typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

int __cdecl d2_CheckActionBlocker(char* a1, int a2);
int __cdecl ai_FindEntityInFavorRange(char* p, int kind, F8 f, int c, float r, int* out);
void* __cdecl gm_StartFilteredEntitySearch(int a1, int a2, int a3);
int __cdecl d2_LoadForm(int a1, int a2, char* text);
void __cdecl d2_CenterDialogWindows(int a1);
void __cdecl d2_SetOverlayAnimation(int a1, int a2);
void __cdecl d2_SetForm(int a1, int a2);
int __cdecl io_AppendText(int a1, int a2, int a3, int a4);
int __cdecl d2_GetWindowListItem(int a1, int a2, int a3);
int __cdecl main_RunFrameLoop(void* a1, int a2);
void __cdecl d2_DestroyForm(int a1);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
int __cdecl d2_ShowModalMessageBox(void* a1, int a2);
void __cdecl cm_SendCopyEntityData(char* msg);
void __cdecl cm_RequestModifyHealth(int a1, int a2);
void __cdecl gm_TryRecordCrime(int a1, int a2, int a3, int a4, int a5);
void __cdecl d3snd_PlayWorkerOrderVoice(void);
void __cdecl sv_ClearObjectSelection(void);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x005ae6a0 */
int __cdecl d2_RunEntfuehrungDialog(void* a0)
{
	char msg[0xf8];
	char text[2048];
	F8 f;
	void* p;
	char* q;
	int found;
	int dialogId;
	int v9;
	int v10;
	int slot;
	int k;
	int i;
	int res;

	res = 0;
	if (a0 != 0 &&
	    d2_CheckActionBlocker((char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*)&g_774970], 3) != 0 &&
	    (*(int*) ((char*) a0 + 0x16c) == 0 ||
	     *(unsigned short*) (*(int*) ((char*) a0 + 0x16c) + 0x27) != *(unsigned short*) a0)) {
	if (*(unsigned char*) ((char*) a0 + 0x1b1) != 0) {
		io_FormatTextBuffer(text, 0x19ba, *(unsigned short*) a0);
		d2_ShowModalMessageBox(text, 0);
		return 0;
	}
	p = *(void**) ((char*) a0 + 0x170);
	if (p == 0) {
		f.mask = 0x4080a0;
		f.b = 0;
		if (ai_FindEntityInFavorRange((char*) a0, 0, f, 0, 100.0f, &found) == 0)
			return 0;
		p = gm_StartFilteredEntitySearch(1, 1, found);
	}
	dialogId = d2_LoadForm(0, 0, (char*) 0x6ab2b0);
	d2_CenterDialogWindows(dialogId);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dialogId, 1);
	v9 = io_AppendText(0x19b9, *(unsigned short*) a0, 3, *(unsigned short*) a0);
	v10 = d2_GetWindowListItem(dialogId, 1, v9);
	v9 = d2_GetWindowListItem(dialogId, 1, v9 + 1);
	*(int*) &g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0)
			g_774654 = 1;
		if (*(int*) &g_100f1dc != -1) {
			if (d2_CurrentElementId == v10) {
				for (i = 0; i < 0x3e; i++)
					((int*) msg)[i] = 0;
				*(unsigned char*) (msg + 4) = 0x3c;
				*(unsigned char*) (msg + 0x36) = 1;
				slot = ((ENTITY_RECORD*)((char*)&g_7f4ca4 - 4))[*(unsigned short*)&g_774970].entity_id;
				*(int*) (msg + 8) = slot;
				*(int*) (msg + 0x58) = *(int*) ((char*) a0 + 4);
				*(int*) (msg + 0x5c) = *(int*) ((char*) p + 1);
				*(int*) (msg + 0x60) = *(int*) (*(int*) &g_7746c4 + 1);
				for (i = 0; i < 8; i++)
					*(int*) (msg + 0x38 + i * 4) = -1;
				k = 0;
				for (q = (char*) &g_7f4ca4; (int) q < (int) 0x85a0a4; q += sizeof(ENTITY_RECORD)) {
					if (*(unsigned char*) (q + 0x184) != 0) {
						*(int*) (msg + 0x38 + k * 4) = *(int*) q;
						k++;
					}
				}
				if (k != 0) {
					cm_SendCopyEntityData(msg);
					cm_RequestModifyHealth(((ENTITY_RECORD*)((char*)&g_7f4ca4 - 4))[*(unsigned short*)&g_774970].entity_id, -3);
					gm_TryRecordCrime(0x1a, 1, ((ENTITY_RECORD*)((char*)&g_7f4ca4 - 4))[*(unsigned short*)&g_774970].entity_id,
						*(int*) ((char*) a0 + 4), -1);
					d3snd_PlayWorkerOrderVoice();
					sv_ClearObjectSelection();
					res = 1;
					g_774654 = 3;
				} else {
					d2_ShowModalMessageBox((void*) g_14abaac, 0);
					*(int*) &g_100f1dc = -1;
				}
			} else if (d2_CurrentElementId == v9)
				g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) 0x5ae6a0, 0x677c7) != 0);
	d2_DestroyForm(dialogId);
	return res;
	}
	return 0;
}
