typedef struct Slot {
	char pad0[0x20];
	int type;
	char pad24[0x88 - 0x24];
	int result;
	char pad8c[0x2f4 - 0x8c];
} Slot;
// SIZE 0x2f4

typedef struct Anim {
	char* seq;
	char frame;
	char pad5[7];
	char running;
	char padd[7];
} Anim;
// SIZE 0x14

extern Slot* g_1015ea0;
extern Anim g_100e7a0[];

// FUNCTION: GOLDTL 0x473030
// SIZE: 131
void __cdecl fcn_00473030(int slot, char mode)
{
	Slot* s;

	if (slot > 0x400) {
		return;
	}
	s = &g_1015ea0[slot];
	if (s->type != 4) {
		return;
	}
	if (mode == 0) {
		g_100e7a0[s->result].frame = 0;
		g_100e7a0[s->result].running = 0;
	} else if (mode == 1) {
		g_100e7a0[s->result].frame = g_100e7a0[s->result].seq[0x16] - 1;
		g_100e7a0[s->result].running = 1;
	}
}
