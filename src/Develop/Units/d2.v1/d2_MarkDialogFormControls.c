

// SIZE 0x2f4
typedef struct {
	char pad0[0x20];
	int alive;
	char pad24[0x24];
	int marked;
	char pad4c[4];
	void* home;
	char pad54[0x2a0];
} Unit;

// SIZE 0x2bc
typedef struct {
	char pad0[0x190];
	int x190;
	char pad194[0xc];
	int x1a0;
	char pad1a4[0x118];
} Home;

#include "Develop/Units/d2.v1/d2_gui.h"
extern int g_7747a8;
extern unsigned short g_773e40[];
#include "Develop/client_types.h"
extern D2_FORM_RECORD d2_Forms[];

void __cdecl d2_MarkDialogFormControls(int mark)
{
	int i;
	int k;
	Home* h;

	if (mark != 0) {
		g_7747a8 = 0;
		for (i = 0; i < 48; i++) {
			if (((Home*)d2_Forms)[i].x190 != 0 && ((Home*)d2_Forms)[i].x1a0 != 0) {
				h = &((Home*)d2_Forms)[i];
				for (k = 0; k < 0x400; k++) {
					if ((*(int*)&((D2_CONTROL_TL*)d2_Controls)[k].kind) != 0 && (*(void**)&((D2_CONTROL_TL*)d2_Controls)[k].value_050) == h && (*(int*)&((D2_CONTROL_TL*)d2_Controls)[k].value_048) == 0) {
						g_773e40[g_7747a8++] = (unsigned short) k;
						(*(int*)&((D2_CONTROL_TL*)d2_Controls)[k].value_048) = 1;
					}
				}
			}
		}
	} else {
		for (i = 0; i < g_7747a8; i++) {
			(*(int*)&((D2_CONTROL_TL*)d2_Controls)[g_773e40[i]].value_048) = 0;
		}
	}
}
