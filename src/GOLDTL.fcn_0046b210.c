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

extern char* g_1015ea0;
extern int g_772528;
extern int g_67d370;

// FUNCTION: GOLDTL 0x46b210
int __cdecl fcn_0046b210(int x, int y)
{
	int i;
	Slot* s;

	for (i = g_772528; i >= 0; i--) {
		s = &((Slot*)g_1015ea0)[i];
		if (x >= s->x && x <= s->x + s->w && y >= s->y && y <= s->y + s->h && s->type == 0x40) {
			if (s->used == 0) {
				break;
			}
			if (y >= s->top && y <= s->bottom && s->hidden4c == 0) {
				g_67d370 = i;
				return s->value;
			}
		}
	}
	g_67d370 = -1;
	return -1;
}
