typedef struct Ent {
	unsigned short id;
	unsigned char kind;
	char pad3[0x165 - 3];
	unsigned char role;
	char pad166[0x16c - 0x166];
	char* home;
	char pad170[0x184 - 0x170];
	char* job;
	char pad188[0x1b4 - 0x188];
	unsigned int flags;
	char pad1b8[0x21c - 0x1b8];
} Ent;
// SIZE 0x21c

extern Ent g_7f4ca0[768];
extern short g_7f4c04;

float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_005904a0(Ent* e, int a2);

// FUNCTION: GOLD 0x483ed0
// SIZE: 224
// FUNCTION: GOLDTL 0x4833a0
// SIZE: 212
void __cdecl fcn_004833a0(Ent* e)
{
	Ent* found;
	int i;

	found = 0;
	if (g_7f4c04 != 7 && g_7f4c04 != 0xc && g_7f4c04 != 0x12) {
		e->flags &= ~0x1000;
		return;
	}
	if (e->flags & 0x1000) {
		return;
	}
	e->flags |= 0x1000;
	for (i = 0; found == 0 && i < 768; i++) {
		if (g_7f4ca0[i].id != 0xffff && g_7f4ca0[i].home == e->home && g_7f4ca0[i].role == 0x1c && g_7f4ca0[i].kind == 0x14
		    && (g_7f4ca0[i].flags & 1) && g_7f4ca0[i].job && *(int*) (g_7f4ca0[i].job + 0x2c) == *(int*) (g_7f4ca0[i].home + 1)) {
			found = &g_7f4ca0[i];
		}
	}
	if (found && gm_RandomFloat01() > 0.75f) {
		fcn_005904a0(found, 0);
	}
}
