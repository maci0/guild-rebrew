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

extern char* d2_Controls;
extern char* lpObjektePROT;
extern int g_665f58[4];
extern int g_665f84[4];
extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_SetElementEnabled(int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_RefreshRentAGraveOptions(char* a, int dlg, int mode, int* ids, int* sel)
{
	char* s;
	int i;

	s = *(char**) (a + 0x65);
	d2_SetForm(dlg, mode);
	io_AppendText((int) str_dollar_C);
	for (i = 0; i < 4; i++) {
		ids[i] = d2_AddElementToWindow(6 + i * 0x6c, 0, g_665f58[i], d2_CurrentWindowId);
		((D2_CONTROL_TL*) d2_Controls)[ids[i]].value_05c = 1;
		((D2_CONTROL_TL*) d2_Controls)[ids[i]].flags_1d0 = 3;
		((D2_CONTROL_TL*) d2_Controls)[ids[i]].associated_object = (char*) &((OBJECT_PROTOTYPE*)lpObjektePROT)[g_665f84[i]];
	}
	d2_SetElementEnabled(ids[1], (unsigned char) s[0x19]);
	d2_SetElementEnabled(ids[2], (unsigned char) s[0x1a]);
	d2_SetElementEnabled(ids[3], (unsigned char) s[0x1b]);
	if (*sel == 3 && s[0x1b] == 1) {
		((D2_CONTROL_TL*) d2_Controls)[ids[3]].value_03c = 1;
	} else if (*sel == 2 && s[0x1a] == 1) {
		((D2_CONTROL_TL*) d2_Controls)[ids[2]].value_03c = 1;
	} else if (*sel == 1 && s[0x19] == 1) {
		((D2_CONTROL_TL*) d2_Controls)[ids[1]].value_03c = 1;
	} else {
		((D2_CONTROL_TL*) d2_Controls)[ids[0]].value_03c = 1;
		*sel = 0;
	}
	((D2_CONTROL_TL*) d2_Controls)[ids[*sel]].value_038 = 1;
}
