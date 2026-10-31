int __cdecl fcn_005373e0(void* handler, int screen_id);

/* Screen arm body for the "Gesetze\Auswahl2" dialog (laws selection).
 *
 * Registry model: fcn_005373e0(handler, screen_id) stores the handler in
 * g_7e46ac, validates the screen id against an 8-byte-entry table at
 * 0x7e35c0 and the current slot record at 0x7f4ca0, and returns nonzero to
 * pump the screen again. This body registers itself as
 * fcn_005373e0(fcn_005cff20, 0x677c7) and loops on that result until it is 0.
 *
 * Called with four arguments by the small wrapper fcn_005d0460 after its
 * fcn_0050e520 dispatch check; the sibling arm for the other dispatch result
 * is the unrowed function at 0x5cff10, which the wrapper tail-jumps to.
 * arg1 is the dialog record pointer (null returns 0 early); its ushort at
 * +0x25 is compared with 0xffff. arg2 and arg3 are read inside.
 *
 * Body shape: frame 0x244, two returns, 413 instructions, 29 calls. It builds
 * the dialog with fcn_00470820(0, 0, "Gesetze\Auswahl2"), then 0x473a90 /
 * 0x471b60 / 0x4727a0 widget tree calls, 0x519190 and 0x51af00 text, 0x5cf720,
 * 0x46f740 / 0x4693b0 / 0x469470 / 0x50f980 drawing helpers, 0x46e830,
 * 0x46f2c0, 0x46fac0, 0x472900, 0x4677e0, 0x472380, 0x472640, 0x469c40,
 * one indirect callback (call ecx from a frame slot), holder release through
 * fcn_00469510 and final teardown fcn_00471e30. No jump tables, no asm. */

/* One lot/party record, stride 0x21c. */
typedef struct GOLDTL_House5cff {
	unsigned short id;              /* 0x000 */
	char pad2[0x16a];
	int f16c;                       /* 0x16c */
	int f170;                       /* 0x170 */
	char pad174[0x18];
	int f18c;                       /* 0x18c */
	char pad190[0x8c];
} GOLDTL_House5cff;                     /* SIZE 0x21c */

/* Entity type record, stride 0x24d. */
typedef struct GOLDTL_EntType5cff {
	unsigned char type;             /* 0x000 */
	char pad1[0x24c];
} GOLDTL_EntType5cff;                   /* SIZE 0x24d */

/* One selectable law row. */
typedef struct GOLDTL_LawSlot {
	int btn;                        /* 0x00 */
	int label;                      /* 0x04 */
	int name;                       /* 0x08 */
	int slider;                     /* 0x0c */
	int pad10;                      /* 0x10 */
	int id;                         /* 0x14 */
	int pad18[2];                   /* 0x18 */
} GOLDTL_LawSlot;                       /* SIZE 0x20 */

/* Screen geometry source (offsets 4/8 are the placement origin). */
typedef struct GOLDTL_Screen5cff {
	int pad0;
	int x;                          /* 0x04 */
	int y;                          /* 0x08 */
} GOLDTL_Screen5cff;

extern unsigned char* lpGebaeudePROT;
extern unsigned short g_774970;
extern int g_772514;
extern char* g_772500;
extern char* g_77255c;
extern int g_1015ea0;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;
extern int g_100f1dc;
extern char g_7f4ca0[];

