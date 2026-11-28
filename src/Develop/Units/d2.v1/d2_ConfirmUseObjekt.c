#include "Develop/DieGildeAddOn/game/entity_record.h"

typedef struct Req {
	unsigned short* s;
	int id;
	int arg;
	int dir;
	int pad;
} Req;
// SIZE 0x14

typedef struct Rec {
	char pad0[0x10];
	int mask;
	char pad14[4];
	unsigned short price;
} Rec;

typedef struct Btn {
	int btn;
	unsigned short* item;
} Btn;
// SIZE 8

typedef struct Ent {
	char pad0[0x1ec];
	int mask;
	char pad1f0[0x21c - 0x1f0];
} Ent;
// SIZE 0x21c

typedef struct Player {
	int pad0;
	int handle;
} Player;

extern int d2_DialogButtonAction;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int io_RightButtonReleased;
extern unsigned char gm_ClientModeFlags;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_EntitySlotTable[];
#include "Develop/client_types.h"
extern D2_ITEM_BUTTON g_776c60[6];
extern char* d2_InventoryPanelEntity;
extern unsigned char gm_ActiveTownIndex;

Rec* __cdecl gm_LookupSpecialObjectRecord(int key, int* out);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
char* __cdecl gm_LookupSpecialObject(int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_ResetUiInputAndBounds(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_SetFormVisibility(int, int);
int __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl d2_GetControlValue(int);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
int __cdecl gm_UseSpecialObject(Ent* e, Req* r);

int __cdecl d2_ConfirmUseObjekt(unsigned short* item)
{
	Req r = {0};
	int tmp;
	char text[0x400];
	Rec* rec;
	int dlg;
	int buy;
	int id;
	int i;

	buy = 0;
	rec = gm_LookupSpecialObjectRecord(*item, &tmp);
	if (rec != 0) {
		dlg = d2_LoadForm(0, 0, "panel\\useobj");
		d2_CenterDialogWindows(dlg);
		d2_SetForm(dlg, 1);
		if ((rec->mask & ((Ent *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot])->mask) == 0 && gm_LookupSpecialObject(id = *item) != 0) {
			io_AppendText(0xfe3, id * 2 + 0x9a8, rec->price, id * 2 + 0x9a8);
		} else {
			io_AppendText(0xfe4, *item * 2 + 0x9a8);
		}
		d2_SetOverlayAnimation(0, 0);
		d2_ResetUiInputAndBounds();
		d2_DialogButtonAction = -1;
		do {
			if (io_RightButtonReleased != 0) {
				d2_DialogCloseRequested = 1;
				buy = 0;
			}
			if (d2_DialogButtonAction != -1) {
				if (d2_DialogButtonAction == 2) {
					buy = 1;
					d2_DialogCloseRequested = 1;
				} else if (d2_DialogButtonAction == 1 && ((*(char*)&gm_ClientModeFlags) & 0x80) == 0) {
					io_FormatTextBuffer(text, 0xfe6, *item * 2 + 0x9a8, *item * 2 + 0x9a8);
					d2_SetFormVisibility(dlg, 0);
					if (d2_ShowModalMessageBox(text, 1) != 0) {
						for (i = 0; i < 6; i++) {
							if (((Btn*)g_776c60)[i].item != 0 && (id = d2_GetControlValue(((Btn*)g_776c60)[i].btn)) != 0) {
								cm_SendSellObjekt(-1, ((Player*)d2_InventoryPanelEntity)->handle, *((Btn*)g_776c60)[i].item, id, gm_ActiveTownIndex, 0);
								d2_SetElementValue(((Btn*)g_776c60)[i].btn, 0, 0x3e7, 0);
							}
						}
						ResetDisplayCounters();
					}
					d2_SetFormVisibility(dlg, 1);
					buy = 0;
					d2_DialogCloseRequested = 1;
				}
			}
		} while (main_RunFrameLoop(d2_ConfirmUseObjekt, 0x677c7) != 0);
		d2_DestroyForm(dlg);
		if (buy == 0) {
			return 0;
		}
		r.s = item;
		r.id = -1;
		r.arg = -1;
		r.dir = 0;
		r.pad = 0;
		gm_UseSpecialObject(((Ent *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot]), &r);
	}
	return r.dir;
}
