typedef struct Ent {
	unsigned short id;
	char pad2[0x7f];
	unsigned char b81;
	unsigned char b82;
	unsigned char b83;
	unsigned char b84;
	char pad85[0x165 - 0x85];
	unsigned char alive;
	char pad166[6];
	int owner;
	char pad170[0xc];
	unsigned char* job;
	char pad180[0x34];
	int flags;
	char pad1b8[0x10];
	int state;
	char pad1cc[0x21c - 0x1cc];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];

unsigned short __cdecl fcn_0042e410(int n);

// FUNCTION: GOLD 0x489470
// SIZE: 480
// FUNCTION: GOLDTL 0x00488a20
// SIZE: 471
int __cdecl fcn_00488a20(Ent* e)
{
	int found;
	int i;

	if (e->state & 4) {
		return 0;
	}
	e->state |= 4;
	found = 0;
	for (i = 0; !found && i < 768; i++) {
		if (((Ent*)g_7f4ca0)[i].id != 0xffff && ((Ent*)g_7f4ca0)[i].owner == e->owner && ((Ent*)g_7f4ca0)[i].alive != 0
		    && (((Ent*)g_7f4ca0)[i].job == 0 || *((Ent*)g_7f4ca0)[i].job == 4 || *((Ent*)g_7f4ca0)[i].job == 0x8c) && (((Ent*)g_7f4ca0)[i].state & 4) == 0) {
			if (((Ent*)g_7f4ca0)[i].b81 < 168.0f || ((Ent*)g_7f4ca0)[i].b82 < 168.0f || ((Ent*)g_7f4ca0)[i].b84 < 168.0f) {
				found = 1;
			}
		}
	}
	if (found && fcn_0042e410(0x80) < 0x60) {
		return 0;
	}
	if (!found && (((Ent*)g_7f4ca0)[i].b81 < 252.0f || ((Ent*)g_7f4ca0)[i].b82 < 252.0f || ((Ent*)g_7f4ca0)[i].b84 < 252.0f) && fcn_0042e410(0x80) > 0x20) {
		return 0;
	}
	for (i = 0; i < 768; i++) {
		if (((Ent*)g_7f4ca0)[i].id != 0xffff && ((Ent*)g_7f4ca0)[i].owner == e->owner && ((Ent*)g_7f4ca0)[i].alive != 0
		    && (((Ent*)g_7f4ca0)[i].job == 0 || *((Ent*)g_7f4ca0)[i].job == 4 || *((Ent*)g_7f4ca0)[i].job == 0x8c) && (((Ent*)g_7f4ca0)[i].state & 4) == 0) {
			((Ent*)g_7f4ca0)[i].flags |= 0x10;
		}
	}
	return 1;
}