void* __cdecl fcn_00470820(short, short, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(int, ...);
void __cdecl fcn_0046e830(int, int, int, int, int);
void __cdecl fcn_0046f2c0(int, int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl d2_CreateRadioGroup(int);
void __cdecl fcn_00469470(int, int);
float __cdecl fcn_0050f980(int, int, int);
int __cdecl fcn_005cf720(unsigned short, unsigned short, void*, int);
int __cdecl fcn_0046fac0(int, int, char*, int);
void __cdecl fcn_00472900(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_00469c40(int, int, int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);

/* ADDRESS: GOLDTL 0x005cff20 */
int __cdecl fcn_005cff20(unsigned char* rec, unsigned char* a2, int a3,
                         void (__cdecl* cb)(int, int))
{
	int n;
	int flag;
	int holder;
	int result;
	int shown;
	int v;
	int width;
	int dlg;
	int btn;
	int name;
	int slider;
	int progress;
	int dy;
	int y;
	int chosen;
	char text[0x20];
	GOLDTL_LawSlot slots[16];
	register unsigned short u1;
	register unsigned short u2;
	unsigned char type;
	GOLDTL_EntType5cff* ent;
	GOLDTL_House5cff* h;
	GOLDTL_LawSlot* s;
	int i;

	result = 0;
	holder = -1;
	n = 0;
	flag = 1;
	if (rec == 0) {
		return 0;
	}
	u1 = *(unsigned short*) (rec + 0x25);
	if (u1 != 0xffff) {
		slots[0].id = u1;
		n = 1;
	}
	u2 = *(unsigned short*) (rec + 0x27);
	if (u2 != 0xffff && u1 != u2) {
		slots[n].id = u2;
		n++;
	}
	ent = &((GOLDTL_EntType5cff*) lpGebaeudePROT)[*(unsigned char*) rec];
	type = ent->type;
	if (type == 1 || type == 2) {
		h = (GOLDTL_House5cff*) g_7f4ca0;
		do {
			if (n >= 16) {
				break;
			}
			if (h->f170 == (int) rec && h->id != u1 && h->id != u2) {
				slots[n].id = h->id;
				n++;
			}
			h++;
		} while ((int) h < 0x85a0a0);
	}
	if ((type > 3 && type < 10) || (type > 10 && type < 15) || type == 16
	    || (type > 17 && type < 23)) {
		h = (GOLDTL_House5cff*) g_7f4ca0;
		do {
			if (n >= 16) {
				break;
			}
			if (h->f16c == (int) rec && h->id != u1 && h->id != u2) {
				slots[n].id = h->id;
				n++;
			}
			h++;
		} while ((int) h < 0x85a0a0);
	}
	dlg = (int) fcn_00470820(0, 0, "Gesetze\\Auswahl2");
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(dlg);
	if (a3 != 0) {
		d2_SetForm(dlg, 1);
		io_AppendText(a3);
	}
	if (n > 2) {
		d2_SetForm(dlg, 2);
		v = g_772514;
		d2_SetForm(dlg, 0);
		fcn_0046e830(-1, -1, g_772514, v, 0x767);
	}
	g_100f1dc = -1;
	do {
		if (flag) {
			d2_SetForm(dlg, 2);
			fcn_0046f2c0(g_772514, 1);
			width = *(short*) (g_772500 + 0x1ec2c);
			dy = *(short*) (g_772500 + 0x1ec2e);
			if (n != 0) {
				y = 0x1e;
				for (i = 0; i < n; i++) {
					s = &slots[i];
					shown = 1;
					if (a2 != 0 && *(int*) (a2 + 4) != 0) {
						shown = fcn_005cf720(g_774970, (unsigned short) s->id,
						                     a2, (int) rec);
						if ((*(int*) a2 | shown) == 0) {
							continue;
						}
					}
					btn = fcn_0046f740(0x96, y, 0x5db, g_772514);
					s->btn = btn;
					if (shown) {
						if (holder == -1) {
							holder = d2_CreateRadioGroup(1);
						} else {
							fcn_00469470(holder, btn);
						}
					}
					progress = (int) fcn_0050f980(g_774970,
					                              (unsigned short) s->id, 1);
					s->label = fcn_0046f740(0x98, y + 1,
					                        ((GOLDTL_House5cff*) g_7f4ca0)[s->id].f18c,
					                        g_772514);
					io_FormatTextBuffer(text, 0x6a9680, s->id);
					name = fcn_0046fac0(0x96 - (0xa0 - width) / 2,
					                    dy + y - 0x46, text, g_772514);
					s->name = name;
					*(int*) (g_1015ea0 + name * 0x2f4 + 0x6c) = 1;
					*(int*) (g_1015ea0 + name * 0x2f4 + 0x18) = 0xa0;
					fcn_00472900(name, 0x56);
					*(int*) (g_1015ea0 + btn * 0x2f4 + 0x5c) = shown;
					*(int*) (g_1015ea0 + btn * 0x2f4 + 0x60) = (shown == 0);
					slider = fcn_004677e0(0x8c, dy + y + 4, 0x40, 0, 0x64,
					                      0x75, 0x442, g_772514);
					s->slider = slider;
					fcn_00472380(slider, 0, 0x64, progress);
					fcn_00472640(slider, 0);
					fcn_00469c40(((GOLDTL_Screen5cff*) g_77255c)->x
					                 - (*(int*) (g_1015ea0 + slider * 0x2f4 + 0x18) - width) / 2
					                 + 0x96,
					             ((GOLDTL_Screen5cff*) g_77255c)->y + y + 4 + dy,
					             slider);
					y += 0x5a;
				}
			}
			flag = 0;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1 && n > 0) {
			for (i = 0; i < n; i++) {
				if (g_67d370 == slots[i].btn) {
					if (i >= 0) {
						chosen = (int) &((GOLDTL_House5cff*) g_7f4ca0)[slots[i].id];
						result = chosen;
						if (cb == 0) {
							g_774654 = 1;
						} else {
							cb(chosen, (int) rec);
							flag = 1;
							if (holder != -1) {
								fcn_00469510(holder);
							}
							holder = -1;
						}
					}
					break;
				}
			}
		}
	} while (fcn_005373e0((void*) fcn_005cff20, 0x677c7) != 0);
	if (holder != -1) {
		fcn_00469510(holder);
	}
	fcn_00471e30(dlg);
	return result;
}
