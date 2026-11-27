#include "client_types.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"


void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)





// SIZE 0xe

typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	int xc;
	char pad10[0x18];
	pos14_7f4c00 name;
	unsigned char x36;
	char pad37[0x21];
	unsigned char x58;
	char pad59[3];
	int x5c;
	int x60;
	char pad64[0x94];
} Packet;
// SIZE 0xf8

typedef struct
{
	int x0;
	int x4;
	char pad8[0x214];
} Player;
// SIZE 0x21c

typedef struct
{
	char pad0[0x223];
	unsigned char x223;
	char pad224[0x29];
} Shop;
// SIZE 0x24d

#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern char* g_7746cc;
extern char s_6aca6c[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl gm_CheckEntityType(unsigned char*);
int __cdecl cm_SendCopyEntityData(Packet*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00476b60(void);
int __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_ConfirmMeisterbrief(unsigned char* obj, int mode)
{
	int btn2;
	int btn1;
	Packet pkt;
	char buf[0x200];
	int dlg;
	int s;
	char* p;

	btn2 = -1;
	dlg = d2_LoadForm(0, 0, s_6aca6c);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	switch (mode) {
	case 0x20:
		s = io_AppendText(0x1938);
		btn1 = d2_GetWindowListItem(dlg, 1, s);
		btn2 = d2_GetWindowListItem(dlg, 1, s + 1);
		break;
	case 0x10:
		io_AppendText(0x1949);
		io_AppendText(0x194b);
		btn1 = d2_GetWindowListItem(dlg, 1, io_AppendText(0x194d));
		break;
	default:
		d2_DestroyForm(dlg);
		return;
	}
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == btn1) {
				for (p = he_StartHandlungSearch(2, 0, 7, 3, *(int*) (obj + 1)); p != 0; p = he_fn_Handlung()) {
					if (p[0xac] == 0) {
						break;
					}
				}
				if (p == 0) {
					memset(&pkt, 0, sizeof(pkt));
					pkt.type = 7;
					pkt.x8 = (*(int*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id);
					pkt.xc = *(int*) (obj + 1);
					pkt.x36 = 1;
					pkt.name = (*(pos14_7f4c00*)&gm_GameTime);
					pkt.x5c = 1;
					if (gm_CheckEntityType(obj) != 0) {
						pkt.x60 = -1;
					}
					else {
						pkt.x60 = *(int*) (g_7746cc + 2);
					}
					pkt.x58 = 0;
					cm_SendCopyEntityData(&pkt);
					io_FormatTextBuffer(buf, 0x1939, ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[obj[0]].worker_kind[0] + 0x130);
					fcn_00476b60();
					d2_ShowModalMessageBox(buf, 0);
				}
				g_774654 = 1;
			}
			else if (d2_CurrentElementId == btn2) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_ConfirmMeisterbrief, 0x677c7) != 0);
	d2_DestroyForm(dlg);
}
