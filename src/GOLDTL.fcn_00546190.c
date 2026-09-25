// FUNCTION: GOLD 0x0053e450
// SIZE: 260
// FUNCTION: GOLDTL 0x546190
// SIZE: 260

#include <string.h>

// SIZE 0xc
struct slot {
	void* obj;
	int ctl;
	int dlg;
};

// SIZE 0x14c
struct unit {
	unsigned char kind;
	char pad1[0x73];
	struct slot* slot;
	unsigned char flags;
	char pad79[3];
	int sound;
	char pad80[0xcc];
};

extern struct unit* g_7d1980[256];
extern struct unit g_77e980[1024];
extern int g_7749d4;
extern int g_7749d8;
extern int g_7dc424;

void __cdecl fcn_0041ddd0(int);
void __cdecl fcn_00545780(struct unit*);

void __cdecl fcn_00546190(struct unit* u)
{
	int i;
	int n;

	if (u == 0) {
		return;
	}
	if (u->sound != 0) {
		fcn_0041ddd0(u->sound);
		u->sound = 0;
	}
	if (u->flags & 8) {
		for (i = 0; i < 256; i++) {
			if (g_7d1980[i] == u) {
				break;
			}
		}
		if (g_7d1980[i] != u) {
			return;
		}
		if (g_7d1980[i]->slot != 0 && g_7d1980[i]->slot->dlg != -1) {
			fcn_00545780(g_7d1980[i]);
		}
		g_7d1980[i] = 0;
		if (i == g_7749d8) {
			for (n = g_7749d8; n >= 0; n--) {
				if (g_7d1980[n] != 0) {
					break;
				}
			}
			g_7749d8 = n < 0 ? 0 : n;
		}
	}
	g_7dc424--;
	memset(u, 0, sizeof(struct unit));
	if (u == &g_77e980[g_7749d4]) {
		for (n = g_7749d4; n >= 0; n--) {
			if (g_77e980[n].kind != 0) {
				break;
			}
		}
		g_7749d4 = n < 0 ? 0 : n;
	}
}
