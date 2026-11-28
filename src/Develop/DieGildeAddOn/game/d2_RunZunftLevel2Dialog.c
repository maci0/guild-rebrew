


typedef struct {
	unsigned short id;
	char pad2[7];
	unsigned char b9;
	char pada[0x15f];
	unsigned char b169;
	char pad16a[0xb2];
} ZUNFT_ENTITY_VIEW;
// SIZE 0x21c

typedef struct {
	int kind;
	int who;
	int cost;
	int pad[2];
} ZUNFT_LEVEL2_REQUEST;
// SIZE 0x14

#define MAX5AA1(a, b) ((a) > (b) ? (a) : (b))

#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char gm_ActiveTownIndex;

extern float g_664388;
extern char g_6aaf58[];
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
extern int d2_CurrentElementId;
#include "Develop/Units/d2.v1/client_dialog_state.h"

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl gm_CheckEntityStock(ZUNFT_ENTITY_VIEW*, int, unsigned char);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl gm_ExecZunftAufruhr(ZUNFT_ENTITY_VIEW*, ZUNFT_LEVEL2_REQUEST*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_RunZunftLevel2Dialog(int unused, char* target)
{
	int w2;
	ZUNFT_LEVEL2_REQUEST req;
	int cost;
	int h;
	int name;
	int t;
	int w1;

	cost = (int) MAX5AA1(gm_WalkEntityChain((*(unsigned short*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_index)) * 0.01f, g_664388);
	if (gm_CheckEntityStock(((ZUNFT_ENTITY_VIEW*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), cost, gm_ActiveTownIndex) == 0) {
		return 0;
	}
	h = d2_LoadForm(0, 0, g_6aaf58);
	d2_CenterDialogWindows(h);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	io_AppendText(0x165f);
	d2_SetForm(h, 2);
	if ((*(unsigned char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].gender) == 0) {
		name = (*(unsigned char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].grade) + 0x253;
	} else {
		name = (*(unsigned char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].grade) + 0x27b;
	}
	t = io_AppendText(0x1660, name, 5, cost, *(unsigned short*) (target + 0x27), target);
	w1 = d2_GetWindowListItem(h, 2, t);
	w2 = d2_GetWindowListItem(h, 2, t + 1);
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == w1 && gm_CheckEntityStock(((ZUNFT_ENTITY_VIEW*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), cost, gm_ActiveTownIndex) != 0) {
				req.kind = 2;
				req.who = *(int*) (target + 1);
				req.cost = cost;
				gm_ExecZunftAufruhr(((ZUNFT_ENTITY_VIEW*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), &req);
				d2_DialogCloseRequested = 2;
			} else if (d2_CurrentElementId == w2) {
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop(d2_RunZunftLevel2Dialog, 0x677c7) != 0);
	d2_DestroyForm(h);
	return 1;
}
