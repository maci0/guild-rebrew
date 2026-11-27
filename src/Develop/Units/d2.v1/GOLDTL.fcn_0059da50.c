


typedef struct
{
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	char padc[0x2a];
	unsigned char x36;
	char pad37;
	int ids[8];
	int x58;
	int x5c;
	char pad60[0x98];
} Packet;
// SIZE 0xf8

#include "Develop/DieGildeAddOn/game/entity_record.h"










#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_14abd04;
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern unsigned char* g_7746c8;
extern char s_6aa4e8[];

int __cdecl he_HasNoActiveAction0x62(char*);
void __cdecl io_FormatTextBuffer(char*, int, unsigned short, char*);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl cm_SendCopyEntityData(Packet*);
void __cdecl gm_ModifyHealth(int, int);
void __cdecl cm_ExProdObjekt(void);
void __cdecl sv_ClearObjectSelection(void);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_OpenRaubzugDialog(int unused, char* e)
{
	int btn1;
	Packet pkt;
	char buf[0x400];
	int dlg;
	int s;
	int btn2;
	int n;
	int i;

	if (e == 0 || *(unsigned short*) (e + 0x27) == 0xffff) {
		return;
	}
	if (he_HasNoActiveAction0x62(e) == 0) {
		io_FormatTextBuffer(buf, 0x1a92, *(unsigned short*) (e + 0x27), e);
		fcn_00526120(buf, 0);
		return;
	}
	dlg = fcn_00470820(0, 0, s_6aa4e8);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	s = io_AppendText(0x1a84, e);
	btn1 = d2_GetWindowListItem(dlg, 1, s);
	btn2 = d2_GetWindowListItem(dlg, 1, s + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == btn1) {
				pkt.type = 0x75;
				pkt.x36 = 1;
				n = 0;
				pkt.x8 = ((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id;
				pkt.x58 = *(int*) (e + 1);
				pkt.x5c = *(int*) (((char*)g_7746c8) + 1);
				for (i = 0; i < 8; i++) {
					pkt.ids[i] = -1;
				}
				for (i = 0; i < 768; i++) {
					if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].selected != 0) {
						pkt.ids[n] = ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id;
						n++;
					}
				}
				if (n != 0) {
					cm_SendCopyEntityData(&pkt);
					gm_ModifyHealth(((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id, -1);
					cm_ExProdObjekt();
				}
				else {
					fcn_00526120((char*) g_14abd04, 0);
				}
				g_774654 = 1;
			}
			else if (d2_CurrentElementId == btn2) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_OpenRaubzugDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	sv_ClearObjectSelection();
}
