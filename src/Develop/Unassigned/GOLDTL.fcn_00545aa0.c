

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
extern unsigned char** g_7749e4;
#include "client_types.h"
extern D2_ACTION_POPUP_SLOT g_77e8c0[16];
#include "Develop/Units/d2.v1/d2_gui.h"
extern unsigned char g_7747b0;
extern volatile int g_6b7fc0;

void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_004707d0(int);

void __cdecl fcn_00545aa0(void)
{
	int i;
	unsigned char* o;

	if (g_6a476c == -1) {
		return;
	}
	if ((*(struct slot**)&g_7749e4) != 0 && (*(struct slot**)&g_7749e4)->ctl != -1 && (*(int*)&((D2_CONTROL_TL*)g_1015ea0)[(*(struct slot**)&g_7749e4)->ctl].value_038) == 0) {
		if ((*(struct slot**)&g_7749e4)->dlg != 0) {
			fcn_00471af0((*(struct slot**)&g_7749e4)->dlg, 0);
		}
		o = (*(struct slot**)&g_7749e4)->obj;
		if (o != 0 && ((o[0] == 0x11 && (o[0xf0] & 0x40) != 0) || o[0] == 0x87) && (g_7747b0 & 4) == 0) {
			g_6b7fc0 = 0;
		}
		(*(struct slot**)&g_7749e4) = 0;
	}
	for (i = 0; i < 16; i++) {
		if (((struct slot*)g_77e8c0)[i].ctl != -1 && (*(struct slot**)&g_7749e4) != &((struct slot*)g_77e8c0)[i] && (*(int*)&((D2_CONTROL_TL*)g_1015ea0)[((struct slot*)g_77e8c0)[i].ctl].value_038) != 0) {
			if ((*(struct slot**)&g_7749e4) != 0 && (*(struct slot**)&g_7749e4)->dlg != -1) {
				if ((*(struct slot**)&g_7749e4)->dlg != 0) {
					fcn_00471af0((*(struct slot**)&g_7749e4)->dlg, 0);
				}
				if ((*(struct slot**)&g_7749e4)->ctl != -1) {
					(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[(*(struct slot**)&g_7749e4)->ctl].value_038) = 0;
					(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[(*(struct slot**)&g_7749e4)->ctl].value_03c) = 0;
				}
				o = (*(struct slot**)&g_7749e4)->obj;
				if (o != 0 && ((o[0] == 0x11 && (o[0xf0] & 0x40) != 0) || o[0] == 0x87) && (g_7747b0 & 4) == 0) {
					g_6b7fc0 = 0;
				}
			}
			/* literal address: c2 must assume it may alias the slot read below,
			 * which schedules the store ahead of the load as the original does */
			*(struct slot**) 0x7749e4 = &((struct slot*)g_77e8c0)[i];
			fcn_00471af0(((struct slot*)g_77e8c0)[i].dlg, 1);
			fcn_004707d0((*(struct slot**)&g_7749e4)->dlg);
			o = (*(struct slot**)&g_7749e4)->obj;
			if (o != 0 && ((o[0] == 0x11 && (o[0xf0] & 0x40) != 0) || o[0] == 0x87) && (g_7747b0 & 4) == 0) {
				g_6b7fc0 = 1;
			}
		}
	}
}
unsigned char _dpad_774970[116];
