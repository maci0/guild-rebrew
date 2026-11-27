#include "client_types.h"


#include <string.h>





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
	int x58;
	int x5c;
	char pad60[0x98];
} Packet;
// SIZE 0xf8

#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int g_100f1dc;
extern int g_14ce8e0;
#include "client_dialog_state.h"

int __cdecl gm_CalcWerbungSteps(int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl cm_SendCopyEntityData(Packet*);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl io_ClearInputButtonFlags(int);

int __cdecl d2_RunWerbungDialog(unsigned short* target)
{
	Packet pkt;
	int cost;
	int dlg;
	int r;
	int h;

	cost = gm_CalcWerbungSteps(*(int*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id, *(int*) (target + 2));
	dlg = d2_LoadForm(0, 0, "privillegien\\werbung2");
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1ce5, *target, cost);
	g_100f1dc = -1;
	r = 0;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2) {
				memset(&pkt, 0, sizeof(pkt));
				pkt.type = 0x41;
				pkt.x8 = *(int*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id;
				pkt.xc = pkt.x8;
				pkt.name = (*(pos14_7f4c00*)&gm_GameTime);
				pkt.x36 = 2;
				pkt.x5c = *(int*) (target + 2);
				pkt.x58 = pkt.x8;
				h = cm_SendCopyEntityData(&pkt);
				while (cm_GetCommandStatus(h) == 0) {
					cm_StepCommandQueue();
				}
				r = 1;
				g_774654 = 1;
			} else if (g_100f1dc == 1) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunWerbungDialog, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	g_100f1dc = -1;
	io_ClearInputButtonFlags(0x11);
	return r;
}
