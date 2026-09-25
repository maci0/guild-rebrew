// FUNCTION: GOLD 0x577b70
// SIZE: 336
// FUNCTION: GOLDTL 0x580140
// SIZE: 326

// SIZE 0x14
struct page {
	char pad0[8];
	int mode;
	int text;
	int voice;
};

// SIZE 0x20
struct fsm {
	int state;
	int next;
	char pad8[0xc];
	int sound;
	struct page* page;
	char* dlg;
};

extern struct fsm* g_665f08;

int __cdecl fcn_005800e0(void);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00423460(int);
void __cdecl fcn_004237f0(int, int);
int __cdecl fcn_004c3030(int, int, int, int);

int __cdecl fcn_00580140(void)
{
	int r;

	if (g_665f08->page == 0) {
		return -4;
	}
	r = fcn_005800e0();
	if (r == -4) {
		return r;
	}
	if ((g_665f08->page->mode == 1 || g_665f08->page->mode == 2) && (g_665f08->next == 0xa || g_665f08->next == 0xb)) {
		fcn_004727a0(*(int*) (*(char**) (g_665f08->dlg + 0x74) + 8), 1);
		fcn_00519190(0x3fd3);
		fcn_004727a0(*(int*) (*(char**) (g_665f08->dlg + 0x74) + 8), 2);
		fcn_00519190(0x3fd4);
		return 0;
	}
	fcn_004727a0(*(int*) (*(char**) (g_665f08->dlg + 0x74) + 8), 1);
	fcn_00519190(g_665f08->page->text);
	fcn_004727a0(*(int*) (*(char**) (g_665f08->dlg + 0x74) + 8), 2);
	fcn_00519190(g_665f08->page->text + 1);
	if (g_665f08->page->voice != 0) {
		if (g_665f08->sound != 0) {
			if (fcn_00423460(g_665f08->sound) != 0) {
				fcn_004237f0(g_665f08->sound, 0);
			}
			g_665f08->sound = 0;
		}
		g_665f08->sound = fcn_004c3030(-7, 0, g_665f08->page->voice, -1);
	}
	return 0;
}
