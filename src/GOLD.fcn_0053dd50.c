// FUNCTION: GOLD 0x0053dd50
// SIZE: 438

// SIZE 0xc
struct slot {
	unsigned char* obj;
	int ctl;
	int dlg;
};

// SIZE 0x2ec
struct gadget {
	char pad0[0x28];
	int focus;
	int hot;
	char pad30[0x2bc];
};

extern int g_62571c;
extern struct slot* g_6f262c;
extern struct slot g_6faa80[16];
extern char* g_f8f080;
extern unsigned char g_6f23f8;
extern int g_6333e0;

void __cdecl fcn_00475580(int, int);
void __cdecl fcn_00474190(int);

void __cdecl fcn_0053dd50(void)
{
	int i;
	unsigned char* o;

	if (g_62571c == -1) {
		return;
	}
	if (g_6f262c != 0 && g_6f262c->ctl != -1 && ((struct gadget*)g_f8f080)[g_6f262c->ctl].focus == 0) {
		if (g_6f262c->dlg != 0) {
			fcn_00475580(g_6f262c->dlg, 0);
		}
		o = g_6f262c->obj;
		if (o != 0 && ((o[0] == 0x11 && (o[0xf0] & 0x40) != 0) || o[0] == 0x87) && (g_6f23f8 & 4) == 0) {
			g_6333e0 = 0;
		}
		g_6f262c = 0;
	}
	for (i = 0; i < 16; i++) {
		if (g_6faa80[i].ctl != -1 && g_6f262c != &g_6faa80[i] && ((struct gadget*)g_f8f080)[g_6faa80[i].ctl].focus != 0) {
			if (g_6f262c != 0 && g_6f262c->dlg != -1) {
				if (g_6f262c->dlg != 0) {
					fcn_00475580(g_6f262c->dlg, 0);
				}
				if (g_6f262c->ctl != -1) {
					((struct gadget*)g_f8f080)[g_6f262c->ctl].focus = 0;
					((struct gadget*)g_f8f080)[g_6f262c->ctl].hot = 0;
				}
				o = g_6f262c->obj;
				if (o != 0 && ((o[0] == 0x11 && (o[0xf0] & 0x40) != 0) || o[0] == 0x87) && (g_6f23f8 & 4) == 0) {
					g_6333e0 = 0;
				}
			}
			/* literal address: c2 must assume it may alias the slot read below,
			 * which schedules the store ahead of the load as the original does */
			*(struct slot**) 0x6f262c = &g_6faa80[i];
			fcn_00475580(g_6faa80[i].dlg, 1);
			fcn_00474190(g_6f262c->dlg);
			o = g_6f262c->obj;
			if (o != 0 && ((o[0] == 0x11 && (o[0xf0] & 0x40) != 0) || o[0] == 0x87) && (g_6f23f8 & 4) == 0) {
				g_6333e0 = 1;
			}
		}
	}
}
