extern int g_10069a0[9];
extern unsigned short g_774970;
extern int g_100f1dc;
extern int g_67d370;
extern char g_6a3440;
extern int g_7728dc;
extern int g_774654;

int __cdecl fcn_004b3c50(int a);
void __cdecl fcn_004b5630(int a, int b);
int __cdecl fcn_00470820(int a, int b, char* s);
void __cdecl fcn_00471b60(int a);
void __cdecl d2_SetForm(int a, int b);
int __cdecl io_AppendText(int a, ...);
int __cdecl fcn_00472250(int a, int b, int c);
int __cdecl fcn_004b3d80(int a, int b, int c);
int __cdecl fcn_004c5790(int a, void* b);
int __cdecl fcn_004c4450(int a);
void __cdecl fcn_00535960(void);
int __cdecl fcn_005373e0(void* a, int b);
void __cdecl fcn_00471e30(int a);
void __cdecl fcn_004b5530(int a, int b);
void __cdecl fcn_004b5b20(int a);
void __cdecl fcn_004230e0(int a);

/* The dialog message the three choice handlers send. Only three fields are
 * touched here; the native object is 0x7c bytes. */
typedef struct DLG_MSG {
	int id;
	char pad0[0xc];
	int vend;
	char pad1[0xc];
	int vunk;
	char pad2[0x58];
} DLG_MSG;

/* Mission announcement dialog for the special\mission sequence: opens the
 * dialog, resolves three choice strings, waits for the selection, then tears
 * the dialog and the arena down. Native body: 684 bytes, frame 0x190. */
/* ADDRESS: GOLDTL 0x004b5b40 */
void __cdecl fcn_004b5b40(int mode)
{
	DLG_MSG m1;
	DLG_MSG m2;
	DLG_MSG m3;
	int* obj;
	int changed;
	int arena_done;
	int flags;
	int r1;
	int r2;
	int r3;
	int q;
	int i;
	int h;
	char* slot;
	int dlg;

	changed = 0;
	arena_done = 0;
	obj = 0;
	slot = (char*) (0x7f4ca0 + (int) g_774970 * 0x21c);
	h = fcn_004b3c50(g_10069a0[0]);
	for (i = 0; i < 9; i++) {
		g_10069a0[i] = 0;
	}
	flags = (mode & ~9) | 0x100;
	fcn_004b5630(h, flags);
	dlg = fcn_00470820(0, 0, "special\\mission");
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1b95, *(unsigned short*) slot);
	r1 = fcn_00472250(dlg, 1, io_AppendText(0x1b96, 0x1b98));
	r2 = fcn_00472250(dlg, 1, io_AppendText(0x1b96, 0x1b99));
	r3 = fcn_00472250(dlg, 1, io_AppendText(0x1b96, 0x1b9a));
	flags |= 0x80;
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (g_67d370 == r1) {
				obj = (int*) fcn_004b3d80(*(int*) (slot + 4), (int) g_6a3440, 1);
				m1.id = *(int*) (slot + 4);
				m1.vend = 0;
				changed = 1;
				m1.vunk = *obj;
				q = fcn_004c5790(10, &m1);
				while (fcn_004c4450(q) == 0) {
					fcn_00535960();
				}
			}
			else if (g_67d370 == r2) {
				g_6a3440 = -1;
				m2.id = *(int*) (slot + 4);
				m2.vend = 0;
				m2.vunk = 0;
				q = fcn_004c5790(10, &m2);
				while (fcn_004c4450(q) == 0) {
					fcn_00535960();
				}
			}
			else if (g_67d370 == r3) {
				g_6a3440 = -1;
				m3.id = *(int*) (slot + 4);
				arena_done = 1;
				m3.vend = 1;
				m3.vunk = 0;
				q = fcn_004c5790(10, &m3);
				while (fcn_004c4450(q) == 0) {
					fcn_00535960();
				}
			}
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_004b5b40, flags) != 0);
	fcn_00471e30(dlg);
	if (changed) {
		fcn_004b5530(*obj, flags);
	}
	else if (arena_done) {
		fcn_004b5b20(flags);
	}
	if (g_7728dc != 0) {
		fcn_004230e0(g_7728dc);
	}
	g_7728dc = 0;
}
