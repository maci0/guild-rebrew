/* the current screen/desk record behind g_77255c */
typedef struct {
	char p0[0xc];
	int x;
	int y;
	char p14[0x14];
	int* list;
	int count;
} Screen;

extern char g_77470e;
extern int g_7e46ac;
extern Screen* g_77255c;
extern char* g_1015ea0;
extern int g_772514;
extern int g_6b7fac;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_00470820(int a0, int a1, char* caption);
void __cdecl fcn_00519190(int a0);
void __cdecl fcn_00471b60(int dlg);
int __cdecl fcn_004693b0(int a0);
void __cdecl fcn_00469470(int parent, int id);
void __cdecl fcn_004695a0(int parent, int a1);
void __cdecl fcn_004727a0(int dlg, int a1);
int __cdecl fcn_004677e0(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7);
int __cdecl fcn_005373e0(void* fn, int a1);
void __cdecl fcn_00469630(int parent);
void __cdecl fcn_004707d0(int dlg);
void __cdecl d2_SetElementValue(int h, int a1, int a2, int v);
void __cdecl fcn_00469510(int parent);
void __cdecl fcn_00471e30(int dlg);

/* ADDRESS: GOLDTL 0x00526660 */
int __cdecl fcn_00526660(int parent, int flags)
{
	int style;
	int n;
	int h;
	int saved;
	int big;
	char* caption;
	int id;
	int i;
	int dlg;

	if (g_77470e != 0) {
		return 0;
	}
	h = -1;
	n = 0;
	saved = g_6b7fac;
	style = g_7e46ac & 0xc7;
	if (flags & 2) {
		caption = (char*) 0x68d760;
	} else if (flags & 0x10) {
		caption = (char*) 0x68d74c;
	} else if (flags & 0x20) {
		caption = (char*) 0x68d730;
	} else {
		caption = (char*) 0x68d704;
	}
	dlg = fcn_00470820(0, 0, caption);
	if (flags & 8) {
		style = 0x717c6;
	}
	fcn_00519190(parent);
	fcn_00471b60(dlg);
	i = fcn_004693b0(0);
	g_77470e = 1;
	if (g_77255c->count > 0) {
		for (i = 0; i < g_77255c->count; i++) {
			id = g_77255c->list[i];
			if (*(int*) (g_1015ea0 + id * 756 + 0x20) != 0x40) {
				fcn_00469470(parent, id);
			}
		}
	}
	fcn_004695a0(parent, 0);
	fcn_004727a0(dlg, 0);
	big = flags & 0x80;
	if (big != 0) {
		h = fcn_004677e0(0x1c, g_77255c->y - 0x20, g_77255c->x - 0x40, 0, 0x1f4, 0x83, 0x42, g_772514);
	}
	if (fcn_005373e0((void*) 0x526660, style) != 0) {
		do {
			fcn_00469630(parent);
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
		} while (fcn_005373e0((void*) 0x526660, style) != 0);
	}
	g_77470e = 0;
	fcn_00469510(parent);
	fcn_00471e30(dlg);
	return h;
}
