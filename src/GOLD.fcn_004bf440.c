extern char* g_f8f080;
extern char* g_6f0754;

struct slot_4bf440 {
	int id;
	char* obj;
	char pad8[0x10];
};
// SIZE 0x18

struct panel_4bf440 {
	char pad0[0xdc];
	struct slot_4bf440 slots[412];
	char pad277c[0x28];
	int count;
};
// SIZE 0x27a8

/* ADDRESS: GOLD 0x004bf440 */

void __cdecl fcn_004bf440(char* list, struct panel_4bf440* panel)
{
	char* out[8];
	char** p;
	char* n;
	int i;

	for (i = 0; i < panel->count; i++) {
		if (panel->slots[i].obj != 0) {
			if (panel->slots[i].obj != g_6f0754) {
				*(int*) (g_f8f080 + panel->slots[i].id * 748 + 0x1c0) |= 1;
				*(int*) (g_f8f080 + panel->slots[i].id * 748 + 0x2c) = 0;
			} else {
				*(int*) (g_f8f080 + panel->slots[i].id * 748 + 0x1c0) &= ~1;
				*(int*) (g_f8f080 + panel->slots[i].id * 748 + 0x2c) = 1;
			}
		}
	}
	n = list;
	if (n != 0) {
		p = out;
		do {
			for (i = 0; i < panel->count; i++) {
				if (panel->slots[i].obj != 0 && *(int*) (panel->slots[i].obj + 1) == *(int*) (n + 4)) {
					*(int*) (g_f8f080 + panel->slots[i].id * 748 + 0x2c) = 1;
					*(int*) (g_f8f080 + panel->slots[i].id * 748 + 0x1c0) &= ~1;
					*p++ = panel->slots[i].obj;
					break;
				}
			}
			n = *(char**) (n + 0x3c);
		} while (n != 0);
	}
}
