typedef struct {
	int v[0x11];
} SEANCE_TARGET_REC;

typedef struct {
	int kind;
	int cost;
	int f8;
	unsigned char fc;
	char padd[3];
	int f10;
	SEANCE_TARGET_REC rec;
} Result_58ee70;

typedef struct {
	int dlg;
	int w1;
	int w2;
	int w3;
	int w4;
	int w5;
	int w6;
	char* rec;
	int rec_id;
	unsigned char rec_state;
	char pad25[3];
	char entries[0x60];
	int selected;
} Dialog_58ee70;

#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_slot_table[2];
extern int g_14b5650;
extern int g_14b5674;
extern int g_665f78[];

void* __cdecl FindSlotEntryFiltered(int, char*, unsigned char*, void*, int);
int __cdecl gm_GetEntitySlotIndex(int, void*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
int __cdecl d2_CreateRentAGraveDialog(int*, int);
void __cdecl d3_EndCameraAndUiMode(void);
int __cdecl d2_RunSeanceMenu(int, char*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl gm_ModifyHealth(int, int);
void __cdecl d2_RunSeanceDialog(char*, char*);
void __cdecl d2_RunSeanceItemsDialog(char*, char*);
void __cdecl d2_RunSeanceTreasureDialog(char*, char*);
void __cdecl d2_ShowModalMessageBox(int, int);

/* ADDRESS: GOLDTL 0x0058ee70 */
void __cdecl d2_RunSeanceAction(char* e)
{
	Result_58ee70 result;
	Dialog_58ee70 dlg;
	unsigned char text[0x100];
	unsigned char* rec;
	int r;
	unsigned char v;

	rec = FindSlotEntryFiltered((int) (g_slot_table + g_774970 * 0x21c), e, 0, (void*) 0x4f1820, 0xff);
	if (rec != 0) {
		dlg.rec = (char*) rec;
		dlg.rec_id = *(int*) rec;
		v = (unsigned char) gm_GetEntitySlotIndex(*(int*) (e + 0x65), rec);
		dlg.rec_state = v;
		io_FormatTextBuffer(text, 0x4107, g_665f78[*(int*) rec]);
		if (!d2_CreateRentAGraveDialog((int*) &dlg, g_14b5650)) {
			d3_EndCameraAndUiMode();
			return;
		}
		r = d2_RunSeanceMenu((int) e, (char*) &dlg, (int) &result);
		d2_DestroyForm(dlg.dlg);
		if (r != 0) {
			cm_RequestChangeBits(*(int*) (g_slot_table + g_774970 * 0x21c + 4), 0x1cc, 4, 0x800000, 0);
			if (result.cost != 0) {
				gm_ModifyHealth(*(int*) (g_slot_table + g_774970 * 0x21c + 4), -result.cost);
			}
			switch (result.kind) {
			case 1:
				d2_RunSeanceDialog(e, (char*) &result);
				break;
			case 2:
				d2_RunSeanceItemsDialog(e, (char*) &result);
				break;
			case 3:
				d2_RunSeanceTreasureDialog(e, (char*) &result);
				break;
			}
		}
		d3_EndCameraAndUiMode();
	} else {
		d2_ShowModalMessageBox(g_14b5674, 0);
	}
}
