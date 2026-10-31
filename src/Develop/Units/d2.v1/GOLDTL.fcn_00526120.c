typedef struct Ctl {
	char pad0[0x20];
	int f20;
	char pad24[0x2d0];
} Ctl;
// SIZE 0x2f4

typedef struct Screen {
	char pad0[0xc];
	int xc;
	int x10;
	char pad14[0x14];
	int* ids;
	int count;
} Screen;
// SIZE 0x30

extern int g_6b7fac;
extern char g_77470c;
extern int g_7e46ac;
extern int g_772514;
extern char* g_77255c;
extern char* g_1015ea0;
extern int g_100f1dc;
extern int g_100f894;
#include "client_types.h"
extern List8c_102cbc8 g_102cbc8[];
extern char g_14cf950;
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char*);
void __cdecl fcn_00471b60(int);
int __cdecl d2_CreateRadioGroup(int);
void __cdecl fcn_00469470(int, int);
void __cdecl fcn_004695a0(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00469630(int);
void __cdecl fcn_004707d0(int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);


/* Modal message box: flags pick the layout (2, 0x10, 0x20, 0x100), 8 the
 * wait value, 0x80 a progress bar, 4 closes after 0x1f4 ticks of g_6b7fac,
 * 0x40 calls fcn_004707d0 each frame.
 * Returns the chosen entry + 1, or 0. */
/* ADDRESS: GOLDTL 0x00526120 */
int __cdecl fcn_00526120(char* text, int flags)
{
	int wait;
	int result;
	unsigned int start;
	int timer;
	int bar;
	int dlg;
	int list;
	int screen;
	int i;
	int id;

	start = (*(unsigned int*)&g_6b7fac);
	timer = -1;
	result = 0;
	if (g_77470c != 0) {
		return 0;
	}
	wait = g_7e46ac & ~0x38;
	if (flags & 2) {
		dlg = fcn_00470820(0, 0, "misc\\Messagebox_Autosize");
	} else if (flags & 0x10) {
		dlg = fcn_00470820(0, 0, "misc\\Messagebox_BIG");
	} else if (flags & 0x20) {
		dlg = fcn_00470820(0, 0, "misc\\Messagebox_VERY_BIG");
	} else if (flags & 0x100) {
		dlg = fcn_00470820(0, 0, "misc\\Messagebox_NONE_PERGA");
		d2_SetForm(dlg, 1);
	} else {
		dlg = fcn_00470820(0, 0, "misc\\Messagebox");
	}
	if (flags & 8) {
		wait = 0x717c6;
	}
	io_AppendText(text);
	screen = g_772514;
	fcn_00471b60(dlg);
	g_77470c = 1;
	list = d2_CreateRadioGroup(0);
	for (i = 0; i < ((Screen*)g_77255c)->count; i++) {
		id = ((Screen*)g_77255c)->ids[i];
		if (((Ctl*)g_1015ea0)[id].f20 != 0x40) {
			fcn_00469470(list, id);
		}
	}
	fcn_004695a0(list, 0);
	d2_SetForm(dlg, 0);
	bar = flags & 0x80;
	if (bar) {
		timer = fcn_004677e0(0x1c, ((Screen*)g_77255c)->x10 - 0x18, ((Screen*)g_77255c)->xc - 0x40, 0, 0x1f4, 0x83, 0x42, g_772514);
	}
	while (fcn_005373e0((void*) fcn_00526120, wait) != 0) {
		fcn_00469630(list);
		if (flags & 0x40) {
			fcn_004707d0(dlg);
		}
		if (g_100f1dc == 2 && g_100f894 == screen) {
			result = ((int*)g_102cbc8)[list * 35] + 1;
			g_774654 = 1;
		} else if ((g_100f1dc == 1 && g_100f894 == screen) || g_14cf950 == 1) {
			result = 0;
			g_774654 = 1;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (bar && timer != -1) {
			d2_SetElementValue(timer, 0, 0x1f4, (int) ((*(unsigned int*)&g_6b7fac) - start));
		}
		if ((flags & 4) && (*(unsigned int*)&g_6b7fac) > start + 0x1f4) {
			g_774654 = 1;
		}
	}
	g_77470c = 0;
	fcn_00469510(list);
	fcn_00471e30(dlg);
	return result;
}
