// FUNCTION: GOLDTL 0x545aa0
// SIZE: 422

// SIZE 0xc
struct slot {
	unsigned char* obj;
	int ctl;
	int dlg;
};

// SIZE 0x2f4
struct gadget {
	char pad0[0x38];
	int focus;
	int hot;
	char pad40[0x2b4];
};

extern int g_6a476c;
extern struct slot* g_7749e4;
extern struct slot g_77e8c0[16];
extern struct gadget* g_1015ea0;
extern unsigned char g_7747b0;
extern int g_6b7fc0;

void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_004707d0(int);

void __cdecl fcn_00545aa0(void)
{
	int i;
	unsigned char* o;

	if (g_6a476c == -1) {
		return;
	}
	if (g_7749e4 != 0 && g_7749e4->ctl != -1 && g_1015ea0[g_7749e4->ctl].focus == 0) {
		if (g_7749e4->dlg != 0) {
			fcn_00471af0(g_7749e4->dlg, 0);
		}
		o = g_7749e4->obj;
		if (o != 0 && ((o[0] == 0x11 && (o[0xf0] & 0x40) != 0) || o[0] == 0x87) && (g_7747b0 & 4) == 0) {
			g_6b7fc0 = 0;
		}
		g_7749e4 = 0;
	}
	for (i = 0; i < 16; i++) {
		if (g_77e8c0[i].ctl != -1 && g_7749e4 != &g_77e8c0[i] && g_1015ea0[g_77e8c0[i].ctl].focus != 0) {
			if (g_7749e4 != 0 && g_7749e4->dlg != -1) {
				if (g_7749e4->dlg != 0) {
					fcn_00471af0(g_7749e4->dlg, 0);
				}
				if (g_7749e4->ctl != -1) {
					g_1015ea0[g_7749e4->ctl].focus = 0;
					g_1015ea0[g_7749e4->ctl].hot = 0;
				}
				o = g_7749e4->obj;
				if (o != 0 && ((o[0] == 0x11 && (o[0xf0] & 0x40) != 0) || o[0] == 0x87) && (g_7747b0 & 4) == 0) {
					g_6b7fc0 = 0;
				}
			}
			/* literal address: c2 must assume it may alias the slot read below,
			 * which schedules the store ahead of the load as the original does */
			*(struct slot**) 0x7749e4 = &g_77e8c0[i];
			fcn_00471af0(g_77e8c0[i].dlg, 1);
			fcn_004707d0(g_7749e4->dlg);
			o = g_7749e4->obj;
			if (o != 0 && ((o[0] == 0x11 && (o[0xf0] & 0x40) != 0) || o[0] == 0x87) && (g_7747b0 & 4) == 0) {
				g_6b7fc0 = 1;
			}
		}
	}
}
