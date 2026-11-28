typedef struct
{
	char* e;
	int btn;
	char pad8[8];
	int x;
	int y;
	char pad18[0x14];
	int val;
	int flag;
	char pad34[4];
} Item;
/* SIZE 0x38 */

extern char* d2_FileObjTable;
extern char* d2_CurrentWindow;
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
extern int d2_CurrentElementId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
extern int g_14ce8d8;
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl gm_FindWerbungCandidates(char*, int*, int*);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl d2_BuildPersonStatusDesc(Item*);
int __cdecl gm_CalcWerbungSteps(int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_DrawPersonCard(int, int, int, int, Item*, int);
void __cdecl d2_ShowCenteredText(int, int, int, int, int);
int __cdecl d2_RunWerbungDialog(unsigned short*);
void __cdecl d2_SetGroupVisibility(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005d2ec0 */
int __cdecl d2_RunWerbungSelectDialog(char* a0)
{
	int count;
	int res;
	int dlg;
	int off;
	int ids[9];
	char buf[0x80];
	Item items[9];
	int w;
	int i;

	res = 2;
	gm_FindWerbungCandidates(a0, &count, ids);
	dlg = d2_LoadForm(0, 0, (char*) 0x6acbd4);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1ce3);
	d2_SetForm(dlg, 2);
	w = (((int*) d2_CurrentWindow)[3] - *(short*) (d2_FileObjTable + 0x1ebd8) * 3) / 4;
	off = (((int*) d2_CurrentWindow)[3] - *(short*) (d2_FileObjTable + 0x1ebd8) * 3) % 4 / 2;
	for (i = 0; i < count; i++) {
		items[i].x = off + (*(short*) (d2_FileObjTable + 0x1ebd8) + 10) * (i % 3) + (i % 3 + 1) * w - 10;
		items[i].y = i / 3 * 0x41 * 2 + 5;
		items[i].e = gm_LookupEntityRecordById(ids[i]);
		items[i].flag = 1;
		d2_BuildPersonStatusDesc(&items[i]);
		items[i].val = gm_CalcWerbungSteps(((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot])->entity_id, *(int*) (items[i].e + 4));
		io_FormatTextBuffer(buf, 0x1ce4, items[i].val);
		d2_DrawPersonCard(items[i].x, items[i].y, d2_CurrentWindowId, 0x56, &items[i], 1);
		d2_ShowCenteredText((int) buf, items[i].x + *(short*) (d2_FileObjTable + 0x1ebd8) / 2,
		             *(short*) (d2_FileObjTable + 0x1ebda) + items[i].y + 0x2b, 0xca, 0x56);
	}
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		else if (d2_DialogButtonAction != -1 && g_14ce8d8 != 0) {
			for (i = 0; i < count; i++) {
				if (items[i].btn == d2_CurrentElementId) {
					d2_SetGroupVisibility(dlg, 0);
					if (d2_RunWerbungDialog((unsigned short*) items[i].e) != 0) {
						res = 0x92;
						d2_DialogCloseRequested = 1;
						break;
					}
					d2_SetGroupVisibility(dlg, 1);
				}
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunWerbungSelectDialog, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	return res;
}
