/* Picker screen arm for the supplier/slot dialog.
 *
 * Body shape: creates the dialog context with fcn_00470820(0, 0, 0x6a969c),
 * registers the eight widget rows (fcn_004727a0 0,1,2,3,6,4,5,7), feeds the
 * title through the fcn_00519190 markup expander, fills the local dialog block
 * through the three widget ctors (fcn_0058b030 selection list, fcn_0058b1f0
 * slot rows, fcn_0058b440 trade rows), then loops while
 * fcn_005373e0(0x58bb10, 0x677c7) asks for another pass. Each pass rescans the
 * focus handle at 0x67d370 against the three candidate tables, rebuilds only
 * the groups whose dirty bits are set, and hands the focus change to the
 * per-case callback while gating with fcn_00471af0. The selection result goes
 * to arg1.
 *
 * Native extent 0x58bb10-0x58bfc4 (0x4b4 bytes): frame 0x1dc, one ret, 334
 * instructions, 31 calls, 70 pushes, one indirect call through the callback
 * argument. The three caller arms (0x58fa20, 0x58fb60, 0x58fba0) forward
 * (0, entity, table pointer, selector, callback) and each ends with a jump to
 * 0x532ef0. */

typedef struct {
	int btn;                        /* 0x00 focus widget handle */
	char* item;                     /* 0x04 */
	int id;                         /* 0x08 */
	char kind;                      /* 0x0c */
	char pad0d[3];
} DialogEntry;                          /* SIZE 0x10 */

typedef struct {
	int handle;                     /* 0x000 */
	int filter;                     /* 0x004 */
	int slot;                       /* 0x008 */
	char pad0c[0x08];
	int owner;                      /* 0x014 */
	char pad18[0x18];               /* 0x018, overlays SelDlg::ids */
	int type;                       /* 0x030 */
	DialogEntry entries[16];        /* 0x034 */
	int selected;                   /* 0x134 */
} DialogState;                          /* SIZE 0x138 */

typedef struct {
	int dlg;                        /* 0x00 */
	char pad4[0x0c];
	int font;                       /* 0x10 */
	char pad14[0x0c];
	int ids[4];                     /* 0x20 */
	int sel;                        /* 0x30 */
} SelDlg;                               /* SIZE 0x34 */

typedef struct {
	char* item;                     /* 0x00 */
	int value;                      /* 0x04 */
	unsigned char kind;             /* 0x08 */
	char pad09[3];
	char* item2;                    /* 0x0c */
	int value2;                     /* 0x10 */
} PickResult;                           /* SIZE 0x14 */

extern int g_772514;
extern int g_67d370;
extern int g_6b7fac;
extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_774654;
extern char g_6a9694[];
extern char g_6a969c[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(void);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_0058b030(char*, SelDlg*);
void __cdecl fcn_0058b1f0(char*, DialogState*, unsigned int);
void __cdecl fcn_0058b440(unsigned int, unsigned int*, int, int);
char __cdecl fcn_004f1790(int, void*);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x0058bb10 */
void __cdecl fcn_0058bb10(PickResult* a0, char* a1, int a2, int a3,
			  void (__cdecl* a4)(char*, PickResult*))
{
	SelDlg sel;
	DialogState st;
	int rows[8][3];
	PickResult rec;
	int ctx;
	int saved;
	int deadline;
	int cur;
	int selft;
	int i;
	int flags;
	int found;

	if (a0 != 0) {
		a0->item = 0;
		a0->item2 = 0;
	}
	ctx = fcn_00470820(0, 0, g_6a969c);
	fcn_00473a90();
	fcn_00471b60(ctx);
	d2_SetForm(ctx, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(ctx, 1);
	saved = g_772514;
	fcn_00519190((int) g_6a9694, a2);
	d2_SetForm(ctx, 2);
	d2_SetForm(ctx, 3);
	d2_SetForm(ctx, 6);
	d2_SetForm(ctx, 4);
	d2_SetForm(ctx, 5);
	d2_SetForm(ctx, 7);

	fcn_0058b030(a1, &sel);
	fcn_0058b1f0(a1, &st, 0xffffffff);
	fcn_0058b440((unsigned int) a1, (unsigned int*) &st, -1, a3);
	g_100f1dc = -1;
	deadline = g_6b7fac + 0x96;

	for (;;) {
		flags = 0;
		cur = st.selected;
		selft = 0;
		found = 0;
		if (g_6b7fac > deadline) {
			flags = 7;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			for (i = 0; i < 4; i++) {
				if (sel.ids[i] == g_67d370 && i != cur) {
					selft = i;
					cur = i;
					st.selected = 0;
					flags |= 7;
					found = 1;
					break;
				}
			}
			if (found == 0) {
				for (i = 0; i < 16; i++) {
					if (st.entries[i].btn == g_67d370 && i != cur) {
						cur = i;
						st.selected = i;
						flags |= 3;
						found = 1;
						break;
					}
				}
			}
			if (a3 == 0) {
				if (found == 0) {
					for (i = 0; i < 8; i++) {
						if (rows[i][0] != g_67d370) {
							continue;
						}
						found = 1;
						if (a0 != 0) {
							a0->item = st.entries[selft].item;
							a0->value = *(int*) a0->item;
							a0->kind = (unsigned char) fcn_004f1790(*(int*) (a1 + 0x65), a0->item);
							a0->item2 = (char*) rows[i][2];
							a0->value2 = *(int*) a0->item2;
						}
						if (a4 == 0) {
							if (a0 != 0) {
								g_774654 = 1;
							}
							break;
						}
						rec.item = st.entries[selft].item;
						rec.value = *(int*) rec.item;
						rec.kind = (unsigned char) fcn_004f1790(*(int*) (a1 + 0x65), rec.item);
						rec.item2 = (char*) rows[i][2];
						rec.value2 = *(int*) rec.item2;
						fcn_00471af0(ctx, 0);
						a4(a1, &rec);
						fcn_00471af0(ctx, 1);
						break;
					}
				}
			} else if (a3 == 1 && st.entries[cur].btn == g_67d370) {
				if (a0 != 0) {
					a0->item = st.entries[selft].item;
					a0->value = *(int*) a0->item;
					a0->kind = (unsigned char) fcn_004f1790(*(int*) (a1 + 0x65), a0->item);
					a0->item2 = 0;
					a0->value2 = -1;
				}
				if (a4 == 0) {
					if (a0 != 0) {
						g_774654 = 1;
					}
				} else {
					rec.item = st.entries[selft].item;
					rec.value = *(int*) rec.item;
					rec.kind = (unsigned char) fcn_004f1790(*(int*) (a1 + 0x65), rec.item);
					rec.item2 = 0;
					rec.value2 = -1;
					fcn_00471af0(ctx, 0);
					a4(a1, &rec);
					fcn_00471af0(ctx, 1);
				}
			}
		}
		if (flags & 4) {
			fcn_0058b030(a1, &sel);
			cur = selft;
		}
		if (flags & 2) {
			fcn_0058b1f0(a1, &st, saved);
			cur = selft;
		}
		if (flags & 1) {
			fcn_0058b440((unsigned int) a1, (unsigned int*) &st, cur, a3);
			cur = selft;
		}
		if (fcn_005373e0((void*) 0x58bb10, 0x677c7) == 0) {
			fcn_00471e30(ctx);
			return;
		}
	}
}
