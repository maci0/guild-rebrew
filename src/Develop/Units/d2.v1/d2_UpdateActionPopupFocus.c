

// SIZE 0xc
struct slot {
	unsigned char* obj;
	int ctl;
	int dlg;
};

// SIZE 0x2f4
struct gadget {
	char pad0[0x38];
	int focus;
	int hot;
	char pad40[0x2b4];
};

extern int g_6a476c;
extern unsigned char** tp_d2_ActiveHudSlot;
#include "Develop/client_types.h"
extern D2_ACTION_POPUP_SLOT g_77e8c0[16];
#include "Develop/Units/d2.v1/d2_gui.h"
extern unsigned char gm_ClientModeFlags;
extern volatile int tb_TimerPaused;

void __cdecl d2_SetFormVisibility(int, int);
void __cdecl d2_BringFormToFront(int);

void __cdecl d2_UpdateActionPopupFocus(void)
{
	int i;
	unsigned char* o;

	if (g_6a476c == -1) {
		return;
	}
	if ((*(struct slot**)&tp_d2_ActiveHudSlot) != 0 && (*(struct slot**)&tp_d2_ActiveHudSlot)->ctl != -1 &&
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[(*(struct slot**)&tp_d2_ActiveHudSlot)->ctl].value_038) == 0) {
		if ((*(struct slot**)&tp_d2_ActiveHudSlot)->dlg != 0) {
			d2_SetFormVisibility((*(struct slot**)&tp_d2_ActiveHudSlot)->dlg, 0);
		}
		o = (*(struct slot**)&tp_d2_ActiveHudSlot)->obj;
		if (o != 0 && ((o[0] == 0x11 && (o[0xf0] & 0x40) != 0) || o[0] == 0x87) && (gm_ClientModeFlags & 4) == 0) {
			tb_TimerPaused = 0;
		}
		(*(struct slot**)&tp_d2_ActiveHudSlot) = 0;
	}
	for (i = 0; i < 16; i++) {
		if (((struct slot*)g_77e8c0)[i].ctl != -1 && (*(struct slot**)&tp_d2_ActiveHudSlot) != &((struct slot*)g_77e8c0)[i] &&
			(*(int*)&((D2_CONTROL_TL*)d2_Controls)[((struct slot*)g_77e8c0)[i].ctl].value_038) != 0) {
			if ((*(struct slot**)&tp_d2_ActiveHudSlot) != 0 && (*(struct slot**)&tp_d2_ActiveHudSlot)->dlg != -1) {
				if ((*(struct slot**)&tp_d2_ActiveHudSlot)->dlg != 0) {
					d2_SetFormVisibility((*(struct slot**)&tp_d2_ActiveHudSlot)->dlg, 0);
				}
				if ((*(struct slot**)&tp_d2_ActiveHudSlot)->ctl != -1) {
					(*(int*)&((D2_CONTROL_TL*)d2_Controls)[(*(struct slot**)&tp_d2_ActiveHudSlot)->ctl].value_038) = 0;
					(*(int*)&((D2_CONTROL_TL*)d2_Controls)[(*(struct slot**)&tp_d2_ActiveHudSlot)->ctl].value_03c) = 0;
				}
				o = (*(struct slot**)&tp_d2_ActiveHudSlot)->obj;
				if (o != 0 && ((o[0] == 0x11 && (o[0xf0] & 0x40) != 0) || o[0] == 0x87) && (gm_ClientModeFlags & 4) == 0) {
					tb_TimerPaused = 0;
				}
			}
			/* literal address: c2 must assume it may alias the slot read below,
			 * which schedules the store ahead of the load as the original does */
			*(struct slot**) 0x7749e4 = &((struct slot*)g_77e8c0)[i];
			d2_SetFormVisibility(((struct slot*)g_77e8c0)[i].dlg, 1);
			d2_BringFormToFront((*(struct slot**)&tp_d2_ActiveHudSlot)->dlg);
			o = (*(struct slot**)&tp_d2_ActiveHudSlot)->obj;
			if (o != 0 && ((o[0] == 0x11 && (o[0xf0] & 0x40) != 0) || o[0] == 0x87) && (gm_ClientModeFlags & 4) == 0) {
				tb_TimerPaused = 1;
			}
		}
	}
}
unsigned char _dpad_774970[116];
