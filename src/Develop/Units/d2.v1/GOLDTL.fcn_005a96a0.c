

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"






// SIZE 0x38
typedef struct {
	ENTITY_RECORD* house;
	char pad4[0xc];
	int x;
	int y;
	char pad18[0x18];
	int f30;
	int pad34;
} Item5a96;

#define HOUSES 768


extern char* g_772500;
extern char* g_77255c;
extern int d2_CurrentWindowId;
extern int g_14abb40;
extern int g_14abb44;
extern int g_14abb48;
extern int g_100f1dc;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern int d2_CurrentElementId;
extern char g_6aae98[];

int __cdecl amt_FindOfficeSlotByType(int, void*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
void __cdecl fcn_00533a60(int, int, int*, int, ...);
void __cdecl d2_ClearWindowChildren(int, int);
int __cdecl d2_BuildPersonStatusDesc(Item5a96* s);
void __cdecl fcn_005ca740(int, int, int, int, Item5a96*, int);
void __cdecl fcn_00472640(int i, int flag);
int __cdecl amt_ApplyForOffice(char*, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl amt_GetOfficeGroup(int a);
void __cdecl fcn_005cadc0(int, int, int, int, void*);
void __cdecl fcn_0052f7a0(void);
void __cdecl d2_ShowAmtInfo(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_RunAmtsbewerbungDialog(char* who, int id)
{
	int d;
	int ha;
	int res;
	int hc;
	int hb;
	int prev;
	int w;
	int ids[3];
	ENTITY_RECORD* houses[4];
	char info[0x18];
	Item5a96 items[4];
	int n;
	int j;
	int i;
	int off;
	int r;

	res = 0;
	d = -1;
	ha = -1;
	hb = -1;
	hc = -1;
	prev = -1;
	g_100f1dc = -1;
	do {
		if (amt_FindOfficeSlotByType(id, info) == 0) {
			g_774654 = 1;
		}
		else {
			n = 0;
			for (j = 0; j < HOUSES; j++) {
				if (n >= 4) {
					break;
				}
				if (((ENTITY_RECORD*)g_7f4ca0)[j].entity_index != 0xffff && ((ENTITY_RECORD*)g_7f4ca0)[j].unk_165[3] == id) {
					houses[n] = &((ENTITY_RECORD*)g_7f4ca0)[j];
					n++;
				}
			}
			if (prev != n) {
				prev = n;
				if (d == -1) {
					d = fcn_00470820(0, 0, g_6aae98);
					d2_CenterDialogWindows(d);
					d2_SetOverlayAnimation(0, 0);
					d2_SetForm(d, 1);
					io_AppendText(0x1a07, id + 0x253);
					d2_SetForm(d, 3);
					fcn_00533a60(d2_CurrentWindowId, 0, ids, 3, g_14abb40, g_14abb44, g_14abb48);
					ha = ids[0];
					hb = ids[1];
					hc = ids[2];
				}
				d2_SetForm(d, 2);
				d2_ClearWindowChildren(d2_CurrentWindowId, 1);
				io_AppendText(0x1a0b);
				if (n <= 0) {
					io_AppendText(0x1a0c);
				}
				else {
					w = (((int*)g_77255c)[3] - *(short*) (g_772500 + 0x1ebd8) * 2) / 3;
					off = (((int*)g_77255c)[3] - *(short*) (g_772500 + 0x1ebd8) * 2) % 3 / 2;
					for (i = 0; i < n; i++) {
						items[i].x = off + (*(short*) (g_772500 + 0x1ebd8) + 10) * (i % 2) + (i % 2 + 1) * w - 10;
						items[i].f30 = 0;
						items[i].y = i / 2 * 0x41 * 2 + 0x28;
						items[i].house = houses[i];
						d2_BuildPersonStatusDesc(&items[i]);
						fcn_005ca740(items[i].x, items[i].y, d2_CurrentWindowId, 0x56, &items[i], 1);
					}
				}
				if (n < 4 && who[0x168] == 0) {
					fcn_00472640(ha, 1);
				}
				else {
					fcn_00472640(ha, 0);
				}
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == ha) {
				r = amt_ApplyForOffice(who, id);
				if (r != -1) {
					do {
						if (cm_GetCommandStatus(r) != 0) {
							break;
						}
						cm_StepCommandQueue();
					} while (1);
				}
				if (cm_GetCommandStatus(r) == 1) {
					res = 1;
				}
				fcn_0057e880(0x2f, 0, 0, id);
			}
			else if (d2_CurrentElementId == hb) {
				r = amt_GetOfficeGroup(id);
				fcn_005cadc0(r, 0, 0, 0, fcn_0052f7a0);
			}
			else if (d2_CurrentElementId == hc) {
				d2_ShowAmtInfo(id, 0);
			}
		}
	} while (main_RunFrameLoop(d2_RunAmtsbewerbungDialog, 0x677c7) != 0);
	if (d != -1) {
		d2_DestroyForm(d);
	}
	if (res != 0) {
		g_774654 = 1;
		fcn_0057e880(0x2f, 0, 1, id);
	}
	return res;
}
