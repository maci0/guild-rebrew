typedef struct Ctl {
	char pad0[0x20];
	int f20;
	char pad24[0x2d0];
} Ctl;
/* SIZE 0x2f4 */

typedef struct Screen {
	char pad0[0xc];
	int xc;
	int x10;
	char pad14[0x14];
	int* ids;
	int count;
} Screen;
/* SIZE 0x30 */

extern int g_6b7fac;
extern char g_77470e;
extern int g_7e46ac;
extern int g_772514;
extern Screen* g_77255c;
extern char* g_1015ea0;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_00519190(int);
void __cdecl fcn_00471b60(int);
int __cdecl d2_CreateRadioGroup(int);
void __cdecl fcn_00469470(int, int);
void __cdecl fcn_004695a0(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00469630(int);
void __cdecl fcn_004707d0(int);
void __cdecl d2_SetElementValue(int, int, int, int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);

/* Modal message box: flags pick the layout (2, 0x10, 0x20), 8 the wait
 * value, 0x80 a progress bar, 4 closes after 0x1f4 ticks of g_6b7fac,
 * 0x40 calls fcn_004707d0 each frame. Returns the 1/0 close code. */
/* ADDRESS: GOLDTL 0x00526660 */
int __cdecl fcn_00526660(int parent, int flags)
{
	int style;
	int n;
	int h;
	int saved;
	int big;
	int dlg;
	int list;
	int i;
	int id;

	saved = g_6b7fac;
	h = -1;
	n = 0;
	if (g_77470e != 0) {
		return 0;
	}
	style = g_7e46ac & ~0x38;
	if (flags & 2) {
		dlg = fcn_00470820(0, 0, "misc\\Messagebox_Autosize");
	} else if (flags & 0x10) {
		dlg = fcn_00470820(0, 0, "misc\\Messagebox_BIG");
	} else if (flags & 0x20) {
		dlg = fcn_00470820(0, 0, "misc\\Messagebox_VERY_BIG");
	} else {
		dlg = fcn_00470820(0, 0, "misc\\Messagebox");
	}
	if (flags & 8) {
		style = 0x717c6;
	}
	fcn_00519190(parent);
	fcn_00471b60(dlg);
	list = d2_CreateRadioGroup(0);
	g_77470e = 1;
	for (i = 0; i < g_77255c->count; i++) {
		id = g_77255c->ids[i];
		if (*(int*) (g_1015ea0 + id * 756 + 0x20) != 0x40) {
			fcn_00469470(list, id);
		}
	}
	fcn_004695a0(list, 0);
	d2_SetForm(dlg, 0);
	big = flags & 0x80;
	if (big != 0) {
		h = fcn_004677e0(0x1c, g_77255c->x10 - 0x20, g_77255c->xc - 0x40, 0, 0x1f4, 0x83, 0x42, g_772514);
	}
	while (fcn_005373e0((void*) fcn_00526660, style) != 0) {
		fcn_00469630(list);
		if (flags & 0x40) {
			fcn_004707d0(dlg);
		}
		if (g_100f1dc == 2) {
			g_774654 = 1;
			n = 1;
		} else if (g_100f1dc == 1) {
			g_774654 = 1;
			n = 0;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (big != 0 && h != -1) {
			d2_SetElementValue(h, 0, 0x1f4, g_6b7fac - saved);
		}
		if (flags & 4) {
			if (g_6b7fac > saved + 0x1f4) {
				g_774654 = 1;
			}
		}
	}
	g_77470e = 0;
	fcn_00469510(list);
	fcn_00471e30(dlg);
	return n;
}
