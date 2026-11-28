extern char g_7e4260[];
#include "Develop/client_types.h"



// SIZE 0xe

typedef struct {
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	int xc;
	char pad10[0x18];
	pos14_7f4c00 name;
	unsigned char x36;
	char pad37;
	int ids[8];
	int x58;
	int x5c;
	int x60;
	char pad64[0x94];
} Packet;
// SIZE 0xf8

typedef struct {
	char pad0[4];
	int x4;
	char pad8[0x180];
	unsigned char x188;
	char pad189[0x93];
} Player;
// SIZE 0x21c

extern char gm_EntitySlotTable[];
extern char* d2_InteriorBuilding;
extern int g_14abc44;
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern pos14_7f4c00 gm_GameTime;
extern char s_6aa490[];

int __cdecl d2_ShowModalMessageBox(int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl he_StartHandlungSearch(int, int, int, int, int, int, int);
int __cdecl he_fn_Handlung(void);
int __cdecl cm_SendCopyEntityData(Packet*);
void __cdecl d3snd_PlayWorkerOrderVoice(void);
int __cdecl io_FormatTextBuffer(char*, int, int);
void __cdecl he_AssignActionSlot(int, int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x0059d060 */
/* ADDRESS: GOLDDE 0x00582300 */
int __cdecl d2_RunTaschendiebstahlDialog(int unused, char* param)
{
	Packet pkt;
	char buf[0x400];
	int flag;
	int btn2;
	int btn1;
	int dlg;
	int dlg2;
	int count;
	int n;
	char* p;
	Player* player;
	Player* slot;

	flag = 0;
	dlg = d2_LoadForm(0, 0, s_6aa490);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	n = io_AppendText(0x19ee, *(unsigned short*) (param + 0x27), param);
	btn1 = d2_GetWindowListItem(dlg, 1, n);
	btn2 = d2_GetWindowListItem(dlg, 1, n + 1);
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased)
			d2_DialogCloseRequested = 1;
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == btn1) {
				dlg2 = he_StartHandlungSearch(3, 0, 0x49, 2,
					*(unsigned short*) (d2_InteriorBuilding + 0x27), 3,
					*(int*) (d2_InteriorBuilding + 1));
				while (dlg2 != 0) {
					if (*(int*) (dlg2 + 0xac) == *(int*) (param + 1))
						break;
					dlg2 = he_fn_Handlung();
				}
				if (dlg2 == 0) {
					pkt.type = 0x49;
					slot = &((Player*) gm_EntitySlotTable)[*(unsigned short*) (d2_InteriorBuilding + 0x27)];
					pkt.x8 = slot->x4;
					pkt.xc = *(int*) (d2_InteriorBuilding + 1);
					pkt.name = gm_GameTime;
					pkt.x36 = 1;
					pkt.x58 = *(int*) (param + 1);
					pkt.x5c = *(int*) (d2_InteriorBuilding + 1);
					for (n = 0; n < 8; n++)
						pkt.ids[n] = -1;
					n = 0;
					for (p = (char*) &g_7e4260; (int) p < ((int) &g_7e4260 + 0x80); p += 4) {
						if (n >= 6)
							break;
						player = *(Player**) p;
						if (player != 0 && player->x188 != 0) {
							pkt.ids[n] = player->x4;
							n++;
						}
					}
					if (n == 0) {
						d2_ShowModalMessageBox(g_14abc44, 0);
					}
					else {
						flag = 1;
						cm_SendCopyEntityData(&pkt);
						d3snd_PlayWorkerOrderVoice();
						count = 0;
						for (p = (char*) &g_7e4260; (int) p < ((int) &g_7e4260 + 0x80); p += 4) {
							player = *(Player**) p;
							if (player != 0 && player->x188 != 0)
								count++;
						}
						if (count > 6) {
							io_FormatTextBuffer(buf, 0x19ef, 6);
							d2_ShowModalMessageBox((int) buf, 0);
						}
						d2_DialogCloseRequested = 2;
					}
				}
				else {
					flag = 1;
					d2_DialogCloseRequested = 2;
					for (p = (char*) &g_7e4260; (int) p < ((int) &g_7e4260 + 0x80); p += 4) {
						player = *(Player**) p;
						if (player != 0 && player->x188 != 0)
							he_AssignActionSlot(0, 0, *(unsigned short*) player, dlg2);
					}
				}
			}
			else if (d2_CurrentElementId == btn2) {
				d2_DialogCloseRequested = 1;
			}
		}
		if (main_RunFrameLoop((void*) d2_RunTaschendiebstahlDialog, 0x677c7) == 0) {
			d2_DestroyForm(dlg);
			return flag;
		}
	} while (1);
}
