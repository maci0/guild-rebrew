// FUNCTION: GOLDTL 0x469090
// SIZE: 128
// y = s->y assigned after x in each arm schedules the load between the two
// divisions.

typedef struct Rect0469090 {
	int pad0;
	int left;
	int pad8;
	int width;
} Rect0469090;

typedef struct Slot0469090 {
	char pad0[0x14];
	int y;
	int width;
	char pad1c[0x40 - 0x1c];
	Rect0469090* link;
	char pad44[0x6c - 0x44];
	int used;
	char pad70[0x2f4 - 0x70];
} Slot0469090;
// SIZE 0x2f4

extern char* g_1015ea0;
extern int g_1040494;

void __cdecl fcn_00469c40(int x, int y, int slot);

void __cdecl fcn_00469090(int slot)
{
	Slot0469090* s;
	Rect0469090* r;
	int x;
	int y;

	s = &((Slot0469090*)g_1015ea0)[slot];
	if (s->used != 0) {
		r = s->link;
		if (r != 0) {
			x = r->width / 2 - s->width / 2 + r->left;
			y = s->y;
		} else {
			x = g_1040494 / 2 - s->width / 2;
			y = s->y;
		}
		fcn_00469c40(x, y, slot);
	}
}
