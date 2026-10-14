typedef struct Ent {
	unsigned short id;
	char pad2[0x80];
	unsigned char food;
	unsigned char rest;
	char pad84[0x165 - 0x84];
	unsigned char alive;
	char pad166[6];
	int owner;
	char pad170[0xc];
	int task;
	char pad180[0x34];
	int flags;
	char pad1b8[0x10];
	int state;
	char pad1cc[0x21c - 0x1cc];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];

unsigned short __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLD 0x004892f0 */
/* ADDRESS: GOLDTL 0x004888a0 */
int __cdecl fcn_004888a0(Ent* e)
{
	int found;
	int i;

	if (e->state & 4) {
		return 0;
	}
	e->state |= 4;
	found = 0;
	for (i = 0; !found && i < 768; i++) {
		if (((Ent*)g_7f4ca0)[i].id != 0xffff && ((Ent*)g_7f4ca0)[i].owner == e->owner && ((Ent*)g_7f4ca0)[i].alive != 0 && ((Ent*)g_7f4ca0)[i].task == 0 && (((Ent*)g_7f4ca0)[i].state & 4) == 0) {
			if (((Ent*)g_7f4ca0)[i].rest < 168.0f || ((Ent*)g_7f4ca0)[i].food < 168.0f) {
				found = 1;
			}
		}
	}
	if (found && gm_RandomMod(0x80) < 0x20) {
		return 0;
	}
	if (!found && (((Ent*)g_7f4ca0)[i].rest < 252.0f || ((Ent*)g_7f4ca0)[i].food < 252.0f) && gm_RandomMod(0x80) > 0x60) {
		return 0;
	}
	for (i = 0; i < 768; i++) {
		if (((Ent*)g_7f4ca0)[i].id != 0xffff && ((Ent*)g_7f4ca0)[i].owner == e->owner && ((Ent*)g_7f4ca0)[i].alive != 0 && ((Ent*)g_7f4ca0)[i].task == 0 && (((Ent*)g_7f4ca0)[i].state & 4) == 0) {
			((Ent*)g_7f4ca0)[i].flags |= 0x10;
		}
	}
	return 1;
}
