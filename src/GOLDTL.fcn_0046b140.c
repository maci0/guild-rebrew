typedef struct Slot {
	int id;
	int used;
	int value;
	int pad0c;
	int x;
	int y;
	int w;
	int h;
	int type;
	char pad24[0x30 - 0x24];
	int top;
	int bottom;
	char pad38[0x40 - 0x38];
	char* link;
	int pad44;
	int hidden48;
	int hidden4c;
	char* owner;
	char pad54[0x88 - 0x54];
	int result;
	char pad8c[0x2f4 - 0x8c];
} Slot;
// SIZE 0x2f4

extern Slot* g_1015ea0;
extern Slot** g_772540;
extern int g_67d388;
extern int g_67d370;

// FUNCTION: GOLDTL 0x46b140
// SIZE: 203
int __cdecl fcn_0046b140(int x, int y)
{
	int i;
	int hidden;
	Slot* s;
	int id;

	g_67d388 = -1;
	for (i = 0x3ff; i >= 0; i--) {
		hidden = 0;
		s = g_772540[i];
		if (s) {
			if (s->owner) {
				hidden = *(int*) (s->owner + 0x198);
			}
			if (x >= s->x && x <= s->x + s->w && y >= s->y && y <= s->y + s->h && !hidden && y >= s->top && y <= s->bottom && !s->hidden4c && !s->hidden48) {
				id = s->id;
				g_67d370 = id;
				if (g_1015ea0[id].type == 0x40) {
					g_67d388 = s->result;
					return g_67d388;
				}
				if (s->link) {
					g_67d388 = *(int*) (s->link + 0x27c);
				}
				return s->value;
			}
		}
	}
	g_67d370 = -1;
	return -1;
}
