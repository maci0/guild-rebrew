#include "Develop/DieGildeAddOn/game/object_prototype.h"

// SIZE 0x2f4
struct gadget {
	char pad0[0x38];
	int focus;
	int hot;
	char pad40[0x1c];
	int visible;
	char pad60[0x170];
	int mode;
	char pad1d4[0x11c];
	char* image;
};

// SIZE 0x41
struct icon {
	char pad[0x41];
};

// SIZE 0x34
struct seldlg {
	int dlg;
	char pad4[0xc];
	int font;
	char pad14[0xc];
	int ids[4];
	int sel;
};

extern char* g_1015ea0;
extern char* lpObjektePROT;
extern int g_665f58[4];
extern int g_665f84[4];
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_00472640(int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_0058b030(char* a, struct seldlg* d)
{
	char* s;
	int i;

	s = *(char**) (a + 0x65);
	d2_SetForm(d->dlg, 6);
	io_AppendText((int) g_6811b0);
	for (i = 0; i < 4; i++) {
		d->ids[i] = fcn_0046f740(6 + i * 0x6c, 0, g_665f58[i], d->font);
		((D2_CONTROL_TL*) g_1015ea0)[d->ids[i]].value_05c = 1;
		((D2_CONTROL_TL*) g_1015ea0)[d->ids[i]].flags_1d0 = 3;
		((D2_CONTROL_TL*) g_1015ea0)[d->ids[i]].associated_object = (char*) &((OBJECT_PROTOTYPE*)lpObjektePROT)[g_665f84[i]];
	}
	fcn_00472640(d->ids[1], (unsigned char) s[0x19]);
	fcn_00472640(d->ids[2], (unsigned char) s[0x1a]);
	fcn_00472640(d->ids[3], (unsigned char) s[0x1b]);
	if (d->sel == 3 && s[0x1b] == 1) {
		((D2_CONTROL_TL*) g_1015ea0)[d->ids[3]].value_03c = 1;
	} else if (d->sel == 2 && s[0x1a] == 1) {
		((D2_CONTROL_TL*) g_1015ea0)[d->ids[2]].value_03c = 1;
	} else if (d->sel == 1 && s[0x19] == 1) {
		((D2_CONTROL_TL*) g_1015ea0)[d->ids[1]].value_03c = 1;
	} else {
		((D2_CONTROL_TL*) g_1015ea0)[d->ids[0]].value_03c = 1;
		d->sel = 0;
	}
	((D2_CONTROL_TL*) g_1015ea0)[d->ids[d->sel]].value_038 = 1;
}
